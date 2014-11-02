#include <iostream>
#include <string.h>
#include "../LZW.hpp"
#include <sstream>
#include <algorithm>
using namespace std;

int main(int argc , char * argv[]){
	if(argc != 2){
		cout <<"Usage: "<<argv[0]<<" File_Of_Words"<<endl;
		exit(EXIT_FAILURE);
	}
	string str;
	Trie<string> trie(""),trie2(""),trie3("");
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
	   stringstream ss1; ss1<<trie;
	   std::cout << "At1 ss1\t" <<ss1.rdbuf()->str() << std::endl;	
	   stringstream ss2; compressLZW(ss1,ss2);
	   std::cout << "At2 ss2\t" <<ss2.rdbuf()->str() << std::endl;	
	   stringstream ss3; decompressLZW(ss2,ss3);
	   std::string s1 = ss1.rdbuf()->str();
	   std::string s3 = ss3.rdbuf()->str();
	   std::cout << "At3 ss1\t" <<ss1.rdbuf()->str() << std::endl;	
	   std::cout << "At3 ss3\t" <<ss3.rdbuf()->str() << std::endl;	
	   std::cout << s1.length() << " : " <<s3.length() << "\tequals \n" <<boolalpha<< (s1.compare(s3)) << std::endl;	

	   printf(" HEX-1 | HEX-2 | CHAR-1 | CHAR-2 | Equals || ss3 AT \\0 \n");
	   printf("---------------------------------------------");
	   for(int i=0;i<(int)s1.length();i++){
	   printf("\n %-5x | %-5x | %-6c | %-6c | %-6s ||",s1[i],s3[i],s1[i],s3[i],(s1[i]==s3[i])?"true":"false");
	   if(s3[i]=='\0'){
	   cout << "true";
	   }
	   printf("\n---------------------------------------------");
	   }
	   cout << endl;
	   ss3>>trie2;
	   cout << "\nTrieTrees are identical " << boolalpha<<(trie==trie2)<<endl;	
	   exit(EXIT_FAILURE);	
	   */	
	//Test trie tree serialziation
	//cout << "Testing TreTree serialization\n";
	//stringstream ss;ss<<trie;ss>>trie2;cout << "TrieTrees are identical " << boolalpha<<(trie==trie2)<<endl;	
	//Testing lzw compression decompression
	//cout << "\nTesting LZW Compression Decompression\n";
	//stringstream ss1("TOBEORNOTTOBEORTOBEORNOT\0");
	stringstream ss1;ss1<<trie;
	stringstream ss2;compressLZW(ss1,ss2);
	stringstream ss3;decompressLZW(ss2,ss3);
	cout << "Original:    "<< ss1.str()  << "\nUncompressed:" << ss3.str() << "\nCompressed:" << ss2.str() << endl;
	cout << "Stream Are Identical: " << boolalpha << (ss1.str().compare(ss3.str())==0) << endl;
	cout << "Original Size: " << ss1.str().length() << endl;
	cout << "Compressed Size: " << ss2.str().length() << endl;
	cout << "Uncompressed Size: " << ss3.str().length() << endl;
	exit(EXIT_FAILURE);
	//Testing Serialization and compression of Trie
	cout << "\nSerialziation and compression of Trie\n";
	//cout << trie.details() << endl;
	//cout << "Total Number of Nodes in Trie Tree Removed:            " << trie.compress() << endl << endl;
	//cout << trie.details() << endl;
	cout << "Begining object compression...";
	compressLZW(trie,"test/origTrie.dat");
	/*cout << "Compression Complete."<<endl;
	  cout << "Begining object decompression...";
	  */decompressLZW("test/origTrie.dat",trie3);
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
