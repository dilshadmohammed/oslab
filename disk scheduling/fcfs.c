#include <stdio.h>
#include <stdlib.h>

int main(){
    int n,head_pos;

    printf("Enter the number of tracks: ");
    scanf("%d",&n);

    printf("Enter the initial head position: ");
    scanf("%d",&head_pos);

    int rq[n];

    printf("Enter the request sequence: ");
    for(int i=0;i<n;i++) scanf("%d",&rq[i]);

    int seek_count = 0;
    int current_pos;

    for(int i=0;i<n;i++){
        current_pos = rq[i];
        seek_count += abs(current_pos - head_pos);
        head_pos = current_pos;
    }

    printf("\nSeek sequence: ");
    for(int i=0;i<n;i++){
        printf(" %3d ->",rq[i]);
    }
    printf("\b\b  \n");
    printf("Total head movement: %d\n",seek_count);
    return 0;
}