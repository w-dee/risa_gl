#ifndef RISA_ITERATOR_HPP_
#define RISA_ITERATOR_HPP_

#include "risa_types.hpp"

namespace risa_gl
{
	/**
	 * ピクセルのシーケンシャルイテレータ。
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

		bool operator!=(const sequencial_iterator& rhs) const
		{
			return this->pointer != rhs.pointer;
		}

		const pixel_t& operator*() const
		{
			return *pointer;
		}

		pixel_t& operator*()
		{
			return *pointer;
		}

		iterator& operator++()
		{
			++pointer;
			return *this;
		}

		iterator operator++(int)
		{
			iterator result(*this);
			++pointer;
			return result;
		}
	};

	template <typename pixel_type, size_t alignment>
	class aligned_iterator
	{
	public:
		typedef poxel_type pixel_t;
		typedef byte* pointer_t;

	private:
		pointer_t pointer;

	public:
		aligned_iterator():
			pointer()
		{}

		aligned_iterator(pointer_t pointer_):
			pointer(pointer_)
		{}

		aligned_iterator(const aligned_iterator& source):
			pointer(source.pointer)
		{}

		~aligned_iterator()
		{}

		bool operator!=(const aligned_iterator& rhs) const
		{
			return this->pointer != rhs;
		}

		pixel_t& operator*()
		{
			return reinterpret_cast<pixel_t>(*pointer);
		}

		const pixel_t& operator*() const
		{
			return reinterpret_cast<pixel_t>(*pointer);
		}

		aligned_iterator& operator++()
		{
			this->pointer += alignment;
			return *this;
		}

		aligned_iterator operator++(int)
		{
			aligned_iterator result(*this);
			this->pointer += alignment;
			return result;
		}
	};

	/**
	 * 変形イテレータ
	 * 写像変換後の画像のスキャンなどを行う、特殊なランダムアクセスイテテータ。
	 * 次状態への遷移に必要なパラメタ、関数はtemplateパラメタで渡される
	 * @param state_type 保持された状態
	 * @param transit_function 遷移するための関数が定義されたファンクタ。
	 * 単項ファンクタで、引数の型はstate_type&とする
	 */
	template <typename value_type,
			  typename state_type,
			  typename transit_function>
	class transform_iterator
	{
	public:
		typedef value_type value_t;
		typedef state_type state_t;
		typedef transit_function transit_t;

	private:
		value_t color;
		state_t state;

	public:
		transform_iterator():
			state()
		{}

		transform_iterator(const state_t& state_):
			state(state_)
		{}

		transform_iterator(const transform_iterator& source):
			state(source.state)
		{}

		~transform_iterator()
		{}

		const value_t& operator*() const
		{
			return color;
		}

		bool operator!=(const transform_iterator& rhs) const
		{
			return state != rhs.state;
		}

		transform_iterator& operator++()
		{
			transit_t()(state);
			return *this;
		}

		transform_iterator operator++(int)
		{
			transform_iterator result(*this);
			transit_t()(state);
			return result;
		}
	};

	
};

#endif /* RISA_ITERATOR_HPP_ */
