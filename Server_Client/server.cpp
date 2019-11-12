/* 
/	Dimoiu Cezar-Gabriel 
/  	322CB
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <bits/stdc++.h>
#include "helpers.h"

using namespace std;

#define PORT atoi(argv[1])
#define MAX_CLIENTS 100

void usage(char *file)
{
	fprintf(stderr, "Usage: %s server_port\n", file);
	exit(0);
}

int max(int a, int b) {
	if (a > b) return a;
	else return b;
}

int main(int argc, char *argv[])
{
	int tcp_socket, newtcp_socket;
	int udp_socket;
	char buffer[BUFLEN];
	struct sockaddr_in serv_addr, cli_addr;
	int n, i, ret;
	socklen_t len;

	fd_set read_fds;	// multimea de citire folosita in select()
	fd_set tmp_fds;		// multime folosita temporar
	int fdmax;			// valoare maxima fd din multimea read_fds
	int v[MAX_CLIENTS], nr;		
	//vector<int> v;
	nr = 0;

	if (argc < 2) {
		usage(argv[0]);
	}

	// se goleste multimea de descriptori de citire (read_fds) si multimea temporara (tmp_fds)
	FD_ZERO(&read_fds);
	FD_ZERO(&tmp_fds);

	/* TCP socket */
	tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
	DIE(tcp_socket < 0, "socket");

	DIE(PORT == 0, "atoi");

	memset((char *) &serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	serv_addr.sin_addr.s_addr = INADDR_ANY;

	ret = bind(tcp_socket, (struct sockaddr *) &serv_addr, sizeof(struct sockaddr));
	DIE(ret < 0, "bind");

	ret = listen(tcp_socket, MAX_CLIENTS);
	DIE(ret < 0, "listen");

	/* UDP socket */
	udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
	DIE(udp_socket < 0, "socket");
	ret = bind(udp_socket, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	DIE(ret < 0, "bind");

	// se adauga file descriptorii in multimea read_fds
	FD_SET(tcp_socket, &read_fds);
	FD_SET(udp_socket, &read_fds);
	FD_SET(STDIN_FILENO, &read_fds);

	fdmax = max(tcp_socket, udp_socket);
	int j;
	char *command;
	while (1) {
		tmp_fds = read_fds; 
		ret = select(fdmax + 1, &tmp_fds, NULL, NULL, NULL);
		DIE(ret < 0, "select");

		for (i = 0; i <= fdmax; i++) {	
			if (FD_ISSET(i, &tmp_fds)) {
				if (i == tcp_socket) {
					// a venit o cerere de conexiune pe socketul inactiv (cel cu listen),
					// pe care serverul o accepta
					len = sizeof(cli_addr);
					newtcp_socket = accept(tcp_socket, (struct sockaddr *) &cli_addr, &len);
					DIE(newtcp_socket < 0, "accept");

					v[++nr] = newtcp_socket;

					// se adauga noul socket intors de accept() la multimea descriptorilor de citire
					FD_SET(newtcp_socket, &read_fds);
					if (newtcp_socket > fdmax) { 
						fdmax = newtcp_socket;
					}

					printf("New client %d connected from %s:%d\n",
							newtcp_socket, inet_ntoa(cli_addr.sin_addr), 
							ntohs(cli_addr.sin_port));
				} else if (FD_ISSET(STDIN_FILENO, &tmp_fds)) { // daca citesc de la strin
					memset(buffer, 0, BUFLEN);
					scanf("%s", buffer);
					if (strcmp(buffer, "exit") == 0) { // exit
						for (int j = 1; j <= nr; j++) { // inchide toate conexiunile
							if (j != tcp_socket) {
								close(j);
								FD_CLR(j, &read_fds);
							}
						}
						close(tcp_socket);
						return 0;
					}
				} else if (FD_ISSET(udp_socket, &tmp_fds)) {
				 //primesc pe UDP
					len = sizeof(cli_addr);
					bzero(buffer, sizeof(buffer));
					n = recvfrom(udp_socket, buffer, sizeof(buffer), 0, 
						(struct sockaddr *)&cli_addr, &len);
					DIE(n < 0, "recv");
					/* Trimite catre toti clientii TCP */
					/* TODO trimitere IP:PORT - UDP */
					mesaj_t mesaj;
					/* copiez informatia de la clientul UDP */
					memcpy(&mesaj, buffer, sizeof(buffer));
					// adaug ip si port in mesaj
					mesaj.ip = inet_ntoa(cli_addr.sin_addr);
					mesaj.port = ntohs(cli_addr.sin_port);
					/* trimit catre toti clientii TCP */
					/* TODO: ar trebui sa trimit doar la cei abonati */
					for (int j = 1; j <= nr; j++) {
						if (v[j] != i) {
							n = send(v[j], buffer, sizeof(buffer), 0);
							/* AICI ar trebui sa trimit si IP + PORT */
							DIE(n < 0, "send");
						}
					}
				} else {
					// s-au primit date pe unul din socketii de client,
					// asa ca serverul trebuie sa le receptioneze
					memset(buffer, 0, BUFLEN);
					n = recv(i, buffer, sizeof(buffer), 0);
					DIE(n < 0, "recv");

					if (n == 0) {
						// conexiunea s-a inchis
						printf("Client %d disconnected\n", i);
						close(i);
						// se scoate din multimea de citire socketul inchis 
						FD_CLR(i, &read_fds);
					} else {
						/* TODO: lista cu userii si topics la care sunt abonati fiecare */
					}
				}
			}
		}
	}
	
	close(tcp_socket);
	close(udp_socket);
	return 0;
}
