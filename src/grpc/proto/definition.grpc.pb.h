// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: definition.proto
#ifndef GRPC_definition_2eproto__INCLUDED
#define GRPC_definition_2eproto__INCLUDED

#include "definition.pb.h"

#include <functional>
#include <grpc/impl/codegen/port_platform.h>
#include <grpcpp/impl/codegen/async_generic_service.h>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/client_context.h>
#include <grpcpp/impl/codegen/completion_queue.h>
#include <grpcpp/impl/codegen/message_allocator.h>
#include <grpcpp/impl/codegen/method_handler.h>
#include <grpcpp/impl/codegen/proto_utils.h>
#include <grpcpp/impl/codegen/rpc_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/status.h>
#include <grpcpp/impl/codegen/stub_options.h>
#include <grpcpp/impl/codegen/sync_stream.h>

namespace eventstream {

class EventStream final {
 public:
  static constexpr char const* service_full_name() {
    return "eventstream.EventStream";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    std::unique_ptr< ::grpc::ClientReaderInterface< ::eventstream::Event>> Listen(::grpc::ClientContext* context, const ::eventstream::Auth& request) {
      return std::unique_ptr< ::grpc::ClientReaderInterface< ::eventstream::Event>>(ListenRaw(context, request));
    }
    std::unique_ptr< ::grpc::ClientAsyncReaderInterface< ::eventstream::Event>> AsyncListen(::grpc::ClientContext* context, const ::eventstream::Auth& request, ::grpc::CompletionQueue* cq, void* tag) {
      return std::unique_ptr< ::grpc::ClientAsyncReaderInterface< ::eventstream::Event>>(AsyncListenRaw(context, request, cq, tag));
    }
    std::unique_ptr< ::grpc::ClientAsyncReaderInterface< ::eventstream::Event>> PrepareAsyncListen(::grpc::ClientContext* context, const ::eventstream::Auth& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncReaderInterface< ::eventstream::Event>>(PrepareAsyncListenRaw(context, request, cq));
    }
    class experimental_async_interface {
     public:
      virtual ~experimental_async_interface() {}
      #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      virtual void Listen(::grpc::ClientContext* context, ::eventstream::Auth* request, ::grpc::ClientReadReactor< ::eventstream::Event>* reactor) = 0;
      #else
      virtual void Listen(::grpc::ClientContext* context, ::eventstream::Auth* request, ::grpc::experimental::ClientReadReactor< ::eventstream::Event>* reactor) = 0;
      #endif
    };
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
    typedef class experimental_async_interface async_interface;
    #endif
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
    async_interface* async() { return experimental_async(); }
    #endif
    virtual class experimental_async_interface* experimental_async() { return nullptr; }
  private:
    virtual ::grpc::ClientReaderInterface< ::eventstream::Event>* ListenRaw(::grpc::ClientContext* context, const ::eventstream::Auth& request) = 0;
    virtual ::grpc::ClientAsyncReaderInterface< ::eventstream::Event>* AsyncListenRaw(::grpc::ClientContext* context, const ::eventstream::Auth& request, ::grpc::CompletionQueue* cq, void* tag) = 0;
    virtual ::grpc::ClientAsyncReaderInterface< ::eventstream::Event>* PrepareAsyncListenRaw(::grpc::ClientContext* context, const ::eventstream::Auth& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel);
    std::unique_ptr< ::grpc::ClientReader< ::eventstream::Event>> Listen(::grpc::ClientContext* context, const ::eventstream::Auth& request) {
      return std::unique_ptr< ::grpc::ClientReader< ::eventstream::Event>>(ListenRaw(context, request));
    }
    std::unique_ptr< ::grpc::ClientAsyncReader< ::eventstream::Event>> AsyncListen(::grpc::ClientContext* context, const ::eventstream::Auth& request, ::grpc::CompletionQueue* cq, void* tag) {
      return std::unique_ptr< ::grpc::ClientAsyncReader< ::eventstream::Event>>(AsyncListenRaw(context, request, cq, tag));
    }
    std::unique_ptr< ::grpc::ClientAsyncReader< ::eventstream::Event>> PrepareAsyncListen(::grpc::ClientContext* context, const ::eventstream::Auth& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncReader< ::eventstream::Event>>(PrepareAsyncListenRaw(context, request, cq));
    }
    class experimental_async final :
      public StubInterface::experimental_async_interface {
     public:
      #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      void Listen(::grpc::ClientContext* context, ::eventstream::Auth* request, ::grpc::ClientReadReactor< ::eventstream::Event>* reactor) override;
      #else
      void Listen(::grpc::ClientContext* context, ::eventstream::Auth* request, ::grpc::experimental::ClientReadReactor< ::eventstream::Event>* reactor) override;
      #endif
     private:
      friend class Stub;
      explicit experimental_async(Stub* stub): stub_(stub) { }
      Stub* stub() { return stub_; }
      Stub* stub_;
    };
    class experimental_async_interface* experimental_async() override { return &async_stub_; }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    class experimental_async async_stub_{this};
    ::grpc::ClientReader< ::eventstream::Event>* ListenRaw(::grpc::ClientContext* context, const ::eventstream::Auth& request) override;
    ::grpc::ClientAsyncReader< ::eventstream::Event>* AsyncListenRaw(::grpc::ClientContext* context, const ::eventstream::Auth& request, ::grpc::CompletionQueue* cq, void* tag) override;
    ::grpc::ClientAsyncReader< ::eventstream::Event>* PrepareAsyncListenRaw(::grpc::ClientContext* context, const ::eventstream::Auth& request, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_Listen_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    virtual ::grpc::Status Listen(::grpc::ServerContext* context, const ::eventstream::Auth* request, ::grpc::ServerWriter< ::eventstream::Event>* writer);
  };
  template <class BaseClass>
  class WithAsyncMethod_Listen : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_Listen() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_Listen() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Listen(::grpc::ServerContext* /*context*/, const ::eventstream::Auth* /*request*/, ::grpc::ServerWriter< ::eventstream::Event>* /*writer*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestListen(::grpc::ServerContext* context, ::eventstream::Auth* request, ::grpc::ServerAsyncWriter< ::eventstream::Event>* writer, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncServerStreaming(0, context, request, writer, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_Listen<Service > AsyncService;
  template <class BaseClass>
  class ExperimentalWithCallbackMethod_Listen : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    ExperimentalWithCallbackMethod_Listen() {
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      ::grpc::Service::
    #else
      ::grpc::Service::experimental().
    #endif
        MarkMethodCallback(0,
          new ::grpc_impl::internal::CallbackServerStreamingHandler< ::eventstream::Auth, ::eventstream::Event>(
            [this](
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
                   ::grpc::CallbackServerContext*
    #else
                   ::grpc::experimental::CallbackServerContext*
    #endif
                     context, const ::eventstream::Auth* request) { return this->Listen(context, request); }));
    }
    ~ExperimentalWithCallbackMethod_Listen() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Listen(::grpc::ServerContext* /*context*/, const ::eventstream::Auth* /*request*/, ::grpc::ServerWriter< ::eventstream::Event>* /*writer*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
    virtual ::grpc::ServerWriteReactor< ::eventstream::Event>* Listen(
      ::grpc::CallbackServerContext* /*context*/, const ::eventstream::Auth* /*request*/)
    #else
    virtual ::grpc::experimental::ServerWriteReactor< ::eventstream::Event>* Listen(
      ::grpc::experimental::CallbackServerContext* /*context*/, const ::eventstream::Auth* /*request*/)
    #endif
      { return nullptr; }
  };
  #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
  typedef ExperimentalWithCallbackMethod_Listen<Service > CallbackService;
  #endif

  typedef ExperimentalWithCallbackMethod_Listen<Service > ExperimentalCallbackService;
  template <class BaseClass>
  class WithGenericMethod_Listen : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_Listen() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_Listen() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Listen(::grpc::ServerContext* /*context*/, const ::eventstream::Auth* /*request*/, ::grpc::ServerWriter< ::eventstream::Event>* /*writer*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithRawMethod_Listen : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_Listen() {
      ::grpc::Service::MarkMethodRaw(0);
    }
    ~WithRawMethod_Listen() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Listen(::grpc::ServerContext* /*context*/, const ::eventstream::Auth* /*request*/, ::grpc::ServerWriter< ::eventstream::Event>* /*writer*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestListen(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncWriter< ::grpc::ByteBuffer>* writer, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncServerStreaming(0, context, request, writer, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class ExperimentalWithRawCallbackMethod_Listen : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    ExperimentalWithRawCallbackMethod_Listen() {
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      ::grpc::Service::
    #else
      ::grpc::Service::experimental().
    #endif
        MarkMethodRawCallback(0,
          new ::grpc_impl::internal::CallbackServerStreamingHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
                   ::grpc::CallbackServerContext*
    #else
                   ::grpc::experimental::CallbackServerContext*
    #endif
                     context, const::grpc::ByteBuffer* request) { return this->Listen(context, request); }));
    }
    ~ExperimentalWithRawCallbackMethod_Listen() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Listen(::grpc::ServerContext* /*context*/, const ::eventstream::Auth* /*request*/, ::grpc::ServerWriter< ::eventstream::Event>* /*writer*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
    virtual ::grpc::ServerWriteReactor< ::grpc::ByteBuffer>* Listen(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/)
    #else
    virtual ::grpc::experimental::ServerWriteReactor< ::grpc::ByteBuffer>* Listen(
      ::grpc::experimental::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/)
    #endif
      { return nullptr; }
  };
  typedef Service StreamedUnaryService;
  template <class BaseClass>
  class WithSplitStreamingMethod_Listen : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithSplitStreamingMethod_Listen() {
      ::grpc::Service::MarkMethodStreamed(0,
        new ::grpc::internal::SplitServerStreamingHandler<
          ::eventstream::Auth, ::eventstream::Event>(
            [this](::grpc_impl::ServerContext* context,
                   ::grpc_impl::ServerSplitStreamer<
                     ::eventstream::Auth, ::eventstream::Event>* streamer) {
                       return this->StreamedListen(context,
                         streamer);
                  }));
    }
    ~WithSplitStreamingMethod_Listen() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status Listen(::grpc::ServerContext* /*context*/, const ::eventstream::Auth* /*request*/, ::grpc::ServerWriter< ::eventstream::Event>* /*writer*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with split streamed
    virtual ::grpc::Status StreamedListen(::grpc::ServerContext* context, ::grpc::ServerSplitStreamer< ::eventstream::Auth,::eventstream::Event>* server_split_streamer) = 0;
  };
  typedef WithSplitStreamingMethod_Listen<Service > SplitStreamedService;
  typedef WithSplitStreamingMethod_Listen<Service > StreamedService;
};

}  // namespace eventstream


#endif  // GRPC_definition_2eproto__INCLUDED
