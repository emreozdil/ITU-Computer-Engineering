//  Created by Emre Özdil
//  Copyright © 2015 Emre Özdil. All rights reserved.

#include <iostream>
#include <string>
#include <map>
#include <set>

using namespace std;

int main() {
	/*SET*/
	FILE *myfile = fopen("stopwords.txt", "r");
	if (!myfile) {
		return 0;
	}
	char word[100];
	set <string> stopwords;

	while (!feof(myfile)) {
		fscanf(myfile, "%s", word);
		stopwords.insert(word);
	}
	fclose(myfile);
	/*MAP*/
	myfile = fopen("input.txt", "r");
	if (!myfile) {
		return 0;
	}
	int counter = 0;
	set<string>::iterator its;
	map <string, int> freq;
	while (!feof(myfile)) {
		counter++;
		fscanf(myfile, "%s", word);
		its = stopwords.find(word);
		if (its != stopwords.end()) {
			freq[word]++;
		}
	}
	fclose(myfile);
	/*WRITE*/
	multimap <int, string > freq_rev;
	map<string, int>::iterator it;
	for (it = freq.begin(); it != freq.end(); it++)
		freq_rev.insert(make_pair(it->second, it->first));
	multimap <int, string>::reverse_iterator myit;
	int count;
	for (myit = freq_rev.rbegin(), count = 0; count<freq_rev.size(); myit++, count++)
		cout << (*myit).second << " " << (*myit).first << " % " << 100.0*(*myit).first / counter << endl;
	system("pause");
	return 0;
}
