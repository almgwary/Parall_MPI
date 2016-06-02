 /**
 * Problem     : String toupper
 * Author      : Almgwary
 * Date        : 5-May-2016
 * Thin        : 
 **/

#include <stdio.h>
#include <mpi.h>
#include <time.h>
#include <math.h>


   
 
int main(int argc, char  *argv[])
{
  int my_rank;
  int size ;
  int tag;
  int source;
  int dest ;
  MPI_Status status;

    char  string [100];
    char  subString [100];
  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD , &my_rank);
   
  int input = 0 ;
  int A_r = 0, A_c = 0,
    B_r = 0, B_c = 0;
  int *A,*B,*C;
  int stringSize ;

  
  if(my_rank==0){
    printf("Enter String\n");
    scanf("%s", &string) ; 
    stringSize = strlen(string);
    printf("%d\n", stringSize);
    
 
  }
   
  
  
  MPI_Bcast (&stringSize, 1, MPI_INT, 0, MPI_COMM_WORLD);
  int myStringSize = stringSize/size ; 
  int remaing   = stringSize % size ; 


  MPI_Scatter(string,myStringSize,MPI_CHAR,subString,myStringSize,MPI_CHAR,0,MPI_COMM_WORLD);

   
  int i = 0 ;
  for ( i = 0; i < myStringSize; ++i)
  {
     subString[i]= (char) toupper( (int)subString[i]);
  }
  
  MPI_Gather(subString , myStringSize , MPI_CHAR , string , myStringSize , MPI_CHAR , 0 , MPI_COMM_WORLD);
  
  if (my_rank==0)
  {
    printf("%s - %d\n",string , my_rank );
  
  }

  MPI_Finalize();
  return 0; 
 }


 