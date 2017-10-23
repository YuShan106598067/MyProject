
#include <gtest/gtest.h>

#include "utAtom.h"
#include "utStruct.h"
#include "utList.h"
#include "utScanner.h"
#include "utVariable.h"


int main( int argc , char **argv )
{
    
	testing :: InitGoogleTest( &argc , argv ) ;
	RUN_ALL_TESTS();
	system("PAUSE");
    return  0;
}
