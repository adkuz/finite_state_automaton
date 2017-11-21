#include <algorithm>
#include <iostream>
#include <set>

#include "main_test.hpp"
#include "../fs_machine/ax_libs.hpp"

template< class Container, class Value >
bool characteristic_function( const Container& container, const Value& value )
{
	return std::find( std::begin(container), std::end(container), value ) != std::end(container);
}


TEST_CASE( "Bitvector: scenario 1", "[ax::bitvector]" ) 
{
	
	auto bitvector = ax::bitvector( 14 );

	SECTION( "Setting bits" ) 
	{
		std::set<size_t> bits_to_set = { 0, 1, 2, 3, 5, 8, 13 };
		std::set<size_t> bits_to_reset = { 1, 2, 4, 8 }; 
		std::set<size_t> result_bits;
		
		std::set_difference(
			bits_to_set.begin(), bits_to_set.end(), 
			bits_to_reset.begin(), bits_to_reset.end(),
			std::inserter( result_bits, result_bits.begin() )
		);

		for( auto bit : bits_to_set ) {
			bitvector.set( bit );
			std::cout << bit 
				  << " : " 
				  << ax::to_string( bitvector )
				  << std::endl;
		}

		for( size_t i = 0; i < bitvector.length(); ++i ) {
			CAPTURE( i );
			CAPTURE( ax::to_string( bitvector ) );
			REQUIRE( bitvector[i] == characteristic_function( bits_to_set, i ) );
		}
	}
		
	SECTION( "Testing operator[]" )
    {
    	REQUIRE( bitvector[0] == true );
    	REQUIRE( bitvector[3] == true );
    	REQUIRE( bitvector[6] == false );
    	REQUIRE( bitvector[7] == false );
    	REQUIRE( bitvector[13] == true );
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


