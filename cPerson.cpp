#include "cPerson.h"

// Warning C26812 : Prefer 'enum class' over 'enum' (Enum.3)
#pragma warning( disable : 26812 )

cPerson::cPerson()
{
	// In here, set the default information
	this->gender = cPerson::RATHER_NOT_SAY_UNKNOWN;
	this->streetNumber = -1;
//	this->age = -1;
	this->SIN = 0;
	// Clears the postal code with all zeros.
	memset( this->postalCode, 0, 7 );
}


cPerson::~cPerson()
{
	// Does nothing in this case
}

std::string cPerson::getGenderAsString(void)
{
	switch (this->gender)
	{
	case cPerson::MALE:
		return "MALE";
		break;
	case cPerson::FEMALE:
		return "FEMALE";
		break;
	case cPerson::NON_BINARY:
		return "NON_BINARY";
		break;
	case cPerson::RATHER_NOT_SAY_UNKNOWN:
		return "RATHER_NOT_SAY_UNKNOWN";
		break;
//	default:
//		break;
	}

	// This "should never" happen, but could since the enum is really an integer
	return "OMG! CALL THE DEV TEAM!! SOMEONE SCREWED UP!!!";
}

unsigned int cPerson::getAge(sDateYMD todaysDate) {

	

	int age = todaysDate.year - this->birthDay.year;

	if (todaysDate.month < this->birthDay.month) {
		age--;
	}
	else if (todaysDate.month == this->birthDay.month) {

		if (todaysDate.day < this->birthDay.day) {
			age--;
		}
	}

	
	return age;

}

std::string cPerson::getProvinceAsString(void) {

	switch (this->province)
	{
	case cPerson::NUNAVUT:
		return "NUNAVUT";
		break;
	case cPerson::NORTHWEST_TERRITORIES:
		return "NORTHWEST TERRITORIES";
		break;
	case cPerson::BRITISH_COLUMBIA:
		return "BRITISH COLUMBIA";
		break;
	case cPerson::SASKATCHEWAN:
		return "SASKATCHEWAN";
		break;
	case cPerson::YUKON:
		return "YUKON";
		break;
	case cPerson::NEWFOUNDLAND_AND_LABRADOR:
		return "NEWFOUNDLAND AND LABRADOR";
		break;
	case cPerson::NEW_BRUNSWICK:
		return "NEW BRUNSWICK";
		break;
	case cPerson::PRINCE_EDWARD_ISLAND:
		return "PRINCE EDWARD ISLAND";
		break;
	case cPerson::QUEBEC:
		return "QUEBEC";
		break;
	case cPerson::ONTARIO:
		return "ONTARIO";
		break;
	case cPerson::ALBERTA:
		return "ALBERTA";
		break;
	case cPerson::MANITOBA:
		return "MANITOBA";
		break;
	case cPerson::NOVA_SCOTIA:
		return "NOVA SCOTIA";
		break;

	}

	return "province as string error";
}

std::string cPerson::getPostalCodeAsString(void) {

	std::string postalC = "";

	for (unsigned int i = 0; i < 7; i++) {
		postalC += toupper(this->postalCode[i]);
	}
	return postalC;
}


std::string cPerson::getPhoneNumberAsString(void) {

	std::string phoneN = "";
	phoneN += "(";

	if (this->phoneNumber[0] != 0) {
		phoneN += this->phoneNumber[0] + 48;
	}

	if (this->phoneNumber[0] == 0 && this->phoneNumber[1] != 0) {
		phoneN += this->phoneNumber[1] + 48;
	}
	if (this->phoneNumber[0] != 0) {
		phoneN += this->phoneNumber[1] + 48;
	}



	phoneN += this->phoneNumber[2] + 48;


	//101

	phoneN += ")";

	phoneN += this->phoneNumber[3] + 48;
	phoneN += this->phoneNumber[4] + 48;
	phoneN += this->phoneNumber[5] + 48;
	phoneN += "-";

	phoneN += this->phoneNumber[6] + 48;
	phoneN += this->phoneNumber[7] + 48;
	phoneN += this->phoneNumber[8] + 48;
	phoneN += "-";

	phoneN += this->phoneNumber[9] + 48;
	phoneN += this->phoneNumber[10] + 48;
	phoneN += this->phoneNumber[11] + 48;
	phoneN += this->phoneNumber[12] + 48;
	return phoneN;
}