#pragma once


template<typename T>
class ResourceMgr : public Singleton<ResourceMgr<T>>
{
	friend Singleton<ResourceMgr<T>>;

protected:
	std::unordered_map<std::string, T*> uomapResource;

	ResourceMgr() = default;
	~ResourceMgr()
	{
		unloadAll();
	}

	ResourceMgr(const ResourceMgr&) = delete;
	ResourceMgr& operator=(const ResourceMgr&) = delete;

public:
	static T Empty;

	void unloadAll()
	{
		for (const auto& pair : uomapResource)
		{
			delete pair.second;
		}
		uomapResource.clear();
	}

	bool load(const std::string& id)
	{
		if (uomapResource.find(id) != uomapResource.end())
		{
			return false;
		}
		
		T* resource = new T();
		bool success = resource->loadFromFile(id);
		if (success)
		{
			uomapResource.insert({ id, resource });
		}
		else
		{
			delete resource;
		}
		return success;
	}

	bool unload(const std::string& id)
	{
		auto it = uomapResource.find(id);
		if (it == uomapResource.end())
		{
			return false;
		}
		delete it->second;
		uomapResource.erase(it);
		return true;
	}

	T& get(const std::string& id)
	{
		auto it = uomapResource.find(id);
		if (it == uomapResource.end())
		{
			return Empty;
		}
		return *(it->second);
	}
};

template<typename T>
T ResourceMgr<T>::Empty;

