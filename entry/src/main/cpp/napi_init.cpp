#include "napi/native_api.h"
#include <dlfcn.h>
#include "hilog/log.h"
#include <thread>

#define LOAD_FUNCTION(handle, func) \
    func = (typeof(func))dlsym(handle, #func); \
    if (!func) { \
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_DOMAIN, "ClashNative", "Failed to load function: %{public}s \n", #func); \
        return nullptr; \
    }
typedef unsigned char  (*coreTest_t)();
coreTest_t unpackTool;
static napi_value Add(napi_env env, napi_callback_info info)
{
    size_t argc = 2;
    napi_value args[2] = {nullptr};

    napi_get_cb_info(env, info, &argc, args , nullptr, nullptr);

    napi_valuetype valuetype0;
    napi_typeof(env, args[0], &valuetype0);

    napi_valuetype valuetype1;
    napi_typeof(env, args[1], &valuetype1);

    double value0;
    napi_get_value_double(env, args[0], &value0);

    double value1;
    napi_get_value_double(env, args[1], &value1);
    char result = unpackTool();
//     std::thread t([](){
//         OH_LOG_Print(LOG_APP, LOG_INFO, LOG_DOMAIN, "ClashNative", "core Test   %{public}s \n", result);
//     });
//     t.join();
    napi_value sum;
    napi_create_double(env,  11, &sum);

    return sum;

}



EXTERN_C_START
static napi_value Init(napi_env env, napi_value exports)
{
    void *handle = dlopen("gotest.so", RTLD_LAZY);
    const char* dlsym_error = dlerror();
    if (!handle) {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_DOMAIN, "ClashNative", "Failed to load library: %{public}s \n", dlsym_error);
        return NULL;
    }
    LOAD_FUNCTION(handle, unpackTool);
    dlsym_error = dlerror();
    napi_property_descriptor desc[] = {
        { "add", nullptr, Add, nullptr, nullptr, nullptr, napi_default, nullptr }
    };
    napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc);
    return exports;
}
EXTERN_C_END

static napi_module demoModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = Init,
    .nm_modname = "entry",
    .nm_priv = ((void*)0),
    .reserved = { 0 },
};

extern "C" __attribute__((constructor)) void RegisterEntryModule(void)
{
    napi_module_register(&demoModule);
}
