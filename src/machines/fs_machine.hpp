#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>


#include "../ax_libs.hpp"
#include "base_fs_machine.hpp"


namespace machines {

	using symbol_t = base_finite_state_machine::symbol_index_t;
	static const symbol_t lambda_symbol = -1;


	class finite_state_machine
		: public base_finite_state_machine
	{
	public:
		using characteristic_vector = ax::bitvector;
		using transition_table_t = ax::matrix<characteristic_vector>;
		using lambda_transition_t = std::vector<characteristic_vector>;

	public:
		finite_state_machine(  size_t states_count, size_t symbols_count )
			: base_finite_state_machine( states_count, symbols_count )
			, _transition_table( states_count, symbols_count,
				characteristic_vector( states_count )
			)
			,_lambda_transition( states_count,
				characteristic_vector( states_count )
			)
		{}

		void add_rule( state_index_t state, symbol_index_t symbol,
			state_index_t next_state )
		{
			if( symbol == lambda_symbol ){
				_lambda_transition[state].set( next_state );
			}
			else {
				_transition_table( state, symbol ).set( next_state );
			}
		}

		void delete_rule( state_index_t state, symbol_index_t symbol,
			state_index_t next_state )
		{
			if( symbol == lambda_symbol ){
				_lambda_transition[state].reset( next_state );
			}
			else {
				_transition_table( state, symbol ).reset( next_state );
			}
		}

		void delete_all_rules( state_index_t state, symbol_index_t symbol )
		{
			if( symbol == lambda_symbol ){
				_lambda_transition[state] =
					std::move( characteristic_vector(_states_count) );
			}
			else {
				_transition_table( state, symbol ) =
					std::move( characteristic_vector(_states_count) );
			}
		}

		const characteristic_vector& transitions( state_index_t state, symbol_index_t symbol ) const
		{
			if( symbol == lambda_symbol ){
				return _lambda_transition[state];
			}
			else {
				return _transition_table( state, symbol );
			}
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
