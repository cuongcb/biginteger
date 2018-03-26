#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class BigInteger {
private:
	std::vector<int> mDigits;
	int mSign; // -1, 0, 1

public:
	BigInteger();
	BigInteger(std::string val);
	BigInteger(std::string val, int sign);
	BigInteger(std::vector<int> val, int sign);
	BigInteger(const BigInteger & val);
	BigInteger(int val);
	~BigInteger();
	std::string toString();

	// +
	BigInteger operator+(const BigInteger &rhs);
	// -
	BigInteger operator-(const BigInteger &rhs);
	// *
	BigInteger operator*(const BigInteger &rhs);
	// /
	BigInteger operator/(const BigInteger &rhs);
	// Not
	BigInteger& Not();

private:
	void strimLeftSpace(std::string &s);
	void strimRightSpace(std::string &s);
	int toInt(int ch);
	void Set(std::string val);
	bool lessAbs(const BigInteger &a, const BigInteger &b);
	bool Less(std::vector<int> a, std::vector<int> b);
	std::vector<int> Add(std::vector<int> a, std::vector<int> b);
	std::vector<int> Sub(std::vector<int> a, std::vector<int> b);
};
