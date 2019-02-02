#include "ObjectsManager.h"

#include "Errors.h"
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
		for (auto& ob : objects)
			ob->update(et);
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

	void ObjectsManager::removeObject(Object* ob)
	{
		int i = 0;
		for (auto& cob : objects)
			if (cob == ob)
			{
				objects.erase(objects.begin() + i);
				return;
			}
			else
				i++;
	}
	void ObjectsManager::removeMouseListener(Object* ob)
	{
		int i = 0;
		for (auto& cob : mouseListeners)
			if (cob == ob)
			{
				mouseListeners.erase(mouseListeners.begin() + i);
				return;
			}
			else
				i++;
	}
	void ObjectsManager::removeKeyListener(Object* ob)
	{
		int i = 0;
		for (auto& cob : keyListeners)
			if (cob == ob)
			{
				keyListeners.erase(keyListeners.begin() + i);
				return;
			}
			else
				i++;
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
		for (auto& ob : keyListeners)
			ob->onKeyPress();
	}
	void ObjectsManager::onKeyRelease()
	{
		for (auto& ob : keyListeners)
			ob->onKeyRelease();
	}

	void ObjectsManager::onMousePress()
	{
		for (auto& ob : mouseListeners)
			if (ob->isPointInside(Input::getMousePosition()))
				mouseClickedObject(ob);
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
		for(auto& ob : mouseListeners)
			if (ob->isPointInside(Input::getMousePosition()))
				mouseIsInsideObject(ob);
			else
				mouseIsOutsideObject(ob);
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
