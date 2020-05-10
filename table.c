// implamentation of table 

#include "table.h"
#include <string.h>

Player newPlayer(char *name, int chips) {
	Player p = malloc(sizeof(*p));

	if (p == NULL) {
		fprintf(stderr, "couldn't allocate memory for player\n");
		exit(EXIT_FAILURE);
	}

	p->name = malloc(sizeof(name));
	p->name = stpcpy(p->name, name);
	p->chips = chips;
	p->next = NULL;
	p->hand = newEmptyDeck();
	p->pos = -1;

	return p;
}


void freePlayer(Player p) {

	return;
}