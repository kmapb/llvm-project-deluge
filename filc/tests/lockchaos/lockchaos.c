#include <pthread.h>
#include <stdio.h>
#include <stdfil.h>
#include <string.h>

#define NTHREADS 10
#define REPEAT 10000

typedef struct {
    const char* str;
} stuff;

static pthread_mutex_t lock;
static unsigned count;

static void* thread_main(void* arg)
{
    unsigned i;
    for (i = REPEAT; i--;) {
        pthread_mutex_lock(&lock);
        count++;
        pthread_mutex_unlock(&lock);
    }
    stuff* s = (stuff*)arg;
    return (void*)s->str;
}

int main()
{
    pthread_t threads[NTHREADS];
    unsigned i;

    printf("lock is at %p\n", &lock);
    
    pthread_mutex_init(&lock, NULL);

    for (i = NTHREADS; i--;) {
        stuff* s = zalloc(stuff, 1);
        s->str = zasprintf("thread = %u", i);
        ZASSERT(!pthread_create(threads + i, NULL, thread_main, s));
    }

    for (i = NTHREADS; i--;) {
        const char* str;
        ZASSERT(!pthread_join(threads[i], (void**)&str));
        ZASSERT(!strcmp(str, zasprintf("thread = %u", i)));
    }
    
    printf("count = %u\n", count);
    return 0;
}

