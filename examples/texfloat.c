/*
 * GL_ARB_texture_float render test for OSMesa.
 *
 * Tests:
 *   1. Extension is advertised
 *   2. RGBA32F and RGB32F texture creation and upload
 *   3. GLSL shader reads float texture at full precision (including HDR > 1.0)
 *   4. Render-to-float-texture via FBO (validates store_texel and texrender fixes)
 *
 * This program is in the public domain.
 */

#define _USE_MATH_DEFINES
#define GL_GLEXT_PROTOTYPES
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "OSMesa/gl.h"
#include "OSMesa/glext.h"
#include "OSMesa/osmesa.h"

/* ------------------------------------------------------------------ */
/* Shader helpers                                                      */
/* ------------------------------------------------------------------ */

static GLuint
compile_shader(GLenum type, const char *src)
{
    GLuint s = glCreateShader(type);
    glShaderSource(s, 1, &src, NULL);
    glCompileShader(s);

    GLint ok = 0;
    glGetShaderiv(s, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        char log[1024];
        glGetShaderInfoLog(s, sizeof(log), NULL, log);
        fprintf(stderr, "Shader compile error: %s\n", log);
        glDeleteShader(s);
        return 0;
    }
    return s;
}

static GLuint
make_program(const char *vert_src, const char *frag_src)
{
    GLuint vert = compile_shader(GL_VERTEX_SHADER, vert_src);
    GLuint frag = compile_shader(GL_FRAGMENT_SHADER, frag_src);
    if (!vert || !frag) return 0;

    GLuint prog = glCreateProgram();
    glAttachShader(prog, vert);
    glAttachShader(prog, frag);
    glLinkProgram(prog);

    GLint ok = 0;
    glGetProgramiv(prog, GL_LINK_STATUS, &ok);
    if (!ok) {
        char log[1024];
        glGetProgramInfoLog(prog, sizeof(log), NULL, log);
        fprintf(stderr, "Program link error: %s\n", log);
        glDeleteProgram(prog);
        prog = 0;
    }

    glDeleteShader(vert);
    glDeleteShader(frag);
    return prog;
}

/* ------------------------------------------------------------------ */
/* Draw a fullscreen quad textured with the currently bound texture.  */
/* ------------------------------------------------------------------ */
static void
draw_fullscreen_quad(void)
{
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);  glVertex2f(-1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f);  glVertex2f( 1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f);  glVertex2f( 1.0f,  1.0f);
    glTexCoord2f(0.0f, 1.0f);  glVertex2f(-1.0f,  1.0f);
    glEnd();
}

/* ------------------------------------------------------------------ */
/* Check GL errors, return 1 if any occurred                          */
/* ------------------------------------------------------------------ */
static int
check_gl_error(const char *where)
{
    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        fprintf(stderr, "GL error 0x%x at %s\n", (unsigned)err, where);
        return 1;
    }
    return 0;
}

/* ------------------------------------------------------------------ */
/* Main test                                                           */
/* ------------------------------------------------------------------ */

int
main(void)
{
    int failed = 0;
    int W = 4, H = 4;   /* small framebuffer is enough */

    /* ---- Create OSMesa context & framebuffer (8-bit RGBA) ---- */
    OSMesaContext ctx = OSMesaCreateContextExt(OSMESA_RGBA, 16, 0, 0, NULL);
    if (!ctx) {
        fprintf(stderr, "OSMesaCreateContext failed\n");
        return 1;
    }

    GLubyte *fb = (GLubyte *)calloc(W * H * 4, sizeof(GLubyte));
    if (!fb) {
        fprintf(stderr, "Out of memory\n");
        OSMesaDestroyContext(ctx);
        return 1;
    }

    if (!OSMesaMakeCurrent(ctx, fb, GL_UNSIGNED_BYTE, W, H)) {
        fprintf(stderr, "OSMesaMakeCurrent failed\n");
        free(fb);
        OSMesaDestroyContext(ctx);
        return 1;
    }
    OSMesaPixelStore(OSMESA_Y_UP, 0);

    /* ---- Test 1: extension is advertised ---- */
    {
        const char *exts = (const char *)glGetString(GL_EXTENSIONS);
        if (!exts || !strstr(exts, "GL_ARB_texture_float")) {
            fprintf(stderr, "FAIL Test 1: GL_ARB_texture_float not in extensions\n");
            failed++;
        } else {
            printf("PASS Test 1: GL_ARB_texture_float advertised\n");
        }
    }

    /* ---- Test 2: texture creation with float internal formats ---- */
    {
        /* 2x2 RGBA32F texture */
        GLfloat data[2*2*4] = {
            0.25f, 0.50f, 0.75f, 1.0f,   /* texel (0,0) */
            0.10f, 0.20f, 0.30f, 1.0f,   /* texel (1,0) */
            0.40f, 0.60f, 0.80f, 1.0f,   /* texel (0,1) */
            0.05f, 0.15f, 0.95f, 1.0f,   /* texel (1,1) */
        };

        GLuint tex;
        glGenTextures(1, &tex);
        glBindTexture(GL_TEXTURE_2D, tex);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F_ARB, 2, 2, 0,
                     GL_RGBA, GL_FLOAT, data);

        if (check_gl_error("glTexImage2D GL_RGBA32F_ARB")) {
            fprintf(stderr, "FAIL Test 2a: GL_RGBA32F_ARB texture creation failed\n");
            failed++;
        } else {
            printf("PASS Test 2a: GL_RGBA32F_ARB texture created\n");
        }

        /* Also test RGB32F */
        GLfloat rgb_data[2*2*3] = {
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 0.0f,
        };
        GLuint tex2;
        glGenTextures(1, &tex2);
        glBindTexture(GL_TEXTURE_2D, tex2);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F_ARB, 2, 2, 0,
                     GL_RGB, GL_FLOAT, rgb_data);

        if (check_gl_error("glTexImage2D GL_RGB32F_ARB")) {
            fprintf(stderr, "FAIL Test 2b: GL_RGB32F_ARB texture creation failed\n");
            failed++;
        } else {
            printf("PASS Test 2b: GL_RGB32F_ARB texture created\n");
        }

        glDeleteTextures(1, &tex);
        glDeleteTextures(1, &tex2);
    }

    /* ---- Test 3: GLSL shader reads float texture at expected precision ---- */
    /* A 1x1 RGBA32F texture with value (0.3, 0.6, 0.9, 1.0).
     * A pass-through fragment shader outputs the texture sample.
     * Read back via 8-bit framebuffer; verify R≈0.3, G≈0.6, B≈0.9 within
     * 1/255 tolerance (one quantization step).                               */
    {
        const char *vert =
            "#version 110\n"
            "void main() {\n"
            "    gl_Position = gl_Vertex;\n"
            "    gl_TexCoord[0] = gl_MultiTexCoord0;\n"
            "}\n";
        const char *frag =
            "#version 110\n"
            "uniform sampler2D tex;\n"
            "void main() {\n"
            "    gl_FragColor = texture2D(tex, gl_TexCoord[0].xy);\n"
            "}\n";

        GLuint prog = make_program(vert, frag);
        if (!prog) {
            fprintf(stderr, "FAIL Test 3: shader compilation failed\n");
            failed++;
        } else {
            GLfloat texdata[4] = { 0.3f, 0.6f, 0.9f, 1.0f };
            GLuint tex;
            glGenTextures(1, &tex);
            glBindTexture(GL_TEXTURE_2D, tex);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F_ARB, 1, 1, 0,
                         GL_RGBA, GL_FLOAT, texdata);

            glUseProgram(prog);
            glUniform1i(glGetUniformLocation(prog, "tex"), 0);

            glViewport(0, 0, W, H);
            glClearColor(0, 0, 0, 0);
            glClear(GL_COLOR_BUFFER_BIT);
            draw_fullscreen_quad();
            glFinish();

            /* Read back as 8-bit ubyte */
            GLubyte pixel[4] = { 0, 0, 0, 0 };
            glReadPixels(W/2, H/2, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixel);
            check_gl_error("glReadPixels Test 3");

            /* Convert expected floats to 8-bit and allow ±1 */
            int expR = (int)(0.3f * 255.0f + 0.5f);
            int expG = (int)(0.6f * 255.0f + 0.5f);
            int expB = (int)(0.9f * 255.0f + 0.5f);
            int ok = (abs((int)pixel[0] - expR) <= 1 &&
                      abs((int)pixel[1] - expG) <= 1 &&
                      abs((int)pixel[2] - expB) <= 1);

            if (!ok) {
                fprintf(stderr,
                        "FAIL Test 3: expected ~(%d,%d,%d) got (%d,%d,%d)\n",
                        expR, expG, expB, pixel[0], pixel[1], pixel[2]);
                failed++;
            } else {
                printf("PASS Test 3: float texture sampled correctly "
                       "(%d %d %d ≈ %.2f %.2f %.2f)\n",
                       pixel[0], pixel[1], pixel[2],
                       pixel[0]/255.0f, pixel[1]/255.0f, pixel[2]/255.0f);
            }

            glUseProgram(0);
            glDeleteProgram(prog);
            glDeleteTextures(1, &tex);
        }
    }

    /* ---- Test 4: HDR float values (> 1.0) preserved through GLSL ---- */
    /* Create 1x1 RGBA32F texture with R=2.0, G=0.5, B=0.0, A=1.0.
     * Shader multiplies by 0.5: correct result = (1.0, 0.25, 0.0, 0.5).
     * If HDR is wrongly CLAMPED to 1.0 before the shader: result = (0.5, ...).
     * R=255 distinguishes correct path; R=127 indicates clamping bug.         */
    {
        const char *vert =
            "#version 110\n"
            "void main() {\n"
            "    gl_Position = gl_Vertex;\n"
            "    gl_TexCoord[0] = gl_MultiTexCoord0;\n"
            "}\n";
        const char *frag =
            "#version 110\n"
            "uniform sampler2D tex;\n"
            "void main() {\n"
            "    gl_FragColor = texture2D(tex, gl_TexCoord[0].xy) * 0.5;\n"
            "}\n";

        GLuint prog = make_program(vert, frag);
        if (!prog) {
            fprintf(stderr, "FAIL Test 4: shader compilation failed\n");
            failed++;
        } else {
            GLfloat texdata[4] = { 2.0f, 0.5f, 0.0f, 1.0f };
            GLuint tex;
            glGenTextures(1, &tex);
            glBindTexture(GL_TEXTURE_2D, tex);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F_ARB, 1, 1, 0,
                         GL_RGBA, GL_FLOAT, texdata);

            glUseProgram(prog);
            glUniform1i(glGetUniformLocation(prog, "tex"), 0);

            glViewport(0, 0, W, H);
            glClear(GL_COLOR_BUFFER_BIT);
            draw_fullscreen_quad();
            glFinish();

            GLubyte pixel[4] = { 0, 0, 0, 0 };
            glReadPixels(W/2, H/2, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixel);
            check_gl_error("glReadPixels Test 4");

            /* Expected: R=2.0*0.5=1.0 → 255; G=0.5*0.5=0.25 → 64
             * Clamped-wrong: R=1.0*0.5=0.5 → 127                    */
            int ok = (pixel[0] >= 250 &&                /* R=1.0 → 255 */
                      abs((int)pixel[1] - 64) <= 2);    /* G=0.25 → 64 */

            if (!ok) {
                fprintf(stderr,
                        "FAIL Test 4: HDR: expected R≈255, G≈64, got R=%d, G=%d "
                        "(R≈127 means HDR float clamping is still occurring)\n",
                        pixel[0], pixel[1]);
                failed++;
            } else {
                printf("PASS Test 4: HDR float value preserved "
                       "(R=2.0*0.5→%d, G=0.5*0.5→%d)\n",
                       pixel[0], pixel[1]);
            }

            glUseProgram(0);
            glDeleteProgram(prog);
            glDeleteTextures(1, &tex);
        }
    }

    /* ---- Test 5: Render-to-float-texture via FBO ---- */
    /* Check FBOs are supported, attach a RGBA32F texture, render a known
     * HDR color to it via a GLSL shader, then read back and verify the HDR
     * value was stored with full float precision (not clamped to [0,1]).  */
    {
        const char *exts = (const char *)glGetString(GL_EXTENSIONS);
        if (!exts || !strstr(exts, "GL_EXT_framebuffer_object")) {
            printf("SKIP Test 5: GL_EXT_framebuffer_object not available\n");
        } else {
            /* Shader that outputs a fixed HDR color */
            const char *vert5 =
                "#version 110\n"
                "void main() { gl_Position = gl_Vertex; }\n";
            const char *frag5 =
                "#version 110\n"
                "void main() {\n"
                "    gl_FragColor = vec4(1.5, 0.3, 0.7, 1.0);\n"
                "}\n";

            GLuint prog5 = make_program(vert5, frag5);
            if (!prog5) {
                fprintf(stderr, "FAIL Test 5: shader compilation failed\n");
                failed++;
            } else {
                /* Create the float render target texture */
                GLuint fbo_tex;
                glGenTextures(1, &fbo_tex);
                glBindTexture(GL_TEXTURE_2D, fbo_tex);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F_ARB, W, H, 0,
                             GL_RGBA, GL_FLOAT, NULL);
                glBindTexture(GL_TEXTURE_2D, 0);

                /* Create FBO and attach the texture */
                GLuint fbo;
                glGenFramebuffersEXT(1, &fbo);
                glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo);
                glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT,
                                          GL_COLOR_ATTACHMENT0_EXT,
                                          GL_TEXTURE_2D, fbo_tex, 0);

                GLenum status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
                if (status != GL_FRAMEBUFFER_COMPLETE_EXT) {
                    fprintf(stderr, "SKIP Test 5: FBO incomplete (status=0x%x)\n",
                            (unsigned)status);
                    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
                    glDeleteFramebuffersEXT(1, &fbo);
                    glDeleteTextures(1, &fbo_tex);
                    glDeleteProgram(prog5);
                } else {
                    /* Render the HDR color to the float FBO */
                    glUseProgram(prog5);
                    glViewport(0, 0, W, H);
                    glClearColor(0, 0, 0, 0);
                    glClear(GL_COLOR_BUFFER_BIT);
                    glBegin(GL_QUADS);
                    glVertex2f(-1.0f, -1.0f);
                    glVertex2f( 1.0f, -1.0f);
                    glVertex2f( 1.0f,  1.0f);
                    glVertex2f(-1.0f,  1.0f);
                    glEnd();
                    glUseProgram(0);
                    glFinish();

                    /* Read back directly from float FBO */
                    GLfloat pixel[4] = { 0, 0, 0, 0 };
                    glReadPixels(W/2, H/2, 1, 1, GL_RGBA, GL_FLOAT, pixel);
                    check_gl_error("glReadPixels Test 5");

                    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

                    /* Verify HDR R=1.5 is stored (not clamped to 1.0) */
                    const float tol = 0.01f;
                    int ok = (fabsf(pixel[0] - 1.5f) < tol &&
                              fabsf(pixel[1] - 0.3f) < tol &&
                              fabsf(pixel[2] - 0.7f) < tol);

                    if (!ok) {
                        fprintf(stderr,
                                "FAIL Test 5: FBO float: expected (1.5,0.3,0.7) "
                                "got (%.4f,%.4f,%.4f)\n",
                                pixel[0], pixel[1], pixel[2]);
                        failed++;
                    } else {
                        printf("PASS Test 5: Render-to-float-texture HDR (%.4f %.4f %.4f)\n",
                               pixel[0], pixel[1], pixel[2]);
                    }

                    glDeleteFramebuffersEXT(1, &fbo);
                    glDeleteTextures(1, &fbo_tex);
                }
                glDeleteProgram(prog5);
            }
        }
    }

    /* ---- Cleanup ---- */
    free(fb);
    OSMesaDestroyContext(ctx);

    if (failed) {
        printf("\n%d test(s) FAILED\n", failed);
        return 1;
    }
    printf("\nAll tests PASSED\n");
    return 0;
}

/*
 * Local Variables:
 * tab-width: 8
 * mode: C
 * indent-tabs-mode: t
 * c-file-style: "stroustrup"
 * End:
 * ex: shiftwidth=4 tabstop=8 cino=N-s
 */
