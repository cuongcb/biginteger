#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>

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
	void set(std::string val);
	bool lessAbs(const BigInteger &a, const BigInteger &b);
	bool less(const std::vector<int> &a, const std::vector<int> &b);
	bool equal(const std::vector<int> &a, const std::vector<int> &b);
	std::vector<int> add(const std::vector<int> &a, const std::vector<int> &b);
	std::vector<int> sub(const std::vector<int> &a, const std::vector<int> &b);
	std::vector<int> mul(const std::vector<int> &a, const std::vector<int> &b);
	std::vector<int> div(const std::vector<int> &a, const std::vector<int> &b);
};
