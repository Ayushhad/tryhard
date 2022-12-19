#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <strings.h>
#include <sys/un.h>
#include <sys/types.h>
#include <fcntl.h>

void genRandomString(char s[][6]){
    for(int i = 0; i<50; i++){
        for(int j=0; j<5; j++){
            s[i][j] = 'A'+rand()%26;
        }
        s[i][5] = '\0';
    }
}


int main(){
    char randString[50][6];
    genRandomString(randString);
    printf("The randomly generated strings are\n");
    for(int i = 0; i<50; i++){
        printf("%d) ",(i+1));
        printf("%s",randString[i]);
        printf("\n");
    }
    mkfifo("f1.txt",0666);
    mkfifo("f2.txt",0666);
    char *str2d = malloc(1e4);
    int r1;
    for(int i=0;i<50;i++){
        printf("client Sending String %d",(i+1));
        for(int j=i;j<i+5;j++){
            int f1 = open("f1.txt",O_WRONLY);
            r1 = write(f1,randString[j],sizeof(randString[j])+1);
            sleep(1);
            close(f1);
        }
        int f2 = open("f2.txt",O_RDONLY);
        r1 = read(f2,str2d,sizeof(str2d));
        close(f2);
        i = atoi(str2d)+1;
        printf("Max ID recieved from Server : %s\n",str2d);
    }
}