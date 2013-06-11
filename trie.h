#ifndef TRIE_H
#define TRIE_H

#include <string>
#include "myexception.h"

namespace KeywordExtractor {

const int MAX_TRIE_DEPTH = 6;
/*
This trie inserts a string but does not store end of string.
So even prefix are considered to be strings.
So, we also can't remove the strings.
*/

const int ALPHABET_SIZE = 26;

class Trie {
	Trie *alphabet[ALPHABET_SIZE];
	void checkStr(const std::string &, int);
	public:
	Trie();
	void insert(const std::string &, int len);
	bool check(const std::string &, int len);
	int countAll();
	virtual ~Trie();	
};


}

#endif
