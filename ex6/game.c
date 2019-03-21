/******************************************
* Student name: Elad Israel
* Student: 313448888
* Course Exercise Group: 06
* Exercise name: Exercise 6
******************************************/

#include "game.h"
#include "utils.h"
#include <stdio.h>

//constant texts for prints
#define ADD_PERSON_MSG "Add a person to the game? (0|1)"
#define LATE_MSG "Are you late? (0|1)"
#define BF_ID_MSG "Insert your best friend's ID:"
#define ID_NOT_FOUND "No Such ID:"
#define COWARD_MSG "Is there a coward in here? (0|1)"
#define COWARD_ID_MSG "Insert your ID, you, lame pudding-heart coward:"
#define COWARD_DESTRUCT_MSG "Let the world know that you are a coward,"
#define STAYING_ALIVE_A "Ah, ha, ha, ha, stayin' alive, stayin' alive! Ah, ha, ha, ha, \""
#define STAYING_ALIVE_B "\" stayin' alive!"

void DestroyCircle(Person* head);

/****************************************************************************************************************
 * Function name: InitTheHungerGame
 * Input: -
 * Output: Person*
 * Function Operation: The function initializes the game. After calling the function a pointer will be returned
 *                     to the first person from a dynamically assigned circle.
 *                     In case of failure while creating the circle,
 *                     or if no people were created at all, the function will return NULL.
 ***************************************************************************************************************/
Person* InitTheHungerGame()
{
    //keeps user decision whether to add a new person or not
    int addOrQuit;
    //points to the head of the circle
    Person *head=NULL;
    printf(ADD_PERSON_MSG"\n");
    scanf("%d",&addOrQuit);
    //add the first person
    if(addOrQuit==YES)
    {
        head=CreatePerson();
        //memory allocation failed - circle is empty
        if(head==NULL)
            return NULL;
    }
    //circle is empty
    else
        return NULL;
    //add second person?
    printf(ADD_PERSON_MSG"\n");
    scanf("%d",&addOrQuit);
    //add the second person
    if(addOrQuit==YES)
    {
        //create next person and connects to head. second parameter send to func is 0: next doesn't exist(NULL)
        head->CreateNext(head,NO);
        //memory allocation failed-only head exists
        if(head->next==NULL)
        {
            FreeAll(head);
            return NULL;
        }
        printf(ADD_PERSON_MSG"\n");
        scanf("%d",&addOrQuit);
    }
    //else: will return head(reaches end of func). create temp that keeps next of head
    Person *temp=head->next;
    //while user keeps adding persons
    while(addOrQuit==YES)
    {
        //create next person and connects to temp. second parameter send to func is 0: next doesn't exist(NULL)
        temp->CreateNext(temp,NO);
        //memory allocation failed- need to free every person that was previously created in the circle
        if(temp->next==NULL)
        {
            //destroy(free) the entire circle
            DestroyCircle(head);
            return NULL;
        }
        //advance temp
        temp=temp->next;
        //head->CreateNext(temp,nextNull);
        printf(ADD_PERSON_MSG"\n");
        scanf("%d",&addOrQuit);
    }
    return head;
}

/****************************************************************************************************************
 * Function name: InsertLaters
 * Input: Person* head
 * Output: -
 * Function Operation: The function brings in more people who are late to arrive, and wants to enter the circle
 *                     and settles them next to their best friend.
 ***************************************************************************************************************/
void InsertLaters(Person* head)
{
    //can't insert to an empty array
    if(head==NULL)
        return;
    //keeps user's answer
    int isLate;
    //keeps best friend ID
    int bfID;
    printf(LATE_MSG"\n");
    scanf("%d",&isLate);
    //while user keeps inserting laters
    while(isLate==YES)
    {
        //will point to the best friend
        Person *bf=NULL;
        //will keep the next of bf in order to compare it later
        Person *bfNext=NULL;
        printf(BF_ID_MSG"\n");
        scanf("%d", &bfID);
        //search the circle for the best friend, and insert it to the pointer
        bf = SearchCircleByID(head, bfID);
        //best friend wasn't found in the circle
        if (bf == NULL)
        {
            printf(ID_NOT_FOUND" %d\n", bfID);
            printf(LATE_MSG"\n");
            scanf("%d",&isLate);
            //continue to the next iteration of the loop
            continue;
        }
        //keeps next of bf in order to compare it later
        bfNext=bf->next;
        //create new person between bf and next of bf. second parameter send to func is 1: next does exist
        bf->CreateNext(bf, YES, bf->next);
        //next of bf wasn't changed- memory allocation in CreateNext Failed
        if(bfNext==bf->next)
            return;
        printf(LATE_MSG"\n");
        scanf("%d",&isLate);
    }
}

/****************************************************************************************************************
 * Function name: RemoveCowards
 * Input: Person* head
 * Output: Person*
 * Function Operation: The function removes from the circle the cowards who do not have the courage to participate
 *                     in the game(receives their ID).
 *                     as it's not possible to remove people from an empty circle, an error will be printed.
 ***************************************************************************************************************/
Person* RemoveCowards(Person* head)
{
    //can't remove from an empty array
    if(head==NULL)
        return head;
    //keeps user's answer
    int isCoward;
    //keeps coward's ID
    int cowardID;
    printf(COWARD_MSG"\n");
    scanf("%d",&isCoward);
    //while user keeps removing cowards
    while(isCoward==YES)
    {
        //will point to the coward
        Person *coward=NULL;
        //will keep the previous of the coward in order to connect the circle again
        Person *previous=NULL;
        printf(COWARD_ID_MSG"\n");
        scanf("%d",&cowardID);
        //search for the coward according to the id inserted by the user and points to him
        coward=SearchCircleByID(head,cowardID);
        //coward wasn't found in the circle
        if (coward == NULL)
        {
            printf(ID_NOT_FOUND" %d\n", cowardID);
            printf(COWARD_MSG"\n");
            scanf("%d",&isCoward);
            //continue to the next iteration of the loop
            continue;
        }
        printf(COWARD_DESTRUCT_MSG" %s!\n",coward->name);
        //finds the previous of the coward in order to connect the circle again
        previous=FindPreviousByID(head,cowardID);
        //coward is the head- destruct coward and make it's next the head
        if(previous==NULL)
            head=coward->SelfDestruct(coward);
        else //coward isn't the head- destruct coward and connect the previous and the next of him.
            previous->next=coward->SelfDestruct(coward);
        //circle is empty
        if(head==NULL)
            return head;
        printf(COWARD_MSG"\n");
        scanf("%d",&isCoward);
    }
    return head;
}

/****************************************************************************************************************
 * Function name: LetTheHungerGameBegin
 * Input: Person* head
 * Output: -
 * Function Operation: The function starts the game.
 *                     The game goes like this: the head of the circle starts, and kills the person next to him.
 *                     the the next person alive kills the next person alive and so on...
 *                     Eventually the function announces who won and remains alive.
 ***************************************************************************************************************/
void LetTheHungerGameBegin(Person* head)
{
    //circle is empty
    if(head==NULL)
        return;
    //find the last person in the circle
    Person *last=head;
    while(last->next!=NULL)
        last=last->next;
    //connecting the circle(make next of last the head)
    last->next=head;
    // while the head isn't connected to himself(only the winner left in the circle)
    while(head->next!=head)
    {
        //kill person message
        printf("%s kills %s",head->name,head->next->name);
        //kill kids message(s)
        for(int i=0;i<head->next->numOfKids;i++)
            printf(" and %s",head->next->kids[i]);
        printf("\n");
        //the actual kill- kills the next person alive
        head->KillNext(head);
        //advance head
        head=head->next;
    }
    //winner announcement
    printf(STAYING_ALIVE_A"%s"STAYING_ALIVE_B"\n",head->name);
    //free the winner
    FreeAll(head);
}

/****************************************************************************************************************
 * Function name: DestroyCircle
 * Input: Person* head
 * Output: -
 * Function Operation: The function destroys the circle whose head was received.
 ***************************************************************************************************************/
void DestroyCircle(Person* head)
{
    //as long as head isn't NULL- free it and advance the pointer
    while(head!=NULL)
    {
        //keeps next of head(because head is being freed so cannot access it's next
        Person *temp = head->next;
        FreeAll(head);
        //temp is the new head- then repeat the loop to destroy hi, too(if exists)
        head=temp;
    }
}