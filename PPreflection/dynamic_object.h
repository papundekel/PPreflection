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
		};

	private:
		struct void_tag {};

		union data
		{
			alignas(max_align_t) char* ptr;
			invalid_code code;

			constexpr data() noexcept
				: ptr(nullptr)
			{}
			explicit constexpr data(invalid_code code) noexcept
				: code(code)
			{}
			explicit constexpr data(char* ptr) noexcept
				: ptr(ptr)
			{}
		};

		class deleter
		{
			struct optional_cv_type
			{
				const complete_object_type* type;
				PP::cv_qualifier cv;
			};

			struct releaser
			{
				constexpr optional_cv_type operator()(optional_cv_type& u) const noexcept
				{
					return PP::exchange(u, optional_cv_type{nullptr, PP::cv_qualifier::none});
				}
			};

			PP::unique<optional_cv_type, releaser> type_;

		public:
			constexpr deleter(cv_type<complete_object_type> t) noexcept;
			constexpr deleter(int = 0) noexcept
				: type_(PP::unique_default_releaser_tag, nullptr, PP::cv_qualifier::none)
			{}
			constexpr void operator()(PP::unique<data, PP::default_releaser>& u) const;

			constexpr bool has_valid_type() const
			{
				return type_.get_object().type;
			}
			constexpr cv_type<complete_object_type> get_cv_type() const;
		};

		PP::scoped<PP::unique<data, PP::default_releaser>, deleter> x;

		static constexpr auto* get_address(auto& r) noexcept;
		static constexpr auto* get_address(auto& p, const complete_object_type& t) noexcept;

		static constexpr dynamic_reference reference_cast_helper(auto& r) noexcept;

		static constexpr char* allocate_and_initialize(PP::concepts::invocable auto&& i) noexcept;

		explicit constexpr dynamic_object(invalid_code code) noexcept;

		constexpr bool invalid_check_helper(invalid_code code) const noexcept;

		constexpr bool has_valid_type() const noexcept
		{
			return x.get_destructor().has_valid_type();
		}

	public:
		static constexpr dynamic_object create_invalid(invalid_code code) noexcept
		{
			return dynamic_object(code);
		}
		static constexpr dynamic_object create_void() noexcept
		{
			return dynamic_object(invalid_code::none);
		}

		static constexpr dynamic_object create(PP::concepts::type auto t, auto&&... args);

		constexpr dynamic_object() = default;

		constexpr cv_type<complete_object_type> get_cv_type()       noexcept;
		constexpr cv_type<complete_object_type> get_cv_type() const noexcept;

		constexpr operator dynamic_reference()       noexcept;
		constexpr operator dynamic_reference() const noexcept;

		constexpr explicit operator bool() const noexcept;
		constexpr invalid_code get_error_code() const noexcept;
		constexpr bool is_void() const noexcept;

		explicit constexpr dynamic_object(PP::concepts::invocable auto&& initializer);
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
