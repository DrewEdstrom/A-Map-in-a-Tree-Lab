#ifndef SPLAYTREE_H_INC
#define SPLAYTREE_H_INC

#include <string>

template <typename T>
class SplayTree
{
    private:
    class Node
    {
        public:

        //the data/object stored at the node
        T element;
        //the pointers to the left child, right child, and parent of the
        //node
        Node *left, *right, *parent;

        Node(T new_elem)
        :
        element{new_elem},
        left{nullptr},
        right{nullptr},
        parent{nullptr}
        {
        }

        Node(T new_elem, Node *new_left, Node *new_right, Node *new_parent)
        :
        element{new_elem},
        left{new_left},
        right{new_right},
        parent{new_parent}
        {
        }

        //copy constructor
        Node(Node const&node)
        :
        Node(node.element, node.left, node.right, node.parent)
        {
        }

        //assignment operator overload
        Node& operator=(Node const&node) 
        {
            //avoid double assignment
            if (this == &node) 
            {
                return *this;
            }

            //copy each part of node
            element = node.element;
            parent = node.parent;
            left = node.left;
            right = node.right;

            //update parents of child nodes if necessary
            if(left != nullptr)
            {
                left->parent = this;
            }

            if(right != nullptr) 
            {
                right->parent = this;
            }
            
            return *this;
        }
    };

    private:

    //the root node of the SplayTree
    Node *root;

    public:

    SplayTree()
    :
    root{nullptr}
    {
    }

    //create a SplayTree with a pre-existing root node
    SplayTree(Node *new_root)
    :
    root{new_root}
    {
    }

    //copy constructor
    SplayTree(SplayTree const&tree)
    :
    SplayTree(tree.root)
    {
    }

    //assignment operator overload
    SplayTree& operator=(SplayTree const&tree) 
    {
        //avoid double assignment
        if (this == &tree) 
        {
            return *this;
        }

        //copy each part of tree
        root = tree.root;
        
        return *this;
    }

    //destructor
    ~SplayTree()
    {
        delete root;
        root = nullptr;
    }

    //inserts a given element into the SplayTree
    void insert(T new_elem)
    {
        //if no root exists, create one
        if(root == nullptr)
        {
            root = new Node(new_elem);
        }
        else
        {
            //what is to become the parent of a newly inserted node
            Node *parent_node{find(new_elem, root)};

            //if element already exists in tree, no insertion occurs
            if(new_elem == parent_node->element)
            {
                return;
            }
            //if element comes before the element at the parent node, place
            //as left child
            else if(new_elem < parent_node->element)
            {
                parent_node->left = new Node(new_elem);
                parent_node->left->parent = parent_node;
                root = splay(root, parent_node->left->element);
            }
            //otherwise place as right child
            else
            {
                parent_node->right = new Node(new_elem);
                parent_node->right->parent = parent_node;
                root = splay(root, parent_node->right->element);
            }
        }

        
    }

    //removes a given element from the SplayTree
    void remove(T elem)
    {
        //if tree is empty, no removal occurs
        if(root == nullptr)
        {
            return;
        }

        //the node that contains elem, or where the search for it terminates
        Node *n_to_rm{find(elem, root)};

        //element not found, no remove operation is performed
        if(n_to_rm == nullptr || n_to_rm->element != elem)
        {
            root = splay(root, n_to_rm->element);
            return;
        }
    
        //splay the node to be removed to the root first
        root = splay(root, elem);
        n_to_rm = root; //now n_to_rm is the root
    
        //node has no children, simply remove it
        if(n_to_rm->left == nullptr && n_to_rm->right == nullptr)
        {
            delete n_to_rm;
            root = nullptr;
        }
        //node has one child, update various pointers and then remove
        else if(n_to_rm->left == nullptr || n_to_rm->right == nullptr)
        {
            root = n_to_rm->left != nullptr ? n_to_rm->left : n_to_rm->right;
            root->parent = nullptr;
            delete n_to_rm;
        }
        //node has two children
        else
        {
            //split the tree
            Node *left_subtree = n_to_rm->left;
            Node *right_subtree = n_to_rm->right;
        
            //detach left subtree from root
            left_subtree->parent = nullptr;
        
            //find the largest element in the left subtree
            Node *max_node = left_subtree;

            while(max_node->right != nullptr) 
            {
                max_node = max_node->right;
            }
        
            //splay this node to the root of left subtree
            root = splay(left_subtree, max_node->element);
        
            //connect right subtree to the right of the new root
            root->right = right_subtree;

            if(right_subtree != nullptr) 
            {
                right_subtree->parent = root;
            }
        
            //delete the original node
            delete n_to_rm;
        }
    }

    //returns the node containing elem if found, otherwise returns the node
    //accessed before search terminated
    Node* find(T elem, Node *cur_node)
    {
        //protect against attempting to access a nullptr
        if(cur_node == nullptr)
        {
            return nullptr;
        }
        //terminate search if element is found or a leaf is reached
        else if((cur_node->left == nullptr && elem < cur_node->element)
        || (cur_node->right == nullptr && elem > cur_node->element)
        || (cur_node->element == elem))
        {
            return cur_node;
        }
        //move left if the element is less than the element at the current
        //node
        else if(elem < cur_node->element)
        {
            cur_node = cur_node->left;
        }
        //move right if the element is greater than the element at the
        //current node
        else
        {
            cur_node = cur_node->right;
        }

        return find(elem, cur_node);
    }

    //performs a right rotation on a given node, x
    Node* rotate_right(Node *x)
    {
        //right rotation
        Node *y = x->left;
        x->left = y->right;
    
        //update parent of newly rotated node if it exists
        if(x->left != nullptr) 
        {
            x->left->parent = x;
        }
    
        //update parents of each node
        y->right = x;
        y->parent = x->parent;
        x->parent = y;
    
        return y;
    }

    //performs a left rotation of a given node, x
    Node* rotate_left(Node *x)
    {
        //left rotation
        Node *y = x->right;
        x->right = y->left;
    
        //update parent of newly rotated node if it exists
        if(x->right != nullptr) 
        {
            x->right->parent = x;
        }
    
        //update parents of newly rotated nodes
        y->left = x;
        y->parent = x->parent;
        x->parent = y;
    
        return y;
    }

    //finds a given element and returns it if found, or returns the last
    //element accessed before search terminated
    T find(T elem)
    {
        //the node resulting from a search for an element
        Node *node{find(elem, root)};

        root = splay(root, elem);

        return node->element;
    }

    //splays the tree until root is updated
    Node* splay(Node *rt, T key)
    {
        if(rt == nullptr || rt->element == key) 
        {
            return rt;
        }
    
        if(key < rt->element) 
        {
            if(rt->left == nullptr) 
            {
                return rt;
            }
            
            if(key < rt->left->element) 
            {
                // zig-zig case
                rt->left->left = splay(rt->left->left, key);
                rt = rotate_right(rt);
            }
            else if(key > rt->left->element) 
            {
                // zig-zag case
                rt->left->right = splay(rt->left->right, key);

                if(rt->left->right != nullptr) 
                {
                    rt->left = rotate_left(rt->left);
                }
            }
            
            if(rt->left == nullptr) 
            {
                return rt;
            }
            
            return rotate_right(rt);
        }
        // key > root->element
        else 
        { 
            if(rt->right == nullptr) 
            {
                return rt;
            }
            
            if(key > rt->right->element) 
            {
                // zag-zag case
                rt->right->right = splay(rt->right->right, key);
                rt = rotate_left(rt);
            }
            else if(key < rt->right->element) 
            {
                // zag-zig case
                rt->right->left = splay(rt->right->left, key);
                
                if(rt->right->left != nullptr) 
                {
                    rt->right = rotate_right(rt->right);
                }
            }
            
            if(rt->right == nullptr) 
            {
                return rt;
            }
            
            return rotate_left(rt);
        }
        
    }

//serializes the SplayTree using an in-order traversal
std::string serialize()
{
    return serialize_helper(root);
}

//helper function for serialize()
std::string serialize_helper(Node *node)
{
    if(node == nullptr)
    {
        return "nil";
    }

    std::string left_serialized{serialize_helper(node->left) + ","};
    std::string right_serialized{serialize_helper(node->right)};

    return (node->element).to_string() + "," + left_serialized + right_serialized;
}

};

#endif
