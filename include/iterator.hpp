#ifndef RISA_ITERATOR_HPP_
#define RISA_ITERATOR_HPP_

#include <risa_types.hpp>
#include <exception.hpp>
#include <iterator>
#include <cassert>

namespace risa_gl
{
	/**
	 * シーケンシャルイテレータ
	 * @param ValueType デリファレンスの型
	 */
	template <typename ValueType>
	class sequential_iterator
	{
	public:
		typedef ValueType  value_type;
		typedef ValueType* pointer;
		typedef ValueType& reference;
		typedef const ValueType& const_reference;
		typedef std::random_access_iterator_tag iterator_category;
		typedef ptrdiff_t difference_type;

		enum {
			element_size = sizeof(value_type)
		};

	private:
		pointer itor;

	public:
		sequential_iterator():
			itor()
		{}

		sequential_iterator(pointer pointer):
			itor(pointer)
		{}
			
		sequential_iterator(const sequential_iterator& source):
			itor(source.itor)
		{}

		~sequential_iterator()
		{}

		reference operator*()
		{
			return *itor;
		}

		const_reference operator*() const
		{
			return *itor;
		}

		pointer operator->()
		{
			return itor;
		}

		const pointer operator->() const
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

		sequential_iterator& operator--()
		{
			--itor;
			return *this;
		}

		sequential_iterator operator--(int)
		{
			sequential_iterator result(*this);
			--itor;
			return *this;
		}

		sequential_iterator operator+(const int difference)
		{
			itor += difference;
			return *this;
		}

		sequential_iterator operator-(const int difference)
		{
			itor -= difference;
			return *this;
		}

		bool operator==(const sequential_iterator& rhs) const
		{
			return this->itor == rhs.itor;
		}

		bool operator!=(const sequential_iterator& rhs) const
		{
			return !this->operator==(rhs);
		}

		bool operator<(const sequential_iterator& rhs) const
		{
			return this->itor < rhs.itor;
		}
	};

	/**
	 * アライメント境界にそろえられたイテレータ
	 * @todo ValueTypeをメモリチャンク型とか作ってそっちをパラメタにし
	 * たほうがいいかな
	 */
	template <typename ValueType, size_t FragmentsSize>
	class alignment_iterator
	{
	public:
		enum {
			fragments_size = FragmentsSize
		};
		enum {
			element_size = FragmentsSize
		};


		typedef ValueType value_type;
		typedef ValueType* pointer;
		typedef ValueType& reference;
		typedef const ValueType& const_reference;
		typedef std::random_access_iterator_tag iterator_category;
		typedef ptrdiff_t difference_type;

	private:
		pointer itor;

	public:
		alignment_iterator():
			itor()
		{}

		alignment_iterator(pointer pointer):
			itor(pointer)
		{
			if (reinterpret_cast<size_t>(pointer) % fragments_size)
				throw alignment_error();
		}
			
		alignment_iterator(const alignment_iterator& source):
			itor(source.itor)
		{}

		~alignment_iterator()
		{}

		reference operator*()
		{
			return *itor;
		}

		const_reference operator*() const
		{
			return *itor;
		}

		pointer operator->()
		{
			return itor;
		}

		const pointer operator->() const
		{
			return itor;
		}

		alignment_iterator& operator++()
		{
			itor = reinterpret_cast<pointer>(
				reinterpret_cast<byte*>(itor) + fragments_size);
			return *this;
		}

		alignment_iterator operator++(int)
		{
			alignment_iterator result(*this);
			++itor;
			return result;
		}

		alignment_iterator& operator--()
		{
			itor = reinterpret_cast<pointer>(
				reinterpret_cast<byte*>(itor) - fragments_size);
			return *this;
		}

		alignment_iterator operator--(int)
		{
			alignment_iterator result(*this);
			--itor;
			return result;
		}

		bool operator==(const alignment_iterator& rhs) const
		{
			return this->itor == rhs.itor;
		}

		bool operator!=(const alignment_iterator& rhs) const
		{
			return !this->operator==(rhs);
		}

		bool operator<(const alignment_iterator& rhs) const
		{
			return this->itor < rhs.itor;
		}
	};

	template <typename BaseType, typename InterpolateType>
	class transform_iterator
	{
	public:
		typedef BaseType value_type;
		typedef BaseType* pointer;
		typedef const BaseType* const_pointer;
		typedef BaseType& reference;
		typedef const BaseType& const_reference;
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef ptrdiff_t difference_type;

		typedef InterpolateType interpolate_type;

	private:
		pointer current;

	public:
		transform_iterator():
			current()
		{}

		transform_iterator(const_pointer point):
			current(point)
		{}
		
		transform_iterator(const transform_iterator& src):
			current(src.curent)
		{}

		~transform_iterator()
		{}

		transform_iterator& operator=(const transform_iterator& src)
		{
			if (this != &src)
				current = src.current;

			return *this;
		}

		transform_iterator& operator++()
		{
			++current;
			return *this;
		}

		transform_iterator operator++(int)
		{
			transform_iterator result(*this);
			++(*this);
			return result;
		}

		transform_iterator& operator--()
		{
			--current;
			return *this;
		}

		transform_iterator operator--(int)
		{
			transform_iterator result(*this);
			--(*this);
			return result;
		}

		reference operator*()
		{
			return *current;
		}

		const reference operator*() const
		{
			return *current;
		}

		pointer operator->()
		{
			return current;
		}

		const pointer operator->() const
		{
			return current;
		}
	};
}

#endif /* RISA_ITERATOR_HPP_ */
