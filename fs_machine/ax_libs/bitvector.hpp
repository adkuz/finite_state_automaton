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

		static const byte_t byte_size = 8; 

	public:
		bitvector( size_t size ) 
			: _lenght( size )
			, _bitvector( _bytes_count(size) )
		{
			for (auto& byte : _bitvector)
				byte = byte_t( 0 );
		}

		template<class T>
		bitvector( std::initializer_list<T>& objects ) 
			: _lenght( objects.size() )
			, _bitvector( _bytes_count(objects.size()) )
		{
			for (auto& byte : _bitvector)
				byte = byte_t( 0 );
		}

		size_t length() const
		{
			return _lenght;
		}

		bool operator[]( size_t index ) const
		{
			auto [ byte_index, bit_index ] = _byte_and_bit_indexes( index );

			return ( _bitvector[byte_index] & _mask( bit_index ) ) ? true : false;
		}

		bool set( size_t index )
		{
			_check_index( index );

			auto [ byte_index, bit_index ] = _byte_and_bit_indexes( index );
			
			_bitvector[byte_index] |= _mask( bit_index );
		}

		bool reset( size_t index )
		{
			_check_index( index );

			auto [ byte_index, bit_index ] = _byte_and_bit_indexes( index );
			
			_bitvector[byte_index] ^= _mask( bit_index );
		}


	protected:
		size_t _lenght;
		bits_t _bitvector;

		void _check_index( size_t index ) 
		{
			if( index >= _lenght ) {
				throw std::out_of_range("Index is too high");
			}
		}
		
		static size_t _bytes_count( size_t bits_count )
		{
			return static_cast<size_t>( ceil(bits_count / byte_size) );
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

	string_t to_string(const bitvector& bv, const char* separator = " ",  size_t block_size = 4)
	{
		string_t result;
		string_t sep = string_t(separator);

		auto length = bv.length();
		for( size_t i = 0; i < length; ++i ) {
			result += ( bv[i] ) ? '1' : '0';
			if ( (i + 1) % block_size == 0 )
				result += sep;
		}

		return result;
	}



}