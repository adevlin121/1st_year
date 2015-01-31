/*
 Aidan Devlin
 11-2-2014
 Program to print a tree
 */

#include <stdio.h>

main()
{
    //declaring variables
    int lines, space, stars, i, j=0;
    
    //reading in how many lines the tree will be in size
    scanf("%d",&lines);
    
    //setting up the first line of the tree
    space=lines;
    stars=1;
    
    //loop to count how manh lines to print
    for (j=0; j<lines; j++)
    {
        //loop to print the correct amount of spaces before the stars
        for (i=0; i<space; i++)
        {
            printf(" ");
        }
        
        //loop to print the correct number of stars
        for (i=0; i<stars; i++)
        {
            printf("*");
        }
        
        //getting ready for the next line of stars
        printf("\n");
        stars=stars+2;
        space--;
    }
    
    //loop to print the spaces before the trunk star
    for (i=0; i<lines; i++)
    {
        printf(" ");
    }
    
    //printing the trunk star
    printf("*");
}

