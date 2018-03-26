#include "..\inc\BigInteger.h"

BigInteger::BigInteger()
{
	mSign = 0;
}

BigInteger::BigInteger(std::string val)
{
	Set(val);
}

BigInteger::BigInteger(std::string val, int sign): mSign(sign)
{
	Set(val);
}

BigInteger::BigInteger(std::vector<int> val, int sign) : mDigits(val), mSign(sign)
{

}

BigInteger::BigInteger(const BigInteger & val)
{
	this->mDigits = val.mDigits;
	this->mSign = val.mSign;
}

BigInteger::BigInteger(int val)
{
	if (val < 0)
		mSign = -1;
	else if (val > 0)
		mSign = 1;
	else
		mSign = 0;

	while (val)
	{
		mDigits.insert(mDigits.begin(), val % 10);
		val = val / 10;
	}
}

BigInteger BigInteger::operator+(const BigInteger &rhs)
{
	if (mSign == 0)
	{
		this->mDigits = rhs.mDigits;
		this->mSign = rhs.mSign;
		return *this;
	}
	else if (rhs.mSign == 0)
	{
		return *this;
	}
	
	BigInteger result;

	if (mSign == rhs.mSign) // normal add
	{
		result.mSign = mSign;
		result.mDigits = Add(mDigits, rhs.mDigits);

		return result;
	}

	if (Less(mDigits, rhs.mDigits))
	{
		result.mSign = rhs.mSign;
	}
	else
	{
		result.mSign = mSign;
	}

	result.mDigits = Sub(mDigits, rhs.mDigits);

	return result;
}

BigInteger BigInteger::operator-(const BigInteger &rhs)
{
	return (*this + BigInteger(rhs.mDigits, -rhs.mSign));
}

void BigInteger::strimLeftSpace(std::string &s)
{
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
		return !isspace(ch);
	}));
}

void BigInteger::strimRightSpace(std::string &s)
{
	s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
		return !isspace(ch);
	}).base(), s.end());
}

int BigInteger::toInt(int ch)
{
	return (ch - '0');
}

void BigInteger::Set(std::string val)
{
	unsigned int cursor = 0;
	mSign = 1;

	strimLeftSpace(val);
	strimRightSpace(val);

	if (val.length() == 0)
	{
		throw "Null value";
	}

	int indexMinus = val.find_last_of("-");
	int indexPlus = val.find_last_of("+");

	if (indexMinus >= 0)
	{
		if (indexMinus != 0 || indexPlus >= 0)
			throw "Illegal sign";
		mSign = -1;
		cursor = 1;
	}
	else if (indexPlus >= 0)
	{
		if (indexPlus != 0)
			throw "Illegal sign";
		cursor = 1;
	}

	if (cursor == val.length() || !isdigit(val[cursor])) // s = "+" or "-"
		throw "Illegal string";

	while (cursor < val.length() && val[cursor] == '0') cursor++;

	if (cursor == val.length())
	{
		mDigits.push_back(0);
		mSign = 0;
		return;
	}

	while (cursor < val.length() && isdigit(val[cursor]))
	{
		mDigits.push_back(toInt(val[cursor]));
		cursor++;
	}
}

BigInteger::~BigInteger()
{
}

std::string BigInteger::toString()
{
	std::string result = "";

	if (mSign == 0)
		return "0";
	else if (mSign < 0)
		result += "-";

	for (auto digit : mDigits)
		result += std::to_string(digit);

	return result;
}

bool BigInteger::lessAbs(const BigInteger &a, const BigInteger &b)
{
	if (a.mDigits.size() < b.mDigits.size())
		return true;
	else if (a.mDigits.size() > b.mDigits.size())
		return false;

	for (unsigned int i = 0; i < a.mDigits.size(); i++)
	{
		if (a.mDigits[i] < b.mDigits[i])
			return true;
	}

	return false;
}

bool BigInteger::Less(std::vector<int> a, std::vector<int> b)
{
	if (a.size() < b.size())
		return true;
	else if (a.size() > b.size())
		return false;

	for (unsigned int i = 0; i < a.size(); i++)
	{
		if (a[i] < b[i])
			return true;
		else if (a[i] > b[i])
			return false;
	}

	return false;
}

std::vector<int> BigInteger::Add(std::vector<int> a, std::vector<int> b)
{
	std::vector<int> result;
	int carry = 0;
	int sum = 0;
	int i = a.size() - 1, j = b.size() - 1;

	for (; i >= 0 && j >= 0; i--, j--)
	{
		sum = a[i] + b[j] + carry;
		carry = sum / 10;
		result.insert(result.begin(), sum % 10);
	}

	while (i >= 0)
	{
		sum = a[i] + carry;
		result.insert(result.begin(), sum % 10);
		carry = sum / 10;
		i--;
	}

	while (j >= 0)
	{
		sum = b[j] + carry;
		result.insert(result.begin(), sum % 10);
		carry = sum / 10;
		j--;
	}

	if (carry > 0)
		result.insert(result.begin(), carry);

	return result;
}

std::vector<int> BigInteger::Sub(std::vector<int> a, std::vector<int> b)
{
	if (Less(a, b)) return Sub(b, a);

	std::vector<int> result;

	int sub = 0;
	int carry = 0;

	int i = a.size() - 1, j = b.size() - 1;

	for (; i >= 0 && j >= 0; i--, j--)
	{
		b[j] += carry;

		if (a[i] < b[j])
		{
			a[i] += 10;
			carry = 1;
		}
		else
		{
			carry = 0;
		}

		sub = a[i] - b[j];
		
		result.insert(result.begin(), sub);
	}

	while (i > 0)
	{
		if (a[i] < carry)
		{
			a[i] = 9;
		}
		else
		{
			a[i] -= carry;
			carry = 0;
		}

		result.insert(result.begin(), a[i--]);
	}

	if (i == 0 && a[i] > carry)
	{
		result.insert(result.begin(), a[i] - carry);
	}

	return result;
}