CC=gcc
CFLAGS= -ljson-c -Wall

client: client.c requests.c helpers.c
		$(CC) -o client client.c requests.c helpers.c $(CFLAGS)
		
run: client
		./client

clean:
		rm -f *.o client
