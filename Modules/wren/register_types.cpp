#include "register_types.h"

#include "core/class_db.h"
#include "wren_manager.h"

void register_wren_types() {
    ClassDB::register_class<WrenManager>();
}

void unregister_wren_types() {
   // Nothing to do here in this example.
}