#pragma once
#include <memory>
#include <optional>
#include "descriptor.hpp"
#include "dynamic_ptr.hpp"
#include "simple_range.hpp"
#include "static_wrap.hpp"
#include "dynamic_wrap.hpp"

class namespace_t;

template <typename T>
using cref_t = std::reference_wrapper<const T>;

class function : public descriptor
{
	const char* name;

	const namespace_t* parent_namespace;

	const type& return_type;
	simple_range<cref_t<type>> argument_types;

	void (*invoker)(void*, const dynamic_ptr*);

	constexpr function(const char* name, const namespace_t* parent_namespace, void (*invoker)(void*, const dynamic_ptr*)) noexcept
		: name(name)
		, parent_namespace(parent_namespace)
		, invoker(invoker)
	{}

	template <typename T>
	struct deleter
	{
		constexpr void operator()(T* ptr) noexcept
		{
			ptr->~T();
			delete[] ((std::byte*)ptr);
		}
	};

public:
	template <typename T>
	using ptr = std::unique_ptr<T, deleter<T>>;

	constexpr void print_name(simple_ostream& out) const noexcept final
	{
		out.write(name);
	}

	constexpr function set_parent(const namespace_t* parent_namespace) const noexcept
	{
		return { name, parent_namespace, invoker };
	}

	constexpr function(const char* name, void (*invoker)(void*, const dynamic_ptr*)) noexcept
		: function(name, nullptr, invoker)
	{}

	template <typename T = void>
	constexpr std::optional<static_wrap<T>> invoke_static(const dynamic_ptr* args)
	{
		if (type::convertible(return_type, reflect<T>) && zip_with(args, argument_types,
				[](auto arg, auto& arg_type)
				{
					return type::convertible(arg.get_type(), arg_type);
				}) | all)
			return wrap<T>(invoker, args);

		return std::nullopt;
	}

	constexpr auto invoke_dynamic(simple_range<const dynamic_ptr> args = {})
	{
		return dynamic_wrap(return_type, invoker, args);
	}

	constexpr auto& get_parent() const noexcept
	{
		return *parent_namespace;
	}

private:
	template <typename T>
	static constexpr decltype(auto) cast(void* argument) noexcept
	{
		if constexpr (std::is_lvalue_reference_v<T>)
			return *reinterpret_cast<std::remove_reference_t<T>*>(argument);
		else if constexpr (std::is_rvalue_reference_v<T>)
			return std::move(*reinterpret_cast<std::remove_reference_t<T>*>(argument));
		else if constexpr (std::is_pointer_v<T>)
			return reinterpret_cast<T>(argument);
		else
			return *reinterpret_cast<T*>(argument);
	}

	template <typename Return, typename... Args, std::size_t... I>
	static constexpr void initiliaze(Return(&f)(Args...), void* result, simple_range<const dynamic_ptr> args, std::index_sequence<I...>)
	{
		new (result) Return(f(cast<Args>(args[I].get_ptr())...));
	}

public:
	template <typename Return, typename... Args>
	struct helper
	{
		template <Return(&f)(Args...)>
		static constexpr auto help = [](void* result, simple_range<const dynamic_ptr> args)
		{
			initiliaze(f, result, args, std::index_sequence_for<Args...> {});
		};
	};
};
