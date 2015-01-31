/*
 Aidan Devlin
 25-2-2014
 Program to convert temperatures and find the average in kelvin
 */

#include <stdio.h>
#define NUM 5

//prototypes for functions
float convert_temp(float[]);
void in_Kelvin(float *ptr);

main()
{
    //declaring variables
    int i;
    float temps_c[NUM];
    float ave=0;
    
    //asking the user to input 5 temperatures
    printf("Please input 5 temperatures in Celcius\n");
    
    //reading in the users answers
    for (i=0; i<NUM; i++)
    {
        scanf("%f",&temps_c[i]);
    }
    
    //calling the function to convert the temperatures
    ave=convert_temp(temps_c);
    
    //displaying the average temperature in celcius
    printf("\nThe average temperature in Celcius is %f\n",ave);
    
    //calling the function to convert celcius to kelvin
    in_Kelvin(&ave);
    
    printf("The average temperature in Kelvin is %f",ave);
}

//declaring convert_temp function
float convert_temp(float temps_c[])
{
    //declaring an array for fahrenheit temps to be stored into
    float temps_f[NUM];
    int i=0;
    float total=0;
    float ave=0;
    
    //for loop to convert celcius numbers to fahrenheit and add celcius temps
    for(i=0; i<NUM; i++)
    {
        temps_f[i]=((temps_c[i]*9)/5)+32;
        total=temps_c[i]+total;
    }
    
    //for loop to read out temps and show conversion
    for(i=0; i<NUM; i++)
    {
        printf("%f degrees Celcius = %f degrees Fahrenheit\n",temps_c[i],temps_f[i]);
    }
    
    //calculating the average
    ave=total/NUM;
    
    //returning the average to main
    return ave;
}

//declaring the in_Kelvin function
void in_Kelvin(float *ptr)
{
    //line of code to convert celcius to kelvin
    *ptr=*ptr+273;
}