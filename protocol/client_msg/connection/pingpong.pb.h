// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: client_msg/connection/pingpong.proto

#ifndef PROTOBUF_client_5fmsg_2fconnection_2fpingpong_2eproto__INCLUDED
#define PROTOBUF_client_5fmsg_2fconnection_2fpingpong_2eproto__INCLUDED

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
namespace connection {
class Ping;
class PingDefaultTypeInternal;
extern PingDefaultTypeInternal _Ping_default_instance_;
class Pong;
class PongDefaultTypeInternal;
extern PongDefaultTypeInternal _Pong_default_instance_;
}  // namespace connection
}  // namespace client
}  // namespace external

namespace external {
namespace client {
namespace connection {

namespace protobuf_client_5fmsg_2fconnection_2fpingpong_2eproto {
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
}  // namespace protobuf_client_5fmsg_2fconnection_2fpingpong_2eproto

// ===================================================================

class Ping : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:external.client.connection.Ping) */ {
 public:
  Ping();
  virtual ~Ping();

  Ping(const Ping& from);

  inline Ping& operator=(const Ping& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Ping(Ping&& from) noexcept
    : Ping() {
    *this = ::std::move(from);
  }

  inline Ping& operator=(Ping&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const Ping& default_instance();

  static inline const Ping* internal_default_instance() {
    return reinterpret_cast<const Ping*>(
               &_Ping_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    0;

  void Swap(Ping* other);
  friend void swap(Ping& a, Ping& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Ping* New() const PROTOBUF_FINAL { return New(NULL); }

  Ping* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const Ping& from);
  void MergeFrom(const Ping& from);
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
  void InternalSwap(Ping* other);
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

  // .external.client.Version version = 1;
  bool has_version() const;
  void clear_version();
  static const int kVersionFieldNumber = 1;
  const ::external::client::Version& version() const;
  ::external::client::Version* mutable_version();
  ::external::client::Version* release_version();
  void set_allocated_version(::external::client::Version* version);

  // @@protoc_insertion_point(class_scope:external.client.connection.Ping)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::external::client::Version* version_;
  mutable int _cached_size_;
  friend struct protobuf_client_5fmsg_2fconnection_2fpingpong_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class Pong : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:external.client.connection.Pong) */ {
 public:
  Pong();
  virtual ~Pong();

  Pong(const Pong& from);

  inline Pong& operator=(const Pong& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Pong(Pong&& from) noexcept
    : Pong() {
    *this = ::std::move(from);
  }

  inline Pong& operator=(Pong&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const Pong& default_instance();

  static inline const Pong* internal_default_instance() {
    return reinterpret_cast<const Pong*>(
               &_Pong_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    1;

  void Swap(Pong* other);
  friend void swap(Pong& a, Pong& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Pong* New() const PROTOBUF_FINAL { return New(NULL); }

  Pong* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const Pong& from);
  void MergeFrom(const Pong& from);
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
  void InternalSwap(Pong* other);
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

  // .external.client.Version version = 1;
  bool has_version() const;
  void clear_version();
  static const int kVersionFieldNumber = 1;
  const ::external::client::Version& version() const;
  ::external::client::Version* mutable_version();
  ::external::client::Version* release_version();
  void set_allocated_version(::external::client::Version* version);

  // @@protoc_insertion_point(class_scope:external.client.connection.Pong)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::external::client::Version* version_;
  mutable int _cached_size_;
  friend struct protobuf_client_5fmsg_2fconnection_2fpingpong_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Ping

// .external.client.Version version = 1;
inline bool Ping::has_version() const {
  return this != internal_default_instance() && version_ != NULL;
}
inline void Ping::clear_version() {
  if (GetArenaNoVirtual() == NULL && version_ != NULL) delete version_;
  version_ = NULL;
}
inline const ::external::client::Version& Ping::version() const {
  const ::external::client::Version* p = version_;
  // @@protoc_insertion_point(field_get:external.client.connection.Ping.version)
  return p != NULL ? *p : *reinterpret_cast<const ::external::client::Version*>(
      &::external::client::_Version_default_instance_);
}
inline ::external::client::Version* Ping::mutable_version() {
  
  if (version_ == NULL) {
    version_ = new ::external::client::Version;
  }
  // @@protoc_insertion_point(field_mutable:external.client.connection.Ping.version)
  return version_;
}
inline ::external::client::Version* Ping::release_version() {
  // @@protoc_insertion_point(field_release:external.client.connection.Ping.version)
  
  ::external::client::Version* temp = version_;
  version_ = NULL;
  return temp;
}
inline void Ping::set_allocated_version(::external::client::Version* version) {
  delete version_;
  version_ = version;
  if (version) {
    
  } else {
    
  }
  // @@protoc_insertion_point(field_set_allocated:external.client.connection.Ping.version)
}

// -------------------------------------------------------------------

// Pong

// .external.client.Version version = 1;
inline bool Pong::has_version() const {
  return this != internal_default_instance() && version_ != NULL;
}
inline void Pong::clear_version() {
  if (GetArenaNoVirtual() == NULL && version_ != NULL) delete version_;
  version_ = NULL;
}
inline const ::external::client::Version& Pong::version() const {
  const ::external::client::Version* p = version_;
  // @@protoc_insertion_point(field_get:external.client.connection.Pong.version)
  return p != NULL ? *p : *reinterpret_cast<const ::external::client::Version*>(
      &::external::client::_Version_default_instance_);
}
inline ::external::client::Version* Pong::mutable_version() {
  
  if (version_ == NULL) {
    version_ = new ::external::client::Version;
  }
  // @@protoc_insertion_point(field_mutable:external.client.connection.Pong.version)
  return version_;
}
inline ::external::client::Version* Pong::release_version() {
  // @@protoc_insertion_point(field_release:external.client.connection.Pong.version)
  
  ::external::client::Version* temp = version_;
  version_ = NULL;
  return temp;
}
inline void Pong::set_allocated_version(::external::client::Version* version) {
  delete version_;
  version_ = version;
  if (version) {
    
  } else {
    
  }
  // @@protoc_insertion_point(field_set_allocated:external.client.connection.Pong.version)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)


}  // namespace connection
}  // namespace client
}  // namespace external

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_client_5fmsg_2fconnection_2fpingpong_2eproto__INCLUDED