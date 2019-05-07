// Generated by gencpp from file hps_camera/measureData.msg
// DO NOT EDIT!


#ifndef HPS_CAMERA_MESSAGE_MEASUREDATA_H
#define HPS_CAMERA_MESSAGE_MEASUREDATA_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <hps_camera/PointCloudData.h>

namespace hps_camera
{
template <class ContainerAllocator>
struct measureData_
{
  typedef measureData_<ContainerAllocator> Type;

  measureData_()
    : point_cloud_data()  {
    }
  measureData_(const ContainerAllocator& _alloc)
    : point_cloud_data(_alloc)  {
  (void)_alloc;
    }



   typedef  ::hps_camera::PointCloudData_<ContainerAllocator>  _point_cloud_data_type;
  _point_cloud_data_type point_cloud_data;





  typedef boost::shared_ptr< ::hps_camera::measureData_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::hps_camera::measureData_<ContainerAllocator> const> ConstPtr;

}; // struct measureData_

typedef ::hps_camera::measureData_<std::allocator<void> > measureData;

typedef boost::shared_ptr< ::hps_camera::measureData > measureDataPtr;
typedef boost::shared_ptr< ::hps_camera::measureData const> measureDataConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::hps_camera::measureData_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::hps_camera::measureData_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace hps_camera

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': False}
// {'hps_camera': ['/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/src/hps_camera/msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::hps_camera::measureData_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::hps_camera::measureData_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::hps_camera::measureData_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::hps_camera::measureData_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::hps_camera::measureData_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::hps_camera::measureData_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::hps_camera::measureData_<ContainerAllocator> >
{
  static const char* value()
  {
    return "d25e7f28a0c985f85d20386b940737b5";
  }

  static const char* value(const ::hps_camera::measureData_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xd25e7f28a0c985f8ULL;
  static const uint64_t static_value2 = 0x5d20386b940737b5ULL;
};

template<class ContainerAllocator>
struct DataType< ::hps_camera::measureData_<ContainerAllocator> >
{
  static const char* value()
  {
    return "hps_camera/measureData";
  }

  static const char* value(const ::hps_camera::measureData_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::hps_camera::measureData_<ContainerAllocator> >
{
  static const char* value()
  {
    return "hps_camera/PointCloudData point_cloud_data\n\
\n\
================================================================================\n\
MSG: hps_camera/PointCloudData\n\
float32[] x\n\
float32[] y\n\
float32[] z\n\
uint16 width\n\
uint16 height\n\
uint16 points\n\
\n\
uint16 distance_average\n\
\n\
";
  }

  static const char* value(const ::hps_camera::measureData_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::hps_camera::measureData_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.point_cloud_data);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct measureData_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::hps_camera::measureData_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::hps_camera::measureData_<ContainerAllocator>& v)
  {
    s << indent << "point_cloud_data: ";
    s << std::endl;
    Printer< ::hps_camera::PointCloudData_<ContainerAllocator> >::stream(s, indent + "  ", v.point_cloud_data);
  }
};

} // namespace message_operations
} // namespace ros

#endif // HPS_CAMERA_MESSAGE_MEASUREDATA_H
