
#include "DBConnection.h"
DBConnection::DBConnection(std::string filename)
{
	sqlite3_initialize();

	db_url = filename;
	if (filename != "") {
		db_url = filename;
	}
	else {
		db_url = "example.db";
	}
	db = NULL;
	errMsg = "";
}

DBConnection::~DBConnection()
{
	db_url = "";
	db = NULL;
	errMsg = "";
	sqlite3_shutdown();
}

/* Establishing the connection to database */
int DBConnection::Connect()
{
	int rc = SQLITE_EMPTY;

	try {
		rc = sqlite3_open(db_url.c_str(), &db);
		errMsg = sqlite3_errmsg(GetDatabase());    //  gets text that describes the error

		return rc;
	}
	catch (...) {
		rc = SQLITE_CANTOPEN;
	}

	return rc;
}

/* Disconnects from a database */
int DBConnection::Disconnect()
{
	int rc = SQLITE_EMPTY;

	try {
		rc = sqlite3_close(db);
		errMsg = sqlite3_errmsg(GetDatabase());    //  gets text that describes the error
	}
	catch (...) {
		rc = SQLITE_ERROR;
	}

	return rc;
}

sqlite3 * DBConnection::GetDatabase()
{
	return db;
}

std::string DBConnection::DB_Url()
{
	return db_url;
}
