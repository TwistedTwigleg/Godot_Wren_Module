/* foreign_node.h */

#ifndef FOREIGN_NODE_H
#define FOREIGN_NODE_H

#include "scene/main/node.h"
#include "../wrapper_classes/wrapper_node.h"
#include "../wren_manager.h"

class Foreign_Node {

public:
    Foreign_Node();
    ~Foreign_Node();

    static void allocate(WrenVM* vm);
    static void finalize(void* data);
    static WrenForeignMethodFn bind_methods(WrenVM* vm, const char* module, const char* className, bool isStatic, const char* signature);
    static bool bind_classes(WrenVM* vm, const char* module, const char* className, WrenForeignClassMethods *methods);

    // Properties
    // ==============
    // TODO - add other properties
    static void get_node_name(WrenVM* vm);
    static void set_node_name(WrenVM* vm);
    // ==============

    // Godot Methods
    // ==============
    // TODO - add other methods
    static void method_node_add_child(WrenVM* vm);
    static void method_node_get_child(WrenVM* vm);
    static void method_node_get_node(WrenVM* vm);
    static void method_node_get_parent(WrenVM* vm);
    // ==============

    // Misc
    // ==============
    // Really just for debugging, since I cannot get it to directly print the values in Wren currently...
    static void print_to_console(WrenVM* vm);
    // ==============
};

#endif // FOREIGN_NODE_H