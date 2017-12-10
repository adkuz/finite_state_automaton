#pragma once

#include "../ax_libs.hpp"


namespace machines {

	class base_finite_state_machine
	{
	public:
		using size_t = std::size_t;
		using state_index_t = unsigned short int;
		using symbol_index_t = unsigned short int;

		using final_states_t = ax::bitvector;

		static constexpr size_t max_state_cout = 8 * sizeof( state_index_t );

	public:

		base_finite_state_machine( size_t states_count, size_t symbols_count )
			: _states_count( states_count )
			, _symbols_count( symbols_count )
			, _start_state( 0 )
			, _final_states( states_count )
		{}

		bool set_final_state( state_index_t state_index )
		{
			if( _is_valid_state( state_index ) ) {
				_final_states.set( state_index );
				return true;
			}
			return false;
		}

		bool uset_final_state( state_index_t state_index )
		{
			if( _is_valid_state( state_index ) ) {
				_final_states.reset( state_index );
				return true;
			}
			return false;
		}

		template<class It>
		bool set_final_states( It begin, It end )
		{
			_final_states = final_states_t( _states_count );
			bool is_all_right = true;

			for( auto it = begin; it != end; it = std::next(it) ) {
				is_all_right = is_all_right && set_final_state( *it );
			}
			return is_all_right;
		}

		void set_final_states( const final_states_t& states )
		{
			if( states.length() != _states_count )
				throw std::invalid_argument("set_tensition: mask length should be equal states_count()");

			_final_states = states;
		}

		template<class It>
		bool unset_final_states( It begin, It end )
		{
			_final_states = final_states_t( _states_count );
			bool is_all_right = true;

			for( auto it = begin; it != end; it = std::next(it) ) {
				is_all_right = is_all_right && unset_final_state( *it );
			}
			return is_all_right;
		}

		const final_states_t& final_states() const
		{
			return _final_states;
		}

		bool set_start_state( state_index_t state_index )
		{
			if( _is_valid_state( state_index ) ) {
				_start_state = state_index;
				return true;
			}
			return false;
		}

		state_index_t start_state() const
		{
			return _start_state;
		}

		size_t states_count() const
		{
			return _states_count;
		}

		size_t symbols_count() const
		{
			return _symbols_count;
		}

		bool is_final_state( state_index_t state_index ) const
		{
			return this->_final_states[ state_index ];
		}

		friend std::ostream& operator <<( std::ostream& ostr, const base_finite_state_machine& m)
		{
			ostr << "base: [ states: 0.."
				 << m.states_count() - 1
				 << ", symbols: 0.."
				 << m.symbols_count() - 1
				 << ", final states mask = "
				 << ax::to_string( m.final_states() )
				 << " ]";
			return ostr;
		}

	protected:
		size_t _states_count;
		size_t _symbols_count;

		state_index_t  _start_state;
		final_states_t _final_states;

		bool _is_valid_state( state_index_t state_index ) const
		{
			return state_index < this->_states_count;
		}
	};
}
