#include <stdio.h>

void firstfit(int blocksize[],int processes[],int nb,int np){
    int allocated[np];
    for(int i=0;i<np;i++)
        allocated[i]=-1;
    for(int i=0;i<np;i++){
        for(int j=0;j<nb;j++){
            if(processes[i]<=blocksize[j]){
                allocated[i] = j;
                blocksize[j] -= processes[i];
                break;
            }
        }
    }

    printf("\nProcess No.\tProcess Size\tBlock no.\n"); 
    for (int i = 0; i < np; i++) 
    { 
        printf(" %i\t\t\t", i+1); 
        printf("%i\t\t\t\t", processes[i]); 
        if (allocated[i] != -1) 
            printf("%i", allocated[i] + 1); 
        else
            printf("Not Allocated"); 
        printf("\n"); 
    } 
}

void bestfit(int blocksize[],int processes[],int nb,int np){
    int allocated[np];
    for(int i=0;i<np;i++)
        allocated[i]=-1;
    for(int i=0;i<np;i++){
        int best = -1,best_size=999;
        for(int j=0;j<nb;j++){
           if(best_size>blocksize[j] && processes[i]<=blocksize[j])
           {
            best_size = blocksize[j];
            best = j;
           }
        }
        if(best!=-1 && processes[i]<=blocksize[best]){

            allocated[i] = best;
            blocksize[best] -= processes[i];
            
        }
    }

    printf("\nProcess No.\tProcess Size\tBlock no.\n"); 
    for (int i = 0; i < np; i++) 
    { 
        printf(" %i\t\t\t", i+1); 
        printf("%i\t\t\t\t", processes[i]); 
        if (allocated[i] != -1) 
            printf("%i", allocated[i] + 1); 
        else
            printf("Not Allocated"); 
        printf("\n"); 
    } 
}

void worstfit(int blocksize[],int processes[],int nb,int np){
    int allocated[np];
    for(int i=0;i<np;i++)
        allocated[i]=-1;
    for(int i=0;i<np;i++){
        int worst = -1,max_size=-999;
        for(int j=0;j<nb;j++){
           if(max_size<blocksize[j] && processes[i]<=blocksize[j])
           {
            max_size = blocksize[j];
            worst = j;
           }
        }
        if(worst!=-1 && processes[i]<=blocksize[worst]){

            allocated[i] = worst;
            blocksize[worst] -= processes[i];
            
        }
    }

    printf("\nProcess No.\tProcess Size\tBlock no.\n"); 
    for (int i = 0; i < np; i++) 
    { 
        printf(" %i\t\t\t", i+1); 
        printf("%i\t\t\t\t", processes[i]); 
        if (allocated[i] != -1) 
            printf("%i", allocated[i] + 1); 
        else
            printf("Not Allocated"); 
        printf("\n"); 
    } 
}

int main(){
    int nb,np;
    int blocksize[100],processes[100];
    int blocksize_copy[100],processes_copy[100];

    printf("Enter number of blocks: ");
    scanf("%d",&nb);
    printf("Enter size of each block (seperated by space): ");
    for(int i=0;i<nb;i++){
        scanf("%d",&blocksize[i]);
    }

    printf("Enter number of processes: ");
    scanf("%d",&np);
    printf("Enter size of each process (seperated by space): ");
    for(int i=0;i<np;i++){
        scanf("%d",&processes[i]);
    }

    
    while (1)
    {   
        
        int choice;
        printf("\nchoose an option\n\t1.Bestfit\n\t2.FirstFit\n\t3.WorstFit\n\t4.Exit\n\n\tEnter a choice: ");
        scanf("%d",&choice);

        for (int i = 0; i < nb; i++) {
            blocksize_copy[i] = blocksize[i];
        }
        for (int i = 0; i < np; i++) {
            processes_copy[i] = processes[i];
        }
        switch (choice)
        {
        case 1:bestfit(blocksize_copy,processes_copy,nb,np);
            break;    
        case 2:firstfit(blocksize_copy,processes_copy,nb,np);
            break;
        case 3: worstfit(blocksize_copy,processes_copy,nb,np);
            break;
        case 4: return 0;
        
        default:
            printf("\tInvalid choice\n");
        }
    }

}