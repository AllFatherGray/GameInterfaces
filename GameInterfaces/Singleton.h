#pragma once
// Singleton for Games. No heap for now.
template<class T>
class Singleton
{
public:
	static T& Instance()
	{
		static T& _Instance = T();
		return _Instance;
	}
};