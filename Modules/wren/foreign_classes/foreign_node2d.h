/* foreign_node2d.h */

#ifndef FOREIGN_NODE2D_H
#define FOREIGN_NODE2D_H

#include "scene/2d/node_2d.h"
#include "../wrapper_classes/wrapper_node2d.h"
#include "../wren_manager.h"

class Foreign_Node2D {

public:
    Foreign_Node2D();
    ~Foreign_Node2D();

    static void allocate(WrenVM* vm);
    static void finalize(void* data);
    static WrenForeignMethodFn bind_methods(WrenVM* vm, const char* module, const char* className, bool isStatic, const char* signature);
    static bool bind_classes(WrenVM* vm, const char* module, const char* className, WrenForeignClassMethods *methods);

    // Properties
    // ==============
    // TODO - add other properties
    static void get_node2d_global_position(WrenVM* vm);
    static void set_node2d_global_position(WrenVM* vm);
    // ==============

    // Godot Methods
    // ==============
    // TODO - add other methods
    // ==============

    // Misc
    // ==============
    static void cast_to_node(WrenVM* vm);
    static void cast_from_node(WrenVM* vm);

    // Really just for debugging, since I cannot get it to directly print the values in Wren currently...
    static void print_to_console(WrenVM* vm);
    // ==============
};

#endif // FOREIGN_NODE2D_H