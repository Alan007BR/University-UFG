#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ECHOMAX 255     /* maior mensagem suportada */

int main(int argc, char *argv[])
{
    int sock;
    struct sockaddr_in echoServAddr; /* informacoes locais */
    struct sockaddr_in echoClntAddr; /* informacoes remotas (do cliente) */
    unsigned int cliAddrLen = sizeof(echoClntAddr); /* tamanho das informacoes remotas */
    unsigned short echoServPort;     /* porta do servidor */
    char echoBuffer[ECHOMAX];        /* buffer para a mensagem a ser ecoada */
    int recvMsgSize;                 /* tamanho da mensagem recebida */

    if (argc != 2)         /* verificacao do numero de argumentos */
    {
        fprintf(stderr,"Uso:  %s <numero da porta> (se nao for o root, use > 1023)\n", argv[0]);
        exit(1);
    }

    echoServPort = atoi(argv[1]);  /* primeiro arg.:  porta local */

    /* cria um socket UDP para enviar/receber datagramas */
    if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
    {
	    perror("socket()");
	    exit(1);
    }
    /* configura a estrutura de informacoes locais */
    memset(&echoServAddr, 0, sizeof(echoServAddr));   /* zera todos os campos da  estrutura */
    echoServAddr.sin_family = AF_INET;                /* familia de enderecos da Internet */
    echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY); /* qualquer interface de entrada */
    echoServAddr.sin_port = htons(echoServPort);      /* porta local */

    /* "liga" o socket a porta (e endereco) local(is) */
    if (bind(sock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
    {
	    perror("bind()");
	    exit(1);
    }
  
    for (;;) /* laco infinito */
    {
        /* se bloqueia ate receber um datagrama de um cliente */
        if ((recvMsgSize = recvfrom(sock, echoBuffer, ECHOMAX, 0,
            (struct sockaddr *) &echoClntAddr, &cliAddrLen)) < 0)
	    {
		    perror("recvfrom()");
		    exit(1);
	    }

        printf("Datagrama recebido do cliente: %s\n", inet_ntoa(echoClntAddr.sin_addr));

        /* devolve o datagrama de volta ao cliente */
        if (sendto(sock, echoBuffer, recvMsgSize, 0, 
             (struct sockaddr *) &echoClntAddr, sizeof(echoClntAddr)) != recvMsgSize)
	    {
		    perror("sendto()");
		    exit(1);
	    }
    }
}