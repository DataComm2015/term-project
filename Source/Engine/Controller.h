#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <vector>
#include "Event.h"

namespace Marx
{
	/*
	* Controller class. Holds controller event queue
	*/
	class Controller
	{
		public:
			vector<Event> eventQueue_;
			virtual vector<Event> getEvents() = 0;
			virtual void gameAction(Event) = 0;
	};
}

#endif /* CONTROLLER_H_ */
