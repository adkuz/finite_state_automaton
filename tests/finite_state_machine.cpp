#include "main_test.hpp"

#include "../fs_machine/fs_machine.hpp"



TEST_CASE( "Factorials are computed", "[factorial]" ) {
    REQUIRE( Factorial(1) == 1 );
    REQUIRE( Factorial(2) == 2 );
    REQUIRE( Factorial(3) == 7 );
    REQUIRE( Factorial(10) == 3628800 );
}