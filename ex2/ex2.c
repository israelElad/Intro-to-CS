#include <stdio.h>

/******************************************
* Student name: Elad israel
* Student: 313448888
* Course Exercise Group: 06
* Exercise name: Exercise 2
******************************************/

// Functions Declaration
void mission1();
int power(int base,int pow);
void mission2();
void mission3();
void mission4();
void mission5();


/************************************************************************
* function name: main
* The Input: -
* The output: 0 if successful
* The Function operation: asks user for mission number and executes
*                         that mission accordingly using functions
*************************************************************************/
int main()
{
    //receives mission number
    int mNum;
    printf("Please enter the mission number:\n");
    scanf("%d",&mNum);
    //executes the mission according to the user's input using functions
    switch(mNum)
    {
        case 1:
            mission1();
            break;
        case 2:
            mission2();
            break;
        case 3:
            mission3();
            break;
        case 4:
            mission4();
            break;
        case 5:
            mission5();
            break;
        //not 1-5
        default:printf("Error");
    }
    return 0;
}

/************************************************************************
* function name: mission1
* The Input: -
* The output: -
* The Function operation: receives 6 chars representing a binary number
*                         and prints it in decimal
*************************************************************************/
void mission1()
{
    //stores the binary number
    char bNum[6];
    //stores the decimal array
    int dNum[6];
    //sums the decimal value
    int sum=0;
    //used as a way to operate in reverse on the array
    int reverse=0;
    //dummy will receives the \n
    char dummy;
    //index used in "for" loop
    int i;
    printf("Enter six digits binary number:\n");
    //receives the \n as dummy
    scanf("%c",&dummy);
    //receives the binary sequence
    for(i=0;i<6;i++)
        scanf("%c", &bNum[i]);
    //duplicates the chars array to an int array
    for(i=0;i<6;i++)
    {
        if(bNum[i]=='0')
            dNum[i]=0;
        else
            dNum[i]=1;
    }
    //if positive-calculates it's decimal value(using reverse to avoid wrong power)
    if(dNum[0]==0)
        for(i=5;i>=0;i--)
        {
            sum += dNum[i] * power(2, reverse);
            reverse++;
        }
    //if negative
    else
    {
        //NOT
        for(i=0;i<6;i++)
        {
            if(dNum[i]==0)
                dNum[i]=1;
            else
                dNum[i]=0;
        }
        //calculates it's decimal value(using reverse to avoid wrong power)
        for(i=5;i>=0;i--)
        {
            sum += dNum[i] * power(2, reverse);
            reverse++;
        }
        //adds 1 to the number and multiply by (-1) so it would be the correct negative decimal value
        sum+=1;
        sum*=(-1);
    }
    //prints the decimal value(from if OR from else)
    printf("%d",sum);
}

/************************************************************************
* function name: power
* The Input: -
* The output: -
* The Function operation: used in mission1- receives a base and a power and calculates it
*************************************************************************/
int power(int base,int pow)
{
    int final=1;
    //while reduces the pow every time it multiplies the number
    while(pow>0)
    {
        final*=base;
        pow--;
    }

    return final;
}

/************************************************************************
* function name: mission2
* The Input: -
* The output: -
* The Function operation: receives the ASCII code of some character and prints
* the letter and capital letter accordingly. if entered a ASCII value that
* doesn't match a letter - the function will only print the number.
*************************************************************************/
void mission2()
{
    //stores the difference between a letter and it's equivalent capital letter
    const int difUpLow='a'-'A';
    int charP;
    //asks the user to enter the ASCII value and stores it in charP
    printf("Enter ASCII code of some character:\n");
    scanf("%d",&charP);
    //the letter is a capital letter
    if(charP>='A'&&charP<='Z')
    {
        printf("The number is: %d\n",charP);
        printf("The letter is: %c\n",charP+difUpLow);
        printf("The capital letter is: %c\n",charP);
    }
    //the letter isn't a capital letter
    else
    {
        //the letter is a small letter
        if(charP>='a'&&charP<='z')
        {
            printf("The number is: %d\n",charP);
            printf("The letter is: %c\n",charP);
            printf("The capital letter is: %c\n",charP-difUpLow);
        }
        //the ASCII number doesn't match any english letter- prints the number
        else
        {
            printf("The number is: %d\n",charP);
        }
    }
}

/***********************************************************************************
* function name: mission3
* The Input: -
* The output: -
* The Function operation: receives a decimal number of the following format:xyz.abc
* then prints left digits: xyz, right digits: abc,
* and the sum of the digits in the odd positions(x,z,a,c)
***********************************************************************************/

void mission3()
{
    //stores the float number received from user
    float rNum;
    //stores the int number  after converting it
    int cNum;
    //index used in loops
    int i;
    //stores the sum of the digits in the odd positions(x,z,a,c)
    int sum=0;
    printf("Enter a real number:\n");
    scanf("%f",&rNum);
    //takes out the digits that cause the deviation except the first one so it could be rounded
    cNum=rNum*10000;
    //the problematic digit needs to be rounded up
    if (cNum%10>=5)
        //rounds up the number and cuts the additional letter added by the float
        cNum=(cNum+10)/10;
    else
        //rounds down the number and cuts the additional letter added by the float
        cNum=cNum/10;
    // now we have the original number recieved times 1000(abc.xyz-->abcxyz)
    // integer part(3 left digits:abc)
    printf("The integer part: %d\n",cNum/1000);
    // fractional part(3 right digits:xyz)
    printf("The fractional part: %d\n",cNum%1000);
    // sum of the digits in odd positions(a+c+x+z)
    sum=(cNum%10)+((cNum/100)%10)+((cNum/1000)%10)+((cNum/100000)%10);
    printf("The sum of odd digits: %d",sum);
}


/***********************************************************************************
* function name: mission4
* The Input: -
* The output: -
* The Function operation: operates a "crazy" calculator
* as follows: ! add, @ subtract, # multiply, \ float division % int(whole numbers) division
***********************************************************************************/

void mission4()
{
    //stores the symbol(if correct: ! @ # \ %)
    char symbol;
    //stores the two numbers received by user
    int num1,num2;
    printf("Welcome to the crazy calculator:\n");
    printf("Enter two numbers:\n");
    scanf("%d%d",&num1,&num2);
    printf("Enter an action from: {! @ # \\ %%}:\n");
    scanf(" %c",&symbol);
    //do the operations of the "crazy calculator" according to the user's input
    switch(symbol)
    {
        case '!':
            printf("%d %c %d = %d",num1,symbol,num2,(num1+num2));
            break;
        case '@':
            printf("%d %c %d = %d",num1,symbol,num2,(num1-num2));
            break;
        case '#':
            printf("%d %c %d = %d",num1,symbol,num2,(num1*num2));
            break;
        case '\\':
            printf("%d %c %d = %f",num1,symbol,num2,((float)num1)/(float)num2);
            break;
        case '%':
            printf("%d %c %d = %d",num1,symbol,num2,(num1/num2));
            break;
        // entered a number that isn't one of the "crazy calculator" functions
        default:
            printf("The action '%c' is not \"good\" for me!",symbol);
    }
}


/***********************************************************************************
* function name: mission5
* The Input: -
* The output: -
* The Function operation: shows a quadratic equation, as a humal would write it.
***********************************************************************************/

void mission5()
{
    //stores the coefficients
    int a,b,c;
    //asks the user for the coefficients of the quadratic equation
    printf("Enter three coefficients:\n");
    scanf("%d%d%d",&a,&b,&c);
    //prints "a" value and x^2 after it. if a==0 then prints nothing
    if(a>0)
    {
        if (a != 1)
            printf("%d", a);
        printf("x^2");
    }
    else //a is negative or 0
    {
        if (a < 0)
        {
            //if a is -1 than we wouldn't want to print the "1" in "-1"
            if (a != -1)
                printf("%d", a);
            else
                printf("-");
            printf("x^2");
        }
    }
    //prints "b" value and x after it. if b==0 then prints nothing
    if(b>0)
    {
        //prints "+" only if a isn't 0(as humans writes it)
        if (a != 0)
            printf("+");
        //prints "b" value unless b==1(in that case we wouldn't want to print it)
        if(b!=1)
            printf("%d", b);
        printf("x");
    }
    else
        //b is negative or 0
        if(b<0)
        {
            //if b is -1 than we wouldn't want to print the "1" in "-1"
            if(b!=-1)
                printf("%d", b);
            else
                printf("-");
            printf("x");
        }
    //prints "c" value
    if(c>0)
    {
        //if a,b are 0 than we wouldn't want to print the "+"
        if (b!=0||a!=0)
            printf("+");
        printf("%d",c);
    }
    else//c is negative or 0
    if(c<0)
            printf("%d",c);
    //takes care of the possibility that all numbers are 0
    if(a==0&&b==0&&c==0)
        printf("0");
    printf(" = 0");
}

