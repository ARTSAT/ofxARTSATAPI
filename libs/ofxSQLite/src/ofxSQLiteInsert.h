/*
**      ofxSQLite addon
**
**      Original Copyright (C) 2010 - 2012 Diederick Huijbers.
**                                          http://www.roxlu.com/
**                                          info@roxlu.com
**
**      ofxSQLiteInsert.h
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

#ifndef OFXSQLITEINSERTH
#define OFXSQLITEINSERTH

#include "ofxSQLiteAbstract.h"
#include <vector>
#include "ofxSQLiteFieldValues.h"
#include <string>


class sqlite3;
class ofxSQLiteInsert {
	public:
		ofxSQLiteInsert(sqlite3* pSQLite, std::string sTable);
		std::string getLiteralQuery();
		ofxSQLiteFieldValues getFields();

		template<typename T>
		ofxSQLiteInsert& use(std::string sField, T sValue) {
			field_values.use(sField, sValue);
 			return *this;
		}
		int execute();

	private:
		std::string table;
		sqlite3* sqlite;
		int pair_count;
		ofxSQLiteFieldValues field_values;
};
#endif
