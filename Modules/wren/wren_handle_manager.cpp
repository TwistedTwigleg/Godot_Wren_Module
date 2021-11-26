
#include "wren_handle_manager.h"

WrenHandleManager* WrenHandleManager::active_handler = nullptr;

WrenHandleManager::WrenHandleManager()
{
    handle_map = std::map<String, WrenHandle*>();
}
WrenHandleManager::~WrenHandleManager()
{
    // Free any remaining handles
    if (wren_vm != nullptr)
    {
        std::map<String, WrenHandle*>::iterator iter;
        for (iter = handle_map.begin(); iter != handle_map.end(); iter++)
        {
            wrenReleaseHandle(wren_vm, iter->second);
        }
    }
}

void WrenHandleManager::set_vm(WrenVM* vm)
{
    if (vm == nullptr)
    {
        print_error("Cannot assign VM to null instance");
        return;
    }
    wren_vm = vm;
}

void WrenHandleManager::set_as_active_handler()
{
    WrenHandleManager::active_handler = this;
}

void WrenHandleManager::set_cache_handle_with_name(String handle_name, int slot_to_cache, bool skip_check)
{
    if (wren_vm != nullptr)
    {
        if (skip_check == false)
        {
            if (handle_map.find(handle_name) != handle_map.end())
            {
                print_error("Cannot cache handle: name passed already taken!");
                print_error(handle_name);
                return;
            }
        }

        WrenHandle* handle = wrenGetSlotHandle(wren_vm, slot_to_cache);
        handle_map.insert(std::pair<String, WrenHandle*>(handle_name, handle));
    }
}

WrenHandle* WrenHandleManager::get_cache_handle_with_name(String handle_name, bool skip_check)
{
    if (skip_check == false)
    {
        if (handle_map.find(handle_name) == handle_map.end())
        {
            return nullptr;
        }
    }
    return handle_map[handle_name];
}

void WrenHandleManager::release_cache_handle_with_name(String handle_name)
{
    if (wren_vm != nullptr)
    {
        if (handle_map.find(handle_name) == handle_map.end())
        {
            return;
        }
        
        WrenHandle* handle = handle_map[handle_name];
        wrenReleaseHandle(wren_vm, handle);
        handle_map.erase(handle_name);
    }
}

void WrenHandleManager::set_cache_handle_get_variable(const char* module, const char* variable, String handle_name, int slot_to_cache)
{
    if (handle_map.find(handle_name) != handle_map.end())
    {
        print_error("Cache handle with name already set");
        return;
    }

    wrenEnsureSlots(wren_vm, slot_to_cache+1);
    wrenGetVariable(wren_vm, module, variable, slot_to_cache);
    set_cache_handle_with_name(handle_name, slot_to_cache, true);
}

void WrenHandleManager::set_cache_handle_call_handle(const char* call_name, String handle_name)
{
    if (handle_map.find(handle_name) != handle_map.end())
    {
        print_error("Cache handle with name already set");
        return;
    }

    WrenHandle* new_handle = wrenMakeCallHandle(wren_vm, call_name);
    handle_map[handle_name] = new_handle;
}
