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
		void appendMouseListener(Object* ob);
		void appendKeyListener(Object* ob);

		void removeObject(Object* ob);
		void removeMouseListener(Object* ob);
		void removeKeyListener(Object* ob);

		bool containsObject(Object* ob) const;
		bool containsMouseListener(Object* ob) const;
		bool containsKeyListener(Object* ob) const;

		Object* getObject(size_t id) const;
		Object* getMouseListener(size_t id) const;
		Object* getKeyListener(size_t id) const;

		void onKeyPress();
		void onKeyRelease();

		void onMousePress(); 
		void mouseClickedObject(vie::Object* ob);

		void onMouseRelease();
		bool isNoClickedObject();
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
		std::vector<Object*> mouseListeners;
		std::vector<Object*> keyListeners;

		Object* clickedObject;

		void forAllObjectsRunFunction(const std::vector<Object*>& vtr, void(*fnc)(ObjectsManager*, Object*));
		void forAllObjectsRunFunction(const std::vector<Object*>& vtr, void(*fnc)(Object*));
	};

}
