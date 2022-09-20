#include <iostream>
#include "SplayTree.h"

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
        Node* inserted_node = _insert(key, root);
        splay(inserted_node);
    } else {
        root = new Node;
        root->key = key;
        root->left = nullptr;
        root->right = nullptr;
        root->parent = nullptr;
    }
}

Node* SplayTree::_insert(int key, Node* leaf) {
    if (key < leaf->key) {
        if (leaf->left != nullptr) {
            _insert(key, leaf->left);
        } else {
            leaf->left = new Node;
            leaf->left->key = key;
            leaf->left->left = nullptr;
            leaf->left->right = nullptr;
            leaf->left->parent = leaf;
            return leaf->left;
        }
    } else {
        if (leaf->right != nullptr) {
            _insert(key, leaf->right);
        } else {
            leaf->right = new Node;
            leaf->right->key = key;
            leaf->right->left = nullptr;
            leaf->right->right = nullptr;
            leaf->right->parent = leaf;
            return leaf->right;
        }
    }
    return nullptr;
}

bool SplayTree::find(int key) {
    Node* node = _find(key, root);
    splay(node);
    return node != nullptr;
}

Node* SplayTree::_find(int key, Node* leaf) {
    if (leaf == nullptr || key == leaf->key) {
        return leaf;
    }

    if (key < leaf->key) {
        return _find(key, leaf->left);
    } else {
        return _find(key, leaf->right);
    }
}

void SplayTree::print(void) {
    _print(root, "", false, false);
}

void SplayTree::_print(Node* leaf, const std::string& prefix, bool is_left, bool has_sibling) {
    if (leaf != nullptr) {
        std::cout << prefix;
        std::cout << (is_left ? "├──" : "└──" );
        std::cout << leaf->key << std::endl;
        
        _print(leaf->left, prefix + (is_left ? "│  " : "   "), true, leaf->right != nullptr);
        _print(leaf->right, prefix + (is_left ? "│  " : "   "), false, leaf->left != nullptr);
    } else if (has_sibling) {
        std::cout << prefix;
        std::cout << (is_left ? "├──" : "└──" );
        std::cout << "X" << std::endl;
    }
}






// Splay tree rotations
void SplayTree::zig(Node* leaf) {
    // TODO what to do about duplicate keys
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
    Node* ggparent = grandparent->parent;

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
        leaf->right = parent;
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
        leaf->left = parent;
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

void SplayTree::splay(Node* leaf) {
    while (leaf != root) {
        if (leaf->parent == root) {
            zig(leaf);
        } else if (leaf->key < leaf->parent->key == leaf->parent->key < leaf->parent->parent->key) {
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
    Node* z = _find(key, root);
    splay(z);

    SplayTree* high = new SplayTree();
    high->root = z->right;
    if (high->root != nullptr) {
        high->root->parent = nullptr;
    }

    z->right = nullptr;
    return high;
}

void SplayTree::join(SplayTree* high) {
    Node* z = subtree_max(root);
    splay(z);
    z->right = high->root;
    if (z->right != nullptr) {
        z->right->parent = z;
    }
}


void SplayTree::erase(int key) {
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
