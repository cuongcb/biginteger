#include "..\inc\BigInteger.h"

BigInteger::BigInteger()
{
	mSign = 0;
}

BigInteger::BigInteger(std::string val)
{
	set(val);
}

BigInteger::BigInteger(std::string val, int sign): mSign(sign)
{
	set(val);
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
		result.mDigits = add(mDigits, rhs.mDigits);

		return result;
	}

	if (less(mDigits, rhs.mDigits))
	{
		result.mSign = rhs.mSign;
	}
	else
	{
		result.mSign = mSign;
	}

	result.mDigits = sub(mDigits, rhs.mDigits);

	return result;
}

BigInteger BigInteger::operator-(const BigInteger &rhs)
{
	return (*this + BigInteger(rhs.mDigits, -rhs.mSign));
}

BigInteger BigInteger::operator*(const BigInteger &rhs)
{
	if (mSign == 0 || rhs.mSign == 0)
		return BigInteger();

	std::vector<int> product = mul(mDigits, rhs.mDigits);

	return BigInteger(product, mSign * rhs.mSign);
}

BigInteger BigInteger::operator/(const BigInteger &rhs)
{
	if (rhs.mSign == 0)
	{
		throw std::domain_error("divided by zero");
	}
	else if (mSign == 0)
	{
		return BigInteger("0", 0);
	}
	else // both non-zero
	{
		std::vector<int> quotient = div(mDigits, rhs.mDigits);
		if (equal(quotient, std::vector<int>(1, 0)))
		{
			return BigInteger("0", 0);
		}
		
		return BigInteger(quotient, mSign * rhs.mSign);
	}
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

void BigInteger::set(std::string val)
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

	for (std::vector<int>::size_type i = 0; i < a.mDigits.size(); i++)
	{
		if (a.mDigits[i] < b.mDigits[i])
			return true;
	}

	return false;
}

bool BigInteger::less(const std::vector<int> &a, const std::vector<int> &b)
{
	if (a.size() < b.size())
		return true;
	else if (a.size() > b.size())
		return false;

	for (std::vector<int>::size_type i = 0; i < a.size(); i++)
	{
		if (a[i] < b[i])
			return true;
		else if (a[i] > b[i])
			return false;
	}

	return false;
}

bool BigInteger::equal(const std::vector<int> &a, const std::vector<int> &b)
{
	if (a.size() != b.size())
		return false;

	for (std::vector<int>::size_type i = 0; i < a.size(); i++)
	{
		if (a[i] != b[i])
			return false;
	}

	return true;
}

std::vector<int> BigInteger::add(const std::vector<int> &a, const std::vector<int> &b)
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

std::vector<int> BigInteger::sub(const std::vector<int> &a, const std::vector<int> &b)
{
	if (equal(a, b)) return std::vector<int>(1, 0);
	if (less(a, b)) return sub(b, a);

	std::vector<int> result;

	int sub = 0;
	int carry = 0;

	int i = a.size() - 1, j = b.size() - 1;

	for (; i >= 0 && j >= 0; i--, j--)
	{
		sub = a[i] - b[j] - carry;

		if (sub < 0)
		{
			sub += 10;
			carry = 1;
		}
		else
		{
			carry = 0;
		}
		
		result.insert(result.begin(), sub);
	}

	for (; i > 0; i--)
	{
		sub = a[i] - carry;
		if (sub < 0)
		{
			sub += 10;
			carry = 1;
		}
		else
		{
			carry = 0;
		}

		result.insert(result.begin(), sub);
	}

	if (i == 0 && a[i] > carry)
	{
		result.insert(result.begin(), a[i] - carry);
	}

	return result;
}

std::vector<int> BigInteger::mul(const std::vector<int> &a, const std::vector<int> &b)
{
	typedef std::vector<int>::size_type vec_sz;
	vec_sz a_size = a.size();
	vec_sz b_size = b.size();

	std::vector<int> product = std::vector<int>(a_size + b_size, 0);

	for (int b_i = b_size - 1; b_i >= 0; --b_i)
	{
		int carry = 0;
		for (int a_i = a_size - 1; a_i >= 0; --a_i)
		{
			product[a_i + b_i + 1] += carry + a[a_i] * b[b_i];
			carry = product[a_i + b_i + 1] / 10;
			product[a_i + b_i + 1] %= 10;
		}
		product[b_i] += carry;
	}

	for (std::vector<int>::const_iterator iter = product.begin(); iter != product.end();)
	{
		if (*iter == 0)
		{
			iter = product.erase(iter);
		}
		else
		{
			break;
		}
	}

	return product;
}

std::vector<int> BigInteger::div(const std::vector<int> &a, const std::vector<int> &b)
{
	if (equal(a, b)) return std::vector<int>(1, 1);
	else if (less(a, b)) return std::vector<int>(1, 0);

	std::vector<int> quotient;

	typedef std::vector<int>::size_type vec_sz;
	vec_sz asize = a.size();
	vec_sz bsize = b.size();
	vec_sz i = 0, j = bsize;

	while (i != asize)
	{
		std::vector<int> dividend = std::vector<int>(a.begin() + i, a.begin() + j); // [begin + i, begin + j)
		int divisor = 1;
		while (less(mul(b, std::vector<int>(1, divisor)), dividend)
			   || equal(mul(b, std::vector<int>(1, divisor)), dividend))
		{
			divisor++;
		}
		quotient.push_back(divisor-1);

		i = j;
		j += bsize;
		j = (j < asize) ? j : asize;
	}

	for (std::vector<int>::const_iterator iter = quotient.begin(); iter != quotient.end();)
	{
		if (*iter == 0)
		{
			iter = quotient.erase(iter);
		}
		else
		{
			break;
		}
	}

	return quotient;
}