#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "sorting.h"

long *Load_File(char *Filename, int *Size){
	FILE * inf = fopen(Filename,"r");
	int n;              // the number of integers to be sorted

	// error
	if(inf == NULL){
		return NULL;}

	// scan the first value in the file--number of elemetns to be sorted
	fscanf(inf, "%d", &n);
	*Size = n;
	int i;
	long *Array = malloc(sizeof(long)*n);
	for(i = 0 ; i < n; i++)
	{	
		fscanf(inf, "%ld\n",&Array[i]);
		//error
	}
	fclose(inf);

	/*for(i = 0; i < n; i++)
	  {
	  printf("%ld", Array[i]);
	  }*/
	// what does it return?
	return(Array);
}	              

int Save_File(char *Filename, long *Array, int Size){
	FILE *inf = fopen(Filename,"w");
	if(inf == NULL){
		return 0;}
	int i;  // Array index
	fprintf(inf, "%d\n", Size);
	// number of elements to be sorted
	for(i = 0; i < Size; i++){
		fprintf(inf,"%ld\n",Array[i]);
	}
	fclose(inf);
	return(i);   

}

// power function to calculate 2^p*3^q
/*int int_pow(int base, int exp)
  {
  int result = 1;
  while (exp)
  {
  if (exp & 1){
  result *= base;}
  exp /= 2;
  base *= base;
  }
  return result;
  }*/

void Shell_Insertion_Sort (long *Array, int Size, double *NComp, double *NMove){
	//generate Seq1
	int *res = malloc(sizeof(int) * Size);  // Seq1
	res[0] = 1;  // the first element of Seq1 is 1
	int p2 = 0;  // location of 2
	int p3 = 0;  // location of 3
	int i_Seq1 = 0;  // index of Seq1
	int u2 = 0;  // elements got by multiply 2
	int u3 = 0;  // elements got by multiply 3
	while(res[i_Seq1 - 1] < Size){
	       /*if(res[p2] * 2 == res[i_Seq1 - 1]){
                p2 += 1;}
               else if(res[p3] * 3 == res[i_Seq1 - 1]){
                p3 += 1;}*/
	       i_Seq1++;
               u2 = res[p2] * 2;
               u3 = res[p3] * 3;
               if(u2 < u3){
               p2 += 1;
               res[i_Seq1] = u2;}
               else{
               p3 += 1;
               res[i_Seq1] = u3;}
	       

          }
	
	i_Seq1--;
	//do shell-insertion sort
	int gap;
	int j;
	int i; 
	while( i_Seq1 >= 0){
		gap = res[i_Seq1];
		i_Seq1--;
		for(j = gap; j < Size; j ++){
			long temp = Array[j];
			i = j;
			(*NMove) ++;
			//for(k = j; (k >= gap) && (Array[k - gap] > temp); k -= gap){
			while(i >= gap && Array[i - gap] > temp){ 
				(*NComp) += 1;
				Array[i] = Array[i - gap];
				i -= gap;
				(*NMove) ++;
			}
			Array[i] = temp;
			(*NMove) ++;	
		}
	}
	free(res);
}

void swap(long *xp, long *yp){
	long temp = *xp;
	*xp = *yp;
	*yp = temp;
}

void Improved_Bubble_Sort (long *Array, int Size, double *NComp, double *NMove){
	// generate Seq2
	int i_Seq2 = 0;  //array index of Seq2
	int n = Size / 1.3;
	int *Seq2 = malloc(sizeof(int) * Size);

	if(n == 9 || n == 10){
		n = 11;}
	Seq2[i_Seq2] = n;
	while(n > 1){
		n = n / 1.3;
		if(n == 9 || n == 10){
			n = 11;}
		i_Seq2++;
		Seq2[i_Seq2] = n;
	}
	//using bubble sort with gaps to sort the array
	//comb
	int i = 0; // gap index in Seq2
	int gap;  
	int j = 0;  // index for subarray selected
	for(i = 0; i <= i_Seq2; i++){
		gap = Seq2[i]; 
		(*NComp)++;    
		
		for(j = 0; j < Size - gap; j++){
			if(Array[j] > Array[j + gap]){
				(*NComp)++;
				swap(&Array[j],&Array[j + gap]);
				(*NMove) += 3;
			}
			}
		}
	
	free(Seq2);
}



