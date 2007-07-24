#ifndef RISA_ALLOCATOR_HPP_
#define RISA_ALLOCATOR_HPP_

#include "risa_types.hpp"

namespace risa_gl {
	/**
	 * @todo マルチスレッド初期化への対応
	 */
	template <typename types, size_t aligned_size>
	class aligned_allocator
	{
		friend class aligned_allocator_test;

	public:
		typedef types* pointer;
		typedef const types* const_pointer;
		typedef types& reference;
		typedef const types& const_reference;
		typedef types value_type;
		typedef size_t size_type;
		typedef ptrdiff_t differnce_type;

	private:
		typedef void* allocated_pointer_type;
		typedef void* aligned_ponter_type;

	public:
		template <typename U>
		struct rebind
		{
			typedef aligned_allocator<U, aligned_size> other;
		};

		pointer address(reference r)
		{
			return &r;
		}

		const_pointer address(const_reference s)
		{
			return &s;
		}

		pointer allocate(size_type n, const void* = 0) throw(std::bad_alloc)
		{
			const size_type aligned_allocate_size =
				aligned_size + (n * sizeof(value_type)) + aligned_size;

			allocated_pointer_type p =
				reinterpret_cast<allocated_pointer_type>
				(new byte[aligned_allocate_size]);

			size_type offset =
				(reinterpret_cast<size_type>(p)+aligned_size) % aligned_size;

			aligned_ponter_type aligned_pointer = p;
			if (offset != 0)
				aligned_pointer = reinterpret_cast<byte*>(p) +
					aligned_size - offset;
			
			/* save original allocation pointer. */
			size_type* org_pointer =
				reinterpret_cast<size_type*>(aligned_pointer);
			--org_pointer;
			*org_pointer = reinterpret_cast<size_type>(p);

			return reinterpret_cast<pointer>(aligned_pointer);
		}

		void deallocate(pointer p, size_type /*n*/)
		{
			size_type* org_pointer = reinterpret_cast<size_type*>(p);
			--org_pointer;
			byte* allocate_pointer = reinterpret_cast<byte*>(org_pointer);
			delete[] allocate_pointer;
		}

		size_type max_size() const
		{
			return 2UL * 1024 * 1024 * 1024 / sizeof(types);
		}

		bool operator==(const aligned_allocator&) const
		{
			return true;
		}

		bool operator!=(const aligned_allocator&) const
		{
			return false;
		}

		aligned_allocator()
		{}

		~aligned_allocator()
		{}

		aligned_allocator(const aligned_allocator&)
		{}

		void construct(pointer p, const_reference value)
		{
			new (p) types(value);
		}

		void destroy(pointer p)
		{
			p->~types();
		}
	};

};
#endif /* RISA_ALLOCATOR_HPP_ */
