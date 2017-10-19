#ifndef ATOM_H
#define ATOM_H

#include <string>

using std::string;


class Term{

	public:
	  virtual string symbol() const{
		  return symbol();
	  };

	  virtual string value() const{
		return symbol();
	  };
	  virtual string **ptr() {
		  return NULL;
	  };

	  virtual bool match(Term & term) {
		return symbol() == term.symbol();
	  }
	  

};

class Atom : public Term{
	public:
	  Atom (string s) :_symbol(s) {
		  *_value = s;
	  }

	  string symbol() const {
		  return _symbol;
	  }
	  string value()  {
		  return (*_value);
	  }
	  string **ptr() {
		  return &_value;
	  }

	  bool match(Term &a) {

			  _assignable = true;
		  if (a.ptr())
		  {
			  if (a.value().length() == 0) {
				  **a.ptr() = _symbol;
			  }
			  else if (a.value() != *_value)
				  _assignable = false;
			  else
				  _assignable = true;
			  return _assignable;
		  }
	  }

private:
	bool _assignable;
	string _symbol;
	string *_value = new string[1];

};


#endif
