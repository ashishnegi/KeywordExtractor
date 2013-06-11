#include "Trie.h"
#include "myexception.h"

namespace KeywordExtractor {

Trie :: Trie() {
	int size = (sizeof (alphabet)/sizeof(Trie*));
	for(int i=0;i<size; ++i) {
		alphabet[i] = NULL;
	}
}

Trie :: ~Trie() {
	for(int i=0;i<ALPHABET_SIZE;++i)
		delete alphabet[i];
}

/*
Storing only bo of boy --> not last character.
*/

void Trie :: insert(const std::string & str1, int len) {
	std::string str(str1);
	checkStr(str, len);
	Trie * next = this;
	int location = 0, pos;
	
	while(location < (len-1)) {
		pos = str[location]-'a';
		if(next->alphabet[pos] == NULL) {
			next->alphabet[pos] = new Trie();	
		}
		next = next->alphabet[pos];
		++location;
	}
}

/*
If boy is in the trie then only bo is stored --> so all bo? are in trie :(.
*/

bool Trie :: check(const std::string & str1, int len) {
	std::string str(str1);
	checkStr(str, len);
	Trie * next = this;
	int location = 0, pos;
	
	while(location < (len-1)) {
		pos = str[location]-'a';
		if(next->alphabet[pos] == NULL) {
			return false;	
		}
		next = next->alphabet[pos];
		++location;
	}
	
	return true;
}
 
void Trie :: checkStr(const std::string & str, int len) {
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

/*
Apply a infix on the trie.
*/

int Trie :: countAll() {
	int count = 1;
	for(int i=0;i<ALPHABET_SIZE;++i) {
		if(alphabet[i])
			count += alphabet[i]->countAll();
	}
	return count;
}
}
