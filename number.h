#pragma once
#ifndef NUMBER_H
#define NUMBER_H

#include <string>
#include <sstream>
//symbol(), value() and match()
using std::string;

class Number : public Term {
public:
	Number(double s){
		ss << s;
		*_symbol = ss.str();
	}
	
	string symbol() const {
		return *_symbol;
	}
	string value() const{
		return *_symbol;
	}

	string **ptr() {
		return &_symbol;
	}

	bool match(Term &a) {
		_assignable = true;
		if (a.ptr())
		{
			if (a.value().length() == 0) {
				*a.ptr() = _symbol;
			}
			else if (a.value() != *_symbol)
				_assignable = false;
			else
				_assignable = true;
			return _assignable;
		}
	}

private:
	std::stringstream ss;
	bool _assignable;
	string *_symbol = new string[1];

};

#endif
