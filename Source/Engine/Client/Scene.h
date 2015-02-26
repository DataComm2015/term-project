#ifndef SCENE_H_
#define SCENE_H_

/**
* The base Scene class can be extended to have other funcitonality, or it can be used as a void
*
*
*
**/
#include <vector>

namespace Marx
{
	class Scene
	{
	public:
		virtual void onLoad();
		virtual void unLoad();
		virtual void processEvents();
		virtual void update();
		virtual void draw();
	};
}

#endif