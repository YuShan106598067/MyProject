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
		_symbol = ss.str();
		*_value = ss.str();
	}
	
	string symbol() const {
		return _symbol;
	}
	string value() const{
		return *_value;
	}

	string **ptr() {
		return &_value;
	}

	bool match(Term &a) {
		_assignable = true;

		if (a.value().length() == 0) {
			**a.ptr() = *_value;
		}
		if (a.value() != *_value && a.value().length() != 0)
			_assignable = false;
		return _assignable;
	}

private:
	std::stringstream ss;
	bool _assignable;
	string *_value = new string[1];
	string  _symbol;

};

#endif
