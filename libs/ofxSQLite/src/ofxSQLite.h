/*
**      ofxSQLite addon
**
**      Original Copyright (C) 2010 - 2012 Diederick Huijbers.
**                                          http://www.roxlu.com/
**                                          info@roxlu.com
**
**      ofxSQLite.h
**
**      ------------------------------------------------------------------------
**
**      The MIT License (MIT)
**
**      Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
**      associated documentation files (the "Software"), to deal in the Software without restriction,
**      including without limitation the rights to use, copy, modify, merge, publish, distribute,
**      sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
**      furnished to do so, subject to the following conditions:
**      The above copyright notice and this permission notice shall be included in all copies or
**      substantial portions of the Software.
**      THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
**      BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
**      IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
**      WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
**      OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * When compiling the sqlite.c file I needed to put:
 * SQLITE_ENABLE_UPDATE_DELETE_LIMIT=1
 * in the build options.
 *
 * Or you can use a build define like: SQLITE_DEBUG 0
 *
 */
#ifndef OFXSQLITEH
#define OFXSQLITEH
#define DSQLITE_ENABLE_UPDATE_DELETE_LIMIT 1

#include <vector>
#include <string>
#include "lib/sqlite/sqlite3.h"
//#include "ofMain.h"

#include "ofxSQLiteTypeNow.h"

//
//#include "ofxSQLite.h"
#include "ofxSQLiteAbstract.h"
#include "ofxSQLiteInsert.h"
#include "ofxSQLiteUpdate.h"
#include "ofxSQLiteDelete.h"
#include "ofxSQLiteSelect.h"
#include "ofxSQLiteType.h"
#include "ofxSQLiteTypeNow.h"
//#include "ofxSQLiteSimpler.h"
class ofxSQLiteSimpler;
//
/*
class ofxSQLiteInsert;
class ofxSQLiteSelect;
class ofxSQLiteUpdate;
class ofxSQLiteDelete;
*/
class ofxSQLite {
	public:
		ofxSQLite();
		ofxSQLite(std::string sDB);
		void setup(std::string sDB);
		ofxSQLiteInsert insert(std::string sTable);
		ofxSQLiteUpdate update(std::string sTable);
		ofxSQLiteDelete remove(std::string sTable);
		ofxSQLiteSelect select(std::string sFields);
		void printTable(std::string sTable);
		
		ofxSQLiteSimpler operator[](const std::string sKeyValue);
		
		int lastInsertID();
		const char* getError();

		int simpleQuery(const char* pSQL);
		inline ofxSQLiteTypeNow now() {
			return ofxSQLiteTypeNow();
		}
		
		inline sqlite3* getSQLitePtr();		

	private:
		sqlite3* db;
		std::string db_name;
		std::string db_file;
};

inline sqlite3* ofxSQLite::getSQLitePtr() {
	return db;
}

class ofxSQLiteSimpler {
public:
	ofxSQLiteSimpler(ofxSQLite& rDB, string sTable)
	:db(rDB)
	,table(sTable)
	{
	}
	
	template<typename T>
	ofxSQLiteSelect find(string sWhereField, T mWhereValue, string sSelectFields = "*") {
		ofxSQLiteSelect sel = db.select(sSelectFields).from(table).where(sWhereField, mWhereValue).execute();
		return sel;
	}
	
	// example: db["pakbox_users"].findOne("pu_id", 68, "pu_name").getString(0);
	template<typename T>
	ofxSQLiteSelect findOne(string sWhereField, T mWhereValue, string sSelectFields = "*") {
		ofxSQLiteSelect sel = db
			.select(sSelectFields)
			.from(table)
			.where(sWhereField, mWhereValue)
			.limit(1)
			.execute()
			.begin();
		
		return sel;
	}
	
	void print(){
		cout << db.select("*").from(table).execute().getResultAsAsciiTable();
	}
	
private:
	ofxSQLite& db;
	string table;

};

#endif

