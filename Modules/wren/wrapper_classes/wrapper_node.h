/* wrapper_node.h */

#ifndef WRAPPER_NODE_H
#define WRAPPER_NODE_H

#include "scene/main/node.h"
#include "../wren_manager.h"

class Wrapper_Node {

public:
    Wrapper_Node();
    Wrapper_Node(Node* default_ref);
    ~Wrapper_Node();

    Node* node_reference;
    void set_node_reference(Node* new_ref);
    Node* get_node_reference();
};

#endif // WRAPPER_NODE_H