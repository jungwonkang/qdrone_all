// Generated by gencpp from file dji_sdk/Activation.msg
// DO NOT EDIT!


#ifndef DJI_SDK_MESSAGE_ACTIVATION_H
#define DJI_SDK_MESSAGE_ACTIVATION_H

#include <ros/service_traits.h>


#include <dji_sdk/ActivationRequest.h>
#include <dji_sdk/ActivationResponse.h>


namespace dji_sdk
{

struct Activation
{

typedef ActivationRequest Request;
typedef ActivationResponse Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;

}; // struct Activation
} // namespace dji_sdk


namespace ros
{
namespace service_traits
{


template<>
struct MD5Sum< ::dji_sdk::Activation > {
  static const char* value()
  {
    return "f03b0bc279b265c40946c1011df83013";
  }

  static const char* value(const ::dji_sdk::Activation&) { return value(); }
};

template<>
struct DataType< ::dji_sdk::Activation > {
  static const char* value()
  {
    return "dji_sdk/Activation";
  }

  static const char* value(const ::dji_sdk::Activation&) { return value(); }
};


// service_traits::MD5Sum< ::dji_sdk::ActivationRequest> should match 
// service_traits::MD5Sum< ::dji_sdk::Activation > 
template<>
struct MD5Sum< ::dji_sdk::ActivationRequest>
{
  static const char* value()
  {
    return MD5Sum< ::dji_sdk::Activation >::value();
  }
  static const char* value(const ::dji_sdk::ActivationRequest&)
  {
    return value();
  }
};

// service_traits::DataType< ::dji_sdk::ActivationRequest> should match 
// service_traits::DataType< ::dji_sdk::Activation > 
template<>
struct DataType< ::dji_sdk::ActivationRequest>
{
  static const char* value()
  {
    return DataType< ::dji_sdk::Activation >::value();
  }
  static const char* value(const ::dji_sdk::ActivationRequest&)
  {
    return value();
  }
};

// service_traits::MD5Sum< ::dji_sdk::ActivationResponse> should match 
// service_traits::MD5Sum< ::dji_sdk::Activation > 
template<>
struct MD5Sum< ::dji_sdk::ActivationResponse>
{
  static const char* value()
  {
    return MD5Sum< ::dji_sdk::Activation >::value();
  }
  static const char* value(const ::dji_sdk::ActivationResponse&)
  {
    return value();
  }
};

// service_traits::DataType< ::dji_sdk::ActivationResponse> should match 
// service_traits::DataType< ::dji_sdk::Activation > 
template<>
struct DataType< ::dji_sdk::ActivationResponse>
{
  static const char* value()
  {
    return DataType< ::dji_sdk::Activation >::value();
  }
  static const char* value(const ::dji_sdk::ActivationResponse&)
  {
    return value();
  }
};

} // namespace service_traits
} // namespace ros

#endif // DJI_SDK_MESSAGE_ACTIVATION_H
