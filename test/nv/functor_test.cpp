#include <cppunit/extensions/HelperMacros.h>
#include <risa_gl/nv/functor.hpp>

class functor_test : public CppUnit::TestFixture 
{
	CPPUNIT_TEST_SUITE(functor_test);
	CPPUNIT_TEST(inverse_test);
	CPPUNIT_TEST_SUITE_END();

private:
	void identity_test()
	{
		
	}

	void inverse_test()
	{
		//		functor::
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( functor_test );
