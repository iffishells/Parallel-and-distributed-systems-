#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/wait.h>
#include<netdb.h>
#include <arpa/inet.h>

#define MYPORT 53004
#define MAX_DNS_SIZE 1000

int main(int argc, char *argv[]) {
	int sockfd;
	struct sockaddr_in their_addr;
	struct hostent *he;
	int numbytes, i, addr_len;
	char dst[INET_ADDRSTRLEN];
	char IP_addr[500][INET_ADDRSTRLEN];
	char dns[MAX_DNS_SIZE];

	/* client's address information */
	if (argc != 2) {
		fprintf(stderr,"usage: client hostname\n");
		exit(1);
	}

	if ((he=gethostbyname(argv[1])) == NULL) {
		herror("gethostbyname");
		exit(1);
	}

	/* get the host info */
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}

	their_addr.sin_family = AF_INET;
	their_addr.sin_port = htons(MYPORT);
	their_addr.sin_addr = *((struct in_addr *)he->h_addr);
	bzero(&(their_addr.sin_zero), 8);

	printf("Enter the domain name: ");
	scanf("%s", dns);
	if((numbytes=sendto(sockfd, dns, strlen(dns), 0,
	   (struct sockaddr *)&their_addr, sizeof(struct sockaddr))) == -1) {
		perror("sendto");
		exit(1);
	}

	inet_ntop(AF_INET, &(their_addr.sin_addr), dst, INET_ADDRSTRLEN);
	printf("sent %d bytes to %s\n",numbytes,dst);

	addr_len = sizeof(struct sockaddr);
	if((numbytes=recvfrom(sockfd, IP_addr, 500*INET_ADDRSTRLEN, 0,
	   (struct sockaddr *)&their_addr, &addr_len)) == -1) {
		perror("recvfrom");
		exit(1);
	}

	printf("Received back the IP addresses\n");

	i=0;
	while(strcmp(IP_addr[i], "end")) {
		printf("%s\n", IP_addr[i]);
		i++;
	}

	close(sockfd);
	return 0;
}

