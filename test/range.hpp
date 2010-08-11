template <typename type>
bool range(type lhs, type rhs, type range_offset)
{
	type differ = lhs - rhs;
	return ((differ >= 0) ? differ : -differ) <= range_offset;
}

#define CPPUNIT_ASSERT_RANGE(expected, actual, delta) \
	CPPUNIT_ASSERT(range(expected, actual, delta))

