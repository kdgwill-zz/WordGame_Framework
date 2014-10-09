#include <iostream>
#include <string.h>
#include "LZW.hpp"
#include <sstream>
using namespace std;

int main(){
/**	if(argc != 2){
		printf("Usage: %s FILE_TO_BE_COMPRESSED\n",argv[0]);
		exit(EXIT_FAILURE);
	}
	char* s1 =  argv[1];
        const int i = sizeof(s1)+5;
	char s2[i];
        strcat(s2,s1);
        strcat(s2,".LZW");
	*/
        //compression
	//char s3[] = "TOBEORNOTTOBEORTOBEORNOT";
	//char s3[] = "TOBEORNOTTOBEORTOBEORNOT";
	//char s3[] = "zß水𝄋 is 10 bytes, but only 4 characters";
	/*char s3[] = u8"TOBEORNOTTOBEORTOBEORNOT\u00df\u6c34\U0001d10b";

	printf("Encoding Message:[%s]\n",s3);
	auto e = encode(s3);
        
	for(auto j : e){
		cout << j << ", ";
	}
	cout << endl;
	//decompression
        auto s4 = decode(e);
	cout << "DeCoded Message: " << s4 << endl;
	*/
/*
	std::stringstream ssi;
	std::stringstream sso;
	std::stringstream ss;
	ssi<<"TOBEORNOTTOBEORTOBEORNOT";
	cout << "ORIGINAL: " << ssi.str() << endl;
	encode(ssi,sso);
	cout << "ENCODED : "<<sso.str() << endl;
	decode(sso,ss);
	cout << "DECODED : " << ss.str() << endl;
*/
	//printf("Encoded Message:  %s\n",s4.arr);
	//printf("LZW Compression | Decompression %s\n", strcmp(s4.arr,s3)==0?"Success":"Failure");
	//exit(EXIT_FAILURE);
        compress("test/test.dat","test/compressedTest.dat");
        decompress("test/compressedTest.dat","test/test2.dat"); 
	std::string command;
	command += "cmp --silent ";
	command += "test/test.dat ";
	command += "test/test2.dat ";
	command += "|| echo \"Files Are Different\"";
	command += "&& du test/test.dat test/test2.dat test/compressedTest.dat\n";
	std::system(command.c_str());
}
