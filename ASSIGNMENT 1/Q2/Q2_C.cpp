#include<bits/stdc++.h>
#include <omp.h>
using namespace std;
using namespace std::chrono;

int arr[4096];
int prefsum[4096];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    // initialising the original array and the prefix array as 0 , to avoid garbage values getting stored 
    memset(arr, 0, sizeof(arr));
    memset(prefsum, 0 , sizeof(prefsum));

    // randomly filling all the array elements using random function
    // taking modulo with 11 , so that the range of elements in array is between 0 to 10
    for(int i=0;i<4096;i++)
    {
        arr[i] = rand()%11;
    }

    for(int i=0;i<4096;i++)
    {
        if(i==0)
        prefsum[i]=arr[i];
        else
        prefsum[i] = prefsum[i-1]+arr[i];
    }
    // start time 
    auto start = chrono::high_resolution_clock::now();

    // sequentially calculating the prefix sum 
    // here prefix sum[i] storres the sum of 0...i elements of array 

    // Algorithm used to parallelise :
    // we will be dividing the original array into sub arrays 
    // number of subarrays whose sum we need to find = number of threads used in processing the prefix sum
    // each thread will calculate the prefix sum for its assigned subarray
    // the prefix sums that are calculated above , will be less than the actual sums, since there would be elements which would have been ignored before the start of the particular subarray 
    // hence the last elements of all these subarrays are stored in another temporary array
    // and therefore prefix sum will be calculated for this subarray, incase some element was missed in calculation of prefix sum 

   
    int i=0;
    int last=0;
    int thread_total=128;
    int prefix_sum[thread_total]={0};
    int temp[thread_total]={0};
    int mynum=0;
    // int num_threads=0;
    int n = 4096;

	#pragma omp parallel num_threads(thread_total) private(i, mynum,last) shared(arr, prefix_sum, temp)
	{

		int mynum = omp_get_thread_num();
        // setting the size of the subarray segment length 
		int subarray_seg = 4096/thread_total;

        // each thread getting allocated to calculate the sum of its own segment array 
		for(i=(mynum*subarray_seg)+1;i<((mynum+1)*subarray_seg);i++)
			arr[i]+=arr[i-1];
		
		prefix_sum[mynum] = arr[i-1];
		
		#pragma omp barrier
		
            // the prefix sums that are calculated above , will be less than the actual sums, since there would be elements which would have been ignored before the start of the particular subarray 
            // hence the last elements of all these subarrays are stored in another temporary array
            // and therefore prefix sum will be calculated for this subarray, incase some element was missed in calculation of prefix sum 

            for(i=1;i<thread_total;i<<=1)
            {
                if(mynum>=i)
                {
                    temp[mynum] = prefix_sum[mynum] + prefix_sum[mynum - i];
                }
            
            
                #pragma omp barrier
                #pragma omp single
                    memcpy(prefix_sum+1, temp+1, sizeof(int) * (thread_total-1));
            }
            last = ((mynum+1)*subarray_seg);
            for(i=(mynum*subarray_seg);i<last;i++)
                arr[i] += (prefix_sum[mynum] - arr[last - 1]);
                
	}

    // printing the prefix sum of the array containing 4096 elements
   
    for(int i=0;i<4096;i++)
    {
        
        cout<<arr[i]<<"\n";
    }
  
        // end time 
    auto end = chrono::high_resolution_clock::now();
    // calculating the total time taken to compute prefix sum sequentially 
	double time_taken =  chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    time_taken *= 1e-9;
  

    cout<<  "TOTAL TIME TAKEN BY PARALLELISATION PROGRAM BY OPENMP TO RUN IS "<< fixed  << time_taken << setprecision(15);
    cout << " sec" << endl;




}