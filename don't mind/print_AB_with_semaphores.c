#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>

sem_t *sem_A,*sem_B;

int main(){

    sem_A = sem_open("/sem_A", O_CREAT, 0644, 1); 
    sem_B = sem_open("/sem_B", O_CREAT, 0644, 0); 

    int pid = fork();

    for(int i=0;i<10;i++){
        if(pid==0){
            sem_wait(sem_A);
            printf("A");
            fflush(stdout);
            sem_post(sem_B);
        }
        else{
            sem_wait(sem_B);
            printf("B");
            fflush(stdout);
            sem_post(sem_A);
        }
    }

    if(pid!=0){
    wait(NULL);
    sem_close(sem_A);
    sem_close(sem_B);
    sem_unlink("/sem_A");
    sem_unlink("/sem_B");
    }
}
