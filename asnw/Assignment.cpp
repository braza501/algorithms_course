// Binary Search Tree with UNIQUE keys


// for testing only
// Returns total number of created Nodes
// Can be useful to find memory leaks
#include <iostream>
#include <cassert>

using namespace std;

class CBinarySearchTree {
    struct Node;
public:


    // default constructor
    CBinarySearchTree() {
        root = nullptr;
    }
    ~CBinarySearchTree(){
        DeleteAll();
    }

    void Add(int newKey, int newValue);

    // Checks if key presented in array
    bool Has(int keyToCheck) const;

    // Deletes key from the tree
    // Returns true if deleted
    // Cost in your mark 2 times bigger!!
    bool Delete(int keyToDelete);

    // Get value for key
    // if key is not in tree - assert
    int &operator[](int keyToFind);

    const int &operator[](int keyToFind) const;

    // Returns size of tree
    int Size() const {
        return count;
    }

    // Returns if tree is empty
    bool IsEmpty() const { return count == 0; };

    // Deletes all tree elements
    void DeleteAll();

    // Returns max depth of tree
    int MaxDepth() const;

private:
    Node *FindMin(Node *x);

    bool get(int key) const;

    void DeleteAll(Node *x);

    Node *get(Node *x, int) const;

    Node *put(Node *x, int key, int val);

    Node *Delete(Node *x, int key);

    int MaxDepth(Node *x) const;

    struct Node {
        Node *left = nullptr;
        Node *right = nullptr;
        int key;
        int value;

        Node(int _key, int _value) : key(_key), value(_value) {}

    };

    int count = 0;
    Node *root;
};

CBinarySearchTree::Node *CBinarySearchTree::put(Node *x, int key, int val) {
    if (x == nullptr) {
        count++;
        return new Node(key, val);

    }
    if (key < x->key) x->left = put(x->left, key, val);
    else if (key > x->key) x->right = put(x->right, key, val);
    else x->value = val;
    return x;
}

void CBinarySearchTree::Add(int newKey, int newValue) {
    root = put(root, newKey, newValue);
}

void TestBinarySearchTree();

bool CBinarySearchTree::get(int key) const {
    Node *x = get(root, key);
    if (x == nullptr) return false;
    else return true;
}

CBinarySearchTree::Node *CBinarySearchTree::get(Node *x, int key) const {
    if (x == nullptr) return nullptr;
    if (key < x->key) return get(x->left, key);
    else if (key > x->key) return get(x->right, key);
    else return x;
}

bool CBinarySearchTree::Has(int keyToCheck) const {
    return get(keyToCheck);
}

const int &CBinarySearchTree::operator[](int keyToFind) const {
    Node *x = get(root, keyToFind);
    assert(x != nullptr);
    return x->value;
}

int &CBinarySearchTree::operator[](int keyToFind) {
    Node *x = get(root, keyToFind);
    assert(x != nullptr);
    return x->value;
}

void CBinarySearchTree::DeleteAll() {
    DeleteAll(root);
    count = 0;
    root = nullptr;
}

void CBinarySearchTree::DeleteAll(Node *x) {
    if (x != nullptr) {
        DeleteAll(x->left);
        DeleteAll(x->right);
        delete x;
    }
}

CBinarySearchTree::Node *CBinarySearchTree::FindMin(Node *x) {
    while (x->left != nullptr) {
        x = x->left;
    }
    return x;
}

CBinarySearchTree::Node *CBinarySearchTree::Delete(Node *x, int key) {
    if (x == nullptr) return x;
    else if (key < x->key) x->left = Delete(x->left, key);
    else if (key > x->key) x->right = Delete(x->right, key);
    else {
        if (x->left == nullptr && x->right == nullptr) {
            delete x;
            x = nullptr;

        } else if (x->left == nullptr) {
            Node *temp = x;
            x = x->right;
            delete temp;
        } else if (x->right == nullptr) {
            Node *temp = x;
            x = x->left;
            delete temp;
        } else {
            Node *temp = FindMin(x->right);
            x->key = temp->key;
            x->right = Delete(x->right, temp->key);
        }
    }
    return x;
}

bool CBinarySearchTree::Delete(int keyToDelete) {
    if (!(Has(keyToDelete))) return false;
    root = Delete(root, keyToDelete);
    count--;
    return true;
}

int CBinarySearchTree::MaxDepth(Node *x) const {
    if (x == nullptr)
        return 0;
    else {
        int left = MaxDepth(x->left);
        int right = MaxDepth(x->right);


        if (left > right)
            return (left + 1);
        else return (right + 1);
    }
}
int CBinarySearchTree::MaxDepth() const {
    return MaxDepth(root);
}

void TestBinarySearchTree(){
    CBinarySearchTree tree;
    tree.Add(3, 7);
    tree.Add(4, 2);
    cout << tree.Size() << endl;
    cout << tree.Has(5) << endl;
    cout << tree[3] << endl;
    //tree.DeleteAll();
    tree.Add(5, 777);
    cout << tree.Delete(5) << endl;
}

int main() {

    TestBinarySearchTree()
        CBinarySearchTree tree;

    return 0;
}