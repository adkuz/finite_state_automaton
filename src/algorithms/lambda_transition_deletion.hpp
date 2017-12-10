#include <unordered_set>

#include "../ax_libs.hpp"
#include "../machines.hpp"



namespace algs {

    template< typename T >
    using set = std::unordered_set<T>;

    using machine_t = machines::finite_state_machine;
    using state_t = machine_t::state_index_t;
    using symbol_t = machine_t::symbol_index_t;
    using lambda_transition_t = machine_t::lambda_transition_t;

    using no_l_machine_t = machines::finite_state_machine;

    auto lambda = machines::lambda_symbol;


    auto transitive_closure_of_lambda_transitions( const machine_t& machine )
        -> lambda_transition_t
    {
        /* Based on Floyd–Warshall algorithm */

        lambda_transition_t closure = machine.lambda_transitions();
        lambda_transition_t prev_closure = closure;
        do {
            prev_closure = closure;

            for( state_t start = 0; start < machine.states_count(); ++start ) {
                auto mask = prev_closure[start];

                for( state_t end = 0; end < machine.states_count(); ++end ) {
                    if( mask[end] ) {
                        closure[start] |= prev_closure[end];
                    }
                }
            }
        } while ( closure != prev_closure );

        /*
            Now 'closure' is transitive closure of machine's
            lambda transition matrix, but it is not suitable,
            make sense.
            since the transition from state to itself by lambda doesn`t
        */

        for( size_t i = 0; i < closure.size(); ++i )
            closure[i].reset(i);

        return closure;
    }

    auto to_no_lambda_mashine( const machine_t& machine )
        -> no_l_machine_t
    {
        auto result_machine = no_l_machine_t(
            machine.states_count(),
            machine.symbols_count()
        );

        auto lambda_tr = transitive_closure_of_lambda_transitions(machine);

        for( state_t start = 0; start < machine.states_count(); ++start )
            for( state_t end = 0; end < machine.states_count(); ++end ) {
                if( lambda_tr[start][end] ) {
                    for( symbol_t smbl = 0; smbl < machine.symbols_count(); ++smbl ) {
                        result_machine.set_transitions(start, smbl,
                            result_machine.transitions(start, smbl) | machine.transitions(end, smbl)
                        );
                    }
                }
            }

        return result_machine;
    }

}
