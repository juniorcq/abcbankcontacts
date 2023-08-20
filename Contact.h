//
#ifndef ABCBANKCONTACT_CONTACT_H
#define ABCBANKCONTACT_CONTACT_H
#include <iostream>
#include <vector>
#include "Address.h"
#include "Phone.h"

class Contact {
private:
	int id;
protected:
	std::string firstName;
	std::string secondName;
	std::string birthday;
	std::string personalPhotoUrl;
	//vector<Address*>* addresses;
	// vector<Phone*>* phones;

public:

	Contact();
	Contact(std::string firstName, std::string secondName, std::string birthday, std::string personalPhotoUrl);
	~Contact();

	int GetId();
	std::string GetFirstName();
	std::string GetSecondName();
	std::string GetBirthday();
	std::string GetPersonalPhotoUrl();


	void SetId(int id);
	void SetFirstName(std::string firstName);
	void SetSecondName(std::string secondName);
	void SetBirthday(std::string birthday);
	void SetPersonalPhotoUrl(std::string personalPhotoUrl);




};


#endif //ABCBANKCONTACT_CONTACT_H
