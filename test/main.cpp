#include <fcntl.h>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(){
    int pos = 0;
    int buffsize = 256;
    bool cont = true;

    int fd = open("../include/config.hpp", O_RDONLY, S_IRWXU);
    int fd_1 = open("copy.py", O_CREAT | O_RDWR, 0666);

    if(fd>0){ 
        unsigned char* buffer = (unsigned char*) malloc(buffsize);

        while(cont){ //if(cont){
            memset(buffer, 0, buffsize);
            int pos3 = (int) read(fd, buffer, buffsize);
            if(pos3>0){
                write(fd_1,buffer,pos3);
            }
            else cont = false;
        }

        close(fd);
        close(fd_1);

        free(buffer);
    }

    int N=5;
    void *ptr = mmap ( NULL, N*sizeof(int),PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
    if(ptr == MAP_FAILED){ 
        printf("Mapping Failed\n");
        return 1;
    }

    int err = munmap(ptr, 10*sizeof(int));
    if(err != 0){
        printf("UnMapping Failed\n");
        return 1;
    }
    
    return 0;
}