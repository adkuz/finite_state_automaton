#include "../../../src/ax_libs.hpp"
#include "../../../src/algorithms.hpp"

#include "../../main_test.hpp"

TEST_CASE( "Testing transitive closure of lambda transitions" )
{
    auto lambda = machines::lambda_symbol;

    SECTION( "Test on machine 1" )
    {
        constexpr size_t n = 5;
        constexpr size_t m = 10;
        auto machine = machines::finite_state_machine( 5, 9 );

        ax::matrix<int> transitions = {
            { 0, 1, 0, 0, 1 },
            { 0, 0, 1, 0, 0 },
            { 0, 0, 0, 1, 0 },
            { 0, 1, 0, 0, 0 },
            { 0, 0, 0, 0, 0 },
        };

        ax::matrix<int> closure = {
            { 0, 1, 1, 1, 1 },
            { 0, 0, 1, 1, 0 },
            { 0, 1, 0, 1, 0 },
            { 0, 1, 1, 0, 0 },
            { 0, 0, 0, 0, 0 },
        };

        SECTION( "Check matrix sizes" )
        {
            assert( closure.row_count() == n );
            assert( closure.col_count() == n );

            assert( transitions.row_count() == n );
            assert( transitions.col_count() == n );
        }

        for( size_t r = 0; r < transitions.row_count(); ++r )
            for( size_t c = 0; c < transitions.col_count(); ++c )
                if( transitions( r, c ) )
                    machine.add_rule( r, lambda, c );

        auto result = algs::transitive_closure_of_lambda_transitions( machine );

        ax::matrix<int> result_matrix(
            transitions.row_count(),
            transitions.col_count(),
            [&result]( auto r, auto c )
            {
                return ( result[r][c] ) ? 1 : 0;
            }
        );

        REQUIRE( closure == result_matrix );
    }

    SECTION( "Test on machine 1" )
    {
        constexpr size_t n = 5;
        constexpr size_t m = 10;
        auto machine = machines::finite_state_machine( 5, 9 );

        ax::matrix<int> transitions = {
            { 0, 1, 0, 0, 1 },
            { 0, 0, 1, 0, 0 },
            { 0, 0, 0, 1, 0 },
            { 0, 1, 0, 0, 0 },
            { 0, 0, 0, 0, 0 },
        };

        ax::matrix<int> closure = {
            { 0, 1, 1, 1, 1 },
            { 0, 0, 1, 1, 0 },
            { 0, 1, 0, 1, 0 },
            { 0, 1, 1, 0, 0 },
            { 0, 0, 0, 0, 0 },
        };

        SECTION( "Check matrix sizes" )
        {
            assert( closure.row_count() == n );
            assert( closure.col_count() == n );

            assert( transitions.row_count() == n );
            assert( transitions.col_count() == n );
        }

        for( size_t r = 0; r < transitions.row_count(); ++r )
            for( size_t c = 0; c < transitions.col_count(); ++c )
                if( transitions( r, c ) )
                    machine.add_rule( r, lambda, c );

        auto result = algs::transitive_closure_of_lambda_transitions( machine );

        ax::matrix<int> result_matrix(
            transitions.row_count(),
            transitions.col_count(),
            [&result]( auto r, auto c )
            {
                return ( result[r][c] ) ? 1 : 0;
            }
        );

        REQUIRE( closure == result_matrix );
    }
}

TEST_CASE( "Testing fs-machine -> no-lambda-machine" )
{
    auto lambda = machines::lambda_symbol;

    SECTION( "Test on machine 1" )
    {
        constexpr size_t n = 5;
        constexpr size_t m = 10;
        auto machine = machines::finite_state_machine( n, m );

        ax::matrix<int> transitions = {
            { 0, 1, 0, 0, 1 },
            { 0, 0, 1, 0, 0 },
            { 0, 0, 0, 1, 0 },
            { 0, 1, 0, 0, 0 },
            { 0, 0, 0, 0, 0 },
        };

        ax::matrix<int> closure = {
            { 0, 1, 1, 1, 1 },
            { 0, 0, 1, 1, 0 },
            { 0, 1, 0, 1, 0 },
            { 0, 1, 1, 0, 0 },
            { 0, 0, 0, 0, 0 },
        };

        SECTION( "Check matrix sizes" )
        {
            assert( closure.row_count() == n );
            assert( closure.col_count() == n );

            assert( transitions.row_count() == n );
            assert( transitions.col_count() == n );
        }

        for( size_t r = 0; r < transitions.row_count(); ++r )
            for( size_t c = 0; c < transitions.col_count(); ++c )
                if( transitions( r, c ) )
                    machine.add_rule( r, lambda, c );

        auto result = algs::transitive_closure_of_lambda_transitions( machine );

        ax::matrix<int> result_matrix(
            transitions.row_count(),
            transitions.col_count(),
            [&result]( auto r, auto c )
            {
                return ( result[r][c] ) ? 1 : 0;
            }
        );

        auto megatron = algs::to_no_lambda_mashine( machine );

        SECTION( "Check result automaton parameters" )
        {
            REQUIRE( megatron.states_count() == n );
            REQUIRE( megatron.symbols_count() == m );
        }
    }

}
