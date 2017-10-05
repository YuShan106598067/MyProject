#ifndef ATOM_H
#define ATOM_H

#include <string>

using std::string;

class Variable;
class Number;

class Atom{
public:
  Atom (string s):_symbol(s),_value(s){}
  bool operator ==(Atom a) {
	  return _symbol == a._symbol;
	  return _value == a._value;
  }
  string _symbol;
  string _value;
  string value() { return _value; }
  bool match(Atom &atom);
  bool match(Variable &variable);
  bool match(Number &number);

private:
	bool _assignable = true;

};

#endif
