#include <iostream>
#include <fstream>
#include <iomanip>//setw
#include "Trie.hpp"
#include <termios.h>
#include <vector>
using namespace std;
using com::wordgame::utility::trie::Trie;

char getche(void);

int main(int argc , char * argv[]){
	if(argc != 2){
		cout <<"Usage: "<<argv[0]<<" File_Of_Words"<<endl;
	}

	Trie<int> trie(0);
	vector<string> vec;
	string str;
	//LOAD Trie Table
	std::ifstream file(argv[1]);
	while(!file.eof())
	{
		file >> str;
		trie.put(str,str.length());
		vec.push_back(str);
	}
	file.close();
	cout << "Total Number of Nodes Before Compression: " << trie.size() << endl;
	//if(trie.size()!=99451){cout << "Initial Size Incorrect" << endl;return 1;}
	cout << "Total Nodes Removed: " << trie.compress() << endl;
	cout << "Total Number of Nodes After Compression: " << trie.size() << endl;

	cout << "[I] for interactive mode, anything else for Debug Mode" << endl;
	str = getche();cout << endl;
	//DebugMode
	if(tolower(str[0])!='i'){
		int size = (int)vec.size();
		int mod = size * 10/100;
		int p = -10;
		cout << "Processing " << size << " word/s ";
		for(int i=0;i < size;i++){
			str = vec[i];
			if(!trie.contains(str)){
				cout << "X\nTrie Tree Could Not Find " << str  << endl;
				exit(EXIT_FAILURE);	
			}
			if(i%mod==0){
				p+=10;
				cout << '=';
			}
		}
		cout << "> Processing Completed" << endl;
	}else
		//Interactive User 
		do{
			cout << "\n\nPlease Enter A Word : (Q)uit" << endl;
			str = "";
			cout << '[';
			for(int i = 0;(str+=getche())[i]!='\n';i++){//while the character is not string
				if(str[0] == 'Q'){
					cout <<  "uitting...]" << endl;
					goto QUIT;
				}else if(!isalpha(str[i])){
					cout << "\n[Quitting...]" << endl;
					goto QUIT;
				}
				if(!str.empty() && trie.contains(str)){
					cout << "] is contained within the Trie-Table" << endl;
					cout << '[' << str;
				}else{
					string lp = trie.longestPrefix(str);
					if(!lp.empty()){
						cout << "] current closest match is " << lp << endl;					
						cout << '[' << str;
					}
				}	

			}
			cout << endl << endl;
			str.pop_back();//remove newline character
			if(!trie.contains(str)) ::printf("[%s] is not contained within the Trie-Table\n\n",str.c_str());	
			//check for validity
			cout << "Linux System Command:\n";
			string command = "grep \"^" + str + "$\" " + argv[1];
			std::system(command.c_str());
			cout << "-------------------------" <<endl;
			//This Helps Flush input stream before next use
			cin.clear();
			fflush(stdin);
		}while(true);
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
