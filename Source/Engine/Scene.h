#ifndef SCENE_H_
#define SCENE_H_

namespace Marx
{
	/* 
	*	Basic scene will be created as a blank scene for the scene loader.
	*   
	*/
	class Scene
	{
		public:
			Scene();
			
			bool onLoad();
			bool unLoad();
			void events(); 
			void update();
			void draw();
			
		//private:
			// Not sure whats in a Scene yet
	};
} /* namespace Marx */

#endif /* SCENE_H_ */
