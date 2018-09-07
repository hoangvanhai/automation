// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: client_msg/sensor/reset.proto

#ifndef PROTOBUF_client_5fmsg_2fsensor_2freset_2eproto__INCLUDED
#define PROTOBUF_client_5fmsg_2fsensor_2freset_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3004000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3004000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
#include "client_msg/common.pb.h"
// @@protoc_insertion_point(includes)
namespace external {
namespace client {
namespace sensor {
class Reset;
class ResetDefaultTypeInternal;
extern ResetDefaultTypeInternal _Reset_default_instance_;
}  // namespace sensor
}  // namespace client
}  // namespace external

namespace external {
namespace client {
namespace sensor {

namespace protobuf_client_5fmsg_2fsensor_2freset_2eproto {
// Internal implementation detail -- do not call these.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[];
  static const ::google::protobuf::uint32 offsets[];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static void InitDefaultsImpl();
};
void AddDescriptors();
void InitDefaults();
}  // namespace protobuf_client_5fmsg_2fsensor_2freset_2eproto

// ===================================================================

class Reset : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:external.client.sensor.Reset) */ {
 public:
  Reset();
  virtual ~Reset();

  Reset(const Reset& from);

  inline Reset& operator=(const Reset& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Reset(Reset&& from) noexcept
    : Reset() {
    *this = ::std::move(from);
  }

  inline Reset& operator=(Reset&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const Reset& default_instance();

  static inline const Reset* internal_default_instance() {
    return reinterpret_cast<const Reset*>(
               &_Reset_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    0;

  void Swap(Reset* other);
  friend void swap(Reset& a, Reset& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Reset* New() const PROTOBUF_FINAL { return New(NULL); }

  Reset* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const Reset& from);
  void MergeFrom(const Reset& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(Reset* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // .external.client.Sensor sensor = 1;
  bool has_sensor() const;
  void clear_sensor();
  static const int kSensorFieldNumber = 1;
  const ::external::client::Sensor& sensor() const;
  ::external::client::Sensor* mutable_sensor();
  ::external::client::Sensor* release_sensor();
  void set_allocated_sensor(::external::client::Sensor* sensor);

  // @@protoc_insertion_point(class_scope:external.client.sensor.Reset)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::external::client::Sensor* sensor_;
  mutable int _cached_size_;
  friend struct protobuf_client_5fmsg_2fsensor_2freset_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Reset

// .external.client.Sensor sensor = 1;
inline bool Reset::has_sensor() const {
  return this != internal_default_instance() && sensor_ != NULL;
}
inline void Reset::clear_sensor() {
  if (GetArenaNoVirtual() == NULL && sensor_ != NULL) delete sensor_;
  sensor_ = NULL;
}
inline const ::external::client::Sensor& Reset::sensor() const {
  const ::external::client::Sensor* p = sensor_;
  // @@protoc_insertion_point(field_get:external.client.sensor.Reset.sensor)
  return p != NULL ? *p : *reinterpret_cast<const ::external::client::Sensor*>(
      &::external::client::_Sensor_default_instance_);
}
inline ::external::client::Sensor* Reset::mutable_sensor() {
  
  if (sensor_ == NULL) {
    sensor_ = new ::external::client::Sensor;
  }
  // @@protoc_insertion_point(field_mutable:external.client.sensor.Reset.sensor)
  return sensor_;
}
inline ::external::client::Sensor* Reset::release_sensor() {
  // @@protoc_insertion_point(field_release:external.client.sensor.Reset.sensor)
  
  ::external::client::Sensor* temp = sensor_;
  sensor_ = NULL;
  return temp;
}
inline void Reset::set_allocated_sensor(::external::client::Sensor* sensor) {
  delete sensor_;
  sensor_ = sensor;
  if (sensor) {
    
  } else {
    
  }
  // @@protoc_insertion_point(field_set_allocated:external.client.sensor.Reset.sensor)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)


}  // namespace sensor
}  // namespace client
}  // namespace external

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_client_5fmsg_2fsensor_2freset_2eproto__INCLUDED
