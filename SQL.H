#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Main.hpp"
#include<iostream>
#include<vector>
#include <filesystem>
#include <fstream>
#include "ToolsCl.h"
#include "SQL/sqlite3.h"
// this is the Sql File 
//
namespace fs = std::filesystem;
static int *  callback ( void* list, int argc, char** argv, char** azColName) {
	std::vector<char> vec1;
	//vec1.clear();
	int i = 0;
	std::fstream filestream;
	filestream.open("TblRecords", std::ios::binary | std::ios::out);
	printf("%s = %s\n data", azColName[i], argv[i] ? argv[i] : "NULL");
	for (i = 0; i < argc; i++) {
		printf("%s = %s\n data", azColName[i], argv[i] ? argv[i] : "NULL");
		//std::cout << "\n argv[i],"<<argv[i];
		vec1.push_back(*argv[i]);
		if (filestream.is_open()) {
			//if TblRecords exists or opened then : 
			filestream.write(argv[i],sizeof(argv[i]));
		}
		
	}
	filestream.close(); 
	filestream.open("TblRecords", std::ios::binary | std::ios::in);
	std::string temp; 
	if (filestream.is_open()) {
		std::cout << "\n";
		while (std::getline(filestream, temp)) {
			std::cout << temp << "\t";
		}
		std::cout << "\n";
	}
	printf("\n");
	return 0;
}
// 
//
class SQLCL {
public:  
	//DEFAULT CONSTRUCTOR 
	SQLCL() {


	}
	std::string gettblname() {
		return dbname;
	}
	//THE PROCEDURE TO DISPLAY THE DATABASES IN THE FOLDER 
	void displayDB() {
		std::string dbfolder = "DATABASES/";
		for (int index = 0; const auto & file : fs::directory_iterator(dbfolder)) {
			std::cout << "[ " << file.path() << "] ";
			databases_list.push_back(file.path());
			index++;
			std::cout << std::endl;

		}

	}//ENDPROCEDURE 
	
	void Create_Table(std::string tblname ) {
		CheckDBExists();
		if (dbexists == false) {
			database = sqlite3_open(dbname.c_str(), &db);
			if (database) {
				fprintf(stderr, "[Can't open database:] %s\n", sqlite3_errmsg(db));

			}
			else {
				fprintf(stderr, "[Opened database successfully]\n");
			}
		}
		sql = "CREATE TABLE "+tblname+"(dte STRING, usr STRING, score INT, wvenum INT); ";
		database = sqlite3_exec(db, sql.c_str(), NULL, NULL, &errmsg);
		if (database != SQLITE_OK) {
			fprintf(stderr, "[SQL error:] %s\n", errmsg);
			sqlite3_free(errmsg);
		}
		else
		{
			std::cout<< "[Table by the name: ["+tblname+"] created successfully]\n";
		}
	}
	void add_DATA(std::string tblname,Gamestats GStats) {
		std::string query = "INSERT INTO "+tblname+" VALUES('"+GStats.date+"','"+GStats.usrname +"','"+GStats.scoreStr + "','" +GStats.wavenumStr +"');";
		database = sqlite3_exec(db, query.c_str(), NULL, NULL, &errmsg);
		if (database != SQLITE_OK) {
			fprintf(stderr, "[SQL error:] %s\n", errmsg);
			sqlite3_free(errmsg);
		}
		else {
			fprintf(stdout, "[Records created successfully]\n");
		}
	} // END PROCEDURE 
private:
	void CheckDBExists() {
		//this procedure is created with the future in mind, in the case
		// that there are more than one database; 
		//we need to dump everything inside the database folder 
		std::string dbfolder = "DATABASES/";
		std::vector< fs::path > dblist; 
		for ( const auto & file : fs::directory_iterator(dbfolder)) {
			std::cout << "[ " << file.path() << "] ";
			dblist.push_back(file.path());
			std::cout << std::endl;
		}
		// SETTING THE HIGHER BOUND AND LOWER BOUND VARS FOR 
		// dblist 
		int HB = dblist.size();
		int LB = -1;
		int mid = (HB + LB)/ 2; 
		//
		fs::path temp; 
		//now we need to sort the folder just in case 
		// I will use a simple bubble sort algorthim as the number of flashcards is not that great
		if (HB > 0) {
			printf("\n[PERFORMING BUBBLE SORT]\n", stdout);
			for (int i = 0; i < HB - 1; i++) {
				for (int x = 0; x < HB - (1 + i); x++) {
					std::cout << "Comparing: " << dblist[x] << "\t\t\t,with : " << dblist[x + 1] << "\n";
					if (dblist[x] > dblist[x + 1]) {
						temp = dblist[x];
						dblist[x] = dblist[x + 1];
						dblist[x + 1] = temp;
						std::cout << "switch: " << dblist[x] << "\t\t\t,with : " << dblist[x + 1] << "\n";
					}
				}
			}
			//now we need to search for our database 
			printf("\n[PERFORMING BINARY SEARCH FOR THE DATABASE]\n");
			while (LB < HB) {
				mid = (HB + LB) / 2;

				if (dblist[mid] == dbname) {
					std::cout << "[MIDPOINT : " << mid << ", Database:" << dblist[mid] << " ,HB" << HB << " ,LB" << LB << "]" << std::endl;
					dbexists = true; 
				}
				else if (dblist[mid] > dbname) {
					std::cout << "[MIDPOINT : " << mid << ", Database:" << dblist[mid] << " ,HB" << HB << " ,LB" << LB << "]" << std::endl;
					HB = mid - 1;
				}
				else {
					std::cout << "[MIDPOINT : " << mid << ", Database:" << dblist[mid] << " ,HB" << HB << " ,LB" << LB << "]" << std::endl;
					LB = mid + 1;
				}
			}
			
		}
	}
	//vars
	std::string sql; 
	 sqlite3* db;
	 std::vector< std::filesystem::path> databases_list;
	 bool dbexists = false; 
	 std::string dbname = "SCOREBOARD";
	 int database; 
	 char* errmsg = 0;
	 sqlite3_stmt* stmt;
};