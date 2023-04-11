#include <iostream>

// 节点颜色 openai 写的代码
enum Color {
    RED,
    BLACK
};

// 红黑树节点
class RBNode {
public:
    RBNode(int value, Color color = Color::RED) {
        this->value = value;
        this->color = color;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }

    int value;
    Color color;
    RBNode* left;
    RBNode* right;
    RBNode* parent;
};

// 红黑树
class RBTree {
public:
    // 初始化根节点
    RBTree() {
        root = nullptr;
    }

    // 释放内存
    ~RBTree() {
        destroy(root);
    }

    // 查找
    RBNode* search(int value) {
        RBNode* node = root;
        while (node != nullptr && node->value != value) {
            if (node->value > value) {
                node = node->left;
            } else {
                node = node->right;
            }
        }
        return node;
    }

    // 插入
    void insert(int value) {
        RBNode* node = new RBNode(value);
        insert(node);
    }

    // 删除
    void remove(int value) {
        RBNode* node = search(value);
        remove(node);
    }

    // 中序遍历
    void inorder_traversal() {
        inorder_traversal(root);
    }

private:
    RBNode* root;

    // 释放内存
    void destroy(RBNode* node) {
        if (node != nullptr) {
            destroy(node->left);
            destroy(node->right);
            delete node;
        }
    }

    // 左旋
    void rotate_left(RBNode* node) {
        RBNode* right = node->right;
        if (right == nullptr) {
            return;
        }
        RBNode* parent = node->parent;
        node->right = right->left;
        right->left = node;
        right->parent = parent;
        node->parent = right;
        if (parent != nullptr) {
            if (parent->left == node) {
                parent->left = right;
            } else {
                parent->right = right;
            }
        } else {
            root = right;
        }
        if (node->right != nullptr) {
            node->right->parent = node;
        }
    }

    // 右旋
    void rotate_right(RBNode* node) {
        RBNode* left = node->left;
        if (left == nullptr) {
            return;
        }
        RBNode* parent = node->parent;
        node->left = left->right;
        left->right = node;
        left->parent = parent;
        node->parent = left;
        if (parent != nullptr) {
            if (parent->left == node) {
                parent->left = left;
            } else {
                parent->right = left;
            }
        } else {
            root = left;
        }
        if (node->left != nullptr) {
            node->left->parent = node;
        }
    }

    // 插入
    void insert(RBNode* node) {
        RBNode* parent = nullptr;
        RBNode* temp = root;
        while (temp != nullptr) {
            parent = temp;
            if (node->value < temp->value) {
                temp = temp->left;
            } else {
                temp = temp->right;
            }
        }
        node->parent = parent;
        if (parent == nullptr) {
            root = node;
        } else if (node->value < parent->value) {
            parent->left = node;
        } else {
            parent->right = node;
        }
        insert_fixup(node);
    }

    // 插入修复
    void insert_fixup(RBNode* node) {
        while (node != root && node->parent->color == Color::RED) {
            RBNode* parent = node->parent;
            RBNode* grandparent = parent->parent;
            if (parent == grandparent->left) {
                RBNode* uncle = grandparent->right;
                if (uncle != nullptr && uncle->color == Color::RED) {
                    parent->color = Color::BLACK;
                    uncle->color = Color::BLACK;
                    grandparent->color = Color::RED;
                    node = grandparent;
                } else {
                    if (node == parent->right) {
                        node = parent;
                        rotate_left(node);
                    }
                    parent->color = Color::BLACK;
                    grandparent->color = Color::RED;
                    rotate_right(grandparent);
                }
            } else {
                RBNode* uncle = grandparent->left;
                if (uncle != nullptr && uncle->color == Color::RED) {
                    parent->color = Color::BLACK;
                    uncle->color = Color::BLACK;
                    grandparent->color = Color::RED;
                    node = grandparent;
                } else {
                    if (node == parent->left) {
                        node = parent;
                        rotate_right(node);
                    }
                    parent->color = Color::BLACK;
                    grandparent->color = Color::RED;
                    rotate_left(grandparent);
                }
            }
        }
        root->color = Color::BLACK;
    }

    // 删除
    void remove(RBNode* node) {
        if (node == nullptr) {
            return;
        }
        // 如果删除的节点有两个儿子，则用中序遍历的后继节点替代该节点
        if (node->left != nullptr && node->right != nullptr) {
            RBNode* temp = node->right;
            while (temp->left != nullptr) {
                temp = temp->left;
            }
            node->value = temp->value;
            node = temp;
        }
        RBNode* child = (node->left != nullptr ? node->left : node->right);
        if (child != nullptr) {
            child->parent = node->parent;
        }
        if (node->parent == nullptr) {
            root = child;
        } else if (node == node->parent->left) {
            node->parent->left = child;
        } else {
            node->parent->right = child;
        }
        if (node->color == Color::BLACK) {
            remove_fixup(child, node->parent);
        }
        delete node;
    }

    // 删除修复
    void remove_fixup(RBNode* node, RBNode* parent) {
        while ((node == nullptr || node->color == Color::BLACK) && node != root) {
            if (node == parent->left) {
                RBNode* sibling = parent->right;
                if (sibling->color == Color::RED) {
                    sibling->color = Color::BLACK;
                    parent->color = Color::RED;
                    rotate_left(parent);
                    sibling = parent->right;
                }
                if ((sibling->left == nullptr || sibling->left->color == Color::BLACK) &&
                    (sibling->right == nullptr || sibling->right->color == Color::BLACK)) {
                    sibling->color = Color::RED;
                    node = parent;
                    parent = node->parent;
                } else {
                    if (sibling->right == nullptr || sibling->right->color == Color::BLACK) {
                        sibling->left->color = Color::BLACK;
                        sibling->color = Color::RED;
                        rotate_right(sibling);
                        sibling = parent->right;
                    }
                    sibling->color = parent->color;
                    parent->color = Color::BLACK;
                    sibling->right->color = Color::BLACK;
                    rotate_left(parent);
                    node = root;
                    break;
                }
            } else {
                RBNode* sibling = parent->left;
                if (sibling->color == Color::RED) {
                    sibling->color = Color::BLACK;
                    parent->color = Color::RED;
                    rotate_right(parent);
                    sibling = parent->left;
                }
                if ((sibling->left == nullptr || sibling->left->color == Color::BLACK) &&
                    (sibling->right == nullptr || sibling->right->color == Color::BLACK)) {
                    sibling->color = Color::RED;
                    node = parent;
                    parent = node->parent;
                } else {
                    if (sibling->left == nullptr || sibling->left->color == Color::BLACK) {
                        sibling->right->color = Color::BLACK;
                        sibling->color = Color::RED;
                        rotate_left(sibling);
                        sibling = parent->left;
                    }
                    sibling->color = parent->color;
                    parent->color = Color::BLACK;
                    sibling->left->color = Color::BLACK;
                    rotate_right(parent);
                    node = root;
                    break;
                }
            }
        }
        if (node != nullptr) {
            node->color = Color::BLACK;
        }
    }

    // 中序遍历
    void inorder_traversal(RBNode* node) {
        if (node != nullptr) {
            inorder_traversal(node->left);
            std::cout << node->value << " ";
            inorder_traversal(node->right);
        }
    }
};

int main() {
    RBTree tree;

    tree.insert(5);
    tree.insert(8);
    tree.insert(1);
    tree.insert(6);
    tree.insert(4);
    tree.insert(9);
    tree.insert(2);

    tree.inorder_traversal();
    std::cout << std::endl;

    tree.remove(6);
    tree.remove(9);

    tree.inorder_traversal();
    std::cout << std::endl;

    return 0;
}
