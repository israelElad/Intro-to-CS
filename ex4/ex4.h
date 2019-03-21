/******************************************
* Student name: Elad israel
* Student: 313448888
* Course Exercise Group: 06
* Exercise name: Exercise 4
******************************************/

/************************************************************************
* function name: Collatz
* The Input: long int number. valid values: positive numbers.
* The Output: -
* The Function operation: checks the Collatz conjecture: do the following
* to any number- and you will eventually get "1": divide even numbers by 2,
* and multiply odd numbers by 3 and then add 1.
*************************************************************************/
void Collatz(long int);

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
void ProofCollatzUntill(long int);

/*******************************************************************************
* Function name: Fermat
* Input: int n(valid values >= 0), int stop(valid values >= 0).
* Output: -
* Function Operation: the function indirectly checks Fermat's Last Theorem
*                     it prints all the values that satisfy the following expression:
*                     a^n+b^n=c^n for the given exponent between 1 and the given stop value.
*******************************************************************************/
void Fermat(int n,int stop);

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
int IsDividedBy3Rec(long int);

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
int IsDividedBy3Iter(long int n);

/***************************************************************************************************
* Function name: FindCommonDigit
* Input: long int n(valid values > 0, digits sorted in ascending order from left to right).
* Output: int(values -1 to 9)
* Function Operation: the function receives two long integers and returns -1
*                     if they do not have any common digits, otherwise the function returns
*                     The most right shared digit.
****************************************************************************************************/
int FindCommonDigit(long int n1,long int n2);

/***************************************************************************************************
* Function name: CountDigit
* Input: long int n(valid values > 0), int d(valid values 0 to 9).
* Output: int(values >= 0)
* Function Operation: the function receives a number and a digit and returns how many times
*                     the digit appears in the number.
****************************************************************************************************/
int CountDigit(long int,int);

/***************************************************************************************************
* Function name: PrintReverse
* Input: long int n(valid values > 0).
* Output: -
* Function Operation: the function receives a number prints it backwards
****************************************************************************************************/
void PrintReverse(long int n);

