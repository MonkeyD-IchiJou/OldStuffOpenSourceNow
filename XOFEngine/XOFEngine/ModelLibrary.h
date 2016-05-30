#ifndef MODEL_LIBRARY_H
#define MODEL_LIBRARY_H

#include <map>
#include <string>

using std::string;
using std::map;

namespace pp
{
	// this class will keep all the game assets
	class Mesh;
	class lua_backend;

	class ModelLibrary
	{
	public:
		void init(void);
		void cleanUP(void);

		map<string, Mesh*> models;

		// Singleton class implementation
		static inline ModelLibrary* getInstance(void)
		{
			if (s_instance == nullptr)
			{
				s_instance = new ModelLibrary();
			}

			return s_instance;
		}

		// check whether exist or not
		static inline bool exists(void)
		{
			return s_instance != nullptr;
		}

	private:
		// singleton properties
		static ModelLibrary* s_instance;

		void initALLMesh(void);

		ModelLibrary(void);
		~ModelLibrary(void);
	};
}


#endif

