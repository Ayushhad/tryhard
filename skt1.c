#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<unistd.h>
#include<time.h>

int main(int argc, char* argv[]) {
	struct sockaddr_un addr;
	char s[10];
  int r,sock;
	sock = socket(AF_UNIX, SOCK_SEQPACKET, 0);
	if((sock <0)) {
		printf("Socket\n");
		exit(EXIT_FAILURE);
	}	

	memset(&addr, 0, sizeof(addr));
  int i = 1;
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, "socketfile.socket", sizeof(addr.sun_path) - 1);
	r = connect(sock, (const struct sockaddr *) &addr, sizeof(addr));

	if((r <0)) {
		printf("Server is down\n");
		exit(EXIT_FAILURE);
	}	
	char randString[50][6];
    for(int i = 0; i<50; i++){
        for(int j=0; j<5; j++){
            randString[i][j] = 'A'+rand()%26;
        }
        randString[i][6] = '\0';
    }
    printf("The randomly generated strings are\n");
    for(int i = 0; i<50; i++){
        printf("%d) ",(i+1));
        printf("%s",randString[i]);
        printf("\n");
    }
	if(argc > 1) {
		strncpy(s, "DOWN", sizeof("DOWN"));
		write(sock, s, sizeof(s));
		close(sock);
		exit(EXIT_SUCCESS);
	}
	else {
		int ID = 1;
		while(1) {
      int i = ID;
			for(int i=0;i<ID+5;i++) {
				r = write(sock, randString[i], strlen(randString[i]) + 1);
			}
			r = read(sock, s, sizeof(s));
			if((r <0)) {
				printf("read");
				exit(EXIT_FAILURE);
			}
			s[sizeof(s) - 1] = 0;
			int index = atoi(s);
			printf("Highest Id recieved : %s\n\n", s);
			if(index == 50) {
				printf("All strings passed\n");
				strncpy(s, "DOWN", sizeof("DOWN"));
				write(sock, s, sizeof(s));
				close(sock);
				exit(EXIT_SUCCESS);
				break;
			}
			else {
				ID = index +1;
			}
		}
	}
}
