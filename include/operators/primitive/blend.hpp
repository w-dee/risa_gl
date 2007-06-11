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
					dest_head->set_red(
						saturation(head->get_red() * (255 - dest->get_alpha()) +
								   dest_head->get_red() * dest_head->get_alpha()));
					dest_head->set_green(
						saturation(head->get_green() * (255 - dest->get_alpha()) +
								   dest_head->get_green() * dest_head->get_alpha()));
					dest_head->set_blue(
						saturation(head->get_blue() * (255 - dest->get_alpha()) +
								   dest_head->get_blue() * dest_head->get_alpha()));
					/* アルファ値の扱いどうするのさ？ */
//					dest_head->set_alpha();
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
					dest_head->set_red(
						saturation(head->get_red() +
								   dest_head->get_red() * dest_head->get_alpha()));
					dest_head->set_green(
						saturation(head->get_green() +
								   dest_head->get_green() * dest_head->get_alpha()));
					dest_head->set_blue(
						saturation(head->get_blue() +
								   dest_head->get_blue() * dest_head->get_alpha()));
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
					dest_head->set_red(
						saturation(head->get_red() -
								   dest_head->get_red() * dest_head->get_alpha()));
					dest_head->set_green(
						saturation(head->get_green() -
								   dest_head->get_green() * dest_head->get_alpha()));
					dest_head->set_blue(
						saturation(head->get_blue() -
								   dest_head->get_blue() * dest_head->get_alpha()));
				}
			}
		};
	};
};

#endif /* RISA_PRIMITIVE_BLEND_HPP_ */

