/* foreign_node.cpp */

#include "foreign_node.h"
#include "../wren_manager.h"

Foreign_Node::Foreign_Node()
{

}
Foreign_Node::~Foreign_Node()
{

}

void Foreign_Node::allocate(WrenVM* vm)
{
    Wrapper_Node* node = (Wrapper_Node*)wrenSetSlotNewForeign(vm, 0, 0, sizeof(Wrapper_Node));
    // Not sure if we need to init or not here...

    if (node->node_reference == nullptr)
    {
        node->node_reference = new Node();
    }
}
void Foreign_Node::finalize(void* data)
{
    // NOT SURE IF NEEDED
    Wrapper_Node* node = (Wrapper_Node*)data;
    if (node->node_reference != nullptr)
    {
        // Not sure if we need to delete the node another way...
        node->node_reference->queue_delete();
    }
}
WrenForeignMethodFn Foreign_Node::bind_methods(WrenVM* vm, const char* module, const char* className, bool isStatic, const char* signature)
{
    if (!isStatic)
    {
        // Properties:
        // ========================
        if (strcmp(signature, "name()") == 0) { return Foreign_Node::get_node_name; }
        else if (strcmp(signature, "name") == 0) { return Foreign_Node::get_node_name; }
        else if (strcmp(signature, "name=(_)") == 0) { return Foreign_Node::set_node_name; }
        // ========================

        // Godot Methods:
        // ========================
        else if (strcmp(signature, "add_child(_)") == 0) { return Foreign_Node::method_node_add_child; }
        else if (strcmp(signature, "get_child(_)") == 0) { return Foreign_Node::method_node_get_child; }
        else if (strcmp(signature, "get_node(_)") == 0) { return Foreign_Node::method_node_get_node; }
        else if (strcmp(signature, "get_parent()") == 0) { return Foreign_Node::method_node_get_parent; }
        // ========================

        // Misc
        // ========================
        else if (strcmp(signature, "print_to_console()") == 0)
        {
            return Foreign_Node::print_to_console;
        }
        // ========================
    }
    return NULL;
}
bool Foreign_Node::bind_classes(WrenVM* vm, const char* module, const char* className, WrenForeignClassMethods *methods)
{
    if (strcmp(className, "Node") == 0)
    {
        methods->allocate = Foreign_Node::allocate;
        methods->finalize = Foreign_Node::finalize;
        return true;
    }
    return false;
}


// Properties:
// ============================================================
void Foreign_Node::get_node_name(WrenVM* vm)
{
    Wrapper_Node* node = (Wrapper_Node*)wrenGetSlotForeign(vm, 0);
    String name_str = node->node_reference->get_name();
    std::wstring name_ws = name_str.c_str();
    std::string name_ss(name_ws.begin(), name_ws.end());

    wrenSetSlotString(vm, 0, name_ss.c_str());
}
void Foreign_Node::set_node_name(WrenVM* vm)
{
    Wrapper_Node* node = (Wrapper_Node*)wrenGetSlotForeign(vm, 0);
    const char* new_name = wrenGetSlotString(vm, 1);
    node->node_reference->set_name(new_name);
}
// ============================================================

// Godot Methods:
// ============================================================
void Foreign_Node::method_node_add_child(WrenVM* vm)
{
    Wrapper_Node* node = (Wrapper_Node*)wrenGetSlotForeign(vm, 0);
    Wrapper_Node* node_other = (Wrapper_Node*)wrenGetSlotForeign(vm, 1);
    bool node_other_legible = wrenGetSlotBool(vm, 2);

    node->node_reference->add_child(node_other->node_reference, node_other_legible);
}

void Foreign_Node::method_node_get_child(WrenVM* vm)
{
    Wrapper_Node* node = (Wrapper_Node*)wrenGetSlotForeign(vm, 0);
    int child_index = (int)wrenGetSlotDouble(vm, 1);

    if (WrenHandleManager::active_handler != nullptr)
    {
        WrenHandle* node_wren_handle = WrenHandleManager::active_handler->get_cache_handle_with_name("Wren_Node");
        if (node_wren_handle == nullptr)
        {
            WrenHandleManager::active_handler->set_cache_handle_get_variable("main", "Node", "Wren_Node", 1);
            node_wren_handle = WrenHandleManager::active_handler->get_cache_handle_with_name("Wren_Node", true);
        }
        wrenSetSlotHandle(vm, 1, node_wren_handle);

        Wrapper_Node* new_node = (Wrapper_Node*)wrenSetSlotNewForeign(vm, 0, 1, sizeof(Wrapper_Node));
        new_node->set_node_reference(node->node_reference->get_child(child_index));
    }
    else
    {
        print_error("ERROR - cannot find wren handle instance! Cannot call get_child function!");
        return;
    }
}

void Foreign_Node::method_node_get_node(WrenVM* vm)
{

    Wrapper_Node* node = (Wrapper_Node*)wrenGetSlotForeign(vm, 0);
    const char* child_path = wrenGetSlotString(vm, 1);

    if (WrenHandleManager::active_handler != nullptr)
    {
        WrenHandle* node_wren_handle = WrenHandleManager::active_handler->get_cache_handle_with_name("Wren_Node");
        if (node_wren_handle == nullptr)
        {
            WrenHandleManager::active_handler->set_cache_handle_get_variable("main", "Node", "Wren_Node", 1);
            node_wren_handle = WrenHandleManager::active_handler->get_cache_handle_with_name("Wren_Node", true);
        }
        wrenSetSlotHandle(vm, 1, node_wren_handle);

        Wrapper_Node* new_node = (Wrapper_Node*)wrenSetSlotNewForeign(vm, 0, 1, sizeof(Wrapper_Node));
        NodePath path = NodePath(String(child_path));
        new_node->set_node_reference(node->node_reference->get_node(path));
    }
    else
    {
        print_error("ERROR - cannot find wren handle instance! Cannot call get_node function!");
        return;
    }
}

void Foreign_Node::method_node_get_parent(WrenVM* vm)
{
    Wrapper_Node* node = (Wrapper_Node*)wrenGetSlotForeign(vm, 0);

    if (WrenHandleManager::active_handler != nullptr)
    {
        WrenHandle* node_wren_handle = WrenHandleManager::active_handler->get_cache_handle_with_name("Wren_Node");
        if (node_wren_handle == nullptr)
        {
            WrenHandleManager::active_handler->set_cache_handle_get_variable("main", "Node", "Wren_Node", 1);
            node_wren_handle = WrenHandleManager::active_handler->get_cache_handle_with_name("Wren_Node", true);
        }
        wrenSetSlotHandle(vm, 1, node_wren_handle);

        Wrapper_Node* new_node = (Wrapper_Node*)wrenSetSlotNewForeign(vm, 0, 1, sizeof(Wrapper_Node));
        new_node->set_node_reference(node->node_reference->get_parent());
    }
    else
    {
        print_error("ERROR - cannot find wren handle instance! Cannot call get_node function!");
        return;
    }
}
// ============================================================

// Misc
// ============================================================
void Foreign_Node::print_to_console(WrenVM* vm)
{
    Wrapper_Node* node = (Wrapper_Node*)wrenGetSlotForeign(vm, 0);
    String return_string = "(";
    return_string += node->node_reference->get_name();
    return_string += ")";
    print_line(return_string);
}
// ============================================================
