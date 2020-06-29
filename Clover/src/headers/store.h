#ifndef STORE_H_INCLUDED
#define STORE_H_INCLUDED

#include <map>
#include <memory>
#include "base_component.h"

namespace ce {
	namespace Core {

		// using unique ptr because the box owns the component.
		using Box = std::map<Entity, std::unique_ptr<BComponent>>;

		/// <summary>
		///		Utility class to add, remove, and get handler on a component from a Box
		/// </summary>
		class CBox {
			public:
				void Add(std::unique_ptr<BComponent> comp);
				BComponent* Get(Entity owner);
				void Remove(Entity owner);

			private:
				Box Components_;
		};

		// Syntaxical sugar
		using Boxes = std::map<CType, CBox>;

		/// <summary>
		///		Keep and owns the components, sorted by types and labelled by their owner.
		/// </summary>
		class Store {
		public:

			Store();

			/// <summary>
			///		Add a component to the boxes and return a pointer on the added component data
			/// </summary>
			/// <typeparam name="T">The concrete component type for the return cast</typeparam>
			/// <param name="comp">The component to add to the store</param>
			/// <returns>nullptr or a pointer to the concrete component data</returns>
			template<class T>
			T* Add(std::unique_ptr<BComponent> comp)
			{
				auto t = comp->Type();

				// find the right box
				auto box = Boxes_.find(t);

				// add the box, it does not exist yet
				if (box == Boxes_.end())
				{
					CBox new_box{};
					Boxes_.emplace(t, std::move(new_box));
					box = Boxes_.find(t);
				}

				auto owner = comp->Owner();

				// move the component unique_ptr ownership to the box where it will live
				box->second.Add(std::move(comp));

				return static_cast<T*>(box->second.Get(owner));
			}

			/// <summary>
			///		Get a raw pointer on the component data
			/// </summary>
			/// <typeparam name="T">Concrete component type</typeparam>
			/// <param name="type">Type id of the component</param>
			/// <param name="owner">Entity that owns the component</param>
			/// <returns>nullptr or a pointer on the component data</returns>
			template<class T>
			T* Get(CType type, Entity owner) {

				auto box = Boxes_.find(type);

				// there is no box for the required type
				if (box == Boxes_.end())
					return nullptr;

				return static_cast<T*>(box->second.Get(owner));
			}

		private:
			Boxes Boxes_;
		};

	}
}

#endif
