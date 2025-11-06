#include <stdio.h>
#include <pthread.h>
#include <sched.h>
#include <unistd.h>

void* threadFunc(void* arg) {
    int id = *(int*)arg;
    for (int i = 0; i < 5; i++) {
        printf("Thread %d is running\n", id);
        //usleep(500000); // 0.5 second
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;
    pthread_attr_t attr1, attr2;
    struct sched_param param1, param2;
    int id1 = 1, id2 = 2;

    // Initialize attributes
    pthread_attr_init(&attr1);

    pthread_attr_init(&attr2);

    // Set scheduling policy
    pthread_attr_setschedpolicy(&attr1, SCHED_RR);
    pthread_attr_setschedpolicy(&attr2, SCHED_RR);

    // Set thread priorities (higher number = higher priority)
   // param1.sched_priority = 20;
    param2.sched_priority = 10;
    printf("Enter the priority: ");
    scanf("%d",&param1.sched_priority);
    pthread_attr_setschedparam(&attr1, &param1);
    pthread_attr_setschedparam(&attr2, &param2);

    // // Use explicit scheduling
    // pthread_attr_setinheritsched(&attr1, PTHREAD_EXPLICIT_SCHED);
    // pthread_attr_setinheritsched(&attr2, PTHREAD_EXPLICIT_SCHED);

    // Create threads
    pthread_create(&t1, &attr1, threadFunc, &id1);
    pthread_create(&t2, &attr2, threadFunc, &id2);

    // Join threads
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // Destroy attributes
    pthread_attr_destroy(&attr1);
    pthread_attr_destroy(&attr2);

    return 0;
}
