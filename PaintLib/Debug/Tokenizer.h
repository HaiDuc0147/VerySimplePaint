#pragma once
#include<vector>
#include<string>
using namespace std;
class Tokenizer {
public:
	static vector<string> split(string haystack, string seperator = " ");
};