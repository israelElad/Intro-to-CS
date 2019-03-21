"""
*Student name: Elad Israel
*Student ID: 313448888
*Course Exercise Group: 89110-06
*Exercise name: ex1
"""

# asks mission number from user
print("please enter the mission number:")
missionNum=input()

""" 
mission 1:
getting a number from user and it's base, and printing it in decimal.
"""
if missionNum==1:
    # asks user for number to convert
    print("please enter a number:")
    num=raw_input()
    # convert num to list so it will be possible to seperate every letter easily.
    num=list(num)
    # asks user for the number's base
    print("please enter a base (2-9):")
    base=input()
    # reversing the list to easily go through every letter and exponentiate it according to the loop index.
    num.reverse()
    sum=0
    """
    "for" goes through all of the list(every letter of it)
    and converts it to decimal by multiplying it with it's base
    and exponentiante it according to the loop index.
    """
    for i in range(len(num)):
        num[i]=int(num[i])*(base**i)
        sum=sum+int(num[i])
    # prints the number in decimal
    print(sum)


    """mission 2:getting a number from user in base 8(octal) or 16(decimal), and printing it in binary."""
elif (missionNum==2):
    # asks user for number to convert
    print("please enter a number:")
    numToConvert=raw_input()
    # asks user for the number's base
    print("please enter a base (16 or 8):")
    baseToConvert=input()
    #convertedNum will sum all the letters after their conversion
    convertedNum=""
    # "if" checks if the base is 8 and then goes to the corresponding dictionary
    if(baseToConvert==8):
        base8Dict={'0':'000','1':'001','2':'010', '3':'011', '4':'100', '5':'101', '6':'110', '7':'111'}
        # "for" goes through every letter and converts it to it's base 8 equivalent
        for j in range(len(numToConvert)):
            convertedNum=convertedNum+str(base8Dict[numToConvert[j]])
        print convertedNum
    # "elif" checks if the base is 16 and then goes to the corresponding dictionary
    elif(baseToConvert==16):
        base16Dict={'0':'0000','1':'0001','2':'0010', '3':'0011', '4':'0100', '5':'0101', '6':'0110', '7':'0111', '8':'1000', '9':'1001', 'A':'1010','B':'1011','C':'1100','D':'1101','E':'1110','F':'1111'}
        # "for" goes through every letter and converts it to it's base 16 equivalent
        for j in range(len(numToConvert)):
            convertedNum=convertedNum+str(base16Dict[numToConvert[j]])
        print convertedNum

    """
    mission 3:
    getting a number from user in base 10, and a base, and then printing the number in the received base .
    """
elif missionNum==3:
    # asks user for number to convert
    print("please enter a number:")
    num = input()
    # asks user for the number's base
    print("please enter a base (16,8,4 or 2):")
    base = input()
    # remainderList will save all the remainders from the division
    remainderList=[]
    # "while" divides the number multiple times until the division is 0 and adds the remainders into a list
    while(num!=0):
        remainderList.append(num%base)
        num=int(num/base)
    # reversing the list so that it will be in the correct order
    remainderList.reverse()
    strNum=""
    # "for" deals with converting 10-15 numbers to a char.
    for i in range(len(remainderList)):
        if remainderList[i]==10:
            remainderList[i]='A'
        elif remainderList[i]==11:
            remainderList[i]='B'
        elif remainderList[i]==12:
            remainderList[i]='C'
        elif remainderList[i]==13:
            remainderList[i]='D'
        elif remainderList[i]==14:
            remainderList[i]='E'
        elif remainderList[i] == 15:
            remainderList[i] ='F'
        strNum+=str(remainderList[i])
    print strNum

    """
    mission 4:
    getting an 8-bit binary number from user, and printing it as signed and unsigned in decimal
    """
elif missionNum==4:
    # asks user for number to convert
    print("please enter an 8-bit binary number")
    bNum = raw_input()
    # copies the number to a list, and makes a duplicate of the list.
    bNumCopy=list(bNum)
    bNum = list(bNum)
    # reverse the original list so that the "for" will go through it in the correct order
    bNum.reverse()
    sum = 0
    # for converts the number from binary to decimal
    for i in range(8):
        bNum[i] = int(bNum[i]) * (2 ** i)
        sum = sum + int(bNum[i])
    print "unsigned:", sum
    # checks if the left letter is 0(and the numbers stays the same)
    if bNumCopy[0]=='0':
        print "signed:", sum
    else: #binary num starts with 1
        # does "NOT" to the number
        for i in range(8):
            if bNumCopy[i]=='0':
                bNumCopy[i]=1
            else:
                bNumCopy[i]=0
        sum=0
        # reverse the original list so that the "for" will go through it in the correct order
        bNumCopy.reverse()
        # converts the number to decimal
        for i in range(8):
            bNumCopy[i] = int(bNumCopy[i]) * (2 ** i)
            sum = sum + int(bNumCopy[i])
        #prints the number after adding 1 to it(as the conversion to negetive requires)
        print "signed:",-(sum+1)

# if user entered wrong mission number
else:
    print("Error")