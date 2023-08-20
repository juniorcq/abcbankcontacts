// abcbankcontactscrow.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "crow_all.h"
#include "Contact.h"
#include "DBConnection.h"
#include "DBController.h"


int main()
{

	crow::SimpleApp app; //define your crow application

						 ///////////////////////  GETS  ////////////////////////////////////////////////
	CROW_ROUTE(app, "/")([]() {
		return "Type url to get info";
	});

	/////////////////CONTACT'S GETS//////////////////////////
	CROW_ROUTE(app, "/contacts")([]() {
		Contact* contact = new Contact();
		DBController* dbController = new DBController("example.db");
		std::vector<Contact*>* contacts = dbController->GetContacts();

		if (contacts->size() <= 0)
		{
			crow::json::wvalue x({ { "message", "There are not contacts!" } });
			return x;
		}

		crow::json::wvalue x =
		{

		};

		for (int i = 0; i < contacts->size(); i++)
		{

			x["Contact " + std::to_string(i + 1)] =
			{
				{ "Id: " ,contacts->at(i)->GetId() },
				{ "First Name: " ,contacts->at(i)->GetFirstName() },
				{ "Second Name: " ,contacts->at(i)->GetSecondName() },
				{ "Birthday: " ,contacts->at(i)->GetBirthday() },
				{ "Personal Photo: " ,contacts->at(i)->GetPersonalPhotoUrl() }
			};

		}
		return x;
	});

	//Get Contact by Contact id
	CROW_ROUTE(app, "/contactbyid/<string>")([](std::string id) {

		DBController* dbController = new DBController("example.db");
		int contact_id = dbController->IsIntegerBiggerThanCero(id);


		if (contact_id < 0)
		{
			crow::json::wvalue x({ { "message", "You must enter a valid id number!" } });
			return x;
		}

		Contact* contact = new Contact();

		contact = dbController->GetContactWithId(contact_id);

		if (contact)
		{
			crow::json::wvalue x =
			{
				{ "Id", contact->GetId() },
				{ "First Name", contact->GetFirstName() },
				{ "Second Name", contact->GetSecondName() },
				{ "Birthday", contact->GetBirthday() },
				{ "Personal Photo", contact->GetPersonalPhotoUrl() }
			};
			return x;
		}

		crow::json::wvalue x({ { "message", "There is not contact with that id!" } });
		return x;

	});

	//Get contact's phones by contact id
	CROW_ROUTE(app, "/contactbyidphones/<string>")([](std::string id) {

		DBController* dbController = new DBController("example.db");
		int contact_id = dbController->IsIntegerBiggerThanCero(id);

		if (contact_id < 0)
		{
			crow::json::wvalue x({ { "message", "You must enter a valid id number!" } });
			return x;
		}

		std::vector<Phone*>* phones = dbController->GetContactPhones(contact_id);

		if (phones->size() <= 0)
		{
			crow::json::wvalue x({ { "message", "Contacts with no phones registered!" } });
			return x;
		}

		crow::json::wvalue x =
		{

		};

		for (int i = 0; i < phones->size(); i++)
		{
			x["Phones "][i] =
			{
				{ "Phone Id: " ,phones->at(i)->GetId() },
				{ "Phone " + std::to_string(i) ,phones->at(i)->GetPhone() }
			};
		}

		return x;

	});

	//Get contact's address by contact id
	CROW_ROUTE(app, "/contactaddressbycontactid/<string>")([](std::string id) {

		DBController* dbController = new DBController("example.db");
		int contact_id = dbController->IsIntegerBiggerThanCero(id);

		if (contact_id < 0)
		{
			crow::json::wvalue x({ { "message", "You must enter a valid id number!" } });
			return x;
		}

		std::vector<Address*>* address = dbController->GetContactAddress(contact_id);

		if (address->size() <= 0)
		{
			crow::json::wvalue x({ { "message", "Contacts with no address registered!" } });
			return x;
		}

		crow::json::wvalue x =
		{

		};

		for (int i = 0; i < address->size(); i++)
		{
			x["Address "][i] =
			{
				{ "Address Id: " ,address->at(i)->GetId() },
				{ "Description " + std::to_string(i) ,address->at(i)->GetAddress() }
			};
		}

		return x;

	});

	//Get contacts in range of age
	CROW_ROUTE(app, "/contactbyidrangeofage/<string>/<string>")([](std::string age_from, std::string age_to) {

		DBController* dbController = new DBController("example.db");
		int from = dbController->IsIntegerBiggerThanCero(age_from);
		int to = dbController->IsIntegerBiggerThanCero(age_to);

		if (from < 0 || to < 0)
		{
			crow::json::wvalue x({ { "message", "You must enter a valid age number!" } });

			return x;
		}

		std::vector<Contact*>* contacts = dbController->GetContactWithAgeInRange(from, to);

		if (contacts->size() <= 0)
		{
			crow::json::wvalue x({ { "message", "There are not contacts in that range of age!" } });
			return x;
		}

		crow::json::wvalue x =
		{

		};

		for (int i = 0; i < contacts->size(); i++)
		{

			x["Contact " + std::to_string(i + 1)] =
			{
				{ "Id: " ,contacts->at(i)->GetId() },
				{ "First Name: " ,contacts->at(i)->GetFirstName() },
				{ "Second Name: " ,contacts->at(i)->GetSecondName() },
				{ "Birthday: " ,contacts->at(i)->GetBirthday() },
				{ "Personal Photo: " ,contacts->at(i)->GetPersonalPhotoUrl() }
			};

		}
		return x;

	});

	//Get Contacts who lives in address_id
	CROW_ROUTE(app, "/contactslivesin/<string>")([](std::string address_id) {

		DBController* dbController = new DBController("example.db");
		int id = dbController->IsIntegerBiggerThanCero(address_id);

		if (id < 0)
		{
			crow::json::wvalue x({ { "message", "You must enter a valid id number!" } });
			return x;
		}

		std::vector<Contact*>* contacts = dbController->GetContactsWhoLiveIn(id);

		if (contacts->size() <= 0)
		{
			crow::json::wvalue x({ { "message", "There are not contacts who lives in address with that address id!" } });
			return x;
		}

		crow::json::wvalue x =
		{

		};

		for (int i = 0; i < contacts->size(); i++)
		{

			x["Contact " + std::to_string(i + 1)] =
			{
				{ "Id: " ,contacts->at(i)->GetId() },
				{ "First Name: " ,contacts->at(i)->GetFirstName() },
				{ "Second Name: " ,contacts->at(i)->GetSecondName() },
				{ "Birthday: " ,contacts->at(i)->GetBirthday() },
				{ "Personal Photo: " ,contacts->at(i)->GetPersonalPhotoUrl() }
			};

		}

		return x;

	});

	//GetContactWithAddressLike
	CROW_ROUTE(app, "/addreslike/<string>/<string>")([](std::string firstname, std::string addreslike) {

		DBController* dbController = new DBController("example.db");
		std::vector<AddresLike*>* data = dbController->GetContactWithAddressLike(firstname, addreslike);

		if (data->size() <= 0)
		{

			crow::json::wvalue x({ { "message", "There are no contacts with that firstname and address like that!" } });
			return x;
		}

		crow::json::wvalue x =
		{

		};

		for (int i = 0; i < data->size(); i++)
		{

			x["Address Like " + std::to_string(i + 1)] =
			{

				{ "Contact Id: " ,data->at(i)->contact_id },
				{ "First Name: " ,data->at(i)->firstName },
				{ "Second Name: " ,data->at(i)->secondName },
				{ "Birthday: " ,data->at(i)->birthday },
				{ "Personal Photo: " ,data->at(i)->photo },
				{ "Address id: " ,data->at(i)->address_id },
				{ "Address Description: " ,data->at(i)->address_description }

			};

		}

		return x;

	});


	/////////////////INSERT//////////////////////////

	//void InsertAddress(std::string description);
	CROW_ROUTE(app, "/insertaddress/<string>")([](std::string description) {

		DBController* dbController = new DBController("example.db");

		int rc = dbController->InsertAddress(description);

		crow::json::wvalue x =
		{

		};

		if (rc == SQLITE_OK)
		{
			crow::json::wvalue x({ { "message", "Address was inserted!" } });
			return x;
		}
		else
		{
			crow::json::wvalue x({ { "message", "Address was not inserted!" } });
			return x;
		}

	});

	// void AddPhoneToContact(int contact_id,std::string phone);
	CROW_ROUTE(app, "/addphonetocontact/<string>/<string>")([](std::string contact_id, std::string phone) {


		DBController* dbController = new DBController("example.db");
		int contactid = dbController->IsIntegerBiggerThanCero(contact_id);

		if (contactid < 0)
		{
			crow::json::wvalue x({ { "message", "You must enter a valid contact id number!" } });
			return x;
		}

		int rc = dbController->AddPhoneToContact(contactid, phone);

		if (rc == SQLITE_OK)
		{
			crow::json::wvalue x({ { "message", "Phone was  added!" } });
			return x;
		}
		else
		{
			crow::json::wvalue x({ { "message", "Verify data!" } });
			return x;

		}

	});

	// int InsertContact(std::string firstName, std::string secondName, std::string birthday, std::string personalPhotoURL);
	CROW_ROUTE(app, "/insertcontact/<string>/<string>/<string>/<string>")([](std::string firstName, std::string secondName, std::string birthday, std::string personalPhotoURL) {

		if (firstName == "" || secondName == "")
		{
			crow::json::wvalue x({ { "message", "Contact was not inserted, verify data!" } });
			return x;
		}

		//Verify photo url exist
		//Verify birthday pattern

		DBController* dbController = new DBController("example.db");


		int rc = dbController->InsertContact(firstName, secondName, birthday, personalPhotoURL);

		if (rc == SQLITE_OK)
		{
			crow::json::wvalue x({ { "message", "Contact was inserted!" } });
			return x;
		}
		else
		{
			crow::json::wvalue x({ { "message", "Contact was not inserted, verify!" } });
			return x;
		}

	});

	// int AddAddressToContact(int contact_id, int address_id);
	CROW_ROUTE(app, "/addaddresstocontact/<string>/<string>")([](std::string contact_id, std::string address_id) {

		DBController* dbController = new DBController("example.db");
		int contactid = dbController->IsIntegerBiggerThanCero(contact_id);
		int addressid = dbController->IsIntegerBiggerThanCero(address_id);

		if (contactid <= 0 || addressid <= 0)
		{
			crow::json::wvalue x({ { "message", "You must enter a valid id number!" } });
			return x;
		}

		int rc = SQLITE_EMPTY;

		rc = dbController->AddAddressToContact(contactid, addressid);

		if (rc == SQLITE_OK)
		{
			crow::json::wvalue x({ { "message", "Address was added to contatct!" } });
			return x;
		}
		else
		{
			crow::json::wvalue x({ { "message", "Address was not added to contatct!" } });
			return x;
		}



	});


	/////////////////CONTACT'S UPDATE//////////////////////////

	//  update contact (int contact_id, int address_id);
	CROW_ROUTE(app, "/updatecontact/<string>/<string>/<string>/<string>/<string>")([](std::string contact_id, std::string firstName, std::string secondName, std::string birthday, std::string personalPhotoURL) {

		DBController* dbController = new DBController("example.db");
		int contactid = dbController->IsIntegerBiggerThanCero(contact_id);

		if (contactid <= 0)
		{
			crow::json::wvalue x({ { "message", "You must enter a valid contact id number!" } });
			return x;
		}

		int rc = SQLITE_EMPTY;

		//Verify birthday format
		//Verify photo url

		rc = dbController->UpdateContact(contactid, firstName, secondName, birthday, personalPhotoURL);

		if (rc == SQLITE_OK)
		{
			crow::json::wvalue x({ { "message", "Contact was updated !" } });
			return x;
		}
		else
		{
			crow::json::wvalue x({ { "message", "Contact was not updated!" } });
			return x;
		}


	});


	/////////////////DELETE//////////////////////////

	//Delete Contact by Contact id
	CROW_ROUTE(app, "/deletecontact/<string>")([](std::string id) {

		DBController* dbController = new DBController("example.db");
		int contact_id = dbController->IsIntegerBiggerThanCero(id);

		if (contact_id <= 0)
		{
			crow::json::wvalue x({ { "message", "You must enter a valid id number!" } });
			return x;
		}

		int rc = dbController->DeleteContactById(contact_id);


		if (rc == SQLITE_OK)
		{
			crow::json::wvalue x({ { "Contact with id successful deleted", id } });
			return x;
		}
		else
		{
			crow::json::wvalue x({ { "Contact with id was not deleted", id } });
			return x;
		}

	});

	//Delete Address from Contact by Contact id
	CROW_ROUTE(app, "/deleteaddressfromContact/<string>/<string>")([](std::string contact_id, std::string address_id) {

		DBController* dbController = new DBController("example.db");
		int contactid = dbController->IsIntegerBiggerThanCero(contact_id);
		int addressid = dbController->IsIntegerBiggerThanCero(address_id);


		if (contactid <= 0 || addressid <= 0)
		{
			crow::json::wvalue x({ { "message", "You must enter a valid id number!" } });
			return x;
		}

		int rc = dbController->DeleteAddressFromContact(contactid, addressid);


		if (rc == SQLITE_OK)
		{
			crow::json::wvalue x({ { "Address with id successful deleted from contact", address_id } });
			return x;
		}
		else
		{
			crow::json::wvalue x({ { "Address with id was not deleted from contact", address_id } });
			return x;
		}

	});


	//Delete Phone from Contact by Contact id and Phone id
	CROW_ROUTE(app, "/deletephonefromcontact/<string>/<string>")([](std::string contact_id, std::string phone_id) {


		DBController* dbController = new DBController("example.db");
		int contactid = dbController->IsIntegerBiggerThanCero(contact_id);
		int phoneid = dbController->IsIntegerBiggerThanCero(phone_id);

		if (contactid <= 0 || phoneid <= 0)
		{
			crow::json::wvalue x({ { "message", "You must enter a valid id number!" } });
			return x;
		}

		int rc = dbController->DeletePhoneFromContact(contactid, phoneid);


		if (rc == SQLITE_OK)
		{
			crow::json::wvalue x({ { "Phone with id successful deleted from contact", phone_id } });
			return x;
		}
		else
		{
			crow::json::wvalue x({ { "Phone with id was not deleted from contact", phone_id } });
			return x;
		}

	});


	//set the port, set the app to run on multiple threads, and run the app
	app.port(18080).multithreaded().run();


	return 0;
}
