// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: client_msg/server/turnoff.proto

#ifndef PROTOBUF_client_5fmsg_2fserver_2fturnoff_2eproto__INCLUDED
#define PROTOBUF_client_5fmsg_2fserver_2fturnoff_2eproto__INCLUDED

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
// @@protoc_insertion_point(includes)
namespace external {
namespace client {
namespace server {
class TurnOff;
class TurnOffDefaultTypeInternal;
extern TurnOffDefaultTypeInternal _TurnOff_default_instance_;
}  // namespace server
}  // namespace client
}  // namespace external

namespace external {
namespace client {
namespace server {

namespace protobuf_client_5fmsg_2fserver_2fturnoff_2eproto {
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
}  // namespace protobuf_client_5fmsg_2fserver_2fturnoff_2eproto

// ===================================================================

class TurnOff : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:external.client.server.TurnOff) */ {
 public:
  TurnOff();
  virtual ~TurnOff();

  TurnOff(const TurnOff& from);

  inline TurnOff& operator=(const TurnOff& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  TurnOff(TurnOff&& from) noexcept
    : TurnOff() {
    *this = ::std::move(from);
  }

  inline TurnOff& operator=(TurnOff&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const TurnOff& default_instance();

  static inline const TurnOff* internal_default_instance() {
    return reinterpret_cast<const TurnOff*>(
               &_TurnOff_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    0;

  void Swap(TurnOff* other);
  friend void swap(TurnOff& a, TurnOff& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline TurnOff* New() const PROTOBUF_FINAL { return New(NULL); }

  TurnOff* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const TurnOff& from);
  void MergeFrom(const TurnOff& from);
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
  void InternalSwap(TurnOff* other);
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

  // string username = 1;
  void clear_username();
  static const int kUsernameFieldNumber = 1;
  const ::std::string& username() const;
  void set_username(const ::std::string& value);
  #if LANG_CXX11
  void set_username(::std::string&& value);
  #endif
  void set_username(const char* value);
  void set_username(const char* value, size_t size);
  ::std::string* mutable_username();
  ::std::string* release_username();
  void set_allocated_username(::std::string* username);

  // string secret = 2;
  void clear_secret();
  static const int kSecretFieldNumber = 2;
  const ::std::string& secret() const;
  void set_secret(const ::std::string& value);
  #if LANG_CXX11
  void set_secret(::std::string&& value);
  #endif
  void set_secret(const char* value);
  void set_secret(const char* value, size_t size);
  ::std::string* mutable_secret();
  ::std::string* release_secret();
  void set_allocated_secret(::std::string* secret);

  // uint32 timeout = 3;
  void clear_timeout();
  static const int kTimeoutFieldNumber = 3;
  ::google::protobuf::uint32 timeout() const;
  void set_timeout(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:external.client.server.TurnOff)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr username_;
  ::google::protobuf::internal::ArenaStringPtr secret_;
  ::google::protobuf::uint32 timeout_;
  mutable int _cached_size_;
  friend struct protobuf_client_5fmsg_2fserver_2fturnoff_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// TurnOff

// string username = 1;
inline void TurnOff::clear_username() {
  username_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& TurnOff::username() const {
  // @@protoc_insertion_point(field_get:external.client.server.TurnOff.username)
  return username_.GetNoArena();
}
inline void TurnOff::set_username(const ::std::string& value) {
  
  username_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:external.client.server.TurnOff.username)
}
#if LANG_CXX11
inline void TurnOff::set_username(::std::string&& value) {
  
  username_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:external.client.server.TurnOff.username)
}
#endif
inline void TurnOff::set_username(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  username_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:external.client.server.TurnOff.username)
}
inline void TurnOff::set_username(const char* value, size_t size) {
  
  username_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:external.client.server.TurnOff.username)
}
inline ::std::string* TurnOff::mutable_username() {
  
  // @@protoc_insertion_point(field_mutable:external.client.server.TurnOff.username)
  return username_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* TurnOff::release_username() {
  // @@protoc_insertion_point(field_release:external.client.server.TurnOff.username)
  
  return username_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void TurnOff::set_allocated_username(::std::string* username) {
  if (username != NULL) {
    
  } else {
    
  }
  username_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), username);
  // @@protoc_insertion_point(field_set_allocated:external.client.server.TurnOff.username)
}

// string secret = 2;
inline void TurnOff::clear_secret() {
  secret_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& TurnOff::secret() const {
  // @@protoc_insertion_point(field_get:external.client.server.TurnOff.secret)
  return secret_.GetNoArena();
}
inline void TurnOff::set_secret(const ::std::string& value) {
  
  secret_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:external.client.server.TurnOff.secret)
}
#if LANG_CXX11
inline void TurnOff::set_secret(::std::string&& value) {
  
  secret_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:external.client.server.TurnOff.secret)
}
#endif
inline void TurnOff::set_secret(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  secret_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:external.client.server.TurnOff.secret)
}
inline void TurnOff::set_secret(const char* value, size_t size) {
  
  secret_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:external.client.server.TurnOff.secret)
}
inline ::std::string* TurnOff::mutable_secret() {
  
  // @@protoc_insertion_point(field_mutable:external.client.server.TurnOff.secret)
  return secret_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* TurnOff::release_secret() {
  // @@protoc_insertion_point(field_release:external.client.server.TurnOff.secret)
  
  return secret_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void TurnOff::set_allocated_secret(::std::string* secret) {
  if (secret != NULL) {
    
  } else {
    
  }
  secret_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), secret);
  // @@protoc_insertion_point(field_set_allocated:external.client.server.TurnOff.secret)
}

// uint32 timeout = 3;
inline void TurnOff::clear_timeout() {
  timeout_ = 0u;
}
inline ::google::protobuf::uint32 TurnOff::timeout() const {
  // @@protoc_insertion_point(field_get:external.client.server.TurnOff.timeout)
  return timeout_;
}
inline void TurnOff::set_timeout(::google::protobuf::uint32 value) {
  
  timeout_ = value;
  // @@protoc_insertion_point(field_set:external.client.server.TurnOff.timeout)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)


}  // namespace server
}  // namespace client
}  // namespace external

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_client_5fmsg_2fserver_2fturnoff_2eproto__INCLUDED
