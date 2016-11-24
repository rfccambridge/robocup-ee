
#ifndef CUBE_COM_SPECS_H
#define CUBE_COM_SPECS_H

#include <string>
#include <map>

//The template is a mere trick to get the static variable contained only
// count the instances of each individual derived class
template <typename Derived>
class CubeComSpecs
{
protected:
  static int n_instances;
  static std::map<int, Derived*> derived_instances;

  int com_id;

  CubeComSpecs()
  {
    com_id = n_instances++;

    //Add `this` to the map of derived instances
    dp = dynamic_cast<Derived*>(this); //Extract a pointer of the `Derived` type
    derived_instances.insert(std::pair<int, Derived*>(com_id, dp));
  }

  ~CubeComSpecs()
  {
    --n_instances;

    //Remove `this` to the map of derived instances
    derived_instances.erase(com_id);
  }

  static Derived *lookup_by_id(const int id) const
  {
    std::map<int, Derived*>::iterator it = derived_instances.find(id);

    //Return accordingly based on whether `id` was found
    if(it == derived_instances.end())
      return NULL;
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
int CubeComSpecs<Derived>::n_instances = 0;

template <typename Derived> 
std::map<int, Derived*> derived_instances;

#endif /* CUBE_COM_SPECS_H */
