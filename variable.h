#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include "atom.h"

using std::string;

class Variable : public Term {
	public:
		
	  Variable(string s) {
		  *_symbol = s;
	  }

	  string symbol() const {
		  return *_symbol;
	  }
	  string value() const {
		  return *_value;
	  }
	  string **ptr() {
		  return &_value;
	  }
	  bool match(Term &a) {
		  int i = 0;
		  _assignable = true;
		  Variable * ps = dynamic_cast<Variable *>(&a);

		  if (a.ptr())
		  {
			  if ((*_value).length() == 0 && a.value().length() != 0) {
				  if (ps) 
					  _value = (*ps)._value;
				  else {
					  *_value = **a.ptr();
					  a._value = _value;
				  }
			  }
			  if (a.value().length() == 0)
				  *a.ptr() = _value;

			  if (a.value() != *_value)
				  _assignable = false;
		  }
		  else
		  {
			  if (_value->length() == 0) 
				  *_value = a.value();
			  else 
				  _assignable = false;
		  }
		  return _assignable;
		
	  }
		string *_value = new string[100];
	private:

	  bool _assignable;
	  string *_symbol = new string[100];


};

#endif
