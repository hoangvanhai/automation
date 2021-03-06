// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: client_msg/configuration/signalcalc.proto

#ifndef PROTOBUF_client_5fmsg_2fconfiguration_2fsignalcalc_2eproto__INCLUDED
#define PROTOBUF_client_5fmsg_2fconfiguration_2fsignalcalc_2eproto__INCLUDED

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
namespace configuration {
class ConfigureSignalCalculation;
class ConfigureSignalCalculationDefaultTypeInternal;
extern ConfigureSignalCalculationDefaultTypeInternal _ConfigureSignalCalculation_default_instance_;
}  // namespace configuration
}  // namespace client
}  // namespace external

namespace external {
namespace client {
namespace configuration {

namespace protobuf_client_5fmsg_2fconfiguration_2fsignalcalc_2eproto {
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
}  // namespace protobuf_client_5fmsg_2fconfiguration_2fsignalcalc_2eproto

// ===================================================================

class ConfigureSignalCalculation : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:external.client.configuration.ConfigureSignalCalculation) */ {
 public:
  ConfigureSignalCalculation();
  virtual ~ConfigureSignalCalculation();

  ConfigureSignalCalculation(const ConfigureSignalCalculation& from);

  inline ConfigureSignalCalculation& operator=(const ConfigureSignalCalculation& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  ConfigureSignalCalculation(ConfigureSignalCalculation&& from) noexcept
    : ConfigureSignalCalculation() {
    *this = ::std::move(from);
  }

  inline ConfigureSignalCalculation& operator=(ConfigureSignalCalculation&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const ConfigureSignalCalculation& default_instance();

  static inline const ConfigureSignalCalculation* internal_default_instance() {
    return reinterpret_cast<const ConfigureSignalCalculation*>(
               &_ConfigureSignalCalculation_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    0;

  void Swap(ConfigureSignalCalculation* other);
  friend void swap(ConfigureSignalCalculation& a, ConfigureSignalCalculation& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline ConfigureSignalCalculation* New() const PROTOBUF_FINAL { return New(NULL); }

  ConfigureSignalCalculation* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const ConfigureSignalCalculation& from);
  void MergeFrom(const ConfigureSignalCalculation& from);
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
  void InternalSwap(ConfigureSignalCalculation* other);
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

  // uint32 mode = 1;
  void clear_mode();
  static const int kModeFieldNumber = 1;
  ::google::protobuf::uint32 mode() const;
  void set_mode(::google::protobuf::uint32 value);

  // uint32 option = 2;
  void clear_option();
  static const int kOptionFieldNumber = 2;
  ::google::protobuf::uint32 option() const;
  void set_option(::google::protobuf::uint32 value);

  // float factor = 3;
  void clear_factor();
  static const int kFactorFieldNumber = 3;
  float factor() const;
  void set_factor(float value);

  // @@protoc_insertion_point(class_scope:external.client.configuration.ConfigureSignalCalculation)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint32 mode_;
  ::google::protobuf::uint32 option_;
  float factor_;
  mutable int _cached_size_;
  friend struct protobuf_client_5fmsg_2fconfiguration_2fsignalcalc_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// ConfigureSignalCalculation

// uint32 mode = 1;
inline void ConfigureSignalCalculation::clear_mode() {
  mode_ = 0u;
}
inline ::google::protobuf::uint32 ConfigureSignalCalculation::mode() const {
  // @@protoc_insertion_point(field_get:external.client.configuration.ConfigureSignalCalculation.mode)
  return mode_;
}
inline void ConfigureSignalCalculation::set_mode(::google::protobuf::uint32 value) {
  
  mode_ = value;
  // @@protoc_insertion_point(field_set:external.client.configuration.ConfigureSignalCalculation.mode)
}

// uint32 option = 2;
inline void ConfigureSignalCalculation::clear_option() {
  option_ = 0u;
}
inline ::google::protobuf::uint32 ConfigureSignalCalculation::option() const {
  // @@protoc_insertion_point(field_get:external.client.configuration.ConfigureSignalCalculation.option)
  return option_;
}
inline void ConfigureSignalCalculation::set_option(::google::protobuf::uint32 value) {
  
  option_ = value;
  // @@protoc_insertion_point(field_set:external.client.configuration.ConfigureSignalCalculation.option)
}

// float factor = 3;
inline void ConfigureSignalCalculation::clear_factor() {
  factor_ = 0;
}
inline float ConfigureSignalCalculation::factor() const {
  // @@protoc_insertion_point(field_get:external.client.configuration.ConfigureSignalCalculation.factor)
  return factor_;
}
inline void ConfigureSignalCalculation::set_factor(float value) {
  
  factor_ = value;
  // @@protoc_insertion_point(field_set:external.client.configuration.ConfigureSignalCalculation.factor)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)


}  // namespace configuration
}  // namespace client
}  // namespace external

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_client_5fmsg_2fconfiguration_2fsignalcalc_2eproto__INCLUDED
