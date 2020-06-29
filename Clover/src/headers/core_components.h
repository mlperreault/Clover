#ifndef CORE_COMPONENTS_H_INCLUDED
#define CORE_COMPONENTS_H_INCLUDED

#include "base_component.h"
#include "entity.h"

namespace ce {
	namespace Core {

		const CType NODE_TYPE = "NODE";

		class Node : public BComponent {
		public:
			Node(Entity o, int xpos, int ypos, int zpos) : BComponent{o, NODE_TYPE} , x{xpos}, y{ypos}, z{zpos}
			{};
			int x;
			int y;
			int z;
		};
	}
}

#endif