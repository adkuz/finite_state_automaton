#include <unordered_set>
#include <vector>

#include "../fs_machine/base_fs_machine.hpp"

#include "main_test.hpp"




TEST_CASE( "Test base_finite_state_machine: get-methods" )
{
	using machine_t = machines::base_finite_state_machine;

	auto machine = machine_t( 10, 17 );

	REQUIRE( machine.states_count() == 10 );
	REQUIRE( machine.symbols_count() == 17 );

}

TEST_CASE( "Test base_finite_state_machine: final states" )
{
	using machine_t = machines::base_finite_state_machine;

	auto machine = machine_t( 10, 17 );

	SECTION( "Setting finite states : set_/unset_state_as_final" )
	{
		auto final_states_set = std::unordered_set<int>({
			2, 4, 7, 3, 8, 9,
		});

		auto not_final_states_set = std::unordered_set<int>({
			2, 8, 
		});

		for( auto state_index : final_states_set ) {
			machine.set_state_as_final( state_index );
		}	

		REQUIRE( machine.is_final_state( 2  ) == true );
		REQUIRE( machine.is_final_state( 7  ) == true );
		REQUIRE( machine.is_final_state( 3  ) == true );

		REQUIRE( machine.is_final_state( 5  ) == false );

		for( auto state_index : not_final_states_set ) {
			machine.unset_state_as_final( state_index );
		}

		REQUIRE( machine.is_final_state( 7  ) == true );
		REQUIRE( machine.is_final_state( 3  ) == true );

		REQUIRE( machine.is_final_state( 2  ) == false );
		REQUIRE( machine.is_final_state( 5  ) == false );
		REQUIRE( machine.is_final_state( 8  ) == false );
	}

	SECTION( "Setting finite states : set_finite_states" )
	{
		auto final_states_set = std::unordered_set<int>({
			2, 4, 7, 3, 8, 9,
		});
		auto final_states_vector = std::vector<int>({
			2, 5, 8, 0, 1,
		});

		machine.set_finite_states( 
			std::begin(final_states_set),
			std::end(final_states_set)
		);
			

		REQUIRE( machine.is_final_state( 2 ) == true );
		REQUIRE( machine.is_final_state( 4 ) == true );
		REQUIRE( machine.is_final_state( 9 ) == true );

		REQUIRE( machine.is_final_state( 0 ) == false );
		REQUIRE( machine.is_final_state( 5 ) == false );


		machine.set_finite_states( 
			std::begin(final_states_vector),
			std::end(final_states_vector)
		);

		REQUIRE( machine.is_final_state( 2 ) == true );
		REQUIRE( machine.is_final_state( 0 ) == true );
		REQUIRE( machine.is_final_state( 1 ) == true );
		REQUIRE( machine.is_final_state( 8 ) == true );

		REQUIRE( machine.is_final_state( 3 ) == false );
		REQUIRE( machine.is_final_state( 4 ) == false );
		REQUIRE( machine.is_final_state( 9 ) == false );
	}

}