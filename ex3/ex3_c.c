/******************************************
* Student name: Elad israel
* Student: 313448888
* Course Exercise Group: 06
* Exercise name: Exercise 2 in C
******************************************/


#include <stdio.h>
#include <math.h>

int main()
{
    // first input for mission number
    int missionNum;
    printf("please enter a mission number:\n");
    scanf("%d",&missionNum);
    //while mission number received from user isn't 0, give user another try.
    while (missionNum!=0)
    {
        /*mission 1: asks the user for a number, and checks if
          the number received is a prime number, in 3 different
          efficiency methods.*/
        if (missionNum == 1)
        {
            char missionType;
            int prime;
            printf("please enter the mission type:\n");
            scanf(" %c",&missionType);
            printf("please enter a number:\n");
            scanf("%d",&prime);
            // efficiency 'a' - checks division with all numbers smaller than the number received
            if (missionType == 'a')
            {
                // the number is a prime unless found otherwise
                int isPrime=1;
                int i;
                // checks division with all numbers between 2 and the number received
                for(i=2;i<prime;i++)
                {
                    // if the division has no remainders - it proves the number isn't a prime
                    if((prime%i)==0)
                    {
                        // number isn't a prime.
                        isPrime=0;
                        // there is no need to continue going through the rest of the numbers
                        break;
                    }
                }
                // specific numbers that needs to be addressed(prime smaller than 2)
                if(prime<2)
                    isPrime=0;
                // final answer - is primary or not
                if(isPrime==1)
                    printf("YES\n");
                else
                    printf("NO\n");
            }
            else //mission type != 'a'
            {
                // efficiency 'b' - checks division with all numbers smaller than the number's square root
                if(missionType=='b')
                {
                    // the number is a prime unless found otherwise
                    int isPrime = 1;
                    int i;
                    // calculates the received number's square root
                    int square;
                    square = (int) sqrt(prime);
                    // checks division with all numbers between 2 and the root of number received
                    for (i = 2; i <= square; i++)
                    {
                        // if the division has no remainders - it proves the number isn't a prime
                        if ((prime % i) == 0)
                        {
                            // number isn't a prime.
                            isPrime = 0;
                            // there is no need to continue going through the rest of the numbers
                            break;
                        }
                    }
                    // specific numbers that needs to be addressed(prime smaller than 2)
                    if (prime < 2)
                        isPrime = 0;
                    // final answer - is primary or not
                    if (isPrime == 1)
                        printf("YES\n");
                    else
                        printf("NO\n");
                }
                // efficiency 'c' - checks division by 2 and then checks division with all odd numbers smaller than the number's square root
                else
                {
                    // the number is a prime unless found otherwise
                    int isPrime = 1;
                    int i;
                    // calculates the received number's square root
                    int square;
                    square = (int) sqrt(prime);
                    // checks division with all numbers between 2 and the root of number received
                    if ((prime % 2 == 0)&&(prime!=2))
                        // num is divided by 2 --> not a prime
                        isPrime = 0;
                    else //num is not divided by 2
                    {
                        // checks division with all numbers between 2 and the root of number received
                        for (i = 3; i <= square; i=i+2)
                        {
                            // if the division has no remainders - it proves the number isn't a prime
                            if ((prime % i) == 0)
                            {
                                // number isn't a prime.
                                isPrime = 0;
                                // there is no need to continue going through the rest of the numbers
                                break;
                            }
                        }
                    }
                    // specific numbers that needs to be addressed(prime smaller than 2)
                    if (prime < 2)
                        isPrime = 0;
                    // final answer - is primary or not
                    if (isPrime == 1)
                        printf("YES\n");
                    else
                        printf("NO\n");
                }
            }
        }
        else //mission num != 1
        {
            /*mission 2: asks the user for two natural numbers,
              and prints the numbers between 1 to 100 that are
              divided by these numbers                       */
            if (missionNum == 2)
            {
                int num1,num2;
                int i;
                int min;
                printf("please enter two numbers:\n");
                // splits the two numbers received to two variables
                scanf("%d %d",&num1,&num2);
                // checks which number is the minimum for edge cases
                if(num1>num2)
                    min=num2;
                else
                    min=num1;
                // prints "[" as the output requires
                printf("[");
                // checks if the numbers between 1 to 100 are divided with the provided numbers
                for(i=1;i<=100;i++)
                {
                    // they are divided
                    if(((i%num1)==0)||((i%num2) == 0))
                    {
                        // if i is the first number in the output(min num received)
                        if(i==min)
                        {
                            // print only the number without ", "
                            printf("%d", i);
                            continue;
                        }
                        // prints the number according to the required structure
                        printf(", %d",i);
                    }
                }
                // prints "]" as the output requires
                printf("]\n");
            }
            else // missionNum isn't 1 or 2
            {
                // if the mission number received from user is 0, break the loop.
                if (missionNum == 0)
                    break;
            }
        }
        // give user another try if the loop hasn't been broken
        printf("please enter a mission number:\n");
        scanf("%d",&missionNum);
    }
}

/* Run time for case a: python   1.77936697 c  0.06675792
Run time for case b: python  0.01620293  c  0.00398993
Run time for case c: python  0.01577187  c 0.00411892 */




