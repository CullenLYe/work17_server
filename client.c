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

int main() {
  
	sprintf(clientname, "%d", getpid());
	mkfifo(clientname, 0644);
	server = open("servername", O_WRONLY);
	write(server, clientname, sizeof(buffer));
	client = open(clientname, O_RDONLY);
	remove(clientname);
	printf("Rot1 Program:\n\n");

	while(1) {
    printf("Input some text: ");
    fgets(buffer, sizeof(buffer), stdin);
    size_t len = strlen(buffer)-1;
    if(buffer[len]=='\n') buffer[len] = '\0';

    write(server, buffer, sizeof(buffer));
    read(client, buffer, sizeof(buffer));
    printf("Rot1: %s\n\n", buffer);
	}

	return 0;
}
