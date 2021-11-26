#include "wrapper_node2d.h"

Wrapper_Node2D::Wrapper_Node2D()
{
    node_reference = nullptr;
}
Wrapper_Node2D::Wrapper_Node2D(Node2D* default_ref)
{
    node_reference = default_ref;
}
Wrapper_Node2D::~Wrapper_Node2D()
{

}

void Wrapper_Node2D::set_node_reference(Node2D* new_ref)
{
    // TODO - remove old reference node?
    /*
    if (node_reference != nullptr)
    {
        if (node_reference->is_inside_tree() == false)
        {
            node_reference->queue_delete();
        }
    }
    */
    node_reference = new_ref;
}
Node2D* Wrapper_Node2D::get_node_reference()
{
    return node_reference;
}


void Wrapper_Node2D::set_node_reference_from_node(Wrapper_Node* new_ref)
{
    if (new_ref->node_reference == nullptr)
    {
        print_error("Cannot cast Node due to node reference not pointing to valid node!");
        return;
    }

    Node2D* cast = Object::cast_to<Node2D>(new_ref->node_reference);

    if (cast != NULL)
    {
        set_node_reference(cast);
    }
    else
    {
        print_error("Cannot cast Node with name: " + new_ref->node_reference->get_name() + " to Node2D!");
    }
}
Node* Wrapper_Node2D::get_node_reference_as_node()
{
    return Object::cast_to<Node>(node_reference);
}