/******************************************************************************
 * **  LZW compression
 * **  --------------------------------------------------------------------------
 * **  
 * **  Compresses data using LZW algorithm.
 * ** 
 * **  Port of LZW.java http://algs4.cs.princeton.edu/55compression/LZW.java.html 
 * ** 
 * **  Author: Kyle D. Williams
 * ******************************************************************************/
#ifndef COM_WORDGAME_UTILITY_LZW_HPP_KDGWILL
#define COM_WORDGAME_UTILITY_LZW_HPP_KDGWILL
#include <locale.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string> 
#include <cstdint>
#include "Trie.hpp"
//Compress Raw Stream ideally use sstream or fstream
void compressLZW(std::istream & src, std::ostream & dst);
//Decompress Raw Stream ideally use sstream or fstream
void decompressLZW(std::istream & src, std::ostream & dst);
//Compress Directly to File
void compressLZW(char * src, char * dst);
//Decompress Directly to File
void decompressLZW(char * src, char * dst);
//Compress Complex Stream
void compressLZW(char * src, std::ostringstream & dst);
//Decompress Complex String Stream
void decompressLZW(std::istringstream & src, char * dst);
#include "LZW.ii" //quick hack to add functionality without linking
#endif
