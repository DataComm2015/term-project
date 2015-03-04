#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>

typedef unsigned int id_resource;

namespace Manager
{
	/**
	 * Resource Manager.
	 * 
	 * Loads files into resources of type T(declared when instantiated).
	 * 
	 * @author Lewis Scott
	 */
	template <typename T> class ResourceManager
	{
		public:
			/**
			* Constructor.
			*/
			ResourceManager(){ ID_RESOURCE = 1; }
	
			/**
			* Destructor.
			*/
			virtual ~ResourceManager(){ clear(); }
		
			/**
			* Loads a resource from the specified file.
			*
			* @param - std::string path - a qualified path to the desired resource
			* @return - object<T> - The resource that was loaded
			*/
			//virtual T load(const std::string);
		
			/**
			* Creates an ID for a resource and stores it.
			*
			* @param - object<T> res - The resource to store
			* @return - id_resource - The ID assigned to the resource
			*/
			id_resource store(T res)
			{
				if(res == 0)
					return 0;

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
			void store(T res, id_resource id, bool dealloc = false)
			{
				if(res == 0)
					return;
				
				typename std::map<id_resource, T>::iterator it = resource_map.find(id);
				
				if(it != resource_map.end())
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
			T get(id_resource id)
			{
				typename std::map<id_resource, T>::iterator it = resource_map.find(id);
				
				if(it != resource_map.end())
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
			T remove(id_resource id)
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
			unsigned int clear(bool dealloc = false)
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
		
		private:
			unsigned int ID_RESOURCE;
			std::map<id_resource, T> resource_map;
	};
}

#endif // RESOURCE_MANAGER_H
