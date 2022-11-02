#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/mman.h>
#define BUFFERSIZE 5

   int fileDescriptor = shm_open("consumer.c", O_CREAT | O_RDWR, 0666);
    ftruncate(fileDescriptor, 1024);
    struct data *mem = mmap(NULL, 1024, PROT_READ|PROT_WRITE, MAP_SHARED, fileDescriptor, 0);

    mem->table[0] = -1;
    mem->table[1] = -1;

    sem_init(&mem->mutex, 1, 1);

int in=0;
int out=0;
int buffer[BUFFERSIZE];
int item_count = 0;     
int mutex = 1;

void wait(int*);
void signal(int*);
void *producer();
void *consumer();

int main(){
    pthread_t producer_t, consumer_t;
    pthread_create(&producer_t, NULL, producer, NULL);
    pthread_create(&consumer_t, NULL, consumer, NULL);
    pthread_join(producer_t, NULL);
    pthread_join(consumer_t, NULL);
    return 0;
}
void wait(int *semaphore){
        while(*semaphore <= 0);
        *semaphore -= 1;
}
void signal(int *semaphore){
        *semaphore += 1;
}}
void wait(int *semaphore){
        while(*semaphore <= 0);
        *semaphore -= 1;
}
void signal(int *semaphore){
        *semaphore += 1;
}
void *producer(){
    int produced = 0;
    while(1){
        wait(&mutex);
                produced++;
                printf("Job %d started\n", produced);
                buffer[in] = produced;
        in = (in+1)%BUFFERSIZE;
                signal(&item_count);
        signal(&mutex); 
        sleep(1);
    }
}
