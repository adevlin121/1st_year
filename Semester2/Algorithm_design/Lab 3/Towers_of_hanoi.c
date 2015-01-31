/*
 Aidan Devlin
 17/2/2014
 Program to get the fewest moves for tower of hanoi problem
 */

#include <stdio.h>

//function prototype
void movetower (int, int, int, int);

int moves;
main()
{
    //declaring variables
    int disks=0;
    int source=1;
    int dest=3;
    int spare=2;
    moves=0;
    
    //asking the user to input the number of disks
    printf("How many disks?\n");
    scanf("%d",&disks);
    printf("\n");
    
    //decreses disks by 1 to account for disk 0
    disks--;
    
    
    //calling the function
    movetower(disks, source, dest, spare);
    printf("took %d moves",moves);
}

//declaring the function
void movetower(int disks, int source, int dest, int spare)
{
    if (disks==0)
    {
        printf("Move disk %d from tower %d to tower %d\n",disks, source, dest);
        moves++;
    }
    
    else
    {
        movetower(disks-1, source, spare, dest);
        printf("Move disk %d from tower %d to tower %d\n",disks, source, dest);
        moves++;
        movetower(disks-1, spare, dest, source);
    }
}