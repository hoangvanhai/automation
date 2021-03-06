// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: client_msg/server/turnoff.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "client_msg/server/turnoff.pb.h"

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
namespace server {
class TurnOffDefaultTypeInternal {
public:
 ::google::protobuf::internal::ExplicitlyConstructed<TurnOff>
     _instance;
} _TurnOff_default_instance_;

namespace protobuf_client_5fmsg_2fserver_2fturnoff_2eproto {


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
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TurnOff, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TurnOff, username_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TurnOff, secret_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TurnOff, timeout_),
};
static const ::google::protobuf::internal::MigrationSchema schemas[] GOOGLE_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(TurnOff)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&_TurnOff_default_instance_),
};

namespace {

void protobuf_AssignDescriptors() {
  AddDescriptors();
  ::google::protobuf::MessageFactory* factory = NULL;
  AssignDescriptors(
      "client_msg/server/turnoff.proto", schemas, file_default_instances, TableStruct::offsets, factory,
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
  _TurnOff_default_instance_._instance.DefaultConstruct();
  ::google::protobuf::internal::OnShutdownDestroyMessage(
      &_TurnOff_default_instance_);}

void InitDefaults() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &TableStruct::InitDefaultsImpl);
}
namespace {
void AddDescriptorsImpl() {
  InitDefaults();
  static const char descriptor[] GOOGLE_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
      "\n\037client_msg/server/turnoff.proto\022\026exter"
      "nal.client.server\"<\n\007TurnOff\022\020\n\010username"
      "\030\001 \001(\t\022\016\n\006secret\030\002 \001(\t\022\017\n\007timeout\030\003 \001(\rb"
      "\006proto3"
  };
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
      descriptor, 127);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "client_msg/server/turnoff.proto", &protobuf_RegisterTypes);
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

}  // namespace protobuf_client_5fmsg_2fserver_2fturnoff_2eproto


// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int TurnOff::kUsernameFieldNumber;
const int TurnOff::kSecretFieldNumber;
const int TurnOff::kTimeoutFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

TurnOff::TurnOff()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (GOOGLE_PREDICT_TRUE(this != internal_default_instance())) {
    protobuf_client_5fmsg_2fserver_2fturnoff_2eproto::InitDefaults();
  }
  SharedCtor();
  // @@protoc_insertion_point(constructor:external.client.server.TurnOff)
}
TurnOff::TurnOff(const TurnOff& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      _cached_size_(0) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  username_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (from.username().size() > 0) {
    username_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.username_);
  }
  secret_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (from.secret().size() > 0) {
    secret_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.secret_);
  }
  timeout_ = from.timeout_;
  // @@protoc_insertion_point(copy_constructor:external.client.server.TurnOff)
}

void TurnOff::SharedCtor() {
  username_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  secret_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  timeout_ = 0u;
  _cached_size_ = 0;
}

TurnOff::~TurnOff() {
  // @@protoc_insertion_point(destructor:external.client.server.TurnOff)
  SharedDtor();
}

void TurnOff::SharedDtor() {
  username_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  secret_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

void TurnOff::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* TurnOff::descriptor() {
  protobuf_client_5fmsg_2fserver_2fturnoff_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_client_5fmsg_2fserver_2fturnoff_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const TurnOff& TurnOff::default_instance() {
  protobuf_client_5fmsg_2fserver_2fturnoff_2eproto::InitDefaults();
  return *internal_default_instance();
}

TurnOff* TurnOff::New(::google::protobuf::Arena* arena) const {
  TurnOff* n = new TurnOff;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void TurnOff::Clear() {
// @@protoc_insertion_point(message_clear_start:external.client.server.TurnOff)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  username_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  secret_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  timeout_ = 0u;
  _internal_metadata_.Clear();
}

bool TurnOff::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:external.client.server.TurnOff)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // string username = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(10u /* 10 & 0xFF */)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_username()));
          DO_(::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
            this->username().data(), static_cast<int>(this->username().length()),
            ::google::protobuf::internal::WireFormatLite::PARSE,
            "external.client.server.TurnOff.username"));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // string secret = 2;
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(18u /* 18 & 0xFF */)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_secret()));
          DO_(::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
            this->secret().data(), static_cast<int>(this->secret().length()),
            ::google::protobuf::internal::WireFormatLite::PARSE,
            "external.client.server.TurnOff.secret"));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // uint32 timeout = 3;
      case 3: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(24u /* 24 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &timeout_)));
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
  // @@protoc_insertion_point(parse_success:external.client.server.TurnOff)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:external.client.server.TurnOff)
  return false;
#undef DO_
}

void TurnOff::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:external.client.server.TurnOff)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // string username = 1;
  if (this->username().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->username().data(), static_cast<int>(this->username().length()),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "external.client.server.TurnOff.username");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->username(), output);
  }

  // string secret = 2;
  if (this->secret().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->secret().data(), static_cast<int>(this->secret().length()),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "external.client.server.TurnOff.secret");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      2, this->secret(), output);
  }

  // uint32 timeout = 3;
  if (this->timeout() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(3, this->timeout(), output);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), output);
  }
  // @@protoc_insertion_point(serialize_end:external.client.server.TurnOff)
}

::google::protobuf::uint8* TurnOff::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:external.client.server.TurnOff)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // string username = 1;
  if (this->username().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->username().data(), static_cast<int>(this->username().length()),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "external.client.server.TurnOff.username");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->username(), target);
  }

  // string secret = 2;
  if (this->secret().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->secret().data(), static_cast<int>(this->secret().length()),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "external.client.server.TurnOff.secret");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->secret(), target);
  }

  // uint32 timeout = 3;
  if (this->timeout() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(3, this->timeout(), target);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:external.client.server.TurnOff)
  return target;
}

size_t TurnOff::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:external.client.server.TurnOff)
  size_t total_size = 0;

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()));
  }
  // string username = 1;
  if (this->username().size() > 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->username());
  }

  // string secret = 2;
  if (this->secret().size() > 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->secret());
  }

  // uint32 timeout = 3;
  if (this->timeout() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::UInt32Size(
        this->timeout());
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void TurnOff::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:external.client.server.TurnOff)
  GOOGLE_DCHECK_NE(&from, this);
  const TurnOff* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const TurnOff>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:external.client.server.TurnOff)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:external.client.server.TurnOff)
    MergeFrom(*source);
  }
}

void TurnOff::MergeFrom(const TurnOff& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:external.client.server.TurnOff)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.username().size() > 0) {

    username_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.username_);
  }
  if (from.secret().size() > 0) {

    secret_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.secret_);
  }
  if (from.timeout() != 0) {
    set_timeout(from.timeout());
  }
}

void TurnOff::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:external.client.server.TurnOff)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void TurnOff::CopyFrom(const TurnOff& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:external.client.server.TurnOff)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool TurnOff::IsInitialized() const {
  return true;
}

void TurnOff::Swap(TurnOff* other) {
  if (other == this) return;
  InternalSwap(other);
}
void TurnOff::InternalSwap(TurnOff* other) {
  using std::swap;
  username_.Swap(&other->username_);
  secret_.Swap(&other->secret_);
  swap(timeout_, other->timeout_);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata TurnOff::GetMetadata() const {
  protobuf_client_5fmsg_2fserver_2fturnoff_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_client_5fmsg_2fserver_2fturnoff_2eproto::file_level_metadata[kIndexInFileMessages];
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// TurnOff

// string username = 1;
void TurnOff::clear_username() {
  username_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
const ::std::string& TurnOff::username() const {
  // @@protoc_insertion_point(field_get:external.client.server.TurnOff.username)
  return username_.GetNoArena();
}
void TurnOff::set_username(const ::std::string& value) {
  
  username_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:external.client.server.TurnOff.username)
}
#if LANG_CXX11
void TurnOff::set_username(::std::string&& value) {
  
  username_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:external.client.server.TurnOff.username)
}
#endif
void TurnOff::set_username(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  username_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:external.client.server.TurnOff.username)
}
void TurnOff::set_username(const char* value, size_t size) {
  
  username_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:external.client.server.TurnOff.username)
}
::std::string* TurnOff::mutable_username() {
  
  // @@protoc_insertion_point(field_mutable:external.client.server.TurnOff.username)
  return username_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
::std::string* TurnOff::release_username() {
  // @@protoc_insertion_point(field_release:external.client.server.TurnOff.username)
  
  return username_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
void TurnOff::set_allocated_username(::std::string* username) {
  if (username != NULL) {
    
  } else {
    
  }
  username_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), username);
  // @@protoc_insertion_point(field_set_allocated:external.client.server.TurnOff.username)
}

// string secret = 2;
void TurnOff::clear_secret() {
  secret_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
const ::std::string& TurnOff::secret() const {
  // @@protoc_insertion_point(field_get:external.client.server.TurnOff.secret)
  return secret_.GetNoArena();
}
void TurnOff::set_secret(const ::std::string& value) {
  
  secret_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:external.client.server.TurnOff.secret)
}
#if LANG_CXX11
void TurnOff::set_secret(::std::string&& value) {
  
  secret_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:external.client.server.TurnOff.secret)
}
#endif
void TurnOff::set_secret(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  secret_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:external.client.server.TurnOff.secret)
}
void TurnOff::set_secret(const char* value, size_t size) {
  
  secret_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:external.client.server.TurnOff.secret)
}
::std::string* TurnOff::mutable_secret() {
  
  // @@protoc_insertion_point(field_mutable:external.client.server.TurnOff.secret)
  return secret_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
::std::string* TurnOff::release_secret() {
  // @@protoc_insertion_point(field_release:external.client.server.TurnOff.secret)
  
  return secret_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
void TurnOff::set_allocated_secret(::std::string* secret) {
  if (secret != NULL) {
    
  } else {
    
  }
  secret_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), secret);
  // @@protoc_insertion_point(field_set_allocated:external.client.server.TurnOff.secret)
}

// uint32 timeout = 3;
void TurnOff::clear_timeout() {
  timeout_ = 0u;
}
::google::protobuf::uint32 TurnOff::timeout() const {
  // @@protoc_insertion_point(field_get:external.client.server.TurnOff.timeout)
  return timeout_;
}
void TurnOff::set_timeout(::google::protobuf::uint32 value) {
  
  timeout_ = value;
  // @@protoc_insertion_point(field_set:external.client.server.TurnOff.timeout)
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace server
}  // namespace client
}  // namespace external

// @@protoc_insertion_point(global_scope)
