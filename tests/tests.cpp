// tests.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <boost/test/unit_test.hpp>
#include <string>
#include <vector>
#include "stdafx.h"
#include "../task3/CMyStringList.h"
#include "../task3/Iterator.h"

using namespace std;

vector<string> StringListAsNormalVector(CMyStringList &list)
{
	vector<string> result;

	for (auto &str : list)
	{
		result.push_back(str);
	}

	return result;
}

BOOST_AUTO_TEST_CASE(TestEmptyList)
{
	CMyStringList l;
	BOOST_CHECK(l.begin() == l.end());
}

BOOST_AUTO_TEST_CASE(TestListInsertion)
{
	CMyStringList l;

	l.Insert(l.end(), "test");
	BOOST_CHECK(StringListAsNormalVector(l) == vector<string>({ "test" }));

	l.Insert(l.begin(), "more");
	BOOST_CHECK(StringListAsNormalVector(l) == vector<string>({ "more", "test" }));

	l.Insert(l.end(), "end");
	BOOST_CHECK(StringListAsNormalVector(l) == vector<string>({ "more", "test", "end" }));

	l.Insert(++l.begin(), "middle");
	BOOST_CHECK(StringListAsNormalVector(l) == vector<string>({ "more", "middle", "test", "end" }));
}

struct StringListFixture
{
	CMyStringList l;

	StringListFixture()
	{
		l.Insert(l.end(), "1");
		l.Insert(l.end(), "2");
		l.Insert(l.end(), "3");
		l.Insert(l.end(), "4");
		l.Insert(l.end(), "5");
	}
};

BOOST_FIXTURE_TEST_SUITE(StringList, StringListFixture)

BOOST_AUTO_TEST_CASE(CanObtainListBeginAndEnd)
{
	BOOST_CHECK_EQUAL(*l.begin(), "1");
	BOOST_CHECK_EQUAL(*--l.end(), "5");
}

BOOST_AUTO_TEST_CASE(CanIterateThroughList)
{
	auto it = l.begin();
	BOOST_CHECK_EQUAL(*it, "1");

	++it;
	BOOST_CHECK_EQUAL(*it, "2");

	++it;
	++it;
	BOOST_CHECK_EQUAL(*it, "4");

	--it;
	BOOST_CHECK_EQUAL(*it, "3");

	++it;
	++it;
	BOOST_CHECK_EQUAL(*it, "5");

	++it;
	--it;
	BOOST_CHECK_EQUAL(*it, "5");
}

BOOST_AUTO_TEST_CASE(TestListRemoval)
{
	l.Remove(l.begin());
	BOOST_CHECK(StringListAsNormalVector(l) == vector<string>({ "2", "3", "4", "5" }));

	l.Remove(--l.end());
	BOOST_CHECK(StringListAsNormalVector(l) == vector<string>({ "2", "3", "4" }));

	l.Remove(++l.begin());
	BOOST_CHECK(StringListAsNormalVector(l) == vector<string>({ "2", "4" }));

	l.Remove(l.begin());
	BOOST_CHECK(StringListAsNormalVector(l) == vector<string>({ "4" }));

	l.Remove(l.begin());
	BOOST_CHECK(StringListAsNormalVector(l).empty());
}

BOOST_AUTO_TEST_SUITE_END()