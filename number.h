#ifndef NUMBER_H
#define NUMBER_H

#include <string>

//symbol(), value() and match()
using std::string;

class Atom;
class Variable;

class Number{
public:
	Number(int s):_symbol(std::to_string(s)),_value(std::to_string(s)) {}
	string  _symbol;
	string value() { return _value; }
	string symbol() { return _symbol; }
	bool match(Number &a);
	bool match(Atom &a);
	bool match(Variable &b);

private:
	string _value;
	bool _assignable = true;
};

#endif
