#include "main_test.hpp"

#include "../fs_machine/ax_libs.hpp"



TEST_CASE( "Bitvectors are testing", "[bitvector]" ) {
	auto bitset = ax::bitvector( 14 );

    REQUIRE( bitset.length() == 14 );
    REQUIRE( bitset.length() == 15 );

}