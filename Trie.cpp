#include "Trie.hpp"
#include <stdexcept>

namespace trie = com::wordgame::utility::trie;
using namespace trie;

template<typename value>
using TrieNode = typename Trie<value>::TrieNode;

static void __toLowerCase(string & s){
	for(int i = 0; i<(int)s.length(); i++){
		s[i] = ::tolower(s[i]);
	}
}

//Longest Common Prefix
//use d to seek into s1 then begin compare s2
static int __lcp(int d,string s1,string s2){
	int count = 0;
	//Must Determine position of last matching character and match the letters 
	//after it meaning decrease total length of search by 1
	for(int i = 0; (d+i) < (int)s1.length()-1 && i < (int)s2.length()-1; i++){
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
	::__toLowerCase(key);
	TrieNode* x = get(root,key,0);
	return x!=nullptr? x->val : defVal;
}


template<typename value>
TrieNode<value> * Trie<value>::get(TrieNode * x,string & key,int d)const{
	if(key.empty()){throw std::invalid_argument("key must have length >= 1");}
	if(x == nullptr) {return nullptr;}
	int offset = ::__lcp(d,key,x->c);
	d += offset;//need to be on last letter // but if at 0 will cause issues so make case
	if	(key[d]<x->c[offset])	return get(x->left, key, d);//if key val less than curr node
	else if	(key[d]>x->c[offset])	return get(x->right,key, d);//if key val greater than curr node
	else if	(d<(int)key.length()-1)	return get(x->mid,  key, d+1);// need to be -2 because of \0 of string
	else 				return x;
}

template<typename value>
void Trie<value>::put(string key,value val){	
	if(val==defVal)throw std::invalid_argument("value is equivalent to default value; Adding is irrelevant");
	if(!contains(key))N++;//increase size
	::__toLowerCase(key);
	root = put(root,key,val,0);
}

template<typename value>
TrieNode<value> * Trie<value>::put(TrieNode  * x, string & key, value val, int d){
	if(x==nullptr) x = new TrieNode(string(1,key[d]),defVal);
	int offset = ::__lcp(d,key,x->c);
	d += offset;//need to be on last letter // but if at 0 will cause issues so make case
	if	(key[d]<x->c[offset])	x->left  = put(x->left,  key, val, d);   //if key val less than curr node
	else if	(key[d]>x->c[offset])	x->right = put(x->right, key, val, d);   //if key val greater than curr node
	else if	(d<(int)key.length()-1)	x->mid   = put(x->mid,   key, val, d+1); //need to be -2 because of  \0
	else 				x->val = val;
	return x;
}

template<typename value>
string Trie<value>::longestPrefix(string key) const{
	if(key.empty()) return "";
	::__toLowerCase(key);	
	TrieNode * x = root;
	int i = 0;
	int len = 0;
	while(x!=nullptr && i < (int)key.length()){
		int offset = __lcp(i,key,x->c);
		i += offset;//need to be on last letter // but if at 0 will cause issues so make case
		if(key[i] < x->c[offset])	x = x->left;
		else if(key[i] > x->c[offset])	x = x->right;
		else{
			i++;
			if(x->val != defVal)len = i;
			x = x->mid;
		}	   
	}
	return key.substr(0,len);
}

template<typename value>
int Trie<value>::compress(){
	int oldN = N;
	//Should think about Sorting and reseting root 
	root = compress(root);		
	return oldN - N;
}

template<typename value>
TrieNode<value> * Trie<value>::compress(TrieNode * x){
	if(x == nullptr) return nullptr;
	else if(x->left != nullptr || x->right != nullptr){
		x->left  = compress(x->left);
		x->mid   = compress(x->mid);
		x->right = compress(x->right);
	}else if(x->mid != nullptr && x->val == defVal){
		//due to matching and general tree structure 
		//changing the parent or child of an an 
		//active node causes mis matching with subsequent calls to get 
		N--;
		x->mid->c.insert(0,x->c);//current letter needs to prepend its next
		return compress(x->mid);
	}
	return x;
}
