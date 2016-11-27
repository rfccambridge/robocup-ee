
#ifndef CUBE_COM_SPECS_H
#define CUBE_COM_SPECS_H

#include <string>
#include <map>

#include "shared_code.h"

//The template is a mere trick to get the static variable contained only
// count the instances of each individual derived class
template <typename Derived>
class CubeComSpecs
{
protected:
  static int running_id;
  static std::map<int, Derived*> map_instances;

  int com_id;

  CubeComSpecs()
  {
    com_id = running_id++;

    //Add `this` to the map of derived instances
    Derived* dp = (Derived*)this; //Extract a pointer of the `Derived` type
    map_instances.insert(std::pair<int, Derived*>(com_id, dp));
  }

  ~CubeComSpecs()
  {
    //Remove `this` to the map of derived instances
    map_instances.erase(com_id);
  }

  static Derived *lookup_by_id(const int id)
  {
    typename std::map<int, Derived*>::iterator it = map_instances.find(id);

    //Return accordingly based on whether `id` was found
    if(it == map_instances.end())
      PRINT_ERROR_AND(return NULL);
    else
      return it->second;
  }

  static const std::string name_service_get_pos()
  {
    return "service_get_pos";
  }

  static const std::string name_messenger_set_pos()
  {
    return "messenger_set_pos";
  }

};

//Declare the static template types
template <typename Derived> 
int CubeComSpecs<Derived>::running_id = 0;

template <typename Derived> 
std::map<int, Derived*> CubeComSpecs<Derived>::map_instances;

#endif /* CUBE_COM_SPECS_H */
