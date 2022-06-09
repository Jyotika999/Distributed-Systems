#include<bits/stdc++.h>
using namespace std;
using namespace std::chrono;

// creating a matrix of 1024*1024 dimensions
long long int  matrix1[1024][1024];
long long int matrix2[1024][1024];

    // for matrix multiplication of matrix1 and matrix2 , stored in product 
    // rows in matrix1 = r1 = 1024
    // cols in matrix1 = c1 = 1024
    // rows in matrix2 = r2 = 1024
    // cols in matrix2 = c2 = 1024

    // dimensions of final product matrix should be [r1 * c2]
    // hence the product matrix is of size 1024*1024

long long int product[1024][1024];
long long int num_threads=128;
long long int size = 1024;

void * matrix_sum( void *arg )
{

  
 long long int tid = *(long long int *)(arg); // get the thread ID assigned sequentially.
 long long int portion_size = size / num_threads;
 long long int row_start = tid * portion_size;
 long long int row_end = (tid+1) * portion_size;

  for (long long int i = row_start; i < row_end; ++i)
  { // i represents the row index of matrix 1 

    for (long long int j = 0; j <    1024; ++j)
    { // j represents the column index of matrix 2 
     
        // sums the multiplcation of the cells in row of matrix1 and column of matrix 2
      for (long long int k = 0; k < 1024; ++k)
       { 
	         product[i][j] += matrix1[ i ][ k ] * matrix2[ k ][ j ];
       }
    }
  }
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
 

	auto start = chrono::high_resolution_clock::now();


      pthread_t * threads;
    
      threads = (pthread_t *) malloc( num_threads * sizeof(pthread_t) );

  
    // initialising the matrix of dimensions 1024*1024 with random values between 0 to  10
    for(long long int i=0; i<1024;i++)
    {
        for(long long int j=0;j<1024;j++)
        {
            matrix1[i][j] = rand()%11;  // taking modulo with 11 so that all numbers are between 0 to 10
            matrix2[i][j] = rand()%11;
        }
    }

    // initialising the product matrix with 0 , to exclude the garbage values if any
    for(long long int i=0;i<1024;i++)
    {
        for(long long int j=0;j<1024;j++)
        {
            product[i][j]=0;
        }
    }

    for (long long int i = 0; i < num_threads; ++i ) 
    {
        long long int *thread_id;
        thread_id = (long long int *) malloc( sizeof(long long int) );
        *thread_id = i;
        pthread_create( &threads[i], NULL, matrix_sum, (void *)thread_id );
   }

  for (long long int  i = 0; i < num_threads; ++i ) {
    pthread_join( threads[i], NULL );
  }

  

    // matrix multiplication of matrix1 and matrix2 
    // rows in matrix1 = r1 = 1024
    // cols in matrix1 = c1 = 1024
    // rows in matrix2 = r2 = 1024
    // cols in matrix2 = c2 = 1024

    // dimensions of final product matrix should be [r1 * c2]
    // hence the product matrix is of size 1024*1024


    // printing the final result
    cout<<"FINAL PRODUCT MATRIX IS \n";

    for(long long int i=0;i<1024;i++)
    {
        for(long long int j=0;j<1024;j++)
        {
            cout<<product[i][j]<<" ";
        }
        cout<<"\n";
    }

  
	auto end = chrono::high_resolution_clock::now();

	double time_taken =  chrono::duration_cast<chrono::nanoseconds>(end - start).count();
  
    time_taken *= 1e-9;
  

    cout<<  "TOTAL TIME TAKEN BY PARALLELISATION BY PTHREADS PROGRAM TO RUN IS "<< fixed  << time_taken << setprecision(9);
    cout << " sec" << endl;

}