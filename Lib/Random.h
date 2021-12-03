#pragma once
class Random {
private:
	static bool _initialized;
public:
	int nextInt();
	int nextInt(int);
	int nextInt(int, int);
};