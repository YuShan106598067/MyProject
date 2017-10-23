#ifndef LIST_H
#define LIST_H

#include "atom.h"

#include <string>
using std::string;

#include <vector>
using std::vector;

class List : public Term {
public:
	string symbol() const {
		string ret = "[";
		std::vector<Term *>::const_iterator it = _elements.begin();
		if (it != _elements.end()) {
			for (; it != _elements.end() - 1 ; ++it)
				ret += (*it)->symbol() + ", ";
			ret += (*it)->symbol();
		}
		ret +=  "]";
		return ret;
	}
	string value() const {
		string ret = "[";
		std::vector<Term *>::const_iterator it = _elements.begin();
		if (it != _elements.end()) {
			for (; it != _elements.end() - 1; ++it)
				ret += (*it)->value() + ", ";
			ret += (*it)->value();
		}
		ret += "]";
		return ret;
	}
	bool match(Term & term);

public:
  List (): _elements() {}
  List (vector<Term *> const & elements):_elements(elements){
  }
  Term * head() const throw(string){

	  std::vector<Term *>::const_iterator it = _elements.begin();
	  if (it != _elements.end())
		  return *it;
	  else
		 throw std::range_error("Accessing head in an empty list");
  }
  List * tail() const {
	  std::vector<Term *>::const_iterator it = _elements.begin();
	  if (it != _elements.end()) {
		  List  * tail = new List[10];
		  for (++it; it != _elements.end(); ++it)
			  tail->_elements.push_back(*it);
		  return tail;
	  }
	  else
		  throw std::range_error("Accessing tail in an empty list");
  }

private:
  vector<Term *> _elements ;
};

#endif
