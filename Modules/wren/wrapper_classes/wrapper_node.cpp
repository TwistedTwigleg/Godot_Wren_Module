#include "wrapper_node.h"

Wrapper_Node::Wrapper_Node()
{
    node_reference = nullptr;
}
Wrapper_Node::Wrapper_Node(Node* default_ref)
{
    node_reference = default_ref;
}
Wrapper_Node::~Wrapper_Node()
{

}

void Wrapper_Node::set_node_reference(Node* new_ref)
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
Node* Wrapper_Node::get_node_reference()
{
    return node_reference;
}