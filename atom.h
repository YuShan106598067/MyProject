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
	  Atom (string s) :_symbol(s), _value(s) {
	  }

	  string symbol() const {
		  return _symbol;
	  }
	  string value() const {
		  return _value;
	  }

	  bool match(Term &a) {
		  _assignable = true;
		  if (_value.length() == 0) {
			  _value = a.symbol();
		  }

		  if (a.value() != _value && a.value().length()!=0)
			  _assignable = false;
		  return _assignable;
	  }

private:
	bool _assignable;
	string _symbol;
	string _value;

};


#endif

