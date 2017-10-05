#include "atom.h"
#include "variable.h"
#include "number.h"

bool Atom::match(Atom &a)
{
	if (a._symbol != _symbol)
		_assignable = false;
	return _assignable;
}

bool Atom::match(Variable &a){
	if (a.value().length() == 0)
		a._value = _symbol;
	if (a.value() != _value)
		_assignable = false;
	return _assignable;
}

bool Atom::match(Number &a)
{
	if (a._symbol != _symbol)
		_assignable = false;
	return _assignable;
}
