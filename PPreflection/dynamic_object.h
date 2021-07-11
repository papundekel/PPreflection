#pragma once
#include <cstddef>
#include <variant>

#include "PP/concepts/invocable.hpp"
#include "PP/concepts/same_except_cvref.hpp"
#include "PP/get_type.hpp"
#include "PP/movable.hpp"
#include "PP/scoped.hpp"
#include "PP/string_view.hpp"

namespace PPreflection
{
	class complete_object_type;
	class dynamic_reference;
	template <typename>
	class cv_type;

	class dynamic_object
	{
		friend class null_type;

	public:
		enum class invalid_code
		{
			none,

			implicit_conversion_error,
			indestructible_return_value,
			no_valid_overload,
			overload_resolution_error,
			abstract_class,
		};

	private:
		struct void_tag
		{};

		struct small_byte_array
		{
			alignas(std::max_align_t) char bytes[sizeof(void*)];
		};

		union data
		{
			small_byte_array small_bytes;
			void* ptr;
			invalid_code code;

			constexpr data() noexcept
				: ptr(nullptr)
			{}
			explicit constexpr data(invalid_code code) noexcept
				: code(code)
			{}
			explicit constexpr data(small_byte_array small_bytes) noexcept
				: small_bytes(small_bytes)
			{}
			explicit constexpr data(void* ptr) noexcept
				: ptr(ptr)
			{}
		};

		class allocated_ptr
		{
			union
			{
				small_byte_array small_bytes;
				void* ptr;
			};
			bool is_small;

		public:
			constexpr allocated_ptr(void* ptr) noexcept
				: ptr(ptr)
				, is_small(false)
			{}
			constexpr allocated_ptr() noexcept
				: small_bytes()
				, is_small(true)
			{}

			constexpr data initialize_and_get(auto initializer) noexcept
			{
				initializer(is_small ? &small_bytes : ptr);

				if (is_small)
					return data(small_bytes);
				else
					return data(ptr);
			}
		};

		class deleter
		{
			PP::movable<const complete_object_type*, PP::nullptr_releaser>
				type_;
			PP::cv_qualifier cv;

		public:
			constexpr deleter(cv_type<complete_object_type> t) noexcept;
			constexpr deleter(int = 0) noexcept
				: type_(PP::movable_default_releaser_tag, nullptr)
			{}

			constexpr void operator()(
				PP::movable<data, PP::default_releaser>& u) const;
			constexpr const complete_object_type& get_type() const;
			constexpr PP::cv_qualifier get_cv() const;
			constexpr bool has_valid_type() const
			{
				return type_[PP::tags::o];
			}
			constexpr void change_type(const complete_object_type& target_type)
			{
				type_[PP::tags::o] = &target_type;
			}
		};

	private:
		PP::scoped<PP::movable<data, PP::default_releaser>, deleter> x;

	public:
		dynamic_object() = default;
		dynamic_object(dynamic_object&&) = default;
		explicit constexpr dynamic_object(
			PP::concepts::invocable auto&& initializer);

	private:
		explicit constexpr dynamic_object(invalid_code code) noexcept
			: x(PP::in_place_tag, 0, PP::movable_default_releaser_tag, code)
		{}
		constexpr dynamic_object(
			cv_type<complete_object_type> cv_type,
			PP::concepts::invocable auto&& initializer) noexcept;
		constexpr dynamic_object(cv_type<complete_object_type> cv_type,
								 data data) noexcept;

	public:
		dynamic_object& operator=(dynamic_object&&) = default;

		static constexpr dynamic_object create_invalid(
			invalid_code code) noexcept
		{
			return dynamic_object(code);
		}
		static constexpr dynamic_object create_void() noexcept
		{
			return dynamic_object(invalid_code::none);
		}

		static constexpr dynamic_object create(PP::concepts::type auto t,
											   auto&&... args);
		static constexpr dynamic_object create_copy(auto&& arg);
		static dynamic_object create_shallow_copy(dynamic_reference r) noexcept;

		constexpr cv_type<complete_object_type> get_cv_type() const noexcept;

		constexpr const complete_object_type& get_type() const noexcept;

		constexpr operator dynamic_reference() const;
		constexpr dynamic_reference move() const;

		constexpr explicit operator bool() const noexcept;
		constexpr invalid_code get_error_code() const noexcept;
		constexpr bool is_void() const noexcept;

		constexpr dynamic_object cast(
			const complete_object_type& target_type) && noexcept
		{
			auto temp = PP::move(*this);
			temp.x.get_destructor().change_type(target_type);
			return PP::move(temp);
		}

	private:
		static constexpr auto* get_address(
			auto& unique,
			const complete_object_type& t) noexcept;
		constexpr const void* get_address() const noexcept;

		constexpr dynamic_reference reference_cast_helper(
			PP::concepts::value auto rvalue) const;

		static allocated_ptr allocate(const auto& t) noexcept;

		static constexpr data allocate_and_initialize(
			PP::concepts::invocable auto&& i) noexcept;

		constexpr bool has_valid_type() const noexcept
		{
			return x.get_destructor().has_valid_type();
		}
	};

	static constexpr PP::string_view code_to_string(
		dynamic_object::invalid_code code) noexcept
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
