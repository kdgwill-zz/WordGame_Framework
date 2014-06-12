#ifndef _COM_WORDGAME_UTILITY_TRIE_H_KYLE
#define _COM_WORDGAME_UTILITY_TRIE_H_KYLE
#include <string>
#include <memory>
using std::string;
namespace com{	namespace wordgame{ namespace utility{ namespace trie{

struct TrieNode{
	char c;
	TrieNode *left, *mid, *right;
	bool isWord;
	TrieNode(char key,
			TrieNode * leftNode = nullptr,
			TrieNode * midNode  = nullptr,
			TrieNode * rightNode = nullptr,
			bool word = false
		):c(key),
	left(leftNode),
	mid(midNode),
	right(rightNode),
	isWord(word){}
};



class Trie{
	private:
		TrieNode* root = nullptr;//root of TST
		int N = 0; //size
		bool lock = false;//Lock adding strings after compression
		TrieNode * get(TrieNode * x,string & key,int d)const;
		TrieNode * add(TrieNode  * x, string & s, int d);
	public:
		//return number of key-value pairs
		int size()const;
		//is string key in table
		bool contains(string & key)const;
		//Return Value
		bool get(string key)const;
		//Insert String into symbol Table
		void add(string s);
		//Find and return longest prefix of s in TST
		string longestPrefix(string s) const;
		//compress the table making it immutable
		void compress();
};


}}}}

#endif
