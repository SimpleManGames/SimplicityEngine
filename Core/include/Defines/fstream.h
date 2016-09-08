#ifndef _FSTREAM_H
#define _FSTREAM_H

//C Runtime Header Files
//----------------------
#ifndef _FSTREAM_
#include <fstream>
#endif

//Defines
//-------
#ifdef UNICODE
#define tfstream fstream
#define tofstream wofstream
#define tifstream wifstream
#else
#define tfstream fstream
#define tofstream ofstream
#define tifstream ifstream
#endif

#endif //_OFSTREAM