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
        printf("String Recieved : ");
        int f1 = open("f1",O_RDONLY);
        struct msg mr[5];
        int ret = read(f1,mr,sizeof(mr));
        struct msg mm;
        for(int j=0;j<5;j++){
            printf("ID: %d- %s\n",mr[j].idx,mr[j].str);
            mm.idx=mr[j].idx;
            strncpy(mm.str,mr[j].str,sizeof(mr[j].str));
        }
        close(f1);
        id = mr[5].idx;
        f1 = open("f1",O_WRONLY);
        int r = write(f1,&mm,sizeof(f1));
        close(f1);
        printf("Highest ID sent by Client\n");
    }
    unlink("f1"); 
}
