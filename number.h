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
		*_value = ss.str();
	}
	
	string symbol() const {
		return *_value;
	}
	string value() const{
		return *_value;
	}

	string **ptr() {
		return &_value;
	}

	bool match(Term &a) {
		Number * ps = dynamic_cast<Number *>(&a);
		_assignable = true;
		if (ps) {
			if (ps->symbol() != *_value)
				_assignable = false;
		}
		else {
			if (a.ptr())
			{
				if (a.value().length() == 0) {
					**a.ptr() = *_value;
					*a.ptr() = _value;
				}
				else if (a.value() != *_value)
					_assignable = false;
				else
					_assignable = true;
			}
		}
		return _assignable;
	}
	string *_value = new string[100];
private:
	std::stringstream ss;
	bool _assignable;


};

#endif
