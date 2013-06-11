#include "ternarysearchtree.h"
#include "Trie.h"
#include <cstdio>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <ctime>

int min(int a, int b) {
	if(a < b)
		return a;
	return b;
	return b + (a-b)*((a-b)&(1<<((sizeof (int)) - 1)));	
}

//#define TST

#ifndef TST
KeywordExtractor :: Trie trie;
#else 
KeywordExtractor :: TernarySearchTree trie('s');
#endif

int main(int argc, char *argv[]) {
	time_t start = clock();

	int noWords;
	char str[100];
	
	scanf("%d", &noWords);

#ifdef DEBUG
		printf(">%d<\n",noWord);
		fflush(stdio);
#endif	

	int i=0, len;
	
	long long totalChars = 0;

	while(i < noWords) {
		scanf("%s", str);
		std::string word(str);
#ifdef DEBUG
		printf(">%s<\n",&word[0]);
#endif
		len = word.length();
		for(int j=0;j<len;++j) {
			if(word[j]>='A' && word[j]<='Z') {
				word[j] += 32;
			}
		}
		
		try {
#ifndef TST
			trie.insert(word,min(KeywordExtractor :: MAX_TRIE_DEPTH, len));
#else
			trie.insert(word, len);
#endif	
			totalChars += len;
		} catch (MyException exp) {
			std::cout << "\nFor string " << word << " Error: "  << exp;
		}	
		++i;
	}	
	
	std::string checks[3] = {"hello", "cat", "bomb"};
	int sizeCheck = sizeof(checks)/sizeof(std::string);
	
	printf("\n>sizeCheck: %d<", sizeCheck);
	
	for(int i=0;i<sizeCheck;++i) {
		if(
#ifdef TST
			trie.check(checks[i], checks[i].length())
#else		
			trie.check(checks[i],min(KeywordExtractor :: MAX_TRIE_DEPTH, checks[i].length()))
#endif	
			)
			printf("\nGot %s", &checks[i][0]);
	}


	printf("\nTotalChars : %d\n", totalChars);
	
	int totalTries = trie.countAll();
	int totalMemory = totalTries * 
#ifdef TST
		sizeof(KeywordExtractor::TernarySearchTree);
#else
		sizeof(KeywordExtractor :: Trie);
#endif

	printf("\nTotal Tries:%d\nTotal Memory: %d\nUseful Memory (perc.): %f\n", 
		totalTries, totalMemory, ((100*totalChars)/(double)totalMemory));

	if(argc == 2) {
		std::ifstream inf(argv[1]);
		if(!inf.is_open()) {
			std::cout << "\nCan't open file: " << argv[1];
		} else {
			std::map<std::string, int> countKeywords;
			std::string word;
			bool badWord = false;

			while(!inf.eof()) {
				inf >> word;
				len = word.length();
				badWord = false;
				
				for(int i=0;i<len;++i) {
					if(word[i]>='A' && word[i]<='Z') {
						word[i] += 32;
					} else if(!(word[i]>='a' && word[i]<='z')) {
						badWord = true;
						break;
					}
				}

				if(badWord) {
					continue;
				}

				try {
					if(!trie.check(word, 
#ifdef TST
						len)
#else
						min(KeywordExtractor :: MAX_TRIE_DEPTH, len))
#endif	
						) {
						++countKeywords[word];
					}
				} catch (MyException exp) {
				}
			}

			struct Result {
				std::string keyword;
				int count;

				Result(std::string _k, int _c) : keyword(_k), count(_c) {
				}

				bool operator<(const Result &res) const {
					return count > res.count;
				}
			};

			std::vector<Result> results;

			std::cout << "\nKeyword\tCount\n";
			for(std::map<std::string,int>::iterator mit = countKeywords.begin();
				mit != countKeywords.end(); ++mit) {
					results.push_back(Result(mit->first, mit->second));
					// std::cout << mit->first << "\t" << mit->second << std::endl;
			}

			sort(results.begin(), results.end());

			for(std::vector<Result> :: iterator rit = results.begin();
				rit < results.end(); ++rit) {
					std::cout << rit->keyword << "\t" << rit->count << std::endl;
			}

		}
	}

	time_t end = clock();
	printf("\nTIME: %f", (end/(double)CLOCKS_PER_SEC - start/(double)CLOCKS_PER_SEC));
	return 0;
}
