//--------------------------------------------------------------------------
// Question Description:
// the following text file:
/*
Algorithms - design and analysis (Stanford), Part I.
Programming Question 2:
1) Task is to compute the total number of comparisons used to sort the given input file by QuickSort.
2) Compute the number of comparisons (as in Problem 1), always using the final element of 
the given array as the pivot element
3) Compute the number of comparisons (as in Problem 1), using the "median-of-three" pivot rule
@author: Alimbekov Renat
*/
//-----------------------------------------------------------------------
// Author: MiracleZhang 
// Date:  07/16/16
//----------------------------------------------------------------------
// the right answer for my QuickSort.txt is that:
// Task 1: 162085
// Task 2: 164123
// Task 3: 138382
//-----------------------------------------------------------------------
// Attentionremember the boundary condition of the quick sort
// And also the time to swap the elements 
//-----------------------------------------------------------------------


#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

enum Type{FIRST, LAST, MEDIAN};
int sort(vector<int>& a, int b, int c, const Type &t);  
int partition_first(vector<int>& a, int b, int c); 
int partition_last(vector<int>& a, int b, int c);
int partition_median(vector<int>& vec, int low, int high);
int getIndex(vector<int>& vec, int low, int high, int medium);

int main ()
{
	// set the data and make it 3 copies
	vector<int> num_first;
	ifstream infile;
	infile.open("QuickSort.txt", ios::in);  
    int tmp;  
    while (infile >> tmp)  
        num_first.push_back(tmp);  
    infile.close(); 
    vector<int> num_second (num_first);
    vector<int> num_third (num_first);

    // TASK 1
	int cnt_first = sort(num_first, 0, num_first.size()-1, FIRST);  
    cout << "# of comparisons in the Task 1: " << cnt_first << endl; 

    // TASK 2
    int cnt_last = sort(num_second, 0, num_second.size()-1, LAST);  
    cout << "# of comparisons in the Task 2: " << cnt_last << endl;  

    // TASK 3
    int cnt_median = sort(num_third, 0, num_third.size()-1, MEDIAN);  
    cout << "# of comparisons in the Task 3: " << cnt_median << endl; 

	return 0;
}

// qsort according to the Type
int sort(vector<int>& vec, int low, int high, const Type &t)
{
	if (high <= low)
		return 0;
	int pivot = 0;
	if (t == FIRST)
		pivot = partition_first(vec, low, high);
	if (t == LAST)
		pivot = partition_last(vec, low, high);
	if (t == MEDIAN)
		pivot = partition_median(vec, low, high);
	int first = sort(vec, low, pivot-1, t);
	int second = sort(vec, pivot+1, high, t);
	return first+second+(high-low);
}
//---------------------------------------------------------
//Qsort with the first partition as the privot
int partition_first(vector<int>& vec, int low, int high)
{
	int pivot = vec[low];
	int i = low +1;
	int j;
	for (j = low+1; j <= high; ++j)
	{
		if (vec[j]<pivot)
		{
			swap(vec[j], vec[i]);
			i++;
		}
	}
	swap(vec[low], vec[i-1]);  
	return (i-1);
}

//-------------------------------------------------------------
// Qsort with the last partition as the privot
int partition_last(vector<int>& vec, int low, int high) {  
  
    int pivot = vec[high];  
    swap(vec[low], vec[high]);  
    int i = low + 1;  
    int j;  
    for (j = low + 1; j <= high; ++j) {  
        if (vec[j] < pivot) {  
            swap(vec[i], vec[j]);  
            ++i;  
        }  
    }  
    swap (vec[i-1], vec[low]);  
    return (i-1);  
} 

//-----------------------------------------------------------
// Qsort with the medium partition as the privot
int partition_median(vector<int>& vec, int low, int high)
{
	int index = getIndex(vec, low, high, (low+high)/2);
	int pivot = vec[index];
	swap(vec[low], vec[index]);		// the swap step should be in that way 
	int i = low + 1;  
    int j;  
    for (j = low + 1; j <= high; ++j) {  
        if (vec[j] < pivot) {  
            swap(vec[i], vec[j]);  
            ++i;  
        }  
    }  
    swap (vec[i-1], vec[low]);  
    return (i-1);  
}

//-----------------------------------------------------------
// to get the medium between the three numbers
int getIndex(vector<int>& vec, int low, int high, int medium)
{
	if (vec[low]>vec[high])
	{
		if(vec[high]>vec[medium]) 
		{
			return high;
		}
		else 
		{
			if(vec[low]>vec[medium]) {
					return medium;
				}
				else {
					return low;
				}	
		}
	}
	else
	{
		if(vec[low]>vec[medium]) 
		{
			return low;
		}
		else 
		{
			if(vec[high]>vec[medium]) {
					return medium;
				}
				else {
					return high;
				}	
		}
	}
}