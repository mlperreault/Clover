#include <memory>

#include "headers/store.h"
#include "headers/base_component.h"

namespace ce {
	namespace Core {

		/// <summary>
		///		Add a component to the box
		/// </summary>
		/// <param name="comp">The component to add to the box</param>
		void CBox::Add(std::unique_ptr<BComponent> comp)
		{
			auto owner = comp->Owner();
			Components_.emplace(owner, std::move(comp));
		}

		/// <summary>
		///		Get a component in this box for the entity
		/// </summary>
		/// <param name="owner">Owner of the component</param>
		/// <returns>nullptr or a pointer on the component data</returns>
		BComponent* CBox::Get(Entity owner)
		{
			auto found = Components_.find(owner);

			if (found != Components_.end())
			{
				return found->second.get();
			}

			return nullptr;
		}

		/// <summary>
		///		Remove a component in this box for the entity
		/// </summary>
		/// <param name="owner">Owner of the component</param>
		void CBox::Remove(Entity owner)
		{
			Components_.erase(owner);
		}

		/// <summary>
		///		Constructor
		/// </summary>
		/// <returns></returns>
		Store::Store() {}
	}
}