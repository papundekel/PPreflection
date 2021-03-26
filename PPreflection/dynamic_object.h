#pragma once
#include "PP/concepts/invocable.hpp"
#include "PP/concepts/same_except_cvref.hpp"
#include "PP/get_type.hpp"
#include "PP/scoped.hpp"
#include "PP/string_view.hpp"
#include "PP/unique.hpp"

namespace PPreflection
{
	class complete_object_type;
	class dynamic_reference;
	template <typename>
	class cv_type;

	class dynamic_object
	{
	public:
		enum class invalid_code
		{
			none,

			implicit_conversion_error,
			indestructible_return_value,
			no_valid_overload,
			overload_resolution_error,
		};

	private:
		struct void_tag {};

		union data
		{
			alignas(max_align_t) void* ptr;
			invalid_code code;

			constexpr data() noexcept
				: ptr(nullptr)
			{}
			explicit constexpr data(invalid_code code) noexcept
				: code(code)
			{}
			explicit constexpr data(void* ptr) noexcept
				: ptr(ptr)
			{}
		};

		class deleter
		{
			PP::unique<const complete_object_type*, PP::pointer_releaser> type_;
			PP::cv_qualifier cv;

		public:
			constexpr deleter(cv_type<complete_object_type> t) noexcept;
			constexpr deleter(int = 0) noexcept
				: type_(PP::unique_default_releaser_tag, nullptr)
			{}

			constexpr void operator()(PP::unique<data, PP::default_releaser>& u) const;
			constexpr const complete_object_type& get_type() const;
			constexpr PP::cv_qualifier get_cv() const;
			constexpr bool has_valid_type() const
			{
				return type_.get_object();
			}
			constexpr void change_type(const complete_object_type& target_type)
			{
				type_.get_object() = &target_type;
			}
		};

		class allocated_ptr
		{
			void* ptr;
			bool small;

		public:
			constexpr allocated_ptr() noexcept
				: ptr(nullptr)
				, small(true)
			{}
			constexpr allocated_ptr(void* ptr) noexcept
				: ptr(ptr)
				, small(false)
			{}

			constexpr void* initialize_and_get(auto i) noexcept
			{
				i(small ? &ptr : ptr);
				return ptr;
			}
		};

	private:
		PP::scoped<PP::unique<data, PP::default_releaser>, deleter> x;

	public:
		dynamic_object() = default;
		dynamic_object(dynamic_object&&) = default;
		explicit constexpr dynamic_object(PP::concepts::invocable auto&& initializer);

	private:
		explicit constexpr dynamic_object(invalid_code code) noexcept
			: x(PP::in_place_tag, 0, PP::unique_default_releaser_tag, code)
		{}
		constexpr dynamic_object(cv_type<complete_object_type> cv_type, void* data) noexcept;

	public:
		dynamic_object& operator=(dynamic_object&&) = default;

		static constexpr dynamic_object create_invalid(invalid_code code) noexcept
		{
			return dynamic_object(code);
		}
		static constexpr dynamic_object create_void() noexcept
		{
			return dynamic_object(invalid_code::none);
		}

		static constexpr dynamic_object create(PP::concepts::type auto t, auto&&... args);
		static constexpr dynamic_object create_shallow_copy(dynamic_reference r) noexcept;

		constexpr cv_type<complete_object_type> get_cv_type() const noexcept;

		constexpr const complete_object_type& get_type() const noexcept;

		constexpr operator dynamic_reference() const;
		constexpr dynamic_reference move() const;

		constexpr explicit operator bool() const noexcept;
		constexpr invalid_code get_error_code() const noexcept;
		constexpr bool is_void() const noexcept;

		constexpr dynamic_object cast(const complete_object_type& target_type) && noexcept
		{
			auto temp = PP::move(*this);
			temp.x.get_destructor().change_type(target_type);
			return PP::move(temp);
		}
	
	private:
		static constexpr auto* get_address(auto& r) noexcept;
		static constexpr auto* get_address(auto& p, const complete_object_type& t) noexcept;

		static constexpr dynamic_reference reference_cast_helper(PP::concepts::value auto rvalue) const;

		static constexpr allocated_ptr allocate(const complete_object_type& t) noexcept;
		static constexpr void* allocate_and_initialize(PP::concepts::invocable auto&& i) noexcept;

		constexpr bool has_valid_type() const noexcept
		{
			return x.get_destructor().has_valid_type();
		}
	};

	static constexpr PP::string_view code_to_string(dynamic_object::invalid_code code) noexcept
	{
		switch (code)
		{
		case dynamic_object::invalid_code::none:
			return "none";
		case dynamic_object::invalid_code::implicit_conversion_error:
			return "implicit_conversion_error";
		case dynamic_object::invalid_code::indestructible_return_value:
			return "indestructible_return_value";
		default:
			return "";
		}
	}
}
