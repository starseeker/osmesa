/*
 * Verify that a small glDrawArrays range at a high offset in a large VBO is
 * mapped and rebased correctly by software TNL.
 *
 * This program is in the public domain.
 */

#define GL_GLEXT_PROTOTYPES
#include <stdio.h>
#include <stdlib.h>

#include "OSMesa/gl.h"
#include "OSMesa/glext.h"
#include "OSMesa/osmesa.h"

#define WIDTH 32
#define HEIGHT 32
#define VERTEX_COUNT 4521162
#define FIRST_VERTEX 1496982

int
main(void)
{
    OSMesaContext context = NULL;
    GLubyte framebuffer[WIDTH * HEIGHT * 4] = {0};
    GLfloat *vertices = NULL;
    GLuint buffer = 0;
    GLint buffer_size = 0;
    GLenum error;
    size_t bytes = (size_t)VERTEX_COUNT * 3 * sizeof(GLfloat);
    int result = 1;

    vertices = (GLfloat *)calloc((size_t)VERTEX_COUNT * 3, sizeof(GLfloat));
    if (!vertices) {
	fprintf(stderr, "vertex allocation failed\n");
	return 1;
    }
    vertices[(size_t)FIRST_VERTEX * 3 + 0] = -0.75f;
    vertices[(size_t)FIRST_VERTEX * 3 + 1] = 0.0f;
    vertices[((size_t)FIRST_VERTEX + 1) * 3 + 0] = 0.75f;
    vertices[((size_t)FIRST_VERTEX + 1) * 3 + 1] = 0.0f;

    context = OSMesaCreateContextExt(OSMESA_RGBA, 0, 0, 0, NULL);
    if (!context ||
	!OSMesaMakeCurrent(context, framebuffer, GL_UNSIGNED_BYTE,
		WIDTH, HEIGHT)) {
	fprintf(stderr, "OSMesa context creation failed\n");
	goto cleanup;
    }

    glViewport(0, 0, WIDTH, HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);

    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)bytes, vertices, GL_STATIC_DRAW);
    glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &buffer_size);
    error = glGetError();
    if (error != GL_NO_ERROR || buffer_size != (GLint)bytes) {
	fprintf(stderr, "VBO upload failed: error=0x%x size=%d expected=%lu\n",
		(unsigned int)error, buffer_size, (unsigned long)bytes);
	goto cleanup;
    }

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, (const GLvoid *)0);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);
    glDrawArrays(GL_LINES, FIRST_VERTEX, 2);
    glFinish();
    error = glGetError();
    if (error != GL_NO_ERROR) {
	fprintf(stderr, "high-offset draw failed: error=0x%x\n",
		(unsigned int)error);
	goto cleanup;
    }

    printf("PASS: %lu-byte VBO range [%d, %d)\n",
	   (unsigned long)bytes, FIRST_VERTEX, FIRST_VERTEX + 2);
    result = 0;

cleanup:
    if (context) {
	glDisableClientState(GL_VERTEX_ARRAY);
	if (buffer)
	    glDeleteBuffers(1, &buffer);
	OSMesaDestroyContext(context);
    }
    free(vertices);
    return result;
}
