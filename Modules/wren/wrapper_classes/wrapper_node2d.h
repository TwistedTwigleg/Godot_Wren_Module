/* wrapper_node2d.h */

#ifndef WRAPPER_NODE2D_H
#define WRAPPER_NODE2D_H

#include "scene/2d/node_2d.h"
#include "wrapper_node.h"

class Wrapper_Node2D {

public:
    Wrapper_Node2D();
    Wrapper_Node2D(Node2D* default_ref);
    ~Wrapper_Node2D();

    Node2D* node_reference;
    void set_node_reference(Node2D* new_ref);
    Node2D* get_node_reference();

    void set_node_reference_from_node(Wrapper_Node* new_ref);
    Node* get_node_reference_as_node();
};

#endif // WRAPPER_NODE2D_H