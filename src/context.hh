#ifndef __CONTEXT_HH__
#define __CONTEXT_HH__

#include "common.hh"

namespace pulse {
  enum InfoType {
    INFO_SOURCE_LIST,
    INFO_SINK_LIST,
  };
  
  class Context: public ObjectWrap {
    friend class Stream;
  protected:
    pa_context *pa_ctx;
    Isolate *isolate;

    Context(Isolate *isolate, String::Utf8Value *client_name);
    ~Context();
    
    /* state */
    Global<Function> state_callback;
    pa_context_state_t pa_state;
    static void StateCallback(pa_context *c, void *ud);
    void state_listener(Local<Value> callback);
    
    /* connection */
    int connect(String::Utf8Value *server_name, pa_context_flags flags);
    void disconnect();

    static void EventCallback(pa_context *c, const char *name, pa_proplist *p, void *ud);
    
    /* introspection */
    void info(InfoType infotype, Local<Function> callback);
  public:
    static pa_mainloop_api mainloop_api;

    static void Init(Local<Object> target);

    static void New(const FunctionCallbackInfo<Value>& info);

    static void Connect(const FunctionCallbackInfo<Value>& info);
    static void Disconnect(const FunctionCallbackInfo<Value>& info);

    static void Info(const FunctionCallbackInfo<Value>& info);
  };
}

#endif//__CONTEXT_HH__
