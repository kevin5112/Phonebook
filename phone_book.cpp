// menu:
// 1. add contact
//      - add first name
//      - add phone number
// 2. remove contact
//      *edge case - same name
// 3. search contact
//      - search by name(*edge case - same name)
// 4. display contacts

#include <iostream>
#include <list>
#include <string>
#include <boost/algorithm/string.hpp>
using namespace std;

class Contact
{
public:

    string  GetName()
    {
        return name;
    }

    void  SetName(string newName)
    {
        name = newName;
    }

    void  SetNumber(string newNumber)
    {
        number = newNumber;
    }

    string  GetNumber()
    {
        return number;
    }

private:
    string  name;
    string  number;
};

void    DisplayMenu();
void    AddContact(Contact newContact, list<Contact> &phoneBook);
void    DisplayContacts(list<Contact> phoneBook);
void    RemoveContact(string name, list<Contact> &phoneBook);
void    SearchContact(string name, list<Contact> &phoneBook);
void    DisplaySingleContact(Contact foundContact, list<Contact> &phoneBook);

int     main()
{
    Contact         newContact;
    string          name;
    string          phoneNumber;
    list<Contact>   phoneBook;
    int             userInput;
    string          nameToDelete;
    string          nameToSearch;

    while(true)
    {
        DisplayMenu();
        cin >> userInput;
        if(cin.fail())
        { 
            cout << "Not an int.. Please try again.\n\n";

            // clears cin error state
            cin.clear();

            //disgards 'bad' characters
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        switch (userInput)
        {
            case 1: // Add Contact
                cout << "Enter first name of contact: ";
                cin >> name;
                newContact.SetName(name);
                cout << "Enter phone number: ";
                cin >> phoneNumber;
                newContact.SetNumber(phoneNumber);
                AddContact(newContact, phoneBook);
                break;
            case 2: // Remove Contact
                if(phoneBook.size() > 1)
                {
                    cout << "Enter name of contact to remove: ";
                    cin >> nameToDelete;
                }
                RemoveContact(nameToDelete, phoneBook);
                break;
            case 3: // Search Contact
                if(phoneBook.size() > 1)
                {
                    cout << "Enter name of contact to search: ";
                    cin >> nameToSearch;
                }
                SearchContact(nameToSearch, phoneBook);
                break;
            case 4: // Display Contacts
                DisplayContacts(phoneBook);
                break;
            case 5: // Exit
                cout << "Program Terminating...\n";
                exit(0);
                break;
            default: // Invalid Responses
                cout << "Invalid Response. Please try again..\n";
                break;

        }
    }
    return 0;
}

void    DisplayMenu()
{
    cout << "Menu:\n"
         << "1. Add Contact\n"
         << "2. Remove Contact\n"
         << "3. Search Contact\n"
         << "4. Display Contacts\n"
         << "5. Exit\n\n"
         << "Please pick an option: ";
}

void    AddContact(Contact newContact, list<Contact> &phoneBook)
{
    if(phoneBook.empty())
    {
        phoneBook.push_back(newContact);
        return;
    }

    for(list<Contact>::iterator it = phoneBook.begin(); it != phoneBook.end(); ++it)
    {
        // checking to see which name comes first inorder to store in 
        // alphabetical order
        if(newContact.GetName() < it->GetName())
        {
            phoneBook.insert(it, newContact);
            return;
        }
    }
    phoneBook.push_back(newContact);
}

void    DisplayContacts(list<Contact> phoneBook)
{
    if(phoneBook.empty())
        cout << "Phonebook is empty..\n\n";
    for(list<Contact>::iterator it = phoneBook.begin(); it != phoneBook.end(); ++it)
    {
        cout << "\nName: " << it->GetName() << endl;
        cout << "Number: " << it->GetNumber() << endl << endl;
    }
    return;
}

void    RemoveContact(string name, list<Contact> &phoneBook)
{
    // case check for empty phoneBook
    if(phoneBook.empty())
    {   
        cout << "Phonebook is empty...\n\n";
        return;
    }

    // case check for one element in phoneBook
    if(phoneBook.size() == 1)
    {
        cout << "Removed last contact in Phonebook.\n";
        phoneBook.pop_front();
        return;
    }

    // making forloop to iterate through phoneBook to find target
    for(list<Contact>::iterator it = phoneBook.begin(); it != phoneBook.end(); ++it)
    {       
        // case insensitive check to see if names are the same
        if(boost::iequals(it->GetName(), name))
        {
            phoneBook.erase(it);
            return;
        }
    }

    cout << "Could not find name of contact.\n\n";
    return;
}

void    SearchContact(string name, list<Contact> &phoneBook)
{
    // returns if it's an empty phonebook
    if(phoneBook.empty())
    {
        cout << "Phonebook is empty...\n\n";
        return;
    }

    if(phoneBook.size() == 1)
    {
        cout << "There is only one contact in this phonebook.\n";
        DisplaySingleContact(phoneBook.front(), phoneBook);
        return;
    }

    // iterate through to find contact name, then call displaysinglecontact to display that single contact
    for(list<Contact>::iterator it = phoneBook.begin(); it != phoneBook.end(); ++it)
    {
        if(boost::iequals(it->GetName(), name))
        {
            DisplaySingleContact(*it, phoneBook);
            return;
        }
    }
    cout << "Contact not found...\n\n";
    return;
}

void    DisplaySingleContact(Contact foundContact, list<Contact> &phoneBook)
{
    cout << "Contact Info..\n"
         << "Name: " << foundContact.GetName() << endl
         << "Number: " << foundContact.GetNumber() << endl << endl;
    return;
}