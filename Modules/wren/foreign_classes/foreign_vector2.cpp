/* foreign_vector2.cpp */

#include "foreign_vector2.h"

// HELPFUL REFERENCE: https://nelari.us/post/wren-embedding-1/

Foreign_Vector2::Foreign_Vector2()
{

}
Foreign_Vector2::~Foreign_Vector2()
{

}

void Foreign_Vector2::allocate(WrenVM* vm)
{
    Vector2* vec2 = (Vector2*)wrenSetSlotNewForeign(vm, 0, 0, sizeof(Vector2));
    double val_x = wrenGetSlotDouble(vm, 1);
    double val_y = wrenGetSlotDouble(vm, 2);
    vec2->x = val_x;
    vec2->y = val_y;
}
void Foreign_Vector2::finalize(void* data)
{
    // Not really anything to do here, I don't think...
}
WrenForeignMethodFn Foreign_Vector2::bind_methods(WrenVM* vm, const char* module, const char* className, bool isStatic, const char* signature)
{
    if (!isStatic)
    {
        // Properties:
        // ========================
        if (strcmp(signature, "x()") == 0) { return Foreign_Vector2::get_vector2_x; }
        else if (strcmp(signature, "x") == 0) { return Foreign_Vector2::get_vector2_x; }
        else if (strcmp(signature, "x=(_)") == 0) { return Foreign_Vector2::set_vector2_x; }

        else if (strcmp(signature, "y()") == 0) { return Foreign_Vector2::get_vector2_y; }
        else if (strcmp(signature, "y") == 0) { return Foreign_Vector2::get_vector2_y; }
        else if (strcmp(signature, "y=(_)") == 0) { return Foreign_Vector2::set_vector2_y; }
        // ========================

        // Godot Methods:
        // ========================
        else if (strcmp(signature, "abs()") == 0) { return Foreign_Vector2::method_vector2_abs; }
        // ========================

        // Misc
        // ========================
        else if (strcmp(signature, "set(_,_)") == 0)
        {
            return Foreign_Vector2::custom_vector2_set;
        }
        else if (strcmp(signature, "normalize()") == 0)
        {
            return Foreign_Vector2::custom_vector2_normalize;
        }
        else if (strcmp(signature, "get_as_string()") == 0)
        {
            return Foreign_Vector2::custom_vector2_get_as_string;
        }
        else if (strcmp(signature, "print_to_console()") == 0)
        {
            return Foreign_Vector2::print_to_console;
        }
        // ========================
    }
    return NULL;
}
bool Foreign_Vector2::bind_classes(WrenVM* vm, const char* module, const char* className, WrenForeignClassMethods *methods)
{
    if (strcmp(className, "Vector2") == 0)
    {
        methods->allocate = Foreign_Vector2::allocate;
        methods->finalize = Foreign_Vector2::finalize;
        return true;
    }
    return false;
}


// Properties:
// ============================================================
void Foreign_Vector2::get_vector2_x(WrenVM* vm)
{
    Vector2* vec = (Vector2*)wrenGetSlotForeign(vm, 0);
    wrenSetSlotDouble(vm, 0, (double)vec->x);
}
void Foreign_Vector2::set_vector2_x(WrenVM* vm)
{
    Vector2* vec = (Vector2*)wrenGetSlotForeign(vm, 0);
    double new_x = wrenGetSlotDouble(vm, 1);
    vec->x = new_x;
}
void Foreign_Vector2::get_vector2_y(WrenVM* vm)
{
    Vector2* vec = (Vector2*)wrenGetSlotForeign(vm, 0);
    wrenSetSlotDouble(vm, 0, (double)vec->y);
}
void Foreign_Vector2::set_vector2_y(WrenVM* vm)
{
    Vector2* vec = (Vector2*)wrenGetSlotForeign(vm, 0);
    double new_y = wrenGetSlotDouble(vm, 1);
    vec->y = new_y;
}
// ============================================================

// Godot Methods:
// ============================================================
void Foreign_Vector2::method_vector2_abs(WrenVM* vm)
{
    Vector2* vec = (Vector2*)wrenGetSlotForeign(vm, 0);
    
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
        Vector2 vec_abs = vec->abs();
        new_vec2->x = vec_abs.x;
        new_vec2->y = vec_abs.y;
    }
    else
    {
        print_error("ERROR - cannot find wren handle instance! Cannot call vector2_abs function!");
        return;
    }
}
// MAKE OTHERS BELOW WORK

void Foreign_Vector2::method_vector2_angle(WrenVM* vm)
{
    Vector2* vec = (Vector2*)wrenGetSlotForeign(vm, 0);
    wrenSetSlotDouble(vm, 0, vec->angle());
}

void Foreign_Vector2::method_vector2_angle_to(WrenVM* vm)
{
    Vector2* vec = (Vector2*)wrenGetSlotForeign(vm, 0);
    Vector2* vec_other = (Vector2*)wrenGetSlotForeign(vm, 1);
    wrenSetSlotDouble(vm, 0, vec->angle_to(*vec_other));
}

void Foreign_Vector2::method_vector2_angle_to_point(WrenVM* vm)
{
    Vector2* vec = (Vector2*)wrenGetSlotForeign(vm, 0);
    Vector2* vec_other = (Vector2*)wrenGetSlotForeign(vm, 1);
    wrenSetSlotDouble(vm, 0, vec->angle_to_point(*vec_other));
}

void Foreign_Vector2::method_vector2_aspect(WrenVM* vm)
{
    Vector2* vec = (Vector2*)wrenGetSlotForeign(vm, 0);
    wrenSetSlotDouble(vm, 0, vec->aspect());
}

void Foreign_Vector2::method_vector2_bounce(WrenVM* vm)
{
    Vector2* vec = (Vector2*)wrenGetSlotForeign(vm, 0);
    Vector2* vec_other = (Vector2*)wrenGetSlotForeign(vm, 1);

    // We need to return a new Vector2, so we mimic the constructor
    Vector2* new_vec2 = (Vector2*)wrenSetSlotNewForeign(vm, 0, 0, sizeof(Vector2));
    new_vec2 = new Vector2(vec->bounce(*vec_other));
}

void Foreign_Vector2::method_vector2_ceil(WrenVM* vm)
{
    Vector2* vec = (Vector2*)wrenGetSlotForeign(vm, 0);
    // We need to return a new Vector2, so we mimic the constructor
    Vector2* new_vec2 = (Vector2*)wrenSetSlotNewForeign(vm, 0, 0, sizeof(Vector2));
    new_vec2 = new Vector2(vec->ceil());
}

void Foreign_Vector2::method_vector2_clamped(WrenVM* vm)
{
    Vector2* vec = (Vector2*)wrenGetSlotForeign(vm, 0);
    double length = wrenGetSlotDouble(vm, 1);
    // We need to return a new Vector2, so we mimic the constructor
    Vector2* new_vec2 = (Vector2*)wrenSetSlotNewForeign(vm, 0, 0, sizeof(Vector2));
    new_vec2 = new Vector2(vec->clamped(length));
}

void Foreign_Vector2::method_vector2_cross(WrenVM* vm)
{
    Vector2* vec = (Vector2*)wrenGetSlotForeign(vm, 0);
    Vector2* vec_other = (Vector2*)wrenGetSlotForeign(vm, 1);
    wrenSetSlotDouble(vm, 0, vec->cross(*vec_other));
}

void Foreign_Vector2::method_vector2_cubic_interpolate(WrenVM* vm)
{
    Vector2* vec = (Vector2*)wrenGetSlotForeign(vm, 0);
    Vector2* vec_other = (Vector2*)wrenGetSlotForeign(vm, 1);
    Vector2* vec_other_two = (Vector2*)wrenGetSlotForeign(vm, 2);
    Vector2* vec_other_three = (Vector2*)wrenGetSlotForeign(vm, 3);
    float weight = wrenGetSlotDouble(vm, 4);

    // We need to return a new Vector2, so we mimic the constructor
    Vector2* new_vec2 = (Vector2*)wrenSetSlotNewForeign(vm, 0, 0, sizeof(Vector2));
    new_vec2 = new Vector2(vec->cubic_interpolate(*vec_other, *vec_other_two, *vec_other_three, weight));
}

void Foreign_Vector2::method_vector2_direction_to(WrenVM *vm)
{
    Vector2* vec = (Vector2*)wrenGetSlotForeign(vm, 0);
    Vector2* vec_other = (Vector2*)wrenGetSlotForeign(vm, 1);
    // We need to return a new Vector2, so we mimic the constructor
    Vector2* new_vec2 = (Vector2*)wrenSetSlotNewForeign(vm, 0, 0, sizeof(Vector2));
    new_vec2 = new Vector2(vec->direction_to(*vec_other));
}

void Foreign_Vector2::method_vector2_distance_to(WrenVM *vm)
{
    Vector2* vec = (Vector2*)wrenGetSlotForeign(vm, 0);
    Vector2* vec_other = (Vector2*)wrenGetSlotForeign(vm, 1);
    wrenSetSlotDouble(vm, 0, vec->distance_to(*vec_other));
}

void Foreign_Vector2::method_vector2_distance_squared_to(WrenVM *vm)
{
    Vector2* vec = (Vector2*)wrenGetSlotForeign(vm, 0);
    Vector2* vec_other = (Vector2*)wrenGetSlotForeign(vm, 1);
    wrenSetSlotDouble(vm, 0, vec->distance_squared_to(*vec_other));
}

void Foreign_Vector2::method_vector2_dot(WrenVM *vm)
{
    Vector2* vec = (Vector2*)wrenGetSlotForeign(vm, 0);
    Vector2* vec_other = (Vector2*)wrenGetSlotForeign(vm, 1);
    wrenSetSlotDouble(vm, 0, vec->dot(*vec_other));
}

// CONTINUE AT FLOOR

// ============================================================

// Misc
// ============================================================
void Foreign_Vector2::custom_vector2_set(WrenVM* vm)
{
    Vector2* vec = (Vector2*)wrenGetSlotForeign(vm, 0);
    vec->x = wrenGetSlotDouble(vm, 1);
    vec->y = wrenGetSlotDouble(vm, 2);
}

void Foreign_Vector2::custom_vector2_get_as_string(WrenVM* vm)
{
    Vector2* vec = (Vector2*)wrenGetSlotForeign(vm, 0);

    String return_string = "(";
    return_string += String::num(vec->x);
    return_string += ", ";
    return_string += String::num(vec->y);
    return_string += ")";

    std::wstring return_string_ws = std::wstring(return_string.c_str());
    std::string return_string_ss(return_string_ws.begin(), return_string_ws.end());

    wrenSetSlotString(vm, 0, return_string_ss.c_str());
}
void Foreign_Vector2::custom_vector2_normalize(WrenVM* vm)
{
    Vector2* vec = (Vector2*)wrenGetSlotForeign(vm, 0);
    vec->normalize();
}


void Foreign_Vector2::print_to_console(WrenVM* vm)
{
    Vector2* vec = (Vector2*)wrenGetSlotForeign(vm, 0);
    String return_string = "(";
    return_string += String::num(vec->x);
    return_string += ", ";
    return_string += String::num(vec->y);
    return_string += ")";
    print_line(return_string);
}
// ============================================================
