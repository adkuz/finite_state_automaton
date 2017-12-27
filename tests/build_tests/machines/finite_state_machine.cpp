#include <iostream>
#include <unordered_map>
#include <vector>

#include "../../../src/ax_libs.hpp"
#include "../../../src/machines.hpp"

#include "../../main_test.hpp"



TEST_CASE( "Testing finite state machine (FSM)" )
{
	using machine_t = machines::finite_state_machine;

	machine_t megatron( 13, 7 );

	SECTION( "Adding rules" )
	{
		auto rules = std::vector<std::vector<size_t>>( 5 );

		for( auto& v : rules )
			v = std::move( std::vector<size_t>( 3, 0 ) );

		rules[0][0] = 3; rules[0][1] = 1; rules[0][2] = 4;
		rules[1][0] = 0; rules[1][1] = 5; rules[1][2] = 12;
		rules[2][0] = 1; rules[2][1] = 6; rules[2][2] = 2;
		rules[3][0] = 2; rules[3][1] = 2; rules[3][2] = 1;
		rules[4][0] = 3; rules[4][1] = 1; rules[4][2] = 7;

		for( size_t row = 0; row < 5; ++row ) {
			megatron.add_rule(rules[row][0], rules[row][1], rules[row][2]);
		}

	}

}
