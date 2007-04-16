#ifndef RISA_ITERATOR_TRAITS_HPP_
#define RISA_ITERATOR_TRAITS_HPP_

#include "exception.hpp"

namespace risa_gl
{
	/**
	 * 対象ポインタがアライメント境界に整列されているかを調べる
	 * @param alignment 境界バイト数
	 * @param ptr 調べる対象ポインタ
	 * @return 整列されていればtrue
	 */
	template <typename pixel_type, size_t alignment>
	class iterator_adapter
	{
	public:
		typedef pixel_type pixel_t;
		typedef sequencial_iterator<pixel_t>  seq_itor_t;
		typedef aligned_iterator<pixel_t, alignment> align_itor_t;

		static bool is_alignment(const void* ptr)
		{
			return (reinterpret_cast<size_t>(ptr) % alignment) == 0;
		}

		static seq_itor_t to_sequencial(align_itor_t& itor)
		{
			return seq_itor(&*itor);
		}

		static align_itor_t to_alignment(seq_itor_t& itor)
		{
			if (!is_alignment(itor.get()))
				throw alignment_error("bad iterator alignment.");

			return align_itor_t(
				reinterpret_cast<typename align_itor_t::pointer_t>(&*itor));
		}
	};
};

#endif /* RISA_ITERATOR_TRAITS_HPP_ */
