/*
**      ofxSQLite addon
**
**      Original Copyright (C) 2010 - 2012 Diederick Huijbers.
**                                          http://www.roxlu.com/
**                                          info@roxlu.com
**
**      ofxSQLiteUpdate.h
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

#ifndef OFXSQLITEUPDATEH
#define OFXSQLITEUPDATEH

#include <vector>
#include <string>
#include "ofxSQLiteWhere.h"
#include "ofxSQLiteFieldValues.h"

class ofxSQLiteFieldValues;
class sqlite3;

class ofxSQLiteUpdate {
	public:
		ofxSQLiteUpdate(sqlite3*  pSQLite, std::string sTable);

		template<typename T>
		ofxSQLiteUpdate& use(std::string sField, T sValue) {
			field_values.use(sField, sValue);
 			return *this;
		}

		std::string getLiteralQuery();
		int execute();

		// where clause..
		template<typename T>
		ofxSQLiteUpdate& where(std::string sField, T mValue) {
			return where(sField, mValue, WHERE);
		}
		template<typename T>
		ofxSQLiteUpdate& orWhere(std::string sField, T mValue) {
			return where(sField, mValue, WHERE_OR);
		}
		template<typename T>
		ofxSQLiteUpdate& andWhere(std::string sField, T mValue) {
			return where(sField, mValue, WHERE_AND);
		}
		template<typename T>
		ofxSQLiteUpdate& where(std::string sField, T mValue, int nType) {
			wheres.where(sField, mValue, nType);
			return *this;
		}

	private:
		std::string table;
		ofxSQLiteWhere wheres;
		ofxSQLiteFieldValues field_values;
		sqlite3* sqlite;
};
#endif
