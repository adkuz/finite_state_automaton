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


TEST_CASE( "Bitvector: set / reset", "[ax::bitvector]" ) 
{
	const size_t length = 14;
	auto bitvector = ax::bitvector( length );

	SECTION( "Testing set/reset" ) 
	{
		const std::set<size_t> bits_to_set = { 0, 1, 2, 3, 5, 8, 13 };
		const std::set<size_t> bits_to_reset = { 1, 2, 4, 8 }; 
		std::set<size_t> result_bits;
		
		std::set_difference(
			bits_to_set.begin(), bits_to_set.end(), 
			bits_to_reset.begin(), bits_to_reset.end(),
			std::inserter( result_bits, result_bits.begin() )
		);

		for( auto bit : bits_to_set )
			bitvector.set( bit );

		for( size_t i = 0; i < bitvector.length(); ++i ) {
			auto bit_index = i;
			CAPTURE( bit_index );
			CAPTURE( ax::to_string( bitvector ) );
			REQUIRE( bitvector[i] == characteristic_function( bits_to_set, i ) );
		}

		for( auto bit : bits_to_reset )
			bitvector.reset( bit );
		
		for( size_t i = 0; i < bitvector.length(); ++i ) {
			auto bit_index = i;
			CAPTURE( bit_index );
			CAPTURE( ax::to_string( bitvector ) );
			REQUIRE( bitvector[i] == characteristic_function( result_bits, i ) );
		}

	}
		
	SECTION( "Testing operator[]" )
    {
    	CAPTURE( ax::to_string( bitvector ) );
    	
    	bitvector.set( 0 );
    	bitvector.set( 3 );
    	bitvector.set( 6 );
    	bitvector.set( 13 );

    	bitvector.reset( 6 );

    	REQUIRE( bitvector[0] == true );
    	REQUIRE( bitvector[3] == true );
    	REQUIRE( bitvector[6] == false );
    	REQUIRE( bitvector[7] == false );
    	REQUIRE( bitvector[13] == true );
    }

    SECTION( "Testing convert bitset to string by ax::to_string" )
    {
    	bitvector.set( 0 );
    	REQUIRE( ax::to_string( bitvector, "--" )      == "1000--0000--0000--00" );

    	bitvector.set( 6 );
	    REQUIRE( ax::to_string( bitvector, "^" , 3 )   == "100^000^100^000^00" );

    	bitvector.set( 13 );
    	bitvector.reset( 0 );
    	REQUIRE( ax::to_string( bitvector, "..." , 5 ) == "00000...01000...0001" );
    	REQUIRE( ax::to_string( bitvector, "," , 2 )   == "00,00,00,10,00,00,01" );    	
    }
}


