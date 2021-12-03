#include"Tokenizer.h"
vector<string> Tokenizer::split(string haystack, string seperator) {
	vector<string> tokens;
	int startPos = 0;
	int foundPos = 0;
	while (true) {
		foundPos = haystack.find(seperator, startPos);
		if (foundPos != string::npos) {
			string substring = haystack.substr(startPos, foundPos - startPos);
			tokens.push_back(substring);
			startPos = foundPos + seperator.length();
		}
		else {
			string substring = haystack.substr(startPos, haystack.length() - startPos);
			tokens.push_back(substring);
			break;
		}
	}
	return tokens;
}