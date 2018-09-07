// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: client_msg/server/operation.proto

#ifndef PROTOBUF_client_5fmsg_2fserver_2foperation_2eproto__INCLUDED
#define PROTOBUF_client_5fmsg_2fserver_2foperation_2eproto__INCLUDED

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
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
namespace external {
namespace client {
namespace server {
class ConfigureOperation;
class ConfigureOperationDefaultTypeInternal;
extern ConfigureOperationDefaultTypeInternal _ConfigureOperation_default_instance_;
}  // namespace server
}  // namespace client
}  // namespace external

namespace external {
namespace client {
namespace server {

namespace protobuf_client_5fmsg_2fserver_2foperation_2eproto {
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
}  // namespace protobuf_client_5fmsg_2fserver_2foperation_2eproto

enum ConfigureOperation_Mode {
  ConfigureOperation_Mode_NORMAL = 0,
  ConfigureOperation_Mode_CALIBRATION = 1,
  ConfigureOperation_Mode_TEST = 2,
  ConfigureOperation_Mode_ConfigureOperation_Mode_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  ConfigureOperation_Mode_ConfigureOperation_Mode_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool ConfigureOperation_Mode_IsValid(int value);
const ConfigureOperation_Mode ConfigureOperation_Mode_Mode_MIN = ConfigureOperation_Mode_NORMAL;
const ConfigureOperation_Mode ConfigureOperation_Mode_Mode_MAX = ConfigureOperation_Mode_TEST;
const int ConfigureOperation_Mode_Mode_ARRAYSIZE = ConfigureOperation_Mode_Mode_MAX + 1;

const ::google::protobuf::EnumDescriptor* ConfigureOperation_Mode_descriptor();
inline const ::std::string& ConfigureOperation_Mode_Name(ConfigureOperation_Mode value) {
  return ::google::protobuf::internal::NameOfEnum(
    ConfigureOperation_Mode_descriptor(), value);
}
inline bool ConfigureOperation_Mode_Parse(
    const ::std::string& name, ConfigureOperation_Mode* value) {
  return ::google::protobuf::internal::ParseNamedEnum<ConfigureOperation_Mode>(
    ConfigureOperation_Mode_descriptor(), name, value);
}
// ===================================================================

class ConfigureOperation : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:external.client.server.ConfigureOperation) */ {
 public:
  ConfigureOperation();
  virtual ~ConfigureOperation();

  ConfigureOperation(const ConfigureOperation& from);

  inline ConfigureOperation& operator=(const ConfigureOperation& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  ConfigureOperation(ConfigureOperation&& from) noexcept
    : ConfigureOperation() {
    *this = ::std::move(from);
  }

  inline ConfigureOperation& operator=(ConfigureOperation&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const ConfigureOperation& default_instance();

  static inline const ConfigureOperation* internal_default_instance() {
    return reinterpret_cast<const ConfigureOperation*>(
               &_ConfigureOperation_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    0;

  void Swap(ConfigureOperation* other);
  friend void swap(ConfigureOperation& a, ConfigureOperation& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline ConfigureOperation* New() const PROTOBUF_FINAL { return New(NULL); }

  ConfigureOperation* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const ConfigureOperation& from);
  void MergeFrom(const ConfigureOperation& from);
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
  void InternalSwap(ConfigureOperation* other);
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

  typedef ConfigureOperation_Mode Mode;
  static const Mode NORMAL =
    ConfigureOperation_Mode_NORMAL;
  static const Mode CALIBRATION =
    ConfigureOperation_Mode_CALIBRATION;
  static const Mode TEST =
    ConfigureOperation_Mode_TEST;
  static inline bool Mode_IsValid(int value) {
    return ConfigureOperation_Mode_IsValid(value);
  }
  static const Mode Mode_MIN =
    ConfigureOperation_Mode_Mode_MIN;
  static const Mode Mode_MAX =
    ConfigureOperation_Mode_Mode_MAX;
  static const int Mode_ARRAYSIZE =
    ConfigureOperation_Mode_Mode_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  Mode_descriptor() {
    return ConfigureOperation_Mode_descriptor();
  }
  static inline const ::std::string& Mode_Name(Mode value) {
    return ConfigureOperation_Mode_Name(value);
  }
  static inline bool Mode_Parse(const ::std::string& name,
      Mode* value) {
    return ConfigureOperation_Mode_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  // .external.client.server.ConfigureOperation.Mode mode = 1;
  void clear_mode();
  static const int kModeFieldNumber = 1;
  ::external::client::server::ConfigureOperation_Mode mode() const;
  void set_mode(::external::client::server::ConfigureOperation_Mode value);

  // @@protoc_insertion_point(class_scope:external.client.server.ConfigureOperation)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  int mode_;
  mutable int _cached_size_;
  friend struct protobuf_client_5fmsg_2fserver_2foperation_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// ConfigureOperation

// .external.client.server.ConfigureOperation.Mode mode = 1;
inline void ConfigureOperation::clear_mode() {
  mode_ = 0;
}
inline ::external::client::server::ConfigureOperation_Mode ConfigureOperation::mode() const {
  // @@protoc_insertion_point(field_get:external.client.server.ConfigureOperation.mode)
  return static_cast< ::external::client::server::ConfigureOperation_Mode >(mode_);
}
inline void ConfigureOperation::set_mode(::external::client::server::ConfigureOperation_Mode value) {
  
  mode_ = value;
  // @@protoc_insertion_point(field_set:external.client.server.ConfigureOperation.mode)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)


}  // namespace server
}  // namespace client
}  // namespace external

namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::external::client::server::ConfigureOperation_Mode> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::external::client::server::ConfigureOperation_Mode>() {
  return ::external::client::server::ConfigureOperation_Mode_descriptor();
}

}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_client_5fmsg_2fserver_2foperation_2eproto__INCLUDED
