#include <stdio.h>

int incomingStream[100];
int n;
int frames = 3;


void printFrame(int queue[],int pagno,int occupied,int miss,int pageReplaced){
    
    printf("\nReference to page no: %d\n",pagno);
    if(miss){
        printf("Page fault\n");
        if(pageReplaced!=-1){
            printf("Page %d is replaced\n",pageReplaced);
        }
    }
    else{
        printf("Hit\n");
    }
    printf("page frame contents after loading the page %d: ",pagno);
    for(int i=0;i<occupied;i++){
        printf("[%d]",queue[i]);
    }
    printf("\n=========================================");
}

int checkHit(int incomingPage,int queue[],int occupied){
        for(int i = 0; i < occupied; i++){
        if(incomingPage == queue[i])
            return 1;
    }
    
    return 0;
}

void lru(){
    int pageFault = 0;
    int hit = 0;
    int queue[frames];
    int distance;
    int occupied = 0;

    for(int i=0;i<n;i++){
        if(checkHit(incomingStream[i],queue,occupied))
         {
            hit++;
           printFrame(queue,incomingStream[i],occupied,0,-1);
         }
        else if(occupied<frames){
            queue[occupied++] = incomingStream[i];
            pageFault++;
            printFrame(queue,incomingStream[i],occupied,1,-1);
        }
        else{
            int max = -9999;
            int index;

            for(int j=0;j<frames;j++){
                distance=0;
                for(int k=i-1;k>=0;k--){
                    ++distance;
                    if(queue[j]==incomingStream[k])
                        break;
                }

                if(distance>max){
                    max = distance;
                    index = j;
                }
            }
            int replaced = queue[index];
            queue[index] = incomingStream[i];
            pageFault++;
            printFrame(queue,incomingStream[i],occupied,1,replaced);
            
        }
        printf("\n");
    }
    printf("\n Page Fault: %d\nHit: %d\n",pageFault,hit);
}

void fifo()
{
    int pageFault = 0;
    int hit = 0;
    int queue[frames];
    int distance;
    int occupied = 0;

    for(int i =0;i<n;i++){

        if(checkHit(incomingStream[i],queue,occupied))
         {
            hit++;
           printFrame(queue,incomingStream[i],occupied,0,-1);
         }
         else if(occupied<frames){
            queue[occupied++] = incomingStream[i];
            pageFault++;
            printFrame(queue,incomingStream[i],occupied,1,-1);
        }
        else{
            int replaced = queue[0],j;
            for(j=1;j<frames;j++){
                queue[j-1] = queue[j];
            }
            queue[j-1] = incomingStream[i];
            pageFault++;
            printFrame(queue,incomingStream[i],occupied,1,replaced);
        }
            printf("\n");
    }
    printf("\n Page Fault: %d\nHit: %d\n",pageFault,hit);


}

void lfu(){
    int pageFault = 0;
    int hit = 0;
    int queue[frames];
    int frequency;
    int occupied = 0;

    for(int i=0;i<n;i++){
        if(checkHit(incomingStream[i],queue,occupied))
         {
            hit++;
           printFrame(queue,incomingStream[i],occupied,0,-1);
         }
        else if(occupied<frames){
            queue[occupied++] = incomingStream[i];
            pageFault++;
            printFrame(queue,incomingStream[i],occupied,1,-1);
        }
        else{
            int min = 9999;
            int index;

            for(int j=0;j<frames;j++){
                frequency=0;
                for(int k=i+1;k<n;k++){
                    if(queue[j]==incomingStream[k])
                        frequency++;
                }

                if(frequency<min){
                    min = frequency;
                    index = j;
                }
            }
            int replaced = queue[index];
            int j;
            for(j=index+1;j<frames;j++){
                queue[j-1] = queue[j];
            }
            queue[j-1] = incomingStream[i];
            //queue[index] = incomingStream[i];
            pageFault++;
            printFrame(queue,incomingStream[i],occupied,1,replaced);
            
        }
        printf("\n");
    }
    printf("\n Page Fault: %d\nHit: %d\n",pageFault,hit);
}



int main(){
    printf("Enter number of incoming stream: ");
    scanf("%d",&n);

    for(int i=0;i<n;i++){
        scanf("%d",&incomingStream[i]);
    }

    while (1)
    {   int choice;
        printf("\n\t1.FIFO\n\t2.LRU\n\t3.LFU\n\t4.Exit\n\tEnter a choice: ");
        scanf("%d",&choice);

        switch (choice)
        {
        case 1:
            fifo();
            break;
        case 2:
            lru();
            break;
        case 3:
            lfu();
            break;
        case 4:
            return 0;
            break;
        default:
            printf("Invalid choice\n");
        }
    }
    

    
}
