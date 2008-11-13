#include <risa_gl/math/cosine.hpp>
#include <risa_gl/util/TimeCounter.hpp>
#include <iostream>
#include <vector>
#include <cmath>

#define rdtsc(val) \
  __asm__ __volatile__ ("rdtsc" : "=A" (val));

const int loop_count = 1000000;
const int wait_counter = 1000;

struct differ
{
	double& result;

	differ(double& result_ref):
		result(result_ref)
	{}

	void operator()(const float lhs, const float rhs)
	{
		result += std::abs(lhs - rhs);
	}
};

inline int checker1()
{
	std::cout <<
		"checker1() std::cos(float) vs template base cosine"
		"(type = float, calc depth = 5) precision." << std::endl;

	std::cout << "loop count for " << (loop_count) << std::endl; 
	TimeCounter basic_counter;
	TimeCounter template_counter;

	std::vector<float> basic_result;
	std::vector<float> template_result;
	basic_result.reserve(loop_count);
	template_result.reserve(loop_count);

	basic_counter.start();
	for (float value = -1.f; value <= 1.f; value += 1.f / loop_count)
		basic_result.push_back(std::cos(value));
	basic_counter.stop();

	template_counter.start();
	for (float value = -1.f; value <= 1.f; value += 1.f / loop_count)
		template_result.push_back(risa_gl::math::cosine<float,5>::value(value));
	template_counter.stop();


	std::cout << "basics: " << 
		(static_cast<double>(basic_counter.getTime()) / 1000.0) << std::endl;
	std::cout << "templates: " << 
		(static_cast<double>(template_counter.getTime()) / 1000.0) << std::endl;

	double statistic = 0.0;
	differ diff(statistic);
	typedef std::vector<float> result_t;
	for (result_t::const_iterator lhs_itor = basic_result.begin(),
			 rhs_itor = template_result.begin();
		 lhs_itor != basic_result.end(); ++lhs_itor, ++rhs_itor)
		diff(*lhs_itor, *rhs_itor);
		 
	std::cout << "statistics: " << (statistic / basic_result.size()) << std::endl;
	return 0;
}


inline int checker2()
{
	std::cout <<
		"checker2() std::cos(float) vs template base cosine"
		"(type = float, calc depth = 5) speed." << std::endl;

	std::cout << "loop count for " << (loop_count * wait_counter) << std::endl; 

	TimeCounter basic_counter;
	TimeCounter template_counter;

	basic_counter.start();
	for (int i = 0; i < wait_counter; ++i)
	for (float value = -1.f; value <= 1.f; value += 1.f / loop_count)
		std::cos(value);
	basic_counter.stop();

	template_counter.start();
	for (int i = 0; i < wait_counter; ++i)
	for (float value = -1.f; value <= 1.f; value += 1.f / loop_count)
		risa_gl::math::cosine<float,5>::value(value);
	template_counter.stop();

	std::cout << "basics: " << 
		(static_cast<double>(basic_counter.getTime()) / 1000.0) << std::endl;
	std::cout << "templates: " << 
		(static_cast<double>(template_counter.getTime()) / 1000.0) << std::endl;

	return 0;
}

inline int checker3()
{
	std::cout <<
		"checker3() template base cosine"
		"(type = double, calc depth = 7) speed." << std::endl;

	std::cout << "loop count for " << (loop_count * wait_counter) << std::endl; 

	TimeCounter template_counter;

	template_counter.start();
	for (int i = 0; i < wait_counter; ++i)
	for (float value = -1.f; value <= 1.f; value += 1.f / loop_count)
		risa_gl::math::cosine<double>::value(value);
	template_counter.stop();

	std::cout << "templates: " << 
		(static_cast<double>(template_counter.getTime()) / 1000.0) << std::endl;

	return 0;
}

inline int checker4()
{
	std::cout << 
		"checker4() std::cos(double) vs template base cosine"
		"(type = double, calc depth = 7)." << std::endl;

	std::cout << "loop count for " << (loop_count) << std::endl; 

	TimeCounter basic_counter;
	TimeCounter template_counter;

	std::vector<double> basic_result;
	std::vector<double> template_result;
	basic_result.reserve(loop_count);
	template_result.reserve(loop_count);

	basic_counter.start();
	for (float value = -1.f; value <= 1.f; value += 1.f / loop_count)
		basic_result.push_back(std::cos(value));
	basic_counter.stop();

	template_counter.start();
	for (float value = -1.f; value <= 1.f; value += 1.f / loop_count)
		template_result.push_back(risa_gl::math::cosine<double>::value(value));
	template_counter.stop();


	std::cout << "basics: " << 
		(static_cast<double>(basic_counter.getTime()) / 1000.0) << std::endl;
	std::cout << "templates: " << 
		(static_cast<double>(template_counter.getTime()) / 1000.0) << std::endl;

	double statistic = 0.0;
	differ diff(statistic);
	typedef std::vector<double> result_t;
	for (result_t::const_iterator lhs_itor = basic_result.begin(),
			 rhs_itor = template_result.begin();
		 lhs_itor != basic_result.end(); ++lhs_itor, ++rhs_itor)
		diff(*lhs_itor, *rhs_itor);
		 
	std::cout << "statistics: " << (statistic / basic_result.size()) << std::endl;
	return 0;
}

double templ_cos(const double value)
{
	return risa_gl::math::cosine<double>::value(value);
}

void checker5()
{
	unsigned long long
		std_start = 0, std_end = 0, templ_start = 0, templ_end = 0;

	const int count = 1;

	double s = 0.0, t = 0.0;
	rdtsc(std_start);
	for (int i = 0; i < count; ++i)
		s += std::cos(0.5);
	rdtsc(std_end);

	rdtsc(templ_start);
	for (int i = 0; i < count; ++i)
		t += templ_cos(0.5);
	rdtsc(templ_end);

	std::cout << "std::cos() used clock of " <<
		(std_end - std_start) << std::endl;
	std::cout << "template cosine used clock of " <<
		(templ_end - templ_start) << std::endl;

	std::cout << "std: " << (s/count) <<
		", template: " << (t/count) << std::endl;

}

int main()
{
// 	std::cout << "loop_count = " << loop_count << std::endl;
// 	std::cout << "wait_counter = " << wait_counter << std::endl;
// 	checker1();
// 	std::cout << std::endl;
// 	checker2();
// 	std::cout << std::endl;
// 	checker3();
// 	std::cout << std::endl;
// 	checker4();
// 	std::cout << std::endl;

	checker5();
	return 0;
}
