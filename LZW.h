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
//Two more for file to char arr

//Compress Directly To File
void compress(char src[],char dst[]);

//Return Compressed txt
int * encode(char input[]);

//Decompress Directly To File
void decompress(char src[],char dst[]);

//Return Decompressed txt
char * decode(int input[]);

#ifdef __cplusplus
}
#endif
#include "LZW.c" //quick hack to add functionality without linking
#endif
