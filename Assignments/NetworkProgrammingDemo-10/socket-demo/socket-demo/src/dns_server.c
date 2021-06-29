-#include<stdio.h>
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
#define MAXBUFLEN 1000
#define MAX_IP_ADDR 500

main() {
	int sockfd;
	struct sockaddr_in my_addr;
	struct sockaddr_in their_addr;
	int addr_len, numbytes, i;
	char buf[MAXBUFLEN];
	char dst[INET_ADDRSTRLEN];
	struct hostent *he;
	char IP_addr[MAX_IP_ADDR][INET_ADDRSTRLEN];

	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}

	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(MYPORT);
	my_addr.sin_addr.s_addr = INADDR_ANY;
	bzero(&(my_addr.sin_zero), 8);

	if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1) {
		perror("bind");
		exit(1);
	}

	while(1) {
		addr_len = sizeof(struct sockaddr);
		if ((numbytes=recvfrom(sockfd, buf, MAXBUFLEN, 0, (struct sockaddr *)&their_addr, &addr_len)) == -1) {
			perror("recvfrom");
			exit(1);
		}

		inet_ntop(AF_INET, &(their_addr.sin_addr), dst, INET_ADDRSTRLEN);
		printf("got packet from %s\n",dst);
		buf[numbytes] = '\0';
		printf("packet contains \"%s\"\n\n",buf);

		he = gethostbyname(buf);

		i=0;
		while(he->h_addr_list[i] != NULL) {
			inet_ntop(AF_INET, (struct in_addr *)he->h_addr_list[i], dst, INET_ADDRSTRLEN);
			strcpy(IP_addr[i], dst);
			i++;
		}
		strcpy(IP_addr[i], "end");

		if(sendto(sockfd, IP_addr, MAX_IP_ADDR*INET_ADDRSTRLEN, 0, (struct sockaddr *)&their_addr, addr_len) == -1) {
			perror("sendto");
			exit(1);
		}
	}
	close(sockfd);
}

