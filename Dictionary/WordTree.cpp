#include "pch.h"
#include "WordTree.h"
#include <string>

//WordTree

void WordTree::add_word(const std::string& word) {
	Node<char> * node = &this->root;

	for (size_t index = 0; index != word.size(); ++index) {
		const char c = std::tolower(word.at(index));

		*node << std::move(Node<char>(c));
		node = &node->operator[](c);
	}

	*node << ('\0');
}

bool WordTree::word(const std::string& word) {
	Node<char> * node = &this->root;

	for (size_t index = 0; index != word.size(); ++index) {
		const char c = std::tolower(word.at(index));

		if (!node->contains(c)) return false;

		node = node->get_ptr(c);
	}
	return node->contains('\0');
}

//impl of Node<char>

template<> const char Node<char>::default_value = '\0';
template<> const size_t Node<char>::max_index = 28;
template<> size_t Node<char>::index(const char& c) {
	switch (c) {
	case 'a': return 1;
	case 'b': return 2;
	case 'c': return 3;
	case 'd': return 4;
	case 'e': return 5;
	case 'f': return 6;
	case 'g': return 7;
	case 'h': return 8;
	case 'i': return 9;
	case 'j': return 10;
	case 'k': return 11;
	case 'l': return 12;
	case 'm': return 13;
	case 'n': return 14;
	case 'o': return 15;
	case 'p': return 16;
	case 'q': return 17;
	case 'r': return 18;
	case 's': return 19;
	case 't': return 20;
	case 'u': return 21;
	case 'v': return 22;
	case 'w': return 23;
	case 'x': return 24;
	case 'y': return 25;
	case 'z': return 26;
	case '\0': return 27;
	case '-': return 28;
	default: return 0;
	}
	//return c - 'a' + 1;
}