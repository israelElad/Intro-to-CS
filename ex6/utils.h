/******************************************
* Student name: Elad Israel
* Student: 313448888
* Course Exercise Group: 06
* Exercise name: Exercise 6
******************************************/

#ifndef UTILS_H
#define UTILS_H
//constants that helps understanding the meaning of the user's input
#define NO 0
#define YES 1

#include "person.h"

/****************************************************************************************************************
 * Function name: PrintCircle
 * Input: Person* head
 * Output: -
 * Function Operation: The function prints the whole circle whose head was received.
 ***************************************************************************************************************/
void PrintCircle(Person* head);

//more functions declarations

/****************************************************************************************************************
 * Function name: SearchCircleByID
 * Input: Person* head,int searchID
 * Output: Person*
 * Function Operation: The function searches the whole circle whose head was received,
 *                     for the person whose id was received.
 *                     returns NULL if wasn't found.
 ***************************************************************************************************************/
Person* SearchCircleByID(Person* head,int searchID);

/****************************************************************************************************************
 * Function name: FindPreviousByID
 * Input: Person* head,int thisID
 * Output: Person*
 * Function Operation: The function searches the whole circle whose head was received,
 *                     for the person next to the person whose id was received.
 *                     returns NULL if wasn't found.
 ***************************************************************************************************************/
Person* FindPreviousByID(Person* head,int thisID);

/****************************************************************************************************************
 * Function name: FreeAll
 * Input: Person* this
 * Output: -
 * Function Operation: The function frees the memory of all the details assigned to the person who was received.
 ***************************************************************************************************************/
void FreeAll(Person* this);

#endif
