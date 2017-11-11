#include <iostream>
#include <iterator>
#include <vector>



namespace machines {

	class finite_state_machine
	{
		using size_t = std::size_t;

		class characteristic_vector
		{
			using vector_t = std::vector<bool>;

		public:
			characteristic_vector(size_t length, std::initializer_list<size_t>& indexes) :
				vector( length )
			{
				for( size_t i = 0; i < length; ++i ) 
					(*this)[i] = false;

				for( auto it = std::begin(indexes); it != std::end(indexes); ++it )
					this->set( *it );
				
			}

			bool set(size_t index)
			{
				if( ! _is_valid(index) ) {
					return false;
				}

				(*this)[index] = true;
				return true;
			}

			bool reset(size_t index)
			{
				if( ! _is_valid(index) ) {
					return false;
				}
				
				(*this)[index] = false;
				return true;			
			}

			bool get(size_t index) const
			{
				if( ! _is_valid(index) ) {
					return false;
				}

				return (*this)[index];
			}

			const bool& operator[](size_t index) const
			{
				return vector[index];
			}

			bool& operator[](size_t index)
			{
				return const_cast<bool&>( 
					static_cast<const characteristic_vector&>(*this)[index] 
					);
			}


		protected:
			vector_t vector;

			bool _is_valid(size_t index) const
			{
				return index < vector.size();
			}
		};
	};
}