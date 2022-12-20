#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <strings.h>
#include <sys/un.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
struct msg{
    char str[6];
    int idx;
};

int main(){
    char randString[50][6];
    for(int i = 0; i<50; i++){
        for(int j=0; j<5; j++){
            randString[i][j] = 'A'+rand()%26;
        }
        randString[i][5] = '\0';
    }
    printf("The randomly generated strings are\n");
    for(int i = 0; i<50; i++){
        printf("%d) ",(i+1));
        printf("%s",randString[i]);
        printf("\n");
    }
    mkfifo("f1",0666);
    mkfifo("f2",0666);
    char *str2d = malloc(1e4);
    int r1;
    char *fil1 = "f1";
    char *fil2 = "f2";
    for(int i=0;i<50;i++){
        printf("Sending set of 5 Strings from P1\n");
        struct msg m[5];
        struct msg m2;
        for(int j=0;j<5;j++){
            m[j].idx=i+j;
            char *pasStr=randString[m[j].idx];
            strncpy(m[j].str,pasStr,sizeof(pasStr));
        }
        int f1 = open(fil1,O_WRONLY);
        int wt= write(f1,&m,sizeof(m));
        close(f1);
        f1 = open(fil1,O_RDONLY);
        int rt = read(f1,&m2,sizeof(m2));
        i=m2.idx+1;
        printf("%s String recived from client",m2.str);
        close(f1);
    }
    unlink(fil1);
}
