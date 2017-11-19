#include <iostream>

#include "main_test.hpp"
#include "../fs_machine/ax_libs.hpp"



TEST_CASE( "Bitvectors are testing", "[ax::bitvector]" ) {
	auto bitset = ax::bitvector( 14 );
	

	
	SECTION( "Testing operator[]" )
    {
    	REQUIRE( bitset[0] == false );
    	REQUIRE( bitset[3] == false );
    	REQUIRE( bitset[6] == false );
    	REQUIRE( bitset[13] == false );
    }

    SECTION( "Testing convert bitset to string by ax::to_string" )
    {
    	INFO( "Something wrong" )
    	REQUIRE( ax::string_t("0000 0000 0000 00") == ax::string_t("0000 0000 0000 00") );
    }
    /*
    std::cout << ax::to_string( bitset, "--" );
    std::cout << ax::to_string( bitset, "^" , 3 );
    std::cout << ax::to_string( bitset, "..." , 5 );
    */
}