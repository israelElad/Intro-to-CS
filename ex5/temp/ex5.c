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
 * Input: database- four arrays from menu(names,familyNames,courses,grades)
 * Output: -
 * Function Operation: the function receives a string from user containing information on a
 *                     student, check the validity of the input, and determines whether the
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
    isValid=SplitToSubstrings(sInput,name,familyName,course,grade);
    if(isValid==0)
    {
        printf("Error: invalid name or grade.\n");
        return;
    }
    //returns student position in array, if hasn't found anything- returns -1;
    stuPosition=SearchForStu(name,familyName,names,familyNames);
    if(stuPosition==-1)
        Insert(name,familyName,course,grade,names,familyNames,courses,grades);
    else
        Update(stuPosition,course,grade,names,familyNames,courses,grades);
}

/**********************************************************************************************
 * Function name: SplitToSubstrings
 * Input: database- four arrays from menu(names,familyNames,courses,grades)
 * Output: int (1 successful, 0 error)
 * Function Operation: the function receives the chars array that the user entered,
 *                     and four temp arrays, and using a pointer that goes through the
 *                     entire array, splits the string that the user entered and inserts
 *                     them to the corresponding array(name,familyName,course,grade).
 **********************************************************************************************/
int SplitToSubstrings(char sInput[],char name[],char familyName[],char course[][MAX_NAME],int grade[])
{
    char tempGrade[MAX_COURSES][MAX_INPUT]={'\0'};
    char *sInputPtr=&sInput[0];
    int i,j,k;
    int gradeToInt;
    int colonFlag=-1, commaFlag=-1, semicolonFlag=-1, linebreakFlag=-1;
    for(i=0;*sInputPtr!='\0';i++)
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
    if(colonFlag==-1||commaFlag==-1||semicolonFlag==-1||linebreakFlag==-1)
        return 0;
    //assign pointer to the beginning of sInput.
    sInputPtr=&sInput[0];
    //name
    if(NameCheckAndSplit(&sInputPtr,name)==0)
        return 0;
    while(*sInputPtr==' ')
        sInputPtr++;
    if(!((*sInputPtr>='a'&&*sInputPtr<='z')||(*sInputPtr>='A'&&*sInputPtr<='Z')))
        return 0;
    for(i=0;*sInputPtr!=':';i++)
    {
        if(i>=MAX_NAME)
            return 0;
        familyName[i]=*sInputPtr;
        if(!((*sInputPtr>='a'&&*sInputPtr<='z')||(*sInputPtr>='A'&&*sInputPtr<='Z')||(*sInputPtr==' ')))
            return 0;
        sInputPtr++;
    }
    sInputPtr++;
    for(k=0;k<MAX_COURSES;k++)
    {
        while(*sInputPtr==' ')
            sInputPtr++;
        for (i=0;*sInputPtr!=',';i++)
        {
            if(i>=MAX_NAME)
                return 0;
            if(!((*sInputPtr>='a'&&*sInputPtr<='z')||(*sInputPtr>='A'&&*sInputPtr<='Z')||(*sInputPtr==' ')))
                return 0;
            course[k][i]=*sInputPtr;
            sInputPtr++;
        }
        sInputPtr++;
        if(*sInputPtr=='\n')
            return 0;
        while(*sInputPtr==' ')
            sInputPtr++;
        for(i=0;*sInputPtr!=';';i++)
        {
            if((i>=MAX_GRADE)||!((*sInputPtr >= '0' && *sInputPtr <= '9')))
                return 0;
            tempGrade[k][i]=*sInputPtr;
            sInputPtr++;
        }
        sInputPtr++;
        gradeToInt=0;
        for(j=0;j<i;j++)
        {
            gradeToInt*=10;
            gradeToInt+=(tempGrade[k][j]-'0');
        }
        if(!(gradeToInt>=0&&gradeToInt<=100))
            return 0;
        grade[k]=gradeToInt;
        if(*sInputPtr=='\n')
            break;
    }
    return 1;
}

/**********************************************************************************************
 * Function name: NameCheckAndSplit
 * Input: pointer and name array from SplitToSubstrings
 * Output: int (1 successful, 0 error)
 * Function Operation: the function receives the pointer that ,
 *                     and four temp arrays, and using a pointer that goes through the
 *                     entire array, splits the string that the user entered and inserts
 *                     them to the corresponding array(name,familyName,course,grade).
 **********************************************************************************************/
int NameCheckAndSplit(char **sInputPtr,char name[])
{
    while(**sInputPtr==' ')
        (*sInputPtr)++;
    if(!((**sInputPtr>='a'&&**sInputPtr<='z')||(**sInputPtr>='A'&&**sInputPtr<='Z')))
        return 0;
    for(int i=0;(**sInputPtr>='a'&&**sInputPtr<='z')||(**sInputPtr>='A'&&**sInputPtr<='Z');i++)
    {
        if(i>=MAX_NAME)
            return 0;
        name[i]=**sInputPtr;
        if(!((**sInputPtr>='a'&&**sInputPtr<='z')||(**sInputPtr>='A'&&**sInputPtr<='Z')))
            return 0;
        (*sInputPtr)++;
    }
    return 1;
}


//returns -1 if not found, position otherwise.
int SearchForStu(char name[],char familyName[],char names[][MAX_NAME],char familyNames[][MAX_NAME])
{
    int i;
    for(i=0;i<MAX_STUDENTS;i++)
    {
        if(strcmp(name,names[i])==0)
            if(strcmp(familyName,familyNames[i])==0)
                return i;
    }
    return -1;
}


void Insert(char name[],char familyName[],char course[][MAX_NAME],int grade[],char names[][MAX_NAME],
            char familyNames[][MAX_NAME],char courses[][MAX_COURSES][MAX_NAME],int grades[][MAX_COURSES])
{
    int insertPosition;
    if(names[MAX_STUDENTS-1][0]!='\0')
        //the whole array is full
        printf("Error: there is no more space.\n");
    else
    {
        insertPosition=SearchWhereToInsert(name,familyName,names,familyNames);
        //there is space to insert(checked before)
        AdvanceAllAfter(insertPosition,names,familyNames,courses,grades);
        InsertInOrder(insertPosition,name,familyName,course,grade,names,familyNames,courses,grades);
        printf("Student \"%s %s\" added.\n",names[insertPosition],familyNames[insertPosition]);
    }
}
// primary search according to name. secondary according to family name.
int SearchWhereToInsert(char name[],char familyName[],char names[][MAX_NAME],char familyNames[][MAX_NAME])
{
    int i;
    for (i = 0; i < MAX_STUDENTS; i++)
    {
        //name<names[i]
        if (strcmp(name, names[i]) < 0||strlen(names[i])==0)
            return i;
        if (strcmp(name, names[i]) == 0)
            break;
    }
    while (strcmp(name, names[i]) == 0)
    {
        if (strcmp(familyName, familyNames[i]) < 0)
            return i;
        //familyName and familyNames[i] aren't the same. otherwise InsertOrUpdate would Update(not Insert).
        i++;
    }
    return i;
}


void AdvanceAllAfter(int insertPosition,char names[][MAX_NAME],char familyNames[][MAX_NAME],
                     char courses[][MAX_COURSES][MAX_NAME],int grades[][MAX_COURSES])
{
    for(int i=MAX_STUDENTS-1;i>insertPosition;i--)
    {
        strcpy(names[i],names[i-1]);
        strcpy(names[i-1],"");
        strcpy(familyNames[i],familyNames[i-1]);
        strcpy(familyNames[i-1],"");
        for(int j=MAX_COURSES-1;j>=0;j--)
        {
            strcpy(courses[i][j],courses[i-1][j]);
            strcpy(courses[i-1][j],"");
            grades[i][j]=grades[i-1][j];
            grades[i-1][j]=0;
        }
    }
}

void InsertInOrder(int insertPosition,char name[],char familyName[],char course[][MAX_NAME],int grade[],
                   char names[][MAX_NAME],char familyNames[][MAX_NAME],
                   char courses[][MAX_COURSES][MAX_NAME],int grades[][MAX_COURSES])
{
    strcpy(names[insertPosition],name);
    strcpy(familyNames[insertPosition],familyName);
    for(int i=0;i<MAX_COURSES;i++)
    {
        strcpy(courses[insertPosition][i],course[i]);
        grades[insertPosition][i]=grade[i];
    }
}


void Update(int stuPosition,char course[][MAX_NAME],int grade[],char names[][MAX_NAME],
            char familyNames[][MAX_NAME],char courses[][MAX_COURSES][MAX_NAME],int grades[][MAX_COURSES])
{
    int foundSameCourseFlag=0;
    //holds 0 if no course has been added/updated. holds 1 if at least 1 has.
    int isUpdatedOrAdded=0;
    //goes through every course in the added array
    for(int i=0;i<MAX_COURSES;i++)
    {
        foundSameCourseFlag=0;
        //goes through every course in the existing array.
        for(int j=0;j<MAX_COURSES;j++)
            if(strcmp(course[i],courses[stuPosition][j])==0)
            {
                foundSameCourseFlag=1;
                isUpdatedOrAdded=1;
                grades[stuPosition][j]=grade[i];
                break;
            }
        //new course:addition of the course is required(course with the same name hasn't been found)
        if(foundSameCourseFlag==0)
        {
            if(strcmp(courses[stuPosition][4],"")!=0)
                break;
            for(int j=0;j<MAX_COURSES;j++)
            {
                if(strcmp(courses[stuPosition][j],"")==0)
                {
                    strcpy(courses[stuPosition][j],course[i]);
                    grades[stuPosition][j]=grade[i];
                    isUpdatedOrAdded=1;
                    break;
                }
            }
        }
    }
    if(isUpdatedOrAdded==0)
        printf("Error: invalid name or grade.\n");
    else
        printf("Student \"%s %s\" updated.\n",names[stuPosition],familyNames[stuPosition]);
}





void DeleteIfExists(char names[][MAX_NAME],char familyNames[][MAX_NAME],
                    char courses[][MAX_COURSES][MAX_NAME],int grades[][MAX_COURSES])
{
    //keeps user input
    char sInput[MAX_INPUT];
    //initialized(to NULL) temp arrays that keeps the splitted arrays(prevalidated)-
    char name[MAX_NAME]={'\0'};
    char familyName[MAX_NAME]={'\0'};
    int isValid;
    int stuPosition;
    char dummy;
    scanf("%c",&dummy);
    fgets(sInput,MAX_INPUT,stdin);
    isValid=SplitNameAndFamilyName(sInput,name,familyName);
    if(isValid==0)
    {
        printf("Error: invalid name.\n");
        return;
    }
    //returns student position in array, if hasn't found anything- returns -1;
    stuPosition=SearchForStu(name,familyName,names,familyNames);
    if(stuPosition==-1)
        printf("Error: student name does not exist.\n");
    else
    {
        Delete(stuPosition, names, familyNames, courses, grades);
        ReverseAllAfter(stuPosition,names,familyNames,courses,grades);
    }
}



int SplitNameAndFamilyName(char sInput[],char name[],char familyName[])
{
    char *sInputPtr=&sInput[0];
    //name
    if(NameCheckAndSplit(&sInputPtr,name)==0)
        return 0;
    //familyName
    while(*sInputPtr==' ')
        sInputPtr++;
    if(!((*sInputPtr>='a'&&*sInputPtr<='z')||(*sInputPtr>='A'&&*sInputPtr<='Z')))
        return 0;
    for(int i=0;*sInputPtr!='\n';i++)
    {
        if(i>=MAX_NAME)
            return 0;
        familyName[i]=*sInputPtr;
        if(!((*sInputPtr>='a'&&*sInputPtr<='z')||(*sInputPtr>='A'&&*sInputPtr<='Z')||(*sInputPtr==' ')))
            return 0;
        sInputPtr++;
    }
    return 1;

}


void Delete(int stuPosition,char names[][MAX_NAME],char familyNames[][MAX_NAME],
            char courses[][MAX_COURSES][MAX_NAME],int grades[][MAX_COURSES])
{
    printf("Student \"%s %s\" deleted.\n",names[stuPosition],familyNames[stuPosition]);
    for(int i=0;i<MAX_NAME;i++)
    {
        names[stuPosition][i]='\0';
        familyNames[stuPosition][i]='\0';
        for(int j=0;j<MAX_COURSES;j++)
            courses[stuPosition][j][i]='\0';
    }
    for(int j=0;j<MAX_COURSES;j++)
        grades[stuPosition][j]=0;
}

void ReverseAllAfter(int deletePosition,char names[][MAX_NAME],char familyNames[][MAX_NAME],
                     char courses[][MAX_COURSES][MAX_NAME],int grades[][MAX_COURSES])
{
    for(int i=deletePosition;i<MAX_STUDENTS-1;i++)
    {
        strcpy(names[i],names[i+1]);
        strcpy(names[i+1],"");
        strcpy(familyNames[i],familyNames[i+1]);
        strcpy(familyNames[i+1],"");
        for(int j=0;j<MAX_COURSES-1;j++)
        {
            strcpy(courses[i][j], courses[i+1][j]);
            strcpy(courses[i+1][j],"");
            grades[i][j]=grades[i+1][j];
            grades[i+1][j]=0;
        }
    }
}


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

void CalculatedScoreForAllStudents(char names[][MAX_NAME],char familyNames[][MAX_NAME],
                     char courses[][MAX_COURSES][MAX_NAME],int grades[][MAX_COURSES])
{
    char aggregationMethod;
    int maxCalScore=0;
    int maxCalStuPos=-1;
    int returnedCalValue;
    scanf(" %c",&aggregationMethod);
    int (*aggFunc)(int,char[][MAX_COURSES][MAX_NAME],int[][MAX_COURSES]);
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
    for(int i=0;(i<MAX_STUDENTS)&&(names[i][0]!='\0');i++)
    {
        returnedCalValue=aggFunc(i,courses,grades);
        if(returnedCalValue==maxCalScore)
            continue;
        if(returnedCalValue>maxCalScore)
        {
            maxCalScore = returnedCalValue;
            maxCalStuPos = i;
        }
    }
    printf("%s %s, %d\n",names[maxCalStuPos],familyNames[maxCalStuPos],maxCalScore);
}


//calculates average score for all grades of a specific student.
int CalAvg(int i,char courses[][MAX_COURSES][MAX_NAME],int grades[][MAX_COURSES])
{
    double gradesSum=0;
    for(int j=0;j<MAX_COURSES;j++)
    {
        if(courses[i][j][0]!='\0')
            gradesSum+=grades[i][j];
    }
    return (int)(gradesSum/CalCount(i,courses,grades));
}


int CalMax(int i,char courses[][MAX_COURSES][MAX_NAME],int grades[][MAX_COURSES])
{
    int maxGrade=0;
    for(int j=0;j<MAX_COURSES;j++)
    {
        if((courses[i][j][0]!='\0')&&(grades[i][j]>maxGrade))
            maxGrade=grades[i][j];
    }
    return maxGrade;
}


int CalMin(int i,char courses[][MAX_COURSES][MAX_NAME],int grades[][MAX_COURSES])
{
    int minGrade=100;
    for(int j=0;j<MAX_COURSES;j++)
    {
        if((courses[i][j][0]!='\0')&&(grades[i][j]<minGrade))
            minGrade=grades[i][j];
    }
    return minGrade;
}


int CalSum(int i,char courses[][MAX_COURSES][MAX_NAME],int grades[][MAX_COURSES])
{
    double gradesSum=0;
    for(int j=0;j<MAX_COURSES;j++)
    {
        if(courses[i][j][0]!='\0')
            gradesSum+=grades[i][j];
    }
    return (int)gradesSum;
}


int CalCount(int i,char courses[][MAX_COURSES][MAX_NAME],int grades[][MAX_COURSES])
{
    int gradesCount;
    for(gradesCount=0;(gradesCount<MAX_COURSES)&&(courses[i][gradesCount][0]!='\0');gradesCount++)
    {
        //do nothing, just advance gradesCount
    }
    return gradesCount;
}


void CalculatedScoreOfEachStudent(char names[][MAX_NAME],char familyNames[][MAX_NAME],
                                  char courses[][MAX_COURSES][MAX_NAME],int grades[][MAX_COURSES])
{
    char aggregationMethod;
    scanf(" %c",&aggregationMethod);
    int (*aggFunc)(int,char[][MAX_COURSES][MAX_NAME],int[][MAX_COURSES]);
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
    for(int i=0;(i<MAX_STUDENTS)&&(names[i][0]!='\0');i++)
    {
        printf("%s %s, %d\n",names[i],familyNames[i],aggFunc(i,courses,grades));
    }
}


