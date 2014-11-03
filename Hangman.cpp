#include <iostream>
#include <fstream>
#include "Trie.hpp"
#include <limits>   // For numeric_limits
#include <memory>
using namespace std;

int main(int argc , char * argv[]){
	if(argc != 2){
		cout <<"Usage: "<<argv[0]<<" File_Of_Words"<<endl;
		exit(EXIT_FAILURE);
	}

	string str;
	Trie<string> trie("");
	//LOAD Trie Table
	std::ifstream file(argv[1]);
	std::locale loc("");
	file.imbue(loc);
	while(file >> str){
		trie.put(str,str);
	}
	file.close();

	vector<string> vec;

	//Typical words lengths range from 3 to 8

	/* initialize random seed: */
	srand (time(0));

	/* generate secret number between 1 and 10: */
	int length = rand() % (15-4) + 4;//4-15
	string wild(length,'.');
	vector<string> words = trie.wildCardMatch(wild);
	int num = rand() % words.size();
	string word = words[num];
	char c;
	int guessLeft = length+1;
	//preprocessing does not seem advantageous  

	while(1){
		cout << "Guess The Word\t" << wild << endl;
		cin >>  c;
		if(!cin){
			cout << "Please Input valid letter" << endl;
		}else if (word.find(c)!=string::npos){ 
			cout << c << " matches!" << endl;
			for(int i =0; i < (int)word.length(); i++){
				if(c==word[i]){
					wild[i]=c;
					guessLeft--;
				}
			}
			guessLeft++;	
		}else{ 
			cout << "No matching letters!" << endl;
			guessLeft--;
		}
		// Clear the error state
		std::cin.clear();
		// Remove the unrecognized characters
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		if(wild.compare(word)==0){
			cout << "Congratulations, you matched " << wild << endl;
			break;
		}else if(guessLeft == 0){
			cout << "Congratulations, YOU LOSE!\nThe word was " << word << endl;
			break;
		}else{
			cout << guessLeft << " guessess left." << endl;
		}

	}

	return 0;
}
