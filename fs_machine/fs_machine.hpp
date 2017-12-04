#include <iostream>
#include <iomanip>
#include <string>


#include "ax_libs.hpp"
#include "base_fs_machine.hpp"


namespace machines {


	class finite_state_machine : public base_finite_state_machine
	{
	public:
		using characteristic_vector = ax::bitvector;
		using transition_table_t = ax::matrix<characteristic_vector>;

	public:
		finite_state_machine(  size_t states_count, size_t symbols_count )
			: base_finite_state_machine( states_count, symbols_count )
			, _transition_table( states_count, symbols_count, characteristic_vector( states_count ) )
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
			_transition_table( state, symbol ) = std::move( characteristic_vector(_states_count) );
		}

		size_t states_count() const
		{
			return _states_count;
		}

		size_t symbols_count() const
		{
			return _symbols_count;
		}

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

	protected:
		transition_table_t  _transition_table;

			
	};
}