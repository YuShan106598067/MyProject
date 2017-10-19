#include <gtest/gtest.h>
#include "utAtom.h"
#include "utStruct.h"
#include "utVariable.h"

int main( int argc , char **argv )
{
    testing :: InitGoogleTest( &argc , argv ) ;
	RUN_ALL_TESTS();
    return 0;
}
