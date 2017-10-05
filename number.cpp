#include "atom.h"
#include "variable.h"
#include "number.h"

bool Number::match(Number &a) {
	if (a._value != _value)
		_assignable = false;
	return _assignable;
}
bool Number::match(Atom &a){
	if (a._symbol != _value)
		_assignable = false;
	return _assignable;
}
bool Number::match(Variable &b){
	if (b.value().length() == 0)
		b._value = _symbol;
	if (b.value() != _value)
		_assignable = false;
	return _assignable;
}