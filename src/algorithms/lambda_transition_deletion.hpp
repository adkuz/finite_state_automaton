#include <unordered_set>

#include "../ax_libs.hpp"
#include "../machines.hpp"



namespace algs {

    template< typename T >
    using set = std::unordered_set<T>;

    using state_t = finite_state_machine::state_index_t;
    using symbol_t = finite_state_machine:symbol_index_t;
    using machine_t = finite_state_machine;
    using lambda_transition_t = machine_t::lambda_transition_t;

    auto lambda = machines::lambda_symbol;

    void delete_lambda_transitions( machine_t& machine, state_t state )
    {
        do {
            auto& transition_mask = machine.transitions( state, lambda );

            for( state_t st = 0; st < transition_mask.length(); ++st ) {
                if( transition_mask[st] ) {
                    for( symbol_t smbl = 0; smbl < machine.symbols_count(); ++smbl ) {
                        machine.set_transitions( state, smbl,
                            machine.transition( state, smbl ) | machine.transition( st, smbl )
                        );
                    }
                }
            }
        } while ( machines.has_lambda_transition( state ) );
    }

    auto transitive_closure_of_lambda_transitions(const machine_t& machine)
        -> lambda_transition_t
    {
        /* Based on Floyd–Warshall algorithm */
        lambda_transition_t closure = machine.lambda_transitions();
        do {
            lambda_transition_t prev_closure = closure;

            for( state_t start = 0; start < machine.states_count(); ++start ) {
                auto mask = prev_closure[start];

                for( state_t end = 0; end < machine.states_count(); ++end ) {
                    if( mask[end] ) {
                        closure[start] |= prev_closure[end];
                    }
                }
            }
        } while ( closure != prev_closure );

        return closure;
    }

    machine_t lambda_transition_deletion( const machine_t& m )
    {

        machine_t machine = m; //copy machine
        /*
        auto clear_states = ax::bitvector( machine.states_count() );
        for( state_t s = 0; s < machine.states_count(); ++s ) {
            if( ! machines.has_lambda_transition( s ) ) {
                clear_states.set( s );
            }
        }
        */

        for( state_t s = 0; s < machine.states_count(); ++s ) {
            if( machines.has_lambda_transition( s ) ) {
                delete_lambda_transitions( machine, s );
            }
        }

    }

}
