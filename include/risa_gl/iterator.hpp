#ifndef RISA_ITERATOR_HPP_
#define RISA_ITERATOR_HPP_

#include <risa_gl/risa_types.hpp>
#include <risa_gl/exception.hpp>
#include <risa_gl/math/vector.hpp>
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

	template <typename PixelStoreType,
			  template <typename> class InterpolateType>
	class linear_iterator
	{
	public:
		typedef PixelStoreType pixel_store_type;
		typedef typename pixel_store_type::pixel_type pixel_type;
		typedef InterpolateType<pixel_store_type> interpolate_type;
		typedef typename interpolate_type::proxy_type value_type;

		typedef std::bidirectional_iterator_tag iterator_category;
		typedef ptrdiff_t difference_type;

	private:
		typedef risa_gl::math::vector2 vector_type;
		const interpolate_type& interpolator;
		
		const int grain_size;
		int current;

	public:
		linear_iterator(const pixel_store_type& store,
						const vector_type& head,
						const vector_type& tail,
						const int grain_size_):
			interpolator(store, grain_size_, head, tail),
			grain_size(grain_size_),
			current(0)
		{}

		linear_iterator(const linear_iterator& src):
			interpolator(src.interpolator),
			grain_size(src.grain_size),
			current(src.current)
		{}

		~linear_iterator()
		{}

		linear_iterator& operator++()
		{
			++current;
			return *this;
		}

		linear_iterator operator++(int)
		{
			linear_iterator result(*this);
			++(*this);
			return result;
		}

		linear_iterator& operator--()
		{
			--current;
			return *this;
		}

		linear_iterator operator--(int)
		{
			linear_iterator result(*this);
			--(*this);
			return result;
		}

		const value_type& operator*() const
		{
			return
				interpolator.create_proxy(
					interpolator.interpolate(
						static_cast<float>(current)/grain_size));
		}

		const value_type* operator->() const
		{
			return 
				interpolator.get_proxy(
					interpolator.interpolate(
						static_cast<float>(current)/grain_size));
		}
	};
}

#endif /* RISA_ITERATOR_HPP_ */
