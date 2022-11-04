#include <iostream>

#include "../Dictionary/Node.h"
#include "../Dictionary/WordTree.h"
#include <assert.h>
#include <fstream>
#include <chrono>

#define NODE 0
#define TREE 1
#define DBG = TREE


class Chrono {
	std::chrono::time_point<std::chrono::steady_clock> cStart;
	std::chrono::time_point<std::chrono::steady_clock> cEnd;

public:
	Chrono() {
		this->cStart;
		this->cEnd;
	}
	inline void start() {
		this->cStart = std::chrono::steady_clock::now();
	}
	inline void stop() {
		this->cEnd = std::chrono::steady_clock::now();
		std::chrono::duration<double> elapsed_seconds = cEnd - cStart;
		std::cout << "stop; duration: " << elapsed_seconds.count() << "s\n";
	}
	inline void restart() {
		this->cEnd = std::chrono::steady_clock::now();
		std::chrono::duration<double> elapsed_seconds = cEnd - cStart;
		std::cout << "restart; duration: " << elapsed_seconds.count() << "s\n";
		this->cStart = std::chrono::steady_clock::now();
	}
};

int main()
{
/*#if DBG == NODE
	{
		Node<char> c('c');
		Node<char> j('j');
		c << std::move(j);
		c['j'] << ('i');
		assert(c['j'].contains('i') == true);
		c.replace(Node<char>('j'));
		assert(c['j'].contains('i') == false);
	}
#endif*/
	{
		WordTree t;
		t.add_word("theredas");
		t.word("theredas");
	}

	{
		WordTree t;
		{
			std::ifstream in("../dict.txt");

			Chrono c;
			c.start();
			while (!in.eof()) {
				std::string s;
				in >> s;
				t.add_word(s);
			}
			c.stop();
		}
	}


}
