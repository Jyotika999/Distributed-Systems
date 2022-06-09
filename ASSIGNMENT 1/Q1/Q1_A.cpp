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


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
 
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
    for(int i=0;i<1024;i++)
    {
        for(int j=0;j<1024;j++)
        {
            product[i][j]=0;
        }
    }


    // matrix multiplication of matrix1 and matrix2 
    // rows in matrix1 = r1 = 1024
    // cols in matrix1 = c1 = 1024
    // rows in matrix2 = r2 = 1024
    // cols in matrix2 = c2 = 1024

    // dimensions of final product matrix should be [r1 * c2]
    // hence the product matrix is of size 1024*1024

    auto start = chrono::high_resolution_clock::now();
    for(long long int i=0;i<1024;i++)
    {
        for(long long int j=0;j<1024;j++)
        {
            for(long long int k=0;k<1024;k++)
            {
                product[i][j] +=  matrix1[i][k]* matrix2[k][j];
            }
        }
    }
    auto end = chrono::high_resolution_clock::now();
  

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

  


	double time_taken =  chrono::duration_cast<chrono::nanoseconds>(end - start).count();
  
    time_taken *= 1e-9;

    cout<<  "TOTAL TIME TAKEN BY SEQUENTIAL PROGRAM TO RUN IS "<< fixed  << time_taken << setprecision(9);
    cout << " sec" << endl;

}

