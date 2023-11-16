#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cctype>
#include <limits>

using namespace std;

class Contact {
public:
    string name;
    string phoneNumber;
};

class AddressBook {
private:
    vector<Contact> contacts;

public:
   void addContact(const string& name, const string& phoneNumber) {
    // Check if the phone number contains only numeric characters and is of maximum length 12
    if (phoneNumber.find_first_not_of("0123456789") != string::npos || phoneNumber.length() > 12) {
        cout << "Invalid phone number. Please enter a numeric value of maximum 12 digits." << endl;
        return;
    }

    // If the phone number is valid, proceed to add the contact
    Contact newContact;
    newContact.name = name;
    newContact.phoneNumber = phoneNumber;
    contacts.push_back(newContact);
    cout << "Contact added successfully." << endl;
}



   void updateContact(const string& name, const string& newPhoneNumber) {
    int count = 0;
    vector<Contact*> matchingContacts;

    for (auto& contact : contacts) {
        if (contact.name == name) {
            matchingContacts.push_back(&contact);
            count++;
        }
    }

    if (count == 0) {
        cout << "Contact not found." << endl;
    } else if (count == 1) {
        // If only one contact matches the name, update its number directly
        matchingContacts[0]->phoneNumber = newPhoneNumber;
        cout << "Contact updated successfully." << endl;
    } else {
        cout << "There are " << count << " contacts with the name '" << name << "'. Which one do you want to update?" << endl;
        for (int i = 0; i < count; ++i) {
            cout << i + 1 << ". " << matchingContacts[i]->name << ", Phone Number: " << matchingContacts[i]->phoneNumber << endl;
        }

        int choice;
        cout << "Enter the number of the contact you want to update: ";
        if (!(cin >> choice) || choice < 1 || choice > count) {
            cout << "Invalid input. Please enter a valid number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        // Update the selected contact's phone number
        matchingContacts[choice - 1]->phoneNumber = newPhoneNumber;
        cout << "Contact updated successfully." << endl;
    }
}


    void updateNameByPhoneNumber(const string& phoneNumber, const string& newName) {
        auto it = find_if(contacts.begin(), contacts.end(), [&phoneNumber](const Contact& c) {
            return c.phoneNumber == phoneNumber;
        });

        if (it != contacts.end()) {
            it->name = newName;
            cout << "Name updated successfully." << endl;
        } else {
            cout << "Contact not found." << endl;
        }
    }

    void deleteContact(const string& name) {
        auto it = remove_if(contacts.begin(), contacts.end(), [&name](const Contact& c) {
            return c.name == name;
        });

        if (it != contacts.end()) {
            contacts.erase(it, contacts.end());
            cout << "Contact deleted successfully." << endl;
        } else {
            cout << "Contact not found." << endl;
        }
    }

    void searchContactByName(const string& name) {
        auto it = find_if(contacts.begin(), contacts.end(), [&name](const Contact& c) {
            return c.name == name;
        });

        if (it != contacts.end()) {
            cout << "Contact found: " << it->name << ", Phone Number: " << it->phoneNumber << endl;
        } else {
            cout << "Contact not found." << endl;
        }
    }

    void searchContactByPhoneNumber(const string& phoneNumber) {
        auto it = find_if(contacts.begin(), contacts.end(), [&phoneNumber](const Contact& c) {
            return c.phoneNumber == phoneNumber;
        });

        if (it != contacts.end()) {
            cout << "Contact found: " << it->name << ", Phone Number: " << it->phoneNumber << endl;
        } else {
            cout << "Contact not found." << endl;
        }
    }

     void bubbleSortContacts() {
    int n = contacts.size();
    bool swapped;
    do {
        swapped = false;
        for (int i = 0; i < n - 1; i++) {
            if (contacts[i].name > contacts[i + 1].name) {
                swap(contacts[i], contacts[i + 1]);
                swapped = true;
            }
        }
    } while (swapped);
}

void displayAllContacts() {
    // Sort the contacts using the custom sorting function
    bubbleSortContacts();


    // Print the sorted contacts
    cout << setw(20) << "Name" << setw(20) << "Phone Number" << endl;
    cout << "---------------------------------------------" << endl;
    for (const auto& contact : contacts) {
        cout << setw(20) << contact.name << setw(20) << contact.phoneNumber << endl;
    }
}

    void saveContactsToFile(const string& filename) {
        ofstream file(filename);
        if (file.is_open()) {
            for (const auto& contact : contacts) {
                file << contact.name << "," << contact.phoneNumber << endl;
            }
            cout << "Contacts saved to file successfully." << endl;
        } else {
            cerr << "Error: Could not open the file for saving contacts." << endl;
        }
    }

    void loadContactsFromFile(const string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            contacts.clear();
            string line;
            while (getline(file, line)) {
                size_t pos = line.find(",");
                if (pos != string::npos) {
                    Contact contact;
                    contact.name = line.substr(0, pos);
                    contact.phoneNumber = line.substr(pos + 1);
                    contacts.push_back(contact);
                }
            }
            cout << "Contacts loaded from file successfully." << endl;
        } else {
            cerr << "Error: Could not open the file for loading contacts." << endl;
        }
    }

    void clearAllContacts() {
        contacts.clear();
        cout << "All contacts cleared." << endl;
    }

   void searchContactsByRange(char startChar, char endChar) {
    bubbleSortContacts();
    cout << "Contacts with names starting from '" << startChar << "' to '" << endChar << "':" << endl;
    for (const auto& contact : contacts) {
        if (toupper(contact.name[0]) >= toupper(startChar) && toupper(contact.name[0]) <= toupper(endChar)) {
            cout << setw(20) << contact.name << setw(20) << contact.phoneNumber << endl;
        }
    }
}


    int getContactCount() const {
        return contacts.size();
    }
};

bool isValidRange(char startChar, char endChar) {
    return (isalpha(startChar) && isalpha(endChar) && toupper(startChar) <= toupper(endChar));
}

int main() {
    AddressBook addressBook;
    string name, phoneNumber, newPhoneNumber, filename, newName;
    char startChar, endChar;
    int choice;

    do {
        cout << "\n[--------------------------------------Welcome to Contact Directory:--------------------------------------]" << endl;
        cout << endl;
        cout << endl;
        cout << "\n[---------------------------------------Contact Menu:-----------------------------------------------------]" << endl;
        cout << endl;
        cout << endl;
        cout << "1. Add Contact" << endl;
        cout << "2. Update Contact by Name" << endl;
        cout << "3. Delete Contact" << endl;
        cout << "4. Search Contact by Name" << endl;
        cout << "5. Search Contact by Phone Number" << endl;
        cout << "6. Display All Contacts" << endl;
        cout << "7. Save Contacts to File" << endl;
        cout << "8. Load Contacts from File" << endl;
        cout << "9. Clear All Contacts" << endl;
        cout << "10. Search Contacts by Name Range" << endl;
        cout << "11. Get Contact Count" << endl;
        cout << "12. Update Contact by Phone Number" << endl;
        cout << "13. Exit" << endl;
        cout << "Enter Choice : ";

        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue; // Ask for input again
        }

        switch (choice) {
        case 1: {
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear any residual characters in the buffer
    cout << "Enter Name: ";
    getline(cin, name);
    cout << "Enter Phone Number: ";
    
    cin.ignore(); // Ignore the newline character after entering the name
    getline(cin, phoneNumber);
    
    if (phoneNumber.find_first_not_of("0123456789") != string::npos || phoneNumber.length() > 12 ) {
        cout << "Invalid phone number. Please enter a numeric value of maximum 12 digits." << endl;
        // Handle the invalid phone number input as required
    } else {
        addressBook.addContact(name, phoneNumber);
    }
    break;
}




          case 2: {
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear any residual characters in the buffer
    cout << "Enter Name to update: ";
    getline(cin, name);
    cout << "Enter new Phone Number: ";
    getline(cin, newPhoneNumber);

    if (newPhoneNumber.find_first_not_of("0123456789") != string::npos || newPhoneNumber.length() > 12) {
        cout << "Invalid phone number. Please enter a numeric value of maximum 12 digits." << endl;
        // Handle the invalid phone number input as required
    } else {
        addressBook.updateContact(name, newPhoneNumber);
    }
    break;
}

            case 3: {
                cout << "Enter Name to delete: ";
                cin >> name;
                addressBook.deleteContact(name);
                break;
            }
            case 4: {
                cout << "Enter Name to search: ";
                cin >> name;
                addressBook.searchContactByName(name);
                break;
            }
            case 5: {
                cout << "Enter Phone Number to search: ";
                cin >> phoneNumber;
                addressBook.searchContactByPhoneNumber(phoneNumber);
                break;
            }
            case 6: {
                addressBook.displayAllContacts();
                break;
            }
            case 7: {
                cout << "Enter filename to save: ";
                cin >> filename;
                addressBook.saveContactsToFile(filename);
                break;
            }
            case 8: {
                cout << "Enter filename to load: ";
                cin >> filename;
                addressBook.loadContactsFromFile(filename);
                break;
            }
            case 9: {
                addressBook.clearAllContacts();
                break;
            }
            case 10: {
                cout << "Enter start character: ";
                cin >> startChar;
                cout << "Enter end character: ";
                cin >> endChar;
                if (isValidRange(startChar, endChar)) {
                    addressBook.searchContactsByRange(startChar, endChar);
                } else {
                    cout << "Invalid range. Please enter valid characters." << endl;
                }
                break;
            }
            case 11: {
                cout << "Number of contacts: " << addressBook.getContactCount() << endl;
                break;
            }
            case 12: {
                cout << "Enter Phone Number to update: ";
                cin >> phoneNumber;
                cout << "Enter new Name: ";
                cin >> newName;
                addressBook.updateNameByPhoneNumber(phoneNumber, newName);
                break;
            }
            case 13: {
                cout << "Exiting..." << endl;
                break;
            }
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 13);

    return 0;
}
