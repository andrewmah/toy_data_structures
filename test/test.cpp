#include "gtest/gtest.h"

#include "../src/splay_tree.h"

TEST(SplayTree, insert_1) {
    SplayTree* tree = new SplayTree();
    for (int i=0; i<8; i++) {
        tree->insert(i);
    }

    EXPECT_EQ(tree->preorder(), "7 6 5 4 3 2 1 0 ");
    EXPECT_EQ(tree->inorder(), "0 1 2 3 4 5 6 7 ");
    EXPECT_EQ(tree->breadth_first(), "7 6 5 4 3 2 1 0 ");
}

TEST(SplayTree, insert_2) {
    SplayTree* tree = new SplayTree();
    for (int i=0; i<4; i++) {
        tree->insert(i);
        tree->insert(7-i);
    } 
    EXPECT_EQ(tree->preorder(), "4 3 2 1 0 5 6 7 ");
    EXPECT_EQ(tree->inorder(), "0 1 2 3 4 5 6 7 ");
    EXPECT_EQ(tree->breadth_first(), "4 3 5 2 6 1 7 0 ");
}

TEST(SplayTree, find_1) {
    SplayTree* tree = new SplayTree();
    for (int i=0; i<8; i++) {
        tree->insert(i);
    } 
    EXPECT_TRUE(tree->find(0));
    EXPECT_TRUE(tree->find(4));

    EXPECT_EQ(tree->preorder(), "4 0 3 1 2 7 5 6 ");
    EXPECT_EQ(tree->inorder(), "0 1 2 3 4 5 6 7 ");
    EXPECT_EQ(tree->breadth_first(), "4 0 7 3 5 1 6 2 ");
}

TEST(SplayTree, find_2) {
    SplayTree* tree = new SplayTree();
    for (int i=0; i<8; i++) {
        tree->insert(i);
    } 
    EXPECT_FALSE(tree->find(-1));
    EXPECT_FALSE(tree->find(8));

    EXPECT_EQ(tree->preorder(), "7 0 5 3 1 2 4 6 ");
    EXPECT_EQ(tree->inorder(), "0 1 2 3 4 5 6 7 ");
    EXPECT_EQ(tree->breadth_first(), "7 0 5 3 6 1 4 2 ");
}

TEST(SplayTree, remove_1) {
    SplayTree* tree = new SplayTree();
    for (int i=0; i<8; i++) {
        tree->insert(i);
    } 
    tree->remove(5);
    tree->remove(6);
    tree->remove(3);

    EXPECT_EQ(tree->preorder(), "2 1 0 4 7 ");
    EXPECT_EQ(tree->inorder(), "0 1 2 4 7 ");
    EXPECT_EQ(tree->breadth_first(), "2 1 4 0 7 ");
}

TEST(SplayTree, remove_2) {
    SplayTree* tree = new SplayTree();
    for (int i=0; i<8; i++) {
        tree->insert(i);
    } 
    tree->remove(-1);
    tree->remove(8);

    EXPECT_EQ(tree->preorder(), "7 0 5 3 1 2 4 6 ");
    EXPECT_EQ(tree->inorder(), "0 1 2 3 4 5 6 7 ");
    EXPECT_EQ(tree->breadth_first(), "7 0 5 3 6 1 4 2 ");
}

TEST(SplayTree, remove_3) {
    SplayTree* tree = new SplayTree();
    tree->insert(1);
    tree->insert(-1);
    tree->insert(4);
    tree->insert(10);
    tree->insert(3);
    tree->remove(-1);

    EXPECT_EQ(tree->preorder(), "1 3 4 10 ");
    EXPECT_EQ(tree->inorder(), "1 3 4 10 ");
    EXPECT_EQ(tree->breadth_first(), "1 3 4 10 ");
}



TEST(SplayTree, large) {
    SplayTree* tree = new SplayTree();
    for (int i=0; i<(1<<16); i++) {
        tree->insert(i);
    } 
    
    tree->remove(12345);
    tree->remove(27951);
    tree->remove(19344);

    EXPECT_TRUE(tree->find(54321));
    EXPECT_FALSE(tree->find(12345));

    std::string str;
    for (int i=0; i<(1<<16); i++) {
        if (i != 12345 && i != 27951 && i != 19344) {
            str.append(std::to_string(i) + " ");
        }
    }
    EXPECT_EQ(tree->inorder(), str);  
}

// TEST(SplayTree, insert_2) {
//     EXPECT_EQ(0,0);
// }

// TEST(SplayTree, find) {
//     EXPECT_EQ(0,0);
// }

// TEST(SplayTree, erase) {
//     EXPECT_EQ(0,0);
// }

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


