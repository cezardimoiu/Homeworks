#include <stdlib.h>     /* exit, atoi, malloc, free */
#include <stdio.h>
#include <unistd.h>     /* read, write, close */
#include <string.h>     /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h>      /* struct hostent, gethostbyname */
#include <arpa/inet.h>
#include "helpers.h"
#include "requests.h"

char *compute_get_request(char *host, char *url, char *url_params)
{
    char *message = calloc(BUFLEN, sizeof(char));
    char *line = calloc(LINELEN, sizeof(char));

    if (url_params != NULL)
        sprintf(line, "GET %s?%s HTTP/1.1", url, url_params);
    else 
        sprintf(line, "GET %s HTTP/1.1", url);
    compute_message(message, line);

    sprintf(line, "Host: %s", host);
    compute_message(message, line);

    strcpy(line, "\r\n");
    strcat(message, line);
    free(line);
    
    return message;
}
char *compute_post_request(char *host, char *url, char *form_data)
{
    char *message = calloc(BUFLEN, sizeof(char));
    char *line = calloc(LINELEN, sizeof(char));
    
    sprintf(line, "POST %s HTTP/1.1", url);
    compute_message(message, line);
    sprintf(line, "Host: %s", host);
    compute_message(message, line);
    
    sprintf(line, "Content-Type: application/x-www-form-urlencoded");
    compute_message(message, line);

    sprintf(line, "Content-Length: %ld", sizeof(form_data));
    compute_message(message, line);

    strcpy(line, "\r\n");
    strcat(message, line);
    return message;
}