#include "ObjectsManager.h"

#include "Errors.h"

namespace vie
{

	ObjectsManager::ObjectsManager() :
		clickedObject(nullptr)
	{
	}

	ObjectsManager::~ObjectsManager()
	{
	}

	void ObjectsManager::update(float et)
	{
		Object* currentObject = objects[0];
		for (int i = 0; i < objects.size(); i++)
		{
			currentObject->update(et);
			currentObject++;
		}
	}

	void ObjectsManager::render(Graphics* g)
	{
		Object* currentObject = objects[0];
		for (int i = 0; i < objects.size(); i++)
		{
			currentObject->render(g);
			currentObject++;
		}
	}

	void ObjectsManager::appendObject(vie::Object* ob)
	{
		if (ob == nullptr)
		{
			fatalError("ObjectsManager could not append nullptr!");
			return;
		}

		objects.push_back(ob);
	}

	vie::Object* ObjectsManager::getObjectByIndex(size_t id)
	{
		return objects[id];
	}

	void ObjectsManager::appendMouseInteractiveObject(vie::Object* ob)
	{
		if (ob == nullptr)
		{
			fatalError("ObjectsManager could not append nullptr!");
			return;
		}

		mouseInteractiveObjects.push_back(ob);
	}

	vie::Object* ObjectsManager::getMouseInteractiveObjectByIndex(size_t id)
	{
		return mouseInteractiveObjects[id];
	}

	//////////////////////////////////////////////////////////

	void ObjectsManager::onKeyPress(unsigned int keyID)
	{

	}

	void ObjectsManager::onKeyRelease(unsigned int keyID)
	{

	}

	void ObjectsManager::onMousePress(unsigned int keyID, glm::vec2 mousePos)
	{
		Object* currentObject = mouseInteractiveObjects[0];
		for (int i = 0; i < mouseInteractiveObjects.size(); i++)
		{
			if (currentObject->isPointInside(mousePos))
				mouseClickedObject(currentObject);

			currentObject++;
		}
	}

	void ObjectsManager::mouseClickedObject(vie::Object* ob)
	{
		clickedObject = ob;
		ob->onMousePress();
	}

	void ObjectsManager::onMouseRelease(unsigned int keyID, glm::vec2 mousePos)
	{
		if (clickedObject == nullptr)
			return;

		if (clickedObject->isPointInside(mousePos))
			mouseReleasedClickedObject();
		else
			mouseReleasedOutsideClickedObject();

		clickedObject = nullptr;
	}

	void ObjectsManager::mouseReleasedClickedObject()
	{
		clickedObject->onMouseRelease();
	}

	void ObjectsManager::mouseReleasedOutsideClickedObject()
	{
		clickedObject->setIsMouseHover(false);
	}

	void ObjectsManager::onMouseMove(glm::vec2 mousePos) 
	{
		Object* currentObject = mouseInteractiveObjects[0];
		for (int i = 0; i < mouseInteractiveObjects.size(); i++)
		{
			if (currentObject->isPointInside(mousePos))
				mouseIsInsideObject(currentObject);
			else
				mouseIsOutsideObject(currentObject);

			currentObject++;
		}
	}

	void ObjectsManager::mouseIsInsideObject(vie::Object* ob)
	{
		if (!ob->getIsMouseHover())
			mouseEnteredObject(ob);

		ob->onMouseMove();
	}

	void ObjectsManager::mouseEnteredObject(vie::Object* ob)
	{
		ob->setIsMouseHover(true);
		ob->onMouseEnter();
	}

	void ObjectsManager::mouseIsOutsideObject(vie::Object* ob)
	{
		if (ob->getIsMouseHover())
			mouseLeavedObject(ob);
	}

	void ObjectsManager::mouseLeavedObject(vie::Object* ob)
	{
		ob->setIsMouseHover(false);
		ob->onMouseLeave();
	}

	void ObjectsManager::onMouseDrag(glm::vec2 mousePos)
	{
		if (clickedObject != nullptr)
			clickedObject->onMouseDrag();
	}
}
