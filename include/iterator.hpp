#ifndef RISA_ITERATOR_HPP_
#define RISA_ITERATOR_HPP_

#include <risa_types.hpp>
#include <exception.hpp>
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
		typedef ValueType* pointer_type;
		typedef ValueType& reference_type;

		enum {
			element_size = sizeof(value_type)
		};

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
		typedef ValueType* pointer_type;
		typedef ValueType& reference_type;

	private:
		pointer_type itor;

	public:
		alignment_iterator():
			itor()
		{}

		alignment_iterator(pointer_type pointer):
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

		alignment_iterator& operator++()
		{
			itor = reinterpret_cast<pointer_type>(
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
			itor = reinterpret_cast<pointer_type>(
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
	};

	template <typename AlgorithmType>
	class transfor_iterator
	{
	public:
		typedef AlgorithmType reverse_projector_type;

		typedef reverse_projector_type::value_type  value_type;
		typedef reverse_projector_type::pointer_type pointer_type;
		typedef reverse_projector_type::reference_type reference_type;

	private:
		reverse_projector_type projector;

	public:
		transform_iterator(const reverse_projector_type& projector_):
			projector(projector_)
		{}
		
		~transform_iterator()
		{}

		transform_iterator& operator++()
		{
			projector.next();
			return *this;
		}

		transform_iterator operator++(int)
		{
			transform_iterator result(projector);
			projector.next();
			return result;
		}

		transform_iterator& operator--()
		{
			projector.previous();
			return *this;
		}

		transform_iterator operator--(int)
		{
			transform_iterator result(projector);
			projector.previous();
			return result;
		}

		reference_type operator*()
		{
			return projector.get_reference();
		}

		const reference_type operator*() const
		{
			return projector.get_reference();
		}

		pointer_type operator->()
		{
			return projector.get_pointer();
		}

		const pointer_type operator->() const
		{
			return projector.get_pointer();
		}
	};
}

#endif /* RISA_ITERATOR_HPP_ */
