#pragma once

#include <unordered_map>
#include <string>

// T must implement the following to work with ResourceManager:
// T(std::string)
// load()
// unload()

template<typename T>
class ResourceManager {
public:
	inline void emplace(std::string identifier) { m_resources.emplace(identifier, identifier); }

	template<class... Args>
	inline void emplace(std::string identifier, Args&& ... args) {
		m_resources.emplace(std::make_pair(identifier, std::forward<Args>(args)...));
	}

	inline void load(const std::string& identifier) { getResource(identifier).load(); }

	inline void unload(const std::string& identifier) { getResource(identifier).unload(); }

	inline const T& getResource(const std::string& identifier) const { return m_resources.find(identifier)->second; }

	inline T& getResource(const std::string& identifier) { return m_resources.find(identifier)->second; }

	inline T* getPointer(const std::string& identifier) { return &(m_resources.find(identifier)->second); }

	T* getAddResource(const std::string& identifier);

private:
	std::unordered_map<std::string, T> m_resources;
};

template<typename T>
T* ResourceManager<T>::getAddResource(const std::string& identifier) {
	size_t n = m_resources.count(identifier);
	if (n == 0) {
		emplace(identifier);
	}
	return getPointer(identifier);
}
