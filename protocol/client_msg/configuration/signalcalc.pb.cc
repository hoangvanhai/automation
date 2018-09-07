// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: client_msg/configuration/signalcalc.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "client_msg/configuration/signalcalc.pb.h"

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
namespace configuration {
class ConfigureSignalCalculationDefaultTypeInternal {
public:
 ::google::protobuf::internal::ExplicitlyConstructed<ConfigureSignalCalculation>
     _instance;
} _ConfigureSignalCalculation_default_instance_;

namespace protobuf_client_5fmsg_2fconfiguration_2fsignalcalc_2eproto {


namespace {

::google::protobuf::Metadata file_level_metadata[1];

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
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ConfigureSignalCalculation, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ConfigureSignalCalculation, mode_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ConfigureSignalCalculation, option_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ConfigureSignalCalculation, factor_),
};
static const ::google::protobuf::internal::MigrationSchema schemas[] GOOGLE_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(ConfigureSignalCalculation)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&_ConfigureSignalCalculation_default_instance_),
};

namespace {

void protobuf_AssignDescriptors() {
  AddDescriptors();
  ::google::protobuf::MessageFactory* factory = NULL;
  AssignDescriptors(
      "client_msg/configuration/signalcalc.proto", schemas, file_default_instances, TableStruct::offsets, factory,
      file_level_metadata, NULL, NULL);
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
  _ConfigureSignalCalculation_default_instance_._instance.DefaultConstruct();
  ::google::protobuf::internal::OnShutdownDestroyMessage(
      &_ConfigureSignalCalculation_default_instance_);}

void InitDefaults() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &TableStruct::InitDefaultsImpl);
}
namespace {
void AddDescriptorsImpl() {
  InitDefaults();
  static const char descriptor[] GOOGLE_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
      "\n)client_msg/configuration/signalcalc.pr"
      "oto\022\035external.client.configuration\"J\n\032Co"
      "nfigureSignalCalculation\022\014\n\004mode\030\001 \001(\r\022\016"
      "\n\006option\030\002 \001(\r\022\016\n\006factor\030\003 \001(\002b\006proto3"
  };
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
      descriptor, 158);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "client_msg/configuration/signalcalc.proto", &protobuf_RegisterTypes);
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

}  // namespace protobuf_client_5fmsg_2fconfiguration_2fsignalcalc_2eproto


// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int ConfigureSignalCalculation::kModeFieldNumber;
const int ConfigureSignalCalculation::kOptionFieldNumber;
const int ConfigureSignalCalculation::kFactorFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

ConfigureSignalCalculation::ConfigureSignalCalculation()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (GOOGLE_PREDICT_TRUE(this != internal_default_instance())) {
    protobuf_client_5fmsg_2fconfiguration_2fsignalcalc_2eproto::InitDefaults();
  }
  SharedCtor();
  // @@protoc_insertion_point(constructor:external.client.configuration.ConfigureSignalCalculation)
}
ConfigureSignalCalculation::ConfigureSignalCalculation(const ConfigureSignalCalculation& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      _cached_size_(0) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::memcpy(&mode_, &from.mode_,
    static_cast<size_t>(reinterpret_cast<char*>(&factor_) -
    reinterpret_cast<char*>(&mode_)) + sizeof(factor_));
  // @@protoc_insertion_point(copy_constructor:external.client.configuration.ConfigureSignalCalculation)
}

void ConfigureSignalCalculation::SharedCtor() {
  ::memset(&mode_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&factor_) -
      reinterpret_cast<char*>(&mode_)) + sizeof(factor_));
  _cached_size_ = 0;
}

ConfigureSignalCalculation::~ConfigureSignalCalculation() {
  // @@protoc_insertion_point(destructor:external.client.configuration.ConfigureSignalCalculation)
  SharedDtor();
}

void ConfigureSignalCalculation::SharedDtor() {
}

void ConfigureSignalCalculation::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* ConfigureSignalCalculation::descriptor() {
  protobuf_client_5fmsg_2fconfiguration_2fsignalcalc_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_client_5fmsg_2fconfiguration_2fsignalcalc_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const ConfigureSignalCalculation& ConfigureSignalCalculation::default_instance() {
  protobuf_client_5fmsg_2fconfiguration_2fsignalcalc_2eproto::InitDefaults();
  return *internal_default_instance();
}

ConfigureSignalCalculation* ConfigureSignalCalculation::New(::google::protobuf::Arena* arena) const {
  ConfigureSignalCalculation* n = new ConfigureSignalCalculation;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void ConfigureSignalCalculation::Clear() {
// @@protoc_insertion_point(message_clear_start:external.client.configuration.ConfigureSignalCalculation)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  ::memset(&mode_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&factor_) -
      reinterpret_cast<char*>(&mode_)) + sizeof(factor_));
  _internal_metadata_.Clear();
}

bool ConfigureSignalCalculation::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:external.client.configuration.ConfigureSignalCalculation)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // uint32 mode = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(8u /* 8 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &mode_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // uint32 option = 2;
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(16u /* 16 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &option_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // float factor = 3;
      case 3: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(29u /* 29 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(
                 input, &factor_)));
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
  // @@protoc_insertion_point(parse_success:external.client.configuration.ConfigureSignalCalculation)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:external.client.configuration.ConfigureSignalCalculation)
  return false;
#undef DO_
}

void ConfigureSignalCalculation::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:external.client.configuration.ConfigureSignalCalculation)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // uint32 mode = 1;
  if (this->mode() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->mode(), output);
  }

  // uint32 option = 2;
  if (this->option() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->option(), output);
  }

  // float factor = 3;
  if (this->factor() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteFloat(3, this->factor(), output);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), output);
  }
  // @@protoc_insertion_point(serialize_end:external.client.configuration.ConfigureSignalCalculation)
}

::google::protobuf::uint8* ConfigureSignalCalculation::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:external.client.configuration.ConfigureSignalCalculation)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // uint32 mode = 1;
  if (this->mode() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->mode(), target);
  }

  // uint32 option = 2;
  if (this->option() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->option(), target);
  }

  // float factor = 3;
  if (this->factor() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteFloatToArray(3, this->factor(), target);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:external.client.configuration.ConfigureSignalCalculation)
  return target;
}

size_t ConfigureSignalCalculation::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:external.client.configuration.ConfigureSignalCalculation)
  size_t total_size = 0;

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()));
  }
  // uint32 mode = 1;
  if (this->mode() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::UInt32Size(
        this->mode());
  }

  // uint32 option = 2;
  if (this->option() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::UInt32Size(
        this->option());
  }

  // float factor = 3;
  if (this->factor() != 0) {
    total_size += 1 + 4;
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void ConfigureSignalCalculation::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:external.client.configuration.ConfigureSignalCalculation)
  GOOGLE_DCHECK_NE(&from, this);
  const ConfigureSignalCalculation* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const ConfigureSignalCalculation>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:external.client.configuration.ConfigureSignalCalculation)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:external.client.configuration.ConfigureSignalCalculation)
    MergeFrom(*source);
  }
}

void ConfigureSignalCalculation::MergeFrom(const ConfigureSignalCalculation& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:external.client.configuration.ConfigureSignalCalculation)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.mode() != 0) {
    set_mode(from.mode());
  }
  if (from.option() != 0) {
    set_option(from.option());
  }
  if (from.factor() != 0) {
    set_factor(from.factor());
  }
}

void ConfigureSignalCalculation::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:external.client.configuration.ConfigureSignalCalculation)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void ConfigureSignalCalculation::CopyFrom(const ConfigureSignalCalculation& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:external.client.configuration.ConfigureSignalCalculation)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ConfigureSignalCalculation::IsInitialized() const {
  return true;
}

void ConfigureSignalCalculation::Swap(ConfigureSignalCalculation* other) {
  if (other == this) return;
  InternalSwap(other);
}
void ConfigureSignalCalculation::InternalSwap(ConfigureSignalCalculation* other) {
  using std::swap;
  swap(mode_, other->mode_);
  swap(option_, other->option_);
  swap(factor_, other->factor_);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata ConfigureSignalCalculation::GetMetadata() const {
  protobuf_client_5fmsg_2fconfiguration_2fsignalcalc_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_client_5fmsg_2fconfiguration_2fsignalcalc_2eproto::file_level_metadata[kIndexInFileMessages];
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// ConfigureSignalCalculation

// uint32 mode = 1;
void ConfigureSignalCalculation::clear_mode() {
  mode_ = 0u;
}
::google::protobuf::uint32 ConfigureSignalCalculation::mode() const {
  // @@protoc_insertion_point(field_get:external.client.configuration.ConfigureSignalCalculation.mode)
  return mode_;
}
void ConfigureSignalCalculation::set_mode(::google::protobuf::uint32 value) {
  
  mode_ = value;
  // @@protoc_insertion_point(field_set:external.client.configuration.ConfigureSignalCalculation.mode)
}

// uint32 option = 2;
void ConfigureSignalCalculation::clear_option() {
  option_ = 0u;
}
::google::protobuf::uint32 ConfigureSignalCalculation::option() const {
  // @@protoc_insertion_point(field_get:external.client.configuration.ConfigureSignalCalculation.option)
  return option_;
}
void ConfigureSignalCalculation::set_option(::google::protobuf::uint32 value) {
  
  option_ = value;
  // @@protoc_insertion_point(field_set:external.client.configuration.ConfigureSignalCalculation.option)
}

// float factor = 3;
void ConfigureSignalCalculation::clear_factor() {
  factor_ = 0;
}
float ConfigureSignalCalculation::factor() const {
  // @@protoc_insertion_point(field_get:external.client.configuration.ConfigureSignalCalculation.factor)
  return factor_;
}
void ConfigureSignalCalculation::set_factor(float value) {
  
  factor_ = value;
  // @@protoc_insertion_point(field_set:external.client.configuration.ConfigureSignalCalculation.factor)
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace configuration
}  // namespace client
}  // namespace external

// @@protoc_insertion_point(global_scope)