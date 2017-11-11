#include <iostream>



class finite_state_machine
{
	using size_t = std::size_t;

	class characteristic_vector
	{
		using vector_t = std::vector<bool>;
	public:
		characteristic_vector(std::initializer_list<size_t>& index_list)
		{

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

		bool operator[](size_t index) const
		{
			return vector[index];
		}

		vector_t::value_type& operator[](size_t index)
		{
			return vector[index];
		}


	protected:
		using vector_t vector;

		bool _is_valid(index) const
		{
			return index < vector.size();
		}
	}
}