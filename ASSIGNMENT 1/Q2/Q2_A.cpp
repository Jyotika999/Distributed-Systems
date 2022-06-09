#include<bits/stdc++.h>
using namespace std;
using namespace std::chrono;

int arr[4096];
int prefix_sum[4096];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    // initialising the original array and the prefix array as 0 , to avoid garbage values getting stored 
    memset(arr, 0, sizeof(arr));
    memset(prefix_sum, 0 , sizeof(prefix_sum));

    // randomly filling all the array elements using random function
    // taking modulo with 11 , so that the range of elements in array is between 0 to 10
    for(int i=0;i<4096;i++)
    {
        arr[i] = rand()%11;
    }

    // start time 
    auto start = chrono::high_resolution_clock::now();

    // sequentially calculating the prefix sum 
    // here prefix sum[i] storres the sum of 0...i elements of array 

    for(int i=1;i<4096;i++)
    {
        if(i==0)
        {
            prefix_sum[i] = arr[i];
        }
        else
        {
               prefix_sum[i] = prefix_sum[i-1] + arr[i];
        }
    }




    // printing the prefix sum of the array containing 4096 elements
    for(int i=0;i<4096;i++)
    {
        cout<<prefix_sum[i]<<"\n";
    }
  
        // end time 
    auto end = chrono::high_resolution_clock::now();
    // calculating the total time taken to compute prefix sum sequentially 
	double time_taken =  chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    time_taken *= 1e-9;
  

    cout<<  "TOTAL TIME TAKEN BY SEQUENTIAL PROGRAM TO RUN IS "<< fixed  << time_taken << setprecision(15);
    cout << " sec" << endl;




}