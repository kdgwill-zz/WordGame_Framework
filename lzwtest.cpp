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
	//char s3[] = "TO 1 BE 2 OR 3 NOT 4 TO 5 BE 6 OR 7 TO 8 BE 9 OR 10 NOT 11";
	//char s3[] = u8"TOBEORNOTTOBEORTOBEORNOT\u00df\u6c34\U0001d10b";
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
}
