#include <stdio.h>
#include "file.h"
#include<string.h>
#include<stdlib.h>
//Function defination to save the contacts from address-book to .csv file.
void saveContactsToFile(AddressBook *addressBook) 
{
  FILE *sc;
  sc=fopen("shiva.csv","w");// opening file in write mode.

//Check the file if successfully opened.
  if(sc==NULL)
  {
      printf("file is not present");
      return;//if file not present exit.

  }
  int i;
  fprintf(sc,"#%d",addressBook->contactCount);
  fprintf(sc,"\n");
    //writing each contact detail to the file in csv format.
    for( i=0;i<addressBook->contactCount;i++)
    {
      fprintf(sc,"\n%s,%s,%s",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
  fclose(sc);//Closing the file after writing.
}


//Function defination to load the contact detail from csv file in to address book.
void loadContactsFromFile(AddressBook *addressBook) 
{

  FILE *fptr;
  fptr = fopen("shiva.csv","r");//Opening the fie in ("r")read mode.

      if(fptr == NULL)
        {
          printf("Error file is not opened");
          exit(1);// Exit from  program  if file not opened.
        }
      
      char str[100];
    int i;
    if(fgets(str,sizeof(str),fptr)!=NULL)//Reading the 1st line to get the no of contacts.
    {
      if(str[0] == '#')//Check if line start with #.
      {
        addressBook->contactCount=atoi(str+1);//Using atoi converting string after #(str+1) to integer to set contact count.
        for(i=0;i<addressBook->contactCount;i++)
        {
          Contact contacts = addressBook->contacts[i];//Assigning all contacts from address->contacts[i]one by one  to contacts.
          fscanf(fptr, "%[^,], %[^,],%[^\n]\n", contacts.name,contacts.phone,contacts.email);
        }
      }
   }
 fclose(fptr);// close the file after reading.  
}
