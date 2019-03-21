/******************************************
* Student name: Elad Israel
* Student: 313448888
* Course Exercise Group: 06
* Exercise name: Exercise 2
******************************************/

//max length of name the system keeps(20+1 of '/0')
#define MAX_NAME 21
//max input that can be inserted by user
#define MAX_COURSES 5

/**********************************************************************************************
 * Function name: PrintMenu
 * Input: -
 * Output: -
 * Function Operation: the function prints the menu detailing each operation to the user.
 **********************************************************************************************/
void PrintMenu();

/**********************************************************************************************
 * Function name: InsertOrUpdate
 * Input: database- four arrays from main(names,familyNames,courses,grades)
 * Output: -
 * Function Operation: the function receives a string from user containing information on a
 *                     student, splits the input to 4 arrays that stores the student name,
 *                     family name, courses, and grades(in arrays: name,familyName,course,grade)
 *                     while checking the validity of the input, and determines whether the
 *                     student needs to be updated or inserted to the database, and executes
 *                     the operation accordingly.
 **********************************************************************************************/
void InsertOrUpdate(char[][MAX_NAME],char[][MAX_NAME],char[][MAX_COURSES][MAX_NAME],int[][MAX_COURSES]);

/**************************************************************************************************
 * Function name: DeleteIfExists
 * Input: database:3 char arrays,1 int array
 * Output: -
 * Function Operation: the function receives a name to delete from user,
 *                     deletes student if found in the database,otherwise prints error.
 *                     if deleted, reverse the cells in roder for the array to be in order again.
 **************************************************************************************************/
int DeleteIfExists(char[][MAX_NAME],char[][MAX_NAME],char[][MAX_COURSES][MAX_NAME],int[][MAX_COURSES]);

/**********************************************************************************************
 * Function name: PrintAggregationMethod
 * Input: -
 * Output: -
 * Function Operation: the function prints the Prints Aggregation Method menu
 *                     detailing each operation to the user.
 **********************************************************************************************/
void PrintAggregationMethod();

/**********************************************************************************************
 * Function name: CalculatedScoreForAllStudents
 * Input: 3 char arrays, 1 int array(database)
 * Output: -
 * Function Operation: the function finds and prints the student with the highest grade
 *                     according to the aggregation method chosen by user.
 **********************************************************************************************/
void CalculatedScoreForAllStudents(char[][MAX_NAME],char[][MAX_NAME],char[][MAX_COURSES][MAX_NAME],int[][MAX_COURSES]);

/**********************************************************************************************
 * Function name: CalculatedScoreOfEachStudent
 * Input: 3 char arrays, 1 int array(database)
 * Output: -
 * Function Operation: the function prints all the students' max aggregated grade
 *                     according to the aggregation method chosen by user.
 **********************************************************************************************/
void CalculatedScoreOfEachStudent(char[][MAX_NAME],char[][MAX_NAME],char[][MAX_COURSES][MAX_NAME],int[][MAX_COURSES]);
