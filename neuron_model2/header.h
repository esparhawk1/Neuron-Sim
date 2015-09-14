#include <stdio.h>
#include <time.h>
#include <stdlib.h>

typedef struct neuron{
	int val;
	int dead;
	neuron* next;
}

neuron* create_map();
int bump(neuron* head, int max_pot);











