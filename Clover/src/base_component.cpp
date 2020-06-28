#include "headers/base_component.h"

namespace ce {
	namespace Core {

		/// <summary>
		///		Constructor
		/// </summary>
		/// <param name="e"> Component's owner </param>
		/// <param name="t"> Component's type </param>
		BComponent::BComponent(Entity e, CType t)
			: Owner_{ e }, Type_{ t }
		{}

		/// <summary>
		///		Move constructor
		/// </summary>
		/// <param name="other"> Base component to be moved </param>
		/// <returns></returns>
		BComponent::BComponent(BComponent&& other) noexcept
			: Owner_{ std::move(other.Owner_) },
			  Type_{ std::move(other.Type_) }
		{}

		/// <summary>
		///		Move assignement
		/// </summary>
		/// <param name="other"> Base component to be moved </param>
		/// <returns></returns>
		BComponent & BComponent::operator=(BComponent&& other) noexcept 
		{
			Owner_ = std::move(other.Owner_);
			Type_ = std::move(other.Type_);

			return *this;
		}
	}
}