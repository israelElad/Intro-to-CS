/******************************************
* Student name: Elad Israel
* Student: 313448888
* Course Exercise Group: 06
* Exercise name: Exercise 6
******************************************/

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdarg.h>
#include "person.h"
#include "utils.h"


// max names length allowed
#define MAX_NAME 80
//constant texts for prints
#define NAME_UPPER_MSG "Name:"
#define NAME_LOWER_MSG "name:"
#define ID_MSG "ID:"
#define NUM_OF_KIDS_MSG "Num of kids:"
#define KID_MSG "Kid #"

void CreateNextPerson(Person* this, int isNextNext, ...);
void PrintPerson(Person* this);
void KillNextPerson(Person* this);
Person* SelfDestructPerson(Person* this);

/****************************************************************************************************************
 * Function name: CreatePerson
 * Input: -
 * Output: Person*(NULL if invalid)
 * Function Operation: The function assigns memory for a person and returns the pointer to it.
 ***************************************************************************************************************/
Person* CreatePerson()
{
    //keeps the names received from the user
    char tempName[MAX_NAME]={'\0'};
    //assigns memory for a new person
    Person *person=(Person*)malloc(sizeof(Person));
    //memory allocation failed
    if(person==NULL)
        return NULL;
    //initializes all fields within the new structure(including function pointers).
    InitPersonValues(person);
    //insert person's name to the temp char arr
    printf(NAME_UPPER_MSG"\n");
    scanf("%s",tempName);
    //insert person's name to the dynamically allocated array(+1 due to the '\0' at the end of the array)
    person->name=(char*)malloc((strlen(tempName)+1)*sizeof(char));
    //memory allocation failed
    if(person->name==NULL)
    {
        //free previous allocations
        FreeAll(person);
        return NULL;
    }
    //copy temp arr containing the name to the dynamically allocated array
    strcpy(person->name,tempName);
    //receives ID from the user and inserts it to the person's structure
    printf(ID_MSG"\n");
    scanf("%d",&person->id);
    //receives number of kids from the user and inserts it to the person's structure
    printf(NUM_OF_KIDS_MSG"\n");
    scanf("%d",&person->numOfKids);
    //there is at least one kid
    if(person->numOfKids>0)
    {

        /*
         * dynamically allocated array whose size is determined according to the num of kids user inserted.
         * the array contains pointers to pointers(to the arrays of the kids' names).
         * in order to initialize the array- calloc is being used.
         */
        person->kids=(char**)calloc((unsigned int)(person->numOfKids),sizeof(char*));
        //memory allocation failed
        if(person->kids==NULL)
        {
            //free previous allocations
            FreeAll(person);
            return NULL;
        }
        //receives and inserts the kids names to the person's structure
        for(int i=0;i<person->numOfKids;i++)
        {
            printf(KID_MSG"%d "NAME_LOWER_MSG"\n",i+1);
            scanf("%s",tempName);
            //assigns memory for a new kid and connects the new memory to the kids array
            person->kids[i]=(char*)malloc((strlen(tempName)+1)*sizeof(char));
            //memory allocation failed
            if(person->kids[i]==NULL)
            {
                //free previous allocations
                FreeAll(person);
                return NULL;
            }
            //copy temp arr containing the name to the dynamically allocated array
            strcpy(person->kids[i],tempName);
        }
    }
    //assign the appropriate functions to the pointers of the new person
    person->CreateNext=&CreateNextPerson;
    person->Print=&PrintPerson;
    person->KillNext=&KillNextPerson;
    person->SelfDestruct=&SelfDestructPerson;
    return person;
}

/****************************************************************************************************************
 * Function name: InitPersonValues
 * Input: Person* person
 * Output: -
 * Function Operation: The function initializes all fields within the new structure (including function pointers).
 ****************************************************************************************************************/
void InitPersonValues(Person* person)
{
    person->name=NULL;
    person->id=-1;
    person->numOfKids=0;
    person->kids=NULL;
    person->next=NULL;
    person->Print=NULL;
    person->KillNext=NULL;
    person->SelfDestruct=NULL;
    person->CreateNext=NULL;
}

/****************************************************************************************************************
 * Function name: CreateNextPerson
 * Input: Person* this, int isNextNext, ...(other parameter)
 * Output: -
 * Function Operation: The function assigns memory to a new person(using CreatePerson)
 *                     and places it after the person from whom the function was triggered.
 *                     If there is already a previous person, the function will place it after the
 *                     person that has just been added.
 *                     The second parameter of the function is boolean:
 *                     1:If such a person exists (such a situation will occur when trying
 *                     to add someone who is late to the circle).
 *                     0:If there is no such person (such a situation will occur during
 *                     the construction of the circle),
 *                     then there is an unknown parameter(three points)- when calling the function
 *                     with 3 parameters(1 in the boolean)
 *                     the third will be the person next to the one from whom the function was triggered.
 *                     the new person will be added after the person from whom the function was triggered,
 *                     and before the person in the third parameter.
 ****************************************************************************************************************/
void CreateNextPerson(Person* this, int isNextNext, ...)
{
    //uses CreatePerson to create a new person
    Person *nextPerson=CreatePerson();
    //memory allocation failed
    if(nextPerson==NULL)
        return;
    //there is no person next to this(such a situation will occur during the construction of the circle)
    if(isNextNext==0)
        this->next=nextPerson;
    //there is a person next to this(such a situation will occur when trying to add someone who is late to the circle)
    else
    {
        //var of type "va_list" declaration of "nextOfThis" (will become next of the new one=next next of this)
        va_list nextOfThis;
        //reset "nextOfThis" to the location of the first unknown parameter
        va_start(nextOfThis,isNextNext);
        //inserts new person after this
        this->next=nextPerson;
        //extract variable after last known one and inserts it next to the next of this
        nextPerson->next=va_arg(nextOfThis,Person*);
        //free var of type "va_list"
        va_end(nextOfThis);
    }
}

/**********************************************************************************************
 * Function name: PrintPerson
 * Input: Person* this
 * Output: -
 * Function Operation: The function prints the details of the person received.
 **********************************************************************************************/
void PrintPerson(Person* this)
{
    printf(NAME_UPPER_MSG" %s\n",this->name);
    printf(ID_MSG" %d\n",this->id);
    //goes through kids array and prints each kid's name
    for(int i=0;i<this->numOfKids;i++)
        printf(KID_MSG"%d: %s\n",i+1,this->kids[i]);
}

/**********************************************************************************************
 * Function name: KillNextPerson
 * Input: Person* this
 * Output: -
 * Function Operation: The function kills the person after the person from which the function
 *                     was activated, and releases the memory(using SelfDestructPerson).
 **********************************************************************************************/
void KillNextPerson(Person* this)
{
    //inserts next of the person that is being destroyed to this new next(makes next of next the new next of this)
    this->next=SelfDestructPerson(this->next);
}

/**********************************************************************************************
 * Function name: SelfDestructPerson
 * Input: Person* this
 * Output: Person*
 * Function Operation: The function kills the person from which the function was activated,
 *                     and releases its' memory
 **********************************************************************************************/
Person* SelfDestructPerson(Person* this)
{
    //keeps next of this in order to free it
    Person *next=this->next;
    FreeAll(this);
    return next;
}