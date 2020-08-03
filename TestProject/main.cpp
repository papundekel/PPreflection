#include <iostream>
#include <string_view>
#include <map>
#include <utility>
#include <array>
#include <memory>
#include <vector>
#include "reflection/reflection.hpp"

template <typename T>
struct type_object
{
	using type = T;
};
template <typename... T>
struct type_list {};
struct end;

template <typename T, typename... Rest>
void insert_types(type_list<T, Rest...>)
{
	//name_to_type.insert({ t<T>.name, &t<T> });
	insert_types(type_list<Rest...>{});
}

void insert_types(type_list<>) {}

void init()
{
	insert_types(type_list<void, int, char>{});
}

template <auto predicate, typename T, typename... U>
constexpr auto find(type_list<T, U...>)
{
	if constexpr (predicate(type_object<T>{}))
		return type_object<T>{};
	else
		return find<predicate>(type_list<U...>{});
}
template <auto predicate>
constexpr auto find(type_list<>)
{
	return type_object<end>{};
}

template <auto t> using unwrap_type = decltype(t)::type;

template <std::size_t size, typename... T>
using find_size = unwrap_type<find<[]<typename U>(type_object<U>) { return sizeof(U) == size; }>(type_list<T...>{})>;

using intptr = find_size<sizeof(void*), char, short, int, long, long long>;

struct X
{
	virtual void f() = 0;
	virtual ~X()
	{}
};

struct Y : X
{
	intptr x;

	Y()
		: x(200)
	{}

	Y(int x)
		: x(x)
	{}

	auto& operator=(Y&&) noexcept
	{
		return *this;
	}

	void f() override
	{
		std::cout << "f\n";
	}

	~Y() override
	{
		std::cout << "dede\n";
	}
};

Y f(int iv, Y& yr, X* xp, const X& cxr, const Y* cyp)
{
	return {};
}

template <typename T>
using cref_t = std::reference_wrapper<const T>;

template <typename T>
class simple_range
{
	const T* begin_;
	const T* end_;

public:
	constexpr simple_range() noexcept
		: begin_(nullptr)
		, end_(nullptr)
	{}

	template <std::size_t count>
	constexpr simple_range(const std::array<T, count>& array) noexcept
		: begin_(array.data())
		, end_(array.data() + array.size())
	{}

	constexpr auto begin() noexcept
	{
		return begin_;
	}
	constexpr auto end() noexcept
	{
		return end_;
	}
};

struct namespace_t;
struct type;

class descriptor
{
	const char* name_;

public:
	constexpr descriptor(const char* name) noexcept
		: name_(name)
	{}

	constexpr const char* name() const noexcept
	{
		return name_;
	}
};

class data : public descriptor
{
	const type& data_type;

public:
	constexpr data(const char* name, const type& data_type) noexcept
		: descriptor(name)
		, data_type(data_type)
	{}
};

struct variable : public data
{

};

struct field : public data
{

};

class invokable : public descriptor
{
	const type& return_type;

	simple_range<cref_t<type>> argument_types;

	void* (*invoker)(void**);

public:
	constexpr invokable(const char* name, const type& return_type, simple_range<cref_t<type>> argument_types, void* (*invoker)(void**)) noexcept
		: descriptor(name)
		, return_type(return_type)
		, argument_types(argument_types)
		, invoker(invoker)
	{}

	constexpr void invoke(void** args) const noexcept
	{
		invoker(args);
	}

	template <typename T>
	constexpr auto invoke(void** args) const noexcept
	{
		return std::unique_ptr<T,
				decltype([](auto* ptr)
				{
					ptr->~T();
					delete[]((std::byte*)ptr);
				})>
			(reinterpret_cast<T*>(invoker(args)));
	}

	static constexpr void** const no_params = nullptr;
};

class overloaded_invokable : public descriptor
{
	simple_range<invokable> overloads;

public:
	constexpr overloaded_invokable(const char* name, simple_range<invokable> overloads) noexcept
		: descriptor(name)
		, overloads(overloads)
	{}

	constexpr auto get_overloads() const
	{
		return overloads;
	}
};

class overloaded_function : public overloaded_invokable
{
public:
	constexpr overloaded_function(const char* name, simple_range<invokable> overloads) noexcept
		: overloaded_invokable(name, overloads)
	{}
};

class overloaded_method : public overloaded_invokable
{
public:
	constexpr overloaded_method(const char* name, simple_range<invokable> overloads) noexcept
		: overloaded_invokable(name, overloads)
	{}
};

class type : public descriptor
{
	simple_range<overloaded_method> methods;
	simple_range<overloaded_function> static_functions;
	simple_range<field> fields;
	simple_range<variable> static_variables;

public:
	constexpr type(const char* name) noexcept
		: descriptor(name)
	{}
};

class namespace_t : public descriptor
{
	simple_range<type> types;
	simple_range<overloaded_function> functions;
	simple_range<variable> variables;

public:
	constexpr namespace_t(const char* name,	simple_range<type> types, simple_range<overloaded_function> functions, simple_range<variable> variables) noexcept
		: descriptor(name)
		, types(types)
		, functions(functions)
		, variables(variables)
	{}

	constexpr auto get_types() const noexcept
	{
		return types;
	}
	constexpr auto get_functions() const noexcept
	{
		return functions;
	}
	constexpr auto get_variables() const noexcept
	{
		return variables;
	}
};

struct void__ : type
{
	constexpr void__() noexcept
		: type("void")
	{}
};
static constexpr inline void__ void_;

struct int__ : type
{
	constexpr int__() noexcept
		: type("int")
	{}
};
static constexpr inline int__ int_;

struct X__ : type
{
	constexpr X__() noexcept
		: type("X")
	{}
};
static constexpr inline X__ X_;

struct Y__ : type
{
	constexpr Y__() noexcept
		: type("Y")
	{}
};
static constexpr inline Y__ Y_;

template <const auto& inner>
struct const__ : type
{
	constexpr const__() noexcept
		: type(inner.name())
	{}
};
template <const auto& inner>
static constexpr inline const__<inner> const_;

template <const auto& inner>
struct reference__ : type
{
	constexpr reference__() noexcept
		: type(inner.name())
	{}
};
template <const auto& inner>
static constexpr inline reference__<inner> reference_;

template <const auto& inner>
struct pointer__ : type
{
	constexpr pointer__() noexcept
		: type(inner.name())
	{}
};
template <const auto& inner>
static constexpr inline pointer__<inner> pointer_;

struct f0__ : invokable
{
	//Y f(int, Y&, X*, const X&, const Y*);

	static constexpr std::array<cref_t<type>, 5> argument_types =
	{
		int_,
		reference_<Y_>,
		pointer_<X_>,
		reference_<const_<X_>>,
		pointer_<const_<Y_>>
	};

	constexpr f0__() noexcept
		: invokable("f", ::Y_, argument_types,
			[](void** args)
			{
				void* data = new std::byte[sizeof(Y)];

				new (data) Y(f(
					*reinterpret_cast<int*>(args[0]),
					*reinterpret_cast<Y*>(args[1]),
					reinterpret_cast<X*>(args[2]),
					*reinterpret_cast<const X*>(args[3]),
					reinterpret_cast<const Y*>(args[4])));

				return data;
			})
	{}
};

struct f__ : overloaded_function
{
	static constexpr std::array<invokable, 1> overloads = { f0__{} };

	constexpr f__() noexcept
		: overloaded_function("f", overloads)
	{}
};

struct global__ : namespace_t
{
	static constexpr std::array<overloaded_function, 1> functions = { f__{} };

	constexpr global__() noexcept
		: namespace_t("global'", {}, functions, {})
	{}
};
static constexpr inline global__ global_;

namespace reflection
{
	static constexpr inline const namespace_t& global_namespace = global_;
}

/*template <auto f>
constexpr inline auto get_function = nullptr;
template <>
constexpr inline const auto& get_function<f> = */

void f()
{
	Y y;
	int x;

	for (const overloaded_function& f : reflection::global_namespace.get_functions())
	{
		for (const invokable& o : f.get_overloads())
		{
			auto p = o.invoke<Y>(std::array<void*, 5>({ &x, &y, &y, &y, &y }).data());

			p->f();

			break;
		}
		break;
	}
}

int main()
{
	f();

	init();

	std::cout.flush();
	return 0;
}
