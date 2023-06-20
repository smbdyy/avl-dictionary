#ifndef AVLDICTIONARY_DICTIONARY_H
#define AVLDICTIONARY_DICTIONARY_H

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
	static Node* rotateRight(Node* node);
	static Node* rotateLeft(Node* node);
	static int getHeight(Node* node);
	static int getBalance(Node* node);
};

#endif