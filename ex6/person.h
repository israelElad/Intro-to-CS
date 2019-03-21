/******************************************
* Student name: Elad Israel
* Student: 313448888
* Course Exercise Group: 06
* Exercise name: Exercise 6
******************************************/

/****************************************************************************************************************
 * Function name:
 * Input:
 * Output:
 * Function Operation: The function
 ***************************************************************************************************************/


#ifndef PERSON_H
#define PERSON_H

struct Person {
    char* name;
    int id;
    int numOfKids;
    char** kids;
    struct Person* next;
    void (*Print)(struct Person* this);
    void (*KillNext)(struct Person* this);
    struct Person* (*SelfDestruct)(struct Person* this);
    void (*CreateNext)(struct Person* this, int isNextNext, ...);
};

typedef struct Person Person;

//use only once
Person* CreatePerson();
void InitPersonValues(Person* person);

#endif
