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
}