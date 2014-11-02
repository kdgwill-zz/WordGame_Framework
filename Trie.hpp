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
 * **	A Possible upgrade to this tree would be to store words originally as strings
 * **   and splitting them when substrings of those strings are added
 * **   
 * **	Currently a compress method is given allowing the user to manually compress the
 * **   tree tansforming the Trie into a partial string/char trie this requires additional
 * **   complexity in all functions.
 * **
 * **  Author: Kyle D. Williams
 * **
 * ******************************************************************************/
#ifndef COM_WORDGAME_UTILITY_TRIE_HPP_KDGWILL
#define COM_WORDGAME_UTILITY_TRIE_HPP_KDGWILL
#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <sstream>//specifically for serialization

template<typename value>
class Trie{
	private:
		//made public so user can compare
		const value defVal;	
		//Number of words in Tree
		size_t wordCount = 0; 
		//Number of Nodes in Tree
		size_t nodeCount = 0;
		//Ratio of Trie Compression
		float ratio = 0;
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
		std::vector<std::string> keys() const;
		//return all keys starting with a given prefix
		std::vector<std::string> prefixMatch(std::string prefix,const bool & ignoreCase = false) const;
		//compress the table making it immutable returning the number of nodes removed
		size_t compress();
		//Write formated Trie to Output Stream
		//For write to work a values operator<< must be overloaded correctly
		std::ostream & write( std::ostream & dst)const;
		//Read formated Trie from Input Stream
		//For read to work a values operator>> must be overloaded correctly
		std::istream & read( std::istream  & src);
		//Compare Trie trees
		bool equals(const Trie &other_trie)const;
		//return details about the trie tree
		std::string details();
		//FRIENDS DON"T PLAY NICE TO TEMPLATE MUST DECLARE IN DEFINITION TO AVOID UGLY CODE
		//Serialize Trie To Stream
		friend std::ostream & operator<<( std::ostream & dst, const Trie<value> &T ){return T.write(dst);}
		//Deserialize Trie From Stream
		friend std::istream & operator>>( std::istream  & src, Trie<value> &T ){return T.read(src);}
		//Comparison Operator
		friend bool operator== (const Trie &trie1, const Trie &trie2){return trie1.equals(trie2);}
		//Negated Comparison Operator
		friend bool operator!= (const Trie &trie1, const Trie &trie2){return !trie1.equals(trie2);}
};

//Take not this is added inside the header gaurd
//This is the proper way to include template definition files 
#include "Trie.ii"
#endif
