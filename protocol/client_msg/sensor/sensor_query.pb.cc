// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: client_msg/sensor/sensor_query.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "client_msg/sensor/sensor_query.pb.h"

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
namespace sensor {
class QueryDefaultTypeInternal {
public:
 ::google::protobuf::internal::ExplicitlyConstructed<Query>
     _instance;
} _Query_default_instance_;
class ResponseDefaultTypeInternal {
public:
 ::google::protobuf::internal::ExplicitlyConstructed<Response>
     _instance;
} _Response_default_instance_;

namespace protobuf_client_5fmsg_2fsensor_2fsensor_5fquery_2eproto {


namespace {

::google::protobuf::Metadata file_level_metadata[2];

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
  { NULL, NULL, 0, -1, -1, -1, -1, NULL, false },
};

const ::google::protobuf::uint32 TableStruct::offsets[] GOOGLE_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Query, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Query, sensor_),
  ~0u,  // no _has_bits_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Response, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Response, sensor_),
};
static const ::google::protobuf::internal::MigrationSchema schemas[] GOOGLE_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(Query)},
  { 6, -1, sizeof(Response)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&_Query_default_instance_),
  reinterpret_cast<const ::google::protobuf::Message*>(&_Response_default_instance_),
};

namespace {

void protobuf_AssignDescriptors() {
  AddDescriptors();
  ::google::protobuf::MessageFactory* factory = NULL;
  AssignDescriptors(
      "client_msg/sensor/sensor_query.proto", schemas, file_default_instances, TableStruct::offsets, factory,
      file_level_metadata, NULL, NULL);
}

void protobuf_AssignDescriptorsOnce() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &protobuf_AssignDescriptors);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::internal::RegisterAllTypes(file_level_metadata, 2);
}

}  // namespace
void TableStruct::InitDefaultsImpl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::internal::InitProtobufDefaults();
  ::external::client::protobuf_client_5fmsg_2fcommon_2eproto::InitDefaults();
  _Query_default_instance_._instance.DefaultConstruct();
  ::google::protobuf::internal::OnShutdownDestroyMessage(
      &_Query_default_instance_);_Response_default_instance_._instance.DefaultConstruct();
  ::google::protobuf::internal::OnShutdownDestroyMessage(
      &_Response_default_instance_);}

void InitDefaults() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &TableStruct::InitDefaultsImpl);
}
namespace {
void AddDescriptorsImpl() {
  InitDefaults();
  static const char descriptor[] GOOGLE_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
      "\n$client_msg/sensor/sensor_query.proto\022\026"
      "external.client.sensor\032\027client_msg/commo"
      "n.proto\"0\n\005Query\022\'\n\006sensor\030\001 \003(\0132\027.exter"
      "nal.client.Sensor\"3\n\010Response\022\'\n\006sensor\030"
      "\001 \003(\0132\027.external.client.Sensorb\006proto3"
  };
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
      descriptor, 198);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "client_msg/sensor/sensor_query.proto", &protobuf_RegisterTypes);
  ::external::client::protobuf_client_5fmsg_2fcommon_2eproto::AddDescriptors();
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

}  // namespace protobuf_client_5fmsg_2fsensor_2fsensor_5fquery_2eproto


// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int Query::kSensorFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

Query::Query()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (GOOGLE_PREDICT_TRUE(this != internal_default_instance())) {
    protobuf_client_5fmsg_2fsensor_2fsensor_5fquery_2eproto::InitDefaults();
  }
  SharedCtor();
  // @@protoc_insertion_point(constructor:external.client.sensor.Query)
}
Query::Query(const Query& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      sensor_(from.sensor_),
      _cached_size_(0) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  // @@protoc_insertion_point(copy_constructor:external.client.sensor.Query)
}

void Query::SharedCtor() {
  _cached_size_ = 0;
}

Query::~Query() {
  // @@protoc_insertion_point(destructor:external.client.sensor.Query)
  SharedDtor();
}

void Query::SharedDtor() {
}

void Query::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Query::descriptor() {
  protobuf_client_5fmsg_2fsensor_2fsensor_5fquery_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_client_5fmsg_2fsensor_2fsensor_5fquery_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const Query& Query::default_instance() {
  protobuf_client_5fmsg_2fsensor_2fsensor_5fquery_2eproto::InitDefaults();
  return *internal_default_instance();
}

Query* Query::New(::google::protobuf::Arena* arena) const {
  Query* n = new Query;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void Query::Clear() {
// @@protoc_insertion_point(message_clear_start:external.client.sensor.Query)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  sensor_.Clear();
  _internal_metadata_.Clear();
}

bool Query::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:external.client.sensor.Query)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .external.client.Sensor sensor = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(10u /* 10 & 0xFF */)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_sensor()));
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
  // @@protoc_insertion_point(parse_success:external.client.sensor.Query)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:external.client.sensor.Query)
  return false;
#undef DO_
}

void Query::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:external.client.sensor.Query)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // repeated .external.client.Sensor sensor = 1;
  for (unsigned int i = 0,
      n = static_cast<unsigned int>(this->sensor_size()); i < n; i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->sensor(static_cast<int>(i)), output);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), output);
  }
  // @@protoc_insertion_point(serialize_end:external.client.sensor.Query)
}

::google::protobuf::uint8* Query::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:external.client.sensor.Query)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // repeated .external.client.Sensor sensor = 1;
  for (unsigned int i = 0,
      n = static_cast<unsigned int>(this->sensor_size()); i < n; i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      InternalWriteMessageNoVirtualToArray(
        1, this->sensor(static_cast<int>(i)), deterministic, target);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:external.client.sensor.Query)
  return target;
}

size_t Query::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:external.client.sensor.Query)
  size_t total_size = 0;

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()));
  }
  // repeated .external.client.Sensor sensor = 1;
  {
    unsigned int count = static_cast<unsigned int>(this->sensor_size());
    total_size += 1UL * count;
    for (unsigned int i = 0; i < count; i++) {
      total_size +=
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->sensor(static_cast<int>(i)));
    }
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void Query::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:external.client.sensor.Query)
  GOOGLE_DCHECK_NE(&from, this);
  const Query* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const Query>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:external.client.sensor.Query)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:external.client.sensor.Query)
    MergeFrom(*source);
  }
}

void Query::MergeFrom(const Query& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:external.client.sensor.Query)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  sensor_.MergeFrom(from.sensor_);
}

void Query::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:external.client.sensor.Query)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Query::CopyFrom(const Query& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:external.client.sensor.Query)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Query::IsInitialized() const {
  return true;
}

void Query::Swap(Query* other) {
  if (other == this) return;
  InternalSwap(other);
}
void Query::InternalSwap(Query* other) {
  using std::swap;
  sensor_.InternalSwap(&other->sensor_);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata Query::GetMetadata() const {
  protobuf_client_5fmsg_2fsensor_2fsensor_5fquery_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_client_5fmsg_2fsensor_2fsensor_5fquery_2eproto::file_level_metadata[kIndexInFileMessages];
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// Query

// repeated .external.client.Sensor sensor = 1;
int Query::sensor_size() const {
  return sensor_.size();
}
void Query::clear_sensor() {
  sensor_.Clear();
}
const ::external::client::Sensor& Query::sensor(int index) const {
  // @@protoc_insertion_point(field_get:external.client.sensor.Query.sensor)
  return sensor_.Get(index);
}
::external::client::Sensor* Query::mutable_sensor(int index) {
  // @@protoc_insertion_point(field_mutable:external.client.sensor.Query.sensor)
  return sensor_.Mutable(index);
}
::external::client::Sensor* Query::add_sensor() {
  // @@protoc_insertion_point(field_add:external.client.sensor.Query.sensor)
  return sensor_.Add();
}
::google::protobuf::RepeatedPtrField< ::external::client::Sensor >*
Query::mutable_sensor() {
  // @@protoc_insertion_point(field_mutable_list:external.client.sensor.Query.sensor)
  return &sensor_;
}
const ::google::protobuf::RepeatedPtrField< ::external::client::Sensor >&
Query::sensor() const {
  // @@protoc_insertion_point(field_list:external.client.sensor.Query.sensor)
  return sensor_;
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int Response::kSensorFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

Response::Response()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (GOOGLE_PREDICT_TRUE(this != internal_default_instance())) {
    protobuf_client_5fmsg_2fsensor_2fsensor_5fquery_2eproto::InitDefaults();
  }
  SharedCtor();
  // @@protoc_insertion_point(constructor:external.client.sensor.Response)
}
Response::Response(const Response& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      sensor_(from.sensor_),
      _cached_size_(0) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  // @@protoc_insertion_point(copy_constructor:external.client.sensor.Response)
}

void Response::SharedCtor() {
  _cached_size_ = 0;
}

Response::~Response() {
  // @@protoc_insertion_point(destructor:external.client.sensor.Response)
  SharedDtor();
}

void Response::SharedDtor() {
}

void Response::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Response::descriptor() {
  protobuf_client_5fmsg_2fsensor_2fsensor_5fquery_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_client_5fmsg_2fsensor_2fsensor_5fquery_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const Response& Response::default_instance() {
  protobuf_client_5fmsg_2fsensor_2fsensor_5fquery_2eproto::InitDefaults();
  return *internal_default_instance();
}

Response* Response::New(::google::protobuf::Arena* arena) const {
  Response* n = new Response;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void Response::Clear() {
// @@protoc_insertion_point(message_clear_start:external.client.sensor.Response)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  sensor_.Clear();
  _internal_metadata_.Clear();
}

bool Response::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:external.client.sensor.Response)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .external.client.Sensor sensor = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(10u /* 10 & 0xFF */)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_sensor()));
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
  // @@protoc_insertion_point(parse_success:external.client.sensor.Response)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:external.client.sensor.Response)
  return false;
#undef DO_
}

void Response::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:external.client.sensor.Response)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // repeated .external.client.Sensor sensor = 1;
  for (unsigned int i = 0,
      n = static_cast<unsigned int>(this->sensor_size()); i < n; i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->sensor(static_cast<int>(i)), output);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), output);
  }
  // @@protoc_insertion_point(serialize_end:external.client.sensor.Response)
}

::google::protobuf::uint8* Response::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:external.client.sensor.Response)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // repeated .external.client.Sensor sensor = 1;
  for (unsigned int i = 0,
      n = static_cast<unsigned int>(this->sensor_size()); i < n; i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      InternalWriteMessageNoVirtualToArray(
        1, this->sensor(static_cast<int>(i)), deterministic, target);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:external.client.sensor.Response)
  return target;
}

size_t Response::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:external.client.sensor.Response)
  size_t total_size = 0;

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()));
  }
  // repeated .external.client.Sensor sensor = 1;
  {
    unsigned int count = static_cast<unsigned int>(this->sensor_size());
    total_size += 1UL * count;
    for (unsigned int i = 0; i < count; i++) {
      total_size +=
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->sensor(static_cast<int>(i)));
    }
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void Response::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:external.client.sensor.Response)
  GOOGLE_DCHECK_NE(&from, this);
  const Response* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const Response>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:external.client.sensor.Response)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:external.client.sensor.Response)
    MergeFrom(*source);
  }
}

void Response::MergeFrom(const Response& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:external.client.sensor.Response)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  sensor_.MergeFrom(from.sensor_);
}

void Response::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:external.client.sensor.Response)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Response::CopyFrom(const Response& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:external.client.sensor.Response)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Response::IsInitialized() const {
  return true;
}

void Response::Swap(Response* other) {
  if (other == this) return;
  InternalSwap(other);
}
void Response::InternalSwap(Response* other) {
  using std::swap;
  sensor_.InternalSwap(&other->sensor_);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata Response::GetMetadata() const {
  protobuf_client_5fmsg_2fsensor_2fsensor_5fquery_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_client_5fmsg_2fsensor_2fsensor_5fquery_2eproto::file_level_metadata[kIndexInFileMessages];
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// Response

// repeated .external.client.Sensor sensor = 1;
int Response::sensor_size() const {
  return sensor_.size();
}
void Response::clear_sensor() {
  sensor_.Clear();
}
const ::external::client::Sensor& Response::sensor(int index) const {
  // @@protoc_insertion_point(field_get:external.client.sensor.Response.sensor)
  return sensor_.Get(index);
}
::external::client::Sensor* Response::mutable_sensor(int index) {
  // @@protoc_insertion_point(field_mutable:external.client.sensor.Response.sensor)
  return sensor_.Mutable(index);
}
::external::client::Sensor* Response::add_sensor() {
  // @@protoc_insertion_point(field_add:external.client.sensor.Response.sensor)
  return sensor_.Add();
}
::google::protobuf::RepeatedPtrField< ::external::client::Sensor >*
Response::mutable_sensor() {
  // @@protoc_insertion_point(field_mutable_list:external.client.sensor.Response.sensor)
  return &sensor_;
}
const ::google::protobuf::RepeatedPtrField< ::external::client::Sensor >&
Response::sensor() const {
  // @@protoc_insertion_point(field_list:external.client.sensor.Response.sensor)
  return sensor_;
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace sensor
}  // namespace client
}  // namespace external

// @@protoc_insertion_point(global_scope)
