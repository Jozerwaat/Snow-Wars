#pragma once
#include <vector>
#include <list>
#include <iostream>

template <typename T>
class ObjectPool
{
public:
	ObjectPool() : m_objects() {}

	/// Mark the given object for reuse in the future.
	void Pool(T* obj) { m_objects.emplace_back(obj); }

	T* Get() {
		if (m_objects.empty()) // no objects are free
			return new T();

		auto obj = m_objects.back();	// get the last object in the list
		m_objects.pop_back();

		return obj;
	}
private:
	std::vector<T*> m_objects;
};