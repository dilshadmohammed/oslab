#include <stdio.h>
int allocation[10][10],max[10][10],need[10][10],available[10],finish[10],sq[10];
int nr,np;

void readMatrix(int matrix[10][10]){
    for(int i=0;i<np;i++){
        for(int j=0;j<nr;j++){
            scanf("%d",&matrix[i][j]);
        }
    }
}

void printMatrix(int matrix[10][10]){
    for(int i=0;i<np;i++){
        for(int j=0;j<nr;j++){
            printf("%d ",matrix[i][j]);
        }
        printf("\n");
    }
}

void calculate_need(){
    for(int i=0;i<np;i++){
        for(int j=0;j<nr;j++){
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

void bankers(){
    for(int i=0;i<np;i++)
        finish[i]=0;
    int k=0,iterations=0;
    while(k<np && iterations<np){
        iterations++;
    
        for(int i=0;i<np;i++){
            int flag=0;
            if(finish[i]==0){
                for(int j=0;j<nr;j++){
                    if(need[i][j]>available[j]){
                        flag=1;
                        break;
                    }
                }
                if(flag==0){
                    finish[i]=1;
                    sq[k++] = i;
                    
                    for (int x = 0; x < nr; x++)
                        available[x] += allocation[i][x];
                    iterations=0;
                }
            }
        }
    }


    int flag=0;
    for(int i=0;i<np;i++){
        if(finish[i]==0){
            printf("System is unsafe\n");
            flag = 1;
            break;
        }
    }
    if(flag==0){

    printf("Safe sequence: ");
    for(int i=0;i<np;i++){
        printf("P%d -> ",sq[i]+1);
    }
    }

}


int main(){
    printf("Enter the number of resource types: ");
    scanf("%d",&nr);
    printf("Enter the number of processes: ");
    scanf("%d",&np);
    printf("Enter allocation matrix: \n");
    readMatrix(allocation);
    printf("Enter Max matrix: \n");
    readMatrix(max);
    calculate_need();
    printf("Enter available resources: ");
    for(int i=0;i<nr;i++){
        scanf("%d",&available[i]);
    }

    bankers();
}