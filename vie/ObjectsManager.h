#pragma once

#include <vector>

#include "Graphics.h"
#include "Object.h"

namespace vie
{

	class ObjectsManager
	{
	public:
		ObjectsManager();
		~ObjectsManager();

		void update(float et);
		void render(Graphics* g);

		void appendObject(Object* ob);
		void appendMouseInteractiveObject(Object* ob);
		void appendKeyInteractiveObject(Object* ob);

		Object* getObject(size_t id) const;
		Object* getMouseInteractiveObject(size_t id) const;
		Object* getKeyInteractiveObject(size_t id) const;

		void onKeyPress();
		void onKeyRelease();

		void onMousePress(); 
		void mouseClickedObject(vie::Object* ob);

		void onMouseRelease();
		void mouseReleasedClickedObject();
		void mouseReleasedOutsideClickedObject();
		
		void onMouseMove();
		void mouseIsInsideObject(vie::Object* ob);
		void mouseEnteredObject(vie::Object* ob);
		void mouseIsOutsideObject(vie::Object* ob);
		void mouseLeavedObject(vie::Object* ob);

		void onMouseDrag();

	private:
		std::vector<Object*> objects;
		std::vector<Object*> mouseInteractiveObjects;
		std::vector<Object*> keyInteractiveObjects;

		Object* clickedObject;

		void forAllObjectsRunFunction(const std::vector<Object*>& vtr, void(*fnc)(ObjectsManager*, Object*));
		void forAllObjectsRunFunction(const std::vector<Object*>& vtr, void(*fnc)(Object*));
	};

}
