#include <iostream>
#include <string.h>
#include "LZW.hpp"
#include <sstream>
#include <algorithm>
using namespace std;

int main(int argc , char * argv[]){
	if(argc != 2){
		cout <<"Usage: "<<argv[0]<<" File_Of_Words"<<endl;
		exit(EXIT_FAILURE);
	}
	string str;
	Trie<string> trie(""),trie2("");
	vector<string> vec, vec_2;
	
	//LOAD Trie Table
	std::ifstream file(argv[1]);
	std::locale loc("");
	file.imbue(loc);
	while(file >> str){
		trie.put(str,str);
		vec.push_back(str);
	}
	file.close();
	/*
	stringstream ss;ss<<trie;ss>>trie2;cout << "TrieTrees are identical " << boolalpha<<(trie==trie2)<<endl;	
	stringstream ss1("BLACKBLACKBLACKBLACKBLACKBLACKBLACKBLACKBLACKBLACKBLACKBLACK\t\n\0");
	stringstream ss2;
	compressLZW(ss1,ss2);
	stringstream ss3;
	decompressLZW(ss2,ss3);
	cout << "Original:"<< ss1.str() << "\nCompressed:"<<ss2.str();
	cout << "\nUncompressed:" << ss3.str();
	cout << "Are Identical: " << boolalpha << (ss1.str().compare(ss3.str())==0) << endl;
	cout << "Original Size: " << ss1.str().length() << endl;
	cout << "Compressed Size: " << ss2.str().length() << endl;
	cout << "Uncompressed Size: " << ss3.str().length() << endl;
	exit(EXIT_FAILURE);
	
	cout << trie.details() << endl;
	cout << "Total Number of Nodes in Trie Tree Removed:            " << trie.compress() << endl << endl;
	cout << trie.details() << endl;
	cout << "Begining object compression...";
	*/compressLZW(trie,"test/origTrie.dat");
	/*cout << "Compression Complete."<<endl;
	cout << "Begining object decompression...";
	*/decompressLZW("test/origTrie.dat",trie2);
	/*cout << "Deompression Complete."<<endl;
	cout << "Restored Trie"<<endl;
	cout << trie2.details();
	*/exit(EXIT_FAILURE);


	//DebugMode
	cout << endl << "DEBUG MODE SELECTED" << endl << endl;
	vec_2 = trie2.keys();

	int size = (int)vec.size();
	int size_2 = (int)vec_2.size();
	cout << "Processing " << size << " word/s ";
	if(size!=size_2){
		cout << " X\nTrie Tree has more or contains missing keys\n" << endl;
		printf("Supposed/Actual = [%d/%d]\n",size,size_2);
		exit(EXIT_FAILURE);	
	}

	std::sort(vec.begin(),vec.end());	
	std::sort(vec_2.begin(),vec_2.end());	
	int mod = size * 10/100;
	for(int i=0;i < size;i++){
		string s = trie2.get(vec_2[i]);
		if(s.compare(vec[i])!=0){
			printf(" X\nTrie Tree Contains Unqualified Value at Position");
			printf("[%d] FileValue=[%s]: TrieTree Key/Value=[%s/%s]:\n"
					,i, vec[i].c_str(),   vec_2[i].c_str(),s.c_str());
			exit(EXIT_FAILURE);	
		}
		if(i%mod==0){
			cout << '=';
		}
	}
	cout << "> Processing Completed" << endl;
	return 0;
}
