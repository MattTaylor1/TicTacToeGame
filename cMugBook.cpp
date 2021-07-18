#include "cMugBook.h"
#include "cPerson.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>



cMugBook::cMugBook() {

}

cMugBook::~cMugBook() {

}

//Validation and other methods
bool cMugBook::checkPostal(std::string postalCode) {
    if (postalCode.length() != 7) { return false; }
    if (!isalpha(postalCode[0])) { return false; }
    if (!isdigit(postalCode[1])) { return false; }
    if (!isalpha(postalCode[2])) { return false; }
    if (!isspace(postalCode[3])) { return false; }
    if (!isdigit(postalCode[4])) { return false; }
    if (!isalpha(postalCode[5])) { return false; }
    if (!isdigit(postalCode[6])) { return false; }
    else {
        return true;
    }
}
bool cMugBook::checkString(std::string theString) {
    if (theString == "") {
        //string is blank/empty
        return false;
    }

    return true;
}
std::string cMugBook::formatString(std::string theString) {

    //format we are looking for is:
    //-1st char case upper
    //2nd char+ lower

    for (unsigned int i = 0; i < theString.length(); i++) {
        if (i == 0) {
            theString[i] = toupper(theString[i]);
        }
        else {
            theString[i] = tolower(theString[i]);
        }
    }
    return theString;
}
std::string cMugBook::formatProvince(std::string province) {

    std::string theProvince = "";

    for (unsigned int i = 0; i < province.length(); i++) {
        theProvince += toupper(province[i]);
    }

    return theProvince;

}

//cMugBook methods
bool cMugBook::addUser(cPerson* pThePerson) {

    cPerson* user = getUser(pThePerson->SIN);

    if (user != NULL) {
        //not null so already exists
        std::cout << "User already exists" << std::endl;
        return false;
        
    }

    //first
    //middle
    //last
    //gender (enum)
    //birthday (struct)
    //street#
    //streetName
    //streetType
    //streetDirection
    //city
    //province (enum)
    //postalCode char[7]
    //sin
    //phone# char[13]
    //m_vecFriendsList

    // first
    //if (!checkString(pThePerson->first)) {
      //  return false;
    //}

    //last
   // if (!checkString(pThePerson->last)) {
        //return false;
   // }

    //birthday(age)
   // if (pThePerson->birthDay.year < 1921 || pThePerson->birthDay.year > 2003) {
       // return false;
  //  }
   // if (pThePerson->birthDay.month < 1 || pThePerson->birthDay.month > 12) {
   //     return false;
  //  }
  //  if (pThePerson->birthDay.day < 1 || pThePerson->birthDay.day > 31) {
   //     return false;
   // }

    //street #
   // if (pThePerson->streetNumber < 1) {
   //     return false;
  //  }

    //streetname
   // if (!checkString(pThePerson->streetName)) {
   //     return false;
   // }

    //streetType
   // if (!checkString(pThePerson->streetType)) {
   //     return false;
   // }

    //city
   // if (!checkString(pThePerson->city)) {
   //     return false;
   // }

    //postal code...
    //if (!isalpha(pThePerson->postalCode[0])) { return false; }
   // if (!isdigit(pThePerson->postalCode[1])) { return false; }
   // if (!isalpha(pThePerson->postalCode[2])) { return false; }
   // if (!isspace(pThePerson->postalCode[3])) { return false; }
   // if (!isdigit(pThePerson->postalCode[4])) { return false; }
    //if (!isalpha(pThePerson->postalCode[5])) { return false; }
   // if (!isdigit(pThePerson->postalCode[6])) { return false; }



    //phone number...
    //for (unsigned int i = 0; i < 13; i++) {
        
      //  if ((pThePerson->phoneNumber[i] + 48) < 48 || (pThePerson->phoneNumber[i] + 48) > 57) {
      //      return false;
      //  }
        
    //}

    //SIN
        
    //for (unsigned int i = 0; i < this->m_vecUsers.size(); i++) {
      //  if (pThePerson->SIN = this->m_vecUsers[i]->SIN) {
       //     return false;
        //    }
       // }


    //they passed our gruelling validation process! we can add
    this->m_vecUsers.push_back(pThePerson);
    std::cout << "User added" << std::endl;
    return true;
    
}

bool cMugBook::deleteUser(unsigned int SIN) {

    //see if user exists
    for (unsigned int i = 0; i < this->m_vecUsers.size(); i++) {

        if (this->m_vecUsers[i]->SIN == SIN) {

            this->m_vecUsers.erase(this->m_vecUsers.begin() + i);
            std::cout << "User deleted" << std::endl;
            return true;
        }
    }
    //didn't exist
    std::cout << "User not on the list" << std::endl;
    return false;
}

bool cMugBook::updateUserLastName(unsigned int SIN, std::string newLastName) {

    //check if the user exists
    cPerson* user = getUser(SIN);

    if (user == NULL) {
        return false;
    }

    newLastName = formatString(newLastName);

    if (!checkString(newLastName)) {
        return false;
    }

    if (newLastName == user->last) {
        return false;
    }
    else {
        user->last = newLastName;
        return true;
    }
}

bool cMugBook::updateUserFirstName(unsigned int SIN, std::string newFirstName) {

    //check if the user exists
    cPerson* user = getUser(SIN);

    if (user == NULL) {
        return false;
    }

    newFirstName = formatString(newFirstName);

    if (!checkString(newFirstName)) {
        return false;
    }

        if (newFirstName == user->first) {
            return false;
        }
        else {
            user->first = newFirstName;
            return true;
        }
}

bool cMugBook::updateUserAddress(unsigned int SIN, int streetNumber, std::string streetName,
    std::string streetType, std::string streetDirection,
    std::string city, std::string province, /*Province now as enum)*/
    std::string postalCode, std::string& error) {

    //see if user exists
    cPerson* user = getUser(SIN);

    if (user == NULL) {
        //not added
        return false;
        error = "Error: User not added";
    }

    //streetNumber
    if (streetNumber > 0) {
      user->streetNumber = streetNumber;  
    }
    else {
        error = "Error: invalid street #";
        return false;
    }

    //streetName
    if (checkString(streetName)) {
        streetName = formatString(streetName);
        user->streetName = streetName;
    }
    else {
        error = "Error: invalid street name";
        return false;
    }

    //streetType
    if (checkString(streetType)) {
        streetType = formatString(streetType);
        user->streetType = streetType;
    }
    else {
        error = "Error: invalid street type";
        return false;
    }

    //Direction
    streetDirection = formatString(streetDirection);
    user->streetDirection = streetDirection;
    

    //City
    if (checkString(city)) {
        city = formatString(city);

        user->city = city;
    }
    else {
        error = "Error: invalid city";
        return false;
    }

    //province (set enums)...
    province = formatProvince(province);

    if (province == "ONTARIO") {
        user->province = cPerson::ONTARIO;
    }

    else if (province == "NUNAVUT") {
        user->province = cPerson::NUNAVUT;
    }

    else if (province == "NORTHWEST TERRITORIES") {
        user->province = cPerson::NORTHWEST_TERRITORIES;
    }

    else if (province == "BRITISH COLUMBIA") {
        user->province = cPerson::BRITISH_COLUMBIA;
    }

    else if (province == "SASKATCHEWAN") {
        user->province = cPerson::SASKATCHEWAN;
    }

    else if (province == "YUKON") {
        user->province = cPerson::YUKON;
    }

    else if (province == "NEWFOUNDLAND AND LABRADOR") {
        user->province = cPerson::NEWFOUNDLAND_AND_LABRADOR;
    }

    else if (province == "NEW BRUNSWICK") {
        user->province = cPerson::NEW_BRUNSWICK;
    }

    else if (province == "PRINCE EDWARD ISLAND") {
        user->province = cPerson::PRINCE_EDWARD_ISLAND;
    }

    else if (province == "QUEBEC") {
        user->province = cPerson::QUEBEC;
    }

    else if (province == "ALBERTA") {
        user->province = cPerson::ALBERTA;
    }

    else if (province == "MANITOBA") {
        user->province = cPerson::MANITOBA;
    }

    else if (province == "NOVA SCOTIA") {
        user->province = cPerson::NOVA_SCOTIA;
    }
    else {
        error = "Error: invalid province";
        return false;
    }


    //postalcode 
    if (checkPostal(postalCode)) {
        
            for (int i = 0; i < 7; i++) {
                user->postalCode[i] = postalCode[i];
            }

    }
    else {
        error = "Error: invalid postal code";
        return false;
    }

    return true;
}

bool cMugBook::updateUserGender(unsigned int SIN, cPerson::eGenderType newGenderExpression) {

    //does the person exist
    cPerson* user = getUser(SIN);

    if (user == NULL) {
        return false;
    }


    if (user->gender != newGenderExpression) {

        if (newGenderExpression == cPerson::MALE) {
            user->gender = newGenderExpression;
            return true;
        }
        else if (newGenderExpression == cPerson::FEMALE) {
            user->gender = newGenderExpression;
            return true;
        }
        else if (newGenderExpression == cPerson::NON_BINARY) {
            user->gender = newGenderExpression;
            return true;
        }
        else if (newGenderExpression == cPerson::RATHER_NOT_SAY_UNKNOWN) {
            user->gender = newGenderExpression;
            return true;
        }
        
    }
    else {
        //uhhhhhhhhhhh idk man
        std::cout << "critical error man" << std::endl;
        return false;
    }

}

bool cMugBook::updateUserPhoneNumber(unsigned int SIN, unsigned char phoneNumber[13]) {
    
    //check is user exists
    cPerson* user = getUser(SIN);

    if (user == NULL) {
        return false;
    }

    bool updated = false;
    
    for (unsigned int i = 0; i < 13; i++) {

        if (user->phoneNumber[i] != phoneNumber[i] && phoneNumber[i] != '\0') {
            user->phoneNumber[i] = phoneNumber[i] + 48;
            updated = true;
        }
    }
    return updated;
}

cPerson* cMugBook::getUser(unsigned int SIN) {

    //see if user exists
    for (unsigned int i = 0; i < this->m_vecUsers.size(); i++) {

        if (this->m_vecUsers[i]->SIN == SIN) { 
            return this->m_vecUsers[i]; 
        }
    }
    return NULL;
}

bool cMugBook::addFriend(unsigned int UserSIN, unsigned int FriendSIN, std::string& error) {

    //see if user exists
    cPerson* user = getUser(UserSIN);

    if (user == NULL) {
        error = "User isn't in MugBook";
        return false;
    }

    //see if friend exsists too
    cPerson* theFriend = getUser(FriendSIN);

    if (theFriend == NULL) {
        error = "The friend to add isn't in MugBook";
        return false;
    }

    //	* user and friend are the same person?
    if (user->SIN == theFriend->SIN) {
        error = "User and friend to add are the same";
        return false;
    }

    //already friends?
    for (unsigned int i = 0; i < user->m_vecFriendsList.size(); i++) {
        if (user->m_vecFriendsList[i]->SIN == theFriend->SIN) {
            error = "User and friend to add are already friends";
            return false;
        }
    }

    //okay now you can be friends
    user->m_vecFriendsList.push_back(theFriend);
    std::cout << "Friend was added" << std::endl;
    return true;
}

bool cMugBook::unFriend(unsigned int UserSIN, unsigned int FormerFriendSIN, std::string& error) {

    //see if user exists
    cPerson* user = getUser(UserSIN);
    if (user == NULL) {
        error = "User isn't in MugBook";
        return false;
    }

    //see if friend exsists too
    cPerson* theFormerFriend = getUser(FormerFriendSIN);
    if (theFormerFriend == NULL) {
        error = "The friend to add isn't in MugBook";
        return false;
    }

    //	* user and friend are the same person?
    if (user->SIN == theFormerFriend->SIN) {
        error = "User and former friend are the same";
        return false;
    }

    //loop through friends list, if former friend is there, remove them
    for (unsigned int i = 0; i < user->m_vecFriendsList.size(); i++) {
        if (user->m_vecFriendsList[i]->SIN == theFormerFriend->SIN) {

            user->m_vecFriendsList.erase(user->m_vecFriendsList.begin() + i);
            return true;
        }
    }
    error = "Former friend was not on the user's friend list";
    return false;
}

bool cMugBook::getFriendList(unsigned int UsersSIN, std::vector<cPerson*>& vecFriendList) {

    //user exists?
    cPerson* user = getUser(UsersSIN);
    if (user->SIN == NULL) {
        return false;
    }

    for (unsigned int i = 0; i < user->m_vecFriendsList.size(); i++) {
        vecFriendList.push_back(user->m_vecFriendsList[i]);
    }
    return true;
}


bool cMugBook::saveState(std::string fileName) {

    //open a file for output
    std::ofstream userFile(fileName.c_str());

//first
//middle
//last
//gender (enum)
//birthday (struct) yyyy/mm/dd
//street#
//streetName
//streetType
//streetDirection
//city
//province (enum)
//postalCode char[7]
//sin
//phone# char[13]
//m_vecFriendsList

    for (unsigned int i = 0; i < m_vecUsers.size(); i++) {

        userFile

            << m_vecUsers[i]->first << ","
            << m_vecUsers[i]->middle << ","
            << m_vecUsers[i]->last << ","
            << m_vecUsers[i]->getGenderAsString() << ","
            << m_vecUsers[i]->birthDay.year << ","
            << m_vecUsers[i]->birthDay.month << ","
            << m_vecUsers[i]->birthDay.day << ","
            << m_vecUsers[i]->streetNumber << ","
            << m_vecUsers[i]->streetName << ","
            << m_vecUsers[i]->streetType << ","
            << m_vecUsers[i]->streetDirection << ","
            << m_vecUsers[i]->city << ","
            << m_vecUsers[i]->getProvinceAsString() << ","
            << m_vecUsers[i]->getPostalCodeAsString() << ","
            << m_vecUsers[i]->SIN << ","
            << m_vecUsers[i]->getPhoneNumberAsString() << ",";

        //16th index btw
        for (unsigned int j = 0; j < m_vecUsers[i]->m_vecFriendsList.size(); j++) {
            userFile
                << m_vecUsers[i]->m_vecFriendsList[j]->SIN << ",";
        }
        userFile << std::endl;
    }
    

    return true;
}

bool cMugBook::loadState(std::string fileName) {

    m_vecUsers.clear();

    std::ifstream userFile(fileName.c_str());
    
    std::string error;
    std::string line;
    std::string tempString;

    while (getline(userFile, line)) {

        cPerson* user = new cPerson();

        //first
        std::stringstream ss(line);
        getline(ss, user->first, ',');

        //middle
        getline(ss, user->middle, ',');

        //last
        getline(ss, user->last, ',');

        //gender (enum)
        getline(ss, tempString, ',');

        if (tempString == "MALE") {
            user->gender = cPerson::MALE;
        }
        else if (tempString == "FEMALE") {
            user->gender = cPerson::FEMALE;
        }
        else if (tempString == "NON_BINARY") {
            user->gender = cPerson::NON_BINARY;
        }
        else {
            user->gender = cPerson::RATHER_NOT_SAY_UNKNOWN;
        }
        
        //birthyear
        getline(ss, tempString, ',');
        user->birthDay.year = stoi(tempString);

        //birthmonth
        getline(ss, tempString, ',');
        user->birthDay.month = stoi(tempString);

        //birthDay
        getline(ss, tempString, ',');
        user->birthDay.day = stoi(tempString);

        //streetNum
        getline(ss, tempString, ',');
        user->streetNumber = stoi(tempString);

        //streetName
        getline(ss, user->streetName, ',');

        //streetType
        getline(ss, user->streetType, ',');

        //streetDirection
        getline(ss, user->streetDirection, ',');

        //city
        getline(ss, user->city, ',');

        //province (enum)
        getline(ss, tempString, ',');

        if (tempString == "NUNAVUT") {
            user->province = cPerson::NUNAVUT;
        }
        else if (tempString == "NORTHWEST TERRITORIES") {
            user->province = cPerson::NORTHWEST_TERRITORIES;
        }
        else if (tempString == "BRITISH COLUMBIA") {
            user->province = cPerson::BRITISH_COLUMBIA;
        }
        else if (tempString == "SASKATCHEWAN") {
            user->province = cPerson::SASKATCHEWAN;
        }
        else if (tempString == "YUKON") {
            user->province = cPerson::YUKON;
        }
        else if (tempString == "NEWFOUNDLAND AND LABRADOR") {
            user->province = cPerson::NEWFOUNDLAND_AND_LABRADOR;
        }
        else if (tempString == "NEW BRUNSWICK") {
            user->province = cPerson::NEW_BRUNSWICK;
        }
        else if (tempString == "PRINCE EDWARD ISLAND") {
            user->province = cPerson::PRINCE_EDWARD_ISLAND;
        }
        else if (tempString == "QUEBEC") {
            user->province = cPerson::QUEBEC;
        }
        else if (tempString == "ONTARIO") {
            user->province = cPerson::ONTARIO;
        }
        else if (tempString == "ALBERTA") {
            user->province = cPerson::ALBERTA;
        }
        else if (tempString == "MANITOBA") {
            user->province = cPerson::MANITOBA;
        }
        else if (tempString == "NOVA SCOTIA") {
            user->province = cPerson::NOVA_SCOTIA;
        }

        //postalCode
        getline(ss, tempString, ',');
        for (unsigned int i = 0; i < tempString.length(); i++) {
            user->postalCode[i] = tempString[i];
        }

        //SIN 
        getline(ss, tempString, ',');
        user->SIN = stoi(tempString);

        //phoneNumber
        getline(ss, tempString, ',');

        unsigned int numZero = 17 - tempString.length();

        if (numZero == 0) {
            user->phoneNumber[0] = tempString[1] - 48;
            user->phoneNumber[1] = tempString[2] - 48;
            user->phoneNumber[2] = tempString[3] - 48;
            user->phoneNumber[3] = tempString[5] - 48;
            user->phoneNumber[4] = tempString[6] - 48;
            user->phoneNumber[5] = tempString[7] - 48;
            user->phoneNumber[6] = tempString[9] - 48;
            user->phoneNumber[7] = tempString[10] - 48;
            user->phoneNumber[8] = tempString[11] - 48;
            user->phoneNumber[9] = tempString[13] - 48;
            user->phoneNumber[10] = tempString[14] - 48;
            user->phoneNumber[11] = tempString[15] - 48;
            user->phoneNumber[12] = tempString[16] - 48;
        }
        
        if (numZero == 1) {
            user->phoneNumber[0] = 0;
            user->phoneNumber[1] = tempString[1] - 48;
            user->phoneNumber[2] = tempString[2] - 48;
            user->phoneNumber[3] = tempString[4] - 48;
            user->phoneNumber[4] = tempString[5] - 48;
            user->phoneNumber[5] = tempString[6] - 48;
            user->phoneNumber[6] = tempString[8] - 48;
            user->phoneNumber[7] = tempString[9] - 48;
            user->phoneNumber[8] = tempString[10] - 48;
            user->phoneNumber[9] = tempString[12] - 48;
            user->phoneNumber[10] = tempString[13] - 48;
            user->phoneNumber[11] = tempString[14] - 48;
            user->phoneNumber[12] = tempString[15] - 48;
        }

        if (numZero == 2) {
            user->phoneNumber[0] = 0;
            user->phoneNumber[1] = 0;
            user->phoneNumber[2] = tempString[1] - 48;
            user->phoneNumber[3] = tempString[3] - 48;
            user->phoneNumber[4] = tempString[4] - 48;
            user->phoneNumber[5] = tempString[5] - 48;
            user->phoneNumber[6] = tempString[7] - 48;
            user->phoneNumber[7] = tempString[8] - 48;
            user->phoneNumber[8] = tempString[9] - 48;
            user->phoneNumber[9] = tempString[11] - 48;
            user->phoneNumber[10] = tempString[12] - 48;
            user->phoneNumber[11] = tempString[13] - 48;
            user->phoneNumber[12] = tempString[14] - 48;
        }

        
        
        //addUser
        addUser(user);

    }

    
    //friends list
    std::ifstream friendList(fileName.c_str());
    std::string theLine;
    unsigned int count = 0;

    
        while (getline(friendList, theLine) && count < m_vecUsers.size()) {

            std::stringstream ss(theLine);
            cPerson* user = getUser(m_vecUsers[count]->SIN);

            getline(ss, tempString, ',');
            getline(ss, tempString, ',');
            getline(ss, tempString, ',');
            getline(ss, tempString, ',');
            getline(ss, tempString, ',');
            getline(ss, tempString, ',');
            getline(ss, tempString, ',');
            getline(ss, tempString, ',');
            getline(ss, tempString, ',');
            getline(ss, tempString, ',');
            getline(ss, tempString, ',');
            getline(ss, tempString, ',');
            getline(ss, tempString, ',');
            getline(ss, tempString, ',');
            getline(ss, tempString, ',');
            getline(ss, tempString, ',');
            getline(ss, tempString, ',');

            while (tempString != "") {
                cPerson* theFriend = getUser(stoi(tempString));
                addFriend(user->SIN, theFriend->SIN, error);
                getline(ss, tempString, ',');
            }

            count++;
        }

    

          

    return true;
}

//BONUS saveUser
bool cMugBook::saveUser(unsigned int SIN, std::string filename) {

    cPerson* user = getUser(SIN);

    if (user == NULL) {
        //not in mb
        return false;
    }

    std::ofstream userFile(filename.c_str());

    userFile

        << user->first << ","
        << user->middle << ","
        << user->last << ","
        << user->getGenderAsString() << ","
        << user->birthDay.year << ","
        << user->birthDay.month << ","
        << user->birthDay.day << ","
        << user->streetNumber << ","
        << user->streetName << ","
        << user->streetType << ","
        << user->streetDirection << ","
        << user->city << ","
        << user->getProvinceAsString() << ","
        << user->getPostalCodeAsString() << ","
        << user->SIN << ","
        << user->getPhoneNumberAsString() << ",";

    for (unsigned int i = 0; i < user->m_vecFriendsList.size(); i++) {
        userFile
            << user->m_vecFriendsList[i]->SIN << ",";
    }
    userFile << std::endl;

    return true;

}

bool cMugBook::loadUser(std::string fileName) {

    std::ifstream sUser(fileName.c_str());

    std::string error;
    std::string line;
    std::string tempString;

    while (getline(sUser, line)) {

        cPerson* user = new cPerson();

        //first
        std::stringstream ss(line);
        getline(ss, user->first, ',');

        //middle
        getline(ss, user->middle, ',');

        //last
        getline(ss, user->last, ',');

        //gender (enum)
        getline(ss, tempString, ',');

        if (tempString == "MALE") {
            user->gender = cPerson::MALE;
        }
        else if (tempString == "FEMALE") {
            user->gender = cPerson::FEMALE;
        }
        else if (tempString == "NON_BINARY") {
            user->gender = cPerson::NON_BINARY;
        }
        else {
            user->gender = cPerson::RATHER_NOT_SAY_UNKNOWN;
        }

        //birthyear
        getline(ss, tempString, ',');
        user->birthDay.year = stoi(tempString);

        //birthmonth
        getline(ss, tempString, ',');
        user->birthDay.month = stoi(tempString);

        //birthDay
        getline(ss, tempString, ',');
        user->birthDay.day = stoi(tempString);

        //streetNum
        getline(ss, tempString, ',');
        user->streetNumber = stoi(tempString);

        //streetName
        getline(ss, user->streetName, ',');

        //streetType
        getline(ss, user->streetType, ',');

        //streetDirection
        getline(ss, user->streetDirection, ',');

        //city
        getline(ss, user->city, ',');

        //province (enum)
        getline(ss, tempString, ',');

        if (tempString == "NUNAVUT") {
            user->province = cPerson::NUNAVUT;
        }
        else if (tempString == "NORTHWEST TERRITORIES") {
            user->province = cPerson::NORTHWEST_TERRITORIES;
        }
        else if (tempString == "BRITISH COLUMBIA") {
            user->province = cPerson::BRITISH_COLUMBIA;
        }
        else if (tempString == "SASKATCHEWAN") {
            user->province = cPerson::SASKATCHEWAN;
        }
        else if (tempString == "YUKON") {
            user->province = cPerson::YUKON;
        }
        else if (tempString == "NEWFOUNDLAND AND LABRADOR") {
            user->province = cPerson::NEWFOUNDLAND_AND_LABRADOR;
        }
        else if (tempString == "NEW BRUNSWICK") {
            user->province = cPerson::NEW_BRUNSWICK;
        }
        else if (tempString == "PRINCE EDWARD ISLAND") {
            user->province = cPerson::PRINCE_EDWARD_ISLAND;
        }
        else if (tempString == "QUEBEC") {
            user->province = cPerson::QUEBEC;
        }
        else if (tempString == "ONTARIO") {
            user->province = cPerson::ONTARIO;
        }
        else if (tempString == "ALBERTA") {
            user->province = cPerson::ALBERTA;
        }
        else if (tempString == "MANITOBA") {
            user->province = cPerson::MANITOBA;
        }
        else if (tempString == "NOVA SCOTIA") {
            user->province = cPerson::NOVA_SCOTIA;
        }

        //postalCode
        getline(ss, tempString, ',');
        for (unsigned int i = 0; i < tempString.length(); i++) {
            user->postalCode[i] = tempString[i];
        }

        //SIN 
        getline(ss, tempString, ',');
        user->SIN = stoi(tempString);

        //phoneNumber
        getline(ss, tempString, ',');

        unsigned int numZero = 17 - tempString.length();

        if (numZero == 0) {
            user->phoneNumber[0] = tempString[1] - 48;
            user->phoneNumber[1] = tempString[2] - 48;
            user->phoneNumber[2] = tempString[3] - 48;
            user->phoneNumber[3] = tempString[5] - 48;
            user->phoneNumber[4] = tempString[6] - 48;
            user->phoneNumber[5] = tempString[7] - 48;
            user->phoneNumber[6] = tempString[9] - 48;
            user->phoneNumber[7] = tempString[10] - 48;
            user->phoneNumber[8] = tempString[11] - 48;
            user->phoneNumber[9] = tempString[13] - 48;
            user->phoneNumber[10] = tempString[14] - 48;
            user->phoneNumber[11] = tempString[15] - 48;
            user->phoneNumber[12] = tempString[16] - 48;
        }

        if (numZero == 1) {
            user->phoneNumber[0] = 0;
            user->phoneNumber[1] = tempString[1] - 48;
            user->phoneNumber[2] = tempString[2] - 48;
            user->phoneNumber[3] = tempString[4] - 48;
            user->phoneNumber[4] = tempString[5] - 48;
            user->phoneNumber[5] = tempString[6] - 48;
            user->phoneNumber[6] = tempString[8] - 48;
            user->phoneNumber[7] = tempString[9] - 48;
            user->phoneNumber[8] = tempString[10] - 48;
            user->phoneNumber[9] = tempString[12] - 48;
            user->phoneNumber[10] = tempString[13] - 48;
            user->phoneNumber[11] = tempString[14] - 48;
            user->phoneNumber[12] = tempString[15] - 48;
        }

        if (numZero == 2) {
            user->phoneNumber[0] = 0;
            user->phoneNumber[1] = 0;
            user->phoneNumber[2] = tempString[1] - 48;
            user->phoneNumber[3] = tempString[3] - 48;
            user->phoneNumber[4] = tempString[4] - 48;
            user->phoneNumber[5] = tempString[5] - 48;
            user->phoneNumber[6] = tempString[7] - 48;
            user->phoneNumber[7] = tempString[8] - 48;
            user->phoneNumber[8] = tempString[9] - 48;
            user->phoneNumber[9] = tempString[11] - 48;
            user->phoneNumber[10] = tempString[12] - 48;
            user->phoneNumber[11] = tempString[13] - 48;
            user->phoneNumber[12] = tempString[14] - 48;
        }

        if (getUser(user->SIN) != NULL) {
            return false;
        }

        addUser(user);
        
    }


    //add their friends if they are there
    std::ifstream friendList(fileName.c_str());
    std::string theLine;
    std::string sSIN;
    unsigned int count = 0;

    while (getline(friendList, theLine)) {

        
        std::stringstream ss(theLine);

        getline(ss, tempString, ',');
        getline(ss, tempString, ',');
        getline(ss, tempString, ',');
        getline(ss, tempString, ',');
        getline(ss, tempString, ',');
        getline(ss, tempString, ',');
        getline(ss, tempString, ',');
        getline(ss, tempString, ',');
        getline(ss, tempString, ',');
        getline(ss, tempString, ',');
        getline(ss, tempString, ',');
        getline(ss, tempString, ',');
        getline(ss, tempString, ',');
        getline(ss, tempString, ',');
        getline(ss, sSIN, ',');
        getline(ss, tempString, ',');
        getline(ss, tempString, ',');
        

        cPerson* user = getUser(stoi(sSIN));

        while (tempString != "") {
            cPerson* theFriend = getUser(stoi(tempString));
            addFriend(user->SIN, theFriend->SIN, error);
            getline(ss, tempString, ',');
        }
    }

    return true;

}

//FOR THE FINAL
///////////////////////////////////////////////////////


cTicTacToeGameInstance cMugBook::createcTicTacToeGame(unsigned int Player_X_SIN, unsigned int Player_O_SIN,
  std::string& errorString) {

    //are the users in mugBook
    cPerson* checkX = getUser(Player_X_SIN);
    cPerson* checkO = getUser(Player_O_SIN);

    if (checkX == NULL) {
        Player_X_SIN = 0;
        Player_O_SIN = 0;
        errorString += "X PLAYER INVALID ";
    }

    if (checkO == NULL) {
        Player_X_SIN = 0;
        Player_O_SIN = 0;
        errorString += "O PLAYER INVALID ";
    }

    //are the users already in a game?
    for (unsigned int i = 0; i < this->m_vecGames.size(); i++) 

        if (this->m_vecGames[i].isGameCurrentlyRunning()) {

            if (checkX->SIN == m_vecGames[i].getPlayer_X_SIN() || checkX->SIN == m_vecGames[i].getPlayer_O_SIN()) {
                Player_X_SIN = 0;
                Player_O_SIN = 0;
                errorString += "X PLAYER ALREADY IN GAME ";
            }
        }
    }

    for (unsigned int i = 0; i < this->m_vecGames.size(); i++) {

        if (this->m_vecGames[i].isGameCurrentlyRunning()) {

            if (checkO->SIN == m_vecGames[i].getPlayer_X_SIN() || checkO->SIN == m_vecGames[i].getPlayer_O_SIN()) {
                Player_X_SIN = 0;
                Player_O_SIN = 0;
                errorString += "O PLAYER ALREADY IN GAME ";
            }
        }
    }

    //are they the same person
    if (checkO->SIN == checkX->SIN) {
        Player_X_SIN = 0;
        Player_O_SIN = 0;
        errorString += "PLAYER CANNOT PLAY THEMSELVES";
    }
   
    cTicTacToeGameInstance theGame = cTicTacToeGameInstance(Player_X_SIN, Player_O_SIN);

    

    this->m_vecGames.push_back(theGame);
    return theGame;

}

bool cMugBook::updateTicTacToeGame(cTicTacToeGameInstance theGame, std::string& errorString) {

    //locate game in mugBook
    for (int i = 0; i < this->m_vecGames.size(); i++) {

        //if game is found, update info
        if (this->m_vecGames[i].getUniqueGameID() == theGame.getUniqueGameID()) {
            this->m_vecGames[i].updateGameInList(theGame);
            return true;
        }
    }

    errorString = "Game not found in MugBook";

    return false;
}

unsigned int cMugBook::findANonPlayingTicTacToeUser(void) {

    //find a user to screen
    for (unsigned i = 0; i < this->m_vecUsers.size(); i++) {

        bool available = true;

        //see if they are in a game
        for (unsigned int j = 0; j < this->m_vecGames.size(); j++) {

            //are they in an active game
            if (this->m_vecGames[j].isGameCurrentlyRunning() && (this->m_vecGames[j].getPlayer_X_SIN() == this->m_vecUsers[i]->SIN ||
                   this->m_vecGames[j].getPlayer_O_SIN() == this->m_vecUsers[i]->SIN)) 
            {
                //in a game not available
                available = false;
                break;
            }
        }

        if (available) {
            return this->m_vecUsers[i]->SIN;
        }

    }
   
    //no available people 
    
    return 0;
}

unsigned int cMugBook::findAvailableTicTacToeOpponent(unsigned int OpponentPlayerSIN) {

    cPerson* pTemp = getUser(OpponentPlayerSIN); {

        if (pTemp == NULL) {
            return 0;
        }
    }

    //find a user to screen
    for (unsigned int i = 0; i < this->m_vecUsers.size(); i++) {

        bool available = true;

        //see if they are in a game
        for (unsigned int j = 0; j < this->m_vecGames.size(); j++) {

            //check if user's sin is in an active game
            if (this->m_vecGames[j].isGameCurrentlyRunning()
                && (this->m_vecGames[j].getPlayer_X_SIN() == this->m_vecUsers[i]->SIN ||
                    this->m_vecGames[j].getPlayer_O_SIN() == this->m_vecUsers[i]->SIN)) {
                available = false;
                break;
            }

        }

        //we got em
        if (available && this->m_vecUsers[i]->SIN != OpponentPlayerSIN) {
            return this->m_vecUsers[i]->SIN;
        }

    }
    //no one has the courage to challenge cPerson
    return 0;
}

unsigned int cMugBook::getNumberOfActiveTicTacToeGames(void) {

    unsigned int numGames = 0;

    for (unsigned int i = 0; i < this->m_vecGames.size(); i++) {

        if (this->m_vecGames[i].getPlayer_O_SIN() != 0 && this->m_vecGames[i].getPlayer_X_SIN() != 0) {

            if (this->m_vecGames[i].isGameCurrentlyRunning()) {
                numGames++;
            }
        }
    }

    return numGames;
}

unsigned int cMugBook::getNumberOfCompletedTicTacToeGames(void) {

    unsigned int numGames = 0;

    for (unsigned int i = 0; i < this->m_vecGames.size(); i++) {
        
        if (this->m_vecGames[i].getPlayer_O_SIN() != 0 && this->m_vecGames[i].getPlayer_X_SIN() != 0) {

            if (!this->m_vecGames[i].isGameCurrentlyRunning()) {
                numGames++;
            }
        }
    }

    return numGames;
}

unsigned int cMugBook::getTicTacToeGamesPlayed(unsigned int playerSIN) {

    unsigned int numGames = 0;

    for (unsigned int i = 0; i < this->m_vecGames.size(); i++) {
        
        if (this->m_vecGames[i].getPlayer_O_SIN() == playerSIN ||
            this->m_vecGames[i].getPlayer_X_SIN() == playerSIN) {
            numGames++;
        }
    }

    return numGames;
}

unsigned int cMugBook::getTotalTicTacToeWins(unsigned int playerSIN) {

    unsigned int numGames = 0;

    for (unsigned int i = 0; i < this->m_vecGames.size(); i++) {
        
        if (this->m_vecGames[i].getWinnerSIN() == playerSIN) {
            numGames++;
        }
    }
    return numGames;
}

unsigned int cMugBook::getTotalTicTacToeLoses(unsigned int playerSIN) {

    unsigned int numGames = 0;

    for (unsigned int i = 0; i < this->m_vecGames.size(); i++) {
        
        if ((this->m_vecGames[i].getPlayer_O_SIN() == playerSIN || this->m_vecGames[i].getPlayer_X_SIN() == playerSIN) 
            &&
            this->m_vecGames[i].getWinnerSIN() != playerSIN) {

            numGames++;
        }
    }
    return numGames;
}

//BONUS



bool cMugBook::getGamesPlayed(unsigned int playerSIN, std::vector< cTicTacToeGameInstance* >& vecGamesPlayed) {

    cPerson* test = getUser(playerSIN);

    if (test == NULL) {
        return false;
    }

    for (int i = 0; i < this->m_vecGames.size(); i++) {
        //check to see if player was in the game
        if ((this->m_vecGames[i].getPlayer_O_SIN() == playerSIN ||
            this->m_vecGames[i].getPlayer_X_SIN() == playerSIN) &&
            this->m_vecGames[i].isGameCurrentlyRunning() == false) {

            vecGamesPlayed.push_back(&this->m_vecGames[i]);
        }
    }

    return true;
}