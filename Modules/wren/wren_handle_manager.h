/* wren_handle_manager.h */

#ifndef WREN_HANDLE_MANAGER_H
#define WREN_HANDLE_MANAGER_H

#include "scene/main/node.h"

#include "src/include/wren.hpp"

#include<mutex>
#include<map>

class WrenHandleManager {

public:
    WrenHandleManager();
    ~WrenHandleManager();

    std::map<String, WrenHandle*> handle_map;
    WrenVM* wren_vm;

    void set_vm(WrenVM* vm);
    void set_as_active_handler();

    void set_cache_handle_with_name(String handle_name, int slot_to_cache, bool skip_check=false);
    WrenHandle* get_cache_handle_with_name(String handle_name, bool skip_check=false);
    void release_cache_handle_with_name(String handle_name);

    void set_cache_handle_get_variable(const char* module, const char* variable, String handle_name, int slot_to_cache);
    void set_cache_handle_call_handle(const char* call_name, String handle_name);

    static WrenHandleManager* active_handler;
};

#endif // WREN_HANDLE_MANAGER_H