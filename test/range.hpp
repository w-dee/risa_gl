
#include <string>
#include <sstream>

template <typename type>
bool range(type lhs, type rhs, type range_offset)
{
	type differ = lhs - rhs;
	return ((differ >= 0) ? differ : -differ) <= range_offset;
}

#define CPPUNIT_ASSERT_RANGE(expected, actual, delta)	\
	{ \
		std::stringstream ss; \
		ss <<  "excepted: " << expected << \
			", actual: " << actual << "+/-" << delta << std::ends; \
		CPPUNIT_NS::Asserter::failIf(!range(expected, actual, delta), \
									 ss.str().c_str(), CPPUNIT_SOURCELINE()); \
	}
