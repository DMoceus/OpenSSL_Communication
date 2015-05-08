#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#undef OPENSSL_NO_SSL_INTERN
#include <openssl/ssl.h>
#include <openssl/evp.h>
#include <openssl/rsa.h>
#include <netdb.h>


int main(){
	SSL_library_init();
	SSL_METHOD* method;
	SSL_CTX* ctx;
	OpenSSL_add_all_algorithms();
	SSL_load_error_strings();
	method = SSLv3_client_method();
	ctx = SSL_CTX_new(method);

	int sd;
	struct hostent* host;
	struct sockaddr_in addr;
	host = gethostbyname("localhost");
	sd = socket(PF_INET, SOCK_STREAM,0);
	memset(&addr,0,sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(1234);
	addr.sin_addr.s_addr = *(long*)(host->h_addr);
	int server = connect(sd, (struct sockaddr*)&addr, sizeof(addr));

	SSL* ssl;
	ssl = SSL_new(ctx);
	SSL_set_fd(ssl, server);
	SSL_set_connect_state(ssl);
	SSL_connect(ssl);
	char* reply = "12345";
	SSL_write(ssl,reply,sizeof(reply));
	SSL_free(ssl);
	return 1;
}
