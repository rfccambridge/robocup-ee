#ifndef _ROS_std_msgs_Int64MultiArray_h
#define _ROS_std_msgs_Int64MultiArray_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros_lib/ros/msg.h"
#include "ros_lib/std_msgs/MultiArrayLayout.h"

namespace std_msgs
{

  class Int64MultiArray : public ros::Msg
  {
    public:
      std_msgs::MultiArrayLayout layout;
      uint8_t data_length;
      int64_t st_data;
      int64_t * data;

    Int64MultiArray():
      layout(),
      data_length(0), data(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->layout.serialize(outbuffer + offset);
      *(outbuffer + offset++) = data_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < data_length; i++){
      union {
        int64_t real;
        uint64_t base;
      } u_datai;
      u_datai.real = this->data[i];
      *(outbuffer + offset + 0) = (u_datai.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_datai.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_datai.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_datai.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_datai.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_datai.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_datai.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_datai.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->data[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->layout.deserialize(inbuffer + offset);
      uint8_t data_lengthT = *(inbuffer + offset++);
      if(data_lengthT > data_length)
        this->data = (int64_t*)realloc(this->data, data_lengthT * sizeof(int64_t));
      offset += 3;
      data_length = data_lengthT;
      for( uint8_t i = 0; i < data_length; i++){
      union {
        int64_t real;
        uint64_t base;
      } u_st_data;
      u_st_data.base = 0;
      u_st_data.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_data.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_data.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_data.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_st_data.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_st_data.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_st_data.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_st_data.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->st_data = u_st_data.real;
      offset += sizeof(this->st_data);
        memcpy( &(this->data[i]), &(this->st_data), sizeof(int64_t));
      }
     return offset;
    }

    const char * getType(){ return "std_msgs/Int64MultiArray"; };
    const char * getMD5(){ return "54865aa6c65be0448113a2afc6a49270"; };

  };

}
#endif