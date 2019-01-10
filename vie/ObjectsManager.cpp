#include "ObjectsManager.h"

#include "Errors.h"

namespace vie
{

	ObjectsManager::ObjectsManager()
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

	void ObjectsManager::appendPointerToObject(vie::Object* ob)
	{
		if (ob == nullptr)
		{
			fatalError("ObjectsManager could not append nullptr!");
			return;
		}
		objects.push_back(ob);
	}

	vie::Object* ObjectsManager::getPointerToObjectByIndex(size_t id)
	{
		return objects[id];
	}

}
