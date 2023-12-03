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

// counts amount of nodes on the fixed level of the tree
int countElemOnLevel(TTree root, int level, int current_level) {
  if (!root)
    return 0;
  else {
    if (level == current_level) return 1;
    return countElemOnLevel(root->right, level, current_level + 1) +
           countElemOnLevel(root->left, level, current_level + 1);
  }
}

// -------------------------------- HOMEWORK -------------------------------- \\

// HW-1.1
// find absolute maximum of a tree
data_t findAbsMax(TTree root) {
  if (!root) return 0;
  return max(max(findAbsMax(root->right), findAbsMax(root->left)),
             abs(root->data));
}

void findAbsMax(TTree root, data_t& value) {
  if (!root) return;
  if (abs(root->data) > value) value = abs(root->data);
  findAbsMax(root->right, value);
  findAbsMax(root->left, value);
}

// HW-1.2
// find the value of rightmost leaf
bool isLeaf(TTree root) { return !root->left && !root->right; }

data_t rightLeaf(TTree root) {
  if (isLeaf(root)) return root->data;
  if (root->right)
    rightLeaf(root->right);
  else
    rightLeaf(root->left);
}

// HW-1.3
// create a special binary tree
void create(TTree& root, int n, int current) {
  if (current <= n) {
    root = new Node;
    root->data = current;
    root->right = nullptr;
    root->left = nullptr;
    current++;
    create(root->right, n, current);
    create(root->left, n, current);
  }
  return;
}

// ----------------------------- HOMEWORK END ----------------------------- \\

int main() {
  TTree root = nullptr;
  TTree test = nullptr;

  int count, input, nodes = 0, abs_max = INT_MIN;
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

  findAbsMax(root, abs_max);
  cout << endl << findAbsMax(root) << " --- " << abs_max;

  cout << endl << rightLeaf(root);

  cout << endl;
  int current = 1, n = 4;
  create(test, n, current);
  view(test);
}
