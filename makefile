GXX=gcc -g -lcrypto -lssl

all: server client certificate

server: server.c
	$(GXX) server.c -o server

client: client.c
	$(GXX) client.c -o client

certificate:
	openssl req -x509 -newkey rsa:2048 -keyout key.pem -out cert.pem -days 99

clean:
	rm -f *.o *~ server client *.pem
	rm -rf *.o server client *.pem
	
