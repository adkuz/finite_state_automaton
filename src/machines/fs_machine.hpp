#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>


#include "../ax_libs.hpp"
#include "no_lamda_machine.hpp"


namespace machines {

	using symbol_t = base_finite_state_machine::symbol_index_t;
	static const symbol_t lambda_symbol = -1;


	class finite_state_machine
		: public no_lamda_machine
	{
	public:
		using lambda_transition_t = std::vector<characteristic_vector>;

	public:
		finite_state_machine(  size_t states_count, size_t symbols_count )
			: no_lamda_machine( states_count, symbols_count )
			,_lambda_transition( states_count,
				characteristic_vector( states_count )
			)
		{}

		void add_rule( state_index_t state, symbol_index_t symbol,
			state_index_t next_state )
		{
			if( symbol == lambda_symbol ){
				if( state != next_state )
					_lambda_transition[state].set( next_state );
			}
			else {
				no_lamda_machine::add_rule( state, symbol, next_state );
			}
		}

		void delete_rule( state_index_t state, symbol_index_t symbol,
			state_index_t next_state )
		{
			if( symbol == lambda_symbol ){
				_lambda_transition[state].reset( next_state );
			}
			else {
				no_lamda_machine::delete_rule( state, symbol, next_state );
			}
		}

		void delete_all_rules( state_index_t state, symbol_index_t symbol )
		{
			if( symbol == lambda_symbol ){
				_lambda_transition[state] =
					std::move( characteristic_vector(_states_count) );
			}
			else {
				no_lamda_machine::delete_all_rules( state, symbol );
			}
		}

		const lambda_transition_t& lambda_transitions() const
		{
			return this->_lambda_transition;
		}

		const lambda_transition_t& set_lambda_transitions( const lambda_transition_t& lt )
		{
			if( lt.size() != states_count() || lt[0].length() != states_count() )
				throw std::invalid_argument("set_tensition: mask length should be equal states_count()");

			this->_lambda_transition = lt;
			return this->lambda_transitions();
		}

		size_t states_count() const
		{
			return _states_count;
		}

		size_t symbols_count() const
		{
			return _symbols_count;
		}

		bool has_lambda_transition( state_index_t state ) const
		{
			return _lambda_transition[state];
		}

	protected:
		transition_table_t  _transition_table;
		lambda_transition_t _lambda_transition;
	};
}
