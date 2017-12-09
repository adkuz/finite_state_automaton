#pragma once

#include <exception>
#include <functional>
#include <iostream>
#include <vector>

#include "bitvector.hpp"


namespace ax {

	template<class T>
	class matrix
	{

	public:
		using value_type = T;
		using size_type = std::size_t;
		using matrix_type = std::vector<value_type>;
		using init_func_type = std::function<value_type( size_type, size_type )>;

	public:

		matrix( size_type height = 0, size_type width = 0,
			value_type default_value = value_type(0))
			: _col_count ( width )
			, _row_count( height )
			, _matrix_data( width * height, default_value )
		{}

		matrix( size_type height, size_type width, init_func_type function )
			: _col_count( width )
			, _row_count( height )
			, _matrix_data( width * height )
		{
			for( size_type row = 0; row < _row_count; ++row )
				for( size_type col = 0; col < _col_count; ++col )
					(*this)( row, col ) = function( row, col );
		}


		matrix( const matrix& obj )
            : _col_count( obj._col_count )
            , _row_count( obj._row_count )
            , _matrix_data( obj._matrix_data )
        {}

		matrix( matrix&& obj )
            : _col_count( 0 )
            , _row_count( 0 )
            , _matrix_data()
		{
			std::swap( _row_count, obj._row_count );
			std::swap( _col_count, obj._col_count );
			std::swap( _matrix_data, obj._matrix_data );
		}

		matrix& operator=( const matrix& obj )
		{
            if ( this != &obj )
            {
                _row_count = obj._row_count;
                _col_count = obj._col_count;
                _matrix_data = obj._matrix_data;
            }
            return  *this;
		}

		matrix& operator=( matrix&& obj )
		{
            if ( this != &obj )
            {
                std::swap( _row_count, obj._row_count);
				std::swap( _col_count, obj._col_count);
				std::swap( _matrix_data, obj._matrix_data);
            }
            return  *this;
		}

		matrix( std::initializer_list<std::initializer_list<value_type>> rows )
		{
            _row_count = rows.size();

            if( _row_count ) {
	           _col_count  = std::begin(rows)->size();

	            for ( auto& row : rows )
	            {
	                if ( row.size() != _col_count )
					{
						_row_count = 0;
					 	_col_count = 0;
						_matrix_data.clear();

						throw std::logic_error( "Error! Incorrect initialization matrix" );
					}
	                _matrix_data.insert( _matrix_data.end(), std::begin(row), std::end(row) );
	            }
	       	}
	       	else {
	       	 	_col_count = 0;
	       	}
		}


		template<class It>
		matrix( size_type height, size_type width, It begin, It end )
			: _col_count( width )
			, _row_count( height )
			, _matrix_data( begin, end )
		{
			if( _matrix_data.size() != _col_count * _row_count ) {
			 	_col_count = 0;
				_row_count = 0;
				_matrix_data.clear();

                throw std::logic_error( "Error! Incorrect initialization matrix" );
			}
		}

		const value_type& operator()( size_type row, size_type col ) const
		{
			return _matrix_data[ _col_count * row + col ];
		}

		value_type& operator()( size_type row, size_type col )
		{
			return const_cast<value_type&>(
				const_cast<const matrix&>(*this)( row, col )
			);
		}

		friend bool operator== ( const matrix& lhs, const matrix& rhs )
		{
			_check_size_with_exception( lhs, rhs );

			for( size_type r = 0; r < lhs.row_count(); ++r )
				for( size_type c = 0; c < rhs.col_count(); ++c )
					if( lhs(r,c) != rhs(r,c) )
						return false;

			return true;
		}

		size_type col_count() const
		{
			return _col_count;
		}

		size_type row_count() const
		{
			return _row_count;
		}

		const matrix_type& data() const
		{
			return _matrix_data;
		}

	protected:
		size_type   _col_count;
		size_type   _row_count;
		matrix_type _matrix_data;

		static void _check_size_with_exception( const matrix& lhs, const matrix& rhs )
		{
			if( (lhs._row_count != rhs._col_count) | (lhs._col_count != rhs._row_count) ) {
				throw std::invalid_argument( "Matrix sizes mismatch" );
			}
		}

		void _check_cell_with_exception( size_type row, size_type col )
		{
			if( row >= _row_count || col >= _col_count ){
				throw std::invalid_argument( "Invalid cell index" );
			}
		}
	};


}
