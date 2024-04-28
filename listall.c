#include <stdio.h> 
#include <dirent.h> 
#include <fcntl.h>
#include <unistd.h>
  
void printFileContents(const char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return;
    }

    char buffer[4096];
    int bytes_read;
    printf("Contents of file: %s\n", filename);
    int fdout = open("myoutput.txt", O_WRONLY | O_CREAT, 0644);
    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
        write(fdout, buffer, bytes_read);
    }

    if (bytes_read == -1) {
        perror("read");
    }

    close(fd);
    printf("\n\n");
}

int main(void) 
{ 
    struct dirent *de;  
    DIR *dr = opendir("."); 
  
    if (dr == NULL) 
    { 
        printf("Could not open current directory" ); 
        return 0; 
    } 

    while ((de = readdir(dr)) != NULL)
    {
        if (de->d_type == DT_REG) {
            printFileContents(de->d_name);
        }
    }
  
    closedir(dr);     
    return 0; 
} 