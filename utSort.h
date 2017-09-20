#ifndef EXP_H
#define EXP_H
#include "include/Shapes.h"
#include "include/Media.h"
#include "include/Sort.h"

const double epsilon = 0.000001;



TEST (Sort, sortByIncreasingPerimeter) {
	vertex vertex_1 = { 1, 4 };
	vertex vertex_2 = { 2, 1 };
	vertex vertex_3 = { 4, 3 };
	Rectangle rect(0, 0, 100, 9);
	Rectangle rect2(0, 0, 200, 9);
	Triangle tri(vertex_1, vertex_2, vertex_3);

	std::list<Shape *>  newShapeList ;
	newShapeList.push_back(&rect);
	newShapeList.push_back(&rect2);
	newShapeList.push_back(&tri);
	
	Sort::sortByIncreasingPerimeter(&newShapeList);

	std::list<Shape *>::iterator iter = newShapeList.begin();
	ASSERT_NEAR(9.1529824, (*iter)->perimeter(), epsilon);
	iter++;
	ASSERT_NEAR(218, (*iter)->perimeter(), epsilon);
	iter++;
	ASSERT_NEAR(418, (*iter)->perimeter(), epsilon);
}

TEST (Sort, sortByDecreasingPerimeter) {
	vertex vertex_1 = { 1, 4 };
	vertex vertex_2 = { 2, 1 };
	vertex vertex_3 = { 4, 3 };
	Rectangle rect(0, 0, 100, 9);
	Rectangle rect2(0, 0, 200, 9);
	Triangle tri(vertex_1, vertex_2, vertex_3);

	std::list<Shape *>  newShapeList;
	newShapeList.push_back(&rect);
	newShapeList.push_back(&rect2);
	newShapeList.push_back(&tri);

	Sort::sortByDecreasingPerimeter(&newShapeList);

	std::list<Shape *>::iterator iter = newShapeList.begin();
	ASSERT_NEAR(418, (*iter)->perimeter(), epsilon);
	iter++;
	ASSERT_NEAR(218, (*iter)->perimeter(), epsilon);
	iter++;
	ASSERT_NEAR(9.1529824, (*iter)->perimeter(), epsilon);

}

TEST (Sort, sortByIncreasingArea) {

	Rectangle rect(0, 0, 100, 9);
	Rectangle rect2(0, 0, 50, 9);
	Rectangle rect3(0, 0, 300, 9);

	std::list<Shape *>  newShapeList;
	newShapeList.push_back(&rect);
	newShapeList.push_back(&rect2);
	newShapeList.push_back(&rect3);

	Sort::sortByIncreasingArea(&newShapeList);

	std::list<Shape *>::iterator iter = newShapeList.begin();
	ASSERT_NEAR(450, (*iter)->area(), epsilon);
	iter++;
	ASSERT_NEAR(900, (*iter)->area(), epsilon);
	iter++;
	ASSERT_NEAR(2700, (*iter)->area(), epsilon);

}

TEST (Sort, sortByDecreasingArea) {
	Rectangle rect(0, 0, 100, 9);
	Rectangle rect2(0, 0, 50, 9);
	Rectangle rect3(0, 0, 300, 9);

	std::list<Shape *>  newShapeList;
	newShapeList.push_back(&rect);
	newShapeList.push_back(&rect2);
	newShapeList.push_back(&rect3);

	Sort::sortByDecreasingArea(&newShapeList);

	std::list<Shape *>::iterator iter = newShapeList.begin();
	ASSERT_NEAR(2700, (*iter)->area(), epsilon);
	iter++;
	ASSERT_NEAR(900, (*iter)->area(), epsilon);
	iter++;
	ASSERT_NEAR(450, (*iter)->area(), epsilon);
}

TEST (Sort, sortByIncreasingCompactness) {

	Rectangle rect(0, 0, 100, 9);
	Rectangle rect2(0, 0, 10, 9);
	Rectangle rect3(5, 5, 5, 5);

	std::list<Shape *>  newShapeList;
	newShapeList.push_back(&rect);
	newShapeList.push_back(&rect2);
	newShapeList.push_back(&rect3);

	Sort::sortByIncreasingCompactness(&newShapeList);

	std::list<Shape *>::iterator iter = newShapeList.begin();
	ASSERT_NEAR(25.0/20, (*iter)->area()/ (*iter)->perimeter(), epsilon);
	iter++;
	ASSERT_NEAR(90.0 / 38, (*iter)->area() / (*iter)->perimeter(), epsilon);
	iter++;
	ASSERT_NEAR(900.0 / 218, (*iter)->area() / (*iter)->perimeter(), epsilon);
	iter++;
}

#endif
