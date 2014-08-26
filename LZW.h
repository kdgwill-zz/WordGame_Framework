/******************************************************************************
 * **  LZW compression
 * **  --------------------------------------------------------------------------
 * **  
 * **  Compresses data using LZW algorithm.
 * **  
 * **  Author: Kyle D. Williams
 * **
 * **
 * ******************************************************************************/
#ifndef COM_WORDGAME_UTILITY_LZW_H_KDGWILL
#define COM_WORDGAME_UTILITY_LZW_H_KDGWILL

#ifdef __cplusplus
extern "C"{ //this is used to identify following code as C specific code which will enforce C style name mangling
#endif
#include <string.h> //used for size_t but fine since included file requires it and includegaurds will prevent anything malicious

//Two more for file to char arr
typedef struct encoded_message{
	int * arr;
	size_t size;
}encoded_message;
//typedef struct encoded_message encoded_message;

typedef struct decoded_message{
	char * arr;
	size_t size;
}decoded_message;

//Compress Directly To File
void compress(char src[],char dst[]);

//Return Compressed txt
encoded_message encode(char input[]);

//Decompress Directly To File
void decompress(char src[],char dst[]);

//Return Decompressed txt
decoded_message decode(int input[]);

#ifdef __cplusplus
}
#endif
#include "LZW.i" //quick hack to add functionality without linking
#endif
