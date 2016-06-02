 /**
 * Problem     : Paralle Summ Array
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

 	if (my_rank==0)		
 	{
 		int N = 1000 ;
 		int * vector ;
 		vector= malloc(N*sizeof(int));
 		int i =0;
 		for (; i < 1000; ++i)
 		{
 			vector[i]=1;
 		}
 		int smallSize= N/(size-1);
 		int count=0;
 		i = 1;
 		for (; i < size; ++i)
 		{
 			
 			MPI_Send(&smallSize, 1, MPI_INT,  i, 0, MPI_COMM_WORLD);
 			MPI_Send(&vector[count], smallSize, MPI_INT,  i,0, MPI_COMM_WORLD);
 			count+=smallSize;
 		}

		int sum = 0 ;
 		for ( i = 1; i < size; ++i)
 		{
 			
 			int x ; 
 			MPI_Recv(&x, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
 			sum+=x;
 			
 		}
 		printf("total : %d\n", sum);



 	}else{
 		int mySize ;
 		MPI_Recv(&mySize, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
 		int * vector = malloc(mySize*sizeof(int));
 		MPI_Recv(vector, mySize, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

 		int summy = 0 ;
 		int i;
 		for (i = 0; i < mySize; ++i)
 		{
 			summy+=vector[i];
 		}
		printf("Hello p:%d =  %d \n",my_rank ,summy );
 		MPI_Send(&summy,1,MPI_INT,0,0,MPI_COMM_WORLD);

 	}
 

 	MPI_Finalize();
 	return 0;
 }
 
