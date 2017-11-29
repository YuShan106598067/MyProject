
#include <gtest/gtest.h>
#include "utAtom.h"
#include "utStruct.h"
#include "utScanner.h"
#include "utVariable.h"
#include "utParser.h"
 
int main( int argc , char **argv )
{
    testing :: InitGoogleTest( &argc , argv ) ;
	RUN_ALL_TESTS();
	system("pause");
    return 0 ;
}
