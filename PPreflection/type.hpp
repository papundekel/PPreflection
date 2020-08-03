#pragma once
#include "descriptor.hpp"

class type : public descriptor
{
public:
	enum class category
	{
		basic,
		lreference,
		rreference,
		pointer
	};

	constexpr virtual const type* get_inner_type() const noexcept = 0;
	constexpr virtual category get_category() const noexcept = 0;
	constexpr virtual bool get_constness() const noexcept = 0;
	constexpr virtual std::size_t size() const noexcept = 0;
	constexpr virtual void destroy(void* ptr) const noexcept = 0;

	constexpr bool operator==(const type& other) const noexcept
	{
		return get_category() == other.get_category() &&
			(
				(get_category() == category::basic && this == &other) ||
				*get_inner_type() == *other.get_inner_type()
			);
	}

	static constexpr bool convertible(const type& a, const type& b) noexcept
	{
		// TODO
		return true;
	}
};

class basic_type : public type
{
	const char* name;
	std::size_t size_;
	void (*destructor)(void*);

	constexpr basic_type(const char* name, std::size_t size, void (*destructor)(void*))
		: name(name)
		, size_(size)
		, destructor(destructor)
	{}

public:
	template <typename T>
	static constexpr auto create(const char* name)
	{
		return basic_type(name, sizeof(T), ~T);
	}

	constexpr void print_name(simple_ostream& out) const noexcept override
	{
		out.write(name);
	}
	constexpr const type* get_inner_type() const noexcept override
	{
		return nullptr;
	}
	constexpr category get_category() const noexcept override
	{
		return category::basic;
	}
	constexpr bool get_constness() const noexcept override
	{
		return false;
	}
	constexpr std::size_t size() const noexcept override
	{
		return size_;
	}
	constexpr void destroy(void* ptr) const noexcept override
	{

	}
};

class compound_type : public type
{
protected:
	const type& inner_type;

public:
	compound_type(const type& inner_type)
		: inner_type(inner_type)
	{}

	constexpr const type* get_inner_type() const noexcept final
	{
		return &inner_type;
	}
};

class pointer_type : public compound_type
{
public:
	pointer_type(const type& inner_type)
		: compound_type(inner_type)
	{}

	constexpr void print_name(simple_ostream& out) const noexcept override
	{
		inner_type.print_name(out);
		out.write("*");
	}
	constexpr category get_category() const noexcept final
	{
		return category::pointer;
	}
	constexpr bool get_constness() const noexcept final
	{
		return false;
	}
};

class lreference_type : public compound_type
{
public:
	lreference_type(const type& inner_type)
		: compound_type(inner_type)
	{}

	constexpr void print_name(simple_ostream& out) const noexcept override
	{
		inner_type.print_name(out);
		out.write("&");
	}
	constexpr category get_category() const noexcept final
	{
		return category::lreference;
	}
	constexpr bool get_constness() const noexcept final
	{
		return false;
	}
};

class rreference_type : public compound_type
{
public:
	rreference_type(const type& inner_type)
		: compound_type(inner_type)
	{}

	constexpr void print_name(simple_ostream& out) const noexcept override
	{
		inner_type.print_name(out);
		out.write("&&");
	}
	constexpr category get_category() const noexcept final
	{
		return category::rreference;
	}
	constexpr bool get_constness() const noexcept final
	{
		return false;
	}
};

class const_type : public compound_type
{
public:
	const_type(const type& inner_type)
		: compound_type(inner_type)
	{}

	constexpr void print_name(simple_ostream& out) const noexcept override
	{
		inner_type.print_name(out);
		out.write(" const");
	}
	constexpr category get_category() const noexcept final
	{
		return inner_type.get_category();
	}
	constexpr bool get_constness() const noexcept final
	{
		return true;
	}
};
