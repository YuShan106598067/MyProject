#ifndef PARSER_H
#define PARSER_H
#include <string>
using std::string;

#include "atom.h"
#include "variable.h"
#include "global.h"
#include "scanner.h"
#include "struct.h"
#include "list.h"
#include "node.h"
#include "utParser.h"
#include <sstream>
class Parser{
public:
  Parser(Scanner scanner) : _scanner(scanner), _terms(){}

  Term* createTerm(){
    int token = _scanner.nextToken();
    _currentToken = token;
    if(token == VAR){
      return new Variable(symtable[_scanner.tokenValue()].first);
    }else if(token == NUMBER){
      return new Number(_scanner.tokenValue());
    }else if(token == ATOM || token == ATOMSC){
      Atom* atom = new Atom(symtable[_scanner.tokenValue()].first);
      if(_scanner.currentChar() == '(' ) {
        return structure();
      }
      else
        return atom;
    }
    else if(token == '['){
      return list();
    }

    return nullptr;
  }



  Term * structure() {
    Atom structName = Atom(symtable[_scanner.tokenValue()].first);
    int startIndexOfStructArgs = _terms.size();
    _scanner.nextToken();
    createTerms();
    if(_currentToken == ')')
    {
      vector<Term *> args(_terms.begin() + startIndexOfStructArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfStructArgs, _terms.end());
      return new Struct(structName, args);
    } else {
      throw string("unexpected token");
    }
  }

  Term * list() {
    int startIndexOfListArgs = _terms.size();
    createTerms();
    if(_currentToken == ']')
    {
      vector<Term *> args(_terms.begin() + startIndexOfListArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfListArgs, _terms.end());
      return new List(args);
    } else {
      throw string("unexpected token");
    }
  }

  void matchings(){

	  Term* term = createTerm();
	  if (term != nullptr)
	  {
		  _terms.push_back(term);
		  while ((_currentToken = _scanner.nextToken()) == '=' || _currentToken == ',' || _currentToken == ';') {
			  
			  string Token;
			  std::ostringstream strs;
			  strs << _currentToken;
			  Token = strs.str();
			  Term* equal = new Atom(Token);
			  _terms.push_back(createTerm());
			  _symbols.push_back(equal);
		  }


			  
		  

		  it = _terms.begin();
		  sit = _symbols.begin();
	  }
  }

  Node * expressionTree(){
	  if ((_symbols.size()/ 2) % 2 != 0) {
		  if (i < _symbols.size() / 2 && _symbols.size()>1) {
			  i++;
			  Term* comma;
			  Operators op;
			  sit=sit+1;
			  if ((*sit) ->symbol() == "59") {

				  comma = new Atom(";");
				  op = SEMICOLON;
			  }
			  else {
				  std::vector<Term *>::const_iterator uit;
				  std::vector<Term *>::const_iterator usit;
				  for (uit = _terms.begin(); uit != _terms.end(); ++uit) {
					  for (usit = _terms.begin() + 1; usit != _terms.end(); ++usit) {
						  if ((*usit)->symbol() == (*uit)->symbol())
							  (*usit)->match(**uit);
						  if (typeid(**uit) == typeid(Struct)) {
							  Struct * ps = dynamic_cast<Struct *>(&**uit);
							  for (int i = 0; i < ps->arity(); i++) {
								  if (ps->args(i)->symbol() == (*usit)->symbol()) {
									  ps->args(i)->match(**usit);
									  ps->value();
								  }
							  }
						  }
					  }
				  }

				  comma = new Atom(",");
				  op = COMMA;

			  }				  
			  Node * left = expressionTree();
			  Node * right = expressionTree();
			  return new Node(op, comma, left, right);

		  }
		  else {
			  i++;
			  Term * equality = new Atom("=");
			  Node * left = new Node(TERM, *it);
			  it++;
			  Node * right = new Node(TERM, *it);
			  it++;
			  return new Node(EQUALITY, equality, left, right);
		  }
	  }
	  else {
		  if (i % 2 == 0 && i< _symbols.size()-1) {
			  i++;
			  Term* comma = new Atom(",");
			  Node * left = expressionTree();
			  Node * right = expressionTree();
			  return new Node(COMMA, comma, left, right);

		  }
		  else {

			  std::vector<Term *>::const_iterator uit;
			  std::vector<Term *>::const_iterator usit;
			  for (uit = _terms.begin(); uit != _terms.end(); ++uit) {
				  for (usit = _terms.begin() + 1; usit != _terms.end(); ++usit) {
					  //if ((*usit)->symbol() == (*uit)->symbol())
						  //(*usit)->match(**uit);
					  if (typeid(**uit) == typeid(Struct)) {
						  Struct * ps = dynamic_cast<Struct *>(&**uit);
						  if (typeid(*ps->args(0)) == typeid(Struct)) {
							  Struct * ps2 = dynamic_cast<Struct *>(&*ps->args(0));
							  if (ps2->args(0)->symbol() == (*usit)->symbol()) {
								  ps2->args(0)->match(**usit);
								  ps2->value();
							  }
						  }

					  }
				  }
			  }

			  i++;
			  Term * equality = new Atom("=");
			  Node * left = new Node(TERM, *it);
			  it++;
			  Node * right = new Node(TERM, *it);
			  it++;
			  return new Node(EQUALITY, equality, left, right);
		  }

	  }
  }




  vector<Term *> & getTerms() {
    return _terms;
  }

private:
  FRIEND_TEST(ParserTest, createArgs);
  FRIEND_TEST(ParserTest,ListOfTermsEmpty);
  FRIEND_TEST(ParserTest,listofTermsTwoNumber);
  FRIEND_TEST(ParserTest, createTerm_nestedStruct3);

  void createTerms() {
    Term* term = createTerm();
    if(term!=nullptr)
    {
      _terms.push_back(term);
      while((_currentToken = _scanner.nextToken()) == ',') {
        _terms.push_back(createTerm());
      }
    }
  }
  std::vector<Term *>::const_iterator it;
  std::vector<Term *>::const_iterator sit;
  int i = 0;
  vector<Term *> _symbols;
  vector<Term *> _terms;
  Scanner _scanner;
  int _currentToken;
};
#endif
