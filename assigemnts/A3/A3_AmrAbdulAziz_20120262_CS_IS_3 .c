 /**
 * Problem     : Paralle Ass3 Factorial Bcast
 * Author      : Almgwary
 * Date        : 15-Apr-2016
 * Thin        :  Factorial of 10 in 10 process time = 
 113805
 57680
 **/

    
#include <stdio.h>
#include <mpi.h>
#include <time.h>
#include <math.h>




long long int claculate (int start , int end , int my_rank){
	
	
	int i = start ;
	long long int result = 1 ; 
	for ( ; i <end; ++i)
	{
		//printf("%d * ", i);
		result*= i ;
	}
	//printf(" = %d.\n", result);
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
 	 
 	
 	int N = 0  , n;
 	int subrange = 0 ;
 	int remaining  =  0 ;

 	double start_time, end_time;
	start_time = MPI_Wtime();
	

 	
 	if(my_rank==0){
 		


		
		

 		printf("Enter N = \n");
 		scanf("%d",&N);

 		// get subrange for each procces
 		n  = N ;
 		subrange =  N/size ;
 		remaining  =  N  - subrange*size ;
 	}

 	 
 	// broadCast
 	MPI_Bcast(&N,1,MPI_INT,0/*broadcastingprocess*/,MPI_COMM_WORLD);
 	MPI_Bcast(&subrange,1,MPI_INT,0/*broadcastingprocess*/,MPI_COMM_WORLD); 	
 	
 	// prepar start and end
 	int start =  my_rank*subrange+1;
 	int end = 	start + subrange;
 	 // make calculations
 	long long int result =  claculate(start,end,my_rank);
 	//printf("p%d: calculate partial factorial from %d to %d Result= %d \n  ",my_rank,start,end,result );
 	
 	long long int globalResult = 1 ;
 	
 	MPI_Reduce(&result,&globalResult,1,MPI_INT,MPI_PROD,0,MPI_COMM_WORLD);

 	if(my_rank == 0	){
 		// calculate remaining
 		//printf(" globalResult = %d\n", globalResult);
 		while (remaining >0 ){
 				
 				globalResult*= N;
 				//printf(" N = %d  -> %d\n", N,globalResult);
 				N-- ;
 				//printf("Remaing:%d N= %d  Result=: %d\n", remaining,N, globalResult);
 				
 				remaining--;
 		}
		
		 
		printf("\n\n--------- \n\nFactorial= %lld  \n",globalResult);
		end_time = MPI_Wtime();
		float t = end_time - start_time ;
		printf("Bcast Time == : %f \n", t );

 	}



 	// second caculation 
 	 N= n ;
 	 subrange = N/size  ;
 	 remaining  = N  - subrange*size ;

 	 

 	

 	if(my_rank == 0 ){
 		 
 		 
	start_time = MPI_Wtime();
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
 	  
 	
 	// make calculations
 	 result =  claculate(start,end,my_rank);
 	//printf("p%d: calculate partial factorial from %d to %d Result= %d \n  ",my_rank,start,end,result );
 	globalResult =1 ;


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
 				//printf(" N = %d\n", N);
 				globalResult*= N--;
 				//printf("Remaing:%d N= %d  Result=: %d\n", remaining,N, globalResult);
 				remaining--;
 		}
 		 
 		 
		 
		//double time_spent2 = (double)(end_time - begin_time) / CLOCKS_PER_SEC;
		
		 
		//printf("Factorial=  %lld \n",globalResult);
		end_time = MPI_Wtime();
		float t = end_time - start_time  ;
		printf("Send and Recive Time == : %f \n\n\n--------- \n\n", t );

		 
 	}


 	 
 	MPI_Finalize();
 	return 0;
 }
 	 
 
