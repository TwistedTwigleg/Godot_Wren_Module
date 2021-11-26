/* wren_manager.h */

#ifndef WRENMANAGER_H
#define WRENMANAGER_H

#include "scene/main/node.h"
#include "core/reference.h"
#include "core/os/dir_access.h"

#include "wren_handle_manager.h"
#include "src/include/wren.hpp"

class WrenManager : public Node {
    GDCLASS(WrenManager, Node);

protected:
    static void _bind_methods();
    void _notification(int p_notification);

public:
    WrenManager();
    ~WrenManager();

    void Initialize();
    void SetCodeString(String code_string);

    // FOR TESTING REALLY
    void static WrenExposed(WrenVM* vm);

    static Node* self_ref;
    void static WrenGetNode(WrenVM* vm);

private:

    WrenVM* wren_vm = nullptr;
    static void wren_writeFn(WrenVM* vm, const char* text);
    static void wren_errorFn(WrenVM* vm, WrenErrorType errorType, const char* module, const int line, const char* msg);
    static WrenForeignMethodFn wren_bindForeignMethodFn(WrenVM* vm, const char* module, const char* className, bool isStatic, const char* signature);
    static WrenForeignClassMethods wren_bindForeignClassMethods(WrenVM* vm, const char* module, const char* className);

    WrenHandleManager wren_handle_manager;

    static void change_pointer_address(Node **pointer, Node *new_address);

    //WrenHandle* wren_node_class = nullptr;
    //WrenHandle* wren_node_class_process_func = nullptr;
};

#endif // WRENMANAGER_H