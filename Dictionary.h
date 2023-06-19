#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <string>

class Dictionary {
private:
	class Node {
	public:
		explicit Node(const std::string& word);

		std::string word;
		int count;
		Node* left;
		Node* right;
		int height;
	};
public:
	Dictionary();
	void insert(const std::string& word);
	int getCount(const std::string& word);

private:
	Node* root_;

	Node* insertNode(Node* node, const std::string& word);
	Node* rotateRight(Node* node);
	Node* rotateLeft(Node* node);
	int getHeight(Node* node);
	int getBalance(Node* node);
};

#endif