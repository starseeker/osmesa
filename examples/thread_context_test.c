#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <pthread.h>
#endif

#include <OSMesa/gl.h>
#include <OSMesa/osmesa.h>

struct thread_binding {
    OSMesaContext context;
    unsigned char *buffer;
    int width;
    int height;
    int failed;
};

static int
exercise_display_lists(void)
{
    GLuint list = glGenLists(1);

    if (list == 0)
	return 1;
    glNewList(list, GL_COMPILE);
    glEndList();
    glDeleteLists(list, 1);
    return glGetError() != GL_NO_ERROR;
}

#ifdef _WIN32
static DWORD WINAPI
#else
static void *
#endif
worker_main(void *arg)
{
    struct thread_binding *binding = (struct thread_binding *)arg;

    if (!OSMesaMakeCurrent(binding->context, binding->buffer,
		GL_UNSIGNED_BYTE, binding->width, binding->height) ||
	OSMesaGetCurrentContext() != binding->context ||
	exercise_display_lists())
	binding->failed = 1;
    if (!OSMesaMakeCurrent(NULL, NULL, 0, 0, 0))
	binding->failed = 1;
#ifdef _WIN32
	return 0;
#else
    return NULL;
#endif
}

int
main(void)
{
    enum { WIDTH = 16, HEIGHT = 16 };
    struct thread_binding worker = {NULL, NULL, WIDTH, HEIGHT, 0};
    OSMesaContext main_context = NULL;
    unsigned char *main_buffer = NULL;
#ifdef _WIN32
    HANDLE thread = NULL;
#else
    pthread_t thread;
#endif
    int failed = 0;

    main_context = OSMesaCreateContextExt(OSMESA_RGBA, 24, 0, 0, NULL);
    worker.context = OSMesaCreateContextExt(OSMESA_RGBA, 24, 0, 0, NULL);
    main_buffer = (unsigned char *)calloc(WIDTH * HEIGHT, 4);
    worker.buffer = (unsigned char *)calloc(WIDTH * HEIGHT, 4);
    if (!main_context || !worker.context || !main_buffer || !worker.buffer) {
	fprintf(stderr, "failed to allocate OSMesa test contexts\n");
	failed = 1;
	goto cleanup;
    }

    if (!OSMesaMakeCurrent(main_context, main_buffer, GL_UNSIGNED_BYTE,
		WIDTH, HEIGHT) || exercise_display_lists()) {
	fprintf(stderr, "initial main-thread context exercise failed\n");
	failed = 1;
	goto cleanup;
    }

#ifdef _WIN32
    thread = CreateThread(NULL, 0, worker_main, &worker, 0, NULL);
    if (!thread) {
	fprintf(stderr, "failed to start OSMesa worker thread\n");
	failed = 1;
	goto cleanup;
    }
    if (WaitForSingleObject(thread, INFINITE) != WAIT_OBJECT_0 ||
	worker.failed) {
	fprintf(stderr, "worker-thread context exercise failed\n");
	failed = 1;
    }
    CloseHandle(thread);
#else
    if (pthread_create(&thread, NULL, worker_main, &worker) != 0) {
	fprintf(stderr, "failed to start OSMesa worker thread\n");
	failed = 1;
	goto cleanup;
    }
    if (pthread_join(thread, NULL) != 0 || worker.failed) {
	fprintf(stderr, "worker-thread context exercise failed\n");
	failed = 1;
	goto cleanup;
    }
#endif

    /* The second thread makes glapi switch to TSD.  Core entry points on the
     * original thread must consult that TSD rather than the cleared global. */
    if (!OSMesaMakeCurrent(main_context, main_buffer, GL_UNSIGNED_BYTE,
		WIDTH, HEIGHT) ||
	OSMesaGetCurrentContext() != main_context || exercise_display_lists()) {
	fprintf(stderr, "post-promotion main-thread context exercise failed\n");
	failed = 1;
    }

cleanup:
    OSMesaMakeCurrent(NULL, NULL, 0, 0, 0);
    if (worker.context)
	OSMesaDestroyContext(worker.context);
    if (main_context)
	OSMesaDestroyContext(main_context);
    free(worker.buffer);
    free(main_buffer);
    return failed ? EXIT_FAILURE : EXIT_SUCCESS;
}
