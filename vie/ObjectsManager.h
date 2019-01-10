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
		vie::Object* getObjectByIndex(size_t id);

		void appendMouseInteractiveObject(vie::Object* ob);
		vie::Object* getMouseInteractiveObjectByIndex(size_t id);
		
		void onKeyPress(unsigned int keyID);
		void onKeyRelease(unsigned int keyID);

		void onMousePress(unsigned int keyID, glm::vec2 mousePos);
		void mouseClickedObject(vie::Object* ob);

		void onMouseRelease(unsigned int keyID, glm::vec2 mousePos);
		void mouseReleasedClickedObject();
		void mouseReleasedOutsideClickedObject();
		
		void onMouseMove(glm::vec2 mousePos);
		void mouseIsInsideObject(vie::Object* ob);
		void mouseEnteredObject(vie::Object* ob);
		void mouseIsOutsideObject(vie::Object* ob);
		void mouseLeavedObject(vie::Object* ob);

		void onMouseDrag(glm::vec2 mousePos);

	private:
		std::vector<vie::Object*> objects;
		std::vector<vie::Object*> mouseInteractiveObjects;

		vie::Object* clickedObject;
	};

}
