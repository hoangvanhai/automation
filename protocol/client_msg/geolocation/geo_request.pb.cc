// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: client_msg/geolocation/geo_request.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "client_msg/geolocation/geo_request.pb.h"

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
class RequestDefaultTypeInternal {
public:
 ::google::protobuf::internal::ExplicitlyConstructed<Request>
     _instance;
} _Request_default_instance_;

namespace protobuf_client_5fmsg_2fgeolocation_2fgeo_5frequest_2eproto {


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
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Request, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Request, signal_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Request, mode_),
};
static const ::google::protobuf::internal::MigrationSchema schemas[] GOOGLE_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(Request)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&_Request_default_instance_),
};

namespace {

void protobuf_AssignDescriptors() {
  AddDescriptors();
  ::google::protobuf::MessageFactory* factory = NULL;
  AssignDescriptors(
      "client_msg/geolocation/geo_request.proto", schemas, file_default_instances, TableStruct::offsets, factory,
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
  ::external::client::protobuf_client_5fmsg_2fcommon_2eproto::InitDefaults();
  _Request_default_instance_._instance.DefaultConstruct();
  ::google::protobuf::internal::OnShutdownDestroyMessage(
      &_Request_default_instance_);_Request_default_instance_._instance.get_mutable()->signal_ = const_cast< ::external::client::Signal*>(
      ::external::client::Signal::internal_default_instance());
}

void InitDefaults() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &TableStruct::InitDefaultsImpl);
}
namespace {
void AddDescriptorsImpl() {
  InitDefaults();
  static const char descriptor[] GOOGLE_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
      "\n(client_msg/geolocation/geo_request.pro"
      "to\022\033external.client.geolocation\032\027client_"
      "msg/common.proto\"\223\001\n\007Request\022\'\n\006signal\030\001"
      " \001(\0132\027.external.client.Signal\0227\n\004mode\030\002 "
      "\001(\0162).external.client.geolocation.Reques"
      "t.Mode\"&\n\004Mode\022\010\n\004FAST\020\000\022\024\n\020HIGH_PERFORM"
      "ANCE\020\001b\006proto3"
  };
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
      descriptor, 254);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "client_msg/geolocation/geo_request.proto", &protobuf_RegisterTypes);
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

}  // namespace protobuf_client_5fmsg_2fgeolocation_2fgeo_5frequest_2eproto

const ::google::protobuf::EnumDescriptor* Request_Mode_descriptor() {
  protobuf_client_5fmsg_2fgeolocation_2fgeo_5frequest_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_client_5fmsg_2fgeolocation_2fgeo_5frequest_2eproto::file_level_enum_descriptors[0];
}
bool Request_Mode_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
      return true;
    default:
      return false;
  }
}

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const Request_Mode Request::FAST;
const Request_Mode Request::HIGH_PERFORMANCE;
const Request_Mode Request::Mode_MIN;
const Request_Mode Request::Mode_MAX;
const int Request::Mode_ARRAYSIZE;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int Request::kSignalFieldNumber;
const int Request::kModeFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

Request::Request()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (GOOGLE_PREDICT_TRUE(this != internal_default_instance())) {
    protobuf_client_5fmsg_2fgeolocation_2fgeo_5frequest_2eproto::InitDefaults();
  }
  SharedCtor();
  // @@protoc_insertion_point(constructor:external.client.geolocation.Request)
}
Request::Request(const Request& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      _cached_size_(0) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  if (from.has_signal()) {
    signal_ = new ::external::client::Signal(*from.signal_);
  } else {
    signal_ = NULL;
  }
  mode_ = from.mode_;
  // @@protoc_insertion_point(copy_constructor:external.client.geolocation.Request)
}

void Request::SharedCtor() {
  ::memset(&signal_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&mode_) -
      reinterpret_cast<char*>(&signal_)) + sizeof(mode_));
  _cached_size_ = 0;
}

Request::~Request() {
  // @@protoc_insertion_point(destructor:external.client.geolocation.Request)
  SharedDtor();
}

void Request::SharedDtor() {
  if (this != internal_default_instance()) delete signal_;
}

void Request::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Request::descriptor() {
  protobuf_client_5fmsg_2fgeolocation_2fgeo_5frequest_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_client_5fmsg_2fgeolocation_2fgeo_5frequest_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const Request& Request::default_instance() {
  protobuf_client_5fmsg_2fgeolocation_2fgeo_5frequest_2eproto::InitDefaults();
  return *internal_default_instance();
}

Request* Request::New(::google::protobuf::Arena* arena) const {
  Request* n = new Request;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void Request::Clear() {
// @@protoc_insertion_point(message_clear_start:external.client.geolocation.Request)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  if (GetArenaNoVirtual() == NULL && signal_ != NULL) {
    delete signal_;
  }
  signal_ = NULL;
  mode_ = 0;
  _internal_metadata_.Clear();
}

bool Request::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:external.client.geolocation.Request)
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

      // .external.client.geolocation.Request.Mode mode = 2;
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(16u /* 16 & 0xFF */)) {
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          set_mode(static_cast< ::external::client::geolocation::Request_Mode >(value));
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
  // @@protoc_insertion_point(parse_success:external.client.geolocation.Request)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:external.client.geolocation.Request)
  return false;
#undef DO_
}

void Request::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:external.client.geolocation.Request)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // .external.client.Signal signal = 1;
  if (this->has_signal()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, *this->signal_, output);
  }

  // .external.client.geolocation.Request.Mode mode = 2;
  if (this->mode() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      2, this->mode(), output);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), output);
  }
  // @@protoc_insertion_point(serialize_end:external.client.geolocation.Request)
}

::google::protobuf::uint8* Request::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:external.client.geolocation.Request)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // .external.client.Signal signal = 1;
  if (this->has_signal()) {
    target = ::google::protobuf::internal::WireFormatLite::
      InternalWriteMessageNoVirtualToArray(
        1, *this->signal_, deterministic, target);
  }

  // .external.client.geolocation.Request.Mode mode = 2;
  if (this->mode() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      2, this->mode(), target);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:external.client.geolocation.Request)
  return target;
}

size_t Request::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:external.client.geolocation.Request)
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

  // .external.client.geolocation.Request.Mode mode = 2;
  if (this->mode() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::EnumSize(this->mode());
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void Request::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:external.client.geolocation.Request)
  GOOGLE_DCHECK_NE(&from, this);
  const Request* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const Request>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:external.client.geolocation.Request)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:external.client.geolocation.Request)
    MergeFrom(*source);
  }
}

void Request::MergeFrom(const Request& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:external.client.geolocation.Request)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.has_signal()) {
    mutable_signal()->::external::client::Signal::MergeFrom(from.signal());
  }
  if (from.mode() != 0) {
    set_mode(from.mode());
  }
}

void Request::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:external.client.geolocation.Request)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Request::CopyFrom(const Request& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:external.client.geolocation.Request)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Request::IsInitialized() const {
  return true;
}

void Request::Swap(Request* other) {
  if (other == this) return;
  InternalSwap(other);
}
void Request::InternalSwap(Request* other) {
  using std::swap;
  swap(signal_, other->signal_);
  swap(mode_, other->mode_);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata Request::GetMetadata() const {
  protobuf_client_5fmsg_2fgeolocation_2fgeo_5frequest_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_client_5fmsg_2fgeolocation_2fgeo_5frequest_2eproto::file_level_metadata[kIndexInFileMessages];
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// Request

// .external.client.Signal signal = 1;
bool Request::has_signal() const {
  return this != internal_default_instance() && signal_ != NULL;
}
void Request::clear_signal() {
  if (GetArenaNoVirtual() == NULL && signal_ != NULL) delete signal_;
  signal_ = NULL;
}
const ::external::client::Signal& Request::signal() const {
  const ::external::client::Signal* p = signal_;
  // @@protoc_insertion_point(field_get:external.client.geolocation.Request.signal)
  return p != NULL ? *p : *reinterpret_cast<const ::external::client::Signal*>(
      &::external::client::_Signal_default_instance_);
}
::external::client::Signal* Request::mutable_signal() {
  
  if (signal_ == NULL) {
    signal_ = new ::external::client::Signal;
  }
  // @@protoc_insertion_point(field_mutable:external.client.geolocation.Request.signal)
  return signal_;
}
::external::client::Signal* Request::release_signal() {
  // @@protoc_insertion_point(field_release:external.client.geolocation.Request.signal)
  
  ::external::client::Signal* temp = signal_;
  signal_ = NULL;
  return temp;
}
void Request::set_allocated_signal(::external::client::Signal* signal) {
  delete signal_;
  signal_ = signal;
  if (signal) {
    
  } else {
    
  }
  // @@protoc_insertion_point(field_set_allocated:external.client.geolocation.Request.signal)
}

// .external.client.geolocation.Request.Mode mode = 2;
void Request::clear_mode() {
  mode_ = 0;
}
::external::client::geolocation::Request_Mode Request::mode() const {
  // @@protoc_insertion_point(field_get:external.client.geolocation.Request.mode)
  return static_cast< ::external::client::geolocation::Request_Mode >(mode_);
}
void Request::set_mode(::external::client::geolocation::Request_Mode value) {
  
  mode_ = value;
  // @@protoc_insertion_point(field_set:external.client.geolocation.Request.mode)
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace geolocation
}  // namespace client
}  // namespace external

// @@protoc_insertion_point(global_scope)
