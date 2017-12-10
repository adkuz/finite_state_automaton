#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>


#include "../ax_libs.hpp"
#include "base_fs_machine.hpp"


namespace machines {

	class no_lamda_machine
		: public base_finite_state_machine
	{
	public:
		using characteristic_vector = ax::bitvector;
		using transition_table_t = ax::matrix<characteristic_vector>;

	public:
		no_lamda_machine(  size_t states_count, size_t symbols_count )
			: base_finite_state_machine( states_count, symbols_count )
			, _transition_table( states_count, symbols_count,
				characteristic_vector( states_count )
			)
		{}

		void add_rule( state_index_t state, symbol_index_t symbol,
			state_index_t next_state )
		{
			_transition_table( state, symbol ).set( next_state );
		}

		void delete_rule( state_index_t state, symbol_index_t symbol,
			state_index_t next_state )
		{
				_transition_table( state, symbol ).reset( next_state );
		}

		void delete_all_rules( state_index_t state, symbol_index_t symbol )
		{
			_transition_table( state, symbol ) =
				std::move( characteristic_vector(_states_count) );
		}

		const characteristic_vector& transitions( state_index_t state, symbol_index_t symbol ) const
		{
			return _transition_table( state, symbol );
		}

		void set_transitions( state_index_t state, symbol_index_t symbol, const characteristic_vector& mask )
		{
			if( mask.length() != states_count() )
				throw std::invalid_argument("set_tensition: mask length should be equal states_count()");

			_transition_table( state, symbol ) = mask;
		}

	protected:
		transition_table_t  _transition_table;
	};
}
