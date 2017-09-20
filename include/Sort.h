#include <list>
#include <algorithm>
#include "Shapes.h"


static int change;

class Sort {
	
	
	private:static bool compById(Shape * a, Shape * b )
	{					
		switch (change)
		{
		case 1:
			return (*a).perimeter() < (*b).perimeter();
		case 2:
			return (*a).perimeter() > (*b).perimeter();
		case 3:
			return (*a).area() < (*b).area();
		case 4:
			return (*a).area() > (*b).area();
		case 5:
			return ((*a).area()/ (*a).perimeter()) < ((*b).area()/ (*b).perimeter());
		default:
			return 0;
		}
	}
	public:static void sortByIncreasingPerimeter(std::list<Shape *> * shapeList) {
		change = 1;
		(*shapeList).sort(compById);
	}

	public:static void sortByDecreasingPerimeter(std::list<Shape *> * shapeList) {
		change = 2;
		(*shapeList).sort(compById);
	}

	public:static void sortByIncreasingArea(std::list<Shape *> * shapeList) {
		change = 3;
		(*shapeList).sort(compById);
	}

	public:static void sortByDecreasingArea(std::list<Shape *> * shapeList) {
		change = 4;
		(*shapeList).sort(compById);
	 }
  
	public:static void sortByIncreasingCompactness(std::list<Shape *> * shapeList) {
		change = 5;
		(*shapeList).sort(compById);
	}


  
};
