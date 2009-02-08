#ifndef RISA_RENDER_TEXTURE_POINT_HPP_
#define RISA_RENDER_TEXTURE_POINT_HPP_

namespace risa_gl
{
	namespace render
	{
		template <typename value_t>
		class texture_point
		{
		public:
			typedef value_t value_type;
			
		private:
			value_type s;
			value_type t;

		public:
			texture_point(const value_type& s_ = value_type(),
						  const value_type& t_ = value_type()):
				s(s_), t(t_)
			{}

			value_type get_s()
			{
				return s;
			}

			const value_type& get_s() const
			{
				return s;
			}

			void set_s(const value_type& s_)
			{
				s = s_;
			}

			value_type get_t()
			{
				return t;
			}

			const value_type& get_t() const
			{
				return t;
			}

			void set_t(const value_type& t_)
			{
				t = t_;
			}

			std::pair<value_type, value_type> get_st()
			{
				return std::make_pair(s, t);
			}
		};
	}
}

#endif /* RISA_RENDER_TEXTURE_POINT_HPP_ */
