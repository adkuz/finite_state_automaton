#include "main_test.hpp"

#include "../fs_machine/fs_machine.hpp"



TEST_CASE( "Test base_finite_state_machine" )
{
	using machine_t = machines::base_finite_state_machine;

	auto machine = machine_t( 10, 17 );

	SECTION( "Testing get-methods" )
	{
		REQUIRE( machine.states_count() == 10 );
		REQUIRE( machine.symbols_count() == 17 );
	}

}