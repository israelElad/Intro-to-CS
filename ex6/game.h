/******************************************
* Student name: Elad Israel
* Student: 313448888
* Course Exercise Group: 06
* Exercise name: Exercise 6
******************************************/

#ifndef GAME_H
#define GAME_H

#include "person.h"

Person* InitTheHungerGame();
void InsertLaters(Person* head);
Person* RemoveCowards(Person* head);
void LetTheHungerGameBegin(Person* head);

#endif
