#pragma once

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

#include "types.h"


namespace ax {

	class bitvector
	{
	public:
		using byte_t = std::uint8_t;
		using bits_t = std::vector<byte_t>;
		using size_t = std::size_t;

		using byte_and_bit_indexes_t = std::pair<size_t, byte_t>;

		static const size_t byte_size = 8; 

	public:
		bitvector( size_t size ) 
			: _lenght( size )
			, _byte_vector( _bytes_count(size) )
		{
			for( auto& byte : _byte_vector )
				byte = byte_t( 0 );
		}

		bitvector( size_t size, std::initializer_list<size_t>& bits ) 
			: bitvector( size )
		{
			for( auto& bit : bits )
				this->set( bit );
		}

		bitvector( const bitvector& obj )
			: _lenght( obj._lenght )
			, _byte_vector( obj._byte_vector )
		{}

		bitvector( bitvector&& obj )
			: _lenght( obj._lenght )
			, _byte_vector( std::move(obj._byte_vector) )
		{
			if( obj._byte_vector.empty() ) {
				obj._lenght = 0;
			}
		}

		bitvector& operator= ( const bitvector& obj )
		{
			if( this != &obj ) {
				this->_lenght = obj._lenght;
				this->_byte_vector = obj._byte_vector;
			}
			return *this;
		}

		bitvector& operator= ( bitvector&& obj )
		{
			if( this != &obj ) {
				this->_lenght = obj._lenght;
				this->_byte_vector = std::move( obj._byte_vector );

				if( obj._byte_vector.empty() ) {
					obj._lenght = 0;
				}
			}
			return *this;
		}

		size_t length() const
		{
			return _lenght;
		}

		bool operator[]( size_t index ) const
		{
			_check_index( index );
			
			auto [ byte_index, bit_index ] = _byte_and_bit_indexes( index );

			return ( _byte_vector[byte_index] & _mask( bit_index ) ) ? true : false;
		}

		bool set( size_t index )
		{
			_check_index( index );

			auto [ byte_index, bit_index ] = _byte_and_bit_indexes( index );
			
			_byte_vector[byte_index] |= _mask( bit_index );

			return true;
		}

		bool reset( size_t index )
		{
			_check_index( index );

			auto [ byte_index, bit_index ] = _byte_and_bit_indexes( index );
			
			_byte_vector[byte_index] &= ( _mask( bit_index ) ^ 0xff );

			return true;
		}

		operator bool() const
		{
			for( auto byte : this->_byte_vector ) {
				if( byte )
					return true;
			}

			return false;
		}

		bitvector& operator &= ( const bitvector& rhs )
		{
			_check_legth( rhs.length() );

			auto bytes_count = this->_byte_vector.size();

			for( size_t i = 0; i < bytes_count; ++i ){
				this->_byte_vector[i] &= rhs._byte_vector[i];
			}
			return *this;
		}

		bitvector& operator |= ( const bitvector& rhs )
		{
			_check_legth( rhs.length() );
			
			auto bytes_count = this->_byte_vector.size();

			for( size_t i = 0; i < bytes_count; ++i ){
				this->_byte_vector[i] |= rhs._byte_vector[i];
			}
			return *this;
		}

		bitvector& operator ^= ( const bitvector& rhs )
		{
			_check_legth( rhs.length() );

			auto bytes_count = this->_byte_vector.size();

			for( size_t i = 0; i < bytes_count; ++i ){
				this->_byte_vector[i] ^= rhs._byte_vector[i];
			}
			return *this;
		}

		friend bitvector operator & ( const bitvector& lhs, const bitvector& rhs )
		{
			auto result( lhs );
			result &= rhs;
			return result;
		}

		friend bitvector operator | ( const bitvector& lhs, const bitvector& rhs )
		{
			auto result( lhs );
			result |= rhs;
			return result;
		}

		friend bitvector operator ^ ( const bitvector& lhs, const bitvector& rhs )
		{
			auto result( lhs );
			result ^= rhs;
			return result;
		}

		friend bool operator == ( const bitvector& lhs, const bitvector& rhs )
		{
			return ( lhs ^ rhs ) ? false : true;
		}

		friend bool operator != ( const bitvector& lhs, const bitvector& rhs )
		{
			return ( lhs ^ rhs ) ? true : false;
		}

		friend std::ostream& operator << ( std::ostream& ostr, const bitvector& bv )
		{
			ostr << "[  ";
			for( size_t i = 0; i < bv._byte_vector.size(); ++i ) {
				ostr << uint(bv._byte_vector[i]) << "   ";
			}
			return ostr << "]:" << bv._byte_vector.size() << ":" << bv.length();
		}

	protected:
		size_t _lenght;
		bits_t _byte_vector;

		void _check_index( size_t index ) const
		{
			if( index >= _lenght ) {
				throw std::out_of_range("Index is too high");
			}
		}

		void _check_legth( size_t length )
		{
			if( length != this->_lenght ) {
				throw std::invalid_argument("Lengths mismatch");
			}
		}
		
		static size_t _bytes_count( size_t bits_count )
		{
			return static_cast<size_t>( ceil(float(bits_count) / byte_size) );
		}

		static byte_t _mask( byte_t bit_index )
		{
			return (1 << bit_index);
		}

		static byte_and_bit_indexes_t _byte_and_bit_indexes( size_t index )
		{
			return byte_and_bit_indexes_t( index / byte_size, index % byte_size );
		}
	};

	string_t to_string(const bitvector& bv, const char* separator = " ",  size_t block_size = 4, 
		const char* zero = "0", const char* unit = "1")
	{
		string_t result;
		string_t sep = string_t(separator);

		auto length = bv.length();
		for( size_t i = 0; i < length - 1; ) {
			result += ( bv[i] ) ? unit : zero;
			if ( (++i) % block_size == 0 )
				result += sep;
		}

		result += ( bv[length - 1] ) ? unit : zero;

		return result;
	}



}