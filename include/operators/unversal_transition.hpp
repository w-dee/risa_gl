#ifndef RISA_UNIVERSAL_TRANSITION_HPP_
#define RISA_UNIVERSAL_TRANSITION_HPP_


template <typename src_itor_t, typename alpha_itor_t, typename dest_itor_t>
class universal_transition
{
public:
	typedef src_itor_t source_iterator_type;
	typedef alpha_itor_t alpha_iterator_type;
	typedef dest_itor_t destination_iterator_type;

	void operator()(source_iterator_type& head,
					source_iterator_type& tail,
					alpha_iterator_type& blend_factor,
					destination_iterator_type& dest_head)
	{
		while (head != tail)
			*dest_head++ = *head++ * *blend_factor++;
	}
};


#ifdef __SSE2__
template <typename src_itor_t, typename alpha_itor_t, typename dest_itor_t>
class sse2_universal_transition
{
public:
	typedef src_itor_t source_iterator_type;
	typedef alpha_itor_t alpha_iterator_type;
	typedef dest_itor_t destination_iterator_type;

	void operator()(source_iterator_type& head,
					source_iterator_type& tail,
					alpha_iterator_type& blend_factor,
					destination_iterator_type& dest_head)
	{
		__m128i packed_blend;
		while (head != tail)
		{
			*dest_head++ = *head++ * *blend_factor++;
		}
	}
};
#endif /* __SSE2__ */

#endif /* RISA_UNIVERSAL_TRANSITION_HPP_ */
