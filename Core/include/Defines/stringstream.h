#ifndef _STRINGSTREAM_H
#define _STRINGSTREAM_H

//C Runtime Header Files
//----------------------
#ifndef _SSTREAM_
	#include <sstream>
#endif

//Defines
//-------
#ifdef UNICODE
#define tstringstream wstringstream
#else
#define tstringstream stringstream
#endif

#endif //_STRINGSTREAM_H