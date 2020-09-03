#pragma once
#include "cref_t.h"
#include "pointer_view.h"
#include "../PP/PP/view.hpp"

namespace detail
{
	template <typename T>
	struct name_wrap {};

	template <typename T>
	struct id_wrap {};

	template <typename T>
	struct basic_type_wrap {};

	template <typename T>
	struct constructor_wrap {};

	template <typename ResultType>
	struct reflector
	{
		template <typename T>
		struct reflect
		{
			static constexpr const ResultType& value_f() noexcept;
		};
		template <typename T>
		struct reflect<name_wrap<T>>
		{
			static constexpr const ResultType& value_f() noexcept;
		};
		template <typename T>
		struct reflect<id_wrap<T>>
		{
			static constexpr const ResultType& value_f() noexcept;
		};
		template <typename T>
		struct reflect<constructor_wrap<T>>
		{
			static constexpr const ResultType& value_f() noexcept;
		};
		template <typename T>
		struct reflect<name_wrap<constructor_wrap<T>>>
		{
			static constexpr const ResultType& value_f() noexcept;
		};
	};
}

template <typename T, typename ResultType>
constexpr const ResultType& reflect() noexcept;

template <auto v, typename ResultType>
constexpr decltype(auto) reflect() noexcept;

template <typename Pack, typename ResultType>
constexpr pointer_view<const cref_t<ResultType>> reflect_many() noexcept;

template <typename Pack, typename ResultType>
constexpr PP::view auto reflect_many_view() noexcept;
