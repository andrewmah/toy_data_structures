struct Node {
    int key;
    Node* left;
    Node* right;
    Node* parent;
};

class SplayTree
{
    public: 
        SplayTree();
        ~SplayTree();

        /// @brief Add new item to tree and splay to root
        /// @param key to be added
        void insert(int key);

        /// @brief Search for item in tree and splay to root
        /// @param key to be searched for
        /// @return true if key is in the tree otherwise false
        bool find(int key);

        /// @brief Splay item to root and delete from tree
        /// @param key to be deleted
        void erase(int key);

        /// @brief Display the tree structure on the console
        void print();
    
    private:
        Node* root;

        void _destroy_tree(Node *leaf);
        Node* _insert(int key, Node* leaf);
        Node* _find(int key, Node* leaf);
        void _print(Node* leaf, const std::string& prefix, bool is_left, bool has_sibling);

        // tree rotations
        void zig(Node* leaf);
        void zig_zig(Node* leaf);
        void zig_zag(Node* leaf);

        void splay(Node* leaf);

        Node* max(void);
        Node* min(void);

        SplayTree* split(int key);
        void join(SplayTree*);

        
};