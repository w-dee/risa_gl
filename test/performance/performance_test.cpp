#define NOMINMAX
#include <pixel.hpp>
#include <pixel_store.hpp>
#include <operators/alpha_blend.hpp>
#include <iostream>
#include <algorithm>
#include <Thread/RerunnableThread.hpp>

#include <util/TimeCounter.hpp>

/**
 * 測定するオペレータの指定
 */
typedef risa_gl::operators::alpha_blend_save_destination_alpha_operator target_operator;
//typedef risa_gl::operators::alpha_blend_operator target_operator;


template <
	typename func_t,
	typename src_itor_t,
	typename dest_itor_t>
class Job
{
private:
	func_t functor;
	src_itor_t head;
	src_itor_t tail;
	dest_itor_t dest;

public:
	Job(src_itor_t head_, src_itor_t tail_, dest_itor_t dest_):
	functor(), head(head_), tail(tail_), dest(dest_)
	{}

	virtual ~Job()
	{}

	virtual unsigned int run() throw(ThreadException)
	{
		for (; head != tail; ++head, ++dest)
			functor(head, dest, head);

		return 0;
	}
};

using namespace risa_gl;

std::pair<std::vector<pixel_store<pixel>::fragment_type>,
		  std::vector<pixel_store<pixel>::fragment_type> >
get_interleaved_fragments(pixel_store<pixel>& pix)
{
	std::vector<pixel_store<pixel>::fragment_type> evens;
	std::vector<pixel_store<pixel>::fragment_type> odds;
	
	for (int line = 0; line < pix.get_height(); line += 2)
	{
		evens.push_back(pix.get_fragment(line));
		if (line < pix.get_height())
			odds.push_back(pix.get_fragment(line + 1));
	}

	return make_pair(evens, odds);
}

template <typename operator_type>
class Work : public Runnable
{
public:
	typedef pixel_store<pixel>::fragment_type fragment_type;
	typedef std::vector<fragment_type> fragments_type;
private:
	fragments_type src_fragments;
	fragments_type dest_fragments;

public:
	Work(fragments_type src, fragments_type dest):
		src_fragments(src), dest_fragments(dest)
	{}

	virtual unsigned int run() throw(ThreadException)
	{
		for (fragments_type::iterator src_itor = src_fragments.begin(),
				 dest_itor = dest_fragments.begin();
			 src_itor != src_fragments.end(); ++src_itor, ++dest_itor)
		{
			operator_type oper(src_itor->begin(),
							   src_itor->end(),
							   dest_itor->begin());
			oper.run();
		}
		return 0;
	}
};

typedef Work<Job<
	target_operator,
	pixel_store<pixel>::iterator,
	pixel_store<pixel>::iterator> > alpha_copy;


int main()
{
	typedef pixel_store<pixel> frame_type;
	frame_type frame_buffer(640, 480);
	frame_type back_buffer(640, 480);

	TimeCounter counter;

	std::fill(frame_buffer.begin(), frame_buffer.end(),
				  pixel(255, 255, 255, 128));
	std::fill(back_buffer.begin(), back_buffer.end(),
				  pixel(0, 0, 0, 1));

#ifdef MT
	RerunnableThread proc_even;
#endif /* MT */

	counter.start();

	for (int count = 0; count < 2000; ++count) {
#ifdef MT
		std::pair<std::vector<pixel_store<pixel>::fragment_type>,
			std::vector<pixel_store<pixel>::fragment_type> >
			src_frag_set = get_interleaved_fragments(frame_buffer);

		std::pair<std::vector<pixel_store<pixel>::fragment_type>,
			std::vector<pixel_store<pixel>::fragment_type> >
			dest_frag_set = get_interleaved_fragments(back_buffer);

		alpha_copy even_copy(src_frag_set.first, dest_frag_set.first);
		alpha_copy odd_copy(src_frag_set.second, dest_frag_set.second);

		proc_even.start(&even_copy);

		odd_copy.run();

		proc_even.join();
#else
		frame_type::iterator src_itor = frame_buffer.begin();
		frame_type::iterator dest_itor = back_buffer.begin();

		Job<target_operator,
			frame_type::iterator,
			frame_type::iterator>
		 job
		(frame_buffer.begin(),
		 frame_buffer.end(),
		 back_buffer.begin());
		job.run();
#endif /* MT */
	}

	counter.stop();

#ifdef MT
	proc_even.quit();
#endif /* MT */

	std::cout << "using time for " <<
		(static_cast<double>(counter.getTime()) / 1000.0) << std::endl;

	return 0;
}
