#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include "atom.h"

using std::string;

class Variable : public Term {
	public:
		
	  Variable(string s) :_symbol(s) {
	  }

	  string symbol() const {
		  return _symbol;
	  }
	  string value() const {
		  return *_value;
	  }
	  string **ptr() {
		  return &_value;
	  }
	  bool match(Term &a){
		  _assignable = true;
		  if (_value->length() == 0){
			 *_value = a.value();
		  }
		  if (a.value().length() == 0) {
			 *a.ptr() = _value ;
			 *_value = a.symbol();
		  }
		  if (a.value() != *_value)
			  _assignable = false;
		  return _assignable;
	  }
	  
	private:
	  bool _assignable;
	  string _symbol;
	  string *_value = new string[1];

};

#endif

