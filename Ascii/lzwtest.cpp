#include <iostream>
#include <string.h>
#include "LZW.h"
int main(){
        //compression
	char s3[] = "TOBEORNOTTOBEORTOBEORNOT";
	printf("\n\nEncoding Message:[%s]\n",s3);
	encoded_message e = encode(s3);
        
        printf("Decoding[");
	for(size_t i=0;i<e.size-1;i++){
		printf("%d, ",e.arr[i]);
	}
	printf("]\n");
        //decompression
        decoded_message s4 = decode(e.arr);
	printf("Encoded Message:  %s\n",s4.arr);
	printf("LZW Compression | Decompression %s\n\n", strcmp(s4.arr,s3)==0?"Success":"Failure");

        return 0;
}
