/******************************************************************************
 * **  C Trie Tree
 * **  --------------------------------------------------------------------------
 * **  
 * **  C wrapper for Trie Tree.
 * **  
 * **  Author: Kyle D. Williams
 * **
 * **
 * ******************************************************************************/
#ifndef COM_WORDGAME_UTILITY_CTRIE_H_KDGWILL
#define COM_WORDGAME_UTILITY_CTRIE_H_KDGWILL

#ifdef __cplusplus
extern "C"{ //this is used to identify following code as C specific code which will enforce C style name mangling
#endif

//Declare a new void Type To Emulate C class
typedef void Trie_Int;
//Declare a common struct to emulate C++ Vectors
struct Trie_Int_Vec{
	const char* data;
	int size;
};
typedef Trie_Int_Vec Trie_Int_Vec;
//Create new Trie_Int Object
Trie_Int * newTrie_Int(int defVal);
//Delete Trie_Int Object 
void deleteTrie_Int(Trie_Int * trie);
//return number of key-value pairs
int Trie_Int_size(Trie_Int * t);
//return default value set by user
int Trie_Int_getDefaultValue(Trie_Int * t);
//Check if returned value is not equal to default value
int Trie_Int_contains(Trie_Int * t,const char * key);
//Return Value
int Trie_Int_get(Trie_Int * t,const char * key);
//Insert String into symbol Table
void Trie_Int_put(Trie_Int * t,const char * s,int val);
//Find and return longest prefix of s in TST
const char * Trie_Int_longestPrefix(Trie_Int * t,const char * s);
//return all words contained in the tree
//Trie_Int_Vec keys(Trie_Int * t);
//return all keys starting with a given prefix
//Trie_Int_Vec prefixMatch(Trie_Int * ,const char * prefix);
//compress the table making it immutable returning the number of nodes removed
int Trie_Int_compress(Trie_Int * t);

#ifdef __cplusplus
}
#endif

//Take not this is added inside the header gaurd
//This is the Correct way to include a file as seperate 
#include "ctrie_int.ii" //quick hack to add functionality without linking



#include "Trie.hpp" //C++ code
//THIS HAS TO BE COMPILED WITH C++ COMPILER TO BE COMPILED PROPERLY ANYWAY GAURDS UNEEDED
extern "C"{

//Create new Trie_Int Object
Trie_Int * newTrie_Int(int defVal){return new Trie<int>(defVal);}
//Delete Trie_Int Object
void deleteTrie_Int(Trie_Int * trie){delete ((Trie<int> *)trie);}
//return number of key-value pairs
int Trie_Int_size(Trie_Int * t){return ((Trie<int> *)t)->size();}
//return default value set by user
int Trie_Int_getDefaultValue(Trie_Int * t){return ((Trie<int> *)t)->getDefaultValue();}
//Check if returned value is not equal to default value
int Trie_Int_contains(Trie_Int * t,const char * key){return ((Trie<int> *)t)->contains(key); }
//Return Value
int Trie_Int_get(Trie_Int * t,const char * key){return ((Trie<int> *)t)->get(key); }
//Insert String into symbol Table
void Trie_Int_put(Trie_Int * t,const char * s,int val){ ((Trie<int> *)t)->put(s,val);}
//Find and return longest prefix of s in TST
const char * Trie_Int_longestPrefix(Trie_Int * t,const char * s){
	std::string str = ((Trie<int> *)t)->longestPrefix(s);
	int length = str.length()+1;
	char * arr = new char[length];
	snprintf(arr,length,"%s",str.c_str());
	return arr;
}

//return all words contained in the tree
//Trie_Int_Vec keys(Trie_Int * t);
//return all keys starting with a given prefix
//Trie_Int_Vec prefixMatch(Trie_Int * ,const char * prefix);
//compress the table making it immutable returning the number of nodes removed
int Trie_Int_compress(Trie_Int * t){return  ((Trie<int> *)t)->compress();}

}

#endif
