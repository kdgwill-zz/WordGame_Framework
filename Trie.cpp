#include "Trie.h"
#include <stdexcept>

namespace trie = com::wordgame::utility::trie;
using namespace trie;
/**
//std::exception	An exception and parent class of all the standard C++ exceptions.
 * std::bad_alloc	This can be thrown by new.
 * std::bad_cast		This can be thrown by dynamic_cast.
 * std::bad_exception	This is useful device to handle unexpected exceptions in a C++ program
 * std::bad_typeid	This can be thrown by typeid.
 * std::logic_error	An exception that theoretically can be detected by reading the code.
 * std::domain_error	This is an exception thrown when a mathematically invalid domain is used
 * std::invalid_argument	This is thrown due to invalid arguments.
 * std::length_error	This is thrown when a too big std::string is created
 * std::out_of_range	This can be thrown by the at method from for example a std::vector and std::bitset<>::operator[]().
 * std::runtime_error	An exception that theoretically can not be detected by reading the code.
 * std::overflow_error	This is thrown if a mathematical overflow occurs.
 * std::range_error	This is occured when you try to store a value which is out of range.
 * std::underflow_error	This is thrown if a mathematical underflow occurs.
 */


void toLowerCase(string & s){
	for(int i = 0; s[i] != '\0'; i++){
		s[i] = ::tolower(s[i]);
	}
}

int Trie::size()const{return N;}

bool Trie::get(string key) const {
	if(key.empty()){throw std::invalid_argument("key must have length >= 1");}
	::toLowerCase(key);
	TrieNode* x = get(root,key,0);
	if(x == nullptr) return false;
	return x->isWord;
}

TrieNode * Trie::get(TrieNode * x,string & key,int d)const{
	if(key.empty()){throw std::invalid_argument("key must have length >= 1");}
	if(x == nullptr) {return nullptr;}
	char c = key[d];
	if      (c < x->c)             		return get(x->left,  key, d);
	else if (c > x->c)             		return get(x->right, key, d);
	else if (d < (int)key.length() - 1) 	return get(x->mid,   key, d+1);
	else                           		return x;
}

void Trie::add(string key){	
	if(lock==true)return;//IF TABLE LOCKED RETURN
	if(get(key)==true)return;
	::toLowerCase(key);
	root = add(root,key,0);
	N++;
}

TrieNode * Trie::add(TrieNode  * x, string & key, int d){
	if(lock==true)return nullptr;//IF TABLE LOCKED RETURN
	char c = key[d];
	if(x==nullptr){
		x = new TrieNode(c);
	}
	if      (c < x->c)             		x->left  = add(x->left,  key, d);
	else if (c > x->c)             		x->right = add(x->right, key, d);
	else if (d < (int)key.length() - 1)  	x->mid   = add(x->mid, key, d+1);
	else                          		x->isWord = true;
	return x;
}

string Trie::longestPrefix(string key) const{
	if(key.empty()) return "";
	::toLowerCase(key);	
	TrieNode * x = root;
	int i = 0;
	while(x!=nullptr && i < (int)key.length()){
		char c = key[i];
		if(c < x->c){x = x->left;}
		else if(c > x->c){x = x->right;}
		else{
			i++;
			x = x->mid;
		}	   
	}
	return key.substr(0,i);
}

void Trie::compress(){
	//This will require reorgonizing and Deleting Nodes 
	//should focus from top to bottom it downward sweeping motion
	
}




