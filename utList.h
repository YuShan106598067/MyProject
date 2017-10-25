#ifndef UTLIST_H
#define UTLIST_H

#include <string>
using std::string;

#include "list.h"
#include "struct.h"
#include "atom.h"
//#include "number.h"
#include "variable.h"

// When create a new list without any item
// Then #symbol() of the list should return "[]"
TEST(List, constructor) {
	vector<Term *> args = {};
	List l(args);
	EXPECT_EQ(string("[]"), l.symbol());
}

// Given there are two perfect Numbers: 8128, 496
// When create a new list with the perfect Number
// Then #symbol() of the list should return "[496, 8128]"
TEST(List, Numbers) {
	Number n1(496), n2(8128);
	vector<Term *> args = { &n1, &n2 };
	List l(args);
	EXPECT_EQ(string("[496, 8128]"), l.symbol());
}

// Given there are two atoms: "terence_tao", "alan_mathison_turing"
// When create a new list with the Atoms
// Then #symbol() of the list should return "[terence_tao, alan_mathison_turing]"
TEST(List, Atoms) {
	Atom t("terence_tao"), a("alan_mathison_turing");
	vector<Term *> args = { &t, &a };
	List l(args);
	EXPECT_EQ(string("[terence_tao, alan_mathison_turing]"), l.symbol());
}

// Given there are two variables: X, Y
// When create a new list with the variables
// Then #symbol() of the list should return "[X, Y]"
TEST(List, Vars) {
	Variable x("X"), y("Y");
	vector<Term *> args = { &x, &y };
	List l(args);
	EXPECT_EQ(string("[X, Y]"), l.symbol());
}

// ?- tom = [496, X, terence_tao].
// false.
TEST(List, matchToAtomShouldFail) {
	Variable x("X");
	Number n(496);
	Atom t("terence_tao");
	Atom tom("tom");
	vector<Term *> args = { &x, &n ,&t };
	List l(args);
	ASSERT_FALSE(l.match(tom));
}

// ?- 8128 = [496, X, terence_tao].
// false.
TEST(List, matchToNumberShouldFail) {
	Variable x("X");
	Number n1(496);
	Atom t("terence_tao");
	Number n2(8128);
	vector<Term *> args = { &x, &n1 ,&t };
	List l(args);
	ASSERT_FALSE(l.match(n2));
}

// ?- s(X) = [496, X, terence_tao].
// false.
TEST(List, matchToStructShouldFail) {
	Number n(496);
	Variable x("X");
	Atom t("terence_tao");
	Number n2(8128);
	vector<Term *> args = { &n, &x ,&t };
	List l(args);
	std::vector<Term *> v = { &x };
	Struct s(Atom("s"), v);
	ASSERT_FALSE(l.match(s));
}

// ?- Y = [496, X, terence_tao].
// Y = [496, X, terence_tao].
TEST(List, matchToVarShouldSucceed) {
	Number n(496);
	Variable x("X");
	Atom t("terence_tao");
	Variable y("Y");
	vector<Term *> args = { &n, &x ,&t };
	List l(args);
	ASSERT_TRUE(l.match(y));
}

// ?- X = [496, X, terence_tao].
// false.
TEST(List, matchToVarOccuredInListShouldFail) {
	Number n(496);
	Variable x("X");
	Atom t("terence_tao");
	vector<Term *> args = { &n, &x ,&t };
	List l(args);
	ASSERT_FALSE(l.match(x));
}

// ?- [496, X, terence_tao] = [496, X, terence_tao].
// true.
TEST(List, matchToSameListShouldSucceed) {
	Number n(496);
	Variable x("X");
	Atom t("terence_tao");
	vector<Term *> args = { &n, &x ,&t };
	List l1(args);
	List l2(args);
	ASSERT_TRUE(l1.match(l2));
}

// ?- [496, X, terence_tao] = [496, Y, terence_tao].
// true.
TEST(List, matchToSameListWithDiffVarNameShouldSucceed) {
	Number n(496);
	Variable x("X");
	Variable y("Y");
	Atom t("terence_tao");
	vector<Term *> args = { &n, &x ,&t };
	vector<Term *> args2 = { &n, &y ,&t };
	List l1(args);
	List l2(args2);
	ASSERT_TRUE(l1.match(l2));
}

// ?- [496, X, terence_tao] = [496, 8128, terence_tao].
// X = 8128.
TEST(List, matchToVarToAtominListShouldSucceed) {
	Number n(496);
	Number n2(8128);
	Variable x("X");
	Atom t("terence_tao");
	vector<Term *> args = { &n, &x ,&t };
	vector<Term *> args2 = { &n, &n2 ,&t };
	List l1(args);
	List l2(args2);
	ASSERT_TRUE(l1.match(l2));
	EXPECT_EQ(string("8128"), x.value());
}

// ?- Y = [496, X, terence_tao], X = alan_mathison_turing.
// Y = [496, alan_mathison_turing, terence_tao],
// X = alan_mathison_turing.
TEST(List, matchVarinListToAtomShouldSucceed) {
	Number n(496);
	Number n2(8128);
	Variable x("X");
	Variable y("Y");
	Atom t("terence_tao");
	Atom a("alan_mathison_turing");
	vector<Term *> args = { &n, &x ,&t };
	vector<Term *> args2 = { &n, &a ,&t };
	List l(args);
	List l2(args2);
	y.match(l);
	x.match(a);
	//ASSERT_TRUE(y.match(l2));
	EXPECT_EQ(string("[496, alan_mathison_turing, terence_tao]"), y.value());
	EXPECT_EQ(string("alan_mathison_turing"), x.value());
}

// Example: 
// ?- [first, second, third] = [H|T].
// H = first, T = [second, third].
TEST(List, headAndTailMatching1) {
	Atom f("first"), s("second"), t("third");
	vector<Term *> args = { &f, &s, &t };
	List l(args);

	EXPECT_EQ(string("first"), l.head()->symbol());
	EXPECT_EQ(string("[second, third]"), l.tail()->value());
}

// Example:
// ?- [first, second, third] = [first, H|T].
// H = second, T = [third].
TEST(List, headAndTailMatching2) {
	Atom f("first"), s("second"), t("third");
	vector<Term *> args = { &f, &s, &t };
	List l(args);

	EXPECT_EQ(string("second"), l.tail()->head()->value());
	EXPECT_EQ(string("[third]"), l.tail()->tail()->value());
}

// ?- [[first], second, third] = [H|T].
// H = [first], T = [second, third].
TEST(List, headAndTailMatching3) {
	Atom f("first"), s("second"), t("third");
	vector<Term *> args = {&f};
	List first(args);
	vector<Term *> args2 = { &first, &s, &t };
	List l(args2);
	EXPECT_EQ(string("[first]"), l.head()->symbol());
	EXPECT_EQ(string("[second, third]"), l.tail()->value());
}

// ?- [first, second, third] = [first, second, H|T].
// H = third, T = [].
TEST(List, headAndTailMatching4) {
	Atom f("first"), s("second"), t("third");
	vector<Term *> args = { &f, &s, &t };
	List l(args);
	EXPECT_EQ(string("third"), l.tail()->tail()->head()->value());
	EXPECT_EQ(string("[]"), l.tail()->tail()->tail()->value());
}

// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing head in an empty list" as an exception.
TEST(List, emptyExecptionOfHead) {
	vector<Term *> args = {};
	List l(args);
	try{
		l.head();
	}
	catch (string e){		
		EXPECT_EQ(string("Accessing head in an empty list"), e);
	}
	
}

// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing tail in an empty list" as an exception.
TEST(List, emptyExecptionOfTail) {
	vector<Term *> args = {};
	List l(args);
	try {
		l.tail();
	}
	catch (string e) {
		EXPECT_EQ(string("Accessing tail in an empty list"), e);
	}

}




#endif
