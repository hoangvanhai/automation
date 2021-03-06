// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: client_msg/calibration/table.proto

#ifndef PROTOBUF_client_5fmsg_2fcalibration_2ftable_2eproto__INCLUDED
#define PROTOBUF_client_5fmsg_2fcalibration_2ftable_2eproto__INCLUDED

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
namespace calibration {
class AddTable;
class AddTableDefaultTypeInternal;
extern AddTableDefaultTypeInternal _AddTable_default_instance_;
}  // namespace calibration
}  // namespace client
}  // namespace external

namespace external {
namespace client {
namespace calibration {

namespace protobuf_client_5fmsg_2fcalibration_2ftable_2eproto {
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
}  // namespace protobuf_client_5fmsg_2fcalibration_2ftable_2eproto

enum TableIndex {
  HOT = 0,
  NORMAL = 1,
  COOL = 2,
  TableIndex_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  TableIndex_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool TableIndex_IsValid(int value);
const TableIndex TableIndex_MIN = HOT;
const TableIndex TableIndex_MAX = COOL;
const int TableIndex_ARRAYSIZE = TableIndex_MAX + 1;

const ::google::protobuf::EnumDescriptor* TableIndex_descriptor();
inline const ::std::string& TableIndex_Name(TableIndex value) {
  return ::google::protobuf::internal::NameOfEnum(
    TableIndex_descriptor(), value);
}
inline bool TableIndex_Parse(
    const ::std::string& name, TableIndex* value) {
  return ::google::protobuf::internal::ParseNamedEnum<TableIndex>(
    TableIndex_descriptor(), name, value);
}
// ===================================================================

class AddTable : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:external.client.calibration.AddTable) */ {
 public:
  AddTable();
  virtual ~AddTable();

  AddTable(const AddTable& from);

  inline AddTable& operator=(const AddTable& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  AddTable(AddTable&& from) noexcept
    : AddTable() {
    *this = ::std::move(from);
  }

  inline AddTable& operator=(AddTable&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const AddTable& default_instance();

  static inline const AddTable* internal_default_instance() {
    return reinterpret_cast<const AddTable*>(
               &_AddTable_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    0;

  void Swap(AddTable* other);
  friend void swap(AddTable& a, AddTable& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline AddTable* New() const PROTOBUF_FINAL { return New(NULL); }

  AddTable* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const AddTable& from);
  void MergeFrom(const AddTable& from);
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
  void InternalSwap(AddTable* other);
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

  // repeated float samples = 3;
  int samples_size() const;
  void clear_samples();
  static const int kSamplesFieldNumber = 3;
  float samples(int index) const;
  void set_samples(int index, float value);
  void add_samples(float value);
  const ::google::protobuf::RepeatedField< float >&
      samples() const;
  ::google::protobuf::RepeatedField< float >*
      mutable_samples();

  // .external.client.calibration.TableIndex table_index = 1;
  void clear_table_index();
  static const int kTableIndexFieldNumber = 1;
  ::external::client::calibration::TableIndex table_index() const;
  void set_table_index(::external::client::calibration::TableIndex value);

  // uint32 sample_index = 2;
  void clear_sample_index();
  static const int kSampleIndexFieldNumber = 2;
  ::google::protobuf::uint32 sample_index() const;
  void set_sample_index(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:external.client.calibration.AddTable)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::RepeatedField< float > samples_;
  mutable int _samples_cached_byte_size_;
  int table_index_;
  ::google::protobuf::uint32 sample_index_;
  mutable int _cached_size_;
  friend struct protobuf_client_5fmsg_2fcalibration_2ftable_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// AddTable

// .external.client.calibration.TableIndex table_index = 1;
inline void AddTable::clear_table_index() {
  table_index_ = 0;
}
inline ::external::client::calibration::TableIndex AddTable::table_index() const {
  // @@protoc_insertion_point(field_get:external.client.calibration.AddTable.table_index)
  return static_cast< ::external::client::calibration::TableIndex >(table_index_);
}
inline void AddTable::set_table_index(::external::client::calibration::TableIndex value) {
  
  table_index_ = value;
  // @@protoc_insertion_point(field_set:external.client.calibration.AddTable.table_index)
}

// uint32 sample_index = 2;
inline void AddTable::clear_sample_index() {
  sample_index_ = 0u;
}
inline ::google::protobuf::uint32 AddTable::sample_index() const {
  // @@protoc_insertion_point(field_get:external.client.calibration.AddTable.sample_index)
  return sample_index_;
}
inline void AddTable::set_sample_index(::google::protobuf::uint32 value) {
  
  sample_index_ = value;
  // @@protoc_insertion_point(field_set:external.client.calibration.AddTable.sample_index)
}

// repeated float samples = 3;
inline int AddTable::samples_size() const {
  return samples_.size();
}
inline void AddTable::clear_samples() {
  samples_.Clear();
}
inline float AddTable::samples(int index) const {
  // @@protoc_insertion_point(field_get:external.client.calibration.AddTable.samples)
  return samples_.Get(index);
}
inline void AddTable::set_samples(int index, float value) {
  samples_.Set(index, value);
  // @@protoc_insertion_point(field_set:external.client.calibration.AddTable.samples)
}
inline void AddTable::add_samples(float value) {
  samples_.Add(value);
  // @@protoc_insertion_point(field_add:external.client.calibration.AddTable.samples)
}
inline const ::google::protobuf::RepeatedField< float >&
AddTable::samples() const {
  // @@protoc_insertion_point(field_list:external.client.calibration.AddTable.samples)
  return samples_;
}
inline ::google::protobuf::RepeatedField< float >*
AddTable::mutable_samples() {
  // @@protoc_insertion_point(field_mutable_list:external.client.calibration.AddTable.samples)
  return &samples_;
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)


}  // namespace calibration
}  // namespace client
}  // namespace external

namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::external::client::calibration::TableIndex> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::external::client::calibration::TableIndex>() {
  return ::external::client::calibration::TableIndex_descriptor();
}

}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_client_5fmsg_2fcalibration_2ftable_2eproto__INCLUDED
