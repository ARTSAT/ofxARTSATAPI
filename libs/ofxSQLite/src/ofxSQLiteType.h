/*
**      ofxSQLite addon
**
**      Original Copyright (C) 2010 - 2012 Diederick Huijbers.
**                                          http://www.roxlu.com/
**                                          info@roxlu.com
**
**      ofxSQLiteType.h
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

#ifndef OFXSQLITETYPEH
#define OFXSQLITETYPEH
#include <string>

enum {
 	 OFX_SQLITE_TYPE_INT
	,OFX_SQLITE_TYPE_DOUBLE
	,OFX_SQLITE_TYPE_LONG
	,OFX_SQLITE_TYPE_INT64
	,OFX_SQLITE_TYPE_TEXT
	,OFX_SQLITE_TYPE_NULL
};

class ofxSQLiteType {
public:
	virtual std::string getString()		{	return	"";		}
	virtual int getInt()				{ 	return	0;		}	
	virtual long getLong()				{ 	return	0;		}
	virtual uint64_t getUint64()		{	return  0;		}
	virtual int getType() = 0;
};
#endif
