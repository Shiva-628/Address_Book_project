/* Name: Shiva k V
Date:18/08/24
Description:Address-Book Project
*/

#include <stdio.h> //preprpcessor for input/output functions
#include <stdlib.h>//preprocessors For memory allocation and exit functions             
#include <string.h>//preprocessors for string manipulation functions
#include "contact.h"//For contact data structure definition

#include "file.h"//For file operation data structure definition
#include "populate.h"//For populating initial data

////////////////Function defination for displaying all conatacts//////////////////////////
void listContacts(AddressBook *addressBook, int sortCriteria) 
{
	    // Display contact details
	printf(".........................................................................\n");
	printf(".........................Displaying the contacts..........................\n");
	printf("..........................................................................\n");
	printf("\tSLNO \t\tname\t\t Phone_Number\t\tEmail_ID");

	for(int i=0;i<addressBook->contactCount;i++)
	    {
            //Displaing  contact details
		printf("\n%d \t%s\t\t%s\t\t%s",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
		 
	    }
}
/////////////////////Function to initialize the address book//////////////////////

void initialize(AddressBook *addressBook) 
{
    addressBook->contactCount = 0;
    populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}
//Function  defination to save contacts to a file and exit the program.
void saveAndExit(AddressBook *addressBook) 
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

/////////////Function to create a new contact and add it to the address book.///////////////
void createContact(AddressBook *addressBook)
{
    char name[50];
    char phone[10];
    char email_id[30];
    printf("Enter the name: ");
    getchar(); // Clear newline character from input buffer
    scanf("%[^\n]", name); //Read input until newline

    strcpy(addressBook->contacts[addressBook->contactCount].name, name);// Copy name to the address book

    validate(phone, addressBook);// validate the phone number
    printf("Email must be  starting at any numbers or alphabets and end with @gmail.com\n");
    printf("Enter the Email_ID: "); //taking Email from user 
    getchar();
    scanf("%[^\n]",email_id);//scanning email up to n
     
    gmail_validation(email_id, addressBook);//validate the Gmail 

}  
///////Function  defination to validate the phone number.//////////////
void validate(char *phone, AddressBook *addressBook)
{
    printf("Enter the Phone number: ");// taking contact number from user
    getchar(); // Clear newline character from input buffer
    scanf("%[^\n]", phone);//reading the number
    
    ////////////checking length of phone number/////
    int len = strlen(phone);
  
    if (len == 10) {
        int i;
        int flag = 1; 
        
        for (i = 0; i < len; i++) {
            ///validating phone number between  in the range of 0 to 9 ////////
            if (!(phone[i] >= '0' && phone[i] <= '9')) {
                flag = 0;
                break;
            }
        }
          strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);//Copy phone  to the address book

        if(flag)
        {
            for (int i = 0; i < addressBook->contactCount; i++) 
            {
                // Check for duplicate phone number
              if (strcmp(addressBook->contacts[i].phone, phone) == 0)
               {
                    printf("Phone number already exists.\n");
                    validate(phone, addressBook); //and calling once again recursivelly to new number if already exist.
                    return;
                }
            }          
         strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);// Copy phone  to the address book.    
        } else {
            printf("Invalid phone number - contains non-digit characters\n");
            getchar(); 
         validate(phone, addressBook);//Recursive call to re-enter a valid phone number
            
        }
    } else 
    {
        printf("Invalid phone number - should be exactly 10 digits\n");
        validate(phone, addressBook);// Recursive call to re-enter a valid phone number
    }

}
/////////////Function defination to validate gmail_id///////////
void gmail_validation(char *email_id, AddressBook *addressBook)
{
    const char *str1 = "@";
    const char *str2 = ".com";
    
    int flag=0;

    if (strstr(email_id, str1) != NULL && strstr(email_id, str2))
     {
        //copying validated email to address book.
        strcpy(addressBook->contacts[addressBook->contactCount++].email,email_id);      
        printf("Successfully added Gmail_ID\n");
        
     }
    else {
        printf("Invalid Gmail_ID\n");
        printf("Email must be  starting at any numbers or alphabets  and end with @gmail.com\n");
        printf("Enter the correct Gmail_ID: ");
        getchar(); 
        scanf("%[^\n]", email_id); // Reading the corrected Gmail ID
        gmail_validation(email_id, addressBook); //  validating the corrected ID(recursive calling)
    }
     
}

 ////////Function  defination to search contacts by various criteria////////

void searchContact(AddressBook *addressBook) 
{
    //  logic for search 
    char name[50];
    char phone[11];
    char email[50];
	int choice;
    getchar();
   
    //Displaying menu detail for search contacts.
      printf("\nEnter which member you want to search:\n");
        printf("1. search_by_name\n");
        printf("2. Search_by_contact\n");
        printf("3. search_by_email\n");
        
        printf("Enter your choice: ");
        scanf("%d", &choice);
   
    switch(choice)
    {
        case 1: //Search by name
        {
            char names[50];
                int flag=0;
                int i;
                printf("Enter name:\n");
                getchar();
                scanf("%[^\n]",names);
                
                    printf(".........................................................................\n");
                    printf(".........................Displaying the contacts..........................\n");
                    printf("..........................................................................\n");
                    printf("\n");
                    printf("SL No \t\tName\t\t Contact\t\t Email_ID");
                    
               for (int i = 0; i < addressBook->contactCount; i++) 
                {               
                    if (strstr(addressBook->contacts[i].name, names) != NULL)
                      {
                        // Displaying contact details                   
                        printf("\n%d \t%s\t\t %s\t\t %s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                                            flag=1;     
                      }
                }
                        if(flag==0)
                            {
                                printf("your checking name is not their here\n");
                                break;
                            }
                    
                break;       
            }
            
                case 2:// Search by contact number
                {
                       char contact[11];
                        int flag=0;
                        int i;
                        printf("Enter contact:\n");
                        getchar();
                        scanf("%[^\n]",contact);
                        printf(".........................................................................\n");
                            printf(".........................Displaying the contacts..........................\n");
                            printf("..........................................................................\n");
                            printf("\n");
                            printf("SL No \t\tName\t\t Contact\t\t Email_ID");


                  for (int i = 0; i < addressBook->contactCount; i++) 
                    {
                
                     if (strstr(addressBook->contacts[i].phone, contact) != NULL)
                       {   
                        // Displaying contact details                       
                          printf("\n %d \t%s\t\t %s\t\t%s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                                    flag=1;     
                        }
                    }
                        if(flag==0)
                            {
                                printf("your checking contact is not their here\n");
                                break;
                                
                                
                            }  
                break; 
                }
            
                case 3: // Search by Gmail
                {
                        char gmail[11];
                        int flag=0;
                        int i;
                        printf("Enter Gmail:\n");
                        getchar();
                        scanf("%[^\n]",gmail);
                            printf(".........................................................................\n");
                            printf(".........................Displaying the contacts..........................\n");
                            printf("..........................................................................\n");
                            printf("\n");
                            printf("SL No \t\tName\t\t Contact\t\t Email_ID");
                        
                 printf("\n");
                 for (int i = 0; i < addressBook->contactCount; i++) 
                    {
                
                      if (strstr(addressBook->contacts[i].email, gmail) != NULL)
                      {
                            // Displaying contact details         
                        printf("\n%d \t %s\t\t %s\t\t %s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                                    flag=1;     
                        }
                    }
                        if(flag==0)
                            {
                                printf("\nyour checking gmail is not their here\n");
                                break;  
                            }           
                 break;          
                }
                    default:
                    {
                     printf("Invalid choice. Please enter a number between 1 and 3.\n");
                     break;
                    }
    }
}
////// Function to edit existing contacts/////////////////////
void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    int choice;
    getchar(); 

    printf("\nEnter which member you want to edit:\n");
    printf("1. Edit by name\n");
    printf("2. Edit by contact\n");
    printf("3. Edit by email\n");

    printf("Enter your choice: ");
    scanf("%d", &choice);
        switch(choice)
        {
                case 1: //Edit by name
                {
                    char names[50];
                    int flag= 0;
                    int i,j, index=0;
                    printf("Enter name:\n");
                    getchar(); 

                    // Read name input
                    scanf("%[^\n]", names);

                        printf(".........................................................................\n");
                            printf(".........................Displaying the contacts..........................\n");
                            printf("..........................................................................\n");
                            printf("\n");
                            printf("SL No \t\tName\t\t Contact\t\t Email_ID");
                        
                            printf("\n");
                        for(i=0;i<addressBook->contactCount;i++)
                    {
                            if(strstr(addressBook->contacts[i].name,names)!=NULL)//compaing old name with new name in data     
                            {
                                flag=1;
                                /////// Display contact details ///////
                                printf("%d\t\t%s \t\t%s\t\t%s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                            }  
                    }                                                                  
                    if(flag==0)
                        {
                            printf("\nContact not Found !\n");     
                            return;
                        }
                         if(flag)
                    {
                        //Edit wih new name and replacing by index number
                        char name[30];
                        printf("\nEnter Sl no. of Contact to edit : ");   
                        scanf("%d",&index);
                        printf("\nEnter the new Name : ");
                        getchar();
                        scanf("%[^\n]",name);
                        {
                            for(i=index-1;i<addressBook->contactCount;i++)
                                {                   
                                strcpy(addressBook->contacts[index-1].name,name);//copying name to address book.
                                }
                            
                            printf("--Contact updated Successfully--");                          
                        }
                    }
                break;

                case 2: //Edit by phone number
                {
                    char phone[50];
                    int flag= 0;
                    int i,j, index=0;
                    printf("Enter contact:\n");
                    getchar(); 
                    scanf("%[^\n]", phone);

                        printf(".........................................................................\n");
                            printf(".........................Displaying the contacts..........................\n");
                            printf("..........................................................................\n");
                            printf("\n");
                            printf("SL No \t\tName\t\t Contact\t\t Email_ID");
                        
                            printf("\n");
                        for(i=0;i<addressBook->contactCount;i++)
                    {
                            if(strstr(addressBook->contacts[i].phone,phone)!=NULL)     
                            {
                                flag=1;
                                //Displaying  contact details.
                                printf("%d\t\t%s \t\t%s\t\t%s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                            }  
                    }                                                                  
                    if(flag==0)
                        {
                            printf("\nContact not Found !\n");     
                            return;
                        }
                         if(flag)
                    {
                        
                        char phone[10];
                        printf("\nEnter Sl no. of Contact to edit : ");   
                        scanf("%d",&index);
                        validate(phone, addressBook);
                        
                        //Function defination to validating phone number
                        void validate(char *phone, AddressBook *addressBook)
                        {
                            printf("Enter the Phone number: ");
                            getchar(); // Clearing the buffer
                            scanf("%[^\n]", phone);
                            
                            int len = strlen(phone);
                        
                            if (len == 10) {
                                int i;
                                int flag = 1; 
                                
                                for (i = 0; i < len; i++) 
                                {
                                    if (!(phone[i] >= '0' && phone[i] <= '9')) 
                                    {
                                        flag = 0;
                                        break;
                                    }
                                }
                            for(i=index;i<addressBook->contactCount;i++)
                            {
                                //copying new phone number to addressbook//
                                strcpy(addressBook->contacts[index].phone, phone);
                                printf("--Contact updated Successfully--");  
                            }
                                
                                if(flag)
                                {
                                    for (int i = 0; i < addressBook->contactCount; i++) 
                                    {
                                        //validating duplicate number with address book
                                      if (strcmp(addressBook->contacts[i].phone, phone) == 0)
                                       {
                                            printf("Phone number already exists.\n");
                                            validate(phone, addressBook); // function calling recursivelly if number exists
                                            return;
                                        }
                                    }          
                        
                                
                                } 
                                else
                                 {
                                    printf("Invalid phone number - contains non-digit characters\n");
                                    getchar();
                                    validate(phone, addressBook);// function calling recursivelly, if number contain non-digit chatacters
                                    
                                 }
                            } 
                            else 
                                {
                                    printf("Invalid phone number - should be exactly 10 digits\n");
                                    validate(phone, addressBook);//function calling recursivelly,  number - should be exactly 10 digits
                                }
                        }
                            for(i=index-1;i<addressBook->contactCount;i++)
                                {                             
                                  strcpy(addressBook->contacts[index-1].phone,phone);// copying new phone number to addressbook.
                                }
                                
                            printf("--Contact updated Successfully--");                            
                        }
                    }
                break;  

                case 3:// Edit by Email
                {
                    char email[50];
                    int flag= 0;
                    int i,j, index=0;
                    printf("Enter email:\n");
                    getchar(); 

                    
                    scanf("%[^\n]", email);

                        printf(".........................................................................\n");
                            printf(".........................Displaying the contacts..........................\n");
                            printf("..........................................................................\n");
                            printf("\n");
                            printf("SL No \t\tName\t\t Contact\t\t Email_ID");
                        
                            printf("\n");
                        for(i=0;i<addressBook->contactCount;i++)
                        {
                            if(strstr(addressBook->contacts[i].email,email)!=NULL)     
                            {
                                flag=1;
                                //displaying contacts
                                printf("%d\t\t%s \t\t%s\t\t%s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                            }  
                        }                                                                  
                       if(flag==0)
                        {
                            printf("\nContact not Found !\n");     
                            return;
                        }
                         if(flag)
                       {                        
                            char email_id[100];
                            
                            printf("\nEnter Sl no. of Email to edit : ");   
                            scanf("%d",&index);
                            printf("\nEnter the New Email :");
                            getchar();
                            scanf("%[^\n]",email_id);
                            gmail_e_validation(email_id, addressBook); ///function calling recursivelly for validating gmail                                        
                                for(i=index-1;i<addressBook->contactCount;i++)
                                    { 
                                    strcpy(addressBook->contacts[index-1].email,email_id);// copying new email to address-book
                                    }                               
                                printf("--Contact updated Successfully--"); 
                                                 
                        }
                    }
                break;
                }
            }
        }  
        ////////Function defination to validating gmail///////////
                        void gmail_e_validation(char *email_id, AddressBook *addressBook)
                            {
                                const char *str1 = "@";
                                const char *str2 = ".com"; 
                                int index=0;                                                              
                                if (strstr(email_id, str1) != NULL && strstr(email_id, str2))
                                {
                                    for(int i=index-1;i<addressBook->contactCount;i++)
                                    {                    
                                    //strcpy(addressBook->contacts[index-1].email,email_id);
                                    }
                                    //printf("Successfully added Gmail_ID\n");                                    
                                }
                                else {
                                    printf("Invalid Gmail_ID\n");
                                    printf("Email must be  starting at any numbers or alphabets  and end with @gmail.com\n");
                                    printf("Enter the correct Gmail_ID: ");
                                    getchar(); 
                                    scanf("%[^\n]", email_id); // Reading the corrected Gmail ID
                                    gmail_e_validation(email_id, addressBook); //  validating the corrected ID(by recursive calling)
                                }
                            }   

////// function  defination to validate the delete contact///////                       
void deleteContact(AddressBook *addressBook)
{
    int choice;
    getchar(); 
//Displaying menu options for deleting acontact
    printf("\nEnter which member you want to Delete:\n");
    printf("1. Delete by name\n");
    printf("2. Delete by contact\n");
    printf("3. Delete by email\n");

    printf("Enter your choice: ");
    scanf("%d", &choice);
                   

    switch(choice)// Switch statement to handle the different deletion criteria
    {
        case 1: //Deleting by name
        {
            char names[50];
            int flag= 0;
            int i, index=0;
            printf("Enter name:\n");
            getchar(); //  clearing buffer 

            // Read names input
            scanf("%[^\n]", names);
                    // Displaying the contacts to show which ones match the name//
                  printf(".........................................................................\n");
                    printf(".........................Displaying the contacts..........................\n");
                    printf("..........................................................................\n");
                    printf("\n");
                    printf("SL No \t\tName\t\t Contact\t\t Email_ID");
                   
                    printf("\n");
                for(i=0;i<addressBook->contactCount;i++)// Iterate over the contacts to find and display matching names
            {
                    if(strstr(addressBook->contacts[i].name,names)!=NULL)     
                    {
                        flag=1;
                        //displaying contact detail
                        printf("%d\t\t%s \t\t%s\t\t%s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                    }  
            }                                                                  
            if(flag==0)
                {
                    printf("\nContact not Found !\n");     
                    return;
                }
                //if contact found ask to sl no which one u want to delete.
                    if(flag)
                {
                    printf("\nEnter Sl no. of Contact to Delete : ");   
                    scanf("%d",&index);
                    {
                        // Remove the contact by shifting subsequent contacts
                    for(i=index-1;i<addressBook->contactCount-1;i++)
                        {
                            //replacing index one by one
                            addressBook->contacts[i]=addressBook->contacts[i+1]; 
                        } 
                    printf("--Contact Deleted Successfully--");  
                    addressBook->contactCount--;  // updating contact count                              
                }
        }
            break;
            case 2: //Deleting by number
            {
                char contact[50];
                int flag=1;
                int i,index=0;
                printf("Enter contact:\n");
                getchar();
                scanf("%[^\n]",contact);

                for(i=0;i<addressBook->contactCount;i++)//Iterate over the contacts to find and display matching names
                 {
                    if(strstr(addressBook->contacts[i].phone,contact)!=NULL)     
                    {
                        flag=1;
                        //display contact details.
                        printf("%d.\t\t%s\t\t%s\t\t%s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                    }   
                 }                                                                 
                    if(flag==0)
                    {
                    printf("\nContact not Found !\n");     
                    return;
                    }
                    //if contact number found based on serial number deteting contact detail
                    if(flag)
                    {
                         printf("\nEnter Sl no. of Contact to Delete : ");   
                         scanf("%d",&index);
                         // Remove the contact by shifting subsequent contact
                            for(i=index-1;i<addressBook->contactCount-1;i++)
                            {
                                addressBook->contacts[i]=addressBook->contacts[i+1];  
                            }
                            printf("--Contact Deleted Successfully--"); 
                             
                            addressBook->contactCount--;  //updating contact count                                        
                    }
            }
            break;
        case 3: //Deleting by Email
        {
            char Emailid[20];
            int flag= 0;
            int i, index=0;
            printf("Enter Email_id:\n");
            getchar();            
            scanf("%[^\n]", Emailid);

    
                for(i=0;i<addressBook->contactCount;i++)
               {
                    if(strstr(addressBook->contacts[i].email,Emailid)!=NULL)     
                    {
                        flag=1;
                        printf("%d \t\t%s\t\t%s\t\t%s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                    }  
               }                                                                  
            if(flag==0)
                {
                    printf("\nContact not Found !\n");     
                    return;
                }
                //if contact found deleating contact name by serial number.
                    if(flag)
                {
                    printf("\nEnter Sl no. of Contact to Delete : ");   
                    scanf("%d",&index);
                    // Remove the contact by shifting subsequent contact
                    for(i=index-1;i<addressBook->contactCount-1;i++)
                    {
                        addressBook->contacts[i]=addressBook->contacts[i+1]; 
                    } 
                    printf("--Contact Deleted Successfully--");  
                    addressBook->contactCount--; //updating contact count
                }
            }

            break;       
       }

    }
}
    //NOTE:break,getchar,scanf
		//break is used to exit from switch
        //getchar is used to clear buffer input
        //scanf is used to read the input format
        //printf is used to print the statements either input from user statements or outputs
        //selective scanf is used for reading up to new line(\n)