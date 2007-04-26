#ifndef RISA_ITERATOR_HPP_
#define RISA_ITERATOR_HPP_

#include "risa_types.hpp"

namespace risa_gl
{
	template <typename ValueType>
	class sequential_iterator
	{
	public:
		typedef ValueType  value_type;
		typedef ValueType* pointer_type;
		typedef ValueType& reference_type;

	private:
		pointer_type itor;

	public:
		sequential_iterator():
			itor()
		{}

		sequential_iterator(pointer_type pointer):
			itor(pointer)
		{}
			
		sequential_iterator(const sequential_iterator& source):
			itor(source.itor)
		{}

		~sequential_iterator()
		{}

		reference_type operator*()
		{
			return *itor;
		}

		const reference_type operator*() const
		{
			return *itor;
		}

		pointer_type operator->()
		{
			return itor;
		}

		const pointer_type operator->() const
		{
			return itor;
		}

		sequential_iterator& operator++()
		{
			++itor;
			return *this;
		}

		sequential_iterator operator++(int)
		{
			sequential_iterator result(*this);
			++itor;
			return result;
		}

		bool operator==(const sequential_iterator& rhs) const
		{
			return this->itor == rhs.itor;
		}

		bool operator!=(const sequential_iterator& rhs) const
		{
			return !this->operator==(rhs);
		}

	};
	
};

#endif /* RISA_ITERATOR_HPP_ */
