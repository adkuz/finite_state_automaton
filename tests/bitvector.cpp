#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

#include "main_test.hpp"
#include "../fs_machine/ax_libs.hpp"

template< class Container, class Value >
bool characteristic_function( const Container& container, const Value& value )
{
	return std::find( std::begin(container), std::end(container), value ) != std::end(container);
}

template< class Container >
void print( const Container& container )
{
	std::cout << "{  ";
	for( auto& obj : container )
		std::cout << obj << "  ";
	std::cout << "}" << std::endl;
}

template< class Container >
ax::bitvector make_bitvector( size_t length, const Container& container )
{
	ax::bitvector result( length );
	for( auto index : container )
		result.set( index );
	return result;
}


TEST_CASE( "Bitvector: low iq tests", "[ax::bitvector]" ) 
{
	const size_t length = 14;
	auto bitvector = ax::bitvector( length );

	SECTION( "Testing constructors" )
	{		
		const std::set<size_t> bits_to_set = { 0, 1, 2, 3, 5, 8, 13, 21 };
		ax::bitvector fib(23);

		for( auto bit : bits_to_set )
			fib.set( bit );
		
		INFO( "Copy fib to fib_copy by constructor" );
			auto fib_copy = fib;
		CAPTURE( ax::to_string( fib ) );
		CAPTURE( ax::to_string( fib_copy ) );
		REQUIRE( ( fib == fib_copy ) );

		INFO( "Reset 8 bit" );
			fib.reset( 8 );
		CAPTURE( ax::to_string( fib ) );
		CAPTURE( ax::to_string( fib_copy ) );
		REQUIRE( fib != fib_copy );
		
		INFO( "Copy new fib to fib_copy by operator=" );
			fib_copy = fib;
		CAPTURE( ax::to_string( fib ) );
		CAPTURE( ax::to_string( fib_copy ) );
		REQUIRE( fib == fib_copy );

		INFO( "Move fib to fib_move by constructor" );
			auto fib_move = std::move( fib );
		CAPTURE( ax::to_string( fib_move ) );
		CAPTURE( ax::to_string( fib_copy ) );
		REQUIRE( fib.length() == 0 );
		REQUIRE( fib_copy == fib_move );

		INFO( "Move fib_move to fib by operator=" );
			fib = std::move( fib_move );
		CAPTURE( ax::to_string( fib ) );
		CAPTURE( ax::to_string( fib_copy ) );
		REQUIRE( fib_move.length() == 0 );
		REQUIRE( fib_copy == fib );
	}

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

    SECTION( "Testing bool operator" ) 
    {
		auto zero = ax::bitvector( length );
    	auto bits_7_9 = ax::bitvector( length );
		auto is_true = true;

		INFO( " if( zero )" )
		if( zero ){
			is_true = true;
		}
		else {
			is_true = false;
		}
    	REQUIRE( is_true == false );

		INFO( " if( non_zero )" )
  		bits_7_9.set( 7 );
  		bits_7_9.set( 9 );

  		if( bits_7_9 ){
			is_true = true;
		}
		else {
			is_true = false;
		}
    	REQUIRE( is_true == true );
    }

    SECTION( "Testing binary operator" )
    {
    	const size_t size = 42;
		const std::set<size_t> bitset1 = { 0, 1, 2, 3, 5, 8, 13, 21, 34 };
		const std::set<size_t> bitset2 = { 1, 2, 4, 8, 16, 32 };
		
		std::vector<size_t> bits_union;
		std::vector<size_t> bits_diff;
		std::vector<size_t> bits_intersection;
 
		std::set_union(
			bitset1.begin(), bitset1.end(), 
			bitset2.begin(), bitset2.end(), 
			std::back_inserter(bits_union)
		);

		std::set_symmetric_difference(
        	bitset1.begin(), bitset1.end(), 
			bitset2.begin(), bitset2.end(), 
        	std::back_inserter(bits_diff)
        );

        std::set_intersection(
        	bitset1.begin(), bitset1.end(), 
			bitset2.begin(), bitset2.end(), 
			std::back_inserter(bits_intersection)
        );

        /*print( bitset1 );
        print( bitset2 );
        print( bits_union );
        print( bits_diff );
        print( bits_intersection );*/

		ax::bitvector vector1 = make_bitvector( size, bitset1 );
		ax::bitvector vector2 = make_bitvector( size, bitset2 );
		ax::bitvector vector_union = make_bitvector( size, bits_union );
		ax::bitvector vector_sum = make_bitvector( size, bits_diff );
		ax::bitvector vector_intersection = make_bitvector( size, bits_intersection );

		CAPTURE( ax::to_string( vector1 ) );
		CAPTURE( ax::to_string( vector2 ) );
		CAPTURE( ax::to_string( vector_union ) );
		CAPTURE( ax::to_string( vector_sum ) );
		CAPTURE( ax::to_string( vector_intersection ) );

		REQUIRE( (vector1 & vector2) == vector_intersection );
		REQUIRE( (vector1 | vector2) == vector_union );
		REQUIRE( (vector1 ^ vector2) == vector_sum );
	}
}


