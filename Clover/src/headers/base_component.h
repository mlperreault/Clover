#ifndef BASE_COMPONENT_H_INCLUDED
#define BASE_COMPONENT_H_INCLUDED

#include <utility>
#include <string>
#include "entity.h"

namespace ce {
	namespace Core {

		// identifies components with a type
		using CType = std::string;

		class BComponent {
			
			public:
				Entity Owner() { return Owner_; }
				CType Type() { return Type_; }

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