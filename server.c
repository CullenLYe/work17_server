#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int server, client;
char clientname[200];
char buffer[200];

char *rot1(char *input) {
  int i;
  for (i=0; i<strlen(input); i++) {
    if ((input[i]>=65&&input[i]<=90)||(input[i]>=97&&input[i]<=122)) {
      if (input[i]=='z') input[i]='a';
      else input[i]=input[i]+1;
    }
  }
  return input;
}

int main() {

	mkfifo("servername", 0644);
	server = open("servername", O_RDONLY);
	read(server, clientname, sizeof(buffer));
	client = open(clientname, O_WRONLY);
	printf("Handshake finished.\n");
	remove("servername");

	while(1) {
		read(server, buffer, sizeof(buffer));
		write(client, rot1(buffer), sizeof(buffer));
	}

  close(client);
	close(server);
	return 0;
}
