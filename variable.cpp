#include "atom.h"
#include "number.h"
#include "variable.h"

bool Variable::match(Atom &atom){
	if (_value.length() == 0) {
		_value = atom._symbol;
	}
	if (atom.value() != _value)
		_assignable = false;
	return _assignable;
}

bool Variable::match(Number &number){
	if (_value.length() == 0) {
		_value = number._symbol;
	}
	if (number.value() != _value)
		_assignable = false;
	return _assignable;
}

bool Variable::match(Variable & variable){
	if (_value.length() == 0) {
		_value = variable._symbol;
	}
	if (variable.value() != _value)
		_assignable = false;
	return _assignable;
}

