#ifndef STRUCT_H
#define STRUCT_H

#include "atom.h"
#include <vector>
#include <string>

using std::string;

class Struct: public Term {
public:
  Struct(Atom name, std::vector<Term *> args): _name(name) {
    _args = args;
  }

  Term * args(int index) {
    return _args[index];
  }

  int arity() {
	  return _args.size();
  }

  Atom & name() {
    return _name;
  }
  string symbol() const {
    string ret = _name.symbol() + "(";
	if (!_args.empty()) {
		std::vector<Term *>::const_iterator it = _args.begin();
		for (; it != _args.end() - 1; ++it)
			ret += (*it)->symbol() + ", ";
		ret += (*it)->symbol() + ")";
	}
	else {
		ret +=  ")";
	}
    return ret;
  }
  string value() const {
    string ret = _name.symbol() + "(";
    std::vector<Term *>::const_iterator it = _args.begin();
    for (; it != _args.end()-1; ++it)
      ret += (*it)->value()+", ";
    ret  += (*it)->value()+")";
    return ret;
  }

  bool match(Term & a)
  {
	  if (typeid(a) == typeid(Variable)) {
		  for (int i = 0; i <  _args.size(); i++) {
			  if (_args[i]->symbol() == a.symbol())
				  return false;
		  }
		  return a.match(*this);
	  }
	  if (typeid(a) == typeid(Struct)) {
		  Struct * ps = dynamic_cast<Struct *>(&a);
		  if (ps) {
			  if (_name.symbol() != ps->name().symbol())
				  return false;
			  if (_args.size() != ps->_args.size())
				  return false;
			  for (int i = 0; i< _args.size(); i++) {
				  if (_args[i]->symbol() != ps->_args[i]->symbol()) {
					  if (!_args[i]->match(*ps->_args[i]))
						  return false;
				  }
			  }
			  return true;
		  }
		  return false;
	  }
	  else
		  return symbol() == a.symbol();

  }


private:
  Atom _name;
  std::vector<Term *> _args;
};

#endif
