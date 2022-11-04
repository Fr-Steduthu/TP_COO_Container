#pragma once

#include "Node.h"

class WordTree {
public :
	WordTree() = default;
	~WordTree() = default;

	void add_word(const std::string&);

	bool word(const std::string&);

	friend int main(); //DBG
protected :

private :
	Node<char> root;
};