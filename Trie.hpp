/******************************************************************************
 * **  Trie Tree
 * **  --------------------------------------------------------------------------
 * **  
 * **  Stores strings using Trie Trees.
 * **  
 * **  std::string is used to set and get key values however std::wstring 
 * **  is used internally to provide accuracy and to prevent creation of 
 * **  additional nodes great care is taken to prevent miscalculations 
 * **  when converting between the two
 * **
 * **
 * **  Author: Kyle D. Williams
 * **
 * ******************************************************************************/
#ifndef COM_WORDGAME_UTILITY_TRIE_HPP_KDGWILL
#define COM_WORDGAME_UTILITY_TRIE_HPP_KDGWILL
#include <string>
#include <vector>
#include <stdexcept>

template<typename value>
class Trie{
	private:
		//made public so user can compare
		const value defVal;	
		//Number of words in Tree
		size_t wordCount = 0; 
		//Number of Nodes in Tree
		size_t nodeCount = 0;
	public:
		//default value when initialize TrieNode example int(0) or bool(false)
		struct TrieNode{
			std::string key;
			value val;
			TrieNode *mid, *left, *right;
			TrieNode(
					std::string Key,
					value Value,
					TrieNode * midNode  = nullptr,
					TrieNode * leftNode = nullptr,
					TrieNode * rightNode = nullptr
				):
				key(Key),
				val(Value),
				mid(midNode),
				left(leftNode),
				right(rightNode){}
		};
	private:
		TrieNode * root = nullptr;
		TrieNode * get(TrieNode * x,const std::string & key,size_t d,const bool & ignoreCase=false)const;
		TrieNode * put(TrieNode * x,const std::string & key,const value & val,size_t d);
		void collect(TrieNode * x, std::string prefix, std::vector<std::string> & vec)const;
		//This is specifically for PrefixMatch and should not be used outside of method
		TrieNode * getPrefixNode(TrieNode * x,std::string key,std::string prefix,size_t d,const bool & ignoreCase=false)const;
		TrieNode * compress(TrieNode * x);
		//HELPER FUNCTIONS
		void __toLowerCase(std::string & s) const;
		size_t __lcp(size_t d,const std::string & s1,const std::string & s2) const;
		void cleanUp(TrieNode * X);
	public:
		//Due to Language it is required that the default/Null value is set i.e int(0) or bool(false)
		Trie(value defaultValue);
		//Cleans up Trie Node
		~Trie();
		//return number of key-value pairs
		size_t size()const;
		//return number of nodes int the tree for debugging purposes
		size_t num()const;
		//return default value set by user
		value getDefaultValue()const;
		//Check if returned value is not equal to default value
		bool contains(std::string key,const bool & ignoreCase=false)const;
		//Return Value
		value get(std::string key, const bool & ignoreCase = false)const;
		//Insert String into symbol Table
		void put(std::string key,const value & val);
		//Find and return longest prefix of s in TST
		std::string longestPrefix(std::string prefix,const bool & ignoreCase = false) const;
		//return all words contained in the tree
		std::vector<std::string> keys();
		//return all keys starting with a given prefix
		std::vector<std::string> prefixMatch(std::string prefix,const bool & ignoreCase = false);
		//compress the table making it immutable returning the number of nodes removed
		size_t compress();
};

//Take not this is added inside the header gaurd
//This is the proper way to include template definition files 
#include "Trie.ii"

#endif
