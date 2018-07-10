#ifndef ADTEXCEPTION_H
#define ADTEXCEPTION_H

#include <stdexcept>
#include <Windows.h>
#include <iostream>

using std::wstring;
using std::string;
using std::endl;
using std::exception;
using std::ostream;

class AdtException : public exception
{
public:
	AdtException(const char * what)
		: exception(what) { }

	const wchar_t * What() const
	{
		string str = exception::what();
		const size_t sizeNeeded = MultiByteToWideChar(CP_UTF8, 0, &str[0], static_cast<int>(str.size()), nullptr, 0);
		wstring wstrTo(sizeNeeded, 0);
		MultiByteToWideChar(CP_UTF8, 0, &str[0], str.size(), &wstrTo[0], sizeNeeded);
		
		return wstrTo.c_str();
	}

	friend ostream & operator<<(std::ostream & stream, AdtException & exception)
	{
		stream << exception.what() << endl;
		return stream;
	}
};


#endif
