
#include <stdio.h>
#include <stdlib.h>
#include <sys/random.h>

void roll(int*);

void main(int argc, const char* argv[]){

	//Variables
	char numChars;

	int STR[5] = {0};
	int DEX[5] = {0};
	int CON[5] = {0};
	int INT[5] = {0};
	int WIS[5] = {0};
	int CHA[5] = {0};

	if(argc == 2){
		numChars = atoi(argv[1]);
	}
	else{
		numChars = 1;
	}

	for(int x = 0; x < numChars; x++){

		roll(STR);
		roll(DEX);
		roll(CON);
		roll(INT);
		roll(WIS);
		roll(CHA);

		printf("Character #%d:\n", x + 1);

		printf("STR: %d (%d, %d, %d, %d)\n", STR[0], STR[1], STR[2], STR[3], STR[4]);
		printf("DEX: %d (%d, %d, %d, %d)\n", DEX[0], DEX[1], DEX[2], DEX[3], DEX[4]);
		printf("CON: %d (%d, %d, %d, %d)\n", CON[0], CON[1], CON[2], CON[3], CON[4]);
		printf("INT: %d (%d, %d, %d, %d)\n", INT[0], INT[1], INT[2], INT[3], INT[4]);
		printf("WIS: %d (%d, %d, %d, %d)\n", WIS[0], WIS[1], WIS[2], WIS[3], WIS[4]);
		printf("CHA: %d (%d, %d, %d, %d)\n", CHA[0], CHA[1], CHA[2], CHA[3], CHA[4]);
		printf("\n");

	}

}

void roll(int stat[5]){

	//int stat[5] = {0};
	unsigned char rand[4] = {0};

	if(getrandom(rand, 4, 0) == 4){
		//Yay
	}
	else{
		printf("poop");
		return;
	}

	stat[1] = ((rand[0] % 6) + 1);
	stat[2] = ((rand[1] % 6) + 1);
	stat[3] = ((rand[2] % 6) + 1);
	stat[4] = ((rand[3] % 6) + 1);

	stat[0] = stat[1] + stat[2] + stat[3] + stat[4];

	if(stat[1] <= stat[2] && stat[1] <= stat[3] && stat[1] <= stat[4]){
		stat[0] -= stat[1];
	}
	else if(stat[2] <= stat[1] && stat[2] <= stat[3] && stat[2] <= stat[4]){
		stat[0] -= stat[2];
	}
	else if(stat[3] <= stat[1] && stat[3] <= stat[2] && stat[3] <= stat[4]){
		stat[0] -= stat[3];
	}
	else if(stat[4] <= stat[1] && stat[4] <= stat[2] && stat[4] <= stat[3]){
		stat[0] -= stat[4];
	}

	return;

}