#include <iostream>
#include <fstream>
#include <string>

#include <vector>
#include <algorithm>

using namespace std;

string filename = "contacts.txt";

struct Address
{
  string street;
  string city;
  string state;
  string postalCode;
};

struct Contact
{
  int id;
  string name;
  string phoneNumber;
  string email;
  Address address;
};

struct ContactProfile
{
  int id;
  string name;
  int contactIds[1000];
  int filledSize;
};

vector<Contact> readContactsFromFile(string filename)
{
  vector<Contact> contacts;
  ifstream file(filename);

  if (file.is_open())
  {
    Contact contact;
    while (file >> contact.id >> contact.name >> contact.address.street >> contact.address.city >> contact.address.state >> contact.address.postalCode >> contact.phoneNumber >> contact.email)
    {
      contacts.push_back(contact);
    }
    file.close();
  }
  else
  {
    cout << "Error opening file.\n";
  }

  return contacts;
}

void writeContactsToFile(const vector<Contact> &contacts, string filename)
{
  ofstream file(filename);

  if (file.is_open())
  {
    for (const Contact &contact : contacts)
    {
      file << contact.id << " " << contact.name << " " << contact.address.street << " " << contact.address.city << " " << contact.address.state << " " << contact.address.postalCode << " " << contact.phoneNumber << " " << contact.email << endl;
    }
    file.close();
    cout << "Contacts saved successfully.\n";
  }
  else
  {
    cout << "Error saving contacts to the file.\n";
  }
}

void displayContact(Contact contact)
{
  cout << "Contact ID: " << contact.id << endl;
  cout << "Name: " << contact.name << endl;
  cout << "Address: " << contact.address.street << ", " << contact.address.city << ", " << contact.address.state << " " << contact.address.postalCode << endl;
  cout << "Phone: " << contact.phoneNumber << endl;
  cout << "Email: " << contact.email << endl;
  cout << "-----------------------\n";
}

void displayAllContacts(const vector<Contact> &contacts)
{
  if (contacts.empty())
  {
    cout << "No contacts to display.\n";
  }
  else
  {
    for (const Contact &contact : contacts)
    {
      cout << "Contact ID: " << contact.id << endl;
      cout << "Name: " << contact.name << endl;
      cout << "Address: " << contact.address.street << ", " << contact.address.city << ", " << contact.address.state << " " << contact.address.postalCode << endl;
      cout << "Phone: " << contact.phoneNumber << endl;
      cout << "Email: " << contact.email << endl;
      cout << "-----------------------\n";
    }
  }
}

Contact readContact(vector<Contact> &contacts, int id)
{
  Contact found;
  for (const Contact &contact : contacts)
  {
    if (contact.id == id)
    {
      found = contact;
      break;
    }
  }

  return found;
}

void addContact(vector<Contact> &contacts)
{
  Contact contact;
  int nextId = 1;
  if (!contacts.empty())
  {
    nextId = contacts.back().id + 1;
  }

  contact.id = nextId;
  cout << "Enter contact name: \n";
  cin >> contact.name;
  cout << "Enter contact phone: \n";
  cin.ignore();
  getline(cin, contact.phoneNumber);
  cout << "Enter contact email: \n";
  getline(cin, contact.email);
  cout << "Enter contact address street: \n";
  getline(cin, contact.address.street);
  cout << "Enter contact address city: \n";
  getline(cin, contact.address.city);
  cout << "Enter contact address state: \n";
  getline(cin, contact.address.state);
  cout << "Enter contact address postal code: \n";
  getline(cin, contact.address.postalCode);

  contacts.push_back(contact);
  cout << "Contact added successfully.\n";
}

void sortContactsByName(vector<Contact> &contacts)
{
  sort(contacts.begin(), contacts.end(), [](const Contact &a, const Contact &b)
       { return a.name < b.name; });
}

void searchContactsByName(const vector<Contact> &contacts, string name)
{
  bool found = false;
  for (const Contact &contact : contacts)
  {
    if (contact.name.find(name) != string::npos)
    {
      cout << "Contact ID: " << contact.id << endl;
      cout << "Name: " << contact.name << endl;
      cout << "Address: " << contact.address.street << ", " << contact.address.city << ", " << contact.address.state << " " << contact.address.postalCode << endl;
      cout << "Phone: " << contact.phoneNumber << endl;
      cout << "Email: " << contact.email << endl;
      cout << "-----------------------\n";
      found = true;
    }
  }

  if (!found)
  {
    cout << "No contacts found with that name.\n";
  }
}


void addContactProfile(vector<ContactProfile> &profiles)
{
  ContactProfile profile;
  int nextId = 1;
  if (!profiles.empty())
  {
    nextId = profiles.back().id + 1;
  }

  profile.id = nextId;
  cout << "Enter contact profile name: \n";
  cin >> profile.name;
  profile.filledSize = 0;
  profiles.push_back(profile);

  cout << "Profile added successfully.\n";
}


void addContactByNameToProfile(ContactProfile profile, vector<Contact> &contacts, string name)
{
  bool found = false;
  for (const Contact &contact : contacts)
  {
    if (contact.name.find(name) != string::npos)
    {
      profile.contactIds[profile.filledSize] = contact.id;
      profile.filledSize++;
      found = true;
    }
  }
  if (!found){
      cout << "There is no user id or profile to add.\n";
  }
  else {
    cout << "Contact added to the Contact profile.\n";

  }
}

void searchContactProfileByName(const vector<ContactProfile> &profiles, string name)
{
  bool found = false;
  for (const ContactProfile &profile : profiles)
  {
    if (profile.name.find(name) != string::npos)
    {
      cout << "Profile ID: " << profile.id << endl;
      cout << "Name: " << profile.name << endl;
      cout << "-----------------------\n";
      found = true;
    }
  }

  if (!found)
  {
    cout << "No profile found with that name.\n";
  }
}

ContactProfile getContactProfileByName(const vector<ContactProfile> &profiles, string name)
{
  ContactProfile found;
  for (const ContactProfile &profile : profiles)
  {
    if (profile.name.find(name) != string::npos)
    {
      found = profile;
    }
  }

  return found;
}


void displayContactProfile(ContactProfile profile)
{
  cout << "Profile ID: " << profile.id << endl;
  cout << "Name: " << profile.name << endl;
  cout << "-----------------------\n";
}

void displayAllContactProfiles(const vector<ContactProfile> &profiles)
{
  if (profiles.empty())
  {
    cout << "No Profiles to display.\n";
  }
  else
  {
    for (const ContactProfile &profile : profiles)
    {
      cout << "Contact ID: " << profile.id << endl;
      cout << "Name: " << profile.name << endl;
      cout << "-----------------------\n";
    }
  }
}

ContactProfile readContactProfile(vector<ContactProfile> &profiles, int id)
{
  ContactProfile found;
  for (const ContactProfile &profile : profiles)
  {
    if (profile.id == id)
    {
      found = profile;
      break;
    }
  }

  return found;
}






int main()
{
  vector<Contact> contacts = readContactsFromFile(filename);
  vector<ContactProfile> profiles;
  int inputVar;
  do
  {
    cout << "\nContact Management System\n";
    cout << "1. Display all contacts\n";
    cout << "2. Display contact by ID\n";
    cout << "3. Add a contact\n";
    cout << "4. Sort contacts\n";
    cout << "5. Search contacts by name\n";
    cout << "6. Save contacts to file\n";
    cout << "7. Add Profile\n";
    cout << "8. Search profiles by name\n";
    cout << "9. Add contact to profile\n";
    cout << "10. Display all profiles\n";
    cout << "11. Display profile by ID\n";
    cout << "12. Exit\n";
    cout << "Enter your choice: ";
    cin >> inputVar;

    switch (inputVar)
    {
    case 1:
    {
      displayAllContacts(contacts);
    }
    break;
    case 2:
    {
      int id;
      cout << "Enter contact ID: ";
      cin >> id;
      Contact contact = readContact(contacts, id);
      displayContact(contact);
    }
    break;
    case 3:
    {
      addContact(contacts);
    }
    break;
    case 4:
    {
      sortContactsByName(contacts);
      cout << "Contacts sorted successfully.\n";
    }
    break;
    case 5:
    {
      string name;
      cout << "Enter name to search: ";
      cin.ignore();
      getline(cin, name);
      searchContactsByName(contacts, name);
    }
    break;
    case 6:
    {
      writeContactsToFile(contacts, filename);
      cout << "Contacts saved to file successfully.\n";
    }
    break;
    case 7:
    {
      addContactProfile(profiles);
    }
    break;
    case 8:
    {
      string name;
      cout << "Enter name to search: ";
      cin.ignore();
      getline(cin, name);
      searchContactProfileByName(profiles, name);
    }
    break;
    case 9:
    {
      string name;
      string profileName;
      ContactProfile profile;
      cout << "Enter contact name: ";
      cin.ignore();
      getline(cin, name);
      cout << "Enter profile name: ";
      getline(cin, profileName);
      profile = getContactProfileByName(profiles, name);
      addContactByNameToProfile(profile, contacts, name);
    }
    break;
    case 10:
    {
      displayAllContactProfiles(profiles);
    }
    break;
    case 11:
    {
      int id;
      cout << "Enter profile ID: ";
      cin >> id;
      ContactProfile profile = readContactProfile(profiles, id);
      displayContactProfile(profile);
    }
    case 12:
      cout << "Exiting...\n";
      break;
    default:
      cout << "Invalid choice.\n";
    }
  } while (inputVar != 12);

  return 0;
}
