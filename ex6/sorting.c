/******************************************
* Student name: Elad Israel
* Student: 313448888
* Course Exercise Group: 06
* Exercise name: Exercise 6
******************************************/

#include "sorting.h"
#include "utils.h"
#include <string.h>

//constants that are used to determine the sort method
#define BY_ID 1
#define BY_NAME 2

int CheckID(Person* this);
int CheckName(Person* this);
int CountPersonsInCircle(Person* head);
Person* SortCircle(Person *head,int count,int byIDOrName);

/****************************************************************************************************************
 * Function name: SortCircleByID
 * Input: Person* head
 * Output: Person*
 * Function Operation: The function receives a circle and sort it by the identification numbers of the people in it.
 *                     (calls SortCircle with the head, count of the persons in the circle, and BY_ID so that
 *                     SortCircle will know to sort it by ID).
                       The functions return a pointer to the top of the new circle.
 ***************************************************************************************************************/
Person* SortCircleByID(Person* head)
{
    return SortCircle(head,CountPersonsInCircle(head),BY_ID);
}

/****************************************************************************************************************
 * Function name: SortCircleByName
 * Input: Person* head
 * Output: Person*
 * Function Operation: The function receives a circle and sort it by the names of the people in it.
 *                     (calls SortCircle with the head, count of the persons in the circle, and BY_NAME so that
 *                     SortCircle will know to sort it by name).
                       The functions return a pointer to the top of the new circle.
 ***************************************************************************************************************/
Person* SortCircleByName(Person* head)
{
    return SortCircle(head,CountPersonsInCircle(head),BY_NAME);
}

/****************************************************************************************************************
 * Function name: CountPersonsInCircle
 * Input: Person* head
 * Output: int
 * Function Operation: The function receives a circle and returns the count of how many people are in it.
 ***************************************************************************************************************/
int CountPersonsInCircle(Person* head)
{
    //keeps head in a different pointer in order to avoid advancing the real head
    Person *temp=head;
    int count=0;
    while(temp!=NULL)
    {
        count++;
        //advances temp
        temp=temp->next;
    }
    return count;
}

/****************************************************************************************************************
 * Function name: SortCircle
 * Input: Person *head,int count,int byIDOrName
 * Output: Person*
 * Function Operation: The function receives a circle and sort it by the names of the people in it
 *                     or their identification numbers.
 *                     (receives its' head, count of the persons in the circle, and BY_NAME or BY_ID
 *                     according to the sort method required.
                       The functions return a pointer to the top of the new circle.
 ***************************************************************************************************************/
Person* SortCircle(Person *head,int count,int byIDOrName)
{
    int i,j;
    //keeps head in order to avoid advancing the real head
    Person *this=head;
    //pointer that goes through the entire circle
    Person *temp;
    //initializes pointer to function
    int (*byIDOrNamePtr)(Person*)=NULL;
    //the pointer points to CheckID if sort by ID is required(in order to check the appropriate condition later)
    if(byIDOrName==BY_ID)
        byIDOrNamePtr=&CheckID;
    //the pointer points to CheckName if sort by name is required(in order to check the appropriate condition later)
    if(byIDOrName==BY_NAME)
        byIDOrNamePtr=&CheckName;

    /*
     * goes through the circle almost twice:
     * first loop: goes through every person in the circle and activates the second loop on him.
     * in the second loop: goes through the circle with a specific person and advances it between the next person and
     * the one after him if he is bigger. count-1-i times, because in each iteration of the first loop,
     * the biggest value is sorted to its right place on the end of the circle.
     * Thus, there is no point to searching till the end, as the end of the circle is already sorted.
     * then a condition is checked(if bigger)- the condition activates CheckID/CheckName according to
     * what is assigned in the pointer(according to the sort method).
     */
    for(i=0;i<count-1;i++)
    {
        for(j=0;j<count-1-i;j++)
        {
            //condition explained above returns YES:bigger- swap is required
            if((*byIDOrNamePtr)(this)==YES)
            {
                //finds previous in order to connect it after the swap
                Person *previous=FindPreviousByID(head,this->id);
                //swapping the head
                if(previous==NULL)
                {
                    //keeps next of this value
                    temp=this->next;
                    //set next of this to be the next of the next of this(last)
                    this->next=this->next->next;
                    //set next of temp to this
                    temp->next=this;
                    //temp is the new head
                    head=temp;
                }
                //swapping person in the middle or tail
                else
                {
                    //keeps "this" value
                    temp = this;
                    //set next of previous to next of this
                    previous->next = this->next;
                    //set next of this to the next of the next of this(last)
                    this->next = this->next->next;
                    //set next of next of previous to temp(original this)
                    previous->next->next = temp;
                }
            }
            else
                //condition explained above returns NO:smaller- swap is not required. advance this.
                this=this->next;
        }
        //assign head into this so that it will go through the circle again
        this=head;
    }
    return head;
}

/****************************************************************************************************************
 * Function name: CheckID
 * Input: Person* this
 * Output: int
 * Function Operation: The function checks whether the ID of the person from whom the function was triggered,
 *                     is bigger then the next person, and returns the appropriate answer.
 ***************************************************************************************************************/
int CheckID(Person* this)
{
    if(this->id > this->next->id)
        return YES;
    return NO;
}

/****************************************************************************************************************
 * Function name: CheckName
 * Input: Person* this
 * Output: int
 * Function Operation: The function checks whether the name of the person from whom the function was triggered,
 *                     is bigger lexicographically then the next person, and returns the appropriate answer.
 ***************************************************************************************************************/
int CheckName(Person* this)
{
    if(strcmp(this->name,this->next->name)>0)
        return YES;
    return NO;
}