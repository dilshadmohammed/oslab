#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>  //Header file for sleep(). man 3 sleep for details. 
#include <pthread.h> 
int mutex = 1;
void *printOdd(void *vargp) 
{   
    while (mutex<=0);
    mutex--;
    int n = *((int *)vargp);
     n++;
    for(int i = n; i < n+10; i += 2){
        printf("%d ", i);
    }
    mutex++;
    return NULL; 
} 

void *printEven(void *vargp) 
{ 
    while (mutex<=0);
    mutex--;

    int n = *((int *)vargp);
     
    for(int i = n; i < n+10; i += 2){
        printf("%d ", i);
    }
    mutex++;
    return NULL; 
} 

int main() 
{ 
    pthread_t thread_odd, thread_even;
    
    for (int i = 0; i < 100; i+=10) {
        int n = i;
        pthread_create(&thread_odd, NULL, printOdd, (void *)&n);
        pthread_create(&thread_even, NULL, printEven, (void *)&n); 
        pthread_join(thread_odd, NULL); 
        pthread_join(thread_even, NULL);
    }
    exit(0); 
}
