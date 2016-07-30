//--------------------------------------------------------------------------
// Question Description:
// Download the following text file:
// IntegerArray.txt
// This file contains all of the 100,000 integers between 1 and 100,000 (inclusive) in some order,
// with no integer repeated.
// Your task is to compute the number of inversions in the file given, 
// where the ith row of the file indicates the ith entry of an array.
// Because of the large size of this array,
// you should implement the fast divide-and-conquer algorithm covered in the video lectures.
// The numeric answer for the given input file should be typed in the space below.
//-----------------------------------------------------------------------
// Author: MiracleZhang 
// Date:  07/13/16
// the right answer for my IntegerArray.txt is 2407905288
//-----------------------------------------------------------------------
// Attentionremember the boundary condition of the merge sort
// Because the ans is too large, we need to use unsigned int to store it
//-----------------------------------------------------------------------

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

unsigned int sort(vector<int>&, int, int);
unsigned int merge(vector<int>&, int, int, int);

int main ()
{
	/* copy the file to inversion vector */  
    vector<int> vec;  
    ifstream infile;  
    infile.open("IntegerArray.txt", ios::in);  
    int temp;  
    unsigned int cnt = 0;  
    while (infile >> temp) {  
        vec.push_back(temp);  
    }  
    infile.close();  
    // my simple test for 
    // vector<int> test1;
    // test1.push_back(6);
    // test1.push_back(5);
    // test1.push_back(4);
    // test1.push_back(3);
    // test1.push_back(2);
    // test1.push_back(1);
    // for (int i = 0; i < test1.size(); ++i)
    //     cout<<test1[i]<<endl;
    //cnt = sort(test1, 0, test1.size()-1);  
    cnt = sort(vec, 0, vec.size()-1);  
    cout << "# number of inversions of the numbers in the file: " << cnt << endl; 
    // cout<<(cnt>1)<<endl;
    // for (int i = 0; i < test1.size(); ++i)
    //     cout<<test1[i]<<endl;
  
    return 0;
}

unsigned int sort(vector<int>& vec, int low, int high)
{
	if (high == low)
		return 0;
	int mid = (high + low) /2 ;
	return sort(vec, low, mid)+sort(vec, mid+1, high)+merge(vec, low, mid+1, high);
}

unsigned int merge(vector<int>& vec, int low, int mid, int high)
{
	unsigned int cnt = 0;  
    int i = low;  
    int j = mid;  
    vector<int> aux(vec);
    int k = low;
    
    // if go through either of the number groups, stop,
    // 
    while (i<mid or j<=high)
    {
        if (i==mid)
            vec[k] = aux[j++];
        else if (j>high)
            vec[k] = aux[i++];
        else if (aux[i] <= aux[j])  
            vec[k] = aux[i++];
        else 
        {
            cnt += (mid-i);
            vec[k] = aux[j++]; 
        }
        k++;
    } 
    return cnt; 
}