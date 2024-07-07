#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
	
	int n;
	int fd[2];
	if(pipe(fd) == -1){
		perror("pipe");
	}
	
	printf("Enter the array size: ");
	scanf("%d",&n);
	printf("Enter numbers: ");
	int arr[n];
	for(int i=0;i<n;i++)
		scanf("%d",&arr[i]);
		
	int id = fork();
	int s,e;
	if(id==0){
		s=0;
		e=n/2;
	}
	else{
		s=n/2;
		e=n;
	}
	
	int sum=0;
	for(int i=s;i<e;i++)
		sum+=arr[i];
	
	printf("Sum = %d from process %d\n",sum,getpid());
	
	if(id==0){
		close(fd[0]);
		write(fd[1],&sum,sizeof(int));
		close(fd[1]);
	}
	else{
		int sumFromChild;
		close(fd[1]);
		read(fd[0],&sumFromChild,sizeof(int));
		close(fd[0]);
		printf("Total sum = %d",sum+sumFromChild);
		wait(NULL);
	}
	
	
	return 0;
}
