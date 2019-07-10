#pragma once
#include <iostream>
#include <functional>
#include <map>
#include <any>

class GameComponent;
template<typename T, typename... Args>
GameComponent* CreateFunction(Args... args)
{
	return new T(args...);
}

typedef void (*voidFunction)(void);
class ComponentRegistry
{
public:
	static ComponentRegistry& GetInstance()
	{
		static ComponentRegistry instance;
		return instance;
	}

	template<typename Constructor>
	void Register(const std::string& name, Constructor constructor)
	{
		m_constructors[name]=(voidFunction)constructor;
		
	}
	
	template<typename... Args>
	void Call(const std::string& name, Args... args) //https://stackoverflow.com/a/33837343
	{
		//std::cout << __PRETTY_FUNCTION__ << std::endl;
		auto mapIter = m_constructors.find(name);
		auto func = mapIter->second;
		auto originalFunction = (GameComponent*(*)(Args...))(func);
		originalFunction(args...);
	}



	// these are to prevent copy of the singleton
	ComponentRegistry(ComponentRegistry const&) = delete;
	void operator=(ComponentRegistry const&) = delete;
private:
	ComponentRegistry(){};
	std::map<std::string, voidFunction> m_constructors;
};
