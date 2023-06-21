#include "Dictionary.h"

Dictionary::Node::Node(const std::string& word) {
    this->word = word;
    count = 1;
    left = nullptr;
    right = nullptr;
    height = 1;
}

Dictionary::Dictionary() {
    root_ = nullptr;
    uniqueWordsCount_ = 0;
}

std::map<std::string, int> Dictionary::getTable() const {
    std::map<std::string, int> table;
    addWordToTable(table, root_);

    return table;
}

void Dictionary::addWordToTable(std::map<std::string, int>& table, Node *node) {
    if (node == nullptr) return;

    std::string word = node->word;
    if (table.find(word) != table.end()) {
        table[word]++;
    }
    else {
        table[word] = 1;
    }

    addWordToTable(table, node->left);
    addWordToTable(table, node->left);
}

void Dictionary::insert(const std::string& word) {
    root_ = insertNode(root_, word);
}

Dictionary::Node* Dictionary::insertNode(Node* node, const std::string &word) {
    if (node == nullptr) {
        uniqueWordsCount_++;
        return new Node(word);
    }

    if (word < node->word) {
        node->left = insertNode(node->left, word);
    }
    else if (word > node->word) {
        node->right = insertNode(node->right, word);
    }
    else {
        node->count++;
        return node;
    }

    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

    int balance = getBalance(node);

    if (balance > 1 && word < node->left->word) {
        return rotateRight(node);
    }

    if (balance < -1 && word > node->right->word) {
        return rotateLeft(node);
    }

    if (balance > 1 && word > node->left->word) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && word < node->right->word) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

void Dictionary::deleteWord(const std::string& word) {
    if (getCount(word) == 0) return;
    root_ = deleteNode(root_, word);
    uniqueWordsCount_--;
}

Dictionary::Node* Dictionary::deleteNode(Node* node, const std::string& word) {
    if (node == nullptr) {
        return nullptr;
    }

    if (word < node->word) {
        node->left = deleteNode(node->left, word);
    }
    else if (word > node->word) {
        node->right = deleteNode(node->right, word);
    }
    else {
        Node* temp;
        if (node->left == nullptr) {
            temp = node->right;
        } else if (node->right == nullptr) {
            temp = node->left;
        } else {
            temp = node->right;
            while (temp->left != nullptr) {
                temp = temp->left;
            }
            node->word = temp->word;
            node->count = temp->count;
            node->right = deleteNode(node->right, temp->word);
        }
        delete node;
        return temp;
    }

    node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;

    int balance = getBalance(node);
    if (balance > 1 && getBalance(node->left) >= 0) {
        return rotateRight(node);
    }
    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balance < -1 && getBalance(node->right) <= 0) {
        return rotateLeft(node);
    }
    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

Dictionary::Node* Dictionary::rotateRight(Node* node) {
    Node* leftChild = node->left;
    Node* leftRightChild = leftChild->right;

    leftChild->right = node;
    node->left = leftRightChild;

    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    leftChild->height = 1 + std::max(getHeight(leftChild->left), getHeight(leftChild->right));

    return leftChild;
}

Dictionary::Node* Dictionary::rotateLeft(Node* node) {
    Node* rightChild = node->right;
    Node* rightLeftChild = rightChild->left;

    rightChild->left = node;
    node->right = rightLeftChild;

    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    rightChild->height = 1 + std::max(getHeight(rightChild->left), getHeight(rightChild->right));

    return rightChild;
}

int Dictionary::getHeight(Node* node) {
    if (node == nullptr) {
        return 0;
    }

    return node->height;
}

int Dictionary::getBalance(Node* node) {
    if (node == nullptr) {
        return 0;
    }

    return getHeight(node->left) - getHeight(node->right);
}

int Dictionary::getCount(const std::string& word) const {
    Node* current = root_;

    while (current != nullptr) {
        if (word == current->word) {
            return current->count;
        }

        if (word < current->word) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }

    return 0;
}

int Dictionary::getUniqueWordsCount() const {
    return uniqueWordsCount_;
}