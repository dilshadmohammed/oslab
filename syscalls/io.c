#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
	int fd = open("hello.txt",O_RDONLY);
	char buf[1000];
	write(1,buf,read(fd,buf,1000));
	return 0;
}

