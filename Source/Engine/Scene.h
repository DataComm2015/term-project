/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: Scene.h
--
-- PROGRAM:
--
-- FUNCTIONS: N/A
--
-- DATE: February 15, 2015
--
-- REVISIONS:
--
-- DESIGNER: Marc Rafanan
--           Marc Vouve
--
-- PROGRAMMER: Marc Rafanan
--
-- NOTES:
--        This file defines the Scene class members
--
----------------------------------------------------------------------------------------------------------------------*/

#ifndef SCENE_H_
#define SCENE_H_

namespace Marx
{
    /* 
    *    Basic scene will be created as a blank scene for the scene loader.
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
            // Not sure what's in a Scene yet
    };
} /* namespace Marx */

#endif /* SCENE_H_ */
