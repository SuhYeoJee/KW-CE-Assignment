#include <stdio.h>	//sprintf()
#include <string.h>	//strcpy()
#include <openssl/sha.h>	//SHA1()

char *sha1_hash (char *input_url, char *hashed_url){
	unsigned char hashed_160bits[20];
	char hashed_hex[41];
	int i;
	
	SHA1(input_url, strlen(input_url), hashed_160bits);

	for(i=0;i<sizeof(hashed_160bits);i++)
		sprintf(hashed_hex + i*2, "%02x", hashed_160bits[i]);

	strcpy(hashed_url,hashed_hex);
	return hashed_url;
}
