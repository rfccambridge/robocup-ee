
#ifndef CUBE_COM_SPECS_H
#define CUBE_COM_SPECS_H

#include <string>

//The template is a mere trick to get the static variable contained only
// count the instances of each individual derived class
template <typename Derived>
class CubeComSpecs
{
protected:
  static int running_id;

  CubeComSpecs()
  {
    ++running_id;
  }

  ~CubeComSpecs()
  {
    --running_id;
  }

  const std::string name_service_get_pos()
  {
    return "service_get_pos";
  }

  const std::string name_messenger_set_pos()
  {
    return "messenger_set_pos";
  }

};

template <typename Derived> 
int CubeComSpecs<Derived>::running_id = 0;

#endif /* CUBE_COM_SPECS_H */
