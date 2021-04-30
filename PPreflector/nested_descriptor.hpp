#pragma once
#include "PP/concepts/derived_from.hpp"
#include "PP/utility/forward.hpp"

#include "descriptor.hpp"

namespace PPreflector
{
	template <typename DescriptorParent, typename DescriptorBase>
	requires PP::concepts::derived_from<DescriptorParent, descriptor>&&
		PP::concepts::derived_from<DescriptorBase,
								   descriptor> class nested_descriptor
		: public DescriptorBase
	{
		const DescriptorParent& parent;

	public:
		explicit nested_descriptor(const DescriptorParent& parent,
								   auto&&... args)
			: DescriptorBase(PP_FORWARD(args)...)
			, parent(parent)
		{}

	protected:
		const DescriptorParent* get_parent(void*) const override final
		{
			return &get_parent();
		}
		const DescriptorParent& get_parent() const
		{
			return parent;
		}
	};
}
