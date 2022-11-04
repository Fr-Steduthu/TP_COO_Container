#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <sstream>

template<typename T>
class Node
{
public :
	Node<T>(const T& val) : label(val) {
		this->children = std::vector<std::unique_ptr<Node<T>>>(Node<T>::max_index);
		for (std::unique_ptr<Node<T>>& cell : this->children) {
			cell = nullptr;
		}
	}
	Node() : label(Node<T>::default_value) {
		this->children = std::vector<std::unique_ptr<Node<T>>>(Node<T>::max_index);
		for (std::unique_ptr<Node<T>>& cell : this->children) {
			cell = nullptr;
		}
	}
	Node(Node<T>&) = delete;
	~Node() = default; //Viva los smart ptr
	Node<T>& operator=(const Node<T>& other) = delete;

	inline T get_label() const { return this->label; }

	inline Node<T>& operator<< (Node<T>&& child) {
		size_t index = Node<T>::index(child.label) - 1;

		if (!(bool)this->children[index]) {
			this->replace(std::move(child), index);
		}

		return *this;
	}

	inline void replace(Node<T>&& child) {
		this->replace(std::move(child), Node<T>::index(child.label));
	}
	inline Node<T>* get_ptr(const T& label) {
		return this->children[Node<T>::index(label) - 1].get();
	}

	inline Node<T>& add_unique(Node<T>&& child) {
		const T label = child.label;
		this->operator<<(std::move(child));
		return this->operator[](label);
	}
	inline bool contains(const T& sought_value) {
		//std::cout << "Contain call on " << sought_value << " from " << this->label << "(" << this << "), found " << this->children[Node<T>::index(sought_value) -1] << std::endl;
		return (bool)this->children[Node<T>::index(sought_value) - 1];
	}

	inline Node<T>& operator[] (T sought_value) {
		size_t index = Node<T>::index(sought_value) - 1;
		if (index == (size_t)(-1)) std::cerr << "Index is invalid (-1)" << std::endl;

		if (!(bool)this->children[index]) {
			std::cerr << sought_value << " (index " << Node<T>::index(sought_value) -1 << ") isn't a child of " << this->label << std::endl;
		}

		return *this->children[index];
	}
	inline const Node<T>& operator[] (T sought_value) const {
		return *this->children[Node<T>::index(sought_value) - 1];
	}

	operator std::string() {
		std::ostringstream t;
		t << (std::string)this->label;

		return "Not impelmented yet";

	}

	static size_t index(const T&);
	static const size_t max_index; //inline-able?
	static const T default_value;
	friend int main(); //DBG
protected :

private :
	inline static void swap(Node<T>& self, Node<T>& other) {
		{
			T a = std::move(self.label);
			self.label = std::move(other.label);
			other.label = std::move(a);
		}

		{
			std::vector<std::unique_ptr<Node<T>>> a = std::move(self.children);
			self.children = std::move(other.children);
			other.children = std::move(a);
		}

	}
	inline void replace(Node<T>&& child, const size_t& index) {
		Node<T>* tmp = new Node<T>; //Assure la validite du ptr
		Node<T>::swap(*tmp, child);
		this->children[index].reset(tmp);
	}

	T label;
	std::vector<std::unique_ptr<Node<T>>> children;
};