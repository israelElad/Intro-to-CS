/******************************************
* Student name: Elad Israel
* Student: 313448888
* Course Exercise Group: 06
* Exercise name: Exercise 2
******************************************/

//included in order to use input/output
#include <stdio.h>
//included in order to use external functions
#include "ex5.h"

//max students the system keeps
#define MAX_STUDENTS 50
//max length of name the system keeps(20+1 of '/0')
#define MAX_NAME 21
//max courses allowed for each student
#define MAX_COURSES 5

/************************************************************************
* function name: main
* The Input: -
* The output: 0 if successful
* The Function operation: asks user for operation number and executes
*                         that operation accordingly using functions
*                         (operations explained in the functions)
*************************************************************************/
int main()
{
    //stores operation number received from user.
    int operationNum;
    //stores students' names in an initialized array
    char names[MAX_STUDENTS][MAX_NAME]={'\0'};
    //stores students' family names in an initialized array
    char familyNames[MAX_STUDENTS][MAX_NAME]={'\0'};
    //stores students' courses names in an initialized array(3D because each course contain an array for it's name)
    char courses[MAX_STUDENTS][MAX_COURSES][MAX_NAME]={'\0'};
    //stores students' grades in an initialized array
    int grades[MAX_STUDENTS][MAX_COURSES]={0};
    //function that prints the menu
    PrintMenu();
    //receives operation number from user.
    scanf("%d",&operationNum);
    //stop sign- received 0 from user as operationNum
    while(operationNum!=0)
    {
        switch(operationNum)
        {
            //insert a new student or update an existing one
            case 1:
            {
                //receive name,courses&grades from user,updates them if found in the database,otherwise inserts them.
                InsertOrUpdate(names,familyNames,courses,grades);
                break;
            }
            //delete a student(if exists)
            case 2:
            {
                //receive name to delete from user,deletes student if found in the database,otherwise prints error.
                DeleteIfExists(names,familyNames,courses,grades);
                break;
            }
            //finds and prints the student with the highest grade according to the aggregation method
            case 3:
            {
                //the user is asking information on a student so if the whole array is empty print error and break;
                if(names[0][0]=='\0')
                {
                    printf("Error: there are no students.\n");
                    break;
                }
                //there is at least one student in the arrays - Prints Aggregation Method menu
                PrintAggregationMethod();
                //find and print the student with the highest grade according to the aggregation method chosen by user
                CalculatedScoreForAllStudents(names,familyNames,courses,grades);
                break;
            }
            //prints all the students' max aggregated grade
            case 4:
            {
                //the user is asking information on a student so if the whole array is empty print error and break;
                if(names[0][0]=='\0')
                {
                    printf("Error: there are no students.\n");
                    break;
                }
                //there is at least one student in the arrays - Prints Aggregation Method menu
                PrintAggregationMethod();
                // prints all the students' max aggregated grade according to the aggregation method chosen by user
                CalculatedScoreOfEachStudent(names,familyNames,courses,grades);
                break;
            }
            //prints the extended menu
            case 5:
            {
                PrintMenu();
                break;
            }
            //operation number isn't 1-5
            default:
            {
                printf("Error: unrecognized operation.\n");
                break;
            }
        }
        //if operationNum==5 the menu was printed so there is no need to print
        if(operationNum!=5)
            printf("Select the next operation (insert 5 for complete menu).\n");
        //receives operation number from user.
        scanf("%d",&operationNum);
    }
    return 0;
}