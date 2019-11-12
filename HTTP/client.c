#include <stdio.h>      /* printf, sprintf */
#include <stdlib.h>     /* exit, atoi, malloc, free */
#include <unistd.h>     /* read, write, close */
#include <string.h>     /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h>      /* struct hostent, gethostbyname */
#include <arpa/inet.h>
#include <string.h>
#include <json-c/json.h>
#include "helpers.h"
#include "requests.h"

/* Functie care rezolva task1 */
char *task1(int sockfd) {
    char *message = compute_get_request(IP_SERVER, "/task1/start", NULL);
    send_to_server(sockfd, message);
    char *response = receive_from_server(sockfd);
    free(message);
    return response;
}
/* Get json from message */
char *getJSON(char *buffer) {
    char *data = strstr(buffer, "\r\n\r\n");
    if (data != NULL) data += 4;
    else return "NO DATA";
    return data;
}

/* 
* Functie care primeste ca parametru raspunsul de la server si returneaza cookies
*/
char *getCookie(char *buffer) {
    char *aux_buffer = malloc(BUFLEN);
    strcpy(aux_buffer, buffer);
    char *data = malloc(BUFLEN);
    char *message = malloc(BUFLEN);
    char delim[2] = "\r\n";

    char *token = strtok(aux_buffer, delim);
    int i = 0;
    while (token != NULL && i < 2) {
        i++;
        token = strtok(NULL, delim);
    }
    data = token;
    data += 12;
    strcpy(message, "Cookie: ");
    strcat(message, data);
    strcat(message, ";\n");
    token = strtok(NULL, delim);
    token += 12; // Skip "Set-Cookie: "
    strcat(message, "Cookie: ");
    strcat(message, token);
    return message;
}

/* Functie care preia json de la server si salveaza campurile intr-o structura */
data_T parser(char *buffer) {
    data_T data_json;
    data_json.parsed_json = json_tokener_parse(buffer);

    json_object_object_get_ex(data_json.parsed_json, "enunt", &data_json.enunt);
    json_object_object_get_ex(data_json.parsed_json, "url", &data_json.url);
    json_object_object_get_ex(data_json.parsed_json, "method", &data_json.method);
    json_object_object_get_ex(data_json.parsed_json, "type", &data_json.type);
    json_object_object_get_ex(data_json.parsed_json, "data", &data_json.data);
    json_object_object_get_ex(data_json.data, "username", &data_json.username);
    json_object_object_get_ex(data_json.data, "password", &data_json.password);
    json_object_object_get_ex(data_json.data, "token", &data_json.token);
    json_object_object_get_ex(data_json.data, "queryParams", &data_json.queryParams);
    json_object_object_get_ex(data_json.queryParams, "id", &data_json.id);
    return data_json;
}

/* Functie care rezolva task2 */
char *task2(int sockfd, data_T data_json, char *cookie) {
    char *message = malloc(BUFLEN);
    char *line = malloc(BUFLEN);
    char *data = malloc(BUFLEN);
    sprintf(data, "username=%s&password=%s", json_object_get_string(data_json.username),
        json_object_get_string(data_json.password));

    sprintf(line, "%s %s HTTP/1.1", json_object_get_string(data_json.method),
            json_object_get_string(data_json.url));
    strcat(message, line);
    strcat(message, "\n");

    sprintf(line, "Host: %s", IP_SERVER);
    strcat(message, line);
    strcat(message, "\n");

    strcat(message,cookie);
    strcat(message, "\n");

    sprintf(line, "Content-Type: %s", json_object_get_string(data_json.type));
    strcat(message, line);
    strcat(message, "\n");

    sprintf(line, "Content-Length: %ld", strlen(data));
    strcat(message, line);
    strcat(message, "\n");

    strcpy(line, "\r\n");
    strcat(message, line);

    compute_message(message, data);
    
    send_to_server(sockfd, message);
    free(message);
    free(data);
    free(line);
    return receive_from_server(sockfd);
}
/* Functie care rezolva task3 */
char *task3(int sockfd, data_T data_json, char *cookie) {
    char *message = malloc(BUFLEN);
    char *line = malloc(BUFLEN);
    char *raspuns1 = malloc(BUFLEN);
    char *raspuns2 = malloc(BUFLEN);
    strcpy(raspuns1, "omul");
    strcpy(raspuns2, "numele");

    sprintf(line, "%s %s?raspuns1=%s&raspuns2=%s&id=%s HTTP/1.1",
        json_object_get_string(data_json.method),  
        json_object_get_string(data_json.url), raspuns1, raspuns2, 
        json_object_get_string(data_json.id));
    compute_message(message, line);

    sprintf(line, "Host: %s", IP_SERVER);
    compute_message(message, line);
    sprintf(line, "Authorization: Bearer %s", 
            json_object_get_string(data_json.token));

    compute_message(message, line);

    strcat(message, cookie);
    strcat(message, "\r\n");

    strcpy(line, "\r\n");
    strcat(message, line);
    
    send_to_server(sockfd, message);  
    free(raspuns1);
    free(raspuns2);
    free(line);
    free(message);
    
    return receive_from_server(sockfd);
}
/* Functie care rezolva task4 */
char *task4(int sockfd, data_T data_json, char *cookie) {
    char *message = malloc(BUFLEN);
    char *line = malloc(BUFLEN);

    sprintf(line, "%s %s HTTP/1.1", json_object_get_string(data_json.method),
            json_object_get_string(data_json.url));
    compute_message(message, line);

    sprintf(line, "Host: %s", IP_SERVER);
    compute_message(message, line);

    sprintf(line, "Authorization: Bearer %s", 
            json_object_get_string(data_json.token));
    compute_message(message, line);

    strcat(message, cookie);
    strcat(message, "\r\n\r\n");
    send_to_server(sockfd, message);
    free(message);
    free(line);
    
    return receive_from_server(sockfd);
}

int main(void)
{
    /* --- Task1 --- */

    int sockfd;
    char *buffer;
    char *cookie, *body;
    sockfd = open_connection(IP_SERVER, PORT_SERVER, AF_INET, SOCK_STREAM, 0);
    buffer = task1(sockfd);
    puts(buffer);
    printf("\n");    
    close_connection(sockfd);

    /* --- Task2 --- */

    cookie = getCookie(buffer);
    body = getJSON(buffer);
    data_T data_json = parser(body); 
    
    sockfd = open_connection(IP_SERVER, PORT_SERVER, AF_INET, SOCK_STREAM, 0);  
    buffer = task2(sockfd, data_json, cookie);
    puts(buffer);
    printf("\n");
    close_connection(sockfd);
   
    /* --- Task3 --- */
    
    memset(&data_json, 0, sizeof(data_T));
    cookie = getCookie(buffer);
    body = getJSON(buffer);
    data_json = parser(body);

    sockfd = open_connection(IP_SERVER, PORT_SERVER, AF_INET, SOCK_STREAM, 0);  
    buffer = task3(sockfd, data_json, cookie);
    puts(buffer);
    printf("\n");
    close_connection(sockfd);

    /* --- Task4 --- */

    struct json_object *token;
    token = data_json.token; // copiez tokenul folosit la task3
    memset(&data_json, 0, sizeof(data_T));

    body = getJSON(buffer);
    data_json = parser(body);
    data_json.token = token;
    cookie = getCookie(buffer);

    sockfd = open_connection(IP_SERVER, PORT_SERVER, AF_INET, SOCK_STREAM, 0);
    buffer = task4(sockfd, data_json, cookie);
    puts(buffer);
    printf("\n");
    close_connection(sockfd);
    free(buffer);
    return 0;
}