#include<bits/stdc++.h>
using namespace std;
using namespace std::chrono;

int arr[4096];
int thread_total=128;
int cur_thread=0;
int prefix_sum[128];

// inorder to synchromise the sums that are calculated locally by the threads
pthread_barrier_t barr;

void* sum_calculation_using_threads(void* arg)
{
	int thread_part = cur_thread++;
	int start = thread_part * (4096 / thread_total);
	int end = (thread_part+1) * (4096 / thread_total);
	
	//Prefix Sum of the Present Subarray
	for (int i = start+1; i < end; i++)
		arr[i]+=arr[i-1];
	
	prefix_sum[thread_part] = arr[end-1];
	
	//Barrier is required to synchronize the prefix sum of all subarray
	pthread_barrier_wait(&barr);
	
	// Up Sweep
    int pow1 = 1,pow2;
	int index=0,mid=0;
	int d = log2(thread_total);

    int i=0;
	while(i<d)
	{
		pow2 = 2*pow1;
		if( i == d-1)
			prefix_sum[thread_total-1]=0;
		else
		{
			if(thread_part%pow2 == 0)
			{
				mid = thread_part-1;
				index = mid+pow2;
				prefix_sum[index] = prefix_sum[mid+pow1]+prefix_sum[index];
			}
		}
		pthread_barrier_wait(&barr);
		pow1=pow2;
        i++;
	}
	
	// Down Sweep 
	int idx1,idx2,temp;
	pow2 = pow(2, d);
    i=d-1;
	while(i>=0)
	{
		pow1 = pow2/2;
		if(thread_part%pow2 ==0)
		{
			mid = thread_part-1;
			idx2 = pow1+mid;
			idx1 = pow2+mid;
			temp = prefix_sum[idx2];
			prefix_sum[idx2] = prefix_sum[idx1];
			prefix_sum[idx1] += temp;
		}
		pthread_barrier_wait(&barr);
		pow2 = pow1;
        i--;
	}
	
	for(int i=start;i<end;i++)
		arr[i]+= prefix_sum[thread_part];
	
	return NULL;
}

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

    //  calculating the prefix sum using pthreads
    // here prefix sum[i] storres the sum of 0...i elements of array 
  
    if(pthread_barrier_init(&barr, NULL, thread_total))
	{
		return 0;
	}
	
	pthread_t threads[thread_total];
	
    // creating threads and then allocating each thread to their respective subarrays for calculating their sums
	for(int i=0;i<thread_total;i++)
		pthread_create(&threads[i],NULL, sum_calculation_using_threads,(void *)NULL);
		
    // joining all the threads together
	for (int i=0; i<thread_total; i++)
		pthread_join(threads[i], NULL);



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
  

    cout<<  "TOTAL TIME TAKEN BY PARALLELIZATION PROGRAM BY PTHREADS TO RUN IS "<< fixed  << time_taken << setprecision(15);
    cout << " sec" << endl;


}


// 