// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: client_msg/classification/class_statistic.proto

#ifndef PROTOBUF_client_5fmsg_2fclassification_2fclass_5fstatistic_2eproto__INCLUDED
#define PROTOBUF_client_5fmsg_2fclassification_2fclass_5fstatistic_2eproto__INCLUDED

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
#include "client_msg/common.pb.h"
// @@protoc_insertion_point(includes)
namespace external {
namespace client {
namespace classification {
class Statistic;
class StatisticDefaultTypeInternal;
extern StatisticDefaultTypeInternal _Statistic_default_instance_;
class Statistic_Item;
class Statistic_ItemDefaultTypeInternal;
extern Statistic_ItemDefaultTypeInternal _Statistic_Item_default_instance_;
}  // namespace classification
}  // namespace client
}  // namespace external

namespace external {
namespace client {
namespace classification {

namespace protobuf_client_5fmsg_2fclassification_2fclass_5fstatistic_2eproto {
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
}  // namespace protobuf_client_5fmsg_2fclassification_2fclass_5fstatistic_2eproto

enum Statistic_State {
  Statistic_State_WAITING = 0,
  Statistic_State_RECEIVING = 1,
  Statistic_State_CALCULATING = 2,
  Statistic_State_Statistic_State_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  Statistic_State_Statistic_State_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool Statistic_State_IsValid(int value);
const Statistic_State Statistic_State_State_MIN = Statistic_State_WAITING;
const Statistic_State Statistic_State_State_MAX = Statistic_State_CALCULATING;
const int Statistic_State_State_ARRAYSIZE = Statistic_State_State_MAX + 1;

const ::google::protobuf::EnumDescriptor* Statistic_State_descriptor();
inline const ::std::string& Statistic_State_Name(Statistic_State value) {
  return ::google::protobuf::internal::NameOfEnum(
    Statistic_State_descriptor(), value);
}
inline bool Statistic_State_Parse(
    const ::std::string& name, Statistic_State* value) {
  return ::google::protobuf::internal::ParseNamedEnum<Statistic_State>(
    Statistic_State_descriptor(), name, value);
}
// ===================================================================

class Statistic_Item : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:external.client.classification.Statistic.Item) */ {
 public:
  Statistic_Item();
  virtual ~Statistic_Item();

  Statistic_Item(const Statistic_Item& from);

  inline Statistic_Item& operator=(const Statistic_Item& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Statistic_Item(Statistic_Item&& from) noexcept
    : Statistic_Item() {
    *this = ::std::move(from);
  }

  inline Statistic_Item& operator=(Statistic_Item&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const Statistic_Item& default_instance();

  static inline const Statistic_Item* internal_default_instance() {
    return reinterpret_cast<const Statistic_Item*>(
               &_Statistic_Item_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    0;

  void Swap(Statistic_Item* other);
  friend void swap(Statistic_Item& a, Statistic_Item& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Statistic_Item* New() const PROTOBUF_FINAL { return New(NULL); }

  Statistic_Item* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const Statistic_Item& from);
  void MergeFrom(const Statistic_Item& from);
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
  void InternalSwap(Statistic_Item* other);
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

  // .external.client.Signal signal = 1;
  bool has_signal() const;
  void clear_signal();
  static const int kSignalFieldNumber = 1;
  const ::external::client::Signal& signal() const;
  ::external::client::Signal* mutable_signal();
  ::external::client::Signal* release_signal();
  void set_allocated_signal(::external::client::Signal* signal);

  // uint64 total_samples = 3;
  void clear_total_samples();
  static const int kTotalSamplesFieldNumber = 3;
  ::google::protobuf::uint64 total_samples() const;
  void set_total_samples(::google::protobuf::uint64 value);

  // uint64 received_samples = 4;
  void clear_received_samples();
  static const int kReceivedSamplesFieldNumber = 4;
  ::google::protobuf::uint64 received_samples() const;
  void set_received_samples(::google::protobuf::uint64 value);

  // .external.client.classification.Statistic.State state = 2;
  void clear_state();
  static const int kStateFieldNumber = 2;
  ::external::client::classification::Statistic_State state() const;
  void set_state(::external::client::classification::Statistic_State value);

  // @@protoc_insertion_point(class_scope:external.client.classification.Statistic.Item)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::external::client::Signal* signal_;
  ::google::protobuf::uint64 total_samples_;
  ::google::protobuf::uint64 received_samples_;
  int state_;
  mutable int _cached_size_;
  friend struct protobuf_client_5fmsg_2fclassification_2fclass_5fstatistic_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class Statistic : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:external.client.classification.Statistic) */ {
 public:
  Statistic();
  virtual ~Statistic();

  Statistic(const Statistic& from);

  inline Statistic& operator=(const Statistic& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Statistic(Statistic&& from) noexcept
    : Statistic() {
    *this = ::std::move(from);
  }

  inline Statistic& operator=(Statistic&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const Statistic& default_instance();

  static inline const Statistic* internal_default_instance() {
    return reinterpret_cast<const Statistic*>(
               &_Statistic_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    1;

  void Swap(Statistic* other);
  friend void swap(Statistic& a, Statistic& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Statistic* New() const PROTOBUF_FINAL { return New(NULL); }

  Statistic* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const Statistic& from);
  void MergeFrom(const Statistic& from);
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
  void InternalSwap(Statistic* other);
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

  typedef Statistic_Item Item;

  typedef Statistic_State State;
  static const State WAITING =
    Statistic_State_WAITING;
  static const State RECEIVING =
    Statistic_State_RECEIVING;
  static const State CALCULATING =
    Statistic_State_CALCULATING;
  static inline bool State_IsValid(int value) {
    return Statistic_State_IsValid(value);
  }
  static const State State_MIN =
    Statistic_State_State_MIN;
  static const State State_MAX =
    Statistic_State_State_MAX;
  static const int State_ARRAYSIZE =
    Statistic_State_State_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  State_descriptor() {
    return Statistic_State_descriptor();
  }
  static inline const ::std::string& State_Name(State value) {
    return Statistic_State_Name(value);
  }
  static inline bool State_Parse(const ::std::string& name,
      State* value) {
    return Statistic_State_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  // repeated .external.client.classification.Statistic.Item item = 1;
  int item_size() const;
  void clear_item();
  static const int kItemFieldNumber = 1;
  const ::external::client::classification::Statistic_Item& item(int index) const;
  ::external::client::classification::Statistic_Item* mutable_item(int index);
  ::external::client::classification::Statistic_Item* add_item();
  ::google::protobuf::RepeatedPtrField< ::external::client::classification::Statistic_Item >*
      mutable_item();
  const ::google::protobuf::RepeatedPtrField< ::external::client::classification::Statistic_Item >&
      item() const;

  // @@protoc_insertion_point(class_scope:external.client.classification.Statistic)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::RepeatedPtrField< ::external::client::classification::Statistic_Item > item_;
  mutable int _cached_size_;
  friend struct protobuf_client_5fmsg_2fclassification_2fclass_5fstatistic_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Statistic_Item

// .external.client.Signal signal = 1;
inline bool Statistic_Item::has_signal() const {
  return this != internal_default_instance() && signal_ != NULL;
}
inline void Statistic_Item::clear_signal() {
  if (GetArenaNoVirtual() == NULL && signal_ != NULL) delete signal_;
  signal_ = NULL;
}
inline const ::external::client::Signal& Statistic_Item::signal() const {
  const ::external::client::Signal* p = signal_;
  // @@protoc_insertion_point(field_get:external.client.classification.Statistic.Item.signal)
  return p != NULL ? *p : *reinterpret_cast<const ::external::client::Signal*>(
      &::external::client::_Signal_default_instance_);
}
inline ::external::client::Signal* Statistic_Item::mutable_signal() {
  
  if (signal_ == NULL) {
    signal_ = new ::external::client::Signal;
  }
  // @@protoc_insertion_point(field_mutable:external.client.classification.Statistic.Item.signal)
  return signal_;
}
inline ::external::client::Signal* Statistic_Item::release_signal() {
  // @@protoc_insertion_point(field_release:external.client.classification.Statistic.Item.signal)
  
  ::external::client::Signal* temp = signal_;
  signal_ = NULL;
  return temp;
}
inline void Statistic_Item::set_allocated_signal(::external::client::Signal* signal) {
  delete signal_;
  signal_ = signal;
  if (signal) {
    
  } else {
    
  }
  // @@protoc_insertion_point(field_set_allocated:external.client.classification.Statistic.Item.signal)
}

// .external.client.classification.Statistic.State state = 2;
inline void Statistic_Item::clear_state() {
  state_ = 0;
}
inline ::external::client::classification::Statistic_State Statistic_Item::state() const {
  // @@protoc_insertion_point(field_get:external.client.classification.Statistic.Item.state)
  return static_cast< ::external::client::classification::Statistic_State >(state_);
}
inline void Statistic_Item::set_state(::external::client::classification::Statistic_State value) {
  
  state_ = value;
  // @@protoc_insertion_point(field_set:external.client.classification.Statistic.Item.state)
}

// uint64 total_samples = 3;
inline void Statistic_Item::clear_total_samples() {
  total_samples_ = GOOGLE_ULONGLONG(0);
}
inline ::google::protobuf::uint64 Statistic_Item::total_samples() const {
  // @@protoc_insertion_point(field_get:external.client.classification.Statistic.Item.total_samples)
  return total_samples_;
}
inline void Statistic_Item::set_total_samples(::google::protobuf::uint64 value) {
  
  total_samples_ = value;
  // @@protoc_insertion_point(field_set:external.client.classification.Statistic.Item.total_samples)
}

// uint64 received_samples = 4;
inline void Statistic_Item::clear_received_samples() {
  received_samples_ = GOOGLE_ULONGLONG(0);
}
inline ::google::protobuf::uint64 Statistic_Item::received_samples() const {
  // @@protoc_insertion_point(field_get:external.client.classification.Statistic.Item.received_samples)
  return received_samples_;
}
inline void Statistic_Item::set_received_samples(::google::protobuf::uint64 value) {
  
  received_samples_ = value;
  // @@protoc_insertion_point(field_set:external.client.classification.Statistic.Item.received_samples)
}

// -------------------------------------------------------------------

// Statistic

// repeated .external.client.classification.Statistic.Item item = 1;
inline int Statistic::item_size() const {
  return item_.size();
}
inline void Statistic::clear_item() {
  item_.Clear();
}
inline const ::external::client::classification::Statistic_Item& Statistic::item(int index) const {
  // @@protoc_insertion_point(field_get:external.client.classification.Statistic.item)
  return item_.Get(index);
}
inline ::external::client::classification::Statistic_Item* Statistic::mutable_item(int index) {
  // @@protoc_insertion_point(field_mutable:external.client.classification.Statistic.item)
  return item_.Mutable(index);
}
inline ::external::client::classification::Statistic_Item* Statistic::add_item() {
  // @@protoc_insertion_point(field_add:external.client.classification.Statistic.item)
  return item_.Add();
}
inline ::google::protobuf::RepeatedPtrField< ::external::client::classification::Statistic_Item >*
Statistic::mutable_item() {
  // @@protoc_insertion_point(field_mutable_list:external.client.classification.Statistic.item)
  return &item_;
}
inline const ::google::protobuf::RepeatedPtrField< ::external::client::classification::Statistic_Item >&
Statistic::item() const {
  // @@protoc_insertion_point(field_list:external.client.classification.Statistic.item)
  return item_;
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)


}  // namespace classification
}  // namespace client
}  // namespace external

namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::external::client::classification::Statistic_State> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::external::client::classification::Statistic_State>() {
  return ::external::client::classification::Statistic_State_descriptor();
}

}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_client_5fmsg_2fclassification_2fclass_5fstatistic_2eproto__INCLUDED
