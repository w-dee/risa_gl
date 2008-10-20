

template <typename expantion_t,
		  typename template <typename> src_selector,
		  typename template <typename> src_factor_selector,
		  typename template <typename> dest_selector,
		  typename template <typename> dest_factor_selector>
class selector_function
{
public:
	/// 拡張先の型(uint32, uint64, m128)など
	typedef expantion_t expantion_type;
	/// sourceを抽出するファンクタ型
	typedef src_selector<expantion_type> source_selector_type;
	/// sourceのfactorを抽出するファンクタ型
	typedef src_factor_selector<expantion_type> source_factor_type;
	/// destinationを抽出するファンクタ型
	typedef dest_selector<expantion_type> destination_selector_type;
	/// destinationのfactorを抽出するファンクタ型
	typedef dest_factor_selector<expantion_type> destination_factor_type;

private:
	source_selector_type source_select;
	source_factor_type soruce_factor;
	destination_selector_type destination_select;
	destination_factor_type destination_factor;

public:
	selector_function(source_selector_type source_select_ =
					  source_selctor_type(),
					  source_factor_type soruce_factor_ =
					  soruce_factor_type(),
					  destination_selector_type destination_select_ =
					  destination_selector_type(),
					  destination_factor_type destination_factor =
					  destination_factor_type()):
		source_select(source_select_),
		soruce_factor(soruce_factor_),
		destination_select(destination_select_),
		destination_factor(destination_factor_)
	{}
		
	template <typename input_type>
	exnpation_type get_source(input_type source,
							  input_type destination) const
	{
		return source_select(source, destination);
	}

	template <typename input_type>
	expantion_type get_source_factor(input_type source,
									 input_type destination) const
	{
		return source_factor(source, destination);
	}

	template <typename input_type>
	exnpation_type get_destination(input_type source,
								   input_type destination) const
	{
		return destination_select(source, destination);
	}

	template <typename input_type>
	expantion_type get_destination_factor(input_type source,
										  input_type destination) const
	{
		return destination_factor(source, destination);
	}
};



template <typename result_t>
class gather_function
{
	typedef result_t result_type;

	template <typename input_type>
	result_type gather(input_type higher, input_type lower) const
	{
		return higher | lower;
	}
};

template <typename template <typename> impl_t, typename selector_t,
		  typename mapper_t, typename reducer_t>
class function
{
public:
	typedef mapper_t mapper_type;
	typedef reducer_t reducer_type;
	typedef selector_t selector_type;
	typedef typename selector_type::expantion_type result_type;
	typedef impl_t<result_type> implement_type;

private:
	implement_type implement;
	selector_type selector;
	mapper_type mapper;
	reducer_type reducer;

public:
	function(implement_type implement_ = implement_type(),
			 selector_type selector_ = selector_type()):
		implement(implement_),
		selector(selector_)
	{}

	template <typename input_type>
	result_type opeartor()(input_type src, input_type dest) const
	{
		return reducer.reduce(
			implement(
				mapper.higher(selector.get_source()),
				mapper.higher(selector.get_source_factor()),
				mapper.higher(selector.get_destination()),
				mapper.higher(selector.get_destination_factor())),
			implement(
				mapper.lower(selector.get_source()),
				mapper.lower(selector.get_source_factor()),
				mapper.lower(selector.get_destination()),
				mapper.lower(selector.get_destination_factor())));
	}
};

template <typename selector_t,
		  typename template <typename> function_t>
class binomial_operator
{
public:
	typedef selector_t selector_type;
	typedef function_t<selector_type> function_type;
	typedef typename function_type::result_type result_type;

private:
	//! 画素値を計算可能単位に分割するファンクタ
	scatter_type scatter;

	//! 画素値を計算可能単位から元に戻すファンクタ
	gather_type gather;

	//! 計算可能単位
	selector_type selector;
	function_type<selector_type> function;

public:
	binomial_operator(scatter_type scatter_ = scatter_type(),
					  gather_type gather_ = gather_type(),
					  selector_type selector_ = selector_type(),
					  function_type function_ = function_type()):
		scatter(scatter_),
		gather(gather_),
		selector(selector_),
		function(selector)
	{}

	binomial_operator(function_type function_ = function_type()):
		function(function_)
	{}

	template <typename input_type>
	result_type operator()(input_type src,
						   input_type dest) const
	{
		
		return function(src, dest);
	}
};
