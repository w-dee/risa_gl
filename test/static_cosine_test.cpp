#include <cppunit/extensions/HelperMacros.h>
#include <math/cosine.hpp>
#include <cmath>
#include <iostream>

class cosine_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(cosine_test);
	CPPUNIT_TEST(differTest);
	CPPUNIT_TEST_SUITE_END();

public:

	void differTest()
	{
		float v = -1.f;

		for (; v < 1.f; v+= 0.01f)
		{
			std::cout << "v = "<< v << 
				"dyn cos: " << std::cos(v) <<
				"  static cos: " <<
				risa_gl::math::cosine<float>::get(v) << std::endl;
		}
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( cosine_test );
