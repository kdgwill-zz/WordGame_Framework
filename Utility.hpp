/******************************************************************************
 * **  Utility classes
 * **  --------------------------------------------------------------------------
 * **  
 * ** short set of miscellaneous code that can be usefull 
 * ** 
 * **  Author: Kyle D. Williams
 * ******************************************************************************/
#ifndef COM_WORDGAME_UTILITY_UTILITY_HPP_KDGWILL
#define COM_WORDGAME_UTILITY_UTILITY_HPP_KDGWILL
#include <vector>
namespace CharUtility{
	void quickSort(char * word,int num);	
	void simpleQuickSort(char * word,int num);	
	void mergeSort(char * word,int num);
	void bestShuffle(char * word,int num);
	void knuthShuffle(char * word,int num);
}
#include "Utility.ii"
#endif
