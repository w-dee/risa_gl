#ifndef RISA_RECTANGLE_SET_HPP_
#define RISA_FRAGMENT_SET_HPP_

#include <vector>

namespace risa_gl
{
	template <typename pixel_store_t, typename fragment_t>
	class fragment_set
	{
	public:
		typedef pixel_store_t pixel_store_type;
		typedef fragment_t fragment_type;
		typedef std::vector<fragment_t> fragment_collection_type;

	private:
		fragment_collection_type fragments;

	public:
		fragment_set(fragments_collection_type& fragments_):
			fragments(fragments_)
		{}

		~fragment_set()
		{}

		fragment_type oepartor[](int line)
		{
			if (line < 0 ||
				line >= fragments.size())
				throw std::invalid_argument();

			return fragments[line];
		}
	};
};
#endif /* RISA_FRAGMENT_SET_HPP_ */
