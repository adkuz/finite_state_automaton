#include "../../../src/ax_libs.hpp"
#include "../../../src/algorithms.hpp"

#include "../../main_test.hpp"


TEST_CASE( "determinization" )
{
    auto lambda = machines::lambda_symbol;

    SECTION( "Test on machine 1" )
    {
        auto e = lambda;
        auto machine = machines::finite_state_machine( 4, 2 );

        machine.add_rule( 0, 0, 1 );
        machine.add_rule( 0, 1, 3 );
        machine.add_rule( 0, e, 2 );

        machine.add_rule( 1, e, 3 );
        machine.add_rule( 2, 1, 1 );
        machine.add_rule( 3, e, 2 );

        machine.set_start_state( 0 );

        machine.set_final_state( 3 );

        auto no_e_machine = algs::to_no_lambda_mashine( machine );

        REQUIRE( no_e_machine.is_final_state(1) == true );

        auto heptapod = algs::determinization( no_e_machine );

        REQUIRE( heptapod.symbols_count() == 2 );
    }

    SECTION( "Test on machine 2" )
    {
        auto e = lambda;
        auto machine = machines::finite_state_machine( 9, 2 );

        machine.add_rule( 0, 0, 0 );
        machine.add_rule( 0, 1, 0 );
        machine.add_rule( 0, e, 1 );
        machine.add_rule( 0, e, 4 );

        machine.add_rule( 1, 1, 2 );
        machine.add_rule( 2, 0, 3 );
        machine.add_rule( 3, e, 8 );

        machine.add_rule( 4, 0, 5 );
        machine.add_rule( 5, 0, 6 );
        machine.add_rule( 6, 1, 7 );
        machine.add_rule( 7, e, 8 );

        machine.set_start_state( 0 );

        machine.set_final_state( 8 );

        auto no_e_machine = algs::to_no_lambda_mashine( machine );

        REQUIRE( no_e_machine.is_final_state(3) == true );
        REQUIRE( no_e_machine.is_final_state(7) == true );


        auto heptapod = algs::determinization( no_e_machine );

        //std::cout << machine << std::endl;
        //std::cout << no_e_machine << std::endl;
        //std::cout << heptapod << std::endl;


        REQUIRE( heptapod.symbols_count() == 2 );

        std::vector<int> word1 = {
            1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1
        };

        std::vector<int> word2 = {
            0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0
        };

        std::vector<int> word3 = {
            0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0 , 0, 1
        };

        std::vector<int> word4 = {
            0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0 , 0, 1, 1, 1, 1
        };

        std::vector<int> word5 = {
             1, 1, 0, 0, 1, 0 , 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1
        };


        REQUIRE( heptapod(word1) == false );
        REQUIRE( heptapod(word3) == true );
        REQUIRE( heptapod(word4) == false );
        REQUIRE( heptapod(word2) == true );
        REQUIRE( heptapod(word5) == false );



    }


}
