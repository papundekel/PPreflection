#pragma once
#include "PP/concepts/derived_from.hpp"
#include "PP/utility/forward.hpp"

#include "descriptor.hpp"

namespace PPreflector
{
	///
	/// @brief Represents an entity, which has a parent.
	///
	/// @tparam DescriptorParent The descriptor class of the parent entity.
	/// @tparam DescriptorBase The base descriptor class.
	///
	template <typename DescriptorParent, typename DescriptorBase>
	requires PP::concepts::derived_from<DescriptorParent, descriptor> &&
		PP::concepts::derived_from<DescriptorBase, descriptor>
	class nested_descriptor : public DescriptorBase
	{
		const DescriptorParent& parent;

	public:
		///
		/// @brief Constructs a new nested descriptor.
		///
		/// @param parent A reference to the parent entity descriptor.
		/// @param args Arguments for the DescriptorBase constructor.
		///
		explicit nested_descriptor(const DescriptorParent& parent,
		                           auto&&... args)
			: DescriptorBase(PP_F(args)...)
			, parent(parent)
		{}

	protected:
		///
		/// @brief @see descriptor::get_parent.
		///
		const DescriptorParent* get_parent(void*) const override final
		{
			return &get_parent();
		}
		///
		/// @brief Gets the parent descriptor.
		///
		/// @return A reference to the parent descriptor.
		///
		const DescriptorParent& get_parent() const
		{
			return parent;
		}
	};
}
