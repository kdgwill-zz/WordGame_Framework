#include <iostream>
#include <cstdlib>  // srand, rand 
#include <ctime>    // time 
#include <limits>   // For numeric_limits

using namespace std;

int main (){
	int secret, numGuessed;

	/* initialize random seed: */
	srand (time(NULL));

	/* generate secret number between 1 and 10: */
	secret = rand() % 10 + 1;

	do {
		cout << "Guess the number [1 - 10]: " << endl;
		cin >>  numGuessed;
		if(!cin){
			cout << "Please Input valid number numbers" << endl;
		}else{
			if (secret < numGuessed) 
				cout << "The secret number is lower!" << endl;
			else if (secret > numGuessed) 
				cout << "The secret number is higher!" << endl;
		}
		// Clear the error state
		std::cin.clear();
		// Remove the unrecognized characters
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	} while (secret != numGuessed);

	cout << "Congratulations!" << endl;

	return 0;
}
