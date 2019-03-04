/*
 *1. Open training file. Read into 2 separate matrices.
	X matrix: (N x K+1) First element of every row will be 1.
	Y matrix: (N x 1)   Elements are the last column of the training file.
 *
 *2. Run transpose method and create a new XT matrix.
 *3. Run multiply method and multiply XT with X, in that order to create XTX. (XT. X)
 *4. Run inverse method and take inverse of XTX, returning XTXI.
 *5. Run multiply method and multiply XTXI and XT into new matrix, idk what to name it
 *6. Run multiply method and the idk what to name it with Y matri
 *7. Open the test file and do the plug-in.
 *
 */

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

//int main(int argc, char** argv);
double** multiply(double**, double**, int, int, int);
double** inverse(double** matrix, int);
double** transpose(double**, double**, int, int);
//void print(double**, int, int);
/*
void print (double** matrix, int rows, int columns) {
	int i = 0; int j = 0;
	for (i = 0; i < rows; i++) {
		double element = 0;
		for (j = 0; j < columns; j++) {
			element = matrix[i][j];
			printf("%lf  ", element);
		}
		printf("\n");
	}



}
*/


double** inverse(double** matrix, int dimensions) {
/*
 *this is the crux of the assignment. i need to sovle using jordan-gauss elimination or whatever MINUS the ability to switch rows.
 *this really isn't that hard. it's just hyped. inshAllah.
 *i can basically only do three things: multiply/divide rows, add/subtract rows, or use a term to multiply/divide. i can also do combos of this
 *in class prof said it might be a good idea on focusing how to get the diagonal down to all 1s first. 
 *steps: create augmented matrix. fill it with terms from matrix, and then the 1s and 0s. code the different operations for different instances. 
 * by the end, the entire first part of the aug should turn into the identity matrix. kind of like switching places.
 * return the other second half which has the invrese values.
 */

//create the augmented matrix. its dimensions will be 2 * whatever dimensions are being given
//	printf("im in inverse\n");
	double augCols = dimensions *2; int i = 0; int j = 0;
	double ** augmented;

	augmented = (double**) malloc(dimensions * sizeof(double*)); //same number of rows
		for (i = 0; i <dimensions; i++) { //just double the number of columns
			augmented[i] = (double*) malloc(augCols * sizeof(double));
		}		
//	printf("i just malloced the augmented matrix\n"); 
//now i'm going to take in the entries from the input matrix and put them into the augmented matrix
 
	for ( i = 0; i < dimensions; i++) { //the row size will conintue to be the same
		for (j = 0; j < augCols; j++) { //the columns will be double, AKA the 
			if ( j < dimensions) {
				augmented[i][j] = matrix[i][j];
			} else if ( i == (j - dimensions)) {
				augmented[i][j] = 1.0;
			} else {
				augmented[i][j] = 0.0;
			}
		}
	}
//	printf("augmented: ");
	//print(augmented, dimensions, augCols);
//	printf("i just put in all the elements into the augmented matrix\n");

//now all the different types of operations i can do. i am going to start with turning the diagonal into all 1s. WORK ON THE  diagonal first.
	int k = 0;
	for ( i = 0; i < dimensions; i++) {
		for (j = 0; j < dimensions; j++) {
			if ( i != j) {
				double temp = augmented[j][i] / augmented[i][i];
				for ( k = 0; k < augCols; k++) {
					augmented[j][k] -= (temp * augmented[i][k]);
				}
			}
		}
	}
	for (i = 0; i < dimensions; i++) {
		float temp2 = augmented[i][i];
		for (j = 0; j < augCols; j++) {
			augmented[i][j] /= temp2;
		}
	}
//	printf("augmented: \n");
//	print(augmented, dimensions, augCols);
	
//	printf("i just calculated the inverse\n");
//now return the inverse. this is only going to be the last half of the original matrix. rewrite these into the original matrix.
	double ** inverse;
	inverse = (double **) malloc (dimensions * sizeof(double*));

	for (i = 0; i < dimensions; i++) {
		inverse[i] = (double*) malloc (dimensions * sizeof(double));
	}
//	printf("I just malloced the inverse matrix\n");
	int index;
	for (i = 0; i < dimensions; i++) {
		for (j = 0; j < augCols; j++) {
			if ((j == dimensions) || (j > dimensions)) {
				index = j - dimensions;	
				inverse[i][index] = augmented[i][j];
			}
		
		}
	}
//	printf("inverse: ");
//	print(inverse, dimensions, dimensions);
//	printf("I just reloaded all the elements into the inverse matrix\n");
	return inverse;
}

double** transpose(double** transpose, double** ogMatrix, int  rows, int  columns) {
	//double ** transpose;
	//declare the array of pointers
	//transpose = (double**) malloc(rows * sizeof(double*));
	//declare the rows of the transpose matrix
//	printf("im in transpose\n");



	int i = 0; int j = 0;
	//for (i = 0; i < rows; i++) {
	//	transpose[i] = (double*) malloc(columns * sizeof(double));
//	}


	//now you're going to iterate through the first matrix and find the elements, [i][j]. that element will equal [j][i] of the
	for (i = 0; i < columns; i++) {
		for (j = 0; j < rows; j++) {
			transpose [j][i] = ogMatrix [i][j];
		}
	}
//	printf("transpose: \n");
//	print(transpose, columns, rows);
	return transpose;

}


double** multiply(double** m1, double** m2, int rows, int columns, int colm1) {
	//need to take in the sizes of the matrices too
//	printf("im in multiply\n");
//	int size; 
	int i; int j;
//	 int element;
	double **multiplied;
	multiplied = (double**) malloc(rows * sizeof(double*));//declare h
	//initialize the rows of multiplied, row by row
	for (i =0; i < rows; i++) {
		multiplied[i] = (double *) malloc(columns * sizeof(double));
	}

	//initialize all the elements of the matrix.
	for (i = 0; i < rows; i++) {
		for (j = 0; j < columns; j++) {
			multiplied[i][j] = 0.0;
		}
	}

	int k;
	for (i = 0; i < rows; i++) {
		for (j = 0; j < columns; j++) {
			double sum = 0;
			for (k = 0; k <colm1; k++) {
				sum += ((m1[i][k]) * (m2[k][j]));
			}
			multiplied[i][j] = sum;
		}
	}
//	printf(" multiplied: \n");
//	print(multiplied, rows, columns);
	return multiplied;
}
int main(int argc, char** argv) {
//I must first open the training file and do all the stuff with it before i move onto the test file.
//	printf("im in main\n");
	if (argc != 3) {
		printf("not enough arguments\n");
		return 0;
	}
	//open the training file
	FILE *fp; int rowSize = 0; int colSize = 0;
	fp = fopen(argv[1], "r");
//	printf("opened training file");
	if (fp == NULL) return 0;
	fscanf(fp, "%d\n", &colSize);
//	printf("this is colsize: %d\n", colSize);
	colSize = colSize + 1;
	fscanf(fp, "%d\n", &rowSize);
//	printf("this is rowsize: %d\n", rowSize);
//declare the X array and the Y array.
//X: (rowSize, colSize)
//Y: (rowSize, 1);
	double ** x; double ** y;
	x = (double**) malloc(rowSize * sizeof(double*));
	int i = 0; int j = 0;
	for (i = 0; i <rowSize; i++) {
		x[i] = (double*) malloc(colSize * sizeof(double));
	}
	//add leading ones to the X matrix
	for (i = 0; i <rowSize; i++) {
		for (j = 0; j <rowSize; j++) {
			if (j == 0) x[i][j] = 1.00;
		}
	}
//	printf("i just added all the leading 1s to the x matrix\n");
//on column with as many rows as t original and 
	y = (double**) malloc(rowSize * sizeof(double*));
	for (i = 0; i < rowSize; i++) {
		y[i] = (double*) malloc ( 1 * sizeof(double));
	}
//	printf("i just made the y matrix\n");
//Now read the string and parse its values into the x and y matrices.
//actually make a new matrix that's gonna scan in all the values from the OG matrix. and then manipulate that into x and y.
	double ** og; double element;
	og = (double**) malloc(rowSize * sizeof(double*));
	for (i = 0; i < rowSize; i++) {
		og[i] = (double*) malloc(colSize * sizeof(double));
	} 
//	printf("i just made the og matrix\n");
//	while (!EOF) {
		//scan all the elements into an OG matrix.
		for (i = 0; i < rowSize; i++) {
			for (j = 0; j < colSize; j++) {
				fscanf(fp, "%lf,", &element);
				og[i][j] = element;
			}
		}
//	}
//	printf("original AKA OG: \n");
//	print(og, rowSize, colSize);
//	printf("i just scanned into the og matrix\n");
	fclose(fp);
//traverse thru this to populate x and y. basically a triple nested for loop, in which i'm gonna look thru the rows of original and then populate the X and Y matrices. I need to be careful about X=> x should only be filled from column 1 (skipping column 0) onwards. y=> is going to be the last column. u know that this will be when j==last-1.
//
//	int k = 0;
/*
	for (i = 0; i <rowSize; i++) {
		for (j = 0; j<colSize; j++) {
			for (k = 1; k < colSize; k++) {

				if (j != (rowSize-1))
				x[i][k] = og[i][j];

				else if (j == (rowSize-1))
				y[i][j] = og [i][j]; //this line may be problematic because

			}
		}
	}

*/
//fill in the X matrix, you're only starting from the 1st column onwards
	int temp = 0;
	for (i = 0; i <rowSize; i++) {
		for (j = 0; j <colSize; j++) {
			if (j < (colSize-1)) {
				temp = j+1;
				x[i][temp] = og[i][j];
			}
		}
	}

//	printf("x: \n ");
//	print(x, rowSize, colSize);

//	printf("i just filled in the x matrix\n");
	for ( i = 0; i <rowSize; i++) {
		for (j = 0; j < colSize; j++) {
			if (j == (colSize - 1))
				y[i][0] = og[i][j];
		}
	}
//	printf("y: \n ");
//	print(y, rowSize, 1);
	
//	printf("i just filled in the y matrix\n");

//NOW I HAVE AN X AND Y MATRIX.
//Formula: W = (XT * X) ^-1    * XT*Y
//now do all the back flips with the transpose and inverse matrices. also code the inverse matrix.

//now i have to create the XT matrix. iniitalize it first. and then pass X into the transpose function and fill the response into XT.
	double ** xt;
	xt = (double **) malloc(colSize * sizeof(double*));
	for (i = 0; i < colSize; i++) {
		xt[i] = (double*) malloc(rowSize * sizeof(double));
	}

	//now initialize all of these elements to 0.

	for (i = 0; i <colSize; i++) {
		for (j = 0; j < rowSize; j++) {
			xt[i][j] = 0.00;
		}
	}
//	printf("i just initialized all the xt elements to 0\n");

	//does this work? also put in the dimensions of xt. 
	xt = transpose(xt, x, colSize, rowSize);
//	printf("xt : \n");
//	print(xt, colSize, rowSize);	
	//now make matrix xtx
	double ** xtx;
	xtx = (double **) malloc(rowSize * sizeof(double*));
	for (i = 0; i < rowSize; i++) {
		xtx[i] = (double*) malloc(rowSize * sizeof(double));
	}
//	printf("i just initialized all the xtx elements\n");

	xtx = multiply(xt, x, colSize, colSize, rowSize);
//	printf("xtx:  \n");
//	print(xtx, colSize, colSize);
//	printf("i just went into multiply\n");
	//is the inverse supposed to be (xtx, rowSize) instead?
	xtx = inverse(xtx, colSize);
//	printf("xtx INVERSE: \n");
//	print(xtx, colSize, colSize);
//	printf("i just went into inverse\n");
	//make xty
	double ** xty;
	xty = (double **) malloc(colSize * sizeof(double*));
	for (i = 0; i < colSize; i++) {
		xty[i] = (double*) malloc (1 * sizeof(double));
	}
//	printf("i just made xty\n");
	xty = multiply(xt, y, colSize, 1, rowSize);
//	printf("xty: \n");
//	print(xty, colSize, 1);
//	printf("i just ran multiply\n");
	//make matrix w. it's size is the same as xty.
	double ** w;
	w = (double **) malloc(colSize * sizeof(double*));
	for (i = 0; i < colSize; i++) {
		w[i] = (double*) malloc (1* sizeof(double));
	}
//	printf("i just made w\n");
	w = multiply(xtx, xty, colSize, 1, colSize );
//	printf("w: \n");
//	print(w, 5, 1);
//	printf("i just ran multiply\n");
//now write the for loop that prints out each of the values from the new test file.
/*
 *the way i'm going to do this is take in the test file. 
 *
 *
 */ 
	FILE *test;
	test = fopen(argv[2], "r");
	if (test == NULL) return 0;

//	double xVal = 0;
	int lines = 0;
	//scan in the first line to see how many rows there are
	fscanf(test, "%d\n", &lines);
	double price = w[0][0];
	double p = 0;
	for (i = 0; i < lines; i++) {
		for (j = 0; j < (colSize-1); j++) {
			fscanf(test, "%lf,", &p);
			price += ((p)* w[j+1][0]);
	
		}
		fscanf(test, "\n");
		printf("%0.0lf\n", price);
		price = w[0][0];
	}





//	printf("this is the vlaue of lines: %d\n", lines);
/*	int z = 0; double sum = 0;
	
	for(z = 0; z != lines; z++) {
		sum = 0;
		for (i = 0; i < colSize; i++) {
			for (j = 0; j < 1; j++) {
				if (i == 0 && j == 0) {
					 sum += w[i][j];	
				} else {i
					fscanf(test, "%lf,", &xVal);
					sum += w[i][j] * xVal;		

				}
			}
		}
		printf("%0.0lf\n", sum);
	}
*/
/*
	while( lines != 0){
		for (i = 0; i < 5; i++) {
			lines--;
			value = 0;
			for (int j = 0; j < 1; j++) {
				if (i ==0) {
					value += w[i][j];
				}else{
					fscanf(test, "%lf,", &xVal);
					value += (xVal * w[i][j]);
				}
			printf("%0.0lf\n", value);	
			}	
		}
	}
*/
return 0;
}
