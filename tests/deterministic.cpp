#include <iostream>
#include <unordered_map>
#include <vector>

#include "../fs_machine/ax_libs/matrix.hpp"
#include "../fs_machine/determinism.hpp"

#include "main_test.hpp"



TEST_CASE( "Testing finite state machine (FSM)" )
{
	using machine_t = machines::deterministic_finite_state_machine;

	machine_t megatron( 3, 3 );

    megatron.add_rule( 0, 0, 0 );
    megatron.add_rule( 0, 1, 1 );
    megatron.add_rule( 0, 2, 0 );

    megatron.add_rule( 1, 0, 0 );
    megatron.add_rule( 1, 1, 0 );
    megatron.add_rule( 1, 2, 2 );

    megatron.add_rule( 2, 0, 2 );
    megatron.add_rule( 2, 1, 2 );
    megatron.add_rule( 2, 2, 2 );

    megatron.add_final_state( 0 );
    megatron.add_final_state( 1 );

    megatron.set_start_state( 0 );

    SECTION( "Is correct" )
    {
        REQUIRE( machines::is_deterministic(megatron) == true );
    }

    SECTION( "check good words" )
    {
        std::vector<int> word1 = {
            1, 0, 1, 1, 0, 1, 0, 2, 2, 2, 0, 1, 0, 1, 1, 0, 1
        };

        std::vector<int> word2 = {
            0, 2, 2, 2, 0, 1, 0, 1, 1, 0, 1, 0, 2, 2, 1, 1, 0, 0, 1, 0
        };

        REQUIRE( megatron( word1 ) == true );
        REQUIRE( megatron( word2 ) == true );
    }

    SECTION( "check bad words" )
    {
        std::vector<int> word1 = {
            1, 0, 1, 1, 0, 1, 2, 2, 2, 2, 0, 1, 0, 1, 1, 0, 1
        };

        std::vector<int> word2 = {
            0, 2, 2, 2, 0, 1, 0, 1, 1, 0, 1, 2, 2, 2, 1, 1, 0, 0, 1, 0
        };

        REQUIRE( megatron( word1 ) == false );
        REQUIRE( megatron( word2 ) == false );
    }

}
