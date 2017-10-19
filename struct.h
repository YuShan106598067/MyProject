#ifndef STRUCT_H
#define STRUCT_H

#include "atom.h"
#include "variable.h"
#include <vector>
#include <string>

using std::string;

class Struct :public Term
{
public:
	Struct(Atom const & name, std::vector<Term *> args) :_args(args) {
		Term * _test = new Atom(name.symbol());
		_name = _test;
	}

	Term * args(int index) {
		return _args[index];
	}

	Term const & name() {
		return *_name;
	}
	string symbol() const {
		string ret = _name->symbol() + "(";
		for (int i = 0; i < _args.size() - 1; i++) {
			ret += _args[i]->symbol() + ", ";
		}
		ret += _args[_args.size() - 1]->symbol() + ")";
		return  ret;
	}
	string value() const {

		string ret = _name->symbol() + "(";
		for (int i = 0; i < _args.size() - 1; i++){
			if (_args[_args.size() - 1]->value().length() == 0)
				ret += _args[i]->symbol() + ", ";
			else
				ret += _args[i]->value() + ", ";
		}
		if ( _args[_args.size() - 1]->value().length()==0)
			ret += _args[_args.size() - 1]->symbol() + ")";
		else 
			ret += _args[_args.size() - 1]->value() + ")";

		return  ret;
	}
	bool match(Term &term) {
		Struct * ps = dynamic_cast<Struct *>(&term);
		if (ps) {
			if (!_name->match(*(ps->_name)))
				return false;
			if (_args.size() != ps->_args.size())
				return false;
			for (int i = 0; i<_args.size(); i++) {
				if (_args[i]->symbol() != ps->_args[i]->symbol())
					return false;
			}
			return true;
		}
		return false;
	}
private:
	Term * _name ;
	std::vector<Term *> _args;
};

#endif
