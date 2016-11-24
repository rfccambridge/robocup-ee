
#ifndef CUBE_COM_SPECS_H
#define CUBE_COM_SPECS_H

#include <string>
#include <boost/lexical_cast.hpp> //For int to std::string conversion

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

  std::string running_id_to_str()
  {
    return boost::lexical_cast<std::string>(running_id);
  }

  std::string name_service_get_pos()
  {
    return "service_get_pos" + running_id_to_str();
  }

  std::string name_subscriber_set_pos()
  {
    return "subscriber_set_pos" + running_id_to_str();
  }

};

template <typename Derived> 
int CubeComSpecs<Derived>::running_id = 0;

#endif /* CUBE_COM_SPECS_H */
