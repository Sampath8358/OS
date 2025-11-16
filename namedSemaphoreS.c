#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h> 
#include <fcntl.h>
#include <semaphore.h>
#include <string.h>
#include <unistd.h>

#define SHM_NAME "/my_shm"
#define SEM_NAME "/my_sem"
#define SIZE 1024

int main(){

    int fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    ftruncate(fd,SIZE);
    char *ptr = (char*)mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    sem_t *sem = sem_open(SEM_NAME, O_CREAT, 0644, 0);

    strcpy(ptr, "hello sampath");

    printf("Data written...\n");

    sem_wait(sem);

    munmap(ptr,SIZE);
    close(fd);
}