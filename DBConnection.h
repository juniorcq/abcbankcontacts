
#ifndef ABCBANKCONTACT_DBCONNECTION_H
#define ABCBANKCONTACT_DBCONNECTION_H

#include <iostream>
#include<string.h>
#include "sqlite3.h"
#include <stdio.h>



class DBConnection {

private:
	// Pointer to SQLite connection
	sqlite3 *db;

	// Database url'
	std::string db_url;

	// Save any error messages
	std::string errMsg;

	// Save the result of opening the file
	int rc;

public:
	DBConnection(std::string db_filename = "");
	~DBConnection();
	int Connect();
	int Disconnect();
	sqlite3* GetDatabase();
	std::string DB_Url();

};


#endif //ABCBANKCONTACT_DBCONNECTION_H
