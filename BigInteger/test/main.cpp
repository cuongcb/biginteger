#include "../inc/BigInteger.h"

#define print(x) std::cout << x << std::endl

int main()
{
	BigInteger *a = new BigInteger("-1235436235346245234523476245723532534523523423421312561261461234");
	BigInteger *b = new BigInteger(2093420359);
	BigInteger *c = new BigInteger("-0000000000000");
	BigInteger *d = new BigInteger("+0000000000000");
	BigInteger *e = new BigInteger("-123dafaf");
	BigInteger *f = new BigInteger("            -3");

	BigInteger *g = new BigInteger("1352345252346235725732475", 1);

	print(a->toString());
	print(b->toString());
	print(c->toString());
	print(d->toString());
	print(e->toString());
	print(f->toString());

	print(g->toString());

	BigInteger lhs("999999");
	BigInteger rhs("1");

	BigInteger res = lhs + rhs;

	print(lhs.toString());
	print(rhs.toString());
	print(res.toString());

	std::cin.get();

	return 0;
}