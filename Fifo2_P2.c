#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <strings.h>
#include <sys/un.h>
#include <sys/types.h>
#include <fcntl.h>
struct msg{
    char str[5];
    int idx;
};
int main(){
    int id = -1e6;
    mkfifo("f1",0666);
    mkfifo("f2",0666);
    for(int i=0; i<10 ; i++){
        int f1 = open("f1",O_RDONLY);
        struct msg mr[5];
        int ret = read(f1,mr,sizeof(mr));
        close(f1);
        printf("String Recieved : ");
        for(int j=0;j<5;j++){
            printf("%s",mr[j].str);
        }
        printf("\n");
        id = mr[5].idx;
        f1 = open("f1",O_WRONLY);
        int r = write(f1,&id,sizeof(str2d));
        close(f1);
        printf("Highest ID sent by Client\n");
    }
    unlink(f1);
}
