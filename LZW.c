#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ctrie_int.h"

#ifdef __cplusplus
extern "C"{
#endif

#define R 256  // number of input chars
#define L 4096 // number of codewords = 2^W
#define W 12   // codeword width
///////////////////////DONT FORGET TO CREATE STRUCT FOR ENCODED AND DECODED INSTEAD OF RETURNING ALLOCATED VARIABLE
//Compression
int * encode(char input[]){
	std::setlocale(LC_ALL, "");
	int length = strlen(input);
	int * arr = (int *)calloc(length,sizeof(int));//can never be more than its input 
	size_t size = 0;
	char temp[L];//Probably will not exceed L
	const char * tex;
	//since null character ignored, error will be returned if it is referenced
	Trie_Int * trie = newTrie_Int(0);	
	//Character at ascii 0 is Null 
	//Due to implimentation of Trie Tree
	//will throw error if added so start at 1 instead
	for(int i = 1; i<R; i++){
		//need to convert int to wchar to make sure get full character encoding
		//snprintf(temp,L,"%lc",wchar_t(i));
		snprintf(temp,L,"%lc",wchar_t(i));
		Trie_Int_put(trie,temp,i);
	}
	int code = R+1; // R is codeword for EOF
	//Actual Encoding
	while((length=strlen(input)) > 0){
		tex = Trie_Int_longestPrefix(trie,input); //Find max prefix match tex
		printf("WORD: %-5s\t\t",tex);
		arr[size++] = Trie_Int_get(trie,tex);	//Add encoding 
		int t = strlen(tex);
		if(t < length && code < L){//add s to symbol table
			snprintf(temp,(t+1)+1,"%s",input);//remember need extra for null terminiation
			Trie_Int_put(trie,temp,code++);
		}
		input+=t;//Scan past s in input
		printf("%-4s,%d\t| INSERTED: %-5s  | INPUT: %-25s,%zu\n",tex,t,temp,input,strlen(input));
		delete tex; // prevent memory leak due to using new to allocate
	}

	arr[size++] = R;	//Add encoding 
	arr[size++] = EOF;	//If Reach this token that means its done 
	
	deleteTrie_Int(trie);
	if(size < 1){
		delete arr;
		arr = NULL;
	}else{
		arr = (int*)realloc(arr,sizeof(int)*size);
	}
	return arr;
}

char * decode(int input[]){
	std::setlocale(LC_ALL, "");
	size_t length;//strlen(input);
	for(length=0;input[length]!=R;length++);//find proper length
	char * arr = (char *)calloc(length*10,sizeof(char));//can never be more than its input 
	size_t cons = 0;//to count input
	char st[L][W];//new character string length L
	int i;//next available codeword value
	//Initialize symbol table with all 1-character strings
	for(i = 0;i<R;i++){
		//need to convert int to char *
		snprintf(st[i],2,"%c",char(i));
	}	
	snprintf(st[i++],2,"%s","");//(unused) lookahead for EOF
	
	int codeword = input[cons++]; 
	char * val = st[codeword];
	
	//Actual Encoding	
	while(1){
		strcat(arr,val);
		//arr[size++]=*val;
		//snprintf(arr[size++],W,"%s",val);
		codeword = input[cons++];
		if(codeword == R)break;
		char * s= st[codeword];
		if(i==codeword)sprintf(s,"%s%c",val,val[0]);//special case hack
		if(i < L) sprintf(st[i++],"%s%c",val,s[0]);
		val = s;	
	}
	//arr[size++] = '\0';	//If Reach this token that means its done 
	int size = strlen(arr);
	if(size == 0){
		delete arr;
		arr = NULL;
	}else{
		//arr = (int*)realloc(arr,sizeof(int)*size);
	}
	return arr;

}

void compress(char src[],char dst[]){
	FILE * srp = NULL;
	FILE * dsp = NULL;
	//Open Files
	if((srp=fopen(src,"r"))==NULL){
		fprintf(stderr,"Can not open %s\n",src);
		exit(EXIT_FAILURE);	
	}
	if((dsp=fopen(dst,"wb"))==NULL){
		fprintf(stderr,"Can not open %s\n",dst);
		exit(EXIT_FAILURE);	
	}
	if(setvbuf(dsp,NULL,_IOFBF,L)!=0){
		fputs("Can't create output buffer\n",stderr);
		exit(EXIT_FAILURE);
	}

	//char * encoded;// = encode();

	//Close Files Properly
	if(fclose(srp)!=0){
		fprintf(stderr,"Error in closing files %s\n",src);
	}
	if(fclose(dsp)!=0){
		fprintf(stderr,"Error in closing files %s\n",dst);
	}
	//delete encoded;
}

void decompress(char src[],char dst[]){
	FILE * srp = NULL;
	FILE * dsp = NULL;
	//Trie_Int * trie = newTrie_Int(0);
	//Open Files
	if((srp=fopen(src,"rb"))==NULL){
		fprintf(stderr,"Can not open %s\n",src);
		exit(EXIT_FAILURE);	
	}
	if((dsp=fopen(dst,"w"))==NULL){
		fprintf(stderr,"Can not open %s\n",dst);
		exit(EXIT_FAILURE);	
	}
	if(setvbuf(dsp,NULL,_IOFBF,L)!=0){
		fputs("Can't create output buffer\n",stderr);
		exit(EXIT_FAILURE);
	}
	
	//Close Files Properly
	if(fclose(srp)!=0){
		fprintf(stderr,"Error in closing files %s\n",src);
	}
	if(fclose(dsp)!=0){
		fprintf(stderr,"Error in closing files %s\n",dst);
	}
}

#ifdef __cplusplus
}
#endif
