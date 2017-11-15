#include<stdio.h>
#include<omp.h>
#define ARR_SIZE 600
#define STEP_SIZE 100
int a[ARR_SIZE];
int main(int* argc, char* argv[])
{
        int i, s=0;
        double t1,t2;
        for(i=0; i<ARR_SIZE; i++){
                a[i]=1;
        }
        t1=omp_get_wtime();
        #pragma omp parallel
        {

                #pragma omp for
                for(i=0; i<ARR_SIZE; i+=STEP_SIZE)
                {
                        int j, start = i, end = i + STEP_SIZE - 1;
                        printf("computing sum(%d,%d) from %d of %d\n", start, end, omp_get_thread_num(), omp_get_num_threads());
                        #pragma omp task
                        {
                                int psum = 0;
                                printf("Task computing sum(%d,%d) from %d of %d\n", start, end, omp_get_thread_num(), omp_get_num_threads());

                                for(j=start; j<=end; j++){
                                        psum+=a[j];
                                }

                                #pragma omp critical
                                s+=psum;
                        }
                }
        }

        printf("Sum of the elements of the array: %d. \n", s);

    return 0;
}










