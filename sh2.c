#include <stdio.h>  
#include <stdlib.h>
#include <strings.h>  
#include <unistd.h>  
#include <sys/shm.h>  
#include <string.h>  
#include <time.h>
#include <stdbool.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(){    
    int id=shmget((key_t)2345, 1024, 0666|IPC_CREAT);
    char *mem=(char *)shmat(id,NULL,0);
    for(int i=0;i<=49;i+=5){
        sleep(1);
        for(int j=0;j<=4;j++){
            while(*mem==-1)
            printf("String ID: %d\n",i+j);
            printf("String Value: %s\n",mem);
            *mem = -1;
        }
        printf("\n");
    }
    return 0;
}