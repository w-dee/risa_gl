
#include <string>
#include <sstream>

template <typename type>
bool range(type lhs, type rhs, type range_offset)
{
	type differ = lhs - rhs;
	return ((differ >= 0) ? differ : -differ) <= range_offset;
}

#define CPPUNIT_ASSERT_RANGE(actuals, expected, delta)	\
	{ \
		std::stringstream ss; \
		ss <<  "acutal: " << actuals << \
			", expected: " << expected << "+/-" << delta << std::ends; \
		CPPUNIT_NS::Asserter::failIf(!range(actuals, expected, delta), \
									 ss.str().c_str(), CPPUNIT_SOURCELINE()); \
	}
