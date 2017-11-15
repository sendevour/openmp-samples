#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#include "main.h"
extern void PTUpdateEntry( int arr[MAXDIM][MAXDIM+1], int i, int j, int value  ) ;

void FillPascalTriangle( int arr[MAXDIM][MAXDIM+1] )
{
	int i, j ;
	#pragma omp parallel shared(arr)
	{
		#pragma omp for
		for( i = 0 ; i < MAXDIM ; i++ ){
			for( j = 0 ; j<=i  ; j++ ){
				/* Compute the value of the i, j th entry. Use tasks as appropriate
				Update the entry in the table using the function PTUpdateEntry*/

			#pragma omp task 	
				PTUpdateEntry( arr, i, j, ( j==0 || i==0 || i==j )? 1 : arr[i-1][j] + arr[i-1][j-1] ) ;
			}
		}
	}
}

