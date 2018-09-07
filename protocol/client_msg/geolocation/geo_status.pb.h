// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: client_msg/geolocation/geo_status.proto

#ifndef PROTOBUF_client_5fmsg_2fgeolocation_2fgeo_5fstatus_2eproto__INCLUDED
#define PROTOBUF_client_5fmsg_2fgeolocation_2fgeo_5fstatus_2eproto__INCLUDED

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
namespace geolocation {
class Status;
class StatusDefaultTypeInternal;
extern StatusDefaultTypeInternal _Status_default_instance_;
class Status_Sensor;
class Status_SensorDefaultTypeInternal;
extern Status_SensorDefaultTypeInternal _Status_Sensor_default_instance_;
}  // namespace geolocation
}  // namespace client
}  // namespace external

namespace external {
namespace client {
namespace geolocation {

namespace protobuf_client_5fmsg_2fgeolocation_2fgeo_5fstatus_2eproto {
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
}  // namespace protobuf_client_5fmsg_2fgeolocation_2fgeo_5fstatus_2eproto

// ===================================================================

class Status_Sensor : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:external.client.geolocation.Status.Sensor) */ {
 public:
  Status_Sensor();
  virtual ~Status_Sensor();

  Status_Sensor(const Status_Sensor& from);

  inline Status_Sensor& operator=(const Status_Sensor& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Status_Sensor(Status_Sensor&& from) noexcept
    : Status_Sensor() {
    *this = ::std::move(from);
  }

  inline Status_Sensor& operator=(Status_Sensor&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const Status_Sensor& default_instance();

  static inline const Status_Sensor* internal_default_instance() {
    return reinterpret_cast<const Status_Sensor*>(
               &_Status_Sensor_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    0;

  void Swap(Status_Sensor* other);
  friend void swap(Status_Sensor& a, Status_Sensor& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Status_Sensor* New() const PROTOBUF_FINAL { return New(NULL); }

  Status_Sensor* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const Status_Sensor& from);
  void MergeFrom(const Status_Sensor& from);
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
  void InternalSwap(Status_Sensor* other);
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

  // uint64 id = 1;
  void clear_id();
  static const int kIdFieldNumber = 1;
  ::google::protobuf::uint64 id() const;
  void set_id(::google::protobuf::uint64 value);

  // uint32 total_sample = 2;
  void clear_total_sample();
  static const int kTotalSampleFieldNumber = 2;
  ::google::protobuf::uint32 total_sample() const;
  void set_total_sample(::google::protobuf::uint32 value);

  // uint32 received_sample = 3;
  void clear_received_sample();
  static const int kReceivedSampleFieldNumber = 3;
  ::google::protobuf::uint32 received_sample() const;
  void set_received_sample(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:external.client.geolocation.Status.Sensor)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint64 id_;
  ::google::protobuf::uint32 total_sample_;
  ::google::protobuf::uint32 received_sample_;
  mutable int _cached_size_;
  friend struct protobuf_client_5fmsg_2fgeolocation_2fgeo_5fstatus_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class Status : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:external.client.geolocation.Status) */ {
 public:
  Status();
  virtual ~Status();

  Status(const Status& from);

  inline Status& operator=(const Status& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Status(Status&& from) noexcept
    : Status() {
    *this = ::std::move(from);
  }

  inline Status& operator=(Status&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const Status& default_instance();

  static inline const Status* internal_default_instance() {
    return reinterpret_cast<const Status*>(
               &_Status_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    1;

  void Swap(Status* other);
  friend void swap(Status& a, Status& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Status* New() const PROTOBUF_FINAL { return New(NULL); }

  Status* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const Status& from);
  void MergeFrom(const Status& from);
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
  void InternalSwap(Status* other);
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

  typedef Status_Sensor Sensor;

  // accessors -------------------------------------------------------

  // repeated .external.client.geolocation.Status.Sensor sensor = 2;
  int sensor_size() const;
  void clear_sensor();
  static const int kSensorFieldNumber = 2;
  const ::external::client::geolocation::Status_Sensor& sensor(int index) const;
  ::external::client::geolocation::Status_Sensor* mutable_sensor(int index);
  ::external::client::geolocation::Status_Sensor* add_sensor();
  ::google::protobuf::RepeatedPtrField< ::external::client::geolocation::Status_Sensor >*
      mutable_sensor();
  const ::google::protobuf::RepeatedPtrField< ::external::client::geolocation::Status_Sensor >&
      sensor() const;

  // .external.client.Signal signal = 1;
  bool has_signal() const;
  void clear_signal();
  static const int kSignalFieldNumber = 1;
  const ::external::client::Signal& signal() const;
  ::external::client::Signal* mutable_signal();
  ::external::client::Signal* release_signal();
  void set_allocated_signal(::external::client::Signal* signal);

  // @@protoc_insertion_point(class_scope:external.client.geolocation.Status)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::RepeatedPtrField< ::external::client::geolocation::Status_Sensor > sensor_;
  ::external::client::Signal* signal_;
  mutable int _cached_size_;
  friend struct protobuf_client_5fmsg_2fgeolocation_2fgeo_5fstatus_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Status_Sensor

// uint64 id = 1;
inline void Status_Sensor::clear_id() {
  id_ = GOOGLE_ULONGLONG(0);
}
inline ::google::protobuf::uint64 Status_Sensor::id() const {
  // @@protoc_insertion_point(field_get:external.client.geolocation.Status.Sensor.id)
  return id_;
}
inline void Status_Sensor::set_id(::google::protobuf::uint64 value) {
  
  id_ = value;
  // @@protoc_insertion_point(field_set:external.client.geolocation.Status.Sensor.id)
}

// uint32 total_sample = 2;
inline void Status_Sensor::clear_total_sample() {
  total_sample_ = 0u;
}
inline ::google::protobuf::uint32 Status_Sensor::total_sample() const {
  // @@protoc_insertion_point(field_get:external.client.geolocation.Status.Sensor.total_sample)
  return total_sample_;
}
inline void Status_Sensor::set_total_sample(::google::protobuf::uint32 value) {
  
  total_sample_ = value;
  // @@protoc_insertion_point(field_set:external.client.geolocation.Status.Sensor.total_sample)
}

// uint32 received_sample = 3;
inline void Status_Sensor::clear_received_sample() {
  received_sample_ = 0u;
}
inline ::google::protobuf::uint32 Status_Sensor::received_sample() const {
  // @@protoc_insertion_point(field_get:external.client.geolocation.Status.Sensor.received_sample)
  return received_sample_;
}
inline void Status_Sensor::set_received_sample(::google::protobuf::uint32 value) {
  
  received_sample_ = value;
  // @@protoc_insertion_point(field_set:external.client.geolocation.Status.Sensor.received_sample)
}

// -------------------------------------------------------------------

// Status

// .external.client.Signal signal = 1;
inline bool Status::has_signal() const {
  return this != internal_default_instance() && signal_ != NULL;
}
inline void Status::clear_signal() {
  if (GetArenaNoVirtual() == NULL && signal_ != NULL) delete signal_;
  signal_ = NULL;
}
inline const ::external::client::Signal& Status::signal() const {
  const ::external::client::Signal* p = signal_;
  // @@protoc_insertion_point(field_get:external.client.geolocation.Status.signal)
  return p != NULL ? *p : *reinterpret_cast<const ::external::client::Signal*>(
      &::external::client::_Signal_default_instance_);
}
inline ::external::client::Signal* Status::mutable_signal() {
  
  if (signal_ == NULL) {
    signal_ = new ::external::client::Signal;
  }
  // @@protoc_insertion_point(field_mutable:external.client.geolocation.Status.signal)
  return signal_;
}
inline ::external::client::Signal* Status::release_signal() {
  // @@protoc_insertion_point(field_release:external.client.geolocation.Status.signal)
  
  ::external::client::Signal* temp = signal_;
  signal_ = NULL;
  return temp;
}
inline void Status::set_allocated_signal(::external::client::Signal* signal) {
  delete signal_;
  signal_ = signal;
  if (signal) {
    
  } else {
    
  }
  // @@protoc_insertion_point(field_set_allocated:external.client.geolocation.Status.signal)
}

// repeated .external.client.geolocation.Status.Sensor sensor = 2;
inline int Status::sensor_size() const {
  return sensor_.size();
}
inline void Status::clear_sensor() {
  sensor_.Clear();
}
inline const ::external::client::geolocation::Status_Sensor& Status::sensor(int index) const {
  // @@protoc_insertion_point(field_get:external.client.geolocation.Status.sensor)
  return sensor_.Get(index);
}
inline ::external::client::geolocation::Status_Sensor* Status::mutable_sensor(int index) {
  // @@protoc_insertion_point(field_mutable:external.client.geolocation.Status.sensor)
  return sensor_.Mutable(index);
}
inline ::external::client::geolocation::Status_Sensor* Status::add_sensor() {
  // @@protoc_insertion_point(field_add:external.client.geolocation.Status.sensor)
  return sensor_.Add();
}
inline ::google::protobuf::RepeatedPtrField< ::external::client::geolocation::Status_Sensor >*
Status::mutable_sensor() {
  // @@protoc_insertion_point(field_mutable_list:external.client.geolocation.Status.sensor)
  return &sensor_;
}
inline const ::google::protobuf::RepeatedPtrField< ::external::client::geolocation::Status_Sensor >&
Status::sensor() const {
  // @@protoc_insertion_point(field_list:external.client.geolocation.Status.sensor)
  return sensor_;
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)


}  // namespace geolocation
}  // namespace client
}  // namespace external

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_client_5fmsg_2fgeolocation_2fgeo_5fstatus_2eproto__INCLUDED