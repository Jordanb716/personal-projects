//==============================================================================
// Header: Populations
// Author: Jordan Bergmann
//
// Description: Holds population data for different regions
//==============================================================================


#ifndef popsDoc
#define popsDoc

struct population
{
	int dwarves;
	int elves;
	int gnomes;
	int halfelves;
	int halflings;
	int halforcs;
	int humans;
	int others;
	int total;
};

//Populations

/*
struct example;
example.dwarves = ;
example.elves = ;
example.gnomes = ;
example.halfelves = ;
example.halflings = ;
example.halforcs = ;
example.humans = ;
example.others = ;
example.total = example.dwarves + example.elves + example.gnomes
	+ example.halfelves + example.halflings + example.halforcs
	+ example.humans + example.others;
*/

struct population avistan;
avistan.dwarves = 113358;
avistan.elves = 73235;
avistan.gnomes = 47597;
avistan.halfelves = 46569;
avistan.halflings = 83368;
avistan.halforcs = 22773;
avistan.humans = 1181111;
avistan.others = 0;
avistan.total = avistan.dwarves + avistan.elves + avistan.gnomes
	+ avistan.halfelves + avistan.halflings + avistan.halforcs
	+ avistan.humans + avistan.others;


struct region
{
	char name[100];
	struct population pops;
	int* parent;
	int* children[100];
}









#endif