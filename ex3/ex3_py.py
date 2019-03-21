"""******************************************
* Student name: Elad israel
* Student: 313448888
* Course Exercise Group: 06
* Exercise name: Exercise 3 in Python
******************************************"""

import math

# first input for mission number
print("please enter a mission number:")
missionNum=input()

#while mission number received from user isn't 0, give user another try.
while (missionNum!=0):
    """ mission 1: asks the user for a number, and checks if 
        the number received is a prime number, in 3 different
        efficiency methods.
    """
    if (missionNum==1):
        print("please enter the mission type:")
        missionType=raw_input()
        print("please enter a number:")
        prime=input()
        # efficiency 'a' - checks division with all numbers smaller than the number received
        if(missionType=='a'):
            # the number is a prime unless found otherwise
            isPrime=True
            # checks division with all numbers between 2 and the number received
            for i in xrange(2,prime):
                # if the division has no remainders - it proves the number isn't a prime
                if((prime%i)==0):
                    # number isn't a prime.
                    isPrime=False
                    # there is no need to continue going through the rest of the numbers
                    break
            # specific numbers that needs to be addressed(prime smaller than 2)
            if(prime<2):
                isPrime=False
            # final answer - is primary or not
            if (isPrime is True):
                print "YES"
            else:
                print "NO"

        #efficiency 'b' - checks division with all numbers smaller than the number's square root
        elif(missionType=='b'):
            # the number is a prime unless found otherwise
            isPrime = True
            # calculates the received number's square root
            square=int(math.sqrt(prime))
            # checks division with all numbers between 2 and the root of number received
            for i in xrange(2,square+1):
                # if the division has no remainders - it proves the number isn't a prime
                if ((prime % i) == 0):
                    # number isn't a prime.
                    isPrime = False
                    # there is no need to continue going through the rest of the numbers
                    break
            # specific numbers that needs to be addressed(prime smaller than 2)
            if(prime<2):
                isPrime=False
            # final answer - is primary or not
            if (isPrime is True):
                print "YES"
            else:
                print "NO"

        # efficiency 'c' - checks division by 2 and then checks division with all odd numbers smaller than the number's square root
        else:
            # the number is a prime unless found otherwise
            isPrime = True
            # calculates the received number's square root
            square = int(math.sqrt(prime))
            # checks division by 2(includes all even dividers)
            if ((prime % 2 == 0)&(prime!=0)):
                # num is divided by 2 --> not a prime
                isPrime = False
            else: # num is not divided by 2
                # checks division with all numbers between 2 and the root of number received
                for i in xrange(3, square+1, 2):
                    # if the division has no remainders - it proves the number isn't a prime
                    if ((prime % i) == 0):
                        # number isn't a prime.
                        isPrime = False
                        # there is no need to continue going through the rest of the numbers
                        break
            # specific numbers that needs to be addressed(prime smaller than 2)
            if (prime < 2):
                isPrime = False
            # final answer - is primary or not
            if (isPrime is True):
                print "YES"
            else:
                print "NO"

    elif(missionNum==2):
        """ mission 2: asks the user for two natural numbers,  
        and prints the numbers between 1 to 100 that are 
        divided by these numbers
        """
        print("please enter two numbers:")
        doubleNum=raw_input()
        # splits the two numbers received as one string to two chambers of an array
        splitNumbers=doubleNum.split(' ')
        # converts the array to two int numbers
        num1=int(splitNumbers[0])
        num2=int(splitNumbers[1])
        # contains the dividers
        dividers=[]
        # checks if the numbers between 1 to 100 are divided with the provided numbers
        for i in range(1,101):
            # they are divided
            if (((i%num1)==0)|((i%num2)==0)):
                # add to dividers list
                dividers.append(i)
        print dividers

    # if the mission number received from user is 0, break the loop.
    elif(missionNum==0):
        break
    # give user another try if the loop hasn't been broken
    print("please enter a mission number:")
    missionNum = input()
