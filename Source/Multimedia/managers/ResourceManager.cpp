#include "ResourceManager.h"

/**
* Creates an ID for a resource and stores it.
*
* @param - object<T> res - The resource to store
* @return - id_resource - The ID assigned to the resource
*/
template <class T> id_resource ResourceManager<T>::store(T res)
{
	if(res == NULL)
		return NULL;

	id_resource id = new unsigned int(ID_RESOURCE++);
	resource_map[id] = res;
	
	return id;
}

/**
* Stores a resource, overwriting the previously stored one.
*
* @param - object<T> res - The resource to store
* @param - id_resource id - The id to store it at
* @return - void
*/
template <class T> void ResourceManager<T>::store(T res, id_resource id)
{
	if(res == NULL)
		return NULL;	
	
	typename std::map<id_resource, T>::iterator it = resource_map.find(id);
	
	if(it != resource_map.end)
	{
		remove(id);
		resource_map[id] = res;
	}
}

/**
* Gets a resource from a specified ID.
*
* @param - id_resource id - The id to fetch
* @return - object<T> - The resource loaded, or NULL if not found
*/
template <class T> T ResourceManager<T>::get(id_resource id)
{
	typename std::map<id_resource, T>::iterator it = resource_map.find(id);
	
	if(it != resource_map.end)
		return it->second;
	else
		return NULL;
}

/**
* Removes a resource from the manager, freeing it's ID.
*
* @param - id_resource id - The id of the resource to remove
* @return - object<T> - The object removed, or NULL if not found
*/
template <class T> T ResourceManager<T>::remove(id_resource id)
{
	T retval;
	if((retval = get(id)) != NULL)
	{
		resource_map.erase(id);
		delete id;
		return retval;
	}
	else
		return NULL;
}

/**
* Clears the manager of all resources and IDs.
*
* @return - unsigned int count - The number of resources purged
*/
template <class T> unsigned int ResourceManager<T>::clear()
{
	unsigned int retval = resource_map.size();
	
	//Delete each id_resource
	typename std::map<id_resource, T>::iterator it;
	for(it = resource_map.begin(); it != resource_map.end(); ++it)
		delete it->first;
	
	resource_map.clear();
	
	return retval;
}
