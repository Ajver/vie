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

		void appendPointerToObject(vie::Object* ob);
		vie::Object* getPointerToObjectByIndex(size_t id);
		
	private:
		std::vector<vie::Object*> objects;
	};

}
