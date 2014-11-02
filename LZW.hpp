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
namespace LZW{
	//Compress Raw Stream ideally use stringstream or fstream
	void compressLZW(std::istream & src, std::ostream & dst);
	//Decompress Raw Stream ideally use stringstream or ifstream
	void decompressLZW(std::istream & src, std::ostream & dst);

	//Compress Directly to File
	void compressLZW(const char * src,const char * dst);
	//Decompress Directly to File
	void decompressLZW(const char * src, const char * dst);

	//Compress From Stream to File
	void compressLZW(std::istream & src,const char * dst);
	//Decompress File To Stream
	void decompressLZW(const char * src, std::ostream & dst);

	//Compress Objects to File
	//template<typename value>
	//	void compressLZW(const Trie<value> & srct,const char * dst);
	//Deompress Objects from File
	//template<typename value>
	//	void decompressLZW(const char * src,Trie<value>  & dstt);
}

#include "LZW.ii" //quick hack to add functionality wiithout linking
#endif
