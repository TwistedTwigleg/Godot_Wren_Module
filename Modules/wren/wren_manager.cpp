/* wren_manager.cpp */

#include "wren_manager.h"

#include "foreign_classes/foreign_vector2.h"
#include "foreign_classes/foreign_node.h"
#include "foreign_classes/foreign_node2d.h"

#include "wrapper_classes/wrapper_node.h"

Node* WrenManager::self_ref = nullptr;

void WrenManager::_notification(int p_notification)
{
    if (p_notification == NOTIFICATION_PROCESS)
    {
        WrenHandle* wren_node_class = wren_handle_manager.get_cache_handle_with_name("wren_node_class");
        WrenHandle* wren_node_class_function = wren_handle_manager.get_cache_handle_with_name("wren_node_class_process_func");

        if (wren_node_class != nullptr)
        {
            double delta_time = get_process_delta_time();
            wren_handle_manager.set_as_active_handler();

            wrenEnsureSlots(wren_vm, 2);
            wrenSetSlotHandle(wren_vm, 0, wren_node_class);
            wrenSetSlotDouble(wren_vm, 1, delta_time);
            WrenInterpretResult result = wrenCall(wren_vm, wren_node_class_function);

            switch (result) {
                case WREN_RESULT_COMPILE_ERROR:
                {
                    printf("Function Call Error!\n");
                }
                break;
                
                case WREN_RESULT_RUNTIME_ERROR:
                { 
                    printf("Runtime Error!\n");
                }
                break;
                
                case WREN_RESULT_SUCCESS:
                { 
                    //printf("Function Call Success!\n");
                }
                break;
            }
        }
    }
}

void WrenManager::_bind_methods() {

    ClassDB::bind_method(D_METHOD("initialize"), &WrenManager::Initialize);
    ClassDB::bind_method(D_METHOD("set_code_string", "code_string"), &WrenManager::SetCodeString);

    /*
    ClassDB::bind_method(D_METHOD("set_api_url", "api_url"), &Crashpad::set_crashpad_api_url);
	ClassDB::bind_method(D_METHOD("get_api_url"), &Crashpad::get_crashpad_api_url);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "crashpad_settings/api_url", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT_INTL), "set_api_url", "get_api_url");
    */
}

WrenManager::WrenManager()
{
    set_process(true);
    wren_handle_manager = WrenHandleManager();
}
WrenManager::~WrenManager()
{
    if (wren_vm != nullptr)
    {
        wren_handle_manager.release_cache_handle_with_name("wren_node_class");
        wren_handle_manager.release_cache_handle_with_name("wren_node_class_process_func");

        if (WrenHandleManager::active_handler == &wren_handle_manager)
        {
            WrenHandleManager::active_handler = nullptr;
        }
        wrenFreeVM(wren_vm);
    }
}


void WrenManager::wren_writeFn(WrenVM* vm, const char* text)
{
    printf("%s\n", text);
}
void WrenManager::wren_errorFn(WrenVM* vm, WrenErrorType errorType, const char* module, const int line, const char* msg)
{
    switch (errorType)
    {
        case WREN_ERROR_COMPILE:
        {
            printf("[%s line %d] [Error] %s\n", module, line, msg);
        }
        break;
        
        case WREN_ERROR_STACK_TRACE:
        {
            printf("[%s line %d] in %s\n", module, line, msg);
        }
        break;
        
        case WREN_ERROR_RUNTIME:
        {
            printf("[Runtime Error] %s\n", msg);
        }
        break;
    }
}
WrenForeignMethodFn WrenManager::wren_bindForeignMethodFn(WrenVM* vm, const char* module, const char* className, bool isStatic, const char* signature)
{
    if (strcmp(module, "main") == 0)
    {
        if (strcmp(className, "WrenManager") == 0)
        {
            if (isStatic && strcmp(signature, "WrenExposed(_,_)") == 0)
            {
                return WrenExposed;
            }
            else if (isStatic && strcmp(signature, "WrenGetNode()") == 0)
            {
                return WrenGetNode;
            }
        }

        if (strcmp(className, "Vector2") == 0)
        {
            return Foreign_Vector2::bind_methods(vm, module, className, isStatic, signature);
        }
        else if (strcmp(className, "Node") == 0)
        {
            return Foreign_Node::bind_methods(vm, module, className, isStatic, signature);
        }
        else if (strcmp(className, "Node2d") == 0)
        {
            return Foreign_Node2D::bind_methods(vm, module, className, isStatic, signature);
        }
    }
    return NULL;
}
WrenForeignClassMethods WrenManager::wren_bindForeignClassMethods(WrenVM* vm, const char* module, const char* className)
{
    WrenForeignClassMethods methods;

    // TODO - find a better way to optimize this
    if (Foreign_Vector2::bind_classes(vm, module, className, &methods) == true) {}
    else if (Foreign_Node::bind_classes(vm, module, className, &methods) == true) {}
    else if (Foreign_Node2D::bind_classes(vm, module, className, &methods) == true) {}
    else
    {
        // Unknown class
        methods.allocate = NULL;
        methods.finalize = NULL;
    }

    return methods;
}


void WrenManager::Initialize()
{
    if (WrenManager::self_ref == nullptr)
    {
        print_line("Self name before: " + this->get_name());
        WrenManager::self_ref = Object::cast_to<Node>(this);
        print_line("Self name after: " + self_ref->get_name());
    }

    WrenConfiguration wren_config;
    wrenInitConfiguration(&wren_config);
    wren_config.writeFn = &wren_writeFn;
    wren_config.errorFn = &wren_errorFn;
    wren_config.bindForeignMethodFn = &wren_bindForeignMethodFn;
    wren_config.bindForeignClassFn = &wren_bindForeignClassMethods;

    wren_vm = wrenNewVM(&wren_config);
    wren_handle_manager.set_vm(wren_vm);
}

void WrenManager::SetCodeString(String code_string)
{
    std::wstring code_ws = code_string.c_str();
    std::string code_ss(code_ws.begin(), code_ws.end());

    wren_handle_manager.set_as_active_handler();

    // Execute a string of Wren code!
    WrenInterpretResult result = wrenInterpret(
        wren_vm,
        "main",
        code_ss.c_str()
    );

    switch (result) {
        case WREN_RESULT_COMPILE_ERROR:
        {
            printf("Compile Error!\n");
        }
        break;
        
        case WREN_RESULT_RUNTIME_ERROR:
        { 
            printf("Runtime Error!\n");
        }
        break;
        
        case WREN_RESULT_SUCCESS:
        { 
            printf("Success!\n");
        }
        break;
    }
    wren_handle_manager.set_cache_handle_get_variable("main", "Wren_Node", "wren_node_class", 0);
    wren_handle_manager.set_cache_handle_call_handle("update(_)", "wren_node_class_process_func");
}

void WrenManager::WrenExposed(WrenVM* vm)
{
    double a = wrenGetSlotDouble(vm, 1);
    double b = wrenGetSlotDouble(vm, 2);
    wrenSetSlotDouble(vm, 0, a+b);
}
void WrenManager::WrenGetNode(WrenVM* vm)
{
    print_line("Self name in GetNode call: " + WrenManager::self_ref->get_name());

    if (WrenHandleManager::active_handler != nullptr)
    {
        WrenHandle* node_wren_handle = WrenHandleManager::active_handler->get_cache_handle_with_name("Wren_Node");
        if (node_wren_handle == nullptr)
        {
            WrenHandleManager::active_handler->set_cache_handle_get_variable("main", "Node", "Wren_Node", 1);
            node_wren_handle = WrenHandleManager::active_handler->get_cache_handle_with_name("Wren_Node", true);
        }
        wrenSetSlotHandle(vm, 1, node_wren_handle);

        // TODO - make this work by returning a wrapped that has a reference to a Node, I guess?
        /*
        Node* new_node = (Node*)wrenSetSlotNewForeign(vm, 0, 1, sizeof(Node));
        change_pointer_address(&new_node, WrenManager::self_ref);
        */
        Wrapper_Node* new_node = (Wrapper_Node*)wrenSetSlotNewForeign(vm, 0, 1, sizeof(Wrapper_Node));
        new_node->set_node_reference(WrenManager::self_ref);
    }
    else
    {
        print_error("ERROR - cannot find wren handle instance! Cannot call WrenGetNode function!");
        return;
    }
}
void WrenManager::change_pointer_address(Node **pointer, Node *new_address)
{
    *pointer = new_address;
}
