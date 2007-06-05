#ifndef RISA_PRIMITIVE_BLEND_HPP_
#define RISA_PRIMITIVE_BLEND_HPP_

#include "saturation.hpp"

namespace risa_gl {
	namespace primitive {
		
		/**
		 * アルファ合成
		 */
		class blend
		{
		public:
			template <typename src_iterator_t,
					  typename dest_iterator_t>
			operator()(src_iterator_t& head,
					   src_iterator_t& tail,
					   dest_iterator_t& dest_head)
			{
				while (head != tail)
				{
					dest_head->set_r(
						saturation(head->get_r() * (255 - dest->get_a()) +
								   dest_head->get_r() * dest_head->get_a()));
					dest_head->set_g(
						saturation(head->get_g() * (255 - dest->get_a()) +
								   dest_head->get_g() * dest_head->get_a()));
					dest_head->set_b(
						saturation(head->get_b() * (255 - dest->get_a()) +
								   dest_head->get_b() * dest_head->get_a()));
					/* アルファ値の扱いどうするのさ？ */
//					dest_head->set_a();
				}
			}
		};

		/**
		 * 加算合成
		 */
		class add_blend
		{
		public:
			template <typename src_iterator_t,
					  typename dest_iterator_t>
			operator()(src_iterator_t& head,
					   src_iterator_t& tail,
					   dest_iterator_t& dest_head)
			{
				while (head != tail)
				{
					dest_head->set_r(
						saturation(head->get_r() +
								   dest_head->get_r() * dest_head->get_a()));
					dest_head->set_g(
						saturation(head->get_g() +
								   dest_head->get_g() * dest_head->get_a()));
					dest_head->set_b(
						saturation(head->get_b() +
								   dest_head->get_b() * dest_head->get_a()));
				}
			}
		};

		/**
		 * 減算合成
		 */
		class sub_blend
		{
		public:
			template <typename src_iterator_t,
					  typename dest_iterator_t>
			operator()(src_iterator_t& head,
					   src_iterator_t& tail,
					   dest_iterator_t& dest_head)
			{
				while (head != tail)
				{
					dest_head->set_r(
						saturation(head->get_r() -
								   dest_head->get_r() * dest_head->get_a()));
					dest_head->set_g(
						saturation(head->get_g() -
								   dest_head->get_g() * dest_head->get_a()));
					dest_head->set_b(
						saturation(head->get_b() -
								   dest_head->get_b() * dest_head->get_a()));
				}
			}
		};
	};
};

#endif /* RISA_PRIMITIVE_BLEND_HPP_ */

