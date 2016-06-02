 /**
 * Problem     : Paralle Assignment#4  Matrix Multiblication On Scatter and Gather
 * Author      : Almgwary
 * Date        : 4-May-2016
 * Thin        : 
 **/

#include <stdio.h>
#include <mpi.h>
#include <time.h>
#include <math.h>


 
void arr_alloc(int** arr, int r,int c){*arr= malloc(r*c*sizeof(int));}

void arr_init(int* arr, int r, int c, int init){

   int i=0;
    for(i=0;i<r;++i){
        int j=0;
        for(j=0;j<c;++j){

            arr[i*c+j]=init;
        }
    }
}

void printMatrix(int* arr,int r,int c){
    int i = 0;
    for(i=0;i<r;++i){
        int j=0;
        for(j=0;j<c;++j){
            printf("%d, ",arr[i*c+j]);
        }
        printf("\n");
    }
}

void arr_dealloc(int** arr){free(*arr);}

void arr_input(int* arr, int r, int c){
	int i=0;
	for (i = 0; i < r; ++i) {
		int j;
		for (j = 0; j < c; ++j) {
			scanf("%d",&arr[i*c+j]);
		}
	}
}

void arr_file_input(FILE *file,int* arr, int r, int c){
	int i=0;
	for (i = 0; i < r; ++i) {
		int j;
		for (j = 0; j < c; ++j) {
			fscanf(file,"%d",&arr[i*c+j]);
		}
	}
}

void arr_alloc_input(int** arr_addres, int r,int c){
	 	//allocation
	    arr_alloc(arr_addres,r,c);
	    //input
	    arr_input(*arr_addres,r,c);

}

void arr_alloc_file_input(FILE *file,int** arr_addres, int r,int c){
	 	//allocation
	    arr_alloc(arr_addres,r,c);
	    //input
	    arr_file_input(file,*arr_addres,r,c);

}

void arr_alloc_intit(int** arr_addres, int r, int c, int init){
	 	//allocation
	    arr_alloc(arr_addres,r,c);
	    //initialize
	    arr_init(*arr_addres,r,c,init);
}

int * matrix_multiblication(int* A, int* B, int A_r, int A_c, int B_r, int B_c){
	int *C;
	int C_r= A_r,
		C_c= B_c;

	//allocat C
	arr_alloc(&C,C_r,C_c);
	//multiblaication operation
	int i=0;
	for (i = 0; i < C_r; ++i) {
		int j=0;
		for (j = 0; j < C_c; ++j) {
			int k=0,sum=0;
			for (k = 0; k < A_c; ++k) {
				int A_cell =A[ i * A_c + k ],
					B_cell =B[ k * B_r + j ];
				sum+=( A_cell * B_cell );
			}
			//store result
			C[i*C_c+j]=sum;
		}
	}
	//printMatrix(C,C_r,C_c);
	return C;
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
 	 
 	if (size<3)
 	{
 		printf("Need at least Three MPI tasks. Quitting...\n");
		MPI_Abort(MPI_COMM_WORLD, 0);
		exit(1);
 	}
 	int input = 0 ;
 	int A_r = 0, A_c = 0,
		B_r = 0, B_c = 0;
	int *A,*B,*C;
 	 

 	
 	if(my_rank==0){
 		

 
 		printf("Welcome to vector Matrix multiplication program!\n");
		printf("if you want program input matrices from file Enter 1\n");
		printf("if you want program input matrices from console Enter 2\n");
 		scanf("%d",&input);
 		if (input==1){ // read form file
 			printf("Reading From File\n");
 			char path[100];

 			/**getting File name*/
			printf("Give a File Name: ");
			// Max length of 99 characters; puts a null terminated string in path, thus 99 chars + null is the max
			scanf("%99s", path);
			printf("This is your path: %s\n", path);

			FILE *file= fopen(path,"r+"); //readFromFile
				if(file!=NULL){
							fscanf(file,"%d%d",&A_r,&A_c);
							fscanf(file,"%d%d",&B_r,&B_c);

							if(A_c==B_r){
								arr_alloc_file_input(file,&A,A_r,A_c);
								arr_alloc_file_input(file,&B,B_r,B_c);

								//printf("Multiblication\n");
							   
								//printf("Result\n");
							    //printMatrix(C,A_r,B_c);

							}else{
								printf("A_c!=B_r");
							}
							fclose(file);
				 }else{
					 printf("unable to open file");
				 }

 		}else if (input==2){ // read form console
 			printf("Please enter the first matrix dimensions elements: ");
			printf("A_row?");scanf("%d",&A_r);
			printf("A_col?");scanf("%d",&A_c);

			


			do {
						printf("Please enter the second matrix dimensions elements: ");
						printf("B_row?");scanf("%d",&B_r);
						printf("B_col?");scanf("%d",&B_c);
				} while (A_c!=B_r); 
 			printf("Reading From Consol\n");
 			printf("Please enter the first matrix elements:");
			arr_alloc_input(&A,A_r,A_c);
			printf("Please enter the first matrix elements:");
			arr_alloc_input(&B,B_r,B_c);
 		}

 		printf("------ A ---------\n");
		printMatrix(A , A_r ,A_c);
		printf("------ B ---------\n");
		printMatrix(B , B_r ,B_c);
 		/*this not valid result*/C = matrix_multiblication(A,B,A_r,A_c,B_r,B_c);

 
 	}
 	 
 	/* Bcast dimentions*/
 	MPI_Bcast (&A_c, 1, MPI_INT, 0, MPI_COMM_WORLD);
 	MPI_Bcast (&A_r, 1, MPI_INT, 0, MPI_COMM_WORLD);
 	MPI_Bcast (&B_c, 1, MPI_INT, 0, MPI_COMM_WORLD);
 	MPI_Bcast (&B_r, 1, MPI_INT, 0, MPI_COMM_WORLD);
 	// allocations
 	if (my_rank!=0)
 	{
 		arr_alloc(&A,A_r,A_c);
 		arr_alloc(&B,B_r,B_c);
 		arr_alloc(&C,A_r,B_c);
 	}
 	/* Bcast B and Scatter A*/
 	MPI_Bcast (B, B_r*B_c, MPI_INT, 0, MPI_COMM_WORLD);
 	
   /* Scater A rows 
    * 		1. calculate # of rows for each process then send with scatter
    *		2. collect with all gather
    *		3. calculate remaing rows then send with send and recive
    *		4. collect with recive
    *
	*
    **/
	int  nRow = A_r / size  ; 
	int remaing = A_r % size ; 

	// scattring
	int *subA,*subC;

	arr_alloc(&subA,nRow,A_c);
	arr_alloc(&subC,nRow,B_c);

	//MPI_Scatter (A, SIZE, MPI_INT, small A, small A size, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Scatter(A,nRow*A_c,MPI_INT,subA,nRow*A_c,MPI_INT,0,MPI_COMM_WORLD);


	// printf("------ subA ->%d -------\n",my_rank);
	// printMatrix(subA , nRow ,A_c);

	// do sub multiplicaion
	int r = 0 ;
	for( r ; r <nRow;++r){
		int c2 = 0 ;
		for (c2 = 0; c2< B_c; ++c2)
		{
			 int c1= 0  , sum=0;;
			 for ( c1  = 0; c1  < A_c; ++c1 )
			 {
			 	 sum =  sum + (subA[r*A_c+c1]*B[c1*B_c+c2]) ;
			 	 /**
			 	  *  accessing B as 2d
			 	  *  fist column : 2nd colmn
			 	  *  0 + 0c		 : 1 + 0c
			 	  *  0 + 1c		 : 1 + 1c
			 	  *  0 + 2c		 : 1 + 2c
			 	  *  0 + 3c		 : 1 + 3c
			 	  */
			 	 // printf("[%d] * [%d ] sum+= %d\n",subA[r*A_c+c1],B[c1*B_c+c2]  , sum);
			 }
			// printf("p%d:%d\n",my_rank,sum );
			 subC [r*A_c+c2] =sum ; 
		}
	}
    //MPI_Gather (C[from], SIZE*SIZE/P, MPI_INT, C, SIZE*SIZE/P, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Gather(subC ,nRow*B_c ,MPI_INT , C , nRow*B_c, MPI_INT, 0, MPI_COMM_WORLD  );
    
/*	if (my_rank==0)
 	{
 		printf("------Gather C-------\n");
		printMatrix( C, A_r,B_c);
 	} */
    // handle remaining rows =D
    /**
      * remaining rows < size
      * send for each process 1 row  if process can get row else donot recive or send
      * 
	  **/

	if (my_rank==0) // send remaing rows
 	{
 		int i = 1 ;
 		for ( i ; i < size; ++i)
 		{
 			if ((i+(nRow*size))<=A_r) // send row to work with
			    {  
			    	//printf("$$$$$ sneding sub to p:%d\n", i);
 					MPI_Send(&A[((i-1)+(nRow*size))*A_c], A_c, MPI_INT,  i,0, MPI_COMM_WORLD);
			    }
 		}
 	} 

 	int *subRow,*subRowResult;
 	arr_alloc(&subRow,1,A_c+1);
 	arr_alloc(&subRowResult,1,B_c);

    if (my_rank!=0 && (my_rank+(nRow*size))<=A_r) // i should have row to work with
    {
    	 // recive and do work then send result
    	 //printf("$$$$$ reciving sub from master to  p:%d\n", my_rank);	
    	 MPI_Recv(subRow, A_c, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    	 //printf("$$$$$ recivied sub from master to ---- p:%d, %d , %d\n", subRow[0], subRow[1], subRow[2]);
    }
    // make one row multiblication 


    	

	




   if(my_rank!=0 && (my_rank+(nRow*size))<=A_r) // i send resilt tot master 
    {
    	int c2 = 0 ;
		for (c2 = 0; c2< B_c; ++c2)
		{
			 int c1= 0  , sum=0;;
			 for ( c1  = 0; c1  < A_c; ++c1 )
			 {
			 	 sum =  sum + (subRow[c1]*B[c1*B_c+c2]) ;
			 	 /**
			 	  *  accessing B as 2d
			 	  *  fist column : 2nd colmn
			 	  *  0 + 0c		 : 1 + 0c
			 	  *  0 + 1c		 : 1 + 1c
			 	  *  0 + 2c		 : 1 + 2c
			 	  *  0 + 3c		 : 1 + 3c
			 	  */
			 	 // printf("[%d] * [%d ] sum+= %d\n",subA[r*A_c+c1],B[c1*B_c+c2]  , sum);
			 }
			// printf("p%d:%d\n",my_rank,sum );
			 subRowResult [c2] =sum ; 
			 //printf("#> %d\n", sum);
		}
    	 // recive and do work then send result
    	//printf("))))))))) sending to master %d\n",my_rank );
 		MPI_Send(subRowResult, B_c, MPI_INT,  0,0, MPI_COMM_WORLD);	    	
    	//printf("OOOOOOOO sent to master %d\n",my_rank );
 		
    	//MPI_Recv(subRow, A_c, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    }




  //   // master reciving results

    if (my_rank==0) // send remaing rows
 	{
 		int i = 1 ;
 		for ( i ; i < size; ++i)
 		{
 			if ((i+(nRow*size))<=A_r) // send row to work with
			    {  
			    	 //MPI_Send(A[(i+(nRow*size))*A_c], A_c, MPI_INT,  i,0, MPI_COMM_WORLD);
			    	//printf("))))))))) master reciving %d\n",i );
			    	MPI_Recv(&C[((nRow*size)+i-1)*B_c], B_c, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
			    	//MPI_Recv(subRowResult, B_c, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
			    	

			    	//printf("UUUUUUUUUU master recived %d\n",i );
			    	
			    }
 		}
 	} 









 	if (my_rank==0)
 	{
 		printf("------ C-------\n");
		printMatrix( C, A_r,B_c);
		//printMatrix(subRowResult ,1,B_c);
 	} 
 	 
 	 
 	MPI_Finalize();
 	return 0;
 }
 	 
 