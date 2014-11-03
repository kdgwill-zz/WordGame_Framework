#include <iostream>
#include <locale>
#include <fstream>
#include <sstream>
#include <iomanip>//setw
#include "../Trie.hpp"
#include <termios.h>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

char getch(void);
char getche(void);

int main(int argc , char * argv[]){
	if(argc != 2){
		cout <<"Usage: "<<argv[0]<<" File_Of_Words"<<endl;
		exit(EXIT_FAILURE);
	}

	string str;
	Trie<string> trie("");
	vector<string> vec, vec_2,vec_3;
	//LOAD Trie Table
	std::ifstream file(argv[1]);
	std::locale loc("");
	file.imbue(loc);
	while(file >> str){
		trie.put(str,str);
		vec.push_back(str);
	}
	file.close();

	cout << "Total Number of Words:                                 " << vec.size() << endl;
	cout << "Total Number of Words in Trie Tree:                    " << trie.size() << endl;
	cout << "Total Number of Nodes in Trie Tree Before Compression: " << trie.num() << "\t words:" << trie.keys().size() << endl;
	cout << "Total Number of Nodes in Trie Tree Removed:            " << trie.compress() << endl;
	cout << "Total Number of Nodes in Trie Tree After Compression:  " << trie.num() << "\t words:" << trie.keys().size() << endl;
	cout << "[D] for Debug Mode, anything else for Interactive Mode " << endl;
	
	str = getche();cout << endl;
	//DebugMode
	if(tolower(str[0])==L'd'){
		cout << endl << "DEBUG MODE SELECTED" << endl << endl;
		vec_2 = trie.keys();
		
		int size = (int)vec.size();
		int size_2 = (int)vec_2.size();
		cout << "Processing " << size << " word/s ";
		if(size!=size_2){
			cout << " X\nTrie Tree has more or contains missing keys\n" << endl;
			printf("Supposed/Actual = [%d/%d]",size,size_2);
			exit(EXIT_FAILURE);	
		}

		std::sort(vec.begin(),vec.end());	
		std::sort(vec_2.begin(),vec_2.end());	
		int mod = size * 10/100;
		for(int i=0;i < size;i++){
			string s = trie.get(vec_2[i]);
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
	}else{
		//Interactive User 
		cout << endl << "INTERACTIVE MODE SELECTED" << endl << endl;
		do{
			cout << "\n\nPlease Enter A Word : (Q)uit" << endl;
			str = "";
			cout << '[';
			for(int i = 0;(str+=getche())[i]!='\n';i++){//while the character is not string
				//if(tolower(str[0]) == L'Q'){
				//	cout <<  "uitting...]" << endl;
				//	goto QUIT;
				//}else 
				if(!isprint(str[i])){
					cout << "\n[Quitting...]" << endl;
					goto QUIT;//HAHA yeah i used a goto in a test case
				}
				if(!str.empty() && trie.contains(str,true)){
					cout << "] is contained within the Trie-Table Value: " << trie.get(str)<< endl;
					cout << '[' << str;
				}else{
					string lp = trie.longestPrefix(str,true);
					vec_2 = trie.prefixMatch(str,true);
					vec_3 = trie.wildCardMatch(str,true);
					
					if(!lp.empty()){
						cout << "] current closest match is " << lp << endl;
						cout << "Future Matches Include: ";					
						for(int i = 0;i<(int)vec_2.size()&&i<5;i++){		
							cout << vec_2[i] << ", ";
						}
						cout << endl;
						cout << "WildCard Matches Include: ";					
						for(int i = 0;i<(int)vec_3.size()&&i<5;i++){		
							cout << vec_3[i] << ", ";
						}
						cout << endl;
						
						cout << '[' << str;
					}
					vec_2.clear();
				}	

			}
			cout << endl << endl;
			str.pop_back();//remove newline character
			if(!trie.contains(str,true)) ::printf("[%s] is not contained within the Trie-Table\n\n",str.c_str());	
			//check for validity
			cout << "Linux System Command:"<<endl;
			std::stringstream command;
			command << "grep -i \"^" << str.c_str() << "$\" " << argv[1];
			std::system(command.str().c_str());
			cout << "-------------------------" <<endl;
			//This Helps Flush input stream before next use
			cin.clear();
			fflush(stdin);
		}while(true);
	}
QUIT:
	return 0;
}



/****************************************************************************************************
 * TAKEN FROM http://stackoverflow.com/questions/7469139/what-is-equivalent-to-getch-getche-in-linux *
 ****************************************************************************************************/ 
static struct termios oldt, newt;

/* Initialize new terminal i/o settings */
void initTermios(int echo) 
{
	tcgetattr(0, &oldt); /* grab old terminal i/o settings */
	newt = oldt; /* make new settings same as old settings */
	newt.c_lflag &= ~ICANON; /* disable buffered i/o */
	newt.c_lflag &= echo ? ECHO : ~ECHO; /* set echo mode */
	tcsetattr(0, TCSANOW, &newt); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void) 
{
	tcsetattr(0, TCSANOW, &oldt);
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo) 
{
	char ch;
	initTermios(echo);
	ch = getchar();
	resetTermios();
	return ch;
}


char getch(void) 
{
	return getch_(0);
}

/* Read 1 character with echo */
char getche(void) 
{
	return getch_(1);
}
