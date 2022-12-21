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
    char *mem =(char *)shmat(id,NULL,0);
    char randString[50][7];
    for(int i = 0; i<50; i++){
        for(int j=1; j<6; j++){
            randString[i][j] = 'A'+rand()%26;
        }
        randString[i][6] = '\0';
        randString[i][0] = i;
    }
    sleep(1);
    printf("The randomly generated strings are\n");
    for(int i = 0; i<50; i++){
        printf("%d) ",(i+1));
        printf("%s",randString[i]);
        printf("\n");
    }
    for(int i=0;i<=49;i+=5){
        sleep(1);
        for(int j=0;j<5;j++){
            strcpy(mem,randString[i+j]);
            while(*mem!=-1);
        }
        printf("Highest ID recieved: %d\n",(i+5));
    }
    return 0;
}