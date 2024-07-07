#include <stdio.h>
#include <stdlib.h>

int main(){
    int left=0,right=250;
    int n,head_pos;

    printf("Enter the number of tracks: ");
    scanf("%d",&n);

    printf("Enter the initial head position: ");
    scanf("%d",&head_pos);

    int rq[n];

    printf("Enter the request sequence: ");
    for(int i=0;i<n;i++) scanf("%d",&rq[i]);

    for(int i=0;i<n;i++)
        for(int j=i+1;j<n;j++)
            if(rq[i]>rq[j]){
                int temp = rq[i];
                rq[i] = rq[j];
                rq[j] = temp;
            }

    int start = 0;
    for(; start<n;start++)
        if(rq[start]>head_pos)
            break;


    printf("\nSeek sequence: ");
    int seek_count = 0;
    int current_pos;
    for(int i=start;i<n;i++){
        current_pos = rq[i];
        printf(" %3d ->",rq[i]);
        seek_count += abs(current_pos - head_pos);
        head_pos = current_pos;
    }

    if(current_pos!=right){
        printf(" %3d ->",right);
        seek_count += abs(right - head_pos);
        head_pos = right;
    }

    for(int i = start-1;i>=0;i--){
        current_pos = rq[i];
        printf(" %3d ->",rq[i]);
        seek_count += abs(current_pos - head_pos);
        head_pos = current_pos;
    }
    printf("\b\b  \n");
    printf("Total head movement: %d\n",seek_count);


    return 0;
}