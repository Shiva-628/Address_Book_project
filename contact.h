#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
    char slno;
} Contact;

typedef struct {
    Contact contacts[MAX_CONTACTS];
    int contactCount;
} AddressBook;

void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook, int sortCriteria);
void initialize(AddressBook *addressBook);

void saveContactsToFile(AddressBook *AddressBook);
void validate(char *phone, AddressBook *addressBook);
void gmail_validation(char *gmail_id, AddressBook *addressBook);
void gmail_e_validation(char *gmail_id, AddressBook *addressBook);
void delete_slno( AddressBook *addressBook, char serial_slno);


#endif
