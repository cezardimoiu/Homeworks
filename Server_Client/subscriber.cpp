/* 
/	Dimoiu Cezar-Gabriel 
/  	322CB
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <bits/stdc++.h>
#include "helpers.h"

#define PORT atoi(argv[3])
#define UNSUBSCRIBE -1

using namespace std;

void usage(char *file)
{
	fprintf(stderr, "Usage: %s server_address server_port\n", file);
	exit(0);
}

int main(int argc, char *argv[])
{
	int tcp_socket, n, ret;
	struct sockaddr_in serv_addr;
	char buffer[BUFLEN];

	fd_set read_fds;	// multimea de citire folosita in select()
	fd_set tmp_fds;		// multime folosita temporar
	int fdmax;			// valoare maxima fd din multimea read_fds

	if (argc < 4) {
		usage(argv[0]); //verificare numar de argumente
	}
	FD_ZERO(&read_fds);
	FD_ZERO(&tmp_fds);

	/* Deschid socket */
	tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
	DIE(tcp_socket < 0, "socket");
	/* Il bag in multime  */
	FD_SET(tcp_socket, &read_fds);
	FD_SET(STDIN_FILENO, &read_fds);
	fdmax = tcp_socket;

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	ret = inet_aton(argv[2], &serv_addr.sin_addr);
	DIE(ret == 0, "inet_aton");

	ret = connect(tcp_socket, (struct sockaddr*) &serv_addr, sizeof(serv_addr));
	DIE(ret < 0, "connect");

	/* Cat timp am conexiunea deschisa */
	while (1) {
		tmp_fds = read_fds; 
		
		ret = select(fdmax + 1, &tmp_fds, NULL, NULL, NULL);
		DIE(ret < 0, "select");

		user_t user;
		strcpy(user.id_user, argv[1]);
		if (FD_ISSET(STDIN_FILENO, &tmp_fds)) { //daca e stdin
			// se citeste de la tastatura
			memset(buffer, 0, BUFLEN);
start:
			scanf("%s", buffer);
			if (strncmp(buffer, "exit", 4) == 0) {
				break;
			} else if (strcmp(buffer, "subscribe") == 0) { // citesc subscribe si SF
				scanf("%s", user.topic);
				scanf("%d", &user.SF);
				if (user.SF != 0 && user.SF != 1) // daca comanda e invalida
					goto start;
			} else if (strcmp(buffer, "unsubscribe") == 0) { // citesc unsubscribe
				scanf("%s", user.topic);
				user.SF = UNSUBSCRIBE;
			} else {
				goto start; // daca comanda e invalida citesc din nou pana comanda e valida
			}
			// se trimite mesaj la server
			sprintf(buffer, "%s %d", user.topic, user.SF);
			n = send(tcp_socket, buffer, strlen(buffer), 0);
			DIE(n < 0, "send");
			// afisare mesaj corespunzator in fuctie de comanda
			if (user.SF == UNSUBSCRIBE) 
				printf("unsubscribed %s\n", user.topic);
			else printf("subscribed %s\n", user.topic);
		}

		if (FD_ISSET(tcp_socket, &tmp_fds)) { //daca e pe socket
			memset(buffer, 0, BUFLEN);
			// primesc mesaj
			n = recv(tcp_socket, buffer, sizeof(buffer), 0);
			DIE(n < 0, "recv");
			// structura ca sa afisez corespunzator campurile
			mesaj_t *mesaj = (mesaj_t*)buffer;
			if (mesaj->data_type != 0 && mesaj->data_type != 1 && 
				mesaj->data_type != 2 && mesaj->data_type != 3) {
				printf("WRONG DATA TYPE\n");
			} else if (n > 0) {
				// afisare IP:PORT topic data_type message
				// aici ar trebui sa trimit portul prin buffer
				printf("%s:%d - %s - ", mesaj->ip, mesaj->port, mesaj->topic); 
				// Mesaj->ip si mesaj->port o sa fie NULL respectiv 0, deoarece nu trimit
				// bine din server
				if (mesaj->data_type == 0) printf("INT");
				else if (mesaj->data_type == 1) printf("SHORT_REAL");
				else if (mesaj->data_type == 2) printf("FLOAT");
				else if (mesaj->data_type == 3) printf("STRING");
				printf(" - %s\n", mesaj->message);
			}
		}
	}

	// inchidere socket
	close(tcp_socket);

	return 0;
}
