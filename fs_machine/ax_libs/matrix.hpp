#pragma once

#include <exception>
#include <functional>
#include <iostream>
#include <vector>



namespace types {

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
			: _width( width )
			, _height( height )
			, _matrix_data( width * height, default_value )
		{}

		matrix( size_type height, size_type width, init_func_type function )
			: _width( width )
			, _height( height )
			, _matrix_data( width * height )
		{
			for( size_type row = 0; row < _height; ++row )
				for( size_type col = 0; col < _width; ++col )
					(*this)( row, col ) = function( row, col );
		}	


		matrix( const matrix& obj )
            : _width( obj._width )
            , _height( obj._height )
            , _matrix_data( obj._matrix_data )
        {}

		matrix( matrix&& obj )
            : _width( 0 )
            , _height( 0 )
            , _matrix_data()
		{
			std::swap( _height, obj._height );
			std::swap( _width, obj._width );
			std::swap( _matrix_data, obj._matrix_data );
		}

		matrix& operator=( const matrix& obj ) 
		{
            if ( this != &obj )
            {
                _height = obj._height;
                _width = obj._width;
                _matrix_data = obj._matrix_data;
            }
            return  *this;
		}

		matrix& operator=( matrix&& obj )
		{
            if ( this != &obj )
            {
                std::swap( _height, obj._height);
				std::swap( _width, obj._width);
				std::swap( _matrix_data, obj._matrix_data);
            }
            return  *this;
		}

		matrix( std::initializer_list<std::initializer_list<value_type>> rows )
		{
            _height = rows.size();

            if( _height ) {

	          	_width  = rows.begin()->size();

	            for ( auto& row : rows )
	            {
	                if ( row.size() != _width )
					{
						_height = 0;
						_width = 0;
						_matrix_data.clear();

						throw std::logic_error( "Error! Incorrect initialization matrix" );
					}
	                _matrix_data.insert( _matrix_data.end(), std::begin(row), std::end(row) );
	            }
	       	}
	       	else {
	       		_width = 0;
	       	}
		}


		template<class It>
		matrix( size_type height, size_type width, It begin, It end )
			: _width( width )
			, _height( height )
			, _matrix_data( begin, end )
		{
			if( _matrix_data.size() != _width * _height ) {
				_width = 0;
				_height = 0;
				_matrix_data.clear();
                
                throw std::logic_error( "Error! Incorrect initialization matrix" );
			}
		}

		const value_type& operator()( size_type row, size_type col ) const
		{
			return _matrix_data[ _width * row + col ];
		}

		value_type& operator()( size_type row, size_type col )
		{
			return const_cast<value_type&>( const_cast<const matrix&>(*this)( row, col ) );
		}

		size_type width() const
		{
			return _width;
		}

		size_type height() const
		{
			return _height;
		}

		const matrix_type& data() const
		{
			return _matrix_data;
		}

		matrix& operator+=( const matrix& rhs )
        {
        	_check_size_with_exception( *this, rhs );

            for( size_t i = 0; i < this->_matrix_data.size(); ++i )
            {
                this->_matrix_data[i] += rhs._matrix_data[i];
            }
            return *this;
        }

        friend bool operator==( const matrix& lhs, const matrix& rhs )
        {
        	_check_size_with_exception( lhs, rhs );

        	for( size_t i = 0; i < lhs._matrix_data.size(); ++i )
        		if( lhs._matrix_data[i] != rhs._matrix_data[i] )
        			return false;

        	return true;
        }

        friend bool operator!=( const matrix& lhs, const matrix& rhs )
        {
        	_check_size_with_exception( lhs, rhs );

        	for( size_t i = 0; i < lhs._matrix_data.size(); ++i )
        		if( lhs._matrix_data[i] != rhs._matrix_data[i] )
        			return true;

        	return false;
        }

	    friend matrix operator+( const matrix& lhs, const matrix& rhs )
	    {
	        auto tmp = lhs;
	        tmp += rhs;
	        return tmp;
	    }
	     
	    friend matrix operator*( const matrix& lhs, const matrix& rhs )
	    {
	    	if( lhs.width() != rhs.height() )
				throw std::invalid_argument( "Matrix sizes mismatch" );

			size_type magic_number = lhs.width();

	        return matrix( lhs.height(), rhs.width(), 
	        				[magic_number, &lhs, &rhs]( auto r, auto c )
	        				{
	        					value_type val( 0 );
	        					for( size_type i = 0; i < magic_number; ++i )
	        						val += lhs( r, i ) * rhs( i, c );

	        					return val;
	        				}
	        	   );
	    }
	    

	protected:
		size_type   _width;
		size_type   _height;
		matrix_type _matrix_data;

		static void _check_size_with_exception( const matrix& lhs, const matrix& rhs )
		{
			if( (lhs._width != rhs._width) | (lhs._height != rhs._height) ) {
				throw std::invalid_argument( "Matrix sizes mismatch" );
			}
		}
	};
}
