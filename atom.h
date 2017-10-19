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
	  Atom (string s) {
		  *_symbol = s;
	  }

	  string symbol() const {
		  return *_symbol;
	  }
	  string value()  {
		  return (*_symbol);
	  }
	  string **ptr() {
		  return &_symbol;
	  }

	  bool match(Term &a) {
		  Atom * ps = dynamic_cast<Atom *>(&a);
		  _assignable = true;
		  if (ps) {
			  if (ps->symbol() != *_symbol)
				  _assignable = false;
		  }
			 else {
				 if (a.ptr())
				 {
					 if (a.value().length() == 0) {
						 *a.ptr() = _symbol;
					 }
					 else if (a.value() != *_symbol)
						 _assignable = false;
					 else
						 _assignable = true;				
				 }
			 }
			 return _assignable;
	  }

private:
	
	bool _assignable;
	string *_symbol = new string[1];


};


#endif
