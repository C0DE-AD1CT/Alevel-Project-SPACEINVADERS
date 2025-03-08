#pragma
#include "Arcade.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Main.hpp"
#include<iostream>
#include<vector>
#include <SQL.H>
#include "ToolsCl.h"




//Constant vars 
#define ROW_HEIGHT  50 ; 
#define ROW_WIDTH   250; 
#define LEFTWALLPADX  100; 
#define COLTHICKNESS 3 ; 
#define ROWTHICKNESS 4; 
#define ROWPADDING   25;
// THIS WAS DONE TO CUT TIME 
// IN THE FUTURE THIS WILL NEED TO BE REMOVED AS THIS LEADS TO LINEAR DECISION MAKING . 
#define DATABASENAME "SCOREBOARD"
#define TABLE "SCOREBOARD"
//
// This holds the types of the table in question 
//contains three sub structures : Text_tbl, columnF , Row,F
struct tblTYPES {
	
	struct TEXT_TBL
	{
	private:
		struct TEXT {
			std::string typtext; int txtSize;sf::Color txtColor; bool bold = false;
			bool underlined = false;std::string textX; 
		};
	public: 
		TEXT F; 
	
	};
	struct COLUMNF
		//column info
	{int height = ROW_HEIGHT;int BorderThck = COLTHICKNESS;
		sf::Color border_colour;sf::Color fill_colour;};
	struct ROWF
		//ROW information 
	{int height = ROW_HEIGHT;int width = ROW_WIDTH;
		int InternalPad = ROWPADDING;int BorderThck = ROWTHICKNESS;
		sf::Color border_colour;sf::Color fill_colour;};
	struct DBVARS {
		// holds SQL  // database , table name , the error catcher and other sqlite 3 constants vars 
		sqlite3* db;std::string DB_NAME = DATABASENAME;	std::string TABLE_NAME = TABLE;	char* errmsg = 0;
		int database;std::string SQL;

	};

	struct Layout{ private: 
		struct RowsT {	int RowID;int RowIndex;std::vector<std::string> value;};
		struct columnsT{int fieldPosition;std::vector<std::string> fields;};
	public:	
		std::vector<RowsT> rows;std::vector<columnsT> fields;};
};
//The table frame structure 
//important in its visual construction 
struct tblFrm
{

	tblTYPES::ROWF ROWFR;// defines a placeholder for RowF struct inside table types structure
	tblTYPES::COLUMNF COLFR; // The following show similar form 
	tblTYPES::Layout TBL_LAYOUT;
	tblTYPES::DBVARS TBL_DB_FR;
	std::vector<tblTYPES::TEXT_TBL> TXT_VEC;// creates a vector of tbltypes of text_tables 
	int MAX_ROW = 10;// Max row Num 
	int MAX_COL = 4;// Max col Num 
};
// 
class Table {
public:
	Table() {

	}
	//opening database
	void open_DB() {
		// opens database
		TABLEFRAME.TBL_DB_FR.database = sqlite3_open(TABLEFRAME.TBL_DB_FR.DB_NAME.c_str(),&TABLEFRAME.TBL_DB_FR.db);
		if (TABLEFRAME.TBL_DB_FR.database) {
			fprintf(stderr, "\n[Can't open database:] %s\n", sqlite3_errmsg(TABLEFRAME.TBL_DB_FR.db));}
		else {
			fprintf(stderr, "\n[Opened database successfully]\n");
		}
		
	}
	const char*  read_record(std::string fieldX) {
		//Purpose: to read the database line at atime
		const char* data = " ";
		TABLEFRAME.TBL_DB_FR.SQL = "SELECT "+fieldX+" FROM " + TABLEFRAME.TBL_DB_FR.TABLE_NAME + ";";
		TABLEFRAME.TBL_DB_FR.database = sqlite3_exec( TABLEFRAME.TBL_DB_FR.db,TABLEFRAME.TBL_DB_FR.SQL.c_str(),  **callback, (void*)data, &TABLEFRAME.TBL_DB_FR.errmsg);
		if (TABLEFRAME.TBL_DB_FR.database != SQLITE_OK) {
			printf("\n[ERROR READING THE DATABASE]\n");
			return data; 
		}
		else {
			printf("\n[Success READING THE DATABASE]\n");
			return data; 
		}
		
	}
	//reading database 
	// sorting database 
	//drawing table: 
	void draw_Table(sf::RenderWindow& window) {
		// draws table by retrieving our setup vars 
		open_DB();
		std::string Arr_fieldX[4] = { "dte","usr" ,"score" ,"wvenum"};
		const char* dataX = "";
		for (std::string FIELDX : Arr_fieldX) {
			dataX = read_record(FIELDX);
		}
		yo = 50;
		xo = 50 + LEFTWALLPADX;
		int rowPos[2] = { xo ,yo };
		int rowSize[2] = { TABLEFRAME.ROWFR.width , TABLEFRAME.ROWFR.height };
		for (int field = 0; field < TABLEFRAME.MAX_COL; field++) {
			
			for (int row = 0; row < TABLEFRAME.MAX_ROW; row++) {
				if (row == 0) {
					rowPos[1] = yo;
					int rowPosStr[2];
					rowPosStr[0] = xo;
					rowPosStr[1] = yo - ROWPADDING;
					yo = calc_nextrow_Y(yo);
					
					tools::DrawRect R1(&window, rowSize, rowPos, sf::Color::Blue, sf::Color::Green, 2);
					tools::DrawText t2(window, rowPosStr, 30, Arr_fieldX[field], sf::Color::White, sf::Color::Green, true);
					
				}
				else {
					rowPos[1] = yo;
					int rowPosStr[2];
					rowPosStr[0] = xo;
					rowPosStr[1] = yo - ROWPADDING;
					yo = calc_nextrow_Y(yo);
					tools::DrawRect R2(&window, rowSize, rowPos, sf::Color::Black, sf::Color::Yellow, 2);
					tools::DrawText t2(window, rowPosStr, 30, std::to_string(dataX[field]), sf::Color::White, sf::Color::Green, true);
				}
			}
			xo = calc_nextrow_X(xo);
			rowPos[0] = xo;
			yo = 50;
		}
	}

private:
	int calc_nextrow_Y(int Y) {
		int YN = Y + ROW_HEIGHT; 
		return YN;
	}
	int calc_nextrow_X(int X) {
		int XN = X + ROW_WIDTH;
		return XN;
	}
	int xo ; 
	int yo ; 
	tblFrm TABLEFRAME;
	Gamestats GSTAT; 
};