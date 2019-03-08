
#include <stdio.h>
#include <stdlib.h>
#include <sys/wRandom.h>

void main(int argc, const char* argv[]){

	const int WORLD_X = 100;
	const int WORLD_Y = 100;
	const int ROUNDS = 100;
	const int RANGE = 10;

	int world[WORLD_X][WORLD_Y];

	unsigned char wRand[WORLD_X * WORLD_Y] = {0};
	unsigned char rRand[ROUNDS * 4] = {0};

	//Get random numbers.
	getrandom(wRand, WORLD_X * WORLD_Y, 0);

	//Populate world.
	for(int y = 0; x <= WORLD_Y -1; y++){
		for(int x = 0; x <= WORLD_X -1; x++){
			world[x][y] = ((wRand[x*y] % (RANGE - 1)) + 1); //TEMPORARY COUNTER
		}
	}

	//Print world.
	for(int y = 0; x <= WORLD_Y -1; y++){
		for(int x = 0; x <= WORLD_X -1; x++){
			printf("%d", world[x][y]);
			if(y == WORLD_Y -1){
				printf("\n");
			}
		}
	}

	//Get random numbers.
	getrandom(rRand, RANDOM * 4, 0);

	//Do rounds of interation.
	for(int n = 0; n <= rounds * 4; n+=4){
		for(int y = 0; x <= WORLD_Y -1; y++){
			for(int x = 0; x <= WORLD_X -1; x++){
				
				//Neighbor coordinates.
				int up[2];
				int down[2];
				int left[2];
				int right[2];

				//Set neighbor coordinates.
				//Defaults.
				up[0] = x;
				down[0] = x;
				left[0] = x - 1;
				right[0] = x + 1;
				up[1] = y + 1;
				down[1] = y - 1;
				left[1] = y;
				right[1] = y;

				//Special cases.
				if(y == WORLD_Y -1){ //At top edge.
					down[1] = y - 1;
				}
				else if(y == 0){ //At bottom edge.
					down[1] = WORLD_Y;
				}

				if(x == WORLD_X -1){ //At right edge.
					right[0] = WORLD_X;
				}
				else if(x == 0){ //At left edge.
					left[0] = 0;
				}

				//Per cell, try interaction.
				if(((rRand[n] +0 % 100) + 1) >= (RANGE + 1 - abs(world[x][y] - world[up[0]][up[1]]))){

				}
				if(((rRand[n] +1 % 100) + 1) >= (RANGE + 1 - abs(world[x][y] - world[down[0]][down[1]]))){

				}
				if(((rRand[n] +2 % 100) + 1) >= (RANGE + 1 - abs(world[x][y] - world[left[0]][left[1]]))){

				}
				if(((rRand[n] +3 % 100) + 1) >= (RANGE + 1 - abs(world[x][y] - world[right[0]][right[1]]))){

				}


			}
		}
	}


	}

	//Print world.
	for(int y = 0; x <= WORLD_Y -1; y++){
		for(int x = 0; x <= WORLD_X -1; x++){
			printf("%d", world[x][y]);
			if(y == WORLD_Y -1){
				printf("\n");
			}
		}
	}

}