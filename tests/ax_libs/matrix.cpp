#include <string>

#include "../../src/ax_libs.hpp"

#include "../main_test.hpp"



TEST_CASE( "Testing constructors ( and operator = )" )
{
	SECTION( "Null constructor" )
	{
		auto empty_matrix = ax::matrix<float>();

		INFO( "Constructor requires row counts, column counts and default value." );
		INFO( "Default is ( 0, 0, value_type(0) ) ." );

		REQUIRE( empty_matrix.col_count() == 0 );
		REQUIRE( empty_matrix.row_count() == 0 );
	}

	SECTION( "Constructor with default value" )
	{

		INFO( "Constructing matrix 3x15" );
		auto matrix = ax::matrix<float>( 3, 15, 42. );


		SECTION( "Checking size" )
		{
			REQUIRE( matrix.col_count() == 15 );
			REQUIRE( matrix.row_count() == 3 );
		}

		SECTION( "Chcecking cells, default value is, of course, 42.0 ." )
		{
			REQUIRE( matrix( 2, 1 ) == 42 );
			REQUIRE( matrix( 1, 2 ) == 42 );
			REQUIRE( matrix( 2, 14 ) == 42 );
		}
	}

	SECTION( "Constructor with init function" )
	{

		SECTION( " - lambda" )
		{

			INFO( "Constructing matrix 3x15" );
			std::vector<int> a = { 3, 7, 2, 1, 5 };
			std::vector<int> b = { 3, 2, 1, 6 };
			auto matrix = ax::matrix<int>( a.size(), b.size(),
							[ &a, &b ]( auto row, auto col )
							{
								return a[row] * b[col];
							}
						 );


			SECTION( "Checking size" )
			{
				REQUIRE( matrix.col_count() == 4 );
				REQUIRE( matrix.row_count() == 5 );
			}

			SECTION( "Chcecking cells" )
			{
				for( size_t r = 0; r < matrix.row_count(); ++r )
					for( size_t c = 0; c < matrix.col_count(); ++c )
						REQUIRE( matrix( r, c ) == a[r] * b[c] );
			}
		}
	}

	SECTION( "Constructor from init_lists" )
	{
		INFO( "Constructing matrix 6x4" );

		ax::matrix<float> matrix = {
			{ 0,    2,  5 ,  0  },
			{ 1,    2,  3,   4  },
			{ -.07, 4,  3,   15 },
			{ -31,  8,  0,   1  },
			{ 1,    6,  -2,  28 },
			{ 31,   5,  0.5, 1  }
		};

		SECTION( "Checking size" )
		{
			REQUIRE( matrix.col_count() == 4 );
			REQUIRE( matrix.row_count() == 6 );
		}

		SECTION( "Checking cells" )
		{
			REQUIRE( matrix( 0, 0 ) == 0 );
			REQUIRE( matrix( 1, 2 ) == 3 );
			REQUIRE( matrix( 3, 1 ) == 8 );
			REQUIRE( matrix( 5, 3 ) == 1 );
			REQUIRE( matrix( 2, 3 ) == 15 );
		}
	}

	SECTION( "{ copy, move } x { constructor, operator= }" )
	{
		INFO( "Constructing matrix 6x4" );

		ax::matrix<float> matrix = {
			{ 0,    2,  5 ,  0  },
			{ 1,    2,  3,   4  },
			{ -.07, 4,  3,   15 },
			{ -31,  8,  0,   1  },
			{ 1,    6,  -2,  28 },
			{ 31,   5,  0.5, 1  }
		};

		SECTION( "Testing copy constuctor" )
		{
			auto matrix_copy = matrix;

			for( size_t row = 0; row < matrix.row_count(); ++row )
				for( size_t col = 0; col < matrix.col_count(); ++col )
					REQUIRE( matrix(row, col) == matrix_copy(row, col) );
		}

		SECTION( "Testing move constuctor" )
		{
			auto moved_matrix = std::move( matrix );

			REQUIRE( moved_matrix.col_count() == 4 );
			REQUIRE( moved_matrix.row_count() == 6 );

			REQUIRE( matrix.col_count() == 0 );
			REQUIRE( matrix.row_count() == 0 );

			REQUIRE( moved_matrix( 0, 0 ) == 0 );
			REQUIRE( moved_matrix( 1, 2 ) == 3 );
			REQUIRE( moved_matrix( 3, 1 ) == 8 );
			REQUIRE( moved_matrix( 5, 3 ) == 1 );
			REQUIRE( moved_matrix( 2, 3 ) == 15 );
		}

		SECTION( "Testing copy operator=" )
		{
			decltype( matrix ) new_matrix; // default - empty matrix;

			new_matrix = matrix;

			SECTION( "Checking size" )
			{
				REQUIRE( new_matrix.col_count() == 4 );
				REQUIRE( new_matrix.row_count() == 6 );
			}

			SECTION( "Checking cells" )
			{
				REQUIRE( new_matrix( 0, 0 ) == 0 );
				REQUIRE( new_matrix( 1, 2 ) == 3 );
				REQUIRE( new_matrix( 3, 1 ) == 8 );
				REQUIRE( new_matrix( 5, 3 ) == 1 );
				REQUIRE( new_matrix( 2, 3 ) == 15 );
			}
		}

		SECTION( "Testing move operator=" )
		{
			decltype( matrix ) new_matrix( 3, 2, 1 );

			new_matrix = std::move( matrix );

			SECTION( "Checking sizes" )
			{
				REQUIRE( matrix.col_count() == 2 );
				REQUIRE( matrix.row_count() == 3 );

				REQUIRE( new_matrix.col_count() == 4 );
				REQUIRE( new_matrix.row_count() == 6 );
			}

			SECTION( "Checking cells" )
			{

				REQUIRE( matrix( 0, 0 ) == 1 );
				REQUIRE( matrix( 1, 2 ) == 1 );

				REQUIRE( new_matrix( 0, 0 ) == 0 );
				REQUIRE( new_matrix( 1, 2 ) == 3 );
				REQUIRE( new_matrix( 3, 1 ) == 8 );
				REQUIRE( new_matrix( 5, 3 ) == 1 );
				REQUIRE( new_matrix( 2, 3 ) == 15 );
			}
		}
	}
}
