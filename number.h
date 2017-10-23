#pragma once
#ifndef NUMBER_H
#define NUMBER_H

#include <string>
#include "atom.h"

class Number : public Term {
public:
	Number(double db) :Term(db) {}
};

#endif