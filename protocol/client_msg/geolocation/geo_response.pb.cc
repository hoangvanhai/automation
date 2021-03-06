// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: client_msg/geolocation/geo_response.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "client_msg/geolocation/geo_response.pb.h"

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
namespace geolocation {
class ResponseDefaultTypeInternal {
public:
 ::google::protobuf::internal::ExplicitlyConstructed<Response>
     _instance;
} _Response_default_instance_;

namespace protobuf_client_5fmsg_2fgeolocation_2fgeo_5fresponse_2eproto {


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
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Response, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Response, signal_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Response, error_),
};
static const ::google::protobuf::internal::MigrationSchema schemas[] GOOGLE_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(Response)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&_Response_default_instance_),
};

namespace {

void protobuf_AssignDescriptors() {
  AddDescriptors();
  ::google::protobuf::MessageFactory* factory = NULL;
  AssignDescriptors(
      "client_msg/geolocation/geo_response.proto", schemas, file_default_instances, TableStruct::offsets, factory,
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
  ::external::client::protobuf_client_5fmsg_2fcommon_2eproto::InitDefaults();
  _Response_default_instance_._instance.DefaultConstruct();
  ::google::protobuf::internal::OnShutdownDestroyMessage(
      &_Response_default_instance_);_Response_default_instance_._instance.get_mutable()->signal_ = const_cast< ::external::client::Signal*>(
      ::external::client::Signal::internal_default_instance());
  _Response_default_instance_._instance.get_mutable()->error_ = const_cast< ::external::client::Error*>(
      ::external::client::Error::internal_default_instance());
}

void InitDefaults() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &TableStruct::InitDefaultsImpl);
}
namespace {
void AddDescriptorsImpl() {
  InitDefaults();
  static const char descriptor[] GOOGLE_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
      "\n)client_msg/geolocation/geo_response.pr"
      "oto\022\033external.client.geolocation\032\027client"
      "_msg/common.proto\"Z\n\010Response\022\'\n\006signal\030"
      "\001 \001(\0132\027.external.client.Signal\022%\n\005error\030"
      "\002 \001(\0132\026.external.client.Errorb\006proto3"
  };
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
      descriptor, 197);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "client_msg/geolocation/geo_response.proto", &protobuf_RegisterTypes);
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

}  // namespace protobuf_client_5fmsg_2fgeolocation_2fgeo_5fresponse_2eproto


// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int Response::kSignalFieldNumber;
const int Response::kErrorFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

Response::Response()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (GOOGLE_PREDICT_TRUE(this != internal_default_instance())) {
    protobuf_client_5fmsg_2fgeolocation_2fgeo_5fresponse_2eproto::InitDefaults();
  }
  SharedCtor();
  // @@protoc_insertion_point(constructor:external.client.geolocation.Response)
}
Response::Response(const Response& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      _cached_size_(0) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  if (from.has_signal()) {
    signal_ = new ::external::client::Signal(*from.signal_);
  } else {
    signal_ = NULL;
  }
  if (from.has_error()) {
    error_ = new ::external::client::Error(*from.error_);
  } else {
    error_ = NULL;
  }
  // @@protoc_insertion_point(copy_constructor:external.client.geolocation.Response)
}

void Response::SharedCtor() {
  ::memset(&signal_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&error_) -
      reinterpret_cast<char*>(&signal_)) + sizeof(error_));
  _cached_size_ = 0;
}

Response::~Response() {
  // @@protoc_insertion_point(destructor:external.client.geolocation.Response)
  SharedDtor();
}

void Response::SharedDtor() {
  if (this != internal_default_instance()) delete signal_;
  if (this != internal_default_instance()) delete error_;
}

void Response::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Response::descriptor() {
  protobuf_client_5fmsg_2fgeolocation_2fgeo_5fresponse_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_client_5fmsg_2fgeolocation_2fgeo_5fresponse_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const Response& Response::default_instance() {
  protobuf_client_5fmsg_2fgeolocation_2fgeo_5fresponse_2eproto::InitDefaults();
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
// @@protoc_insertion_point(message_clear_start:external.client.geolocation.Response)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  if (GetArenaNoVirtual() == NULL && signal_ != NULL) {
    delete signal_;
  }
  signal_ = NULL;
  if (GetArenaNoVirtual() == NULL && error_ != NULL) {
    delete error_;
  }
  error_ = NULL;
  _internal_metadata_.Clear();
}

bool Response::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:external.client.geolocation.Response)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // .external.client.Signal signal = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(10u /* 10 & 0xFF */)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_signal()));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // .external.client.Error error = 2;
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(18u /* 18 & 0xFF */)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_error()));
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
  // @@protoc_insertion_point(parse_success:external.client.geolocation.Response)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:external.client.geolocation.Response)
  return false;
#undef DO_
}

void Response::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:external.client.geolocation.Response)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // .external.client.Signal signal = 1;
  if (this->has_signal()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, *this->signal_, output);
  }

  // .external.client.Error error = 2;
  if (this->has_error()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      2, *this->error_, output);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), output);
  }
  // @@protoc_insertion_point(serialize_end:external.client.geolocation.Response)
}

::google::protobuf::uint8* Response::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:external.client.geolocation.Response)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // .external.client.Signal signal = 1;
  if (this->has_signal()) {
    target = ::google::protobuf::internal::WireFormatLite::
      InternalWriteMessageNoVirtualToArray(
        1, *this->signal_, deterministic, target);
  }

  // .external.client.Error error = 2;
  if (this->has_error()) {
    target = ::google::protobuf::internal::WireFormatLite::
      InternalWriteMessageNoVirtualToArray(
        2, *this->error_, deterministic, target);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:external.client.geolocation.Response)
  return target;
}

size_t Response::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:external.client.geolocation.Response)
  size_t total_size = 0;

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()));
  }
  // .external.client.Signal signal = 1;
  if (this->has_signal()) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        *this->signal_);
  }

  // .external.client.Error error = 2;
  if (this->has_error()) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        *this->error_);
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void Response::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:external.client.geolocation.Response)
  GOOGLE_DCHECK_NE(&from, this);
  const Response* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const Response>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:external.client.geolocation.Response)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:external.client.geolocation.Response)
    MergeFrom(*source);
  }
}

void Response::MergeFrom(const Response& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:external.client.geolocation.Response)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.has_signal()) {
    mutable_signal()->::external::client::Signal::MergeFrom(from.signal());
  }
  if (from.has_error()) {
    mutable_error()->::external::client::Error::MergeFrom(from.error());
  }
}

void Response::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:external.client.geolocation.Response)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Response::CopyFrom(const Response& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:external.client.geolocation.Response)
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
  swap(signal_, other->signal_);
  swap(error_, other->error_);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata Response::GetMetadata() const {
  protobuf_client_5fmsg_2fgeolocation_2fgeo_5fresponse_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_client_5fmsg_2fgeolocation_2fgeo_5fresponse_2eproto::file_level_metadata[kIndexInFileMessages];
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// Response

// .external.client.Signal signal = 1;
bool Response::has_signal() const {
  return this != internal_default_instance() && signal_ != NULL;
}
void Response::clear_signal() {
  if (GetArenaNoVirtual() == NULL && signal_ != NULL) delete signal_;
  signal_ = NULL;
}
const ::external::client::Signal& Response::signal() const {
  const ::external::client::Signal* p = signal_;
  // @@protoc_insertion_point(field_get:external.client.geolocation.Response.signal)
  return p != NULL ? *p : *reinterpret_cast<const ::external::client::Signal*>(
      &::external::client::_Signal_default_instance_);
}
::external::client::Signal* Response::mutable_signal() {
  
  if (signal_ == NULL) {
    signal_ = new ::external::client::Signal;
  }
  // @@protoc_insertion_point(field_mutable:external.client.geolocation.Response.signal)
  return signal_;
}
::external::client::Signal* Response::release_signal() {
  // @@protoc_insertion_point(field_release:external.client.geolocation.Response.signal)
  
  ::external::client::Signal* temp = signal_;
  signal_ = NULL;
  return temp;
}
void Response::set_allocated_signal(::external::client::Signal* signal) {
  delete signal_;
  signal_ = signal;
  if (signal) {
    
  } else {
    
  }
  // @@protoc_insertion_point(field_set_allocated:external.client.geolocation.Response.signal)
}

// .external.client.Error error = 2;
bool Response::has_error() const {
  return this != internal_default_instance() && error_ != NULL;
}
void Response::clear_error() {
  if (GetArenaNoVirtual() == NULL && error_ != NULL) delete error_;
  error_ = NULL;
}
const ::external::client::Error& Response::error() const {
  const ::external::client::Error* p = error_;
  // @@protoc_insertion_point(field_get:external.client.geolocation.Response.error)
  return p != NULL ? *p : *reinterpret_cast<const ::external::client::Error*>(
      &::external::client::_Error_default_instance_);
}
::external::client::Error* Response::mutable_error() {
  
  if (error_ == NULL) {
    error_ = new ::external::client::Error;
  }
  // @@protoc_insertion_point(field_mutable:external.client.geolocation.Response.error)
  return error_;
}
::external::client::Error* Response::release_error() {
  // @@protoc_insertion_point(field_release:external.client.geolocation.Response.error)
  
  ::external::client::Error* temp = error_;
  error_ = NULL;
  return temp;
}
void Response::set_allocated_error(::external::client::Error* error) {
  delete error_;
  error_ = error;
  if (error) {
    
  } else {
    
  }
  // @@protoc_insertion_point(field_set_allocated:external.client.geolocation.Response.error)
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace geolocation
}  // namespace client
}  // namespace external

// @@protoc_insertion_point(global_scope)
