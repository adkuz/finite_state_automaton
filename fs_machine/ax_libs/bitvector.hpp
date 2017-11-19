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

		static const byte_t byte_size = 8; 

	public:
		bitvector( size_t size ) 
			: _lenght( size )
			, _bitvector( bytes_count(size) )
		{
			for (auto& byte : _bitvector)
				byte = byte_t( 0 );
		}

		template<class T>
		bitvector( std::initializer_list<T>& objects ) 
			: _lenght( objects.size() )
			, _bitvector( bytes_count(objects.size()) )
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
			size_t byte_index = index / byte_size;
			byte_t bit_index = index % byte_size;

			byte_t bit_mask = 1 << bit_index;

			return ( _bitvector[byte_index] & bit_mask ) ? true : false;
		}

		bool set( size_t index )
		{
			_check_index( index );

			byte_t bit_mask = 1 << bit_index;
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
		
		static size_t bytes_count( size_t bits_count )
		{
			return static_cast<size_t>( ceil(bits_count / byte_size) );
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