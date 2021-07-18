// A classic type of header guard
#ifndef _cPerson_HG_2020_09_26_
#define _cPerson_HG_2020_09_26_

#include <string>
#include <vector>
#include "sDateYMD.h"

// Warning C26812 : Prefer 'enum class' over 'enum' (Enum.3)
#pragma warning( disable : 26812 )

class cPerson
{
public:
	cPerson();		// constructor (c'tor)
	~cPerson();		// destructor (d'tor)

	std::string first;
	std::string middle;
	std::string last;

	enum eGenderType
	{
		MALE = 0,		FEMALE,		NON_BINARY,
		RATHER_NOT_SAY_UNKNOWN
	};

	eGenderType gender;
	std::string getGenderAsString(void);

	sDateYMD birthDay;	// within valid ranges
	// This just returns the "years old" they are
	// i.e. You need to be 21 to rent a car, 19 to buy booze, etc.
	unsigned int getAge(sDateYMD todaysDate);

	int streetNumber;			// default = -1		(which is invalid)
	std::string streetName;		// default for these is blank (i.e. "")
	std::string streetType;	
	std::string streetDirection;
	std::string city;

	enum eProvinces
	{
		NUNAVUT = 20,						QUEBEC = 37,
		NORTHWEST_TERRITORIES  = 52,		ONTARIO = 190,
		BRITISH_COLUMBIA = 263,				ALBERTA = 329,
		SASKATCHEWAN = 418,					MANITOBA = 587,
		YUKON = 612,
		NEWFOUNDLAND_AND_LABRADOR = 719,
		NEW_BRUNSWICK = 765,				NOVA_SCOTIA = 852,
		PRINCE_EDWARD_ISLAND = 984
	};
	eProvinces province;
	// Returned in UPPERCASE : "ONTARIO", "NEW BRUNSWICK", etc.
	std::string getProvinceAsString(void);
	// Canadian postal codes in this format X0X 0X0
	// X = capitol letter, 0 = number (stored as alpha numeric, so '0', not 0
	char postalCode[7];		
	// Converts the postal code as a string (that can be printed with cout, etc.)
	// Should return with seven characters, letters upper case, with a space: "A1B 2C3"
	std::string getPostalCodeAsString(void);

	// Social insurance numbers are 9 digits
	unsigned int SIN;	// = 0		

	// Phone numbers [AAA] [BBB]-[CCC]-[DDDD]
	//  [AAA] is the country code (001 to 999)
	//  [BBB] is the area code (000 to 999)
	//  [CCC][DDDD] is the actual number.
	// The numbers are stored in "string order" like they'd be if they
	// 	were in a string, so the lowest number (least significant) is 
	//  at location 12, not 0, so 1-519-555-1234 would have the “4” phoneNumber[12].
	// Any leading zeros are stored, too. 
	// They are stored AS NUMBERS, not as ASCII-Unicode characters, 
	//  i.e. they are 0 to 9, not characters '0' to '9'
	unsigned char phoneNumber[13];
	// Should be in this format (with brackets, space and hyphens):
	// "(AAA) BBB-CCC-DDDD"
	// (Replace the ABCD values with the numbers indicated above)
	// Remove any leading zeros "(001)" should be "(1)" for example.
	// These are CHARACTERS not numbers (i.e. you should be able to print it)
	std::string getPhoneNumberAsString(void);

	std::vector<cPerson*> m_vecFriendsList;
private:
	

};

#endif
