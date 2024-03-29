#ifndef _ROS_std_msgs_Char_h
#define _ROS_std_msgs_Char_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros_lib/ros/msg.h"

namespace std_msgs
{

  class Char : public ros::Msg
  {
    public:
      uint8_t data;

    Char():
      data(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->data >> (8 * 0)) & 0xFF;
      offset += sizeof(this->data);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->data =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->data);
     return offset;
    }

    const char * getType(){ return "std_msgs/Char"; };
    const char * getMD5(){ return "1bf77f25acecdedba0e224b162199717"; };

  };

}
#endif