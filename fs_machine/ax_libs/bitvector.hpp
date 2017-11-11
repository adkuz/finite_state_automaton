#include <cmath>
#include <iostream>
#include <vector>


namespace ax {

	class bitvector
	{
	public:
		using byte_t = std::uint8_t;
		using bits_t = std::vector<byte_t>;
		using size_t = std::size_t;

	public:
		bitvector(size_t size) : _bitvector( bytes_count(size) ), _lenght( size )
		{
			for (auto& byte : _bitvector)
				byte = byte_t( 0 );
		}

		size_t length() const
		{
			return _lenght;
		}

		friend std::ostream& operator<< (std::ostream& ostr, const bitvector& bitvec)
		{
			for( size_t mask = 1 << byte_size - 1, i = 0; i < bitvec._lenght; ++i ) {

			}
		}

	protected:
		size_t _lenght;
		bits_t _bitvector;

		static const byte_size = 8; 
		static size_t bytes_count(size_t bits_count)
		{
			return static_cast<size_t>( ceil(bits_count / byte_size) );
		}
	};
}