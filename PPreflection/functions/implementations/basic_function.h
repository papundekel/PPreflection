#pragma once
#include "../../types/function_type.h"

namespace PPreflection::detail
{
	template <typename F, typename Base>
	class basic_function : public Base
	{
	private:
		static constexpr auto function_type_ = PP::type<F>;
		static constexpr auto info = PP::function_info(function_type_);

	protected:
		static constexpr auto return_type = info.return_type;
		static constexpr auto parameter_types = info.parameter_types;
		static constexpr auto Noexcept = info.Noexcept;
		static constexpr auto cv = info.cv;
		static constexpr auto ref = info.ref;

	public:
		constexpr const function_type& get_function_type()
			const noexcept override final
		{
			return type::reflect(function_type_);
		}
	};
}
