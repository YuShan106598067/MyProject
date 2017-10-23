
#include "list.h"
#include "atom.h"
#include "variable.h"
#include <typeinfo>

bool List::match(Term & a)
{
	if (typeid(a) == typeid(Variable)) {
		for (int i = 0; i < _elements.size(); i++) {
			if (_elements[i]->symbol() == a.symbol())
			return false;
		}
		return a.match(*this);
	}
	if (typeid(a) == typeid(List)) {
		List * ps = dynamic_cast<List *>(&a);
		if (ps) {
			if (_elements.size() != ps->_elements.size())
				return false;
			for (int i = 0; i<_elements.size(); i++) {
				if (_elements[i]->symbol() != ps->_elements[i]->symbol()) {		
					if (!_elements[i]->match(*ps->_elements[i]))
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




