#include "ResourceManager.h"

/**
* Creates an ID for a resource and stores it.
*
* @param - object<T> res - The resource to store
* @return - id_resource - The ID assigned to the resource
*/
template <typename T> id_resource Manager::ResourceManager<T>::store(T res)
{
	if(res == NULL)
		return NULL;

	id_resource id = ID_RESOURCE;
	ID_RESOURCE++;
	
	resource_map[id] = res;
	
	return id;
}

/**
* Stores a resource, overwriting the previously stored one.
*
* @param - object<T> res - The resource to store
* @param - id_resource id - The id to store it at
* @param - bool dealloc - Whether to 'delete' the element, should be true if elements are 'new' pointers
* @return - void
*/
template <typename T> void Manager::ResourceManager<T>::store(T res, id_resource id, bool dealloc)
{
	if(res == NULL)
		return NULL;	
	
	typename std::map<id_resource, T>::iterator it = resource_map.find(id);
	
	if(it != resource_map.end)
	{
		if(dealloc)
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
template <typename T> T Manager::ResourceManager<T>::get(id_resource id)
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
template <typename T> T Manager::ResourceManager<T>::remove(id_resource id)
{
	T retval;
	if((retval = get(id)) != NULL)
	{
		resource_map.erase(id);
		
		return retval;
	}
	else
		return NULL;
}

/**
* Clears the manager of all resources and IDs.
*
* @param - bool dealloc - Whether to 'delete' the elements, should be true if elements are 'new' pointers
* @return - unsigned int count - The number of resources purged
*/
template <typename T> unsigned int Manager::ResourceManager<T>::clear(bool dealloc)
{
	unsigned int retval = resource_map.size();
	
	//Delete each id_resource
	typename std::map<id_resource, T>::iterator it;
	if(dealloc)
		for(it = resource_map.begin(); it != resource_map.end(); ++it)
			delete it->second;
	
	resource_map.clear();
	
	return retval;
}
