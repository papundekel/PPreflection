#pragma once
#include "array_type.h"
#include "complete_object_type.h"

namespace PPreflection
{
    class known_bound_array_type : public detail::array_type<complete_object_type>
    {
    public:
        constexpr virtual size_t get_extent() const noexcept = 0;

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
            out.write("[");
            out.write(get_extent());
            out.write("]");
            remove_extent().print_name_suffix(out);
        }
        constexpr size_t size() const noexcept override final
        {
            return get_extent() * remove_extent().size();
        }
        void destroy(void* ptr) const noexcept override final;
    };
}
