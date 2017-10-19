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
	  string *_symbol;
	  string *_value;

};

class Atom : public Term{
	public:
	  Atom (string s) {
		  *_value = s;
	  }

	  string symbol() const {
		  return *_value;
	  }
	  string value()  {
		  return (*_value);
	  }
	  string **ptr() {
		  return &_value;
	  }

	  bool match(Term &a) {
		  Atom * ps = dynamic_cast<Atom *>(&a);
		  _assignable = true;
		  if (ps) {
			  if (ps->symbol() != *_value)
				  _assignable = false;
		  }
			 else {
				 if (a.ptr())
				 {
					 if (a.value().length() == 0) {
						 *a.ptr() = _value;
						 **a.ptr() = *_value;
					 }
					 else if (a.value() != *_value)
						 _assignable = false;
					 else
						 _assignable = true;				
				 }
			 }
			 return _assignable;
	  }
	  string *_value = new string[1];
private:
	
	bool _assignable;



};


#endif
