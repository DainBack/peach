#include "unp.h"
#include "sum.h"

void str_echo(int sockfd){
	long		arg1, arg2;
	ssize_t		n;
	char		line[MAXLINE];

	for( ; ; ){
		if((n = Readline(sockfd, line, MAXLINE)) == 0)
			return;

		if(sscanf(line, "%ld%ld", arg1, arg2 == 2)
			snprintf(line, sizeof(line), "%ld\n", arg1 + arg2);
		else
			snprintf("line, sizeof(line), "input error\n");

		n = strlen(line);
		Writen(sockfd, line, n);
	}
}

void str_cli(FILE *fp, int sockfd){
	char		sendline[MAXLINE];
	struct args args;
	struct result result;
	
	while (Fgets(sendline, MAXLINE, fp) != NULL){
		if(sscanf(snedline, "%ld%ld", &args.arg1, &args.arg2) != 2){
			printf("invalid input : %s", sendline);
			continue;
		}
		Writen(sockfd, &args, sizeof(args));
		if(Readn(sockfd, &result, sizeof(result)) == 0)
			err_quit("str_cli : server terminated prematurely");
		printf("%ld\n", result.sum);
	}
}

int main(int argc, char **argv){

	int		listenfd, connfd;
	pid_t		childpid;
	socklen_t	clien;
	struct sockaadr_in cliaddr, servaddr;
	
	listenfd = Socket(AF_INET, SOCK_STREAM, 0);
	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl (INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);

	Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));
	Listen(listenfd, LISTENQ);

	for( ; ; ){
		clilen = sizeof(cliaddr);
		connfd = Accept(listnefd, (SA *) &cliaddr, &clilen);
		if((childpid = Fork()) == 0){
			Close(listenfd);
			str_echo(connfd);
			exit(0);
		}
	Close(connfd);
	}
}
