#pragma once

#include <string>

namespace KeywordExtractor {

class TernarySearchTree;

typedef TernarySearchTree* TernarySearchTreePointer;

class TernarySearchTree
{
public:
	TernarySearchTree(char);
	void insert(const std::string &, int len);
	bool check(const std::string &, int len);
	int countAll();
	~TernarySearchTree(void);
private:
	void checkStr(const std::string &, int);
	void putString(TernarySearchTreePointer *, const std::string &);
	TernarySearchTreePointer lower, equal, higher;
	char key;
};

}