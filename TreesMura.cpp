#include <iostream>

using data_t = int;

struct Node {
  data_t data;
  Node* left;
  Node* right;
};

using TTree = Node*;

using namespace std;

// void init(TTree& root) { root = nullptr; }

TTree insert(TTree& root, data_t key) {
  if (!root) {
    TTree temp = new Node;
    temp->data = key;
    temp->left = nullptr;
    temp->right = nullptr;
    root = temp;
    return temp;
  }

  if (key > root->data) {
    root->right = insert(root->right, key);
  } else if (key < root->data) {
    root->left = insert(root->left, key);
  }

  return root;
}

void view(TTree root) {
  if (!root) {
    return;
  }
  view(root->left);
  cout << root->data << " ";
  view(root->right);
}

// amount of leafs in BST tree
int getLeafs(TTree root) {
  if (!root) return 0;
  if (!root->right && !root->left) return 1;
  return getLeafs(root->right) + getLeafs(root->left);
}

// amount of nodes in BST tree
void getCount(TTree root, int& cnt) {
  if (root) {
    cnt++;
    getCount(root->left, cnt);
    getCount(root->right, cnt);
  }
}

// amount of nodes in BST tree (recursive)
int getCount(TTree root) {
  if (!root) return 0;
  return getCount(root->right) + getCount(root->left) + 1;
}

// the height of BST tree
int getHeight(TTree root) {
  if (!root) return 0;
  return max(getHeight(root->left), getHeight(root->right)) + 1;
}

// checks if BST tree is balanced( height of left subtree is equal to the height
// or right subtree or +1 )
bool isBalanced(TTree root) {
  if (!root) return true;
  return isBalanced(root->right) && isBalanced(root->left) &&
         (abs(getHeight(root->left) - getHeight(root->right)) <= 1);
}

int main() {
  TTree root = nullptr;

  int count, input, nodes = 0;
  cin >> count;
  for (size_t i = 0; i < count; i++) {
    cin >> input;
    insert(root, input);
  }
  cout << endl;
  view(root);
  cout << endl;
  cout << getLeafs(root);

  getCount(root, nodes);
  cout << endl << nodes << " --- " << getCount(root);

  cout << endl << getHeight(root);

  cout << endl << isBalanced(root);
}
