 /**
 * Problem     : Paralle Ass3 Factorial Send and Recive 
 * Author      : Almgwary
 * Date        : 15-Apr-2016
 * Thin        :  Factorial of 10 in 10 process time = 137104
 **/

    
#include <stdio.h>
#include <mpi.h>
#include <time.h>
#include <math.h>




long long int claculate (int start , int end){
	
	
	int i = start ;
	long long int result = 1 ; 
	for ( ; i <end; ++i)
	{
		//printf("%d*", i);
		result*= i ;
	}
	//printf(" = %d\n", result);
	return result ;
}


int main(int argc, char  *argv[])
 {
 	int my_rank;
 	int size ;
 	int tag;
 	int source;
 	int dest ;
 	MPI_Status status;


 	MPI_Init(&argc,&argv);
 	MPI_Comm_size(MPI_COMM_WORLD, &size);
 	MPI_Comm_rank(MPI_COMM_WORLD , &my_rank);
 	 
 	
 	int N = 0 ;
 	int subrange = 0 ;
 	int remaining  =  0 ;

 	clock_t begin_time, end_time;
	double time_spent;

 	
 	if(my_rank==0){
 		


		begin_time = clock();
		

 		printf("Enter N: \n");
 		scanf("%d",&N);

 		// get subrange for each procces
 		subrange =  N/size ;
 		remaining  =  N  - subrange*size ;
 	}

 	if(my_rank == 0 ){

 		int i = 1 ; 
 		for (; i < size; ++i)
 		{
 			MPI_Send(&N, 1, MPI_INT,  i, 0, MPI_COMM_WORLD);
 			MPI_Send(&subrange, 1, MPI_INT,  i, 0, MPI_COMM_WORLD);
 			
 		}
 	}else {
 		MPI_Recv(&N, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
 		MPI_Recv(&subrange, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
 	}
 
 	// prepar start and end
 	int start =  my_rank*subrange+1;
 	int end = 	start + subrange;
 	
 	// make calculations
 	long long int result =  claculate(start,end);
 	printf("p%d: calculate partial factorial from %d to %d Result= %d \n  ",my_rank,start,end,result );
 	long long int globalResult =1 ;
 	
 	if(my_rank!=0){
 		MPI_Send(&result, 1, MPI_INT,  0, 0, MPI_COMM_WORLD);
 	}else {
 		int i = 1 ; 
 		int v ; 
 		for (; i < size; ++i)
 		{
 				MPI_Recv(&v, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
 				globalResult*= v;
 	
 		}
 	}

 	if(my_rank == 0	){
 		// calculate remaining
 		while (remaining >0 ){
 				globalResult*= N--;
 				//printf("Remaing:%d N= %d  Result=: %d\n", remaining,N, globalResult);
 				remaining--;
 		}
 		printf("Factorial: %d\n", globalResult);
 		/* here, do your time-consuming job */
		end_time = clock();
		time_spent = (double)(end_time - begin_time) / CLOCKS_PER_SEC;
		printf("TimeInSendAndRecive: %d\n", time_spent);

 	}
 	 
 	MPI_Finalize();
 	return 0;
 }
 	 
 
