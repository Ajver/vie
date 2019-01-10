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

		void appendObject(vie::Object* ob);
		void appendMouseInteractiveObject(vie::Object* ob);
		void appendKeyInteractiveObject(vie::Object* ob);

		vie::Object* getObject(size_t id) const;
		vie::Object* getMouseInteractiveObject(size_t id) const;
		vie::Object* getKeyInteractiveObject(size_t id) const;

		void onKeyPress(unsigned int keyID);
		void onKeyRelease(unsigned int keyID);

		void onMousePress(unsigned int keyID);
		void mouseClickedObject(vie::Object* ob, unsigned int keyID);

		void onMouseRelease(unsigned int keyID);
		void mouseReleasedClickedObject(unsigned int keyID);
		void mouseReleasedOutsideClickedObject();
		
		void onMouseMove();
		void* checkMouseMoved(vie::Object* ob);
		void mouseIsInsideObject(vie::Object* ob);
		void mouseEnteredObject(vie::Object* ob);
		void mouseIsOutsideObject(vie::Object* ob);
		void mouseLeavedObject(vie::Object* ob);

		void onMouseDrag();

	private:
		std::vector<vie::Object*> objects;
		std::vector<vie::Object*> mouseInteractiveObjects;
		std::vector<vie::Object*> keyInteractiveObjects;

		vie::Object* clickedObject;

		void forAllElementsRunFunction(const std::vector<vie::Object*>& vtr, void* ObjectsManager::* fnc(vie::Object* ob)) const;
	};

}
