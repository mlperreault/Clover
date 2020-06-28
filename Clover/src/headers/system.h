#ifndef SYSTEM_H_INCLUDED
#define SYSTEM_H_INCLUDED

namespace ce {
	namespace Core {

		/// <summary>
		///		Abstract class for systems that needs to update
		/// </summary>
		class System {
		public:
			System() {};

			// let concrete systems implement how they update
			virtual void update(int) = 0;
		};

	}
}

#endif
