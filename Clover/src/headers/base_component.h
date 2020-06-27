#ifndef BASE_COMPONENT_H_INCLUDED
#define BASE_COMPONENT_H_INCLUDED

#include <utility>
#include "entity.h"

namespace ce {
	namespace core {

		// identifies components with a type
		using CType = std::size_t;

		class BComponent {
			protected:
				// protected constructor, must implement concrete classes
				BComponent(Entity e, CType t);

				// not copyable
				BComponent(BComponent const&) = delete;
				BComponent& operator=(BComponent const&) = delete;

				// movable
				BComponent(BComponent&& other) noexcept;
				BComponent& operator=(BComponent&& other) noexcept;

			private:

				// entities that owns the component
				Entity Owner_;
				CType Type_;

		};
	}
}

#endif