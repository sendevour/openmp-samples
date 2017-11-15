#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#include "main.h"
extern void PTUpdateEntry( int arr[MAXDIM][MAXDIM+1], int i, int j, int value  ) ;
int binomialCoeff(int n, int k)
{
    int res = 1, i = 0;
    if (k > n - k)
       k = n - k;
    for (i = 0; i < k; ++i)
    {
        res *= (n - i);
        res /= (i + 1);
    }
    return res;
}
void FillPascalTriangle( int arr[MAXDIM][MAXDIM+1] )
{

        int i, j ;
	int value = 0;
        #pragma omp parallel
        {
		#pragma omp for schedule(dynamic, 2)
		for( i = 0 ; i < MAXDIM ; i++ ){
			for( j = 0 ; j<=i  ; j++ ){
					#pragma omp task firstprivate(i,j) depend(out: value)
                                        value = binomialCoeff(i,j);
		
					#pragma omp task firstprivate(i,j) depend(in: value)
                                        PTUpdateEntry( arr, i, j, value) ;
                        }
		}
        }
}

