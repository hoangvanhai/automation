// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: client_msg/calibration/table.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "client_msg/calibration/table.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace external {
namespace client {
namespace calibration {
class AddTableDefaultTypeInternal {
public:
 ::google::protobuf::internal::ExplicitlyConstructed<AddTable>
     _instance;
} _AddTable_default_instance_;

namespace protobuf_client_5fmsg_2fcalibration_2ftable_2eproto {


namespace {

::google::protobuf::Metadata file_level_metadata[1];
const ::google::protobuf::EnumDescriptor* file_level_enum_descriptors[1];

}  // namespace

PROTOBUF_CONSTEXPR_VAR ::google::protobuf::internal::ParseTableField
    const TableStruct::entries[] GOOGLE_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  {0, 0, 0, ::google::protobuf::internal::kInvalidMask, 0, 0},
};

PROTOBUF_CONSTEXPR_VAR ::google::protobuf::internal::AuxillaryParseTableField
    const TableStruct::aux[] GOOGLE_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  ::google::protobuf::internal::AuxillaryParseTableField(),
};
PROTOBUF_CONSTEXPR_VAR ::google::protobuf::internal::ParseTable const
    TableStruct::schema[] GOOGLE_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  { NULL, NULL, 0, -1, -1, -1, -1, NULL, false },
};

const ::google::protobuf::uint32 TableStruct::offsets[] GOOGLE_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AddTable, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AddTable, table_index_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AddTable, sample_index_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AddTable, samples_),
};
static const ::google::protobuf::internal::MigrationSchema schemas[] GOOGLE_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(AddTable)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&_AddTable_default_instance_),
};

namespace {

void protobuf_AssignDescriptors() {
  AddDescriptors();
  ::google::protobuf::MessageFactory* factory = NULL;
  AssignDescriptors(
      "client_msg/calibration/table.proto", schemas, file_default_instances, TableStruct::offsets, factory,
      file_level_metadata, file_level_enum_descriptors, NULL);
}

void protobuf_AssignDescriptorsOnce() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &protobuf_AssignDescriptors);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::internal::RegisterAllTypes(file_level_metadata, 1);
}

}  // namespace
void TableStruct::InitDefaultsImpl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::internal::InitProtobufDefaults();
  _AddTable_default_instance_._instance.DefaultConstruct();
  ::google::protobuf::internal::OnShutdownDestroyMessage(
      &_AddTable_default_instance_);}

void InitDefaults() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &TableStruct::InitDefaultsImpl);
}
namespace {
void AddDescriptorsImpl() {
  InitDefaults();
  static const char descriptor[] GOOGLE_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
      "\n\"client_msg/calibration/table.proto\022\033ex"
      "ternal.client.calibration\"o\n\010AddTable\022<\n"
      "\013table_index\030\001 \001(\0162\'.external.client.cal"
      "ibration.TableIndex\022\024\n\014sample_index\030\002 \001("
      "\r\022\017\n\007samples\030\003 \003(\002*+\n\nTableIndex\022\007\n\003HOT\020"
      "\000\022\n\n\006NORMAL\020\001\022\010\n\004COOL\020\002b\006proto3"
  };
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
      descriptor, 231);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "client_msg/calibration/table.proto", &protobuf_RegisterTypes);
}
} // anonymous namespace

void AddDescriptors() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &AddDescriptorsImpl);
}
// Force AddDescriptors() to be called at dynamic initialization time.
struct StaticDescriptorInitializer {
  StaticDescriptorInitializer() {
    AddDescriptors();
  }
} static_descriptor_initializer;

}  // namespace protobuf_client_5fmsg_2fcalibration_2ftable_2eproto

const ::google::protobuf::EnumDescriptor* TableIndex_descriptor() {
  protobuf_client_5fmsg_2fcalibration_2ftable_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_client_5fmsg_2fcalibration_2ftable_2eproto::file_level_enum_descriptors[0];
}
bool TableIndex_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 2:
      return true;
    default:
      return false;
  }
}


// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int AddTable::kTableIndexFieldNumber;
const int AddTable::kSampleIndexFieldNumber;
const int AddTable::kSamplesFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

AddTable::AddTable()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (GOOGLE_PREDICT_TRUE(this != internal_default_instance())) {
    protobuf_client_5fmsg_2fcalibration_2ftable_2eproto::InitDefaults();
  }
  SharedCtor();
  // @@protoc_insertion_point(constructor:external.client.calibration.AddTable)
}
AddTable::AddTable(const AddTable& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      samples_(from.samples_),
      _cached_size_(0) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::memcpy(&table_index_, &from.table_index_,
    static_cast<size_t>(reinterpret_cast<char*>(&sample_index_) -
    reinterpret_cast<char*>(&table_index_)) + sizeof(sample_index_));
  // @@protoc_insertion_point(copy_constructor:external.client.calibration.AddTable)
}

void AddTable::SharedCtor() {
  ::memset(&table_index_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&sample_index_) -
      reinterpret_cast<char*>(&table_index_)) + sizeof(sample_index_));
  _cached_size_ = 0;
}

AddTable::~AddTable() {
  // @@protoc_insertion_point(destructor:external.client.calibration.AddTable)
  SharedDtor();
}

void AddTable::SharedDtor() {
}

void AddTable::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* AddTable::descriptor() {
  protobuf_client_5fmsg_2fcalibration_2ftable_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_client_5fmsg_2fcalibration_2ftable_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const AddTable& AddTable::default_instance() {
  protobuf_client_5fmsg_2fcalibration_2ftable_2eproto::InitDefaults();
  return *internal_default_instance();
}

AddTable* AddTable::New(::google::protobuf::Arena* arena) const {
  AddTable* n = new AddTable;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void AddTable::Clear() {
// @@protoc_insertion_point(message_clear_start:external.client.calibration.AddTable)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  samples_.Clear();
  ::memset(&table_index_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&sample_index_) -
      reinterpret_cast<char*>(&table_index_)) + sizeof(sample_index_));
  _internal_metadata_.Clear();
}

bool AddTable::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:external.client.calibration.AddTable)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // .external.client.calibration.TableIndex table_index = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(8u /* 8 & 0xFF */)) {
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          set_table_index(static_cast< ::external::client::calibration::TableIndex >(value));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // uint32 sample_index = 2;
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(16u /* 16 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &sample_index_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // repeated float samples = 3;
      case 3: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(26u /* 26 & 0xFF */)) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPackedPrimitive<
                   float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(
                 input, this->mutable_samples())));
        } else if (
            static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(29u /* 29 & 0xFF */)) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadRepeatedPrimitiveNoInline<
                   float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(
                 1, 26u, input, this->mutable_samples())));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:external.client.calibration.AddTable)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:external.client.calibration.AddTable)
  return false;
#undef DO_
}

void AddTable::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:external.client.calibration.AddTable)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // .external.client.calibration.TableIndex table_index = 1;
  if (this->table_index() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      1, this->table_index(), output);
  }

  // uint32 sample_index = 2;
  if (this->sample_index() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->sample_index(), output);
  }

  // repeated float samples = 3;
  if (this->samples_size() > 0) {
    ::google::protobuf::internal::WireFormatLite::WriteTag(3, ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED, output);
    output->WriteVarint32(static_cast< ::google::protobuf::uint32>(
        _samples_cached_byte_size_));
    ::google::protobuf::internal::WireFormatLite::WriteFloatArray(
      this->samples().data(), this->samples_size(), output);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), output);
  }
  // @@protoc_insertion_point(serialize_end:external.client.calibration.AddTable)
}

::google::protobuf::uint8* AddTable::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:external.client.calibration.AddTable)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // .external.client.calibration.TableIndex table_index = 1;
  if (this->table_index() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      1, this->table_index(), target);
  }

  // uint32 sample_index = 2;
  if (this->sample_index() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->sample_index(), target);
  }

  // repeated float samples = 3;
  if (this->samples_size() > 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteTagToArray(
      3,
      ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED,
      target);
    target = ::google::protobuf::io::CodedOutputStream::WriteVarint32ToArray(
        static_cast< ::google::protobuf::uint32>(
            _samples_cached_byte_size_), target);
    target = ::google::protobuf::internal::WireFormatLite::
      WriteFloatNoTagToArray(this->samples_, target);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:external.client.calibration.AddTable)
  return target;
}

size_t AddTable::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:external.client.calibration.AddTable)
  size_t total_size = 0;

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()));
  }
  // repeated float samples = 3;
  {
    unsigned int count = static_cast<unsigned int>(this->samples_size());
    size_t data_size = 4UL * count;
    if (data_size > 0) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
            static_cast< ::google::protobuf::int32>(data_size));
    }
    int cached_size = ::google::protobuf::internal::ToCachedSize(data_size);
    GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
    _samples_cached_byte_size_ = cached_size;
    GOOGLE_SAFE_CONCURRENT_WRITES_END();
    total_size += data_size;
  }

  // .external.client.calibration.TableIndex table_index = 1;
  if (this->table_index() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::EnumSize(this->table_index());
  }

  // uint32 sample_index = 2;
  if (this->sample_index() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::UInt32Size(
        this->sample_index());
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void AddTable::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:external.client.calibration.AddTable)
  GOOGLE_DCHECK_NE(&from, this);
  const AddTable* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const AddTable>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:external.client.calibration.AddTable)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:external.client.calibration.AddTable)
    MergeFrom(*source);
  }
}

void AddTable::MergeFrom(const AddTable& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:external.client.calibration.AddTable)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  samples_.MergeFrom(from.samples_);
  if (from.table_index() != 0) {
    set_table_index(from.table_index());
  }
  if (from.sample_index() != 0) {
    set_sample_index(from.sample_index());
  }
}

void AddTable::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:external.client.calibration.AddTable)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void AddTable::CopyFrom(const AddTable& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:external.client.calibration.AddTable)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool AddTable::IsInitialized() const {
  return true;
}

void AddTable::Swap(AddTable* other) {
  if (other == this) return;
  InternalSwap(other);
}
void AddTable::InternalSwap(AddTable* other) {
  using std::swap;
  samples_.InternalSwap(&other->samples_);
  swap(table_index_, other->table_index_);
  swap(sample_index_, other->sample_index_);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata AddTable::GetMetadata() const {
  protobuf_client_5fmsg_2fcalibration_2ftable_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_client_5fmsg_2fcalibration_2ftable_2eproto::file_level_metadata[kIndexInFileMessages];
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// AddTable

// .external.client.calibration.TableIndex table_index = 1;
void AddTable::clear_table_index() {
  table_index_ = 0;
}
::external::client::calibration::TableIndex AddTable::table_index() const {
  // @@protoc_insertion_point(field_get:external.client.calibration.AddTable.table_index)
  return static_cast< ::external::client::calibration::TableIndex >(table_index_);
}
void AddTable::set_table_index(::external::client::calibration::TableIndex value) {
  
  table_index_ = value;
  // @@protoc_insertion_point(field_set:external.client.calibration.AddTable.table_index)
}

// uint32 sample_index = 2;
void AddTable::clear_sample_index() {
  sample_index_ = 0u;
}
::google::protobuf::uint32 AddTable::sample_index() const {
  // @@protoc_insertion_point(field_get:external.client.calibration.AddTable.sample_index)
  return sample_index_;
}
void AddTable::set_sample_index(::google::protobuf::uint32 value) {
  
  sample_index_ = value;
  // @@protoc_insertion_point(field_set:external.client.calibration.AddTable.sample_index)
}

// repeated float samples = 3;
int AddTable::samples_size() const {
  return samples_.size();
}
void AddTable::clear_samples() {
  samples_.Clear();
}
float AddTable::samples(int index) const {
  // @@protoc_insertion_point(field_get:external.client.calibration.AddTable.samples)
  return samples_.Get(index);
}
void AddTable::set_samples(int index, float value) {
  samples_.Set(index, value);
  // @@protoc_insertion_point(field_set:external.client.calibration.AddTable.samples)
}
void AddTable::add_samples(float value) {
  samples_.Add(value);
  // @@protoc_insertion_point(field_add:external.client.calibration.AddTable.samples)
}
const ::google::protobuf::RepeatedField< float >&
AddTable::samples() const {
  // @@protoc_insertion_point(field_list:external.client.calibration.AddTable.samples)
  return samples_;
}
::google::protobuf::RepeatedField< float >*
AddTable::mutable_samples() {
  // @@protoc_insertion_point(field_mutable_list:external.client.calibration.AddTable.samples)
  return &samples_;
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace calibration
}  // namespace client
}  // namespace external

// @@protoc_insertion_point(global_scope)
