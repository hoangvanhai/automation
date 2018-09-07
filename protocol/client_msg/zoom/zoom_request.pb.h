// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: client_msg/zoom/zoom_request.proto

#ifndef PROTOBUF_client_5fmsg_2fzoom_2fzoom_5frequest_2eproto__INCLUDED
#define PROTOBUF_client_5fmsg_2fzoom_2fzoom_5frequest_2eproto__INCLUDED

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
namespace zoom {
class Request;
class RequestDefaultTypeInternal;
extern RequestDefaultTypeInternal _Request_default_instance_;
}  // namespace zoom
}  // namespace client
}  // namespace external

namespace external {
namespace client {
namespace zoom {

namespace protobuf_client_5fmsg_2fzoom_2fzoom_5frequest_2eproto {
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
}  // namespace protobuf_client_5fmsg_2fzoom_2fzoom_5frequest_2eproto

// ===================================================================

class Request : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:external.client.zoom.Request) */ {
 public:
  Request();
  virtual ~Request();

  Request(const Request& from);

  inline Request& operator=(const Request& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Request(Request&& from) noexcept
    : Request() {
    *this = ::std::move(from);
  }

  inline Request& operator=(Request&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const Request& default_instance();

  static inline const Request* internal_default_instance() {
    return reinterpret_cast<const Request*>(
               &_Request_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    0;

  void Swap(Request* other);
  friend void swap(Request& a, Request& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Request* New() const PROTOBUF_FINAL { return New(NULL); }

  Request* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const Request& from);
  void MergeFrom(const Request& from);
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
  void InternalSwap(Request* other);
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

  // uint64 frequency = 1;
  void clear_frequency();
  static const int kFrequencyFieldNumber = 1;
  ::google::protobuf::uint64 frequency() const;
  void set_frequency(::google::protobuf::uint64 value);

  // uint32 bandwidth = 2;
  void clear_bandwidth();
  static const int kBandwidthFieldNumber = 2;
  ::google::protobuf::uint32 bandwidth() const;
  void set_bandwidth(::google::protobuf::uint32 value);

  // uint32 sample_count = 3;
  void clear_sample_count();
  static const int kSampleCountFieldNumber = 3;
  ::google::protobuf::uint32 sample_count() const;
  void set_sample_count(::google::protobuf::uint32 value);

  // uint64 timestamp = 4;
  void clear_timestamp();
  static const int kTimestampFieldNumber = 4;
  ::google::protobuf::uint64 timestamp() const;
  void set_timestamp(::google::protobuf::uint64 value);

  // uint64 duration = 5;
  void clear_duration();
  static const int kDurationFieldNumber = 5;
  ::google::protobuf::uint64 duration() const;
  void set_duration(::google::protobuf::uint64 value);

  // uint32 line_count = 6;
  void clear_line_count();
  static const int kLineCountFieldNumber = 6;
  ::google::protobuf::uint32 line_count() const;
  void set_line_count(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:external.client.zoom.Request)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint64 frequency_;
  ::google::protobuf::uint32 bandwidth_;
  ::google::protobuf::uint32 sample_count_;
  ::google::protobuf::uint64 timestamp_;
  ::google::protobuf::uint64 duration_;
  ::google::protobuf::uint32 line_count_;
  mutable int _cached_size_;
  friend struct protobuf_client_5fmsg_2fzoom_2fzoom_5frequest_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Request

// uint64 frequency = 1;
inline void Request::clear_frequency() {
  frequency_ = GOOGLE_ULONGLONG(0);
}
inline ::google::protobuf::uint64 Request::frequency() const {
  // @@protoc_insertion_point(field_get:external.client.zoom.Request.frequency)
  return frequency_;
}
inline void Request::set_frequency(::google::protobuf::uint64 value) {
  
  frequency_ = value;
  // @@protoc_insertion_point(field_set:external.client.zoom.Request.frequency)
}

// uint32 bandwidth = 2;
inline void Request::clear_bandwidth() {
  bandwidth_ = 0u;
}
inline ::google::protobuf::uint32 Request::bandwidth() const {
  // @@protoc_insertion_point(field_get:external.client.zoom.Request.bandwidth)
  return bandwidth_;
}
inline void Request::set_bandwidth(::google::protobuf::uint32 value) {
  
  bandwidth_ = value;
  // @@protoc_insertion_point(field_set:external.client.zoom.Request.bandwidth)
}

// uint32 sample_count = 3;
inline void Request::clear_sample_count() {
  sample_count_ = 0u;
}
inline ::google::protobuf::uint32 Request::sample_count() const {
  // @@protoc_insertion_point(field_get:external.client.zoom.Request.sample_count)
  return sample_count_;
}
inline void Request::set_sample_count(::google::protobuf::uint32 value) {
  
  sample_count_ = value;
  // @@protoc_insertion_point(field_set:external.client.zoom.Request.sample_count)
}

// uint64 timestamp = 4;
inline void Request::clear_timestamp() {
  timestamp_ = GOOGLE_ULONGLONG(0);
}
inline ::google::protobuf::uint64 Request::timestamp() const {
  // @@protoc_insertion_point(field_get:external.client.zoom.Request.timestamp)
  return timestamp_;
}
inline void Request::set_timestamp(::google::protobuf::uint64 value) {
  
  timestamp_ = value;
  // @@protoc_insertion_point(field_set:external.client.zoom.Request.timestamp)
}

// uint64 duration = 5;
inline void Request::clear_duration() {
  duration_ = GOOGLE_ULONGLONG(0);
}
inline ::google::protobuf::uint64 Request::duration() const {
  // @@protoc_insertion_point(field_get:external.client.zoom.Request.duration)
  return duration_;
}
inline void Request::set_duration(::google::protobuf::uint64 value) {
  
  duration_ = value;
  // @@protoc_insertion_point(field_set:external.client.zoom.Request.duration)
}

// uint32 line_count = 6;
inline void Request::clear_line_count() {
  line_count_ = 0u;
}
inline ::google::protobuf::uint32 Request::line_count() const {
  // @@protoc_insertion_point(field_get:external.client.zoom.Request.line_count)
  return line_count_;
}
inline void Request::set_line_count(::google::protobuf::uint32 value) {
  
  line_count_ = value;
  // @@protoc_insertion_point(field_set:external.client.zoom.Request.line_count)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)


}  // namespace zoom
}  // namespace client
}  // namespace external

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_client_5fmsg_2fzoom_2fzoom_5frequest_2eproto__INCLUDED