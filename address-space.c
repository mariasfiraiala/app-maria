#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <errno.h>

/* useful macro for handling error codes */
#define DIE(assertion, call_description)				\
	do {								\
		if (assertion) {					\
			fprintf(stderr, "(%s, %d): ",			\
					__FILE__, __LINE__);		\
			perror(call_description);			\
			exit(EXIT_FAILURE);				\
		}							\
	} while(0)


#define NUM_THREADS     3

static void msg_and_wait(const char *msg)
{
    char buf[256];

    puts(msg);
    fputs("\tPress ENTER to continue ...", stdout);
    fflush(stdout);

    while (1) {
        fgets(buf, 256, stdin);
        if (buf[strlen(buf) - 1] == '\n')
            break;
    }
}

static void *show(void *arg)
{
    struct timespec ts;

    printf("This is thread %lu\n", pthread_self());

    ts.tv_sec = 2;
    ts.tv_nsec = 0;
    nanosleep(&ts, NULL);

    return NULL;
}

int main(void)
{
    pthread_t ths[NUM_THREADS];
    size_t i;

    msg_and_wait("Program started.");

    for (i = 0; i < NUM_THREADS; ++i) {
        DIE(pthread_create(&ths[i], NULL, &show, NULL) != 0, "pthread_create");

        msg_and_wait("Created new thread");
    }

    for (i = 0; i < NUM_THREADS; ++i)
        DIE(pthread_join(ths[i], NULL), "pthread_join");

    return 0;
}
