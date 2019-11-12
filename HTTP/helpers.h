#ifndef _HELPERS_
#define _HELPERS_

#define BUFLEN 2*4096
#define LINELEN 100
#define IP_SERVER "185.118.200.35"
#define PORT_SERVER 8081

typedef struct {
    struct json_object *parsed_json;
    struct json_object *enunt;
    struct json_object *url;
    struct json_object *method;
    struct json_object *type;
    struct json_object *data;
    struct json_object *id;
    struct json_object *username;
    struct json_object *password;
    struct json_object *token;
    struct json_object *queryParams;
} data_T;

void error(const char *msg);
void compute_message(char *message, const char *line);
int open_connection(char *host_ip, int portno, int ip_type, int socket_type, int flag);
void close_connection(int sockfd);
void send_to_server(int sockfd, char *message);
char *receive_from_server(int sockfd);

#endif
