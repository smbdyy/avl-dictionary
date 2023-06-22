#ifndef AVLDICTIONARY_DICTIONARY_H
#define AVLDICTIONARY_DICTIONARY_H

#include <string>
#include <map>

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
    void deleteWord(const std::string& word);
	[[nodiscard]] int getCount(const std::string& word) const;
    [[nodiscard]] std::map<std::string, int> getTable() const;
    [[nodiscard]] int getUniqueWordsCount() const;

private:
	Node* root_;
    int uniqueWordsCount_;

	Node* insertNode(Node* node, const std::string& word);
    Node* deleteNode(Node* node, const std::string& word);
    static Node* findMin(Node* node) ;
    static void addWordToTable(std::map<std::string, int>& table, Node* node);
	static Node* rotateRight(Node* node);
	static Node* rotateLeft(Node* node);
	static int getHeight(Node* node);
	static int getBalance(Node* node);
};

#endif