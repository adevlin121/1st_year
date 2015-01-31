/*
 Lotto Program
 Aidan Devlin
 C13765599
 28-03-2014
 This program uses a switch statement along with multiple functions to carry out a set of menu options
 */

#include <stdio.h>
#include <stdbool.h>
#define LOTTO 6
#define BALLS 42

//prototypes for funtions
void printmenu(void);
void numbers(int *, int *, int *);
void show(int *);
void sort(int *);
void compare(int *, int *, int *);
void freq(int *, int *);
void showfreq(int *);
void exitprog(int *);
int getnum(int *);
int value(int, int *);

main()
{
    //welcoming the user
    printf("Welcome to the Lotto game!\n\n");
   
    //declaring variables and arrays
    int exit=0;
    char menu='0';
    int nums[LOTTO];
    int numsort[LOTTO];
    int matches =0;
    int bmatch =0;
    int range [BALLS];
    int i;
    int check=0;
    
    //initialising arrays
    for(i=0; i<BALLS; i++)
    {
        *(range+i)=0;
    }
    for(i=0; i<LOTTO; i++)
    {
        *(nums+i)=0;
        *(numsort+i)=0;
    }
    
    //while loop to keep the program running until exited
    while(exit==0)
    {
        //calling the menu
        printmenu();
        
        //reading the users input
        scanf("%1s",&menu);
        
        //switch statement reading the users menu option.
        //each case checks the option and calls the relevent function
        switch (menu)
        {
            case '1':
                numbers(nums, numsort, &check);
                
                //calling frequency here to ensure the frequency only changes when the numbers are updated
                freq(numsort, range);
                
                //prevents menu from printin until after user wants to continue
                printf("Hit any key to continue\n");
                getchar();
                getchar();
                break;
                
            case '2':
                if(check == 1)
                {
                    show(nums);
                    //prevents menu from printin until after user wants to continue
                    printf("Hit any key to continue\n");
                    getchar();
                    getchar();
                }
                
                else
                {
                    printf("Select numbers first!\n\n");
                    //prevents menu from printin until after user wants to continue
                    printf("Hit any key to continue\n");
                    getchar();
                    getchar();
                }
                break;
                
            case '3':
                if(check ==1)
                {
                    sort(numsort);
                    
                    //prevents menu from printin until after user wants to continue
                    printf("Hit any key to continue\n");
                    getchar();
                    getchar();
                }
                
                else
                {
                    printf("Select numbers first!\n\n");
                    
                    //prevents menu from printin until after user wants to continue
                    printf("Hit any key to continue\n");
                    getchar();
                    getchar();
                }
                
                break;
                
            case '4':
                if(check == 1)
                {
                    compare(numsort, &matches, &bmatch);
                    
                    //prevents menu from printin until after user wants to continue
                    printf("Hit any key to continue\n");
                    getchar();
                    getchar();
                }
                
                else
                {
                    printf("Select numbers first!\n\n");
                    
                    //prevents menu from printin until after user wants to continue
                    printf("Hit any key to continue\n");
                    getchar();
                    getchar();
                }
                
                break;
                
            case '5':
                if(check == 1)
                {
                    showfreq(range);
                    
                    //prevents menu from printin until after user wants to continue
                    printf("Hit any key to continue\n");
                    getchar();
                    getchar();
                }
                
                else
                {
                    printf("Select numbers first!\n\n");
                    
                    //prevents menu from printin until after user wants to continue
                    printf("Hit any key to continue\n");
                    getchar();
                    getchar();
                }
                
                break;
                
            case '6':
                exitprog(&exit);
                break;
                
            default:
                printf("You have not entered a valid input. Please enter a number from 1-6 and try again\n\n");
                break;
        }//end switch
    }//end while
}//end main

//this function will print the menu after each option has been selected
void printmenu(void)
{
    printf("1: Select your Lotto numbers\n");
    printf("2: Show your Lotto numbers\n");
    printf("3: Show your numbers in order of lowest to highest\n");
    printf("4: Check numbers\n");
    printf("5: Display frequency of numbers selected\n");
    printf("6: Exit Lotto game\n\n");
    printf("Please select an option from the menu by choosing a number and hitting enter:\n\n");
}//end printmenu

//this function is called to allow the user to enter their numbers
void numbers(int *nums, int *numsort, int *check)
{
    //declaring a local counter variable
    int i=0;
    int j=0;
    int temp=0;
    
    //allowing the user to access the other menu options
    *check = 1;
    
    //for loop to write into the array
    for(i=0; i<LOTTO; i++)
    {
        //asking the user to enter a number
        printf("Please enter number %d of your selection\n",i+1);
        
        //reading the users input into the array
        *(nums+i) = getnum(nums);
    }//end for()
    
    //sorting occurs here to avoid the same sort being called twice and causing unnecessary cpu usage
    
    //copying contents of array into second array to be sorted
    for (i=0; i<LOTTO; i++)
    {
        *(numsort+i) = *(nums+i);
    }//end for()
    
    //sorting the second array
    for(i=1; i<LOTTO; i++)
    {
        temp=*(numsort+i);
        j=i-1;
        while((temp<*(numsort+j))&&(j>=0))
        {
            *(numsort+j+1)=*(numsort+j);
            j=j-1;
        }//end while
        *(numsort+j+1)=temp;
    }//end for()
}//end numbers()

//this function is called to show the user the numbers they selected in the order they selected them in
void show(int *nums)
{
    //local counter variable
    int i;
    
    //showing the user the numbers they entered
    printf("The numbers you have entered are:\n");
    
    //for loop to read from array
    for (i=0; i<LOTTO; i++)
    {
        printf("%d ",*(nums+i));
    }
    
    printf("\n\n");
}//end show()

//this function is called to show the user the numbers they selected sorted lowest to highest
void sort(int *numsort)
{
    //local counter
    int i;
    
    printf("The numbers you entered lowest to highest are:\n");
    
    //for loop to read from array
    for(i=0; i<LOTTO; i++)
    {
        printf("%d ", *(numsort+i));
    }//end for()
    
    printf("\n\n");
}//end sort()

//this function is called to check the users numbers with the winning numbers
void compare(int *numsort, int *matches, int *bmatch)
{
    //local variables and initialising winning numbers
    int win1 =1;
    int win2 =3;
    int win3 =5;
    int win4 =7;
    int win5 =9;
    int win6 =11;
    int bonus =42;
    int i;
    
    //for loop to check chosen numbers against winning numbers
    for (i=0; i<LOTTO; i++)
    {
        //if one of the elements of the array is the same as the users it will increment the match counter
        if (*(numsort+i) == win1 || *(numsort+i) == win2 || *(numsort+i) == win3 || *(numsort+i) == win4 || *(numsort+i) == win5 || *(numsort+i) == win6)
        {
            *(matches) = (*(matches)+1);
        }//end if
    }//end for
    
    //for loop to check bonus number
    for (i=0; i<LOTTO; i++)
    {
        if (*(numsort+i) == bonus)
        {
            *(bmatch)=1;
        }//end if
    }//end for
    
    //ifs and else ifs showing the user what they did or didnt win
    if (*matches == 6)
    {
        printf("Congratulations! You have won the Jackpot!\n\n");
    }//end if
    
    else if ((*matches == 5) && (*bmatch == 1))
    {
        printf("Congratulations! You have won a new car!\n\n");
    }//end else if
    
    else if (*matches == 5)
    {
        printf("Congratulations! You have won a holiday!\n\n");
    }//end else if
    
    else if ((*matches == 4) && (*bmatch == 1))
    {
        printf("Congratulations! You have won a weekend away!\n\n");
    }//end else if
    
    else if (*matches == 4)
    {
        printf("Congratulations! You have won a night out!\n\n");
    }//end else if
    
    else if ((*matches == 3) && (*bmatch == 1))
    {
        printf("Congratulations! You have won a cinema ticket!\n\n");
    }//end else if
    
    else
    {
        printf("I'm sorry you didn't win. \nBetter luck next time!\n\n");
    }//end else
}//end compare()

//this function is called to show the user how often they have selected each number
void freq(int *numsort, int *range)
{
    //local variables
    int i,j;
    
    //incrementing the values of the range array for each number entered
    for(i=0; i<BALLS; i++)
    {
        for(j=0; j<LOTTO; j++)
        {
            if(*(numsort+j) == (i+1))
            {
                *(range+i) = (*(range+i)+1);
            }//end if
        }//end inner for
    }//end outer for
}//end freq()

//this function is called to end the program
void exitprog(int *exit)
{
    printf("Thank you for playing the Lotto game!\nGoodbye!");
    *exit=1;
}//end exitprog()

//this function is called to ensure that only correct integer values re entered into the selection
int getnum(int *nums)
{
    //declaring local variables
    bool status;
    int num;
    
    //reading an input
    status = scanf("%d", &num);
    
    //checking the input is valid
    if (status !=1)
    {
        while (status != 1)
        {
            //to stop infinite looping
            getchar();
            
            //telling the user to enter a valid input
            printf("Invalid entry please try again. Select a number between 1 and 42 (inclusive)\n");
            
            //reading user input
            status = scanf("%d",&num);
        }//end while
    }//end if
    
    //calling function to check valid value
    num = value(num, nums);
    
    //returning the value to where the function was called
    return num;
}//end getnum()

//this function is called to show the frequency of each number inputted
void showfreq(int *range)
{
    //local variables
    int i;
    
    //for loop to read from array
    for(i=0; i<BALLS; i++)
    {
        if(*(range+i) > 0)
            printf("The number %d has been used %d times\n", (i+1), *(range+i));
    }//end for
    
    //spacing
    printf("\n");
}//end showfreq

//this function checks the value of the input to see if its too high or low
int value(int num, int *nums)
{
    //local variables
    int i;
    
    //if to check value
    if((num <= 0) || (num >=43))
    {
        printf("Invalid number try again\n");
        num = getnum(nums);
    }
    
    //for loop to check if numbers have been entered before
    for(i=0; i<LOTTO; i++)
    {
        if ((num) == (*(nums+i)))
        {
            printf("Cannot use the same number twice!\n\n");
            num = getnum(nums);
        }//end if
    }//end for
    
    //returning valid number to getnum()
    return num;
}