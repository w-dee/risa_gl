#ifndef RISA_ITERATOR_HPP_
#define RISA_ITERATOR_HPP_

namespace risa_gl
{
	/**
	 * シーケンシャルイテレータ。
	 * イントリンシクスに渡すにはこのタイプである必要がある。
	 */
	template <typename pixel_type>
	class sequencial_iterator
	{
	public:
		typedef pixel_type pixel_t;
		typedef pixel_type* pointer_t;

	private:
		const pixel_t* pointer;

	public:
		sequencial_iterator():
			pointer()
		{}

		sequencial_iterator(const sequencial_iterator& source):
			pointer(source.pointer)
		{}

		sequencial_iterator(const pixel_t* source):
			pointer(source)
		{}

		~sequencial_iterator()
		{}

		const pixel_t& operator*() const
		{
			return *pointer;
		}

		pixel_t& operator*()
		{
			return *pointer;
		}
	};
};

#endif /* RISA_ITERATOR_HPP_ */
