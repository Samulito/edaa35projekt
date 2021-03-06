#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
using namespace std;
using namespace std::chrono;

// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
 
    /* create temp arrays */
    int L[n1], R[n2];
 
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
 
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}
 
/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l+(r-l)/2;
 
        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
 
        merge(arr, l, m, r);
    }
}


int main(){
    vector<int> numbers;
    ifstream in("data1.txt",ios::in);

    int number;
    
    while (in >> number) {
        numbers.push_back(number);
    }

    in.close();


    // skapar en utfil
    ofstream myfile;
    myfile.open ("mergeMain.txt");
	myfile << "itr," << " time in nanosec \n";
    
    for(int i = 0; i < 600; i++){

	vector<int> nbrcopy = numbers;	

        high_resolution_clock::time_point t1 = high_resolution_clock::now();
        
            mergeSort(&nbrcopy[0], 0, nbrcopy.size()-1);

        high_resolution_clock::time_point t2 = high_resolution_clock::now();

        auto duration = duration_cast<nanoseconds>( t2 - t1 ).count();


        // skriver till utfilen
        myfile << (i+1) << ", " << duration << "\n";
    }
    
    //stänger utfilen
    myfile.close();
    return 0;
}
