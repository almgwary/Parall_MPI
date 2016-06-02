/**
 * Name        : Assignment1 Matrix Multiblication
 * Author      : Almgwary
 * Date        : 11-Mar-2016
 * ID          : 20120262
 * Groub 	   : CS_IS3
 **/

#include <stdio.h>
#include <stdlib.h>


void arr_alloc(int** arr, int r,int c){
    *arr= malloc(r*c*sizeof(int));
}

void arr_init(int* arr, int r, int c, int init){

   int i=0;
    for(i=0;i<r;++i){
        int j=0;
        for(j=0;j<c;++j){

            arr[i*c+j]=init;
        }
    }
}

void arr_print(int* arr,int r,int c){
    int i = 0;
    for(i=0;i<r;++i){
        int j=0;
        for(j=0;j<c;++j){
            printf("%d, ",arr[i*c+j]);
        }
        printf("\n");
    }


}

void arr_dealloc(int** arr){
    free(*arr);
}

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

int * matrix_multiblication(int* arr1, int* arr2, int arr1_r, int arr1_c, int arr2_r, int arr2_c){
	int *arr_result;
	int arr_result_r= arr1_r,
		arr_result_c= arr2_c;

	//allocat arr_result
	arr_alloc(&arr_result,arr_result_r,arr_result_c);
	//multiblaication operation
	int i=0;
	for (i = 0; i < arr_result_r; ++i) {
		int j=0;
		for (j = 0; j < arr_result_c; ++j) {
			int k=0,sum=0;
			for (k = 0; k < arr1_c; ++k) {
				int arr1_cell =arr1[ i * arr1_c + k ],
					arr2_cell =arr2[ k * arr2_r + j ];
				sum+=( arr1_cell * arr2_cell );
			}
			//store result
			arr_result[i*arr_result_c+j]=sum;
		}
	}
	//arr_print(arr_result,arr_result_r,arr_result_c);
	return arr_result;
}

int main()
{
	//disable output buffer
	setvbuf(stdout, NULL, _IONBF, 0);

	int arr1_r = 0, arr1_c = 0,
		arr2_r = 0, arr2_c = 0;
	int *arr1=NULL,
		*arr2=NULL,
		*arr_result=NULL;

	printf("Welcome to vector Matrix multiplication program!!\n");
	printf("if you want program input matrices from file Enter 1\n");
	printf("if you want program input matrices from console Enter 2\n");
	int input=0;
	scanf("%d",&input);
	if(input==1){//file C:/Users/elmegwary/EclipsMarsJava/C/Debug/test.txt
		FILE *file= fopen("test.txt","r+");
		if(file!=NULL){
					fscanf(file,"%d%d",&arr1_r,&arr1_c);
					//printf("%d%d",arr1_r,arr1_c);
					arr_alloc_file_input(file,&arr1,arr1_r,arr1_c);

					fscanf(file,"%d",&arr2_r);
					fscanf(file,"%d",&arr2_c);

					if(arr1_c==arr2_r){
						arr_alloc_file_input(file,&arr2,arr2_r,arr2_c);

						printf("Multiblication\n");
					    arr_result = matrix_multiblication(arr1,arr2,arr1_r,arr1_c,arr2_r,arr2_c);

						printf("Result\n");
					    arr_print(arr_result,arr1_r,arr2_c);

					}else{
						printf("arr1_c!=arr2_r");
					}
					fclose(file);
		 }else{
			 printf("unable to open file");
		 }




	}else if(input==2){//console
		printf("Please enter the first matrix dimensions elements: ");
		printf("arr1_row?");scanf("%d",&arr1_r);
		printf("arr1_col?");scanf("%d",&arr1_c);

		printf("Please enter the first matrix elements:");
		arr_alloc_input(&arr1,arr1_r,arr1_c);


		do {
					printf("Please enter the second matrix dimensions elements: ");
					printf("arr2_row?");scanf("%d",&arr2_r);
					printf("arr2_col?");scanf("%d",&arr2_c);
			} while (arr1_c!=arr2_r);
		 arr_alloc_input(&arr2,arr2_r,arr2_c);

		 printf("Multiblication\n");
		 arr_result = matrix_multiblication(arr1,arr2,arr1_r,arr1_c,arr2_r,arr2_c);

		 printf("Result\n");
		 arr_print(arr_result,arr1_r,arr2_c);

	}
















	int x;
	scanf("%d",&x);
    /*free(arr1);
    free(arr2);
    free(arr_result);*/

   return 0;
}
