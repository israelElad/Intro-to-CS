/******************************************
* Student name: Elad Israel
* Student: 313448888
* Course Exercise Group: 06
* Exercise name: Exercise 6
******************************************/

#include <stdio.h>
#include "utils.h"
#include <malloc.h>

//separation line printed between the details of each person
#define SEP_LINE_MSG "----------"

/****************************************************************************************************************
 * Function name: PrintCircle
 * Input: Person* head
 * Output: -
 * Function Operation: The function prints the whole circle whose head was received.
 ***************************************************************************************************************/
void PrintCircle(Person* head)
{
    //circle is empty
    if(head==NULL)
        return;
    //keeps the head to avoid advancing the real head
    Person *printTemp=head;
    printf(SEP_LINE_MSG"\n");
    //keep advancing the temp until reaches the end of the circle
    while(printTemp!=NULL)
    {
        //use the print function using the pointer in each person
        printTemp->Print(printTemp);
        printTemp=printTemp->next;
        printf(SEP_LINE_MSG"\n");
    }
}

/****************************************************************************************************************
 * Function name: SearchCircleByID
 * Input: Person* head,int searchID
 * Output: Person*
 * Function Operation: The function searches the whole circle whose head was received,
 *                     for the person whose id was received.
 *                     returns NULL if wasn't found.
 ***************************************************************************************************************/
Person* SearchCircleByID(Person* head,int searchID)
{
    //keeps the head to avoid advancing the real head
    Person *temp=head;
    //keep advancing the temp until reaches the end of the circle
    while(temp!=NULL)
    {
        //if id was found in the temp- this is the person whose id was received
        if(temp->id==searchID)
            return temp;
        temp=temp->next;
    }
    //wasn't found
    return NULL;
}

/****************************************************************************************************************
 * Function name: FindPreviousByID
 * Input: Person* head,int thisID
 * Output: Person*
 * Function Operation: The function searches the whole circle whose head was received,
 *                     for the person next to the person whose id was received.
 *                     returns NULL if wasn't found.
 ***************************************************************************************************************/
Person* FindPreviousByID(Person* head,int thisID)
{
    //keeps the head to avoid advancing the real head
    Person *temp=head;
    //keep advancing the temp until reaches the end of the circle
    while(temp->next!=NULL)
    {
        //if id was found in the next person- this is the previous to the one whose id was received
        if(temp->next->id==thisID)
            return temp;
        temp=temp->next;
    }
    //wasn't found(ID belong to head)
    return NULL;
}

/****************************************************************************************************************
 * Function name: FreeAll
 * Input: Person* this
 * Output: -
 * Function Operation: The function frees the memory of all the details assigned to the person who was received.
 ***************************************************************************************************************/
void FreeAll(Person* this)
{
    //goes through the entire array of the kids' names and frees them
    for(int i=0;i<this->numOfKids;i++)
        free(this->kids[i]);
    //frees the array of pointers to pointers
    free(this->kids);
    //frees the person's name
    free(this->name);
    //frees the person
    free(this);
}