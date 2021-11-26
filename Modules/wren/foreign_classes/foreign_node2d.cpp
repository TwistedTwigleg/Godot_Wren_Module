/* foreign_node2d.cpp */

#include "foreign_node2d.h"
#include "foreign_vector2.h"
#include "../wrapper_classes/wrapper_node.h"

Foreign_Node2D::Foreign_Node2D()
{

}
Foreign_Node2D::~Foreign_Node2D()
{

}

void Foreign_Node2D::allocate(WrenVM* vm)
{
    Wrapper_Node2D* node = (Wrapper_Node2D*)wrenSetSlotNewForeign(vm, 0, 0, sizeof(Wrapper_Node2D));
    // Not sure if we need to init or not here...
    if (node->node_reference == nullptr)
    {
        node->node_reference = new Node2D();
    }
}
void Foreign_Node2D::finalize(void* data)
{
    // NOT SURE IF NEEDED
    /*
    Wrapper_Node2D* node = (Wrapper_Node2D*)data;
    if (node->node_reference != nullptr)
    {
        // Not sure if we need to delete the node another way...
        node->node_reference->queue_delete();
    }
    */
}
WrenForeignMethodFn Foreign_Node2D::bind_methods(WrenVM* vm, const char* module, const char* className, bool isStatic, const char* signature)
{
    if (!isStatic)
    {
        // Properties:
        // ========================
        if (strcmp(signature, "global_position()") == 0) { return Foreign_Node2D::get_node2d_global_position; }
        else if (strcmp(signature, "global_position") == 0) { return Foreign_Node2D::get_node2d_global_position; }
        else if (strcmp(signature, "global_position=(_)") == 0) { return Foreign_Node2D::set_node2d_global_position; }
        // ========================

        // Godot Methods:
        // ========================
        // ========================

        // Misc
        // ========================
        else if (strcmp(signature, "cast_to_node()") == 0) { return Foreign_Node2D::cast_to_node; }
        else if (strcmp(signature, "cast_from_node(_)") == 0) { return Foreign_Node2D::cast_from_node; }

        else if (strcmp(signature, "print_to_console()") == 0) { return Foreign_Node2D::print_to_console; }
        // ========================
    }
    else
    {
        // Misc
        // ========================
        //if (strcmp(signature, "cast_from_node(_)") == 0) { return Foreign_Node2D::cast_from_node; }
        // ========================
    }

    return NULL;
}
bool Foreign_Node2D::bind_classes(WrenVM* vm, const char* module, const char* className, WrenForeignClassMethods *methods)
{
    if (strcmp(className, "Node2d") == 0)
    {
        methods->allocate = Foreign_Node2D::allocate;
        methods->finalize = Foreign_Node2D::finalize;
        return true;
    }
    return false;
}


// Properties:
// ============================================================
void Foreign_Node2D::get_node2d_global_position(WrenVM* vm)
{
    Wrapper_Node2D* node = (Wrapper_Node2D*)wrenGetSlotForeign(vm, 0);

    if (WrenHandleManager::active_handler != nullptr)
    {
        WrenHandle* vector2_wren_handle = WrenHandleManager::active_handler->get_cache_handle_with_name("Wren_Vector2");
        if (vector2_wren_handle == nullptr)
        {
            WrenHandleManager::active_handler->set_cache_handle_get_variable("main", "Vector2", "Wren_Vector2", 1);
            vector2_wren_handle = WrenHandleManager::active_handler->get_cache_handle_with_name("Wren_Vector2", true);
        }
        wrenSetSlotHandle(vm, 1, vector2_wren_handle);

        Vector2* new_vec2 = (Vector2*)wrenSetSlotNewForeign(vm, 0, 1, sizeof(Vector2));
        Vector2 node_pos = node->node_reference->get_global_position();
        new_vec2->x = node_pos.x;
        new_vec2->y = node_pos.y;
    }
    else
    {
        print_error("ERROR - cannot find wren handle instance! Cannot call get_global_position function!");
        return;
    }
}
void Foreign_Node2D::set_node2d_global_position(WrenVM* vm)
{
    Wrapper_Node2D* node = (Wrapper_Node2D*)wrenGetSlotForeign(vm, 0);
    Vector2* vec2 = (Vector2*)wrenGetSlotForeign(vm, 1);
    node->node_reference->set_global_position(*vec2);
}
// ============================================================

// Godot Methods:
// ============================================================
// ============================================================

// Misc
// ============================================================
void Foreign_Node2D::cast_to_node(WrenVM* vm)
{
    Wrapper_Node2D* node = (Wrapper_Node2D*)wrenGetSlotForeign(vm, 0);
    
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
        new_node->set_node_reference(node->get_node_reference_as_node());
    }
    else
    {
        print_error("ERROR - cannot find wren handle instance! Cannot call cast_to_node function!");
        return;
    }
}
void Foreign_Node2D::cast_from_node(WrenVM* vm)
{
    //Wrapper_Node* node = (Wrapper_Node*)wrenGetSlotForeign(vm, 0);

    Wrapper_Node2D* node_2d = (Wrapper_Node2D*)wrenGetSlotForeign(vm, 0);
    Wrapper_Node* node = (Wrapper_Node*)wrenGetSlotForeign(vm, 1);
    node_2d->set_node_reference_from_node(node);
    
    /*
    if (WrenHandleManager::active_handler != nullptr)
    {
        WrenHandle* node_wren_handle = WrenHandleManager::active_handler->get_cache_handle_with_name("Wren_Node2D");
        if (node_wren_handle == nullptr)
        {
            WrenHandleManager::active_handler->set_cache_handle_get_variable("main", "Node2d", "Wren_Node2D", 1);
            node_wren_handle = WrenHandleManager::active_handler->get_cache_handle_with_name("Wren_Node2D", true);
        }
        wrenSetSlotHandle(vm, 1, node_wren_handle);

        Wrapper_Node2D* new_node = (Wrapper_Node2D*)wrenSetSlotNewForeign(vm, 0, 1, sizeof(Wrapper_Node2D));
        new_node->set_node_reference_from_node(node);
    }
    else
    {
        print_error("ERROR - cannot find wren handle instance! Cannot call cast_to_node function!");
        return;
    }
    */
}

void Foreign_Node2D::print_to_console(WrenVM* vm)
{
    Wrapper_Node2D* node = (Wrapper_Node2D*)wrenGetSlotForeign(vm, 0);
    String return_string = "Node2D name: (";
    return_string += node->node_reference->get_name();
    return_string += ")";
    print_line(return_string);
}
// ============================================================
