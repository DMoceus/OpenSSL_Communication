#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#undef OPENSSL_NO_SSL_INTERN
#include <openssl/ssl.h>
#include <openssl/evp.h>
#include <openssl/rsa.h>
#include <netdb.h>
#include <stdbool.h>
#include <stdlib.h>

int main(int argc, char** argv){
	SSL_library_init();
	SSL_METHOD* method;
	SSL_CTX* ctx;
	OpenSSL_add_all_algorithms();
	SSL_load_error_strings();
	method = SSLv3_client_method();
	ctx = SSL_CTX_new(method);

	int sd, bytes;
	struct hostent* host;
	struct sockaddr_in addr;
	host = gethostbyname(argv[1]);
	sd = socket(PF_INET, SOCK_STREAM,0);
	memset(&addr,0,sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(argv[2]));
	addr.sin_addr.s_addr = *(long*)(host->h_addr);
	connect(sd, (struct sockaddr*)&addr, sizeof(addr));

	SSL* ssl;
	ssl = SSL_new(ctx);
	SSL_set_fd(ssl, sd);
	SSL_connect(ssl);
	char challenge[1024];
	bool isRunning = true;
	char response[1024];
	int checkNumber = 5;
	int responseNumber = 0;
	printf("First Number Check: ");
	if(scanf("%d",&checkNumber) <= 0){
		isRunning = false;
	}
	if(checkNumber <= 0){
		isRunning = false;
	}
	while(isRunning == true){
		sprintf(challenge,"%d",checkNumber);
		printf("checkNumber: %d\nchallenge: %s\n",checkNumber,challenge);
//		itoa(checkNumber,challenge,10);
		SSL_write(ssl,challenge,sizeof(challenge));
		bytes = SSL_read(ssl,response, sizeof(response));
		response[bytes] = 0;
		responseNumber = atoi(response);
		if(responseNumber == (checkNumber - 1)){
			printf("Server Was Correct! Number: %d\n",responseNumber);
			if(scanf("%d",&checkNumber) <= 0){
				isRunning = false;
			}
			if(checkNumber <= 0){
				isRunning = false;
			}
		}
		else{
			printf("Server Was Not Correct! Number: %d\n",responseNumber);
			isRunning = false;
		}
	}
	SSL_free(ssl);
	return 1;
}
