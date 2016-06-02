/**
 * Problem     : Paralle Assignment#2 getMaxOfArray
 * Author      : Almgwary
 * Date        : 28-Mar-2016
 * Thin        : --M
 **/
 #include <stdio.h>
 #include <mpi.h>


	  /***
 		* get number of elemnets for each process and if ther is remining elemnts they will be < n_slaves
 		* they will automticly add for each process
 		* if slave recived size = 0 he will not recive array and will terminate
 		* each slave send max number and master collect them and print final result
 		* each slave take their actual index and send actual max index to master
 		*
 		**/
 int  main(int argc, char  *argv[])
 {
 	int my_rank;
 	int size;
 	int n_slaves;
 	int tag;
 	int source;
 	int destination;
 	MPI_Status status;
 	MPI_Init(&argc,&argv);
 	MPI_Comm_size(MPI_COMM_WORLD,&size);
 	n_slaves = size-1;
 	MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
 	
 	if (my_rank==0)		
 	{
 		int * working_slaves ;
 		working_slaves = malloc(size*sizeof(int));
 		printf("Hello from Master Process\n");
 		printf("number of Slaves Process is: %d \n",n_slaves);
 		printf("Please enter size of array\n");
 		int array_size ;
 		scanf("%d",&array_size);
 		int *array ;
 		array= malloc(array_size*sizeof(int));

 		
 		printf("Please enter arry elemnts\n");
 		int i=0;
 		for (; i < array_size; ++i)
 		{
 			scanf("%d",&array[i]);
 		}

 		int small_part, remaining ,count =0;
 		small_part= array_size/n_slaves;
 		remaining = array_size - (n_slaves*small_part);

 		for ( i = 1; i < size; ++i)
 		{
 			int x =  small_part ;
 			if(remaining>0){ // add remaining valuse
 				x+= 1;
 				remaining--;
 			}

 			MPI_Send(&x,1,MPI_INT,i,0,MPI_COMM_WORLD);
 			MPI_Send(&count,1,MPI_INT,i,0,MPI_COMM_WORLD);
 			if(array_size>0) // // if array size = 0 there is no more work
 				{
 					MPI_Send(&array[count],x,MPI_INT,i,0,MPI_COMM_WORLD);
 					working_slaves[i]=1; // this slave will send value will  work
 				}else {
 					working_slaves[i]=0; // this slave will send value will not work
 				}

 			count+=x;
 			array_size-=x; // if array size = 0 there is no more work
 		}
 		int max = -100000000;
 		int index ;
 		for ( i = 1; i < size; ++i)
 		{
 			if(working_slaves[i]==1){ // check if this slave will send value
 				int x , y;
	 			MPI_Recv(&x, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
	 			MPI_Recv(&y, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
	 			if(x>max){
	 				
	 				max= x;
	 				index=y;
	 			}
 			}
 		}
 		printf("Master process announce the final max which is %d and its index is %d.\nThanks for using our program",max,index);



 	}else{

 		int subSize, actual_index ; 
 		MPI_Recv(&subSize,1,MPI_INT, 0 , 0,MPI_COMM_WORLD,&status);
 		MPI_Recv(&actual_index,1,MPI_INT,0,0,MPI_COMM_WORLD,&status);
 		if(subSize>0){
 			int * array ;
 			array = malloc(subSize*sizeof(int));
 			MPI_Recv(array,subSize,MPI_INT,0,0,MPI_COMM_WORLD,&status);
 			int indx , max = -1000000;
			int i = 0;
 			for (; i < subSize; ++i)
 			{
 				if(array[i]>max){
 					max = array[i];
 					indx = i ;
 				}
 			}
 			MPI_Send(&max,1,MPI_INT,0,0,MPI_COMM_WORLD);
 			actual_index+=indx;
 			MPI_Send(&actual_index,1,MPI_INT,0,0,MPI_COMM_WORLD);
 			printf("Hello from slave#%d Max number in my partition is %d and index is %d.\n",my_rank,max,indx  );
 		}else{
 			printf("Hello From Slave %d i will not work\n",my_rank );
 		}
 		 
 	}

 	MPI_Finalize();
 	return 0;
 } 		 
