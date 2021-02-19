#pragma once
#include "../../functions/constructor.h"
#include "../../functions/member_function.h"
#include "../../functions/static_member_function.h"
#include "../../reflect.h"
#include "../class_type.h"
#include "basic_user_defined_type.hpp"
#include "concepts/class.hpp"
#include "concepts/derived_from.hpp"
#include "concepts/destructible.hpp"
#include "destroy_at.hpp"

namespace PPreflection::detail
{
	template <typename T, typename Base>
	class basic_class_type : public basic_user_defined_type<T, Base>
	{
		static_assert(PP::concepts::derived_from<Base, class_type>);
		static_assert(PP::concepts::class_type<T>);

		//static constexpr auto static_member_functions =
		//	reflect_many(reflect(PP::type<tags::static_member_functions<T>>), PP::type<const static_member_function::overloaded&>);
		//static constexpr auto member_functions =
		//	reflect_many(reflect(PP::type<tags::member_functions<T>>), PP::type<const member_function::overloaded&>);
		static constexpr auto nested_classes =
			reflect_many(reflect(PP::type<tags::nested_classes<T>>), PP::type<const user_defined_type&>);

	public:
		void destroy(void* ptr) const noexcept override final
		{
			if constexpr (PP::concepts::destructible<T>)
				PP::destroy_at(reinterpret_cast<T*>(ptr));
		}

		/*constexpr const overloaded_constructor& get_constructors() const noexcept override final
		{
			return reflect(PP::type<tags::constructors<T>>);
		}*/
		/*constexpr PP::any_view<PP::iterator_category::ra, const member_function::overloaded&> get_member_functions() const noexcept override final
		{
			return member_functions;
		}*/
		/*constexpr PP::any_view<PP::iterator_category::ra, const static_member_function::overloaded&> get_static_member_functions() const noexcept override final
		{
			return static_member_functions;
		}*/

		constexpr PP::any_view<PP::iterator_category::ra, const user_defined_type&> get_nested_classes() const noexcept override final
		{
			return nested_classes;
		}
	};
}
