//==============================================================================
//Main: solver
//Author: Jordan Bergmann
//
//Description: Sudokus are entered, line by line, and the program will output
//	a solution.
//==============================================================================

#include<stdio.h>
#include<time.h>

//Function prototypes
void getSudoku(int sudoku[9][9], FILE* file);
void printSudoku(int sudoku[9][9], int numbered);
int checkSudoku(int sudoku[9][9], int isFull, int verbose);
void playSudoku(int sudoku[9][9]);
void solveSudoku(int sudoku[9][9]);
int checkCell(int sudoku[9][9], int cellX, int cellY, int num);
int checkRow(int sudoku[9][9], int row, int num);
int checkCol(int sudoku[9][9], int col, int num);
int recursiveSolve(int sudoku[9][9], int verbose);


int main(int argc, const char* argv[]){

	int sudoku[9][9] = {0};
	char originalMap [9][9] = {0}; //1's for original numbers.
	char input[100] = {0};
	FILE* file;

	//Check for file.
	if(argc >= 2){
		file = fopen(argv[1], "r");
	}
	else{
		file = 0;
	}

	//Fetch a sudoku from file or manual input.
	getSudoku(sudoku, file);
	if(file != 0){
		fclose(file);
	}

	//Print fetched sudoku.
	printSudoku(sudoku, 0);

	//Check sudoku validity.
	(checkSudoku(sudoku, 0, 1));

	//Ask for mode.
	for(int x = 0; x == 0; ){
		printf("Type 'p' to play, 's' to auto solve ('v' for verbose version), or 'q' to quit.\n");
		fgets(input, 100, stdin);

		//Check input
		if(input[0] == 'p'){
			x = 1;
			playSudoku(sudoku);
		}
		else if(input[0] == 's'){
			x = 1;
			recursiveSolve(sudoku, 0);
		}
		else if(input[0] == 'v'){
			x = 1;
			recursiveSolve(sudoku, 1);
		}
		else if(input[0] == 'q'){
			return 0;
		}
		else{
			printf("Invalid input, please try again.\n");
		}
	}

	return 0;

}

//==============================================================================
//Function: getSudoku
//Description: Asks for an unsolved sudoku, line by line, in console.
//
//Argument list:
//	(int[][])sudoku: Sudoku file to fill.
//	(FILE* file): Opened file to read sudoku from. 0 if not using file.
//
//Return(VOID): N/A
//==============================================================================
void getSudoku(int sudoku[9][9], FILE* file){

	char input[100] = {0};
	int x = 0;
	
	if(file == 0){ //Ask for input.
	printf("Please enter each line of the sudoku, pressing enter after each line.\n");
	printf("Use '_' or '0' for blanks, spaces will be ignored.\n");
	}

	for(int y = 0; y <= 8; y++){
		if(file == 0){ //If no file provided.
			fgets(input , 100, stdin);
		}
		else{ //File provided, read from file.
			fgets(input , 100, file);
		}
		x = 0; //Reset x-axis counter.

		for(int n = 0; n < 100; n++){
			if(input[n] == '\0'){ //If end of string
				if(file == 0){
					y--;
					printf("this line was invalid, please try again.\n");
					n = 200;
				}
				else{
					printf("File was invalid, switching to manual input.\n\n");
					getSudoku(sudoku, 0);
					return;
				}
			}
			else if((input[n] == '_') || (input[n] == '0')){ //If blank space
				sudoku[x][y] = 0;
				x++;
			}
			else if(input[n] >= '0' && input[n] <= '9'){ //If number
				sudoku[x][y] = input[n] - 48;
				x++;
			}

			if(x > 8){ //If done
				n = 200;
			}
			//Done with line
		}
	}
	
	return;

}

//==============================================================================
//Function: printSudoku
//Description: Prints a sudoku to console.
//
//Argument list:
//	(int[])sudoku: Sudoku to print out.
//	(int)numbered: If true, print row/column numbers.
//
//Return(VOID): N/A
//==============================================================================
void printSudoku(int sudoku[9][9], int numbered){

	for(int y = 0; y <= 8; y++){

		if(y == 0){ //Print top horizontal line if applicable.
			if(numbered){ //If numbered, print top numbers
				printf("     1 2 3   4 5 6   7 8 9\n");
			}
			if(numbered){
				printf("   ");
			}
			printf("-------------------------\n");
		}

		if(numbered){
			printf(" %d ", y+1);
		}

		for(int x = 0; x <= 8; x++){
			if(x == 0){ //Print vertical line if applicable.
				printf("| ");
			}

			if(sudoku[x][y] == 0){ //Print space or number.
				printf("_ ");
			}
			else{
				printf("%d ", sudoku[x][y]);
			}

			if((x + 1) % 3 == 0){ //Print vertical line if applicable.
				printf("| ");
			}

			if((x + 1) % 9 == 0){
				printf("\n");
			}

		}
		if((y + 1) % 3 == 0){ //Print horizontal line if applicable.
			if(numbered){
				printf("   ");
			}
			printf("-------------------------\n");
		}
	}
}

//==============================================================================
//Function: checkSudoku
//Description: Check if sudoku is correctly solved.
//
//Argument list:
//	(int[])sudoku: Sudoku grid to check.
//	(int)isFull: 0 if checking validity of unfilled sudoku.
//	(int)verbose: 1 to print out if the sudoku is valid.
//
//Return(int):
//	True: if(isFull == 0) Sudoku is valid. if(isFull == 1) Sudoku is correct.
//	False Sudoku is incorrect or invalid.
//==============================================================================
int checkSudoku(int sudoku[9][9], int isFull, int verbose){

	int checkLine[9]; //Fill to check off numbers in row/column/cell.
	int rowVal = 1;
	int colVal = 1;
	int celVal = 1;

	//Check rows.
	for(int y = 0; y <= 8; y++){

		//Reset checkLine.
		for(int n = 0; n <= 8; n++){
			checkLine[n] = 0;
		}

		for(int n = 1; n <= 9; n++){

			checkLine[n-1] = checkRow(sudoku, y, n);
			if(checkLine[n-1] > 1){ //If too many of number in row.
				rowVal = 0;
			}
			else if((checkLine[n-1] == 0) && (isFull == 1)){ //If none of that number and I care.
				rowVal = 0;
			}
		}
	}
	if(verbose){
		if(rowVal){
			printf("Rows OK.\n");
		}
		else{
			printf("Row invalid.\n");
		}
	}

	//Check columns.
	for(int x = 0; x <= 8; x++){

		//Reset checkLine.
		for(int n = 0; n <= 8; n++){
			checkLine[n] = 0;
		}

		for(int n = 1; n <= 9; n++){

			checkLine[n-1] = checkCol(sudoku, x, n);
			if(checkLine[n-1] > 1){ //If too many of number in column.
				colVal = 0;
			}
			else if((checkLine[n-1] == 0) && (isFull == 1)){ //If none of that number and I care.
				colVal = 0;
			}
		}
	}
	if(verbose){
		if(colVal){
			printf("Columns OK.\n");
		}
		else{
			printf("Column invalid.\n");
		}
	}

	//Check cells.
	for(int y = 1; y <= 3; y++){
		for(int x = 1; x <= 3; x++){
			
			//Reset checkLine.
			for(int n = 0; n <= 8; n++){
				checkLine[n] = 0;
			}

			for(int n = 1; n <= 9; n++){ //Try each number
				checkLine[n-1] = checkCell(sudoku, x, y, n);
				if(checkLine[n-1] > 1){ //If too many of number in cell.
					celVal = 0;
				}
				else if((checkLine[n-1] == 0) && (isFull == 1)){ //If none of that number.
					celVal = 0;
				}


			}
		}
	}

	if(verbose){
		if(celVal){
			printf("Cells OK.\n");
		}
		else{
			printf("Cell invalid.\n");
		}
	}

	if(verbose){
		if(rowVal && colVal && celVal){
			printf("\nSudoku is valid\n");
			return 1;
		}
		else{
			printf("\nSudoku is invalid\n");
			return 0;
		}
	}

	else if(rowVal && colVal && celVal){
		return 1;
	}
	else{
		return 0;
	}
}


//==============================================================================
//Function: playSudoku
//Description: Lets user enter numbers manually into the sudoku, checking for
//	correctness.
//
//Argument list:
//	(int[])sudoku: Sudoku to play.
//
//Return(VOID): N/A
//==============================================================================
void playSudoku(int sudoku[9][9]){

	//Coordinates for entry.
	int xCo = 0;
	int yCo = 0;

	char input[100] = {0};

	printf("\n\n\n\n\n\n\n\n\n\n\n\n");
	printSudoku(sudoku, 1);
	printf("To enter a number, type the row number, the column number,\n");
	printf("and the number you want to enter all on one line.\n");
	printf("To auto solve the sudoku type 's'\n");
	printf("To quit type 'q'\n");

	while(checkSudoku(sudoku, 1, 0) == 0){
		fgets(input , 100, stdin);
		if(input[0] == 's'){ //Solve
			recursiveSolve(sudoku, 0);
			return;
		}
		else if(input[0] >= '0' && input[0] <= '9'){ //Coordinate
			printf("\n\n\n\n\n\n\n\n\n\n\n\n");
			xCo = input[0] - 48;
			for(int x = 1; x <= 100; x++){
				if(input[x] >= '0' && input[x] <= '9'){
					yCo = input[x] - 48;
				
					for(int y = x+1; y <= 100; y++){
						if(input[y] >= '0' && input[y] <= '9'){
							sudoku[xCo-1][yCo-1] = input[y] - 48;
							x = 200;
							y = 200;
						}
					}
				}
			}
			printSudoku(sudoku, 1);
			checkSudoku(sudoku, 0, 1);

		}
		else if(input[0] == 'q'){
			return;
		}
		else{
			printf("Invalid input, please try again.\n");
		}
	}
}

//==============================================================================
//Function: solveSudoku
//Description: Solves an incomplete sudoku.
//
//Argument list:
//	(int[])sudoku: Sudoku to print out.
//
//Return(VOID): N/A
//==============================================================================
/*void solveSudoku(int sudoku[9][9]){

	int valList[9]; //List valid numbers.
	int valCnt; //Number of valid numbers.
	int exclusive;

	while(checkSudoku(sudoku, 1, 0) == 0){
		//Find empty cell
		for(int y = 0; y <= 8; y++){
			for(int x = 0; x <= 8; x++){
				if(sudoku[x][y] == 0){

					//Found empty cell, check valid numbers.
					for(int n = 0; n <= 8; n++){//Reset valList and valCnt.
						valList[n] = 0;
					}
					valCnt = 0;

					for(int n = 1; n <= 9; n++){
						sudoku[x][y] = n; //Try number.
						if(checkSudoku(sudoku, 0, 0)){ //Check if valid.
							valList[valCnt] = n;
							valCnt++;
						}
						valCnt--; //Set valCnt to final number of valid numbers.
					}
					sudoku[x][y] = 0; //Reset blank.

					for(int i = 0; i <= valCnt; i++){ //TEST PRINT
						printf("%d\n", valList[valCnt]);
					}

					//Check each valid number for if it's the only valid location.
					for(int n = 0; n <= valCnt; n++){

						exclusive = 0;

						if((y+1) % 3 == 1){ //Check row 1 of cell.
							if((checkRow(sudoku, y+1, valList[valCnt]) || sudoku[x][y+1] != 0) && (checkRow(sudoku, y+2, valList[valCnt]) || sudoku[x][y+2] != 0)){
								exclusive = 1;
							}
						}
						else if((y+1) % 3 == 2){ //Check row 2 of cell.
							if((checkRow(sudoku, y-1, valList[valCnt]) || sudoku[x][y-1] != 0) && (checkRow(sudoku, y+1, valList[valCnt]) || sudoku[x][y+1] != 0)){
								exclusive = 1;
							}
						}
						else if((y+1) % 3 == 0){ //Check row 3 of cell.
							if((checkRow(sudoku, y+1, valList[valCnt]) || sudoku[x][y-1] != 0) && (checkRow(sudoku, y+2, valList[valCnt]) || sudoku[x][y-2] != 0)){
								exclusive = 1;
							}
						}

						if(exclusive == 1){ //Row exclusive, check columns.
							exclusive = 0;
							if((x+1) % 3 == 1){ //Check column 1 of cell.
								if((checkCol(sudoku, x+1, valList[valCnt]) || sudoku[x+1][y] != 0) && (checkCol(sudoku, x+2, valList[valCnt]) || sudoku[x+2][y] != 0)){
									exclusive = 1;
								}
							}
							else if((x+1) % 3 == 2){ //Check column 2 of cell.
								if((checkCol(sudoku, x-1, valList[valCnt]) || sudoku[x-1][y] != 0) && (checkCol(sudoku, x+1, valList[valCnt]) || sudoku[x+1][y] != 0)){
									exclusive = 1;
								}
							}
							else if((x+1) % 3 == 0){ //Check column 3 of cell.
								if((checkCol(sudoku, x+1, valList[valCnt]) || sudoku[x-1][y] != 0) && (checkCol(sudoku, x+2, valList[valCnt]) || sudoku[x-2][y] != 0)){
									exclusive = 1;
								}
							}
						}

						if(exclusive == 1){ //Row and column exclusive, check cells.
							exclusive = 0;
							if(x / 3 == 0){ //Left
								if(y / 3 == 0){ //Top
									if(checkCell(sudoku, 2, 1, valList[valCnt]) && checkCell(sudoku, 3, 1, valList[valCnt])){
										exclusive = 1;
									}
									else if(checkCell(sudoku, 1, 2, valList[valCnt]) && checkCell(sudoku, 1, 3, valList[valCnt])){
										exclusive = 1;
									}
								}
								else if(y / 3 == 1){ //Middle
									if(checkCell(sudoku, 2, 2, valList[valCnt]) && checkCell(sudoku, 3, 2, valList[valCnt])){
										exclusive = 1;
									}
									else if(checkCell(sudoku, 1, 1, valList[valCnt]) && checkCell(sudoku, 1, 3, valList[valCnt])){
										exclusive = 1;
									}
								}
								else{ //Bottom
									if(checkCell(sudoku, 2, 3, valList[valCnt]) && checkCell(sudoku, 3, 3, valList[valCnt])){
										exclusive = 1;
									}
									else if(checkCell(sudoku, 1, 1, valList[valCnt]) && checkCell(sudoku, 1, 2, valList[valCnt])){
										exclusive = 1;
									}
								}
							}
							else if(x / 3 == 1){ //Middle
								if(y / 3 == 0){ //Top
									if(checkCell(sudoku, 1, 1, valList[valCnt]) && checkCell(sudoku, 3, 1, valList[valCnt])){
										exclusive = 1;
									}
									else if(checkCell(sudoku, 2, 2, valList[valCnt]) && checkCell(sudoku, 2, 3, valList[valCnt])){
										exclusive = 1;
									}
								}
								else if(y / 3 == 1){ //Middle
									if(checkCell(sudoku, 1, 2, valList[valCnt]) && checkCell(sudoku, 3, 2, valList[valCnt])){
										exclusive = 1;
									}
									else if(checkCell(sudoku, 2, 1, valList[valCnt]) && checkCell(sudoku, 2, 3, valList[valCnt])){
										exclusive = 1;
									}
								}
								else{ //Bottom
									if(checkCell(sudoku, 2, 1, valList[valCnt]) && checkCell(sudoku, 2, 2, valList[valCnt])){
										exclusive = 1;
									}
									else if(checkCell(sudoku, 1, 3, valList[valCnt]) && checkCell(sudoku, 3, 3, valList[valCnt])){
										exclusive = 1;
									}
								}
							}
							else{ //Right
								if(y / 3 == 0){ //Top
									if(checkCell(sudoku, 1, 1, valList[valCnt]) && checkCell(sudoku, 2, 1, valList[valCnt])){
										exclusive = 1;
									}
									else if(checkCell(sudoku, 3, 2, valList[valCnt]) && checkCell(sudoku, 3, 3, valList[valCnt])){
										exclusive = 1;
									}
								}
								else if(y / 3 == 1){ //Middle
									if(checkCell(sudoku, 1, 2, valList[valCnt]) && checkCell(sudoku, 2, 2, valList[valCnt])){
										exclusive = 1;
									}
									else if(checkCell(sudoku, 3, 1, valList[valCnt]) && checkCell(sudoku, 3, 3, valList[valCnt])){
										exclusive = 1;
									}
								}
								else{ //Bottom
									if(checkCell(sudoku, 1, 3, valList[valCnt]) && checkCell(sudoku, 2, 3, valList[valCnt])){
										exclusive = 1;
									}
									else if(checkCell(sudoku, 3, 1, valList[valCnt]) && checkCell(sudoku, 3, 2, valList[valCnt])){
										exclusive = 1;
									}
								}
							}
						}
						if(exclusive == 1){ //Number is exclusive, apply number.
							sudoku[x][y] = valList[valCnt];
							n = valCnt;
						}
					}
					printSudoku(sudoku, 0);
				}
			}
		}
		
	}
	printSudoku(sudoku, 0);
}*/

//==============================================================================
//Function: checkRow
//Description: Checks a row for a given number.
//
//Argument list:
//	(int[])sudoku: Sudoku to check.
//	(int)row: Row number to check (1-9).
//	(int)num: Number to check for.
//
//Return(int): How many of the given number are in the selected row.
//==============================================================================
int checkRow(int sudoku[9][9], int row, int num){

	int counter = 0;

	for(int x = 0; x <= 8; x++){
		if(sudoku[x][row] == num){
			counter++;
		}
	}
	return counter;
}

//==============================================================================
//Function: checkCol
//Description: Checks a column for a given number.
//
//Argument list:
//	(int[])sudoku: Sudoku to check.
//	(int)col: Column number to check (1-9).
//	(int)num: Number to check for.
//
//Return(int): How many of the given number are in the selected column.
//==============================================================================
int checkCol(int sudoku[9][9], int col, int num){

	int counter = 0;

	for(int y = 0; y <= 8; y++){
		if(sudoku[col][y] == num){
			counter++;
		}
	}
	return counter;

}

//==============================================================================
//Function: checkCell
//Description: Checks a Cell for a given number.
//
//Argument list:
//	(int[])sudoku: Sudoku to check.
//	(int)cellX: X-coordinate of cell to check. (1-3)
//	(int)cellY: Y-coordinate of cell to check. (1-3)
//
//Return(int): How many of the given number are in the selected cell.
//==============================================================================
int checkCell(int sudoku[9][9], int cellX, int cellY, int num){

	//Lower and upper limits for each cell.
		int xL;
		int yL;
		int xU;
		int yU;
		int counter = 0;

		if(cellX == 1){
			xL = 0;
			xU = 2;
		}
		else if(cellX == 2){
			xL = 3;
			xU = 5;
		}
		else{
			xL = 6;
			xU = 8;
		}

		if(cellY == 1){
			yL = 0;
			yU = 2;
		}
		else if(cellY == 2){
			yL = 3;
			yU = 5;
		}
		else{
			yL = 6;
			yU = 8;
		}

	for(int y = yL; y <= yU; y++){
		for(int x = xL; x <= xU; x++){
			if(sudoku[x][y] == num){
				counter++;
			}
		}
	}
	return counter;
}

//==============================================================================
//Function: recursiveSolve
//Description: Solves an incomplete sudoku using recursion.
//
//Argument list:
//	(int[])sudoku: Sudoku to print out.
//	(int)verbose: If true, print out solve progress.
//
//Return(int):
//	True: Success.
//	False: Branch failed.
//==============================================================================
int recursiveSolve(int sudoku[9][9], int verbose){

	//Find empty cell
	for(int y = 0; y <= 8; y++){
		for(int x = 0; x <= 8; x++){
			if(sudoku[x][y] == 0){
				//Found empty space, try numbers.
				for(int n = 9; n >= 0; n--){
					sudoku[x][y] = n;
					if(n == 0){ //Branch failed, return 0.
						return 0;
					}
					else if(checkSudoku(sudoku, 1, 0)){ //Check if done.
						printf("Found solution!\n");
						printSudoku(sudoku, 0);
						return 1;
					}
					else if(checkSudoku(sudoku, 0, 0)){ //Check if still valid.
						if(x == 8){ //If end of row.
							
							if(recursiveSolve(sudoku, verbose)){ //Valid number, try next.
								return 1;
							}
						}
						else{
							if(verbose){
								printSudoku(sudoku, 0);
								struct timespec tim, tim2;
								tim.tv_sec = 0;
								tim.tv_nsec = 100000000;
								nanosleep(&tim , &tim2);
							}
							if(recursiveSolve(sudoku, verbose)){ //Valid number, try next.
								return 1;
							}
						}
					}
				}
			}
		}
	}
	printf("Error\n");
}


