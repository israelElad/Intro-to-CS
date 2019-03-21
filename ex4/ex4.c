/******************************************
* Student name: Elad israel
* Student: 313448888
* Course Exercise Group: 06
* Exercise name: Exercise 4
******************************************/

//max range of unsigned long int. used in CollatzNoPrint
#define MAX_LONG_INT 0xffffffff
#include <stdio.h>
#include <math.h>

/************************************************************************
* function name: Collatz
* The Input: long int number. valid values: positive numbers.
* The Output: -
* The Function operation: checks the Collatz conjecture: do the following
* to any number- and you will eventually get "1": divide even numbers by 2,
* and multiply odd numbers by 3 and then add 1.
*************************************************************************/
void Collatz(long int n)
{
    //totalsteps needs to be static in order to keep the count from previous runs of the function
    static long int totalSteps = 0;
    //steps counter of current run
    long int steps = 0;
    //first number is always printed
    printf("%ld",n);
    //as long as the number isn't 1 - divide it or multiply it accordingly
    while (n != 1)
    {
        //number is an even number
        if (n % 2 == 0)
        {
            //divide by 2 according to the Collatz conjecture
            n=n/2;
        }
        else //odd number
        {
            //multiply by 3 and add 1 according to the Collatz conjecture
            n=n*3+1;
        }
        //print the current step
        printf("->%ld",n);
        //updates the current and total counters of the steps
        steps++;
        totalSteps++;
    }
    //enter after showing the row of the steps
    printf("\n");
    printf("num of steps: %ld\n",steps);
    printf("total num of steps: %ld\n",totalSteps);
}

/*******************************************************************************
* Function name: CollatzNoPrint
* Input: long int (valid values > 0)
* Output: unsigned long int (values between 0[if steps>unsigned long int]
*        to unsigned long int)
* Function Operation: the function checks the Collatz conjecture for the given
*                     number according to the following conditions:
*                     if steps<=unsigned long int max limit - returns steps count.
*                     if steps>unsigned long int max limit - stops and returns 0.
*******************************************************************************/
unsigned long int CollatzNoPrint(long int n)
{
    //steps counter
    long int steps = 0;
    //as long as the number isn't 1 - divide it or multiply it accordingly
    while (n != 1)
    {
        //number is an even number
        if (n % 2 == 0)
        {
            //divide by 2 according to the Collatz conjecture
            n=n/2;
        }
        else //odd number
        {
            //multiply by 3 and add 1 according to the Collatz conjecture
            n=n*3+1;
        }
        //updates the current and total counters of the steps
        steps++;
        // if number of steps exceeds the max range of unsigned long int(0xffffffff) stop the check and return 0
        if(steps>MAX_LONG_INT)
            return 0;
    }
    //if number of steps doesn't exceeds the max range of unsigned long int(0xffffffff) return steps
    return (unsigned long int)steps;
}

/**************************************************************************************
* Function name: ProofCollatzUntill
* Input: long int
* Output: -
* Function Operation: the function checks the Collatz conjecture for all values
*                     between 1 to the given number using the previous function.
 *                    every value that passes- prints "passed" and the number that passed
 *                    and the amount of steps it took.
 *                    if the function stops prints: "you might wanna check (number) and win 500$ :)"
***************************************************************************************/
void ProofCollatzUntill(long int n)
{
    //stores the value returned from CollatzNoPrint
    unsigned long int stepsCounter;
    //deals with negative numbers(edge case)
    if(n<=0)
        //do nothing.
        return;
    //deals with the specific edge case: number 1
    if(n==1)
        printf("passed: 1 (num of steps: 0)\n");
    //checks all numbers from 1 to n according to CollatzNoPrint
    for(unsigned long int i=1;i<n;i++)
    {
        //runs the i number in CollatzNoPrint(checks if number of steps for i exceeds the max range of unsigned long int)
        stepsCounter=CollatzNoPrint(i);
        //number of steps for i doesn't exceeds the max range of unsigned long int(and deals with number '1' that should always pass)
        if((stepsCounter!=0)||(i==1))
        {
            printf("passed: %ld (num of steps: %lu)\n",i,stepsCounter);
        }
        //CollatzNoPrint returned 0(number of steps exceeded the max range of unsigned long int)
        else
        {
            printf("you might wanna check 3 and win 500$ :)\n");
        }
    }
}

/*******************************************************************************
* Function name: Fermat
* Input: int n(valid values >= 0), int stop(valid values >= 0).
* Output: -
* Function Operation: the function indirectly checks Fermat's Last Theorem
*                     it prints all the values that satisfy the following expression:
*                     a^n+b^n=c^n for the given exponent between 1 and the given stop value.
*******************************************************************************/
void Fermat(int n, int stop)
{
    //a= first base(first number), b= second base(second number), c= third base(result)
    int a,b,c;

    /*
        sumOfPows and result are used to keep the sum the exponentiations of a^n and b^n and the result(c^n)
        (because pow gets and returns a double value. for example pow(5^2) returns 24.999 and not 25
        so we just return the result to the double variables and compare them.
    */
    double sumOfPows;
    double result;
    // used as flag. remains 0 unless found values that satisfy the expression
    int found=0;

    /*
     goes through all numbers in range(primary sort by "a").
     1st loop goes through all numbers for the first base.
     2nd loop goes through all numbers for the second base, initialized as "a" because
     there is no need to check from "1" in every run of the loop if "a" already checked it,
     plus it is needed to avoid printing the same equation twice.
     3rd loop goes through all numbers for the third base.
     */
    for(a=1;a<stop;a++)
    {
        for(b=a;b<stop;b++)
        {
            for(c=1;c<stop;c++)
            {
                // sums the exponentiations of a^n and b^n
                sumOfPows=pow(a,n)+pow(b,n);
                // keeps the result(c^n)
                result=pow(c,n);
                //compares the left expression to the right and check if they are equal.
                if(sumOfPows==result)
                {
                    // the left expression and the right are equal-prints the specific expression
                    printf("Eureka! %d^%d + %d^%d = %d^%d\n", a, n, b, n, c, n);
                    // updates the flag that a valid expression was found in range
                    found=1;
                }
            }
        }
    }
    //a valid expression wasn't found in range
    if(found==0)
        printf("meh :(\n");
}

/*******************************************************************************
* Function name: UnderField3
* Input: long int n(valid values > 0),int toModulo3(valid values 0,1,2,3).
* Output: int(values 0,1,2)
* Function Operation: the function assist "IsDividedBy3Rec" function below.
*                     the function sums the digits of the given number under base 3-
*                     calculates the remainder from 3 of every digit and sums them
*                     according to base 3(0,1,2 numbers only).
*                     the function returns the summed up remainder in field 3.
*******************************************************************************/
int UnderField3(long int n,int toModulo3)
{
    //stop recursion sign- the number has been divided down to 0.
    if(n==0)
        //return the summed up remainder in field 3.
        return toModulo3;
    //current digit is 1
    if(n%10==1)
    {
        //digit is 1 and previous remainder is 0 - update remainder to 1
        if(toModulo3==0)
            toModulo3=1;
        else
        {
            //digit is 1 and previous remainder is 1 - update remainder to 2
            if (toModulo3 == 1)
                toModulo3 = 2;
            else
            {
                //digit is 1 and previous remainder is 2 - update remainder to 0(3 to field 3)
                if (toModulo3 == 2)
                    toModulo3 = 0;
                else
                {
                    //digit is 1 and previous remainder is 3 - update remainder to 1(4 to field 3)
                    if (toModulo3 == 3)
                        toModulo3 = 1;
                }
            }
        }
    }
    //current digit is 2
    if(n%10==2)
    {
        //digit is 2 and previous remainder is 0 - update remainder to 2
        if(toModulo3==0)
            toModulo3=2;
        else
        {
            //digit is 2 and previous remainder is 1 - update remainder to 0(3 to field 3)
            if (toModulo3 == 1)
                toModulo3 = 0;
            else
            {
                //digit is 2 and previous remainder is 2 - update remainder to 1(4 to field 3)
                if (toModulo3 == 2)
                    toModulo3 = 1;
                else
                {
                    //digit is 2 and previous remainder is 3 - update remainder to 2(5 to field 3)
                    if (toModulo3 == 3)
                        toModulo3 = 2;
                }
            }
        }
    }
    //current digit is 2
    if(n%10==3)
    {
        //digit is 3 and previous remainder is 0 - update remainder to 0(3 to field 3)
        if(toModulo3==0)
            toModulo3=0;
        else
        {
            //digit is 3 and previous remainder is 1 - update remainder to 1(4 to field 3)
            if (toModulo3 == 1)
                toModulo3 = 1;
            else
            {
                //digit is 3 and previous remainder is 2 - update remainder to 2(5 to field 3)
                if (toModulo3 == 2)
                    toModulo3 = 2;
                else
                    //digit is 3 and previous remainder is 3 - update remainder to 0(6 to field 3)
                    if(toModulo3==3)
                        toModulo3=0;
            }
        }
    }
    //recursion- returns the number without most right digit and the remainder.
    return UnderField3(n/10,toModulo3);
}

/************************************************************************************
* Function name: IsDividedBy3Rec
* Input: long int n(valid values > 0).
* Output: int(values 0 or 1)
* Function Operation: the function checks if a number that contains 1,2,3 digits only
*                     is divisible by 3 without using elementary arithmetics except /10 and %10.
*                     the function uses "UnderField3" function above to sum the number given
*                     under base 3, and uses the summed up remainder in field 3 to
*                     determine if the number is divisible by 3(returns 1) or not(return 0).
*
*************************************************************************************/
int IsDividedBy3Rec(long int n)
{
    //if there is no remainder after summing up the remainders of all digits
    if(UnderField3(n,0)==0)
        //the number is divisible by 3
        return 1;
    else //there is a remainder after summing up the remainders of all digits
        //the number is not divisible by 3.
        return 0;
}

/*******************************************************************************
* Function name: SumOfDigits
* Input: long int n(valid values > 0).
* Output: int(values > 0)
* Function Operation: the function assist "IsDividedBy3Iter" function below.
*                     the function sums the digits of a given number without
*                     using elementary arithmetics except /10 and %10 and +.
*                     the function returns the sum of the digits.
*******************************************************************************/
int SumOfDigits(long int sumMyDigits)
{
    //initialize sum of digits
    int sum=0;
    //while the number that need to be summed up is a positive number- keep dividing it.
    while(sumMyDigits>0)
    {
        //sums the right digits of the number and adds it to the previous sum.
        sum=sum+sumMyDigits%10;
        //move on to the next digit.
        sumMyDigits=sumMyDigits/10;
    }
    //return the sum of the digits.
    return sum;
}

/***************************************************************************************************
* Function name: IsDividedBy3Iter
* Input: long int n(valid values > 0).
* Output: int(values 0 or 1)
* Function Operation: the function checks if a number is divisible by 3 without using elementary
*                     arithmetics except /10 and %10 and +.
*                     the function uses "SumOfDigits" function above to sum the digits of the given
*                     number, and keeps summing up the digits using the function
*                     until the sum of the digits is a 1 digit number
*                     then it determines if the number is divisible by 3(returns 1) or not(return 0).
****************************************************************************************************/
int IsDividedBy3Iter(long int n)
{
    //while the sum of the digits has two or more digits - keep summing up the digits
    while(n>=10)
        //calls the function that sums the digits and update the number to be the sum of its' digits.
        n=SumOfDigits(n);
    //if sum of digits of the number(after summing its' digits to the point of it having 1 digit only- is 3 or 6 or 9
    if(n==3||n==6||n==9)
        //the number is divisible by 3- return 1
        return 1;
    //else(reaches this code only if isn't divisible)-return 0;
    return 0;
}

/***************************************************************************************************
* Function name: FindCommonDigit
* Input: long int n(valid values > 0, digits sorted in ascending order from left to right).
* Output: int(values -1 to 9)
* Function Operation: the function receives two long integers and returns -1
*                     if they do not have any common digits, otherwise the function returns
*                     The most right shared digit.
****************************************************************************************************/
int FindCommonDigit(long int n1,long int n2)
{
    //both numbers have divided down to 0
    if((n1==0)&&(n2==0))
        //the numbers do not have any common digits
        return -1;
    //if n1's right digit is bigger than n2's right digit
    if(n1%10>n2%10)
        //remove n1's right digit and send the numbers again to the function.
        return FindCommonDigit(n1/10,n2);
    else
        //if n2's right digit is bigger than n1's right digit
        if(n1%10<n2%10)
            //remove n2's right digit and send the numbers again to the function.
            return FindCommonDigit(n1,n2/10);
        else //n1 % 10 == n2 % 10
            //return the digit(equal on both numbers)
            return n1 % 10;
}

/***************************************************************************************************
* Function name: CountDigit
* Input: long int n(valid values > 0), int d(valid values 0 to 9).
* Output: int(values >= 0)
* Function Operation: the function receives a number and a digit and returns how many times
*                     the digit appears in the number.
****************************************************************************************************/
int CountDigit(long int n, int d)
{
    //if num is 0 then stop the recursion
    if(n==0)
        return 0;
    //if right digit equals to the digit we need to check
    if(n%10==d)
        //do the function again plus 1(because the number's right digit is divided by the digit)
        return 1+CountDigit(n/10,d);
    else
        //do the function again plus 1(because the number's right digit is not divided by the digit)
        return CountDigit(n/10,d);
}

/***************************************************************************************************
* Function name: PrintReverse
* Input: long int n(valid values > 0).
* Output: -
* Function Operation: the function receives a number prints it backwards
****************************************************************************************************/
void PrintReverse(long int n)
{
    // after done printing the whole number backwards
    if (n == 0)
    {
        //do a linebreak
        printf("\n");
        //stop the recursion
        return;
    }
    //prints the first digit on the right
    printf("%ld",n%10);
    //deletes the printed digit and moves on to the next one if it exists.
    PrintReverse(n/10);
}