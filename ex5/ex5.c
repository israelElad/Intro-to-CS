/******************************************
* Student name: Elad Israel
* Student: 313448888
* Course Exercise Group: 06
* Exercise name: Exercise 2
******************************************/

//included in order to use input/output
#include <stdio.h>
//included in order to use strings functions
#include <string.h>

//max students the system keeps
#define MAX_STUDENTS 50
//max length of name the system keeps(20+1 of '/0')
#define MAX_NAME 21
//max courses allowed for each student
#define MAX_COURSES 5
//max input that can be inserted by user
#define MAX_INPUT 202
//max digits in a valid grade
#define MAX_GRADE 3

int SplitToSubstrings(char[],char[],char[],char[][MAX_NAME],int[]);
int NameCheckAndSplit(char **sInputPtr,char name[]);
int FamilyNameCheckAndSplit(char **sInputPtr,char familyName[]);
int CourseAndGradeCheckAndSplit(char **sInputPtr,char course[][MAX_NAME],int grade[]);

int SearchForStu(char name[],char[],char[][MAX_NAME],char[][MAX_NAME]);
void Insert(char[],char[],char[][MAX_NAME],int[],char[][MAX_NAME],
            char[][MAX_NAME],char[][MAX_COURSES][MAX_NAME],int[][MAX_COURSES]);
int SearchWhereToInsert(char[],char[],char[][MAX_NAME],char[][MAX_NAME]);
void AdvanceAllAfter(int,char[][MAX_NAME],char[][MAX_NAME],char[][MAX_COURSES][MAX_NAME],int[][MAX_COURSES]);
void InsertInOrder(int,char[],char[],char[][MAX_NAME],int[],char[][MAX_NAME],
                   char[][MAX_NAME],char[][MAX_COURSES][MAX_NAME],int[][MAX_COURSES]);
void Update(int,char[][MAX_NAME],int[],char[][MAX_NAME],
            char[][MAX_NAME],char[][MAX_COURSES][MAX_NAME],int[][MAX_COURSES]);

int SplitNameAndFamilyName(char[],char[],char[]);
void Delete(int,char[][MAX_NAME],char[][MAX_NAME],char[][MAX_COURSES][MAX_NAME],int[][MAX_COURSES]);
void ReverseAllAfter(int,char[][MAX_NAME],char[][MAX_NAME],char[][MAX_COURSES][MAX_NAME],int[][MAX_COURSES]);

int CalAvg(int,char [][MAX_COURSES][MAX_NAME],int [][MAX_COURSES]);
int CalMax(int,char [][MAX_COURSES][MAX_NAME],int [][MAX_COURSES]);
int CalMin(int,char [][MAX_COURSES][MAX_NAME],int [][MAX_COURSES]);
int CalSum(int,char [][MAX_COURSES][MAX_NAME],int [][MAX_COURSES]);
int CalCount(int,char [][MAX_COURSES][MAX_NAME],int [][MAX_COURSES]);

/**********************************************************************************************
 * Function name: PrintMenu
 * Input: -
 * Output: -
 * Function Operation: the function prints the menu detailing each operation to the user.
 **********************************************************************************************/
void PrintMenu()
{
    printf("Please select the operation:\n");
    printf("\t0. Exit.\n");
    printf("\t1. Insert or update student grades.\n");
    printf("\t2. Delete student information.\n");
    printf("\t3. Print the student with maximal computed grade.\n");
    printf("\t4. Print all the students with their computed grades.\n");
    printf("\t5. Print the menu.\n");
}

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
void InsertOrUpdate(char names[][MAX_NAME],char familyNames[][MAX_NAME],
                    char courses[][MAX_COURSES][MAX_NAME],int grades[][MAX_COURSES])
{
    //string(array of chars) that keeps user input
    char sInput[MAX_INPUT];
    //initialized(to NULL) temp arrays that keeps the splitted arrays(pre-validated)
    char name[MAX_NAME]={'\0'};
    char familyName[MAX_NAME]={'\0'};
    char course[MAX_COURSES][MAX_NAME]={'\0'};
    int grade[MAX_COURSES]={0};
    //holds returned value from SplitToSubstrings function - whether the input is valid(1) or not(0).
    int isValid;
    //holds returned value from SearchForStu function - whether the input is valid(1) or not(0).
    int stuPosition;
    char dummy;
    //dummy to receive \n from user input in main.
    scanf("%c",&dummy);
    //receives string input from user
    fgets(sInput,MAX_INPUT,stdin);
    //splits the string that the user entered while checking its validity
    isValid=SplitToSubstrings(sInput,name,familyName,course,grade);
    //invalid
    if(isValid==0)
    {
        printf("Error: invalid name or grade.\n");
        return;
    }
    //returns student position in array, if hasn't found anything- returns -1;
    stuPosition=SearchForStu(name,familyName,names,familyNames);
    //student wasn't found in the database- insert him.
    if(stuPosition==-1)
        Insert(name,familyName,course,grade,names,familyNames,courses,grades);
    //student was found in the database- update his courses and grades.
    else
        Update(stuPosition,course,grade,names,familyNames,courses,grades);
}

/**********************************************************************************************
 * Function name: SplitToSubstrings
 * Input: four arrays(name,familyName,course,grade)
 * Output: int (1 successful, 0 error)
 * Function Operation: the function receives the chars array that the user entered,
 *                     and four temp arrays from InsertOrUpdate, and using a pointer that goes
 *                     through the entire array, splits the string that the user entered and inserts
 *                     them to the corresponding array(name,familyName,course,grade).
 **********************************************************************************************/
int SplitToSubstrings(char sInput[],char name[],char familyName[],char course[][MAX_NAME],int grade[])
{
    //initialize pointer to the beginning of sInput. the pointer goes through the entire array.
    char *sInputPtr=&sInput[0];
    /*
     * general validity test- all signs exists al least once and in the order they should be.
     * flags are initialized to -1. then the pointer goes through the entire array and search
     * for the first sign. if found- continues to search for the next one etc..
     * each sign's flag is only changed if previous signes were found, so the signs
     * must appear in order at least once. (the signs: ':', ',', ';', '\n')
     */
    int colonFlag=-1, commaFlag=-1, semicolonFlag=-1, linebreakFlag=-1;
    for(int i=0;*sInputPtr!='\0';i++)
    {
        if(*sInputPtr==':')
            colonFlag=0;
        if(*sInputPtr==','&&colonFlag==0)
            commaFlag=0;
        if(*sInputPtr==';'&&commaFlag==0)
            semicolonFlag=0;
        if(*sInputPtr=='\n'&&semicolonFlag==0)
            linebreakFlag=0;
        sInputPtr++;
    }
    //a least one of the signs wasn't found- invalid input.
    if(colonFlag==-1||commaFlag==-1||semicolonFlag==-1||linebreakFlag==-1)
        return 0;
    //assign pointer to the beginning of sInput.
    sInputPtr=&sInput[0];
    //inserts the name part of the string to the "name" array, while checking it's validity
    if(NameCheckAndSplit(&sInputPtr,name)==0)
        return 0;
    //inserts the family name part of the string to the "familyName" array, while checking it's validity
    if(FamilyNameCheckAndSplit(&sInputPtr,familyName)==0)
        return 0;
    //advance pointer to skip the semicolon at the end of the family name.
    sInputPtr++;
    //inserts the courses and grades part of the string to the appropriate arrays, while checking their validity
    if(CourseAndGradeCheckAndSplit(&sInputPtr,course,grade)==0)
        return 0;
    return 1;
}

/**********************************************************************************************
 * Function name: NameCheckAndSplit
 * Input: pointer and name array
 * Output: int (1 successful, 0 error)
 * Function Operation: the function receives the temp array containing the student's name,
 *                     and the address of the pointer that goes through the entire array from
 *                     SplitToSubstrings(points right before the name begins), and using that
 *                     pointer goes through the part of the string containing the name,
 *                     and inserts the name to the "name" array, while checking it's validity.
 **********************************************************************************************/
int NameCheckAndSplit(char **sInputPtr,char name[])
{
    //skip spaces
    while(**sInputPtr==' ')
        (*sInputPtr)++;
    //if right after the spaces there is no letter- input is invalid.
    if(!((**sInputPtr>='a'&&**sInputPtr<='z')||(**sInputPtr>='A'&&**sInputPtr<='Z')))
        return 0;
    //as long as every cell is a letter-keep inserting it to the name array
    for(int i=0;(**sInputPtr>='a'&&**sInputPtr<='z')||(**sInputPtr>='A'&&**sInputPtr<='Z');i++)
    {
        //check that the name doesn't exceed MAX_NAME.
        if(i>=MAX_NAME)
            return 0;
        //inserting the letter to the name array
        name[i]=**sInputPtr;
        //if the cell doesn't contain a letter - invalid.
        if(!((**sInputPtr>='a'&&**sInputPtr<='z')||(**sInputPtr>='A'&&**sInputPtr<='Z')))
            return 0;
        (*sInputPtr)++;
    }
    return 1;
}

/**********************************************************************************************
 * Function name: FamilyNameCheckAndSplit
 * Input: pointer and familyName array
 * Output: int (1 successful, 0 error)
 * Function Operation: the function receives the temp array containing the student's family name,
 *                     and the address of the pointer that goes through the entire array from
 *                     SplitToSubstrings(points right before the family name begins), and using that
 *                     pointer goes through the part of the string containing the family name,
 *                     and inserts the name to the "familyName" array, while checking it's validity.
 **********************************************************************************************/
int FamilyNameCheckAndSplit(char **sInputPtr,char familyName[])
{
    //skip spaces
    while(**sInputPtr==' ')
        (*sInputPtr)++;
    //if right after the spaces there is no letter- input is invalid.
    if(!((**sInputPtr>='a'&&**sInputPtr<='z')||(**sInputPtr>='A'&&**sInputPtr<='Z')))
        return 0;
    //as long as the pointer didn't reach the colon-keep inserting the letters to the familyName array
    for(int i=0;**sInputPtr!=':';i++)
    {
        //check that the name doesn't exceed MAX_NAME.
        if(i>=MAX_NAME)
            return 0;
        //inserting the letter to the familyName array
        familyName[i]=**sInputPtr;
        //if the cell doesn't contain a letter or a space - invalid.
        if(!((**sInputPtr>='a'&&**sInputPtr<='z')||(**sInputPtr>='A'&&**sInputPtr<='Z')||(**sInputPtr==' ')))
            return 0;
        (*sInputPtr)++;
    }
    return 1;
}

/************************************************************************************************
 * Function name: CourseAndGradeCheckAndSplit
 * Input: char pointer, char array, and int array
 * Output: int (1 successful, 0 error)
 * Function Operation: the function receives a temp array containing the student's courses,
 *                     and a temp array containing the student's grades,
 *                     and the address of the pointer that goes through the entire array from
 *                     SplitToSubstrings(points right before the courses begins), and using that
 *                     pointer goes through the part of the string containing the courses and grades,
 *                     and inserts the courses and the grades to the "course" and "grade" array,
 *                     while checking their validity.
 ************************************************************************************************/
int CourseAndGradeCheckAndSplit(char **sInputPtr,char course[][MAX_NAME],int grade[])
{
    //temp array that stores the grade in char, until it will be coverted to int.
    char tempGrade[MAX_COURSES][MAX_INPUT]={'\0'};
    int i,j,k;
    //stores conversion result
    int gradeToInt;
    //goes through every course(and in the nested loops goes through every letter of that course)
    for(k=0;k<MAX_COURSES;k++)
    {
        //skip spaces
        while(**sInputPtr==' ')
            (*sInputPtr)++;
        //as long as the pointer didn't reach the comma-keep inserting the letters to the course array
        for (i=0;**sInputPtr!=',';i++)
        {
            //check that the course's name doesn't exceed MAX_NAME.
            if(i>=MAX_NAME)
                return 0;
            //if the cell doesn't contain a letter or a space - invalid.
            if(!((**sInputPtr>='a'&&**sInputPtr<='z')||(**sInputPtr>='A'&&**sInputPtr<='Z')||(**sInputPtr==' ')))
                return 0;
            //inserting the letter to the course array
            course[k][i]=**sInputPtr;
            (*sInputPtr)++;
        }
        //advance pointer to skip the comma at the end of the course's name.
        (*sInputPtr)++;
        //skip spaces
        while(**sInputPtr==' ')
            (*sInputPtr)++;
        // semicolon or '\n' right after course name is invalid
        if(**sInputPtr=='\n'||**sInputPtr==';')
            return 0;
        //as long as the pointer didn't reach the semicolon-keep inserting the letters to tempGrade array
        for(i=0;**sInputPtr!=';';i++)
        {
            //check that the grade contain only a digits and that it doesn't exceed MAX_NAME - invalid.
            if((i>=MAX_GRADE)||!((**sInputPtr >= '0' && **sInputPtr <= '9')))
                return 0;
            //inserting the letter to the tempGrade array
            tempGrade[k][i]=**sInputPtr;
            (*sInputPtr)++;;
        }
        //advance pointer to skip the semicolon at the end of the grade.
        (*sInputPtr)++;
        gradeToInt=0;
        //converts char digits of grade to int(stop at "i" because that's where the grade is over)
        for(j=0;j<i;j++)
        {
            //multiply the result by 10 due to the addition of digit(units becomes tens, tens become hundreds)
            gradeToInt*=10;
            //convert the ascii value to the value of the digit, and add to previous digits.
            gradeToInt+=(tempGrade[k][j]-'0');
        }
        //if grade isn't between 0 to 100 - invalid.
        if(!(gradeToInt>=0&&gradeToInt<=100))
            return 0;
        //insert grade to grade array
        grade[k]=gradeToInt;
        //reached the end of the user's input while everything so far is valid- stop
        if(**sInputPtr=='\n')
            break;
    }
    return 1;
}



/**********************************************************************************************
 * Function name: SearchForStu
 * Input: four char arrays(name,familyName,names,familyNames)
 * Output: int (values between -1 and 49)
 * Function Operation: the function searches for the student given in "name" and "familyName"
 *                     in the database arrays-"names","familyNames".
 *                     if found, the function returns its position.
 *                     if the student hasn't been found- the function returns -1.
 **********************************************************************************************/
int SearchForStu(char name[],char familyName[],char names[][MAX_NAME],char familyNames[][MAX_NAME])
{
    //goes through all the students in the array.
    for(int i=0;i<MAX_STUDENTS;i++)
    {
        //names are the same
        if(strcmp(name,names[i])==0)
            //family names are the same
            if(strcmp(familyName,familyNames[i])==0)
                //return position
                return i;
    }
    //student wasn't found in the database
    return -1;
}

/****************************************************************************************************
 * Function name: Insert
 * Input: three char arrays,one int array(temp), and three char arrays, one int array(database).
 * Output: -
 * Function Operation: the function receives 4 arrays that stores the student name,
 *                     family name, courses, and grades(in arrays: name,familyName,course,grade)
 *                     and inserts them to the database(names,familyNames,courses,grades) accordingly.
 ****************************************************************************************************/
void Insert(char name[],char familyName[],char course[][MAX_NAME],int grade[],char names[][MAX_NAME],
            char familyNames[][MAX_NAME],char courses[][MAX_COURSES][MAX_NAME],int grades[][MAX_COURSES])
{
    //keeps the position the student needs to be inserted to.
    int insertPosition;
    //the whole array is full
    if(names[MAX_STUDENTS-1][0]!='\0')
        printf("Error: there is no more space.\n");
    else //there is space to insert
    {
        //searches lexicographically where to insert the student and returns the position
        insertPosition=SearchWhereToInsert(name,familyName,names,familyNames);
        //advances every student(in all database arrays) after that position
        AdvanceAllAfter(insertPosition,names,familyNames,courses,grades);
        //inserts the student in the right position
        InsertInOrder(insertPosition,name,familyName,course,grade,names,familyNames,courses,grades);
        printf("Student \"%s %s\" added.\n",names[insertPosition],familyNames[insertPosition]);
    }
}

/**********************************************************************************************
 * Function name: SearchWhereToInsert
 * Input: four char arrays(name,familyName,names,familyNames)
 * Output: int (values between 0 and 49)
 * Function Operation: the function searches lexicographically where to insert the student given
 *                     in "name" and "familyName" in the database arrays-"names","familyNames".
 *                     (primary search according to name, secondary according to family name)
 *                     the function returns the position that the new student needs to be.
 **********************************************************************************************/
int SearchWhereToInsert(char name[],char familyName[],char names[][MAX_NAME],char familyNames[][MAX_NAME])
{
    int i;
    for(i=0;i<MAX_STUDENTS;i++)
    {
        //name<names[i] lexicographically
        if(strcmp(name, names[i])<0||strlen(names[i])==0)
            //that's where the student needs to be inserted
            return i;
        //name==names[i] lexicographically
        if(strcmp(name,names[i])==0)
            break;
    }
    //as long as name==names[i] lexicographically- compare family names
    while(strcmp(name,names[i])==0)
    {
        //familyName<familyName[i] lexicographically
        if(strcmp(familyName,familyNames[i])<0)
            //that's where the student needs to be inserted
            return i;
        //familyName and familyNames[i] aren't the same. otherwise InsertOrUpdate would Update(not Insert).
        i++;
    }
    return i;
}

/**********************************************************************************************
 * Function name: AdvanceAllAfter
 * Input: int(insert position), 3 char arrays, 1 int array(database)
 * Output: -
 * Function Operation: the function receives the position that the student need to be inserted to,
 *                     and advances every student(in all database arrays) after that position
 *                     by one cell so that the new student can be inserted to the database arrays.
 **********************************************************************************************/
void AdvanceAllAfter(int insertPosition,char names[][MAX_NAME],char familyNames[][MAX_NAME],
                     char courses[][MAX_COURSES][MAX_NAME],int grades[][MAX_COURSES])
{
    //goes backwards through the array until reaches the insert position
    for(int i=MAX_STUDENTS-1;i>insertPosition;i--)
    {
        //advance names[i-1] to [i]
        strcpy(names[i],names[i-1]);
        //erase names[i-1]
        strcpy(names[i-1],"");
        //advance familyNames[i-1] to [i]
        strcpy(familyNames[i],familyNames[i-1]);
        //erase familyNames[i-1]
        strcpy(familyNames[i-1],"");
        //advance every course and grade
        for(int j=MAX_COURSES-1;j>=0;j--)
        {
            //advance courses[i-1] to [i]
            strcpy(courses[i][j],courses[i-1][j]);
            //erase courses[i-1]
            strcpy(courses[i-1][j],"");
            //advance grades[i-1] to [i]
            grades[i][j]=grades[i-1][j];
            //erase grades[i-1]
            grades[i-1][j]=0;
        }
    }
}

/**********************************************************************************************
 * Function name: InsertInOrder
 * Input: int insertPosition,temp:3 char arrays,1 char array.database:3 char arrays, 1 int array
 * Output: -
 * Function Operation: the function inserts the student in the given position
 *                     (inserts the student stored in name,familyName,course and grade,
 *                     to the database arrays: names,familyNames,courses and grades)
 **********************************************************************************************/
void InsertInOrder(int insertPosition,char name[],char familyName[],char course[][MAX_NAME],
                   int grade[],char names[][MAX_NAME],char familyNames[][MAX_NAME],
                   char courses[][MAX_COURSES][MAX_NAME],int grades[][MAX_COURSES])
{
    //copies name to names in the insert position
    strcpy(names[insertPosition],name);
    //copies familyName to familyNames in the insert position
    strcpy(familyNames[insertPosition],familyName);
    for(int i=0;i<MAX_COURSES;i++)
    {
        //copies course to courses in the insert position
        strcpy(courses[insertPosition][i],course[i]);
        //copies grade to grades in the insert position
        grades[insertPosition][i]=grade[i];
    }
}

/**************************************************************************************************
 * Function name: Update
 * Input: int stuPosition,temp:course char array,int grade array.database:3 char arrays,1 int array
 * Output: -
 * Function Operation: the function updates the student in the given position (updates the student's
 *                     data stored in the database arrays: names,familyNames,courses and grades)
 *                     from the temp arrays: name,familyName,course and grade.
 **************************************************************************************************/
void Update(int stuPosition,char course[][MAX_NAME],int grade[],char names[][MAX_NAME],
            char familyNames[][MAX_NAME],char courses[][MAX_COURSES][MAX_NAME],int grades[][MAX_COURSES])
{
    //holds 0 if same course wasn't found in the loops.
    int foundSameCourseFlag=0;
    //holds 0 if no course has been added/updated. holds 1 if at least one course has.
    int isUpdatedOrAdded=0;
    //goes through every course in the added array
    for(int i=0;i<MAX_COURSES;i++)
    {
        foundSameCourseFlag=0;
        //goes through every course in the existing array.
        for(int j=0;j<MAX_COURSES;j++)
            //the course that needs to be updated and the course in the database match
            if(strcmp(course[i],courses[stuPosition][j])==0)
            {
                //update flags
                foundSameCourseFlag=1;
                isUpdatedOrAdded=1;
                //insert updated grade
                grades[stuPosition][j]=grade[i];
                //there is no need to search for the course any longer
                break;
            }
        //new course:addition of the course is required(course with the same name hasn't been found)
        if(foundSameCourseFlag==0)
        {
            //array is full(last cell in the row isn't)
            if(strcmp(courses[stuPosition][MAX_COURSES-1],"")!=0)
                break;
            //there is space to add another course
            for(int j=0;j<MAX_COURSES;j++)
            {
                //the row is empty(insert there)
                if(strcmp(courses[stuPosition][j],"")==0)
                {
                    //add the course
                    strcpy(courses[stuPosition][j],course[i]);
                    //add its grade
                    grades[stuPosition][j]=grade[i];
                    //update flag
                    isUpdatedOrAdded=1;
                    break;
                }
            }
        }
    }
    //no action was done on the database
    if(isUpdatedOrAdded==0)
        printf("Error: invalid name or grade.\n");
    //student updated
    else
        printf("Student \"%s %s\" updated.\n",names[stuPosition],familyNames[stuPosition]);
}

/**************************************************************************************************
 * Function name: DeleteIfExists
 * Input: database:3 char arrays,1 int array
 * Output: -
 * Function Operation: the function receives a name to delete from user,
 *                     deletes student if found in the database,otherwise prints error.
 *                     if deleted, reverse the cells in roder for the array to be in order again.
 **************************************************************************************************/
void DeleteIfExists(char names[][MAX_NAME],char familyNames[][MAX_NAME],
                    char courses[][MAX_COURSES][MAX_NAME],int grades[][MAX_COURSES])
{
    //keeps user input
    char sInput[MAX_INPUT];
    //initialized(to NULL) temp arrays that keeps the splitted arrays(prevalidated)-
    char name[MAX_NAME]={'\0'};
    char familyName[MAX_NAME]={'\0'};
    //holds returned value from SplitNameAndFamilyName function - whether the input is valid(1) or not(0).
    int isValid;
    //holds returned value from SearchForStu function - whether the input is valid(1) or not(0).
    int stuPosition;
    //dummy to receive \n from user input in main.
    char dummy;
    scanf("%c",&dummy);
    //receives string input from user
    fgets(sInput,MAX_INPUT,stdin);
    //splits the string that the user entered while checking its validity
    isValid=SplitNameAndFamilyName(sInput,name,familyName);
    //invalid
    if(isValid==0)
    {
        printf("Error: invalid name.\n");
        return;
    }
    //returns student position in array, if hasn't found anything- returns -1;
    stuPosition=SearchForStu(name,familyName,names,familyNames);
    //student wasn't found in the database.
    if(stuPosition==-1)
        printf("Error: student name does not exist.\n");
    else
    {
        //deletes student
        Delete(stuPosition, names, familyNames, courses, grades);
        //reverse every student(in all database arrays) after that position
        ReverseAllAfter(stuPosition,names,familyNames,courses,grades);
    }
}


/**********************************************************************************************
 * Function name: SplitNameAndFamilyName
 * Input: char pointer, char name and familyName arrays.
 * Output: int (1 successful, 0 error)
 * Function Operation: the function receives the temp arrays containing the student's name
 *                     and family name, and the string entered by user, and using a
 *                     pointer goes through the string and separates the name and family name
 *                     to the appropriate temp arrays(while checking their validity).
 **********************************************************************************************/
int SplitNameAndFamilyName(char sInput[],char name[],char familyName[])
{
    char *sInputPtr=&sInput[0];
    //check and split name
    if(NameCheckAndSplit(&sInputPtr,name)==0)
        return 0;
    //skip spaces
    while(*sInputPtr==' ')
        sInputPtr++;
    //if not a letter-invalid
    if(!((*sInputPtr>='a'&&*sInputPtr<='z')||(*sInputPtr>='A'&&*sInputPtr<='Z')))
        return 0;
    //check and split familyName
    for(int i=0;*sInputPtr!='\n';i++)
    {
        //check that the familyName doesn't exceed MAX_NAME.
        if(i>=MAX_NAME)
            return 0;
        //inserting the letter to the familyName array
        familyName[i]=*sInputPtr;
        //if the cell doesn't contain a letter or a space - invalid.
        if(!((*sInputPtr>='a'&&*sInputPtr<='z')||(*sInputPtr>='A'&&*sInputPtr<='Z')||(*sInputPtr==' ')))
            return 0;
        sInputPtr++;
    }
    return 1;

}

/**************************************************************************************************
 * Function name: Delete
 * Input: int stuPosition, database: 3 char arrays,1 int array
 * Output: -
 * Function Operation: helper function to DeleteIfExists that actually deletes the position received,
 *                     and prints an appropriate message.
 **************************************************************************************************/
void Delete(int stuPosition,char names[][MAX_NAME],char familyNames[][MAX_NAME],
            char courses[][MAX_COURSES][MAX_NAME],int grades[][MAX_COURSES])
{
    printf("Student \"%s %s\" deleted.\n",names[stuPosition],familyNames[stuPosition]);
    for(int i=0;i<MAX_NAME;i++)
    {
        //delete all arrays in that position
        names[stuPosition][i]='\0';
        familyNames[stuPosition][i]='\0';
        for(int j=0;j<MAX_COURSES;j++)
            courses[stuPosition][j][i]='\0';
    }
    //delete grades
    for(int j=0;j<MAX_COURSES;j++)
        grades[stuPosition][j]=0;
}


/**********************************************************************************************
 * Function name: ReverseAllAfter
 * Input: int(delete position), 3 char arrays, 1 int array(database)
 * Output: -
 * Function Operation: the function receives the position that the student was inserted to,
 *                     and reverse every student(in all database arrays) after that position
 *                     by one cell so that the database arrays will remain sorted.
 **********************************************************************************************/
void ReverseAllAfter(int deletePosition,char names[][MAX_NAME],char familyNames[][MAX_NAME],
                     char courses[][MAX_COURSES][MAX_NAME],int grades[][MAX_COURSES])
{
    for(int i=deletePosition;i<MAX_STUDENTS-1;i++)
    {
        //reverse names[i+1] to [i] and erase it
        strcpy(names[i],names[i+1]);
        strcpy(names[i+1],"");
        //reverse familyNames[i+1] to [i] and erase it
        strcpy(familyNames[i],familyNames[i+1]);
        strcpy(familyNames[i+1],"");
        for(int j=0;j<MAX_COURSES-1;j++)
        {
            //reverse courses[i+1][j] to [i][j] and erase it
            strcpy(courses[i][j], courses[i+1][j]);
            strcpy(courses[i+1][j],"");
            //reverse grades[i+1][j] to [i][j] and erase it
            grades[i][j]=grades[i+1][j];
            grades[i+1][j]=0;
        }
    }
}

/**********************************************************************************************
 * Function name: PrintAggregationMethod
 * Input: -
 * Output: -
 * Function Operation: the function prints the Prints Aggregation Method menu
 *                     detailing each operation to the user.
 **********************************************************************************************/
void PrintAggregationMethod()
{
    printf("Please select the aggregation method:\n");
    printf("\ta. Average grade.\n");
    printf("\tb. Maximal grade.\n");
    printf("\tc. Minimal grade.\n");
    printf("\td. Sum.\n");
    printf("\te. Count.\n");
    printf("\t0. Return the main menu.\n");
}

/**********************************************************************************************
 * Function name: CalculatedScoreForAllStudents
 * Input: 3 char arrays, 1 int array(database)
 * Output: -
 * Function Operation: the function finds and prints the student with the highest grade
 *                     according to the aggregation method chosen by user.
 **********************************************************************************************/
void CalculatedScoreForAllStudents(char names[][MAX_NAME],char familyNames[][MAX_NAME],
                     char courses[][MAX_COURSES][MAX_NAME],int grades[][MAX_COURSES])
{
    char aggregationMethod;
    //keeps max score(initialized to 0:min)
    int maxCalScore=0;
    //keeps max score student's position
    int maxCalStuPos=-1;
    //keeps calculted value returned from function
    int returnedCalValue;
    scanf(" %c",&aggregationMethod);
    //pointer to the appropriate function(according to user input)
    int (*aggFunc)(int,char[][MAX_COURSES][MAX_NAME],int[][MAX_COURSES]);
    //assign the appropriate function(according to user input) to the pointer
    switch (aggregationMethod)
    {
        case 'a': aggFunc=&CalAvg;
            break;
        case 'b': aggFunc=&CalMax;
            break;
        case 'c': aggFunc=&CalMin;
            break;
        case 'd': aggFunc=&CalSum;
            break;
        case 'e': aggFunc=&CalCount;
            break;
        case '0': return;
        default: return;
    }
    //calculates max between all students
    for(int i=0;(i<MAX_STUDENTS)&&(names[i][0]!='\0');i++)
    {
        returnedCalValue=aggFunc(i,courses,grades);
        if(returnedCalValue==maxCalScore)
            continue;
        //new max
        if(returnedCalValue>maxCalScore)
        {
            //update max value and student position
            maxCalScore = returnedCalValue;
            maxCalStuPos = i;
        }
    }
    printf("%s %s, %d\n",names[maxCalStuPos],familyNames[maxCalStuPos],maxCalScore);
}


/**********************************************************************************************
 * Function name: CalAvg
 * Input: int (student row in the database), char array(courses), int array(grades)
 * Output: int(values: 0-100)
 * Function Operation: the function calculates average score for all grades of a specific student
 *                     represented on the database by the row of the index received.
 **********************************************************************************************/
int CalAvg(int i,char courses[][MAX_COURSES][MAX_NAME],int grades[][MAX_COURSES])
{
    double gradesSum=0;
    for(int j=0;j<MAX_COURSES;j++)
    {
        //sum all grades
        if(courses[i][j][0]!='\0')
            gradesSum+=grades[i][j];
    }
    //return sum/num of grades(==avg)
    return (int)(gradesSum/CalCount(i,courses,grades));
}

/**********************************************************************************************
 * Function name: CalMax
 * Input: int (student row in the database), char array(courses), int array(grades)
 * Output: int(values: 0-100)
 * Function Operation: the function calculates max score for all grades of the specific student
 *                     represented on the database by the row of the index received.
 **********************************************************************************************/
int CalMax(int i,char courses[][MAX_COURSES][MAX_NAME],int grades[][MAX_COURSES])
{
    int maxGrade=0;
    for(int j=0;j<MAX_COURSES;j++)
    {
        //if bigger- new max
        if((courses[i][j][0]!='\0')&&(grades[i][j]>maxGrade))
            maxGrade=grades[i][j];
    }
    return maxGrade;
}

/**********************************************************************************************
 * Function name: CalMin
 * Input: int (student row in the database), char array(courses), int array(grades)
 * Output: int(values: 0-100)
 * Function Operation: the function calculates min score for all grades of the specific student
 *                     represented on the database by the row of the index received.
 **********************************************************************************************/
int CalMin(int i,char courses[][MAX_COURSES][MAX_NAME],int grades[][MAX_COURSES])
{
    int minGrade=100;
    for(int j=0;j<MAX_COURSES;j++)
    {
        //if smaller- new min
        if((courses[i][j][0]!='\0')&&(grades[i][j]<minGrade))
            minGrade=grades[i][j];
    }
    return minGrade;
}

/**********************************************************************************************
 * Function name: CalSum
 * Input: int (student row in the database), char array(courses), int array(grades)
 * Output: int(values: 0-500)
 * Function Operation: the function calculates the sum of all grades of the specific student
 *                     represented on the database by the row of the index received.
 **********************************************************************************************/
int CalSum(int i,char courses[][MAX_COURSES][MAX_NAME],int grades[][MAX_COURSES])
{
    double gradesSum=0;
    for(int j=0;j<MAX_COURSES;j++)
    {
        //sums all grades
        if(courses[i][j][0]!='\0')
            gradesSum+=grades[i][j];
    }
    return (int)gradesSum;
}

/**********************************************************************************************
 * Function name: CalCount
 * Input: int(student row in the database), char array(courses), int array(grades)
 * Output: int(values: 0-500)
 * Function Operation: the function counts all grades of the specific student
 *                     represented on the database by the row of the index received.
 **********************************************************************************************/
int CalCount(int i,char courses[][MAX_COURSES][MAX_NAME],int grades[][MAX_COURSES])
{
    int gradesCount;
    for(gradesCount=0;(gradesCount<MAX_COURSES)&&(courses[i][gradesCount][0]!='\0');gradesCount++)
    {
        //do nothing, just advance gradesCount
    }
    return gradesCount;
}

/**********************************************************************************************
 * Function name: CalculatedScoreOfEachStudent
 * Input: 3 char arrays, 1 int array(database)
 * Output: -
 * Function Operation: the function prints all the students' max aggregated grade
 *                     according to the aggregation method chosen by user.
 **********************************************************************************************/
void CalculatedScoreOfEachStudent(char names[][MAX_NAME],char familyNames[][MAX_NAME],
                                  char courses[][MAX_COURSES][MAX_NAME],int grades[][MAX_COURSES])
{
    char aggregationMethod;
    scanf(" %c",&aggregationMethod);
    //pointer to the appropriate function(according to user input)
    int (*aggFunc)(int,char[][MAX_COURSES][MAX_NAME],int[][MAX_COURSES]);
    //assign the appropriate function(according to user input) to the pointer
    switch (aggregationMethod)
    {
        case 'a': aggFunc=&CalAvg;
            break;
        case 'b': aggFunc=&CalMax;
            break;
        case 'c': aggFunc=&CalMin;
            break;
        case 'd': aggFunc=&CalSum;
            break;
        case 'e': aggFunc=&CalCount;
            break;
        case '0': return;
        default: return;
    }
    //prints the calculated score of each student
    for(int i=0;(i<MAX_STUDENTS)&&(names[i][0]!='\0');i++)
    {
        printf("%s %s, %d\n",names[i],familyNames[i],aggFunc(i,courses,grades));
    }
}


