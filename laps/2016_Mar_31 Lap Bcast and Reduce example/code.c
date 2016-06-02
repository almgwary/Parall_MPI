 /**
 * Problem     : Paralle Lap Bcast and Reduce example
 * Author      : Almgwary
 * Date        : 24-Mar-2016
 * Thin        : --M
 **/

    
#include <stdio.h>
#include <mpi.h>

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
 	int x,summationResult ;
 	if (my_rank==0)		
 	{
 		 x=2;
 	}else{
  	}
 	
 	/**all process must run this and get value*/
	MPI_Bcast(&x,1,MPI_INT,0/*broadcastingprocess*/,MPI_COMM_WORLD);

  	/*make operation for casting variable*/
  	x+=my_rank;

	/*add sum result to master 0*/
	//MPI_Reduce(&x,&summationResult,1,MPI_INT,MPI_Sum,0,MPI_COMM_WORLD);
	/*add sum result to all process*/
	MPI_Allreduce(&x,&summationResult,1,MPI_INT,MPI_SUM,MPI_COMM_WORLD);
	
	printf("process= %d x= %d\n",my_rank,summationResult);
 	MPI_Finalize();
 	return 0;
 }
 
