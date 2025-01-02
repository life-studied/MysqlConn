#pragma once

#define DELETE_CONS(classname)\
classname(const classname&) = delete;\
classname operator=(const classname&) = delete;\
classname(classname&&) = delete;\
classname operator=(classname&&) = delete;

template <typename T>
class Singleton
{
public:
	DELETE_CONS(Singleton);
	static T& getInstance()
	{
		static T instance;
		return instance;
	}
};



