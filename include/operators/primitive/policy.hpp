#ifndef RISA_POLICY_HPP_
#define RISA_POLICY_HPP_

namespace risa_gl
{
	namespace primitive
	{
		struct abstruct_policy {};

		struct broken_destination_alpha_policy : public abstruct_policy {};

		struct save_destination_alpha_policy : public abstruct_policy {};


	};
};
#endif /* RISA_POLICY_HPP_ */
