#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>

using std::string;

class Atom;
class Number;

class Variable{
public:
  Variable(string s):_symbol(s){}
  string  _symbol;
  string _value;
  string value(){ return _value; }
  bool match(Atom &atom);
  bool match(Number &number);
  bool match(Variable &variable);

private:
  bool _assignable = true;
};

#endif
