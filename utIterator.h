#ifndef UTITERATOR_H
#define UTITERATOR_H

#include "struct.h"
#include "variable.h"
#include "atom.h"
#include "list.h"
#include "iterator.h"

TEST(iterator, first) {
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), { &X, &two });
    Struct s(Atom("s"), { &one, &t, &Y });
    // StructIterator it(&s);
    Iterator<Term*> *itStruct = s.createIterator();
    // Iterator& itStruct = it;
    // ASSERT_EQ(it.first()->symbol());
    itStruct->first();
    ASSERT_EQ("1", itStruct->currentItem()->symbol());
    ASSERT_FALSE(itStruct->isDone());
    itStruct->next();
    ASSERT_EQ("t(X, 2)", itStruct->currentItem()->symbol());
    ASSERT_FALSE(itStruct->isDone());
    itStruct->next();
    ASSERT_EQ("Y", itStruct->currentItem()->symbol());
    itStruct->next();
    ASSERT_TRUE(itStruct->isDone());
}

TEST(iterator, nested_iterator) {
  Number one(1);
  Variable X("X");
  Variable Y("Y");
  Number two(2);
  Struct t(Atom("t"), { &X, &two });
  Struct s(Atom("s"), { &one, &t, &Y });
  Iterator<Term*> *it = s.createIterator();
  it->first();
  it->next();
  Struct *s2 = dynamic_cast<Struct *>(it->currentItem());

  Iterator<Term*> *it2 = s2->createIterator();
  it2->first();
  ASSERT_EQ("X", it2->currentItem()->symbol());
  ASSERT_FALSE(it2->isDone());
  it2->next();
  ASSERT_EQ("2", it2->currentItem()->symbol());
  ASSERT_FALSE(it2->isDone());
  it2->next();
  ASSERT_TRUE(it2->isDone());
}

TEST(iterator, firstList) {
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), { &X, &two });
    List l({ &one, &t, &Y });
    ListIterator <Term*>it(&l);
    Iterator<Term*> * itList = &it;
    itList->first();
    ASSERT_EQ("1", itList->currentItem()->symbol());
    ASSERT_FALSE(itList->isDone());
    itList->next();
    ASSERT_EQ("t(X, 2)", itList->currentItem()->symbol());
    ASSERT_FALSE(itList->isDone());
    itList->next();
    ASSERT_EQ("Y", itList->currentItem()->symbol());
    itList->next();
    ASSERT_TRUE(itList->isDone());
}

TEST(iterator, NullIterator){
  Number one(1);
  NullIterator<Term*> nullIterator(&one);
  nullIterator.first();
  ASSERT_TRUE(nullIterator.isDone());
  Iterator<Term*> * it = one.createIterator();
  it->first();
  ASSERT_TRUE(it->isDone());
}

TEST(iterator, AtomTreeIterator)
{
  Atom atom("atom");
  Iterator<Term*> *it = atom.createDFSIterator();
  it->first();
  ASSERT_TRUE(it->isDone());

  it = atom.createBFSIterator();
  it->first();
  ASSERT_TRUE(it->isDone());


}
//s(1, t(1,2), X)
/*
       s(1, t(1,2), X)
        /    |     \
       /     |      \
      1    t(1,2)    X
            / \
           /   \
          1     2
DFS:
Stack: [X t(1,2) 1]  
Stack: [X t(1,2)  ]    Output: 1
Stack: [X 2 1]         Output: 1, t(1,2)
Stack: [X 2]           Output: 1, t(1,2), 1
Stack: [X]             Output: 1, t(1,2), 1, 2
Stack: []              Output: 1, t(1,2), 1, 2, X

BFS:
Queue: [1 t(1,2) X]  
Queue: [  t(1,2) X]    Output: 1
Queue: [X 1 2]         Output: 1, t(1,2)
Queue: [1 2]           Output: 1, t(1,2), X
Queue: [2]             Output: 1, t(1,2), X, 1
Queue: []              Output: 1, t(1,2), X, 1, 2
*/
TEST(iterator,TreeDfsIterator){
  Number _1(1) , _2(2);
  Variable X("X");
  vector<Term*> v = {&_1,&_2};
  Struct t(Atom("t"), v);
  vector<Term*> v2 = {&_1,&t,&X};
  Struct s(Atom("s"), v2);
  Iterator<Term*> *it = s.createDFSIterator();
  it->first();
  ASSERT_EQ("1", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("t(1, 2)", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("1", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("2", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("X", it->currentItem()->symbol());
  it->next();
  ASSERT_TRUE(it->isDone());
}

TEST(iterator,TreeDfsIteratorEmpty){
  vector<Term*> v = {};
  Struct t(Atom("t"), v);
  Iterator<Term*> *it = t.createDFSIterator();
  it->first();
  ASSERT_TRUE(it->isDone());
}

TEST(iterator, TreeBFSIterator) {
  Number _1(1) , _2(2);
  Variable X("X");
  vector<Term*> v = {&_1,&_2};
  Struct t(Atom("t"), v);
  vector<Term*> v2 = {&_1,&t,&X};
  Struct s(Atom("s"), v2);
  Iterator<Term*> *it = s.createBFSIterator();
  it->first();
  ASSERT_EQ("1",it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("t(1, 2)",it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("X",it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("1",it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("2",it->currentItem()->symbol());
  it->next();
  ASSERT_TRUE(it->isDone());

  
}

TEST (iterator, TreeBFSIteratorList) {
  Number _1(1) , _2(2);
  Variable X("X");
  vector<Term*> v = {&_1,&_2};
  Struct t(Atom("t"), v);
  vector<Term*> v2 = {&_1,&t,&X};
  List l(v2);
  Iterator<Term*> *it = l.createBFSIterator();
  it->first();
  ASSERT_EQ("1",it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("t(1, 2)",it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("X",it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("1",it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("2",it->currentItem()->symbol());
  it->next();
  ASSERT_TRUE(it->isDone());
}

TEST (iterator, TreeDFSIteratorList) {
  Number _1(1) , _2(2);
  Variable X("X");
  vector<Term*> v = {&_1,&_2};
  Struct t(Atom("t"), v);
  vector<Term*> v2 = {&_1,&t,&X};
  List l(v2);
  Iterator<Term*> *it = l.createDFSIterator();
  it->first();
  ASSERT_EQ("1", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("t(1, 2)", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("1", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("2", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("X", it->currentItem()->symbol());
  it->next();
  ASSERT_TRUE(it->isDone());
}

#endif
