#include <exception>
#include <functional>
#include <unordered_set>
#include <unordered_map>


#include "../ax_libs.hpp"
#include "../machines.hpp"

#include "lambda_transition_deletion.hpp"

namespace algs {

    using automaton_t = machines::deterministic_finite_state_machine;

    using exception_t = std::invalid_argument;

    template <typename T, typename U>
    struct pair_hash {
    public:
        std::hash<T> hashT;
        std::hash<U> hashU;

        pair_hash() = default;

        std::size_t operator()(const std::pair<T, U>& x) const
        {
            return hashT(x.first) ^ hashU(x.second);
        }
    };

    auto determinization( const no_l_machine_t& machine )
        -> automaton_t
    {
        using hyper_state_t = no_l_machine_t::characteristic_vector;
        using applicants_states_t = std::unordered_set<hyper_state_t, hyper_state_t::hasher>;
        using det_states_t = std::unordered_map<hyper_state_t, state_t, hyper_state_t::hasher>;
        using rules_t = std::unordered_map<
                                            std::pair<state_t, symbol_t>,
                                            hyper_state_t,
                                            pair_hash<state_t, symbol_t>
                                          >;

        det_states_t determinated_states;
        applicants_states_t applicants;
        rules_t rules;

        auto is_determinated = [&determinated_states](auto state) -> bool {
            return determinated_states.find(state) != determinated_states.end();
        };
        auto add_to_determinated = [&determinated_states](auto state) -> state_t {
            determinated_states.emplace( state, determinated_states.size() );
            return determinated_states[state];
        };
        auto is_all_determinated = [&applicants]() -> bool {
            return applicants.empty();
        };
        auto add_applicant = [&applicants](auto state) -> size_t {
            applicants.insert(state);
            //std::cout << "_ap size after insert= " << applicants.size() << std::endl;
            return applicants.size();
        };
        auto get_applicant = [&applicants]() -> hyper_state_t {
            hyper_state_t next = *(applicants.begin());
            applicants.erase( applicants.begin() );
            //std::cout << "_ap size = " << applicants.size() << std::endl;
            return next;
        };
        auto add_rule = [&rules](auto state, auto symbol, auto next) {
            rules.emplace( std::make_pair(state, symbol), next );
        };
        auto det_count = [&determinated_states]() -> std::size_t {
            return determinated_states.size();
        };
        auto state_index = [&determinated_states](auto state) -> state_t {
            return determinated_states[state];
        };
        auto transition = [&rules](auto state, auto symbol) -> hyper_state_t {
            return rules.at(std::make_pair(state, symbol));
        };

        auto states_count = machine.states_count();
        auto symbols_count = machine.symbols_count();

        auto default_hyper_state = [states_count]() -> hyper_state_t {
            return hyper_state_t( states_count );
        };

        auto start_state = default_hyper_state();
        auto final_states = machine.final_states();

        //std::cout << "ooo  " << machine.start_state() << std::endl;

        start_state.set( machine.start_state() );
        add_applicant( start_state );

        while( ! is_all_determinated() ) {
            auto hyper_state = get_applicant();

            /*std::cout << "hyper = "
                << ax::to_string( hyper_state ) << std::endl;*/

            auto state_index = add_to_determinated(hyper_state);

            for( symbol_t symbol = 0; symbol < symbols_count; ++symbol ) {

                auto applicant = default_hyper_state();
                for( state_t state = 0; state < states_count; ++state ) {
                    if( hyper_state[state] ) {
                            applicant |= machine.transitions(state, symbol);
                    }
                }

                if( ! is_determinated(applicant) )
                    add_applicant( applicant );

                /*std::cout << "  + " << state_index << " x " << symbol << " -> "
                    << ax::to_string( applicant ) << std::endl;*/

                add_rule( state_index, symbol, applicant );
            }
        }

        auto automaton = automaton_t( det_count(), symbols_count );


        for( auto hyper_state_and_index : determinated_states ) {

            hyper_state_t hyper_state = hyper_state_and_index.first;
            auto state = state_index(hyper_state);

            for( symbol_t symbol = 0; symbol < symbols_count; ++symbol ) {
                auto next_state = state_index(transition(state, symbol));
                automaton.add_rule( state, symbol, next_state );
            }

            if( hyper_state & final_states ) {
                automaton.set_final_state( state );
            }
        }
        automaton.set_start_state( state_index(start_state) );
        //std::cout << "fs = " << ax::to_string( automaton.final_states() ) << std::endl;

        if( ! machines::is_deterministic(automaton) )
            throw exception_t("unlucky");

        return automaton;
    }
}
