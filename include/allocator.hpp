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

		typedef std::map<allocated_pointer_type, aligned_ponter_type>
		allocation_mapper_type;

		allocation_mapper_type& get_alloc_map()
		{
			static allocation_mapper_type alloc_map;
			return alloc_map;
		}
		
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
				(n * sizeof(value_type)) + aligned_size;

			allocated_pointer_type p =
				reinterpret_cast<allocated_pointer_type>
				(new byte[aligned_allocate_size]);

			size_type offset = reinterpret_cast<size_type>(p) % aligned_size;

			aligned_ponter_type aligned_pointer = p;
			if (offset != 0)
				aligned_pointer = reinterpret_cast<byte*>(p) +
					aligned_size - offset;
			
			get_alloc_map()[aligned_pointer] = p;

			return reinterpret_cast<pointer>(aligned_pointer);
		}

		void deallocate(pointer p, size_type /*n*/)
		{
			allocated_pointer_type allocate_pointer = get_alloc_map()[p];
			delete[] reinterpret_cast<byte*>(allocate_pointer);
			get_alloc_map().erase(p);
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
