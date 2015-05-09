#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <openssl/ssl.h>
#include <openssl/evp.h>
#include <openssl/rsa.h>
#include <stdbool.h>
#include <stdlib.h>

int main(int argc, char** argv){
	
	SSL_library_init();
	SSL_METHOD* method;
	SSL_CTX* ctx;
	OpenSSL_add_all_algorithms();
	SSL_load_error_strings();
	method = SSLv3_server_method();
	ctx = SSL_CTX_new(method);


	SSL_CTX_use_certificate_file(ctx,argv[1],SSL_FILETYPE_PEM);
	SSL_CTX_use_PrivateKey_file(ctx,argv[2],SSL_FILETYPE_PEM);
	if(!SSL_CTX_check_private_key(ctx)){
		abort();
	}
	
	//TCP Server SETUP / Connection
	int sd, client;
	struct sockaddr_in addr;
	sd						= socket(PF_INET, SOCK_STREAM, 0); 	//Create new Stream Socket
	memset(&addr, 0, sizeof(addr));
	addr.sin_family			= AF_INET;
	addr.sin_port			= htons(atoi(argv[3]));						//Select port
	addr.sin_addr.s_addr	= INADDR_ANY;						//Any Available Address
	bind(sd, (struct sockaddr*)&addr, sizeof(addr));			//Bind the socket to address
	listen(sd,10);												//Make into Listening Socket
	client = accept(sd,0,0);									//Await and Accept Connections
	

	int bytes;
	char buf[1024];
	int numberHolder;
	SSL* ssl = SSL_new(ctx);
	SSL_set_fd(ssl,client);
	SSL_accept(ssl);
	
	while(true){
		bytes = SSL_read(ssl,buf,sizeof(buf));
		buf[bytes] = 0;
		printf("Passed In: %s\n",buf);
		numberHolder = atoi(buf);
		sprintf(buf,"%d",numberHolder-1);
		SSL_write(ssl,buf,sizeof(buf));
	}

	bytes = SSL_read(ssl,buf,sizeof(buf));
	buf[bytes] = 0;
	printf("Message: %s \n",buf);


	client = SSL_get_fd(ssl);
	SSL_free(ssl);
	close(sd);
	
	return 1;
}
