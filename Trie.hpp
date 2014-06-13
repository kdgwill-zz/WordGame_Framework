#ifndef _COM_WORDGAME_UTILITY_TRIE_H_KYLE
#define _COM_WORDGAME_UTILITY_TRIE_H_KYLE
#include <string>
using std::string;
namespace com{	namespace wordgame{ namespace utility{ namespace trie{

template<typename value>
class Trie{
	private:
		//made public so user can compare
		const value defVal;	
		//Total size of Trie
		int N = 0; 
	public:
		//default value when initialize TrieNode example int(0) or bool(false)
		struct TrieNode{
			string c;
			value val;
			TrieNode *mid, *left, *right;
			TrieNode(
				string key,
				value Value,
				TrieNode * midNode  = nullptr,
				TrieNode * leftNode = nullptr,
				TrieNode * rightNode = nullptr
				):
			c(key),
			val(Value),
			mid(midNode),
			left(leftNode),
			right(rightNode){}
		};
	private:
		//Root of TST
		TrieNode * root = nullptr;
		TrieNode * get(TrieNode * x,string & key,int d)const;
		TrieNode * put(TrieNode  * x, string & s, value val,int d);
		TrieNode * compress(TrieNode * x);
	public:
		//Due to Language it is required that the default/Null value is set i.e int(0) or bool(false)
		Trie(value defaultValue):defVal(defaultValue){}
		//return number of key-value pairs
		int size()const;
		//return default value set by user
		value getDefaultValue()const;
		//Check if returned value is not equal to default value
		bool contains(const string key)const;
		//Return Value
		value get(string key)const;
		//Insert String into symbol Table
		void put(string s,value val);
		//Find and return longest prefix of s in TST
		string longestPrefix(string s) const;
		//compress the table making it immutable returning the number of nodes removed
		int compress();

};

}}}}

//The compiler may not complain initialliy however
//Templates cause visibility issues with user code and is normally defined in the header
//this is a work around 
#include "Trie.cpp"

#endif
