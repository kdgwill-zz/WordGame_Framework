#include "Trie.h"
#include <stdexcept>
#include <iostream>
using namespace std;

namespace trie = com::wordgame::utility::trie;
using namespace trie;

template<typename value>
using TrieNode = typename Trie<value>::TrieNode;

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

//Longest Common Prefix
//use d to seek into s1 then begin compare s2
int lcp(int d,string s1,string s2){
	int count = 0;
	for(int i = 0; (d+i) < (int)s1.length() && i < (int)s2.length(); i++){
		if(s1[d+i] != s2[i])break;
		count++;
	}
	return count;
}

template<typename value>
int Trie<value>::size()const{return N;}

template<typename value>
value Trie<value>::getDefaultValue()const{return defVal;}

template<typename value>
bool Trie<value>::contains(const string key)const{return get(key)!=defVal;}

template<typename value>
value Trie<value>::get(string key) const {
	if(key.empty()){throw std::invalid_argument("key must have length >= 1");}
	::toLowerCase(key);
	TrieNode* x = get(root,key,0);
	return x!=nullptr? x->val : defVal;
}


template<typename value>
TrieNode<value> * Trie<value>::get(TrieNode * x,string & key,int d)const{
	if(key.empty()){throw std::invalid_argument("key must have length >= 1");}
	if(x == nullptr) {return nullptr;}
	int offset = lcp(d,key,x->c);
	if	(key[d] < x->c[0])			return get(x->left, key, d);//if key val less than curr node
	else if	(key[d] > x->c[0])			return get(x->right,key, d);//if key val greater than curr node
	else if	(d < (int)key.length()-1)	return get(x->mid,  key, d+offset);//Current + longest common prefix
	else 					return x;
}

template<typename value>
void Trie<value>::put(string key,value val){	
	if(val==defVal)throw std::invalid_argument("value is equivalent to default value; Adding is irrelevant");
	if(!contains(key))N++;//increase size
	::toLowerCase(key);
	root = put(root,key,val,0);
}

template<typename value>
TrieNode<value> * Trie<value>::put(TrieNode  * x, string & key, value val, int d){
	if(x==nullptr) x = new TrieNode(string(1,key[d]),defVal);
	int offset = lcp(d,key,x->c);
	if	(key[d] < x->c[0])			x->left  = put(x->left,  key, val, d);   //if key val less than curr node
	else if	(key[d] > x->c[0])			x->right = put(x->right, key, val, d);   //if key val greater than curr node
	else if	(d < (int)key.length()-1)	x->mid   = put(x->mid,   key, val, d+offset); //Current + longest common prefix
	else 					x->val = val;
	return x;
}

template<typename value>
string Trie<value>::longestPrefix(string key) const{
	if(key.empty()) return "";
	::toLowerCase(key);	
	TrieNode * x = root;
	int i = 0;
	int len = 0;
	while(x!=nullptr && i < (int)key.length()){
		char c = key[i];
		if(c < x->c[0])		x = x->left;
		else if(c > x->c[0])	x = x->right;
		else{
			int offset = lcp(i,key,x->c);
			i+=offset;
			if(x->val != defVal)len = i;
			x = x->mid;
		}	   
	}
	return key.substr(0,len);
}

template<typename value>
int Trie<value>::compress(){
	int oldN = N;
	//Should thing about Sorting and reseting root 
	compress(nullptr,root);		
	return oldN - N;
}

template<typename value>
void Trie<value>::compress(TrieNode * parent, TrieNode * x){
	if(x == nullptr) return;
	if(x->left == nullptr && x->right==nullptr && x->mid!=nullptr){
		x->mid->c += x->c;
		if(parent!=nullptr)parent->mid = x->mid;	
		compress(parent,x->mid);
		N--;
	}else{
		compress(x,x->left);
		compress(x,x->right);
	}
}
