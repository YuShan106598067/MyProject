#pragma once
#ifndef NUMBER_H
#define NUMBER_H

#include <string>
#include "atom.h"
using std::string;

class Number : public Term {
public:
	Number(double db) :Term(db) {}
};

#endif
