/******************************************
* Student name: Elad Israel
* Student: 313448888
* Course Exercise Group: 06
* Exercise name: Exercise 2
******************************************/

#define MAX_NAME 21
#define MAX_COURSES 5

void PrintMenu();
void InsertOrUpdate(char[][MAX_NAME],char[][MAX_NAME],char[][MAX_COURSES][MAX_NAME],int[][MAX_COURSES]);
int DeleteIfExists(char[][MAX_NAME],char[][MAX_NAME],char[][MAX_COURSES][MAX_NAME],int[][MAX_COURSES]);
void PrintAggregationMethod();
void CalculatedScoreForAllStudents(char[][MAX_NAME],char[][MAX_NAME],char[][MAX_COURSES][MAX_NAME],int[][MAX_COURSES]);
void CalculatedScoreOfEachStudent(char[][MAX_NAME],char[][MAX_NAME],char[][MAX_COURSES][MAX_NAME],int[][MAX_COURSES]);
