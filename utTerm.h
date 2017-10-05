#ifndef UTTERM_H
#define UTTERM_H

#include "variable.h"
#include "atom.h"
#include "number.h"

//test Number.value()
TEST (Number, ctor) {
	Number number(10);
	ASSERT_EQ("10", number.value());
}
//test Number.symbol()
TEST (Number, symbol) {
	Number number(10);
	ASSERT_EQ("10", number._symbol);
}
//?- 25 = 25.
// true.
TEST (Number, matchSuccess) {
	Number number(25);
	Number number1(25);
	EXPECT_TRUE(number.match(number1));
}
//?- 25 = 0.
// false.
TEST (Number, matchFailureDiffValue) {
	Number number(25);
	Number number1(0);
	EXPECT_FALSE(number.match(number1));
}
//?- 25 = tom.
// false.
TEST (Number, matchFailureDiffConstant) {
	Atom tom("tom");
	Number number(25);
	EXPECT_FALSE(number.match(tom));
}
//?- 25 = X.
// true.
TEST (Number, matchSuccessToVariable) {
	Variable X("X");
	Number number(25);
	EXPECT_TRUE(number.match(X));
}

//?- tom = 25.
// false.
TEST (Atom, matchFailureDiffConstant) {
	Atom tom("tom");
	Number X(25);
	EXPECT_FALSE(tom.match(X));
}

// ?- tom = X.
// X = tom.
TEST (Atom, matchSuccessToVariable) {
	Atom tom("tom");
	Variable X("X");
	EXPECT_TRUE(tom.match(X));
	ASSERT_EQ("tom", X._value);
}

// ?- X = tom, tom = X.
// X = tom.
TEST (Atom, matchSuccessToVarInstantedToDiffConstant) {
	Atom tom("tom");
	Variable X("X");
	EXPECT_TRUE(X.match(tom));
	EXPECT_TRUE(tom.match(X));
	ASSERT_EQ("tom", X._value);
}

// ?- X = jerry, tom = X.
// false.
TEST (Atom, matchFailureToVarInstantedToDiffConstant) {
	Atom jerry("jerry");
	Atom tom("tom");
	Variable X("X");
	EXPECT_TRUE(X.match(jerry));
	EXPECT_FALSE(tom.match(X));
}

// ?- X = 5.
// X = 5.
TEST (Variable, matchSuccessToNumber) {
	Variable X("X");
	Number number(5);
	EXPECT_TRUE(X.match(number));
	EXPECT_TRUE(X.match(number));
}

// ?- X = 25, X = 100.
// false.
TEST (Variable, matchFailureToTwoDiffNumbers) {
	Variable X("X");
	Number number(25);
	Number number1(100);
	EXPECT_TRUE(X.match(number));
	EXPECT_FALSE(X.match(number1));
}

// ?- X = tom, X = 25.
// false.
TEST (Variable, matchSuccessToAtomThenFailureToNumber) {
	Variable X("X");
	Atom tom("tom");
	Number number(25);
	EXPECT_TRUE(X.match(tom));
	EXPECT_FALSE(X.match(number));
}
//?- tom = X, 25 = X.
// false.
TEST (Variable, matchSuccessToAtomThenFailureToNumber2) {
	Variable X("X");
	Atom tom("tom");
	Number number(25);
	EXPECT_TRUE(tom.match(X));
	EXPECT_FALSE(X.match(number));
}
//?- X = tom, X = tom.
// true.
TEST(Variable, reAssignTheSameAtom){
	Variable X("X");
	Atom tom("tom");
	EXPECT_TRUE(X.match(tom));
	EXPECT_TRUE(X.match(tom));
}
#endif
