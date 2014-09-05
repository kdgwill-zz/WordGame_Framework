#include <iostream>
#include <string.h>
#include "LZW.h"
int main(){
/**	if(argc != 2){
		printf("Usage: %s FILE_TO_BE_COMPRESSED\n",argv[0]);
		exit(EXIT_FAILURE);
	}
	char* s1 =  argv[1];
        const int i = sizeof(s1)+5;
	char s2[i];
        strcat(s2,s1);
        strcat(s2,".LZW");
	*/
        //compression
	char s3[] = "TOBEORNOTTOBEORTOBEORNOT";
	printf("Encoding Message:[%s]\n",s3);
	encoded_message e = encode(s3);
        
        printf("Decoding[");
	for(size_t i=0;i<e.size-1;i++){
		printf("%d, ",e.arr[i]);
	}
	printf("]\n");
        //decompression
        decoded_message s4 = decode(e.arr);
	printf("Encoded Message:  %s\n",s4.arr);
	printf("LZW Compression | Decompression %s\n", strcmp(s4.arr,s3)==0?"Success":"Failure");
	//exit(EXIT_FAILURE);
        compress("words.dat","test/test.comp");
        decompress("test/test.comp","test/test2.dat"); 
}
