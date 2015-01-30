//
//  main.c
//  Assignment1
//
//  Created by Aidan Devlin on 05/11/2013.
//  Copyright (c) 2013 Aidan Devlin. All rights reserved.
//

#include <stdio.h>

main()
{
    //declaring a lot of variables
    char menu='0';
    char qnum='0';
    int q1ans=0;
    int q2ans=0;
    int q3ans=0;
    int q4ans=0;
    int q5ans=0;
    int correct=0;
    int wrong=0;
    int exit=1;
    int check=0;
    int qcheck=0;
    int check2=1;
    
    while (exit==1)
    {
        
        
        
        //printing the menu
        printf("Menu\n");
        printf("1. Enter the number of questions to be asked for this quiz\n");
        printf("2. Start quiz\n");
        printf("3. Show your score\n");
        printf("4. Exit\n");
    
        //scanning the selection of the menu
        scanf("%1s",&menu);
    
        switch (menu)
        {
            case '1':
                
                //this if is to make sure the user checks the score of the previous round before setting a new number of questions
                if (check2==1)
                {
                    //while loop to ensure a valid input has been entered
                    while (qcheck==0)
                    {
                        //printing and scanning the number of questoins for the quiz
                        printf("\nHow many questions would you like in this quiz? (max. 5)\n");
                        scanf("%1s",&qnum);
                        
                        //telling the user how many questions they have selected
                        if (qnum=='1' || qnum=='2' || qnum=='3' || qnum=='4' || qnum=='5')
                        {
                            printf("\nYou will be asked %c questions\n\n",qnum);
                            qcheck=1;
                        }
                        
                        //telling the user they havent entered a valid question number
                        else
                        {
                            printf("\nInvalid number of questions");
                        }
                        
                    }//end while
                    
                    //letting the user start the quiz after setting a number of questions
                    check=1;
                    qcheck=0;
                    
                    //setting counters to 0 to ensure no remnants of a previous round remain
                    correct=0;
                    wrong=0;

                }//end if
                
                //telling the user they havent checked the scores yet
                else
                {
                    printf("\nNot allowed at this time \nCheck score first!\n\n");
                }
                
                break;
        case '2':
                
                //running the quiz using nested ifs to check which questions to run
                
                //initialising variables to 0 again to ensure no remnants of previous rounds remain
                q1ans=0;
                q2ans=0;
                q3ans=0;
                q4ans=0;
                q5ans=0;
                
                //Q1
                if (qnum=='1' || qnum=='2' || qnum=='3' ||qnum=='4' ||qnum=='5')
                {
                    correct=0;
                    wrong=0;
                    printf("\nQ1. What is the sum of 4, 8, and 13?\n");
                    scanf("%d",&q1ans);
                    
                    
                    //checking Q1 and adding to the relevant counters using an if/else and showing the user what they entered
                    if (q1ans==25)
                    {
                        correct++;
                        printf("You entered: %d - Correct!\n",q1ans);
                    }
                    else
                    {
                        printf("You entered: %d - Wrong!\nCorrect answer: 25\n",q1ans);
                        wrong++;
                    }
                    printf("\n");
                    check2=0;
                }
                
                
                //Q2
                if (qnum=='2' || qnum=='3' || qnum=='4' || qnum=='5')
                {
                    printf("Q2. What is 4x(5^2)?\n");
                    scanf("%d",&q2ans);
                    
                    
                    //checking Q2 same as previous
                    if (q2ans==100)
                    {
                        correct++;
                        printf("You entered: %d - Correct!\n",q2ans);
                    }
                    else
                    {
                        wrong++;
                        printf("You entered: %d - Wrong!\nCorrect answer: 100\n",q2ans);
                    }
                    printf("\n");
                }
                
                //Q3
                if (qnum=='3' || qnum=='4' || qnum=='5')
                {
                    printf("Q3. What is the square root of 49?\n");
                    scanf("%d",&q3ans);
                    
                    
                    //checking Q3 same as previous
                    if (q3ans==7)
                    {
                        correct++;
                        printf("You entered: %d - Correct!\n",q3ans);
                    }
                    else
                    {
                        wrong++;
                        printf("You entered: %d - Wrong!\nCorrect answer: 7\n",q3ans);
                    }
                    printf("\n");

                }
                
                //Q4
                if (qnum=='4' || qnum=='5')
                {
                    printf("Q4. What is the remainder of 24/9?\n");
                    scanf("%d",&q4ans);
                    
                    
                    //checking Q4 same as previous
                    if (q4ans==6)
                    {
                        correct++;
                        printf("You entered: %d - Correct!\n",q4ans);
                    }
                    else
                    {
                        wrong++;
                        printf("You entered: %d - Wrong!\nCorrect answer: 6\n",q4ans);
                    }
                    printf("\n");
                }
                
                //Q5
                if (qnum=='5')
                {
                    printf("Q5. What is (13-5)x(45/9)?\n");
                    scanf("%d",&q5ans);
                    
                    
                    //checking Q5 same as previous
                    if (q5ans==40)
                    {
                        correct++;
                        printf("You entered: %d - Correct!\n",q5ans);
                    }
                    else
                    {
                        wrong++;
                        printf("You entered: %d - Wrong!\nCorrect answer: 40\n",q5ans);
                    }
                    printf("\n");
                }
            
                //telling the user they cannot play the quiz without checking scores first
                if (check==0)
                {
                    printf("\nThat option is not currently available!\n\n");
                }
                
                //this is to ensure the user doesnt start a quiz without setting a number of questions first
                check=0;
                qnum='0';
                break;
                
            case '3':
                
                //checking if they havent done the quiz and then telling the user to do it
                if (correct==0 && wrong==0)
                {
                    printf("\nYou haven't taken the quiz yet!\n\n");
                }
                
                //printing the scores
                else
                {
                    printf("\nYou answered %d questions correct and %d incorrect\n\n",correct,wrong);
                    
                    check=1;
                }
                
                //letting the user start the quiz again after checking the score
                check2=1;
                
                break;
            case '4':
                
                //this changes the value of exit and thus stopping the while loop making the program terminate
                exit--;
                
                break;
            default:
                
                //if an invalid entry on the menu is selected this will be displayed
                printf("\nYou have entered and invalid input \nPlease try again\n\n");
                break;
        }//end switch
    }//end while
}//end main

