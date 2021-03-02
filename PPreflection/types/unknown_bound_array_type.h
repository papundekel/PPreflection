#pragma once
#include "array_type.h"
#include "object_type.h"

namespace PPreflection
{
    class unknown_bound_array_type : public detail::array_type<object_type>
    {
    public:
        constexpr bool has_name(PP::string_view) const noexcept override final
        {
            return false; // TODO
        }
        constexpr void print_name_prefix(PP::simple_ostream& out) const noexcept override final
        {
            remove_extent().print_name_prefix(out);
        }
        constexpr void print_name_suffix(PP::simple_ostream& out) const noexcept override final
        {
            out.write("[]");
            remove_extent().print_name_suffix(out);
        }
    };
}
