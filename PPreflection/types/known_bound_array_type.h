#pragma once
#include "array_type.h"
#include "complete_object_type.h"

namespace PPreflection
{
    class known_bound_array_type : public detail::array_type<complete_object_type>
    {
    public:
		constexpr PP::variant<const known_bound_array_type&, const non_array_object_type&> cast_down(PP::overload_tag<complete_object_type>) const noexcept override final
        {
            return {PP::placeholder, *this};
        }

        constexpr virtual PP::size_t get_extent() const noexcept = 0;

        constexpr bool has_name(PP::string_view) const noexcept override final
        {
            return false;
        }
        constexpr void print_name_prefix(PP::simple_ostream& out) const noexcept override final
        {
            remove_extent().print_name_prefix(out);
        }
        constexpr void print_name_suffix(PP::simple_ostream& out) const noexcept override final
        {
            out.write("[");
            out.write(get_extent());
            out.write("]");
            remove_extent().print_name_suffix(out);
        }
        constexpr PP::size_t size() const noexcept override final
        {
            return get_extent() * remove_extent().type.size();
        }
        void destroy(void* ptr) const noexcept override final;

        constexpr bool operator==(const known_bound_array_type& other) const noexcept;
        constexpr bool operator==(const type& other) const noexcept override final
		{
			return compare(*this, other);
		}
    };
}
