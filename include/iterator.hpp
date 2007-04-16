#ifndef RISA_ITERATOR_HPP_
#define RISA_ITERATOR_HPP_

#include "risa_types.hpp"

namespace risa_gl
{
	template <typename ValueType>
	class sequencial_iterator
	{
	public:
		typedef ValueType  value_type;
		typedef ValueType* pointer_type;
		typedef ValueType& reference_type;

	private:
		pointer_type itor;

	public:
		sequencial_iterator():
			itor()
		{}

		sequencial_iterator(pointer_type pointer):
			
		sequencial_iterator(const sequencial_iterator& source):
			itor(source.itor)
		{}

		~sequencial_iterator()
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

		sequencial_iterator& operator++()
		{
			++itor;
			return *this;
		}

		sequencial_iterator operator++(int)
		{
			sequencial_iterator result(*this);
			++itor;
			return result;
		}

		bool operator==(const sequencial_iterator& rhs) const
		{
			return this->itor == rhs.itor;
		}

		bool operator!=(const sequencial_iterator& rhs) const
		{
			return !this->operator==(rhs);
		}

	};
	
};

#endif /* RISA_ITERATOR_HPP_ */
