#include <math/cosine.hpp>
#include <util/TimeCounter.hpp>
#include <iostream>
#include <vector>
#include <cmath>

struct add
{
	double& result;

	add(double& result_ref):
		result(result_ref)
	{}

	void operator()(const float value) 
	{
		result += static_cast<const double>(value);
	}
};

int checker1()
{
	TimeCounter basic_counter;
	TimeCounter template_counter;

	std::vector<float> basic_result;
	std::vector<float> template_result;
	basic_result.reserve(100000);
	template_result.reserve(100000);

	basic_counter.start();
	for (float value = -1.f; value <= 1.f; value += 0.00001f)
		basic_result.push_back(std::cos(value));
	basic_counter.stop();

	template_counter.start();
	for (float value = -1.f; value <= 1.f; value += 0.00001f)
		template_result.push_back(risa_gl::math::cosine<float>::value(value));
	template_counter.stop();


	std::cout << "basics: " << 
		(static_cast<double>(basic_counter.getTime()) / 1000.0) << std::endl;
	std::cout << "templates: " << 
		(static_cast<double>(template_counter.getTime()) / 1000.0) << std::endl;

	double basic_sum = 0.0;
	double template_sum = 0.0;

	std::for_each(basic_result.begin(), basic_result.end(), add(basic_sum));
	std::for_each(template_result.begin(), template_result.end(), add(template_sum));

	std::cout << "jitter: " << ((template_sum - basic_sum) / 1000) << std::endl;
	return 0;
}


int checker2()
{
	TimeCounter basic_counter;
	TimeCounter template_counter;

	const int wait_counter = 10000;

	basic_counter.start();
	for (int i = 0; i < wait_counter; ++i)
	for (float value = -1.f; value <= 1.f; value += 0.00001f)
		std::cos(value);
	basic_counter.stop();

	template_counter.start();
	for (int i = 0; i < wait_counter; ++i)
	for (float value = -1.f; value <= 1.f; value += 0.00001f)
		risa_gl::math::cosine<float>::value(value);
	template_counter.stop();

	std::cout << "basics: " << 
		(static_cast<double>(basic_counter.getTime()) / 1000.0) << std::endl;
	std::cout << "templates: " << 
		(static_cast<double>(template_counter.getTime()) / 1000.0) << std::endl;

	return 0;
}

int checker3()
{
	TimeCounter template_counter;

	const int wait_counter = 10000;

	template_counter.start();
	for (int i = 0; i < wait_counter; ++i)
	for (float value = -1.f; value <= 1.f; value += 0.00001f)
		risa_gl::math::cosine<double>::value(value);
	template_counter.stop();

	std::cout << "templates: " << 
		(static_cast<double>(template_counter.getTime()) / 1000.0) << std::endl;

	return 0;
}

int checker4()
{
	TimeCounter basic_counter;
	TimeCounter template_counter;

	std::vector<double> basic_result;
	std::vector<double> template_result;
	basic_result.reserve(100000);
	template_result.reserve(100000);

	basic_counter.start();
	for (double value = -1.f; value <= 1.; value += 0.00001)
		basic_result.push_back(std::cos(value));
	basic_counter.stop();

	template_counter.start();
	for (double value = -1.f; value <= 1.; value += 0.00001)
		template_result.push_back(risa_gl::math::cosine<double>::value(value));
	template_counter.stop();


	std::cout << "basics: " << 
		(static_cast<double>(basic_counter.getTime()) / 1000.0) << std::endl;
	std::cout << "templates: " << 
		(static_cast<double>(template_counter.getTime()) / 1000.0) << std::endl;

	double basic_sum = 0.0;
	double template_sum = 0.0;

	std::for_each(basic_result.begin(), basic_result.end(), add(basic_sum));
	std::for_each(template_result.begin(), template_result.end(), add(template_sum));

	std::cout << "jitter: " << ((template_sum - basic_sum) / 1000) << std::endl;
	return 0;
}

int main()
{
	checker1();
	checker2();
	checker3();
	checker4();

	return 0;
}
