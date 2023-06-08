//include necessary header file
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
//making structure necessary variables
struct personal_details //structure for personal details
{
    char name[100],fathers_name[100],mothers_name[100],citizenship_no[10],Gender[10];
    char mobile_no[15];
    int age;
} prec,ptrn[20]; //declaring structure variable

struct date //structure for time period
{
    int day,month,year;
} dob,acc_opendate,dtrn[20],dopentrn[20]; //declaring structure variable

struct address //structure for address variables
{
    char country[20],state[20],district[20],muncipality[20];
    int ward_no;
} add,atrn[20]; //declaring structure variable

struct account_details //structure for account details
{
    int acc_no;
    char acc_type[100];
    float amt;
} accrec,check,acctrn[20]; //declaring the structure variable
// Main function
void main()
{
    int r;
    headmsg("BFK BANK LIMITED"); // Display the header msg
    line(25,7); // Draw the line

    printf("\v\v\v\v\v");
    printf("\t\t\t\t\t\t\t\t            WELCOME   \v\v");
    printf("\t\t\t\t\t\t\t\t              TO      \v\v");
    printf("\t\t\t\t\t\t\t\t      BFK BANK MANAGEMENT  \v\v");
    printf("\t\t\t\t\t\t\t\t          APPLICATION \n");
    line(25,7); // Draw the line
    printf("\n\t\t\t\t\t\t\t\t        -Together we grow");
    printf("\n\n\n\n\t\t\t\t     Press any key to continue....");
    getch();
    //Call the login function to validate username and password
    r=login();
    if(r==1) //Check if login is successfull
    {
        Menu(); //If login is successful continue to main menu
    }
    else
    {
        Close_app(); //If login isnot successfull exit the application
    }
}
//function to calculate interest accured in real time
float interest_check(char acc_type[50],float amt,int openy,int openm,int opend)
{
    // Declare variables for time and interest calculation
    float t,r,p,SI;
    float year_diff,month_diff,day_diff;
    time_t current_time;

    time(&current_time); // Get the current time

    struct tm *local_time = localtime(&current_time); // Convert current_time to a struct tm

    // Calculate the difference in years, months, and days between account opening date and today's date
    year_diff = (local_time->tm_year + 1900 - openy);
    month_diff = abs(local_time->tm_mon + 1 - openm) / 12.0;
    day_diff= abs(local_time->tm_mday - opend) / 365.0;

    // Calculate the difference in time in terms of a fractional year
    t=year_diff+month_diff+day_diff;

    // Determine interest rate and principal amount based on account type
    if(stricmp(acc_type,"Savings")==0)
    {
        p=amt;
        r=8.03;
    }
    else if(stricmp(acc_type,"Current")==0)
    {
        p=amt;
        r=0;
    }
    else if(stricmp(acc_type,"FD1")==0)
    {
        p=amt;
        r=9;
    }
    else if(stricmp(acc_type,"FD2")==0)
    {
        p=amt;
        r=9.49;
    }
    else if(stricmp(acc_type,"FD3")==0)
    {
        p=amt;
        r=9.99;
    }
    SI=(p*t*r)/100; //calculate the interest using simple interest formula
    return SI; //returning the interest accurred
}
// Function to display and manage the main menu
void Menu()
{
    int choice=0;
    while(choice!=8) // Loop until the user chooses to exit (choice = 8)
    {
        system("cls"); // Clear the console screen
        system("color 3"); // Set console color

        headmsg("MAIN MENU"); // Display the main menu header
        line(32, 5); // Draw a line

        // Display menu options
        printf("\v\v\n\t\t\t\t\t\t\t\t    1.Create new account \v");
        printf("\n\t\t\t\t\t\t\t\t    2.Update the details \v");
        printf("\n\t\t\t\t\t\t\t\t    3.View all accounts \v");
        printf("\n\t\t\t\t\t\t\t\t    4.Search for a account \v");
        printf("\n\t\t\t\t\t\t\t\t    5.Delete account\v");
        printf("\n\t\t\t\t\t\t\t\t    6.Transactions \v");
        printf("\n\t\t\t\t\t\t\t\t    7.Update Login Credentials \v");
        printf("\n\t\t\t\t\t\t\t\t    8.Exit \v");

        line(32, 5); // Draw a line

        printf("\n\t\t\t\t\t\t\t\t  Enter your choice....");
        scanf("%d", &choice); // Get user's menu choice

        // Execute the chosen menu option using a switch statement
        switch(choice)
        {
        case 1:
            New_acc(); //Create new account
            break;
        case 2:
            Update_details(); //Update the account details
            break;
        case 3:
            View_all_acc(); //View all accounts details
            break;
        case 4:
            Search_acc(); //Search for a particular account
            break;
        case 5:
            Delete_acc(); //Delete account
            break;
        case 6:
            Transaction(); //Perform various transactions
            break;
        case 7:
            Update_user_password(); //Change the username or password
            break;
        case 8:
            Close_app(); //Exit the application
            break;
        default:
            printf("\n\n\t\t\t\t\t\t\t INVALID CHOICE !!! PLEASE CHOOSE AGAIN");
            delay(40000000000); //// Delay to provide user feedback
        }
    }
}
// Function to create a new account
void New_acc()
{
    int check_acc_no,record_found;
    char try_return;
    int acc_no=0;
    int main_exit;
    time_t current_time;

    time(&current_time); // Get the current time

    struct tm *local_time = localtime(&current_time); // Convert current_time to a struct tm

    FILE *fp;

    // Open the bank.dat file in append and read mode
    fp = fopen("bank.dat", "a+");

    // Check if the file was opened successfully
    if (fp==NULL)
    {
        printf("\n\n\t\t\t\t !!Error loading the file..!!");
        return;
    }
    //Loop for entering the account details
    while(1)
    {
        system("cls"); // Clear the console screen
        headmsg("New Account Form"); // Display the header
        line(32, 5); // Draw a line
        record_found = 0; // Initialize record_found variable

        // Get account number to check its existence

        printf("\n\n\t\t\t\t       Enter account number:");
        scanf("%d",&check_acc_no);

        // Loop through the file to check for existing account number
        while(fscanf(fp,"%d %d %d %s %s %s %s %d %s %d %d %d %s %s %s %s %s %d %d %s %f",&acc_opendate.year,&acc_opendate.month,&acc_opendate.day,
                     prec.name,prec.fathers_name,prec.mothers_name,prec.Gender,&prec.age,prec.citizenship_no,&dob.year,&dob.month,&dob.day,prec.mobile_no,
                     add.country,add.state,add.district,add.muncipality,&add.ward_no,&accrec.acc_no,accrec.acc_type,&accrec.amt)!=EOF)
        {
            if (check_acc_no == accrec.acc_no)
            {
                record_found=1;
                break;
            }
        }
        rewind(fp); // Move file pointer to the beginning

        // If the record is found account number exists
        if (record_found == 1)
        {
            printf("\n\n\t\t\t\t\t\t\t       Account number already in use !!");
            printf("\n\n\t\t\t\t\t\t\t Press T to try again and anykey to return to main menu....");
            scanf(" %c",&try_return);

            // If the user wants to try again, continue the loop
            if(try_return == 't' || try_return == 'T')
            {
                continue;
            }
            else
            {
                break; // Exit the loop if the user doesn't want to try again
            }

        }
        else
        {
            accrec.acc_no = check_acc_no; // Assign the entered account number
            // Prompt user for personal information
            printf("\n\n\n\t\t\t\t\t\t\t\t  **** Personal Information **** ");
            printf("\n\n\t\t\t\t\t Today's Date(YEAR/MM/DD):");
            scanf(" %d %d %d",&acc_opendate.year,&acc_opendate.month,&acc_opendate.day);
            printf("\n\n\t\t\t\t\t Name:");
            scanf("%s",prec.name);
            printf("\n\n\t\t\t\t\t Father Name:");
            scanf("%s",prec.fathers_name);
            printf("\n\n\t\t\t\t\t Mother Name:");
            scanf("%s",prec.mothers_name);
            printf("\n\n\t\t\t\t\t Gender:");
            scanf("%s",prec.Gender);
            printf("\n\n\t\t\t\t\t Age:");
            scanf("%d",&prec.age);
            printf("\n\n\t\t\t\t\t Citizenship No:");
            scanf("%s",prec.citizenship_no);
            printf("\n\n\t\t\t\t\t Date of Birth(YEAR/MM/DD):");
            scanf(" %d %d %d",&dob.year,&dob.month,&dob.day);
            printf("\n\n\t\t\t\t\t Phone no :");
            scanf("%s",&prec.mobile_no);

            // Call Address function to input address details
            Address_details();

            // Call Account function to input account details
            Account_details();

            //Write the data int the file
            fprintf(fp,"%d %d %d %s %s %s %s %d %s %d %d %d %s %s %s %s %s %d %d %s %.2f \n",acc_opendate.year,acc_opendate.month,acc_opendate.day,prec.name,prec.fathers_name,
                    prec.mothers_name,prec.Gender,prec.age,prec.citizenship_no,dob.year,dob.month,dob.day,prec.mobile_no,add.country,add.state,add.district,add.muncipality,add.ward_no,
                    accrec.acc_no,accrec.acc_type,accrec.amt);

            printf("\n\n\n\t\t\t\t\t\t\t\t  **** Account created succesfully ****"); //Display the message to inform user that account has been created successfully
            printf("\n\n\t\t\t\t\t\t\t Press A to add more records and anykey to return to main menu...."); //Ask user if they want to add more record or return to main menu
            scanf(" %c",&try_return);

            // If the user wants to add more record,continue the loop
            if(try_return == 'a' || try_return == 'A')
            {
                continue;
            }
            else
            {
                break; //Exit the loop if the user doesn't want to try again
            }
        }
    }
    fclose(fp); //Close the file
}
//Function to input account details
void Account_details()
{
    system("cls"); // Clear the console screen
    char ch;
    int choice;

    // Display header and account information section
    headmsg("New Account Form");
    line(32,5); //Draw a line

    printf("\n\n\n\t\t\t\t\t\t\t\t  **** Account Information **** ");
    printf("\n\n\n\t\t\t\t\t Types of account:");
    printf("\n\n\t\t\t\t\t\t 1.Savings");
    printf("\n\t\t\t\t\t\t 2.Current");
    printf("\n\t\t\t\t\t\t 3.Fixed_Deposit1(3 to 12 months @ 9%%)");
    printf("\n\t\t\t\t\t\t 4.Fixed_Deposit2(12 to 24 months @ 9.49%%)");
    printf("\n\t\t\t\t\t\t 5.Fixed_Deposit3(above 24 months @ 9.99%%)");
    //Get user's choice for account type
account_type:
    printf("\n\n\t\t\t\t\t\t\t\t  Please enter your choice (1-5): ");
    scanf("%d",&choice);

    //Assign the selected account type based on user's choice
    switch (choice)
    {
    case 1:
        strcpy (accrec.acc_type,"Savings");
        break;
    case 2:
        strcpy (accrec.acc_type, "Current");
        break;
    case 3:
        strcpy (accrec.acc_type, "FD1");
        break;
    case 4:
        strcpy (accrec.acc_type, "FD2");
        break;
    case 5:
        strcpy (accrec.acc_type,"FD3");
        break;
    default:
        printf("\n\n\a\t\t\t\t\t\t\t    Invalid choice. Please select a number from 1 to 5.\n");
        goto account_type; //Ask for input again if choice is invalid
    }

    //Ask the user if they want to make a initial deposit
    printf("\n\n\t\t\t\t\t\t\t\t  Do you want to make a deposit now[Y/N]?");
    scanf(" %c",&ch);
    getchar();

    // If user wants to make a deposit,get the deposit amount
    if( ch == 'y' || ch == 'Y' )
    {
        printf("\n\n\t\t\t\t\t\t Enter the amount to deposit:");
        scanf(" %f",&accrec.amt);
    }
    else
    {
        accrec.amt=0.00; //Set the deposit amount to 0 if no initial deposit is made
    }
}
// Function to input the address details
void Address_details()
{
    system("cls"); // Clear the console screen

    // Display header and address information section
    headmsg("New Account Form");
    line(32,5);

    printf("\n\n\t\t\t\t\t\t\t\t **** Address Information **** ");
    printf("\v\n\t\t\t\t\t Country:"); //Get the country name
    scanf("%s",add.country);
    printf("\v\n\t\t\t\t\t Province:"); // Get the province name
    scanf("%s",add.state);
    printf("\v\n\t\t\t\t\t District:"); // Get the district name
    scanf("%s",add.district);
    printf("\v\n\t\t\t\t\t Muncipality:"); // Get the muncipality name
    scanf("%s",add.muncipality);
    printf("\v\n\t\t\t\t\t Ward No:"); //Get the ward number
    scanf("%d",&add.ward_no);
}
//Function to update the account details
void Update_details()
{
    char new_state[20],new_district[20],new_muncipality[20],new_mob_no[15],try_return;
    int choice,updt_acc_no,new_ward_no,test=0;
    float interest_earned;
    FILE *fp,*fp1;

    // Open the bank.dat file in read mode and new.dat file in write mode
    fp=fopen("bank.dat","r");
    fp1=fopen("new.dat","w");
    // Check if the files were opened successfully
    if (fp == NULL || fp1 == NULL)
    {
        printf("\n\n\t\t\t\t !!Error loading the file..!!");
        return;
    }

    // Loop for account deletion
    while(1)
    {
        system("cls"); // Clear the console screen
        headmsg("UPDATING DETAILS"); // Display the header
        line(32, 5); // Draw a line

        printf("\n\t\t\t\t\t\t     Please provide account number to update its details");
        printf("\n\n\n\t\t\t\t\t Account Number:");
        scanf("%d",&updt_acc_no);

        // Loop through the file to find the account to be updated
        while (fscanf(fp, "%d %d %d %s %s %s %s %d %s %d %d %d %s %s %s %s %s %d %d %s %f\n", &acc_opendate.year, &acc_opendate.month, &acc_opendate.day,
                      prec.name, prec.fathers_name, prec.mothers_name, prec.Gender, &prec.age, prec.citizenship_no, &dob.year, &dob.month, &dob.day, prec.mobile_no,
                      add.country, add.state, add.district, add.muncipality, &add.ward_no, &accrec.acc_no, accrec.acc_type, &accrec.amt) != EOF)
        {
            if(updt_acc_no == accrec.acc_no)
            {
                test++; //increase the test value to check record was found or not later

                interest_earned=interest_check(accrec.acc_type,accrec.amt,acc_opendate.year,acc_opendate.month,acc_opendate.day); //call the interest function to get the interest accured
                printf("\n\n\n     +----------------------+-----------------+--------------+------------------+--------------+----------------------+---------------+-----------------+\n");
                printf("     | %-20s | %-10s  | %-10s | %-15s  | %-10s   | %-15s | %-10s |    %-9s    |",
                       "Account Name", "Account Number", "Account Type", "Account Balance", "Interest", "Account Opening Date", "Mobile Number", "Address");
                printf("\n     +----------------------+-----------------+--------------+------------------+--------------+----------------------+---------------+-----------------+\n");
                printf("     | %-20s |    %-10d   |   %-10s | Rs. %-12.2f | Rs. %-8.2f |      %02d/%02d/%04d      |   %-10s  |   %s-%-2d    |\n",
                       prec.name, accrec.acc_no, accrec.acc_type, accrec.amt, interest_earned, acc_opendate.day, acc_opendate.month, acc_opendate.year, prec.mobile_no, add.district, add.ward_no);
                printf("     +----------------------+-----------------+--------------+------------------+--------------+----------------------+---------------+-----------------+\n");

                //Loop to choose the detail to be updated
                while(1)
                {
                    printf("\n\n\t\t\t\t\t\t      1.Update Mobile No:");
                    printf("\n\n\t\t\t\t\t\t      2.Update Address:");
                    printf("\n\n\n\t\t\t\t\t\t    Which details would you like to update...?");
                    scanf("%d",&choice);

                    //Update the mobile number
                    if(choice == 1)
                    {
diff_mob:
                        printf("\n\n\t\t\t\t\t\t    New Mobile No:");
                        scanf("%s",new_mob_no);
                        // Check if the new mobile number is the same as the old one
                        if(stricmp(prec.mobile_no,new_mob_no)==0)
                        {
                            printf("\n\n\n\n\a\t\t\t\t\t\t\t\t\t **** Cannot use same Mobile Number ****");
                            printf("\n\n\n\n\t\t\t\t\t\t\t\t\t Please Select different Mobile Number");
                            delay(50000000);
                            goto diff_mob;
                        }
                        else
                        {
                            // Write the updated details to the new file
                            fprintf(fp1,"%d %d %d %s %s %s %s %d %s %d %d %d %s %s %s %s %s %d %d %s %.2f \n",acc_opendate.year,acc_opendate.month,acc_opendate.day,prec.name,prec.fathers_name,
                                    prec.mothers_name,prec.Gender,prec.age,prec.citizenship_no,dob.year,dob.month,dob.day,new_mob_no,add.country,add.state,add.district,add.muncipality,add.ward_no,
                                    accrec.acc_no,accrec.acc_type,accrec.amt);
                            printf("\n\n\n\n\t\t\t\t\t\t\t\t **** Account Details Updated Successfully ****");
                            break; // Exit the loop after successful updating the details
                        }

                    }

                    //Update the address
                    else if( choice == 2)
                    {
                        //Get the new address details
diff_cred:
                        printf("\n\n\t\t\t\t\t\t    New Province:");
                        scanf("%s",new_state);
                        printf("\n\n\t\t\t\t\t\t    New District:");
                        scanf("%s",new_district);
                        printf("\n\n\t\t\t\t\t\t    New Metropolitan/Muncipality:");
                        scanf("%s",new_muncipality);
                        printf("\n\n\t\t\t\t\t\t    New Ward No:");
                        scanf("%d",&new_ward_no);

                        // Check if the new credentials are the same as the old ones
                        if(stricmp(add.state,new_state)==0 && stricmp(add.district,new_district)==0 && stricmp(add.muncipality,new_muncipality)==0 && add.ward_no == new_ward_no)
                        {
                            printf("\n\n\n\t\t\t\t\t\t\t\t **** Cannot use same Credentials ****");
                            printf("\n\n\n\t\t\t\t\t\t\t\t Please Select different Credentials");
                            delay(50000000); // delay to get user feedback
                            goto diff_cred; // Go back to entering new credentials
                        }
                        else
                        {
                            // Write the updated details to the new file
                            fprintf(fp1,"%d %d %d %s %s %s %s %d %s %d %d %d %s %s %s %s %s %d %d %s %.2f \n",acc_opendate.year,acc_opendate.month,acc_opendate.day,prec.name,prec.fathers_name,
                                    prec.mothers_name,prec.Gender,prec.age,prec.citizenship_no,dob.year,dob.month,dob.day,prec.mobile_no,add.country,new_state,new_district,new_muncipality,new_ward_no,
                                    accrec.acc_no,accrec.acc_type,accrec.amt);
                            printf("\n\n\n\n\n\t\t\t\t\t\t\t\t **** Account Details Updated Successfully ****");
                            break; // Exit the loop after successful update
                        }
                    }
                    else
                    {
                        printf("\n\n\a\t\t\t\t\t\t\t Invalid choice Please choose carefully!!!");
                        delay(50000000); //delay to get user feedback
                    }
                }
            }
            else
            {
                // Retain other accounts and write them to the new file
                fprintf(fp1,"%d %d %d %s %s %s %s %d %s %d %d %d %s %s %s %s %s %d %d %s %.2f \n",acc_opendate.year,acc_opendate.month,acc_opendate.day,prec.name,prec.fathers_name,
                        prec.mothers_name,prec.Gender,prec.age,prec.citizenship_no,dob.year,dob.month,dob.day,prec.mobile_no,add.country,add.state,add.district,add.muncipality,add.ward_no,
                        accrec.acc_no,accrec.acc_type,accrec.amt);
            }
        }
        rewind(fp); //Return the file pointer to initial position

        // If the test is 0, account record was not found
        if (test == 0)
        {
            printf("\n\n\n\n\a\t\t\t\t\t\t\t\t        Record not found!!!");
            printf("\n\n\t\t\t\t\t\t\t\t Please check credentials properly!");
            delay(50000000);
            printf("\n\n\t\t\t\t\t\t\t Press T to try again and anykey to return to main menu....");
            scanf(" %c",&try_return);

            // If the user wants to try again, continue the loop
            if(try_return == 't' || try_return == 'T')
            {
                continue;
            }
            else
            {
                break; // Exit the loop if the user doesn't want to try again
            }
        }
        else
        {
            printf("\n\n\t\t\t\t\t\t Press any key to return to main menu....");
            getch();
            break; // Exit the loop when the operation is completed
        }
    }
    fclose(fp); //Close the original file
    fclose(fp1); //Close the new file
    remove("bank.dat");//remove the new file to bank.dat
    rename("new.dat","bank.dat");// rename the new.dat to bank.dat
}
//Function to view records of all customer or account
void View_all_acc()
{
    system("cls"); //Clear the console screen

    // Initialize variables for testing,interest calculation and user choice.
    int test=0;
    float interest_earned=0;
    char choice;

    // Display a header message and a dividing line.
    headmsg("ALL ACCOUNT DETAILS");
    line(32,5);

    FILE *fp;
    fp=fopen("bank.dat","r"); //Open the file to read the data

    //Check if file was opened properly or not
    if (fp==NULL)
    {
        printf("\n\n\t\t\t\t !!Error loading the file..!!");
        return;
    }

    // Display header of summary of all accounts.
    printf("\n\n\t\t\t\t\t\t\t\t    **** Summary of all Accounts ****");
    printf("\n\n\n     +----------------------+-----------------+--------------+------------------+--------------+----------------------+---------------+-----------------+\n");
    printf("     | %-20s | %-10s  | %-10s | %-15s  | %-10s   | %-15s | %-10s |    %-9s    |",
           "Account Name", "Account Number", "Account Type", "Account Balance", "Interest", "Account Opening Date", "Mobile Number", "Address");
    printf("\n     +----------------------+-----------------+--------------+------------------+--------------+----------------------+---------------+-----------------+\n");

    // Loop through each account in the data file.
    while (fscanf(fp, "%d %d %d %s %s %s %s %d %s %d %d %d %s %s %s %s %s %d %d %s %f\n", &acc_opendate.year, &acc_opendate.month, &acc_opendate.day,
                  prec.name, prec.fathers_name, prec.mothers_name, prec.Gender, &prec.age, prec.citizenship_no, &dob.year, &dob.month, &dob.day, prec.mobile_no,
                  add.country, add.state, add.district, add.muncipality, &add.ward_no, &accrec.acc_no, accrec.acc_type, &accrec.amt) != EOF)
    {

        test++; // Increment the test variable to indicate records were found.

        interest_earned=interest_check(accrec.acc_type,accrec.amt,acc_opendate.year,acc_opendate.month,acc_opendate.day); //Call the function to get interest accured

        //Display the account information in a formatted manner
        printf("     | %-20s |    %-10d   |   %-10s | Rs. %-12.2f | Rs. %-8.2f |      %02d/%02d/%04d      |   %-10s  |   %s-%-2d    |\n",
               prec.name, accrec.acc_no, accrec.acc_type, accrec.amt, interest_earned, acc_opendate.day, acc_opendate.month, acc_opendate.year, prec.mobile_no, add.district, add.ward_no);
        printf("     +----------------------+-----------------+--------------+------------------+--------------+----------------------+---------------+-----------------+\n");
    }

    // If no records were found, display a message.
    if (test == 0)
    {
        printf("\n\n\t\t\t\t    **** Records not found ****");
    }

    // Ask the user if they want more in-depth profiles.
more:
    printf("\n\n\t\t\t\t\t\t\t Would you like a more in-depth profile of individual[Y/N]?");
    scanf(" %c",&choice);
    if(choice == 'y' || choice == 'Y')
    {
        Search_acc();
    }
    else if(choice == 'n' || choice == 'N')
    {
        printf("\n\n\t\t\t\t\t Press any key to return to main menu....");
        getch();
    }
    else
    {
        printf("\n\n\t\t\t\t\t\t\t\t Invalid choice Please choose carefully!!!");
        goto more;
    }

    fclose(fp); //Close the file
}
// Function to search account details
void Search_acc()
{
    system("cls"); // Clear the console screen

    //Declare and Initialize the variable
    int check_acc_no=0,choice=0,record_found=0;
    float interest_earned=0;
    char check_acc_name[20],try_return;

    headmsg("Search Account Details"); // Display the header message
    line(32,5); // Draw the line
    FILE *fp;

    //Open the file in reading mode to read the data
    fp=fopen("bank.dat","r");

    // Check if file was opened successfully or not
    if (fp==NULL)
    {
        printf("\n\n\t\t\t\t !!Error loading the file!!");
        return;
    }

    //Display the available option to search
    printf("\n\n\t\t\t\t\t\t      1.Search by Account no:");
    printf("\n\n\t\t\t\t\t\t      2.Search by Account Name:");
    printf("\n\n\t\t\t\t\t\t      Do you want to search account details by....");
    scanf(" %d",&choice);

    //Search by account number section
    if (choice == 1)
    {
        //Loop for valid account number
        while(1)
        {
            system("cls"); // Clear the console screen
            headmsg("Search Account Details"); // Display the header
            line(32,5); // Draw the line

            record_found=0;
            printf("\v\n\n\n\t\t\t\t       Enter account number:");
            scanf("%d",&check_acc_no);

            //Read the data from file
            while (fscanf(fp, "%d %d %d %s %s %s %s %d %s %d %d %d %s %s %s %s %s %d %d %s %f\n", &acc_opendate.year, &acc_opendate.month, &acc_opendate.day,
                          prec.name, prec.fathers_name, prec.mothers_name, prec.Gender, &prec.age, prec.citizenship_no, &dob.year, &dob.month, &dob.day, prec.mobile_no,
                          add.country, add.state, add.district, add.muncipality, &add.ward_no, &accrec.acc_no, accrec.acc_type, &accrec.amt) != EOF)
            {
                if (check_acc_no == accrec.acc_no)
                {
                    record_found=1;
                    break; // If record is found stop searching and break from loop
                }
            }
            rewind(fp); // Return the file cursor at the beginning of file

            if (record_found == 1)
            {
                system("cls"); // Clear the console screen
                headmsg("CUSTOMER RECORD"); // Display the header
                line(32,5); // Draw the line

                interest_earned = interest_check(accrec.acc_type, accrec.amt, acc_opendate.year, acc_opendate.month, acc_opendate.day); // call the interest function to get the interest accured

                // Display Personal Details
                printf("\n\n\n\t\t\t\t\t\t\t\t     **** Personal Details **** \n");
                printf("\n\t\t\t\t+----------------------+--------------------+--------------------+-------------+------------+\n");
                printf("\t\t\t\t|    %-13s     | %-18s | %-18s |   %-7s   |    %-5s   |\n",
                       "Name","Father's Name","Mother's Name","Gender","Age");
                printf("\t\t\t\t+----------------------+--------------------+--------------------+-------------+------------+\n");
                printf("\t\t\t\t| %-20s | %-18s | %-18s |   %-7s   |    %-5d   |\n",
                       prec.name, prec.fathers_name, prec.mothers_name, prec.Gender, prec.age);
                printf("\t\t\t\t+----------------------+--------------------+--------------------+-------------+------------+\n");
                printf("\n\t\t\t\t Citizenship No: %d", prec.citizenship_no);
                printf("\n\t\t\t\t Mobile Number : %s\n", prec.mobile_no);

                // Display Address Details
                printf("\n\n\n\n\n\t\t\t\t\t\t\t\t     **** Address Details ****\n");
                printf("\n\t\t\t\t\t+------------+---------------+---------------+----------------+-------------+\n");
                printf("\t\t\t\t\t| Country    | Province      | District      | Jurisdiction   | Ward No     |\n");
                printf("\t\t\t\t\t+------------+---------------+---------------+----------------+-------------+\n");
                printf("\t\t\t\t\t| %-10s | %-13s | %-13s | %-14s | %-11d |\n",
                       add.country, add.state, add.district, add.muncipality, add.ward_no);
                printf("\t\t\t\t\t+------------+---------------+---------------+----------------+-------------+\n");

                // Display Account Details
                printf("\n\n\n\n\n\t\t\t\t\t\t\t\t     **** Account Details ****\n");
                printf("\n\t\t\t+-----------------------+---------------+---------------+-----------------+-------------------+-----------------+\n");
                printf("\t\t\t| Account Opening Date  | Account No    | Account Type  | Actual Balance  | Available Balance | Interest        |\n");
                printf("\t\t\t+-----------------------+---------------+---------------+-----------------+-------------------+-----------------+\n");
                printf("\t\t\t|    %-4d/%-2d/%-2d         | %-13d |    %-8s   | Rs. %-10.2f  | Rs. %-12.2f  | Rs. %-10.2f  |\n",
                       acc_opendate.year, acc_opendate.month, acc_opendate.day, accrec.acc_no, accrec.acc_type, accrec.amt - 1000, accrec.amt, interest_earned);
                printf("\t\t\t+-----------------------+---------------+---------------+-----------------+-------------------+-----------------+\n");

                printf("\n\n\t\t\t\t\t\t\t\t\t -Together we grow"); // Display the bank tag line

                //Prompt the user to view more records or return to main menu
                printf("\n\n\n\n\t\t\t\t\t\t Press V to view more records and anykey to return to main menu....");
                scanf(" %c",&try_return);

                //If user confirms, continue the loop
                if(try_return == 'v' || try_return == 'V')
                {
                    continue;
                }
                else
                {
                    break; // Exit the loop
                }
            }
            else
            {
                printf("\n\n\n\n\a\t\t\t\t\t\t\t\t        Record not found!!!");
                printf("\n\n\t\t\t\t\t\t\t\t Please check credentials properly!");
                delay(50000000);
                printf("\n\n\t\t\t\t\t\t\t Press T to try again and anykey to return to main menu....");
                scanf(" %c",&try_return);

                //Prompt the user to ask to try again or return to main menu
                if(try_return == 't' || try_return == 'T')
                {
                    continue; //If use confirm ,continue the loop
                }
                else
                {
                    break; // Exit the function
                }
            }

        }
    }

    // Search by account name section
    else if(choice == 2)
    {
        while(1) // Loop for valid account number
        {
            system("cls"); // Clear the console screen
            headmsg("Search Account Details"); // Display the header
            line(32, 5); // Draw the line

            record_found=0;
            printf("\n\n\t\t\t\t       Enter account name:");
            scanf("%s",&check_acc_name);

            //Read the data from file
            while (fscanf(fp, "%d %d %d %s %s %s %s %d %s %d %d %d %s %s %s %s %s %d %d %s %f\n", &acc_opendate.year, &acc_opendate.month, &acc_opendate.day,
                          prec.name, prec.fathers_name, prec.mothers_name, prec.Gender, &prec.age, prec.citizenship_no, &dob.year, &dob.month, &dob.day, prec.mobile_no,
                          add.country, add.state, add.district, add.muncipality, &add.ward_no, &accrec.acc_no, accrec.acc_type, &accrec.amt) != EOF)
            {
                if (stricmp(check_acc_name, prec.name)==0)
                {
                    record_found=1;
                    break; // If record is found stop searching and break from loop
                }

            }
            rewind(fp); // Return the file cursor to the beginning of the file

            if (record_found == 1)
            {
                system("cls"); // Clear the console screen
                headmsg("CUSTOMER RECORD"); // Display the header
                line(32,5); // Draw the line

                interest_earned=interest_check(accrec.acc_type,accrec.amt,acc_opendate.year,acc_opendate.month,acc_opendate.day); // Call the interest function to get the interest accured

                // Display Personal Details
                printf("\n\n\n\t\t\t\t\t\t\t\t     **** Personal Details **** \n");
                printf("\n\t\t\t\t+----------------------+--------------------+--------------------+-------------+------------+\n");
                printf("\t\t\t\t|    %-13s     | %-18s | %-18s |   %-7s   |    %-5s   |\n",
                       "Name","Father's Name","Mother's Name","Gender","Age");
                printf("\t\t\t\t+----------------------+--------------------+--------------------+-------------+------------+\n");
                printf("\t\t\t\t| %-20s | %-18s | %-18s |   %-7s   |    %-5d   |\n",
                       prec.name, prec.fathers_name, prec.mothers_name, prec.Gender, prec.age);
                printf("\t\t\t\t+----------------------+--------------------+--------------------+-------------+------------+\n");
                printf("\n\t\t\t\t Citizenship No: %d", prec.citizenship_no);
                printf("\n\t\t\t\t Mobile Number : %s\n", prec.mobile_no);

                // Display Address Details
                printf("\n\n\n\n\n\t\t\t\t\t\t\t\t     **** Address Details ****\n");
                printf("\n\t\t\t\t\t+------------+---------------+---------------+----------------+-------------+\n");
                printf("\t\t\t\t\t| Country    | Province      | District      | Jurisdiction   | Ward No     |\n");
                printf("\t\t\t\t\t+------------+---------------+---------------+----------------+-------------+\n");
                printf("\t\t\t\t\t| %-10s | %-13s | %-13s | %-14s | %-11d |\n",
                       add.country, add.state, add.district, add.muncipality, add.ward_no);
                printf("\t\t\t\t\t+------------+---------------+---------------+----------------+-------------+\n");

                // Display Account Details
                printf("\n\n\n\n\n\t\t\t\t\t\t\t\t     **** Account Details ****\n");
                printf("\n\t\t\t+-----------------------+---------------+---------------+-----------------+-------------------+-----------------+\n");
                printf("\t\t\t| Account Opening Date  | Account No    | Account Type  | Actual Balance  | Available Balance | Interest        |\n");
                printf("\t\t\t+-----------------------+---------------+---------------+-----------------+-------------------+-----------------+\n");
                printf("\t\t\t|    %-4d/%-2d/%-2d         | %-13d |    %-8s   | Rs. %-10.2f  | Rs. %-12.2f  | Rs. %-10.2f  |\n",
                       acc_opendate.year, acc_opendate.month, acc_opendate.day, accrec.acc_no, accrec.acc_type, accrec.amt - 1000, accrec.amt, interest_earned);
                printf("\t\t\t+-----------------------+---------------+---------------+-----------------+-------------------+-----------------+\n");

                printf("\n\n\t\t\t\t\t\t\t\t\t -Together we grow"); // Display the bank tag line

                //Prompt the user to view other records or exit to main menu
                printf("\n\n\t\t\t\t\t\t Press v to view more records and anykey to return to main menu....");
                scanf(" %c",&try_return);

                // Continue the loop if user wish to view more records
                if(try_return == 'v' || try_return == 'V')
                {
                    continue;
                }
                else
                {
                    break; // Exit the function
                }
            }
            else
            {
                printf("\n\n\n\n\a\t\t\t\t\t\t\t\t        Record not found!!!");
                printf("\n\n\t\t\t\t\t\t\t\t Please check credentials properly!");
                delay(50000000);
                printf("\n\n\n\n\t\t\t\t\t\t\t Press T to try again and anykey to return to main menu....");
                scanf(" %c",&try_return);

                // Prompt the user to try again or exit to main menu
                if(try_return == 't' || try_return == 'T')
                {
                    continue;
                }
                else
                {
                    break; // Exit the function
                }
            }
        }
    }
    else
    {
        printf("\n\n\a\t\t\t\t\t\t\t      Invalid choice please select appropriate method!!");
        delay(500000000);
        Search_acc();
    }
    fclose(fp); // Close the file after operation
}
//Function to delete the account
void Delete_acc()
{
    int rem_acc_no,test=0,otp,user_otp;
    char choice,try_return;
    float interest_earned;
    FILE *fp,*fp1;

    // Open the bank1.dat file in read mode and new.dat file in write mode
    fp = fopen("bank.dat", "r");
    fp1 = fopen("new.dat", "w");

    // Check if the files were opened successfully
    if (fp==NULL || fp1 == NULL)
    {
        printf("\n\n\t\t\t\t !!Error loading the file..!!");
        return;
    }
    //Loop for account deletion until user confirm to delete account
    while(1)
    {
        system("cls"); // Clear the console screen
        headmsg("DELETE ACCOUNT"); // Display the header
        line(32, 5); // Draw a line
        test = 0; // Initialize the test variable

        // Get account number to be deleted
        printf("\n\t\t\t\t\t\t     Please provide account number to remove its details");
        printf("\n\n\n\t\t\t\t\t Account Number:");
        scanf("%d",&rem_acc_no);

        // Loop through the file to find the account to be deleted
        while(fscanf(fp,"%d %d %d %s %s %s %s %d %s %d %d %d %s %s %s %s %s %d %d %s %f",&acc_opendate.year,&acc_opendate.month,&acc_opendate.day,
                     prec.name,prec.fathers_name,prec.mothers_name,prec.Gender,&prec.age,prec.citizenship_no,&dob.year,&dob.month,&dob.day,prec.mobile_no,
                     add.country,add.state,add.district,add.muncipality,&add.ward_no,&accrec.acc_no,accrec.acc_type,&accrec.amt)!=EOF)
        {


            if(rem_acc_no == accrec.acc_no)
            {
                test++; //Increase the test to check whether record is found or not later

                //Display the account details in brief
                interest_earned=interest_check(accrec.acc_type,accrec.amt,acc_opendate.year,acc_opendate.month,acc_opendate.day); //call the interest function to get the interest accured
                printf("\n\n\n     +----------------------+-----------------+--------------+------------------+--------------+----------------------+---------------+-----------------+\n");
                printf("     | %-20s | %-10s  | %-10s | %-15s  | %-10s   | %-15s | %-10s |    %-9s    |",
                       "Account Name", "Account Number", "Account Type", "Account Balance", "Interest", "Account Opening Date", "Mobile Number", "Address");
                printf("\n     +----------------------+-----------------+--------------+------------------+--------------+----------------------+---------------+-----------------+\n");
                printf("     | %-20s |    %-10d   |   %-10s | Rs. %-12.2f | Rs. %-8.2f |      %02d/%02d/%04d      |   %-10s  |   %s-%-2d    |\n",
                       prec.name, accrec.acc_no, accrec.acc_type, accrec.amt, interest_earned, acc_opendate.day, acc_opendate.month, acc_opendate.year, prec.mobile_no, add.district, add.ward_no);
                printf("     +----------------------+-----------------+--------------+------------------+--------------+----------------------+---------------+-----------------+\n");

                //Ask for confirmation to delete the account
confirmation:
                printf("\n\n\n\t\t\t\t\t\t\t Are you sure you want to delete this account[Y/N]?");
                scanf(" %c",&choice);

                //If user confirms,ask for OTP verification
                if(choice == 'y' || choice == 'Y')
                {
askotp:
                    otp=otp_generator();
                    printf("\n\n\t\t\t\t\t\t\t\t Your OTP is %d",otp);
                    printf("\n\n\t\t\t\t\t  Enter OTP:");
                    scanf("%d",&user_otp);
                    printf("\n\n\t\t\t\t\t\t\t\t  PLEASE WAIT VERIFYING"); // Display "Verifying" message with a loading animation
                    for(int i=0; i<4; i++)
                    {
                        delay(400000000);
                        printf(".");
                    }

                    //If OTP is correct , delete the account
                    if(user_otp == otp)
                    {
                        printf("\n\n\n\t\t\t\t\t\t\t\t **** Account Deleted Successfully ****");
                    }
                    else
                    {
                        printf("\n\n\a\t\t\t\t\t\t\t\t     Incorrect OTP !!! TRY AGAIN");
                        delay(5000000000);
                        goto askotp;
                    }
                }

                // If user cancels the deletion, retain the account in new file also
                else if(choice == 'n' || choice == 'N')
                {
                    fprintf(fp1,"%d %d %d %s %s %s %s %d %s %d %d %d %s %s %s %s %s %d %d %s %.2f \n",acc_opendate.year,acc_opendate.month,acc_opendate.day,prec.name,prec.fathers_name,
                            prec.mothers_name,prec.Gender,prec.age,prec.citizenship_no,dob.year,dob.month,dob.day,prec.mobile_no,add.country,add.state,add.district,add.muncipality,add.ward_no,
                            accrec.acc_no,accrec.acc_type,accrec.amt);
                    printf("\n\n\n\t\t\t\t\t\t\t\t **** Account Not Deleted ****");

                }
                else
                {
                    printf("\n\n\n\a\t\t\t\t\t\t\t     Invalid choice Please choose carefully!!!");
                    goto confirmation;
                }
            }
            else
            {
                // Retain other accounts and write them to the new file
                fprintf(fp1,"%d %d %d %s %s %s %s %d %s %d %d %d %s %s %s %s %s %d %d %s %.2f \n",acc_opendate.year,acc_opendate.month,acc_opendate.day,prec.name,prec.fathers_name,
                        prec.mothers_name,prec.Gender,prec.age,prec.citizenship_no,dob.year,dob.month,dob.day,prec.mobile_no,add.country,add.state,add.district,add.muncipality,add.ward_no,
                        accrec.acc_no,accrec.acc_type,accrec.amt);
            }
        }

        rewind(fp); //Return the file pointer to initial position

        if (test == 0) //If test is 0,account record was not found and display message accordingly
        {
            printf("\n\n\n\n\a\t\t\t\t\t\t\t\t        Record not found!!!");
            printf("\n\n\t\t\t\t\t\t\t\t Please check credentials properly!");
            delay(50000000);
            printf("\n\n\t\t\t\t\t\t\t Press T to try again and anykey to return to main menu....");
            scanf(" %c",&try_return);

            //If the user wants to try again,continue the loop
            if(try_return == 't' || try_return == 'T')
            {
                continue;
            }
            else
            {
                break; // Exit the loop if the user doesnot want to try again
            }
        }
        else
        {
            printf("\n\n\n\t\t\t\t\t Press any key to return to main menu....");
            getch();
            break; // Exit the loop when the operation is complete

        }
    }
    fclose(fp); //Close the original file
    fclose(fp1); //Close the new file
    remove("bank.dat");//remove the new file to bank.dat
    rename("new.dat","bank.dat");// rename the new.dat to bank.dat
}
//Function to make different type of transactions
void Transaction()
{
    int i=0,total_acc_num=0,s_index=-1,r_index=-1,vf,otp,user_otp,choice;
    int sender_acc_no,receiver_acc_no,sender_check,receiver_check=0;
    float tamount,interest_earned;
    char receiver_acc_name[20],remarks[100],ch,try_return;
    FILE *fp,*fp1;

    // Open data files for reading and writing.
    fp=fopen("bank.dat","r");
    fp1=fopen("new.dat","w");

    // Check for file opening errors.
    if (fp==NULL || fp1==NULL)
    {
        printf("\n\n\t\t\t\t !!Error loading the file..!!");
        return;
    }

    // Read data from the file and count the total number of accounts.
    while (fscanf(fp, "%d %d %d %s %s %s %s %d %s %d %d %d %s %s %s %s %s %d %d %s %f\n",
                  &dopentrn[i].year, &dopentrn[i].month, &dopentrn[i].day,
                  ptrn[i].name, ptrn[i].fathers_name, ptrn[i].mothers_name, ptrn[i].Gender,
                  &ptrn[i].age, ptrn[i].citizenship_no, &dtrn[i].year, &dtrn[i].month, &dtrn[i].day,
                  ptrn[i].mobile_no, atrn[i].country, atrn[i].state, atrn[i].district, atrn[i].muncipality,
                  &atrn[i].ward_no, &acctrn[i].acc_no, acctrn[i].acc_type, &acctrn[i].amt) != EOF)
    {

        i++;
        total_acc_num++;

    }

    // Loop for sender account input until a valid account number is entered.
    while (1)
    {
        system("cls"); //clear the console screen
        headmsg("TRANSACTION PAGE"); // display the header
        line(32,5); //draw the line

        printf("\n\n\t\t\t\t\t Enter Sender A/c no:");
        scanf("%d",&sender_acc_no);

        // Check if the entered sender account number exists in the data.
        for (i=0; i<total_acc_num; i++)
        {
            if (acctrn[i].acc_no == sender_acc_no)
            {
                s_index=i;
            }
        }

        // Handle case when sender account is not found.
        if(s_index == -1 )
        {
            printf("\n\n\t\t\t\t\t\t\t\t Sender Account not found!! ");
            printf("\n\n\t\t\t\t\t\t\t    **** Please check details properly ****");
            delay(500000000);
            continue;
        }
        break;
    }

    // Loop for transaction choices until a valid choice is entered.
    while(1)
    {
        system("cls"); //clear the console screen
        headmsg("TRANSACTION PAGE"); //display the header
        line(32,5); //draw the line

        printf("\n\n\t\t\t\t\t 1.Balance Enquiry");
        printf("\n\n\t\t\t\t\t 2.Withdraw Cash");
        printf("\n\n\t\t\t\t\t 3.Deposit Cash");
        printf("\n\n\t\t\t\t\t 4.Transfer Cash");
        printf("\n\n\t\t\t\t\t What do you want to do?");
        scanf("%d",&choice);
        if(choice==1)
        {
            system("cls"); //clear the console screen
            headmsg("BALANCE ENQUIRY"); //display the header
            line(32,5); //draw the line

            interest_earned=interest_check(acctrn[s_index].acc_type,acctrn[s_index].amt,dopentrn[s_index].year,dopentrn[s_index].month,dopentrn[s_index].day); //call the interest function to get the interest accured

            //Display the account balance details
            printf("\n\n\t\t\t\t\t\t\t\t     **** Account Details ****");
            printf("\n\n\t\t\t\t\t\t\t+-----------------------+-----------------------+\n");
            printf("\t\t\t\t\t\t\t|    Account Holder Name: %-21s |\n", ptrn[s_index].name);
            printf("\t\t\t\t\t\t\t|    Account Number     : %-21d |\n", acctrn[s_index].acc_no);
            printf("\t\t\t\t\t\t\t|    Available Balance  : Rs.%-18.2f |\n", acctrn[s_index].amt - 1000);
            printf("\t\t\t\t\t\t\t|    Actual Balance     : Rs.%-18.2f |\n", acctrn[s_index].amt);
            printf("\t\t\t\t\t\t\t|    Account Type       : %-21s |\n", acctrn[s_index].acc_type);

            // Display interest rate based on account type
            if ( stricmp(acctrn[s_index].acc_type,"savings")==0)
            {
                printf("\t\t\t\t\t\t\t|    Interest Rate      : 8.03%%   \t\t|\n");
            }
            else if ( stricmp(acctrn[s_index].acc_type,"current")==0)
            {
                printf("\t\t\t\t\t\t\t|    Interest Rate      : N/A   \t\t|\n");
            }
            else if ( stricmp(acctrn[s_index].acc_type,"FD1")==0)
            {
                printf("\t\t\t\t\t\t\t|    Interest Rate      : 9%%   \t\t|\n");
            }
            else if ( stricmp(acctrn[s_index].acc_type,"FD2")==0)
            {
                printf("\t\t\t\t\t\t\t|    Interest Rate      : 9.49%%   \t\t|\n");
            }
            else if ( stricmp(acctrn[s_index].acc_type,"FD3")==0)
            {
                printf("\t\t\t\t\t\t\t|    Interest Rate      : 9.99%%   \t\t|\n");
            }
            printf("\t\t\t\t\t\t\t|    Interest Accured   : Rs.%-18.2f |\n",interest_earned);
            printf("\t\t\t\t\t\t\t+-----------------------+-----------------------+\n");
            printf("\n\n\t\t\t\t\t\t\t\t\t -Together We Grow");
        }
        //amount withdrawal section
        else if (choice==2)
        {
properamt: // Label to handle validation of withdrawal amount
            printf("\n\n\n\n\t\t\t\t\t Enter the amount to Withdraw:");
            scanf("%f",&tamount);
            printf("\n\n\t\t\t\t\t\t\t\t\t Verifying,please wait ");
            for(int j=0; j<4; j++)
            {
                printf(".");
                delay(300000000);
            }

            // Validate withdrawal amount
            if(tamount <=0)
            {
                printf("\n\n\t\t\t\t\t\t\t\t Invalid amount Please enter proper amount!!");
                delay(50000000);
                goto properamt; //retry input
            }
            else if(tamount > (acctrn[s_index].amt-1000))
            {
                printf("\n\n\t\t\t\t\t\t\t Insufficient Balance!!");
                delay(50000000);
                return;
            }

            // Check if account type is FD and disallow withdrawal
            if(stricmp(acctrn[s_index].acc_type,"FD1")==0 || stricmp(acctrn[s_index].acc_type,"FD2")==0 || stricmp(acctrn[s_index].acc_type,"FD3")==0)
            {
                printf("\n\n\t\t\t\t\t\t\t\t Cannot Withdraw Money from FD account!!");
                delay(800000000);
                return; //Exit the function
            }

            //Ask the user to confirm the withdrawal and loop until valid response is found
            while (ch != 'y' && ch != 'Y' && ch != 'n' && ch != 'N')

            {
                printf("\n\n\t\t\t\t\t\t\t\t    Please Confirm the transaction[Y/N]:");
                scanf(" %c",&ch);
                if(ch=='y' || ch=='Y')
                {
                    //Generate the OTP and validate it
w_askotp:
                    otp=otp_generator();
                    printf("\n\n\t\t\t\t\t\t\t\t Your OTP is %d",otp);
                    printf("\n\n\t\t\t\t\t  Enter OTP:");
                    scanf("%d",&user_otp);
                    if(user_otp == otp)
                    {
                        printf("\n\n\t\t\t\t\t\t\t\t\t Please wait Processing");
                        for(int j=0; j<4; j++)
                        {
                            printf(".");
                            delay(300000000);
                        }
                        acctrn[s_index].amt=acctrn[s_index].amt-tamount; //withdraw the amount from acount
                        printf("\n\n\t\t\t\t\t\t\t\t **** Amount withdraw successfully ****");
                    }
                    else
                    {
                        printf("\n\n\a\t\t\t\t\t\t\t\t       Incorrect OTP !!! TRY AGAIN");
                        delay(5000000000);
                        goto w_askotp; //retry OTP input
                    }

                }
                else if (ch=='n' || ch=='N')
                {
                    printf("\n\n\a\t\t\t\t\t\t\t\t     **** Transaction Cancelled ****");
                }
                else
                {
                    printf("\n\n\a\t\t\t\t\t\t\t Invalid Choice!!");
                }
            }
        }

        //Deposit section
        else if (choice==3)
        {
            // Prompt the user to enter the amount to deposit
d_properamt:
            printf("\n\n\n\n\t\t\t\t\t Enter the amount to Deposit:");
            scanf("%f",&tamount);

            // Display verification progress
            printf("\n\n\t\t\t\t\t\t\t\t\t Verifying,please wait ");
            for(int j=0; j<4; j++)
            {
                printf(".");
                delay(100000000);
            }

            // Check for invalid deposit amount
            if(tamount <=0)
            {
                printf("\n\n\t\t\t\t\t\t\t\t Invalid amount Please enter proper amount!!");
                goto d_properamt;
            }

            // Check if the account type is FD Fixed Deposit
            if(stricmp(acctrn[s_index].acc_type,"FD1")==0 || stricmp(acctrn[s_index].acc_type,"FD2")==0 || stricmp(acctrn[s_index].acc_type,"FD3")==0)
            {
                printf("\n\n\t\t\t\t\t\t\t\t  Cannot Deposit Money into FD account!!");
                delay(800000000);
                return;
            }

            // Confirm the deposit transaction with the user
            while (ch != 'y' && ch != 'Y' && ch != 'n' && ch != 'N')

            {
                printf("\n\n\t\t\t\t\t\t\t\t    Please Confirm the transaction[Y/N]:");
                scanf(" %c",&ch);

                // If confirmed, proceed with OTP verification
                if(ch=='y' || ch=='Y')
                {

                    // Generate OTP and prompt the user
d_askotp:
                    otp=otp_generator();
                    printf("\n\n\t\t\t\t\t\t\t\t Your OTP is %d",otp);
                    printf("\n\n\t\t\t\t\t  Enter OTP:");
                    scanf("%d",&user_otp);

                    //Verify the OTP
                    if(user_otp == otp)
                    {
                        //Display processing progress
                        printf("\n\n\t\t\t\t\t\t\t\t\t Please wait Processing");
                        for(int j=0; j<4; j++)
                        {
                            printf(".");
                            delay(100000000);
                        }

                        // Update account balance and display success message
                        acctrn[s_index].amt=acctrn[s_index].amt + tamount;
                        printf("\n\n\t\t\t\t\t\t\t\t    **** Amount Deposited successfully ****");
                    }
                    else
                    {
                        // Incorrect OTP, prompt user to try again
                        printf("\n\n\t\t\t\t\t\t\t\t   Incorrect OTP !!! TRY AGAIN");
                        delay(5000000000);
                        goto d_askotp;
                    }

                }
                else if (ch=='n' || ch=='N')
                {
                    printf("\n\n\t\t\t\t\t\t\t\t     **** Transaction Cancelled ****");
                }
                else
                {
                    printf("\n\n\t\t\t\t\t\t\t\t\t      Invalid Choice!!");
                    delay(700000000);
                }
            }
        }

        //Fund transfer section
        else if (choice == 4)
        {
            do
            {
                system("cls"); //clear console screen
                headmsg("FUND TRANSFER PAGE"); //display header
                line(32,5); //Draw a line with =

                //Input receiver account details
                printf("\n\n\t\t\t\t\t Enter the receiver account no:");
                scanf("%d",&receiver_acc_no);
                printf("\n\n\t\t\t\t\t Enter the receiver account name:");
                scanf("%s",receiver_acc_name);
                r_index=-1;
                vf=0;

                // Find the receiver account index
                for (i=0; i<total_acc_num; i++)
                {
                    if (acctrn[i].acc_no == receiver_acc_no)
                    {
                        r_index=i;
                    }
                }

                //Check receiver account existence and match details
                if(r_index == -1 )
                {
                    printf("\n\n\n\n\t\t\t\t\t\t\t\t Receiver Account not found!! ");
                    printf("\n\n\t\t\t\t\t\t\t **** Please check details properly ****");
                    vf=1;
                }
                else if(stricmp(receiver_acc_name,ptrn[r_index].name)!=0) //Check if receiver account name and account number matches or not
                {
                    printf("\n\n\t\t\t\t\t\t Receiver account name doesnot match with receiver account number!!");
                    printf("\n\n\t\t\t\t\t\t\t **** Please check details properly ****");
                    vf=1;
                }
                else if(stricmp(acctrn[r_index].acc_type,"FD1")==0 || stricmp(acctrn[r_index].acc_type,"FD2")==0 || stricmp(acctrn[r_index].acc_type,"FD3")==0) //Check if the receiver account is FD account
                {
                    printf("\n\n\t\t\t\t\t\t\t\t  Cannot Transfer fund to FD account!!");
                    vf=1;
                }
                else if (sender_acc_no == receiver_acc_no)
                {
                    printf("\n\n\t\t\t\t\t\t\t\t  Cannot Transfer fund to Same account!!");
                    vf=1;
                }
                if(vf==1)
                {
                    //Prompt to retry or return
                    printf("\n\n\t\t\t\t\t\t Press T to try again and anykey to return to main menu....");
                    scanf(" %c",&try_return);

                    //If user choose to try again continue the loop
                    if(try_return == 't' || try_return == 'T')
                    {
                        continue;
                    }
                    else
                    {
                        return; //Exit the function and return to main menu
                    }
                }
                break; //End the loop after the operation
            }
            while (1);

            // Loop until proper amount is entered
            while(1)
            {
                printf("\n\n\t\t\t\t\t Enter the amount to transfer:");
                scanf("%f",&tamount);
                printf("\n\n\t\t\t\t\t Remarks:");
                scanf("%s",remarks);
                printf("\n\n\t\t\t\t\t\t\t\t\t Verifying,please wait ");
                for(int j=0; j<4; j++)
                {
                    printf(".");
                    delay(300000000);
                }
                if(tamount <=0)
                {
                    printf("\n\n\t\t\t\t\t\t\t\t Invalid amount Please enter proper amount!!");
                }
                else if(tamount > (acctrn[s_index].amt-1000))
                {
                    printf("\n\n\t\t\t\t\t\t\t Insufficient Balance!!"); // Check if account have sufficient balance or not
                    delay(800000000);
                    return; // Return to main menu
                }
                else
                {
                    break;
                }
            }
            while (ch != 'y' && ch != 'Y' && ch != 'n' && ch != 'N')

            {
                printf("\n\n\n\t\t\t\t\t\t\t\t\t **** Disclaimer ****");
                printf("\n\n\t\t\t\t\t\t\t +-------------------+---------------------------+\n");
                printf("\t\t\t\t\t\t\t |                                               |\n");
                printf("\t\t\t\t\t\t\t |  Sender A/c No    : %-21d     |\n", sender_acc_no);
                printf("\t\t\t\t\t\t\t |  Receiver A/c No  : %-21d     |\n", receiver_acc_no);
                printf("\t\t\t\t\t\t\t |  Receiver A/c Name: %-21s     |\n", receiver_acc_name);
                printf("\t\t\t\t\t\t\t |  Amount           : Rs. %-17.2f     |\n", tamount);
                printf("\t\t\t\t\t\t\t |  Remarks          : %-21s     |\n", remarks);
                printf("\t\t\t\t\t\t\t |                                               |");
                printf("\n\t\t\t\t\t\t\t +-------------------+---------------------------+\n");

                // Display the details for confirmation
                printf("\n\n\t\t\t\t\t\t\t\t    Please Confirm the fund transfer[Y/N]:");
                scanf(" %c",&ch);

                //Ask the user for confirmation
                if(ch=='y' || ch=='Y')
                {
                    //If user confirms ask for the OTP
taskotp:
                    otp=otp_generator(); // Generate the OTP
                    printf("\n\n\t\t\t\t\t\t\t\t Your OTP is %d",otp);
                    printf("\n\n\t\t\t\t\t  Enter OTP:");
                    scanf("%d",&user_otp);

                    // Validate entered OTP
                    if(user_otp == otp)
                    {
                        printf("\n\n\t\t\t\t\t\t\t\t\t Please wait Processing");
                        for(int j=0; j<4; j++)
                        {
                            printf(".");
                            delay(200000000);
                        }

                        //Update the balance from sender and receiver account
                        acctrn[s_index].amt=acctrn[s_index].amt-tamount;
                        acctrn[r_index].amt=acctrn[r_index].amt+tamount;
                        printf("\n\n\t\t\t\t\t\t\t\t    **** Fund transfer successfully ****");
                    }
                    else
                    {
                        printf("\n\n\a\t\t\t\t\t\t\t\t       Incorrect OTP !!! TRY AGAIN");
                        delay(5000000000);
                        goto taskotp; //retry the otp input
                    }

                }
                else if (ch=='n' || ch=='N')
                {
                    printf("\n\n\t\t\t\t\t\t\t\t    **** Fund Transfer Cancelled ****");
                }
                else
                {
                    printf("\n\n\a\t\t\t\t\t\t\t\t\t Invalid Choice!!");
                }
            }
        }
        // Validate the user choice
        else if (choice < 1 || choice > 4)
        {
            printf("\n\n\a\t\t\t\t\t\t Invalid choice. Please select a valid option.\n");
            delay(500000000);
            continue; //Retry if not valid choice
        }
        break; // break the loop if valid choice
    }

    // Write the details into the new file
    for (i=0; i<total_acc_num; i++)
    {
        fprintf(fp1, "%d %d %d %s %s %s %s %d %s %d %d %d %s %s %s %s %s %d %d %s %f\n",
                dopentrn[i].year, dopentrn[i].month, dopentrn[i].day,
                ptrn[i].name, ptrn[i].fathers_name, ptrn[i].mothers_name, ptrn[i].Gender,
                ptrn[i].age, ptrn[i].citizenship_no, dtrn[i].year, dtrn[i].month, dtrn[i].day,
                ptrn[i].mobile_no, atrn[i].country, atrn[i].state, atrn[i].district, atrn[i].muncipality,
                atrn[i].ward_no, acctrn[i].acc_no, acctrn[i].acc_type, acctrn[i].amt);

    }
    fclose(fp); //close the original file
    fclose(fp1); // close the new file
    remove("bank.dat"); // Remove the bank.dat file
    rename("new.dat","bank.dat"); // Rename the new file to bank.daat

    // Ask user to return to main menu
    printf("\n\n\t\t\t\t\t Press any key to return to main menu...");
    getch();
}
// Function to update the username or password
void Update_user_password()
{
    system("cls"); // Clear the console screen

    // Declare variable to store username and password
    char USER[20];
    char PASS[16];
    int attempts = 3,i,choice;
    char username[20],password[16],new_username[15],new_password[16];
    FILE *fp,*fp1;

    // Open Password.dat file to read username and password and new.dat file to store new username and password
    fp=fopen("Username_Password.dat","r");
    fp1=fopen("new.dat","w");
    if (fp == NULL || fp1 == NULL)
    {
        printf("\n\n\t\t\t\t !!Error loading the file..!!");
        return;
    }
    fscanf(fp,"%s %s",USER,PASS);

    // Allow a maximun number of login attempts
    while (attempts > 0)
    {
        headmsg("Updating Credentials"); // Display the header
        line(31,5); // Draw the line

        // Get user input for existing username and password
        printf("\n\n\n\t\t\t\t\t\t Existing Username: ");
        scanf("%19s", username);
        printf("\n\n\n\t\t\t\t\t\t Existing Password: ");
        scanf("%15s", password);
        printf("\n\n\t\t\t\t\t\t\t\t  PLEASE WAIT VERIFYING"); // Display verifying message
        for(i=0; i<4; i++)
        {
            delay(300000000);
            printf(".");
        }
start:
        system("cls"); // clear the console screen
        headmsg("Updating Credentials"); // Display the header
        line(31,5); // Display the line

        if (strcmp(username, USER) == 0 && strcmp(password, PASS) == 0) // Validate username and password
        {
            printf("\n\n\t\t\t\t 1.Change Username");
            printf("\n\n\t\t\t\t 2.Change Password");
            printf("\n\n\t\t\t\t 3.Both");
            printf("\n\n\t\t\t\t What do you want to do....");
            scanf("%d",&choice);

            // updating username section
            if(choice == 1)
            {
guser:
                printf("\n\n\n\t\t\t\t New Username:");
                scanf(" %15s", new_username);
                printf("\n\n\t\t\t\t\t\t\t\t\t Please wait Processing");
                for(int j=0; j<4; j++)
                {
                    printf(".");
                    delay(200000000);
                }
                if (stricmp(USER,new_username)==0) // check if current username and new username are same
                {
                    printf("\n\n\n\t\t\t\t\t\t\t\t **** Cannot use same Username ****");
                    printf("\n\n\n\t\t\t\t\t\t\t\t Please Select different username");
                    delay(50000000);
                    goto guser; // try again to enter username
                }
                else
                {
                    fprintf(fp1,"%s %s",new_username,PASS); // Update the new username into file
                    printf("\n\n\t\t\t\t\t\t\t\t  **** Username Updated Successfully ****");
                    printf("\n\n\t\t\t\t\t Press any key to return to main menu....");
                    getch();
                    break;
                }
            }

            // Updating password section
            else if (choice == 2)
            {
gpassword:
                printf("\n\n\n\t\t\t\t New Password:");
                scanf(" %15s", new_password);
                printf("\n\n\t\t\t\t\t\t\t\t\t Please wait Processing");
                for(int j=0; j<4; j++)
                {
                    printf(".");
                    delay(200000000);
                }
                if (stricmp(PASS,new_password)==0) // Check if current password and new password are same
                {
                    printf("\n\n\n\t\t\t\t\t\t\t\t **** Cannot use same Password ****");
                    printf("\n\n\n\t\t\t\t\t\t\t\t Please Select different Password");
                    delay(50000000);
                    goto gpassword;
                }
                else
                {
                    fprintf(fp1,"%s %s",USER,new_password); // Update new password into the file
                    printf("\n\n\t\t\t\t\t\t\t\t  **** Password Updated Successfully ****");
                    printf("\n\n\t\t\t\t\t Press any key to return to main menu....");
                    getch();
                    break;
                }

            }

            // Updating both username and password
            else if (choice == 3)
            {
guser_gpass:
                printf("\n\n\n\t\t\t\t New Username:");
                scanf(" %15s", new_username);
                printf("\n\n\n\t\t\t\t New Password:");
                scanf(" %15s", new_password);
                printf("\n\n\t\t\t\t\t\t\t\t\t Please wait Processing");
                for(int j=0; j<4; j++)
                {
                    printf(".");
                    delay(200000000);
                }
                if (stricmp(USER,new_username)==0 || stricmp(PASS,new_password)==0) // Check if current credentials matches with new credentials
                {
                    printf("\n\n\n\t\t\t\t\t\t\t   **** Cannot use same Username or Password ****");
                    printf("\n\n\n\t\t\t\t\t\t\t    Please Select different Different Credentials");
                    delay(500000000);
                    goto guser_gpass;
                }
                else
                {
                    fprintf(fp1,"%s %s",new_username,new_password); // Update the new credentials into the file
                    printf("\n\n\t\t\t\t\t\t\t    **** UserName and Password Updated Successfully ****");
                    printf("\n\n\t\t\t\t\t Press any key to return to main menu....");
                    getch();
                    break;
                }
            }
            else
            {
                printf("\n\n\a\t\t\t\t\t\t\t\t  Invalid Choice please choose appropriate options!!");
                delay(700000000);
                goto start;
            }
        }
        else
        {
            attempts--; // Decrement the remaining login attempts
            printf("\v\n\t\t\t\t\t\t\t Incorrect credentials! Please try again.\n");
            printf("\n\t\t\t\t\t\t\t          %d attempts remaining...\n", attempts);
            delay(800000000); // Delay to provide user feedback
        }
    }

    // Display message if maximun attempts are reached
    if(attempts==0)
    {
        system("cls");
        fprintf(fp1,"%s %s",USER,PASS); // Update the new credentials into the file
        printf("\n\t\t\t\t\t\t\t             Too many unsuccessful attempts!!!\n");
        printf("\n\n\t\t\t\t\t\t   For security reasons you cannot change UserName and Password now!!\n");
        printf("\n\n\n\t\t\t\t\t Press any key to return to main menu...");
        getch();
    }
    fclose(fp);  // Close the password.dat file
    fclose(fp1); // Close the new.dat file
    remove("Username_Password.dat"); //Remove the original Username_Password.dat
    rename("new.dat", "Username_Password.dat"); // Rename new.dat file to Username_Password.dat
}
// Function to close the application
void Close_app()
{
    system("cls"); // Clear the console screen
    printf("\n\n\t\t\t\t\t\t      THANK YOU FOR USING OUR APPLICATION !!!!");
    printf("\n\n\t\t\t\t\t\t Copyright \xC2\xA9  2023 BFK Group, All rights reserved.");
    printf("\n\n\t This material may not be reproduced, displayed, modified, or distributed without the express prior written permission of BFK Group \n\n");
}
//function to display the header
void headmsg(char msg[100])
{
    system("cls"); // Clear the console screen
    system("color 9"); // Change the system font color
    printf("\t\t\t\t***************************************************************************************************\n");
    printf("\t\t\t\t**********************                                                       **********************\n");
    printf("\t\t\t\t**********************                                                       **********************\n");
    printf("\t\t\t\t**********************           BANKING MANGEMENT SYSTEM PROJECT            **********************\n");
    printf("\t\t\t\t**********************                                                       **********************\n");
    printf("\t\t\t\t**********************                                                       **********************\n");
    printf("\t\t\t\t***************************************************************************************************\n");
    printf("\n\n\n\n\t\t\t\t\t\t\t\t     **** %s ****\n",msg); // Display the page message
}
//function to make delay
void delay(int nanoseconds)
{
    int i;
    for (i=0; i<nanoseconds; i++)
    {
        int k=k+i;
    }
}
//function to display line
void line(int n,int t)
{
    int i;
    printf("\v\v\v");
    for (i=0; i<n; i++)
    {
        if (i<t) //to display tab space initially before printing line
        {
            printf("\t");
        }
        else
        {
            printf("==="); //print line using = symbol

        }

    }
}
//Function to handle user login
int login()
{
    system("cls"); //Clear the console screen

    //Declare variables to store username and password
    char USER[20];
    char PASS[16];

    FILE *fp;
    fp=fopen("Username_Password.dat","r"); //Open the file for reading the username and password
    if (fp == NULL)
    {
        printf("\n\n\t\t\t\t !!Error loading the file..!!");
        return;
    }
    fscanf(fp,"%s %s",USER,PASS); // Read the last username and password from the file

    const int MAX_ATTEMPTS = 5;
    int attempts = MAX_ATTEMPTS,i,val=0;
    char username[20], password[16];

    while (attempts > 0) // Allow a maximum number of login attempts
    {
        headmsg("Login Page"); // Display the login page header
        line(31, 5); // Draw a line

        // Get user input for username and password
        printf("\n\n\n\t\t\t\t\t\t Username: ");
        scanf("%19s", username);
        printf("\n\n\n\t\t\t\t\t\t Password: ");
        scanf("%15s", password);

        printf("\n\n\t\t\t\t\t\t\t\t  PLEASE WAIT VERIFYING"); // Display "Verifying" message with a loading animation
        for(i=0; i<4; i++)
        {
            delay(400000000);
            printf(".");
        }
        // Compare input credentials with stored credentials
        if (strcmp(username, USER) == 0 && strcmp(password, PASS) == 0)
        {
            printf("\n\n\t\t\t\t\t\t\t      Check  your  email  for  OTP!! \n");
            delay(600000000); // Delay to prompt user to check email
            val=otp_check(); // Call the OTP check function
            fclose(fp); //Close the file
            return val; //terminate the function with a true value
        }
        else
        {
            attempts--; // Decrement the remaining login attempts
            printf("\v\n\t\t\t\t\t\t\t\a Incorrect credentials! Please try again.\n");
            printf("\n\t\t\t\t\t\t\t          %d attempts remaining...\n", attempts);
            delay(600000000); // Delay to provide user feedback
        }
    }
    // Display message if maximum attempts are reached
    if(attempts==0)
    {
        system("cls");
        printf("\n\t\t\t\t\t\t\t             Too many unsuccessful attempts!!!\n");
        printf("\n\n\t\t\t\t\t\t   Account has been blocked. Please try again after 24 hours.\n");
        printf("\n\n\t\t\t\t Press any key to continue....");
        getch();
        fclose(fp); //Close the file
        return val;
    }
}
// Function to generate the OTP
int otp_generator()
{
    // Set a new seed value based on the current time
    srand(time(0));

    // Generate a random integer between 100000 and 999999
    int g_otp = rand() % (999999 - 100000 + 1) + 100000;

    return g_otp;
}
// Function to check the OTP
int  otp_check()
{
    int user_otp,otp;
    do
    {
        system("cls");
        headmsg("Login Page");// Display the login page header
        line(31, 6); // Draw a line

        // Generate a random OTP and display it to the user
        otp=otp_generator();
        printf("\n\n\t\t\t\t\t\t\t\t Your OTP is %d",otp);
        printf("\n\n\t\t\t\t\t   OTP:");
        scanf("%d",&user_otp); // Get user input for OTP

        // Compare user-provided OTP with generated OTP
        if(user_otp == otp)
        {
            printf("\n\n\t\t\t\t\t\t\t\t  PLEASE WAIT VERIFYING"); // Display "Verifying" message with a loading animation
            for(int i=0; i<4; i++)
            {
                delay(400000000);
                printf(".");
            }
            return 1;
        }
        else
        {
            printf("\n\n\t\t\t\t\t\t\t   Incorrect OTP !!! TRY AGAIN");
            delay(5000000000); // Delay to provide user feedback
        }
    }
    while(1); //run loop infinitely until the otp matches
}




/* **** This code is developed by BFK GROUP and they have copyright to this ****
                Copyright © 2023 BFK Group All rights reserved.
This material may not be reproduced, displayed, modified, or distributed without the express prior written permission of BFK Group*/
