#ifndef RISA_ALLOCATOR_HPP_
#define RISA_ALLOCATOR_HPP_

#include <risa_gl/risa_types.hpp>
#include <risa_gl/allocate_implements.hpp>
#include <memory>
#include <cassert>

namespace risa_gl {
	/**
	 */
	template <typename types,
			  size_t aligned_size,
			  typename allocate_implement_type =
			  default_allocate_implements>
	class aligned_allocator
	{
		friend class aligned_allocator_test;

	private:
		typedef allocate_implement_type impl_type;

	public:
		typedef types* pointer;
		typedef const types* const_pointer;
		typedef types& reference;
		typedef const types& const_reference;
		typedef types value_type;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;

		enum
		{
			alignment_size = aligned_size
		};

	private:
		typedef void* allocated_pointer_type;
		typedef void* aligned_pointer_type;

	public:
		template <typename U>
		struct rebind
		{
			typedef 
			aligned_allocator<U, aligned_size, allocate_implement_type> other;
		};

		pointer address(reference r)
		{
			return &r;
		}

		const_pointer address(const_reference s)
		{
			return &s;
		}

		pointer allocate(size_type n,
						 std::allocator<void>::const_pointer = 0)
			throw(std::bad_alloc)
		{
			const size_type pointer_size = sizeof(void*);
			const size_type aligned_allocate_size =
				pointer_size + (n * sizeof(value_type)) + aligned_size;

			allocated_pointer_type p =
				reinterpret_cast<allocated_pointer_type>
				(impl_type::allocate(aligned_allocate_size));

			size_type offset =
				(reinterpret_cast<size_type>(p)+pointer_size) % aligned_size;

			aligned_pointer_type aligned_pointer =
				reinterpret_cast<aligned_pointer_type>
				(reinterpret_cast<byte*>(p) +
				 pointer_size + aligned_size - offset);
			
			/* save original allocation pointer. */
			size_type pointer_save_offset = 
				(reinterpret_cast<size_type>(aligned_pointer) -
				 pointer_size) % pointer_size;
			
			assert((reinterpret_cast<size_type>(aligned_pointer) -
					 reinterpret_cast<size_type>(p)) >=
					(pointer_save_offset + pointer_size));

			*reinterpret_cast<void**>(
				reinterpret_cast<byte*>(aligned_pointer) -
				(pointer_save_offset + pointer_size)) = p;

			return reinterpret_cast<pointer>(aligned_pointer);
		}

		void deallocate(pointer aligned_pointer, size_type /*n*/)
		{
			size_type pointer_size = sizeof(void*);
			size_type pointer_save_offset = 
				(reinterpret_cast<size_type>(aligned_pointer) -
				 pointer_size) % pointer_size;
			
			byte* allocate_pointer =
				*reinterpret_cast<byte**>(
					reinterpret_cast<byte*>(aligned_pointer) -
					(pointer_save_offset + pointer_size));

			impl_type::deallocate(allocate_pointer);
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

		aligned_allocator() throw()
		{}

		aligned_allocator(const aligned_allocator&) throw()
		{}

		template <typename other>
		aligned_allocator(const other&) throw()
		{}

		~aligned_allocator() throw()
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

	template <typename types,
			  typename allocate_implement_type =
			  default_allocate_implements>
	class normal_allocator
	{
	private:
		typedef allocate_implement_type impl_type;

	public:
		typedef types* pointer;
		typedef const types* const_pointer;
		typedef types& reference;
		typedef const types& const_reference;
		typedef types value_type;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;

		enum
		{
			alignment_size = 1
		};

	public:
		template <typename U>
		struct rebind
		{
			typedef normal_allocator<U, allocate_implement_type> other;
		};

		pointer address(reference r)
		{
			return &r;
		}

		const_pointer address(const_reference s)
		{
			return &s;
		}

		pointer allocate(size_type n,
						 std::allocator<void>::const_pointer = 0)
			throw(std::bad_alloc)
		{
			return reinterpret_cast<pointer>
				(impl_type::allocate(n));
		}

		void deallocate(pointer p, size_type /*n*/)
		{
			impl_type::deallocate(reinterpret_cast<byte*>(p));
		}

		size_type max_size() const
		{
			return 2UL * 1024 * 1024 * 1024 / sizeof(types);
		}

		bool operator==(const normal_allocator&) const
		{
			return true;
		}

		bool operator!=(const normal_allocator&) const
		{
			return false;
		}

		normal_allocator() throw()
		{}

		normal_allocator(const normal_allocator&) throw()
		{}

		template <typename other>
		normal_allocator(const other&) throw()
		{}

		~normal_allocator() throw()
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

}
#endif /* RISA_ALLOCATOR_HPP_ */
