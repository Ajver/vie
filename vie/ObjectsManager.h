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

		bool containsObjectWithLabel(const std::string& label) const;
		bool containsMouseListenerWithLabel(const std::string& label) const;
		bool containsKeyListenerWithLabel(const std::string& label) const;

		Object* getObject(size_t id) const;
		Object* getMouseListener(size_t id) const;
		Object* getKeyListener(size_t id) const;

		Object* getObjectByLabel(const std::string& label) const;
		Object* getMouseListenerByLabel(const std::string& label) const;
		Object* getKeyListenerByLabel(const std::string& label) const;

		std::vector<Object*> getObjectsVector() const;

		void onKeyPress();
		void onKeyRelease();
		void onMousePress(); 
		void onMouseRelease();
		void onMouseMove();
		void onMouseDrag();

	private:
		std::vector<Object*> objects;
		std::vector<Object*> mouseListeners;
		std::vector<Object*> keyListeners;

		Object* clickedObject;

		void mouseClickedObject(vie::Object* ob);

		bool isNoClickedObject();
		void mouseReleasedClickedObject();
		void mouseReleasedOutsideClickedObject();

		void mouseIsInsideObject(vie::Object* ob);
		void mouseEnteredObject(vie::Object* ob);
		void mouseIsOutsideObject(vie::Object* ob);
		void mouseLeavedObject(vie::Object* ob);
	};

}
