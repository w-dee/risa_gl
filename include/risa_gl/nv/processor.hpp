#ifndef PROCESSOR_HPP_
#define PROCESSOR_HPP_

namespace binomial
{
	template <typename input_t,
			  typename output_t>
	class processor
	{
	public:
		typedef input_t inputer_type;
		typedef output_t outputer_type;

		typedef outputer_type::result_type result_type;

	private:
		inputer_type inputer;
		outputer_type outputer;

	public:
		template <typename input_type>
		result_type operator()(input_type src, input_type dest) const
		{
			typedef inputer_type::result_type input_result_type;
			input_result_type input_result[inputer_type::divides];

			for (int offset = 0; offset < inputer_type::divides; ++offset) 
			{
				input_result[offset] = 
					inputer.scatter(offset, src, dest);
			}

			outputer.gather(
				
		}
	};

	
}
#endif /* PROCESSOR_HPP_ */
