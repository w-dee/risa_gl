#ifndef RISA_UNIVERSAL_TRANSITION_HPP_
#define RISA_UNIVERSAL_TRANSITION_HPP_


template <typename src_itor_t,
		  typename alpha_itor_t,
		  typename dest_itor_t,
		  typename color_t>
class universal_transition
{
public:
	typedef src_itor_t source_iterator_type;
	typedef alpha_itor_t alpha_iterator_type;
	typedef dest_itor_t destination_iterator_type;
	typedef color_t color_type;

	void operator()(source_iterator_type head,
					source_iterator_type tail,
					alpha_iterator_type blend_factor,
					destination_iterator_type dest_head)
	{
		while (head != tail)
		{
			const int factor = blend_factor++->get_y();
			*dest_head++ = color_type(head->get_r() * factor / 255,
									  head->get_g() * factor / 255,
									  head->get_b() * factor / 255,
									  head->get_a() * factor / 255);
			++head;
		}
	}
};


#ifdef __SSE2__
#include <emmintrin.h>

template <typename src_itor_t, typename alpha_itor_t, typename dest_itor_t>
class sse2_universal_transition
{
public:
	typedef src_itor_t source_iterator_type;
	typedef alpha_itor_t alpha_iterator_type;
	typedef dest_itor_t destination_iterator_type;

	void operator()(source_iterator_type head,
					source_iterator_type tail,
					alpha_iterator_type blend_factor,
					destination_iterator_type dest_head)
	{
		while (head != tail)
		{
			__m128i packed_blend =
				_mm_setr_epi16((blend_factor+0)->get_y(), (blend_factor+0)->get_y(),
							   (blend_factor+0)->get_y(), (blend_factor+0)->get_y(),
							   (blend_factor+1)->get_y(), (blend_factor+1)->get_y(),
							   (blend_factor+1)->get_y(), (blend_factor+1)->get_y(),
							   (blend_factor+2)->get_y(), (blend_factor+2)->get_y(),
							   (blend_factor+2)->get_y(), (blend_factor+2)->get_y(),
							   (blend_factor+3)->get_y(), (blend_factor+3)->get_y(),
							   (blend_factor+3)->get_y(), (blend_factor+3)->get_y());
			__m128i src = _mm_load_si128(reinterpret_cast<__m128i*>(&*head));
			__m128i dest = _mm_mulhi_epu16(src, packed_blend);
			_mm_store_si128(reinterpret_cast<__m128i*>(&*dest_head), dest);
			
			++head;
			++dest_head;
			blend_factor += 4;
		}
	}
};
#endif /* __SSE2__ */

#endif /* RISA_UNIVERSAL_TRANSITION_HPP_ */
