
/*
Aidan Devlin
C13765599
Programming with Persistent Data Assignment
28/04/2014
Program to create
*/

#include <stdio.h>
#include <string.h>

//functions that get called to execute different parts of the menu
//this function prints the menu
void pmenu(void);

//this function starts a dialogue to enter a new employee to teh file
void addemp(void);

//this functiont opens a dialogue that will delete an employee from record
void delemp(void);

//this function reads from the file to list all of the employees working in the company and prints the header file showing how many employees there in total are and how many have been deleted
void listemp(void);

//this function updates the header file to show how many new employees have been added and how many deleted and also deletes the employees that have been marked for deletion
void comprec(void);

//this is the structure for the record of each individual employee
typedef struct newemp
    {
        char empnum[6];
        char surname[16];
        char firstname[16];
        char empaddress[100];
        char depart[10];
        char years[3];
    }newemp;
//this is the structure for the header file
typedef struct header
{
    int total;
    int deleted;
}header;

//this is a global variable for the header file
struct header head;

    
//this ensures the same header will be written with each use of the program
int temptotal =0;
int tempdel=0;


int main()
{
    char menu = '0';
    int exit = 0;
    head.total = 0;
    head.deleted = 0;
    
    // try to read from the file
    FILE *fd;
    fd = fopen ("employees.dat", "rb");
    //if file does not exist execute this code to create the file
    if(!fd)
    {
        fd = fopen("employees.dat", "wb");
        
        //writing the header to the file
        fwrite(&head, sizeof(header), 1, fd);
        printf("\nfile created\n");
    }
    fclose(fd);
    
    //reading the header from the file to the program variables
    fopen("employees.dat", "rb");
    fseek(fd, 0, SEEK_SET);
    fread(&head, sizeof(header), 1, fd);
    fclose (fd);
    
    while(exit==0)
    {
        //this bui of code prints the menu and reads what the user wants to do using a switch statement
        pmenu();
        scanf("%1s",&menu);
        
        //this is a switch statemtent which calls each function in turn to execture the commands
        switch (menu)
        {
            case '1':
            {
                addemp();
                break;
            }
            
            case '2':
            {
                delemp();
                break;
            }
            
            case '3':
            {
                listemp();
                break;
            }
            
            case '4':
            {
                comprec();
                break;
            }
            
            case '5':
            {
                exit = 1;
                break;
            }
            
            default:
            {
                printf("\nInvalid input\n\n");
                break;
            }
            
        }//end switch()
    }//end while()
    
    return 0;
}


//function to print the menu
void pmenu(void)
{
    printf("\nMain Menu\n");
    printf("1. Add Employee\n");
    printf("2. Delete Employee\n");
    printf("3. List Employees\n");
    printf("4. Compact Records\n");
    printf("5. Exit \n");
    printf("\n Please select a number and hit enter\n");
}//end pmenu()

//this function adds an employee to the record using a 
void addemp(void)
{
    struct newemp input;
    struct newemp temp;
    
    //each of these lines request the user to enter the employee information into the record
    printf("\nPlease enter new employee number (5 digits)\n");
    scanf("%5s", &input.empnum);
    
    //checking if employee number already exists
    FILE *fd = fopen("employees.dat", "rb");
    fseek(fd, sizeof(header), SEEK_SET);
    while(fread(&temp, sizeof(newemp), 1,fd) != NULL)
    {
        if(temp.empnum == input.empnum)
        {
            printf("\nEmployee number already exists\nPlease enter a new number:\n");
        }//end if
    }//end while
    fclose(fd);
    
    printf("\nPlease enter employee surname:\n");
    scanf("%15s", &input.surname);
    printf("\nPlease enter employee first name:\n");
    scanf("%15s", &input.firstname);
    printf("\nPlease enter employee address:\n");
    flushall();
    gets(input.empaddress);
    printf("\nPlease enter employee department:\n");
    scanf("%9s", &input.depart);
    printf("\nPlease enter number of years employee has been at company:\n");
    scanf("%2s", &input.years);
    
    //this will write the new employee at the end of the file
    fopen("employees.dat", "ab+");
    fwrite(&input, sizeof(newemp),1,fd);
    fclose(fd);
    
    //incrementing the temporary total of employees each time this function ends sucessfully
    temptotal++;
}

//this function deletes an employee from the record using
void delemp(void)
{
    //temporary record of employee
    struct newemp temp;
    struct newemp del;
    char hat = '*';

    //asking the user to enter id of employee to delete
    printf("\nPlease enter number of employee to delete\n");
    scanf("%5s",&del.empnum);
    
    //opening the file to read and write
    FILE *fd;
    fd = fopen("employees.dat", "rb+");
    fseek(fd, sizeof(header), SEEK_SET);
    while(fread(&temp, sizeof(newemp), 1, fd) != NULL)
    {
        if(strcmp(del.empnum, temp.empnum) ==0)
        {
            fseek(fd, (sizeof(newemp)*(-1)), SEEK_CUR);
            fwrite(&hat, sizeof(hat), 1, fd);
            tempdel++;
            printf("\nFile marked for deletion");
            break;
        }//end if
    }//end while
    fclose(fd);
}//end delemp

//this function lists all of the employees currently on the system
void listemp(void)
{
    //temporary record to read from the file and print to screen
    struct newemp temp;
    
    //open the file to be edited
    FILE *fd = fopen("employees.dat", "rb");
    
    //going to the part of the file that contains the employees files
    fseek(fd, sizeof(head), SEEK_SET);
    
    //reading the employees afterwards
    while(fread(&temp, sizeof(newemp), 1,fd) != NULL)
    {
        if(temp.empnum[0] != '*')
        {
            //printing each part of the eployees files
            printf("\nEmployee number: %s", temp.empnum);
            printf("\nEmployee surname: %s", temp.surname);
            printf("\nEmployee name: %s", temp.firstname);
            printf("\nEmployee address: %s", temp.empaddress);
            printf("\nEmployee department: %s", temp.depart);
            printf("\nYears of employment: %s\n", temp.years);
        }
    }
    
    //closing the file
    fclose(fd);
    
    //reading the header part of the file
    printf("\n\nNumber of employees: %d",(head.total + temptotal));
    printf("\nNumber of deleted employees: %d\n", (head.deleted + tempdel));
}

//this function compresses the records
void comprec(void)
{
    //opening the file from the beginning where the header is located
    FILE *fd = fopen("employees.dat", "rb+");

    //reading in the 2 values for the total and deleted number of employees
    fread (&head, sizeof(header),1,fd);
    
    //adds the temporary number of employees made and deleted to the total number of employees made and deleted
    head.total = head.total + temptotal;
    head.deleted = head.deleted + tempdel;
    fclose(fd);
    
    //opening the file from the beginning again
    fopen("employees.dat", "rb+");
    
    //writing the new values for the total number of employees and deleted employees
    fwrite(&head, sizeof(header), 1, fd);
    fclose(fd);
    
    //resetting the temporary total and deleted number of employees to 0 to avoid accidental incrementing of total and deleted employee values
    temptotal=0;
    tempdel=0;
 
    //writing a new file
    FILE *tempfd;
    tempfd = fopen("tempemployees.dat", "wb");
        
    //writing the header to the temp file
    fwrite(&head, sizeof(header), 1, fd);
    printf("\nnew file created");
    fclose(tempfd);
    
    //creating a temporary record for copying the records between the files
    struct newemp temp;
    
    fopen("employees.dat", "rb");
    fopen("tempemployees.dat", "rb+");
    //writing in the employees not marked for deletion to the new file
    while(fread(&temp, sizeof(newemp), 1, fd) != NULL)
    {
        if(temp.empnum[0] != '*')
        {
            fwrite(&temp, sizeof(newemp), 1, tempfd);
            break;
        }//end if
    }//end while
    
    printf("\nNew file updated");
    
    //removing the old file still containing records for deletion
    remove("employees.dat");
    printf("\nOld file deleted");
    
    //renaming new file containing no records for deletion to the old file name 
    int re;
    re = rename("tempemployees.dat", "employees.dat");
    printf("\nNew file renamed\n");
    
    fclose(fd);
    fclose(tempfd);
}