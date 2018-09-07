#include	"unp.h"
#include	<time.h>

int
main(int argc, char **argv)
{
	int				len, listenfd, connfd;
	struct sockaddr_in	servaddr;
	struct sockaddr_in	cliaddr;
	char				buff[MAXLINE];
	time_t				ticks;

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(atoi(argv[argc-1]));	/* daytime server */

	Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

	Listen(listenfd, LISTENQ);
	len = sizeof(cliaddr);
	for ( ; ; ) {
		connfd = Accept(listenfd, (SA *) &cliaddr, &len);

	printf("Connection form : %s, port %d\n", Inet_ntop(AF_INET, &cliaddr.sin_addr, buff, sizeof(buff)), ntohs(cliaddr.sin_port));

        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        Write(connfd, buff, strlen(buff));
	
		Close(connfd);
	}
}
