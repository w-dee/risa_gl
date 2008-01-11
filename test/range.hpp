template <typename type>
bool range(type lhs, type rhs, type range_offset)
{
	type differ = lhs - rhs;
	return ((differ >= 0) ? differ : -differ) <= range_offset;
}
		
