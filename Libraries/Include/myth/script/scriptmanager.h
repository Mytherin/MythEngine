

extern "C"
{
#include "lua.h"
}

namespace myth
{
	namespace script
	{
		class __declspec(dllexport) ScriptManager
		{
		public:
			//! Initializes the script manager
			/*! Initializes the script manager, initializing the LUA interpreter and the Luabind environment.
			This function must be called prior to calling any other function from the script manager.
			*/
			void Initialize();
			//! Destroys the script manager
			void Destroy();

			//! Executes a LUA file at the specified directory
			/*!
			\param filename The directory of the LUA file
			*/
			void ExecuteFile(const char* filename);
			//! Executes a line of LUA code
			/*!
			\param line The line of code to be executed
			*/
			void ExecuteString(const char* line);
			
			//! Retrieves the value of a global variable with the specified name from LUA as a boolean
			bool GetBool(const char* globalname);
			//! Retrieves the value of a global variable with the specified name from LUA as an integer
			int GetInt(const char* globalname);
			//! Retrieves the value of a global variable with the specified name from LUA as a string
			const char* GetString(const char* globalname);

			static ScriptManager& Instance()
			{
				static ScriptManager* m_instance = new ScriptManager;
				return *m_instance;
			}
		private:
			ScriptManager();
			~ScriptManager();

			//! Pushes the global variable with the specified name onto the top of the LUA stack
			void PushGlobal(const char* globalName);

			lua_State* m_LuaState;
		};

#define g_scriptManager myth::script::ScriptManager::Instance()
	}
}