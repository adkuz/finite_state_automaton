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

    auto lambda = machines::lambda_symbol;



    auto transitive_closure_of_lambda_transitions(const machine_t& machine)
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

        for( size_t i = 0; i < closure.size(); ++i )
            closure[i].reset(i);

        return closure;
    }


}
