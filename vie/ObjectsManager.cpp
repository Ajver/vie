#include "ObjectsManager.h"

#include "Logger.h"
#include "Input.h"

#include <iostream>
#include <algorithm>

namespace vie
{

	ObjectsManager::ObjectsManager() :
		clickedObject(nullptr)
	{
	}

	ObjectsManager::~ObjectsManager()
	{
		objects.clear();
		mouseListeners.clear();
		keyListeners.clear();
	}

	void ObjectsManager::update(float et)
	{
		for (int i = objects.size() - 1; i >= 0; i--)
		{
			if (i < objects.size())
			{
				Object* ob = *(&objects[0] + i);
				ob->update(et);
			}
		}
	}
	void ObjectsManager::render(Graphics* g)
	{
		for (auto& ob : objects)
			ob->render(g);
	}

	void ObjectsManager::appendObject(Object* ob)
	{
		objects.push_back(ob);
	}
	void ObjectsManager::appendMouseListener(Object* ob)
	{
		mouseListeners.push_back(ob);
	}
	void ObjectsManager::appendKeyListener(Object* ob)
	{
		keyListeners.push_back(ob);
	}
	void ObjectsManager::appendAll(Object* ob)
	{
		appendObject(ob);
		appendMouseListener(ob);
		appendKeyListener(ob);
	}

	Object* ObjectsManager::getObject(size_t id) const
	{
		return objects[id];
	}
	Object* ObjectsManager::getMouseListener(size_t id) const
	{
		return mouseListeners[id];
	}
	Object* ObjectsManager::getKeyListener(size_t id) const
	{
		return keyListeners[id];
	}

	Object* ObjectsManager::getObjectByLabel(const std::string& label) const
	{
		for (auto& ob : objects)
			if (ob->isLabeled(label))
				return ob;

		return nullptr;
	}
	Object* ObjectsManager::getMouseListenerByLabel(const std::string& label) const
	{
		for (auto& ob : mouseListeners)
			if (ob->isLabeled(label))
				return ob;

		return nullptr;
	}
	Object* ObjectsManager::getKeyListenerByLabel(const std::string& label) const
	{
		for (auto& ob : keyListeners)
			if (ob->isLabeled(label))
				return ob;

		return nullptr;
	}

	void ObjectsManager::removeObject(Object* rob)
	{
		auto it = std::find(objects.begin(), objects.end(), rob);
		if (it != objects.end())
			objects.erase(it);
	}
	void ObjectsManager::removeMouseListener(Object* rob)
	{
		auto it = std::find(mouseListeners.begin(), mouseListeners.end(), rob);
		if (it != mouseListeners.end())
			mouseListeners.erase(it);
	}
	void ObjectsManager::removeKeyListener(Object* rob)
	{
		auto it = std::find(keyListeners.begin(), keyListeners.end(), rob);
		if (it != keyListeners.end())
			keyListeners.erase(it);
	}
	void ObjectsManager::removeAll(Object* ob)
	{
		removeObject(ob);
		removeMouseListener(ob);
		removeKeyListener(ob);
	}

	void ObjectsManager::destroyObject(Object* &ob)
	{
		removeAll(ob);
		delete ob;
		ob = nullptr;
	}

	bool ObjectsManager::containsObject(Object* ob) const
	{
		return std::find(objects.begin(), objects.end(), ob) != objects.end();
	}
	bool ObjectsManager::containsMouseListener(Object* ob) const
	{
		return std::find(mouseListeners.begin(), mouseListeners.end(), ob) != mouseListeners.end();
	}
	bool ObjectsManager::containsKeyListener(Object* ob) const
	{
		return std::find(keyListeners.begin(), keyListeners.end(), ob) != keyListeners.end();
	}

	bool ObjectsManager::containsObjectWithLabel(const std::string& label) const
	{
		return getObjectByLabel(label) != nullptr;
	}
	bool ObjectsManager::containsMouseListenerWithLabel(const std::string& label) const
	{
		return getMouseListenerByLabel(label) != nullptr;
	}
	bool ObjectsManager::containsKeyListenerWithLabel(const std::string& label) const
	{
		return getKeyListenerByLabel(label) != nullptr;
	}

	void ObjectsManager::onKeyPress()
	{
		for (int i = keyListeners.size() - 1; i >= 0; i--)
		{
			if (i < keyListeners.size())
			{
				Object* ob = *(&keyListeners[0] + i);
				ob->onKeyPress();
			}
		}
	}
	void ObjectsManager::onKeyRelease()
	{
		for (int i = keyListeners.size() - 1; i >= 0; i--)
		{
			if (i < keyListeners.size())
			{
				Object* ob = *(&keyListeners[0] + i);
				ob->onKeyRelease();
			}
		}
	}

	void ObjectsManager::onMousePress()
	{
		for (int i = mouseListeners.size() - 1; i >= 0; i--)
		{
			if (i < mouseListeners.size())
			{
				Object* ob = *(&mouseListeners[0] + i);
				if (ob->isPointInside(Input::getMousePosition()))
					mouseClickedObject(ob);
			}
		}
	}
	void ObjectsManager::mouseClickedObject(Object* ob)
	{
		clickedObject = ob;
		ob->onMousePress();
	}
	void ObjectsManager::onMouseRelease()
	{
		if (isNoClickedObject())
			return;

		if (clickedObject->isPointInside(Input::getMousePosition()))
			mouseReleasedClickedObject();
		else
			mouseReleasedOutsideClickedObject();

		clickedObject = nullptr;
	}

	bool ObjectsManager::isNoClickedObject()
	{
		return clickedObject == nullptr;
	}

	void ObjectsManager::mouseReleasedClickedObject()
	{
		clickedObject->onMouseRelease();
	}

	void ObjectsManager::mouseReleasedOutsideClickedObject()
	{
		clickedObject->setIsMouseHover(false);
	}

	void ObjectsManager::onMouseMove() 
	{
		for (int i = mouseListeners.size() - 1; i >= 0; i--)
		{
			if (i < mouseListeners.size())
			{
				Object* ob = *(&mouseListeners[0] + i);
				if (ob->isPointInside(Input::getMousePosition()))
					mouseIsInsideObject(ob);
				else
					mouseIsOutsideObject(ob);
			}
		}
	}

	void ObjectsManager::mouseIsInsideObject(Object* ob)
	{
		if (!ob->getIsMouseHover())
			mouseEnteredObject(ob);

		ob->onMouseMove();
	}

	void ObjectsManager::mouseEnteredObject(Object* ob)
	{
		ob->setIsMouseHover(true);
		ob->onMouseEnter();
	}

	void ObjectsManager::mouseIsOutsideObject(Object* ob)
	{
		if (ob->getIsMouseHover())
			mouseLeavedObject(ob);
	}

	void ObjectsManager::mouseLeavedObject(Object* ob)
	{
		ob->setIsMouseHover(false);
		ob->onMouseLeave();
	}

	void ObjectsManager::onMouseDrag()
	{
		if (isNoClickedObject())
			return;

		clickedObject->onMouseDrag();
	}

	std::vector<Object*> ObjectsManager::getObjectsVector() const
	{
		return objects;
	}

}
