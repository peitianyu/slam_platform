#ifndef __COMMON_TEST_H__
#define __COMMON_TEST_H__

#include <stdio.h>
#include <stdlib.h>
#include <sstream>


class Tester 
{
private:
	bool ok_;               //result status
	const char* fname_;     //file name
	int line_;              //line number
	std::stringstream ss_;  //message for display

public:
	Tester(const char* f, int l)
	: ok_(true), fname_(f), line_(l) 
	{
	}

	~Tester() 
	{
		if (!ok_) 
		{
			fprintf(stderr, "%s:%d:%s\n", fname_, line_, ss_.str().c_str());
			exit(1);
		}
	}

	Tester& Is(bool b, const char* msg) 
	{
		if (!b) 
		{
			ss_ << " Assertion failure " << msg;
			ok_ = false;
		}
		return *this;
	}


#define BINARY_OP(name,op)                                      \
	template <class X, class Y>                                 \
	Tester& name(const X& x, const Y& y)                        \
	{                                                           \
		if (!(x op y))                                          \
		{                                                       \
			ss_ << " failed: " << x << (" " #op " ") << y;      \
			ok_ = false;                                        \
		}                                                       \
		return *this;                                           \
	}

	BINARY_OP(IsEq, ==)
	BINARY_OP(IsNe, !=)
	BINARY_OP(IsGe, >=)
	BINARY_OP(IsGt, >)
	BINARY_OP(IsLe, <=)
	BINARY_OP(IsLt, <)

#undef BINARY_OP

	template <class V>
	Tester& operator<<(const V& value) 
	{
		if (!ok_) 
		{
		ss_ << " " << value;
		}
		return *this;
	}
};


#define ASSERT_TRUE(c) Tester(__FILE__, __LINE__).Is((c), #c)
#define ASSERT_EQ(a,b) Tester(__FILE__, __LINE__).IsEq((a),(b))
#define ASSERT_NE(a,b) Tester(__FILE__, __LINE__).IsNe((a),(b))
#define ASSERT_GE(a,b) Tester(__FILE__, __LINE__).IsGe((a),(b))
#define ASSERT_GT(a,b) Tester(__FILE__, __LINE__).IsGt((a),(b))
#define ASSERT_LE(a,b) Tester(__FILE__, __LINE__).IsLe((a),(b))
#define ASSERT_LT(a,b) Tester(__FILE__, __LINE__).IsLt((a),(b))

#define TEST(base,name)                                                             \
class _test_##base##name                                                            \
{                                                                                   \
public:                                                                             \
       	void _run();                                                                \
	static void Run()                                                               \
	{                                                                               \
		_test_##base##name t;                                                       \
		t._run();                                                                   \
	}                                                                               \
};                                                                                  \
class _register_##base##name                                                        \
{                                                                                   \
public:                                                                             \
	_register_##base##name()                                                        \
	{                                                                               \
		RegisterTest(#base, #name, &_test_##base##name::Run);               	 	\
	}                                                                               \
};                                                                                  \
_register_##base##name auto_register_##base##name;                                  \
void _test_##base##name::_run()


bool RegisterTest(const char *base, const char* name, void (*func)());

int RunAllTests();



#endif // __COMMON_TEST_H__