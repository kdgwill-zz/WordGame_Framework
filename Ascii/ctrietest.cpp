#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <string.h>
#include "ctrie_int.h"

#define WORD_SIZE 41 //wordsize of 20
#define WORD_SIZE_S "40" //wordsize of 20
int main(int argc , char * argv[]){
	if(argc != 2){
		printf("Usage: %s File_Of_Words\n",argv[0]);
		exit(EXIT_FAILURE);
	}
	FILE * fp = NULL;
	char str[WORD_SIZE] = "\0";
	int size = WORD_SIZE;//RANDOM NUMBER WILL BE RESIZED IN THE END	
	Trie_Int * trie = newTrie_Int(0);
	char (*vec)[WORD_SIZE] = (char(*)[WORD_SIZE])calloc(size,sizeof(char[WORD_SIZE]));
	if((fp=fopen(argv[1],"r"))==NULL){
		printf("Can not open %s",argv[1]);
		exit(EXIT_FAILURE);
	}

	int wordCount = 0;
	setlocale (LC_ALL,"");
	while(fscanf(fp,"%" WORD_SIZE_S "s",str)==1 && str[0]!=EOF){
		//first resize if too small
		if(wordCount >= size){
			size *= 2;
			vec = (char (*)[WORD_SIZE])realloc(vec,sizeof(char*[WORD_SIZE])*size);
		}
		//finally add to table
		//snprintf(vec[wordCount],WORD_SIZE,"%ls",str);//adds /0 in case missing strcpy doesn't do that
		snprintf(vec[wordCount],WORD_SIZE,"%s",str);//adds /0 in case missing strcpy doesn't do that
		Trie_Int_put(trie,str,1);
		wordCount++;
	}
	//Now Reallocate to exact size
	vec = (char (*)[WORD_SIZE])realloc(vec,sizeof(char[WORD_SIZE])*wordCount);
	//Close File Properly
	if(fclose(fp)!=0){
		printf("Error in closing file %s\n",argv[1]);
	}
	printf("WordCount [%d]\n",wordCount);
	printf("Total Number of Nodes Before Compression: %d\n", Trie_Int_size(trie));
	printf("Total Nodes Removed: %d \n",Trie_Int_compress(trie));
	printf("Total Number of Nodes After Compression: %d\n", Trie_Int_size(trie));
	//DebugMode
	int mod = (wordCount * 10)/100;
	int p = -10;
	printf("Processing %d word/s\n", wordCount);
	for(int i=0;i < wordCount;i++){
		strcpy(str,*(vec+i));//   /0 assured from previous calls
		if(Trie_Int_contains(trie,str)==0){
			printf("Processing Interrupted\nTrie Tree Could Not Find %s\n", str);
			exit(EXIT_FAILURE);	
		}
		if(i%mod==0){
			p+=10;
			printf("%3d%% Completed\n",p);
		}

	}
	printf("100%% Completed\n");
	printf("Processing Completed\n");
/*
	FILE * f = NULL;
	if((f=fopen("test.txt","w"))==NULL){
		printf("Can not open %s\n","test.dat");
		exit(EXIT_FAILURE);
	}

	for(int i=0;i < wordCount;i++){
		fprintf(f,"%s\n",vec[i]);
	}
	
	//puts("File contents:");
	//rewind(fp);
	//char words[41];
	//while (fscanf(fp,"%s",words) == 1)
	//	puts(words);
	//puts("Done!");
	//fflush(fp);

	if(fclose(f)!=0){
		printf("Error in closing file %s\n",argv[1]);
	}
*/
	deleteTrie_Int(trie);	
	free(vec);
	return 0;
}
