/* foreign_vector2.h */

#ifndef FOREIGN_VECTOR2_H
#define FOREIGN_VECTOR2_H

#include "scene/2d/node_2d.h"
#include "../wren_manager.h"

class Foreign_Vector2 {

public:
    Foreign_Vector2();
    ~Foreign_Vector2();

    static void allocate(WrenVM* vm);
    static void finalize(void* data);
    static WrenForeignMethodFn bind_methods(WrenVM* vm, const char* module, const char* className, bool isStatic, const char* signature);
    static bool bind_classes(WrenVM* vm, const char* module, const char* className, WrenForeignClassMethods *methods);

    // Properties
    // ==============
    static void get_vector2_x(WrenVM* vm);
    static void set_vector2_x(WrenVM* vm);
    static void get_vector2_y(WrenVM* vm);
    static void set_vector2_y(WrenVM* vm);
    // ==============

    // Godot Methods
    // ==============
    static void method_vector2_abs(WrenVM* vm);
    static void method_vector2_angle(WrenVM* vm);
    static void method_vector2_angle_to(WrenVM* vm);
    static void method_vector2_angle_to_point(WrenVM* vm);
    static void method_vector2_aspect(WrenVM* vm);
    static void method_vector2_bounce(WrenVM* vm);
    static void method_vector2_ceil(WrenVM* vm);
    static void method_vector2_clamped(WrenVM* vm);
    static void method_vector2_cross(WrenVM* vm);
    static void method_vector2_cubic_interpolate(WrenVM* vm);
    static void method_vector2_direction_to(WrenVM* vm);
    static void method_vector2_distance_to(WrenVM* vm);
    static void method_vector2_distance_squared_to(WrenVM* vm);
    static void method_vector2_dot(WrenVM* vm);
    static void method_vector2_floor(WrenVM* vm);
    static void method_vector2_is_equal_approx(WrenVM* vm);
    static void method_vector2_is_normalized(WrenVM* vm);
    static void method_vector2_length(WrenVM* vm);
    static void method_vector2_length_squared(WrenVM* vm);
    static void method_vector2_linear_interpolate(WrenVM* vm);
    static void method_vector2_move_toward(WrenVM* vm);
    static void method_vector2_normalized(WrenVM* vm);
    static void method_vector2_posmod(WrenVM* vm);
    static void method_vector2_posmodv(WrenVM* vm);
    static void method_vector2_project(WrenVM* vm);
    static void method_vector2_reflect(WrenVM* vm);
    static void method_vector2_rotated(WrenVM* vm);
    static void method_vector2_round(WrenVM* vm);
    static void method_vector2_sign(WrenVM* vm);
    static void method_vector2_slerp(WrenVM* vm);
    static void method_vector2_slide(WrenVM* vm);
    static void method_vector2_snapped(WrenVM* vm);
    static void method_vector2_tangent(WrenVM* vm);
    // ==============

    // Misc
    // ==============
    static void custom_vector2_set(WrenVM* vm);
    static void custom_vector2_get_as_string(WrenVM* vm);
    static void custom_vector2_normalize(WrenVM* vm);

    // Really just for debugging, since I cannot get it to directly print the values in Wren currently...
    static void print_to_console(WrenVM* vm);
    // ==============
};

#endif // FOREIGN_VECTOR2_H