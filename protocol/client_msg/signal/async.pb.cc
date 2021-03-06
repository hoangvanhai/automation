// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: client_msg/signal/async.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "client_msg/signal/async.pb.h"

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
namespace signal {
class AsyncDefaultTypeInternal {
public:
 ::google::protobuf::internal::ExplicitlyConstructed<Async>
     _instance;
} _Async_default_instance_;

namespace protobuf_client_5fmsg_2fsignal_2fasync_2eproto {


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
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Async, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Async, signal_),
};
static const ::google::protobuf::internal::MigrationSchema schemas[] GOOGLE_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(Async)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&_Async_default_instance_),
};

namespace {

void protobuf_AssignDescriptors() {
  AddDescriptors();
  ::google::protobuf::MessageFactory* factory = NULL;
  AssignDescriptors(
      "client_msg/signal/async.proto", schemas, file_default_instances, TableStruct::offsets, factory,
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
  _Async_default_instance_._instance.DefaultConstruct();
  ::google::protobuf::internal::OnShutdownDestroyMessage(
      &_Async_default_instance_);}

void InitDefaults() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &TableStruct::InitDefaultsImpl);
}
namespace {
void AddDescriptorsImpl() {
  InitDefaults();
  static const char descriptor[] GOOGLE_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
      "\n\035client_msg/signal/async.proto\022\026externa"
      "l.client.signal\032\027client_msg/common.proto"
      "\"0\n\005Async\022\'\n\006signal\030\001 \003(\0132\027.external.cli"
      "ent.Signalb\006proto3"
  };
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
      descriptor, 138);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "client_msg/signal/async.proto", &protobuf_RegisterTypes);
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

}  // namespace protobuf_client_5fmsg_2fsignal_2fasync_2eproto


// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int Async::kSignalFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

Async::Async()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (GOOGLE_PREDICT_TRUE(this != internal_default_instance())) {
    protobuf_client_5fmsg_2fsignal_2fasync_2eproto::InitDefaults();
  }
  SharedCtor();
  // @@protoc_insertion_point(constructor:external.client.signal.Async)
}
Async::Async(const Async& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      signal_(from.signal_),
      _cached_size_(0) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  // @@protoc_insertion_point(copy_constructor:external.client.signal.Async)
}

void Async::SharedCtor() {
  _cached_size_ = 0;
}

Async::~Async() {
  // @@protoc_insertion_point(destructor:external.client.signal.Async)
  SharedDtor();
}

void Async::SharedDtor() {
}

void Async::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Async::descriptor() {
  protobuf_client_5fmsg_2fsignal_2fasync_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_client_5fmsg_2fsignal_2fasync_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const Async& Async::default_instance() {
  protobuf_client_5fmsg_2fsignal_2fasync_2eproto::InitDefaults();
  return *internal_default_instance();
}

Async* Async::New(::google::protobuf::Arena* arena) const {
  Async* n = new Async;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void Async::Clear() {
// @@protoc_insertion_point(message_clear_start:external.client.signal.Async)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  signal_.Clear();
  _internal_metadata_.Clear();
}

bool Async::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:external.client.signal.Async)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .external.client.Signal signal = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(10u /* 10 & 0xFF */)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_signal()));
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
  // @@protoc_insertion_point(parse_success:external.client.signal.Async)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:external.client.signal.Async)
  return false;
#undef DO_
}

void Async::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:external.client.signal.Async)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // repeated .external.client.Signal signal = 1;
  for (unsigned int i = 0,
      n = static_cast<unsigned int>(this->signal_size()); i < n; i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->signal(static_cast<int>(i)), output);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), output);
  }
  // @@protoc_insertion_point(serialize_end:external.client.signal.Async)
}

::google::protobuf::uint8* Async::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:external.client.signal.Async)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // repeated .external.client.Signal signal = 1;
  for (unsigned int i = 0,
      n = static_cast<unsigned int>(this->signal_size()); i < n; i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      InternalWriteMessageNoVirtualToArray(
        1, this->signal(static_cast<int>(i)), deterministic, target);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:external.client.signal.Async)
  return target;
}

size_t Async::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:external.client.signal.Async)
  size_t total_size = 0;

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()));
  }
  // repeated .external.client.Signal signal = 1;
  {
    unsigned int count = static_cast<unsigned int>(this->signal_size());
    total_size += 1UL * count;
    for (unsigned int i = 0; i < count; i++) {
      total_size +=
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->signal(static_cast<int>(i)));
    }
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void Async::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:external.client.signal.Async)
  GOOGLE_DCHECK_NE(&from, this);
  const Async* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const Async>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:external.client.signal.Async)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:external.client.signal.Async)
    MergeFrom(*source);
  }
}

void Async::MergeFrom(const Async& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:external.client.signal.Async)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  signal_.MergeFrom(from.signal_);
}

void Async::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:external.client.signal.Async)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Async::CopyFrom(const Async& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:external.client.signal.Async)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Async::IsInitialized() const {
  return true;
}

void Async::Swap(Async* other) {
  if (other == this) return;
  InternalSwap(other);
}
void Async::InternalSwap(Async* other) {
  using std::swap;
  signal_.InternalSwap(&other->signal_);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata Async::GetMetadata() const {
  protobuf_client_5fmsg_2fsignal_2fasync_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_client_5fmsg_2fsignal_2fasync_2eproto::file_level_metadata[kIndexInFileMessages];
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// Async

// repeated .external.client.Signal signal = 1;
int Async::signal_size() const {
  return signal_.size();
}
void Async::clear_signal() {
  signal_.Clear();
}
const ::external::client::Signal& Async::signal(int index) const {
  // @@protoc_insertion_point(field_get:external.client.signal.Async.signal)
  return signal_.Get(index);
}
::external::client::Signal* Async::mutable_signal(int index) {
  // @@protoc_insertion_point(field_mutable:external.client.signal.Async.signal)
  return signal_.Mutable(index);
}
::external::client::Signal* Async::add_signal() {
  // @@protoc_insertion_point(field_add:external.client.signal.Async.signal)
  return signal_.Add();
}
::google::protobuf::RepeatedPtrField< ::external::client::Signal >*
Async::mutable_signal() {
  // @@protoc_insertion_point(field_mutable_list:external.client.signal.Async.signal)
  return &signal_;
}
const ::google::protobuf::RepeatedPtrField< ::external::client::Signal >&
Async::signal() const {
  // @@protoc_insertion_point(field_list:external.client.signal.Async.signal)
  return signal_;
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace signal
}  // namespace client
}  // namespace external

// @@protoc_insertion_point(global_scope)
