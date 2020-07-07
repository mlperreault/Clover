#ifndef CORE_COMPONENTS_H_INCLUDED
#define CORE_COMPONENTS_H_INCLUDED

#include "base_component.h"
#include "entity.h"

namespace ce {
	namespace Core {

		const CType NODE_TYPE = "NODE";

		class Node : public BComponent {
		public:
			Node(Entity o, float xpos, float ypos, float zpos) : BComponent{o, NODE_TYPE} , x{xpos}, y{ypos}, z{zpos}
			{};
			float x;
			float y;
			float z;
		};

	}
}

#endif