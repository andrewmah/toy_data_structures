#include <iostream>
#include <queue>

#include "splay_tree.h"

Node::Node(int key_param) {
    key = key_param;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
} 

SplayTree::SplayTree() {
    root = nullptr;
}

SplayTree::~SplayTree() {
    _destroy_tree(root);
}

void SplayTree::_destroy_tree(Node* leaf) {
    if (leaf != nullptr) {
        _destroy_tree(leaf->left);
        _destroy_tree(leaf->right);
        delete leaf;
    }
}

void SplayTree::insert(int key) {
    if (root != nullptr) {
        // TODO allow duplicate keys
        if (!find(key)) {
            Node* inserted_node = _insert(key, root);
            splay(inserted_node);
        } else {
            std::cout << "Duplicate keys not supported" << std::endl;
        }
    } else {
        root = new Node(key);
    }
}

Node* SplayTree::_insert(int key, Node* leaf) {
    if (key < leaf->key) {
        if (leaf->left != nullptr) {
            return _insert(key, leaf->left);
        } else {
            leaf->left = new Node(key);
            leaf->left->key = key;
            leaf->left->parent = leaf;
            return leaf->left;
        }
    } else {
        if (leaf->right != nullptr) {
            return _insert(key, leaf->right);   
        } else {
            leaf->right = new Node(key);
            leaf->right->parent = leaf;
            return leaf->right;
        }
    }
}

bool SplayTree::find(int key) {
    Node* node = _find(key, root);
    return node != nullptr;
}

Node* SplayTree::_find_no_splay(int key, Node* leaf, Node* &last_access) {
    if (leaf == nullptr || key == leaf->key) {
        return leaf;
    }

    last_access = leaf;
    if (key < leaf->key) {
        return _find_no_splay(key, leaf->left, last_access);
    } else {
        return _find_no_splay(key, leaf->right, last_access);
    }
}

Node* SplayTree::_find(int key, Node* leaf) {
    Node* last_access = root;
    Node* node = _find_no_splay(key, root, last_access);

    if (node == nullptr) {
        // if no node is found splay the last accessed node instead
        splay(last_access);
        return nullptr;
    } else {
        splay(node);
        return node;
    }
}








// Splay tree rotations
void SplayTree::zig(Node* leaf) {
    // TODO allow duplicate keys
    Node* parent = leaf->parent;
    Node* grandparent = parent->parent;

    if (leaf->key < parent->key) {
        // leaf is left child
        parent->left = leaf->right;
        if (parent->left != nullptr) {
            parent->left->parent = parent;
        }

        leaf->right = parent;
        if (leaf->right != nullptr) {
            leaf->right->parent = leaf;
        }
    } else {
        //leaf is right child
        parent->right = leaf->left;
        if (parent->right != nullptr) {
            parent->right->parent = parent;
        }

        leaf->left = parent;
        if (leaf->left != nullptr) {
            leaf->left->parent = leaf;
        }
    }

    leaf->parent = grandparent;
    if (grandparent != nullptr) {
        if (parent->key < grandparent->key) {
            // parent is left child
            grandparent->left = leaf;
        } else {
            // parent is right child
            grandparent->right = leaf;
        }
    } else {
        root = leaf;
    }
}

void SplayTree::zig_zig(Node* leaf) {
    Node* parent = leaf->parent;
    Node* grandparent = parent->parent;
    Node* ggparent = grandparent->parent;

    if (leaf->key < parent->key) {
        // leaf and parent are left children
        parent->left = leaf->right;
        if (parent->left != nullptr) {
            parent->left->parent = parent;
        }

        grandparent->left = parent->right;
        if (grandparent->left != nullptr) {
            grandparent->left->parent = grandparent;
        }

        leaf->right = parent;
        if (leaf->right != nullptr) {
            leaf->right->parent = leaf;
        }

        parent->right = grandparent;
        if (parent->right != nullptr) {
            parent->right->parent = parent;
        }
    } else {
        // leaf and parent are right children
        parent->right = leaf->left;
        if (parent->right != nullptr) {
            parent->right->parent = parent;
        }

        grandparent->right = parent->left;
        if (grandparent->right != nullptr) {
            grandparent->right->parent = grandparent;
        }

        leaf->left = parent;
        if (leaf->left != nullptr) {
            leaf->left->parent = leaf;
        }

        parent->left = grandparent;
        if (parent->left != nullptr) {
            parent->left->parent = parent;
        }
    }

    leaf->parent = ggparent;
    if (ggparent != nullptr) {
        if (grandparent->key < ggparent->key) {
            // parent is left child
            ggparent->left = leaf;
        } else {
            // parent is right child
            ggparent->right = leaf;
        }
    } else {
        root = leaf;
    }
}

void SplayTree::zig_zag(Node* leaf) {
    Node* parent = leaf->parent;
    Node* grandparent = parent->parent;
    Node* ggparent = grandparent->parent; //TODO error here if no ggparent

    if (leaf->key < parent->key) {
        // leaf is left child and parent is right child
        parent->left = leaf->right;
        if (parent->left != nullptr) {
            parent->left->parent = parent;
        }

        grandparent->right = leaf->left;
        if (grandparent->right != nullptr) {
            grandparent->right->parent = grandparent;
        }

        leaf->right = parent;
        leaf->right->parent = leaf;

        leaf->left = grandparent;
        leaf->left->parent = leaf;
    } else {
        // leaf is right child and parent is left child
        parent->right = leaf->left;
        if (parent->right != nullptr) {
            parent->right->parent = parent;
        }

        grandparent->left = leaf->right;
        if (grandparent->left != nullptr) {
            grandparent->left->parent = grandparent;
        }

        leaf->left = parent;
        leaf->left->parent = leaf;

        leaf->right = grandparent;
        leaf->right->parent = leaf;
    }

    leaf->parent = ggparent;
    if (ggparent != nullptr) {
        if (grandparent->key < ggparent->key) {
            // grandparent is left child
            ggparent->left = leaf;
        } else {
            // grandparent is right child
            ggparent->right = leaf;
        }
    } else {
        root = leaf;
    }
}

void SplayTree::splay(Node* leaf) {
    while (leaf != root) {
        if (leaf->parent == root) {
            zig(leaf);
        } else if ((leaf->key < leaf->parent->key) == (leaf->parent->key < leaf->parent->parent->key)) {
            zig_zig(leaf);  
        } else {
            zig_zag(leaf);
        }
    }
}

Node* subtree_min(Node* leaf) {
    Node* z = leaf;
    while (z->left != nullptr) {
        z = z->left;
    }
    return z;
}

Node* subtree_max(Node* leaf) {
    Node* z = leaf;
    while (z->right != nullptr) {
        z = z->right;
    }
    return z;
}

SplayTree* SplayTree::split(int key) {
    //[TODO allow to split on nonexistant key?]
    Node* z = _find(key, root);

    SplayTree* high = new SplayTree();
    high->root = z->right;
    if (high->root != nullptr) {
        high->root->parent = nullptr;
    }

    z->right = nullptr;
    return high;
}

void SplayTree::join(SplayTree* high) {
    if (root == nullptr) {
        root = high->root;
        return;
    }
    
    Node* z = subtree_max(root);
    splay(z);
    z->right = high->root;
    if (z->right != nullptr) {
        z->right->parent = z;
    }
}


void SplayTree::remove(int key) {
    if (!find(key)) {
        return;
    }

    SplayTree* high = split(key);

    Node* node = root;
    if (node->left != nullptr) {
        root = node->left;
        root->parent = nullptr;
    } else {
        root = nullptr;
    }
    delete node;

    join(high);
}



const void SplayTree::pretty_print(void) {
    _pretty_print(root, "", false, false);
}

const void SplayTree::_pretty_print(Node* leaf, const std::string& prefix, bool is_left, bool has_sibling) {
    if (leaf != nullptr) {
        std::cout << prefix;
        std::cout << (is_left ? "├──" : "└──" );
        std::cout << leaf->key << std::endl;
        //std::cout << leaf->key << "(" << (leaf->parent == nullptr ? -1 : leaf->parent->key) << ")" << std::endl;
        
        _pretty_print(leaf->left, prefix + (is_left ? "│  " : "   "), true, leaf->right != nullptr);
        _pretty_print(leaf->right, prefix + (is_left ? "│  " : "   "), false, leaf->left != nullptr);
    } else if (has_sibling) {
        std::cout << prefix;
        std::cout << (is_left ? "├──" : "└──" );
        std::cout << "X" << std::endl;
    }
}



const std::string SplayTree::preorder(void) {
    std::string str = "";
    _preorder(root, str);
    return str;
}

const void SplayTree::_preorder(Node* leaf, std::string& str) {
    if (leaf == nullptr) return;

    str = str + std::to_string(leaf->key) + " ";
    _preorder(leaf->left, str);
    _preorder(leaf->right, str);
}


const std::string SplayTree::inorder(void) {
    std::string str = "";
    _inorder(root, str);
    return str;
}

const void SplayTree::_inorder(Node* leaf, std::string& str) {
    if (leaf == nullptr) return;

    _inorder(leaf->left, str);
    str = str + std::to_string(leaf->key) + " ";
    _inorder(leaf->right, str);
}

const std::string SplayTree::breadth_first(void) {
    std::string str = "";
    std::queue<Node*> queue;
    queue.push(root);

    while (!queue.empty()) {
        Node* leaf = queue.front();
        queue.pop();

        if (leaf != nullptr) {
            str = str + std::to_string(leaf->key) + " ";
            queue.push(leaf->left);
            queue.push(leaf->right);
        } 
    }
    return str;
}


