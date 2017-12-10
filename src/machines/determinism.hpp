#pragma once

#include <iostream>
#include <iomanip>
#include <string>


#include "../ax_libs.hpp"
#include "base_fs_machine.hpp"


namespace machines {

    using state_t = base_finite_state_machine::state_index_t;
    static const state_t infinity_state = -1;

	class deterministic_finite_state_machine
        : public base_finite_state_machine
	{
	public:
		using transition_table_t = ax::matrix<state_index_t>;

	public:
		deterministic_finite_state_machine(  size_t states_count, size_t symbols_count )
			: base_finite_state_machine( states_count, symbols_count )
			, _transition_table( states_count, symbols_count,
				state_index_t( infinity_state )
			)
		{}

		void add_rule( state_index_t state, symbol_index_t symbol,
			state_index_t next_state )
		{
			_transition_table( state, symbol ) = next_state;
		}

		void delete_rule( state_index_t state, symbol_index_t symbol,
			state_index_t next_state )
		{
			_transition_table( state, symbol ) = infinity_state;
		}

        state_index_t transition(  state_index_t state, symbol_index_t symbol ) const
        {
            return _transition_table( state, symbol );
        }

		size_t states_count() const
		{
			return _states_count;
		}

		size_t symbols_count() const
		{
			return _symbols_count;
		}

        template<class Sequence>
        bool operator()( const Sequence& word )
        {
            auto state = _start_state;
            for( auto it = std::begin(word); it != std::end(word); ++it ) {
                state = transition( state, *it );
            }
            return is_final_state(state);
        }

        friend std::ostream& operator<<( std::ostream& ostr, const deterministic_finite_state_machine& m )
		{
			ostr << static_cast<const base_finite_state_machine&>( m ) << std::endl;

			for( size_t state = 0; state < m.states_count(); ++ state ) {
		        ostr << std::setw(3) << state << " : ";
		        for( size_t symbol = 0; symbol < m.symbols_count(); ++symbol ) {
		            ostr << "[ "
		                 << std::setw(3)
                         << m.transition( state, symbol )
		                 << " ] ";
		        }
				ostr << std::endl;
			}

			return ostr;
		}

	protected:
		transition_table_t  _transition_table;
	};


    bool is_deterministic( const deterministic_finite_state_machine& laplace_demon )
    {
        auto states_count = laplace_demon.states_count();
        auto symbols_count = laplace_demon.symbols_count();

        for( auto s = states_count; s > 0; ) {
            --s;
            for( auto a = symbols_count; a > 0; ) {
                if( laplace_demon.transition( s, --a ) == infinity_state ) {
                    //std::cout << "s = " << s << " a = " << a << std::endl;
                    return false;
                }
            }
        }

        return laplace_demon.final_states() && laplace_demon.start_state() != infinity_state;
    };
}


/*
friend std::ostream& operator<< ( std::ostream& ostr, const finite_state_machine& machine )
{
    ostr << "{ states : " << std::to_string( machine.states_count() ) << " ; " << std::endl;
    ostr <<  "symbols : " << std::to_string( machine.symbols_count() ) << " }" << std::endl;

    for( size_t state = 0; state < machine.states_count(); ++ state ) {
        ostr << std::setw(3) << state << " : ";
        for( size_t symbol = 0; symbol < machine.symbols_count(); ++symbol ) {
            ostr << "[ "
                 << ax::to_string(machine._transition_table( state, symbol ), "", 8, "_", "1")
                 << " ] ";
        }
        ostr << std::endl;
    }
    return ostr;
}
*/
