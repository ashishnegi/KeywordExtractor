#include "TernarySearchTree.h"
#include "myexception.h"

namespace KeywordExtractor {

TernarySearchTree::TernarySearchTree(char _key) : lower(NULL), equal(NULL), higher(NULL),
												key(_key) {
}

TernarySearchTree::~TernarySearchTree(void) {
	delete lower;
	delete equal;
	delete higher;
}

void TernarySearchTree::insert(const std::string &str1, int len) {
	std::string str(str1);
	checkStr(str,len);
	int i = 0;
	TernarySearchTreePointer next = this;

	while(i < len) {
		if(str[i] == next->key) {
			++i;
			if(next->equal)
				next = next->equal;
			else
				putString(&(next->equal), str.substr(i,len-i));				
		} else if(str[i] < next->key) {
			if(next->lower)
				next = next->lower;
			else
				putString(&(next->lower), str.substr(i,len-i));
		} else if(next->higher) {
			next = next->higher;
		} else
			putString(&(next->higher), str.substr(i,len-i));
	}

	// assert(next);
	putString(&next, str.substr(i,len-i));
}

void TernarySearchTree::putString(TernarySearchTreePointer *root, const std::string &str) {
	TernarySearchTreePointer *next = root;
	int len = str.length();
	for(int i=0;i<len;++i) {
		*next = new TernarySearchTree(str[i]);
		next = &((*next)->equal);
	}
}

bool TernarySearchTree::check(const std::string &str, int len) {
	int i = 0;
	TernarySearchTreePointer next = this;

	while((next) && (i < len)) {
		// printf("\nSearching %c and node;s ket is %c", str[i], next->key);
		if(str[i] == next->key) {
			next = next->equal;
			++i;
		} else if(str[i] < next->key) {
			next = next->lower;
		} else {
			next = next->higher;
		}
	}

	if(i == len)
		return true;
	return false;
}

int TernarySearchTree::countAll() {
	int count = 1;
	if(lower)
		count += lower->countAll();
	if(equal)
		count += equal->countAll();
	if(higher)
		count += higher->countAll();
	return count;
}

void TernarySearchTree::checkStr(const std::string & str, int len) {
	for(int i=0;i<len;++i) {
		if(!(str[i] >= 'a' && str[i] <= 'z')) {
			if(str[i] >= 'A' && str[i] <= 'Z') {
				char *p = const_cast<char *>(&str[i]);
				*p += 32;
				continue;
			}
			IllegalStringException exp("Illegal String " + str);
			throw exp;
		}
	}
}


}