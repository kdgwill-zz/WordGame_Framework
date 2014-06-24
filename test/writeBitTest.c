#include <stdio.h>

typedef char type_s;
void bprintf(type_s num);

int main(){
	for(int i = 0;i<10;i++){
		type_s t = (type_s)i;
		bprintf(t);
	}
	return 0;
}




void bprintf(type_s num){
	unsigned int size = sizeof(type_s);
	unsigned int maxPow = 1<<(size*8-1);
	unsigned int i=0;
	int j = 0;
	for(;i<size*8;++i){
		// print last bit and shift left.
		printf("%u", !!(num&maxPow));
		num = num<<1;j++;
	}
	printf(": %d\n",j);
}
