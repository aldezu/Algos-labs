#include "pch.h"
#include "CppUnitTest.h"
#include <string>
#include "..\Array_work\FunnyArray.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

Funny_Array<int> createFunny_Array() {
	Funny_Array<int> d(1);
	d.insert(1);
	return d;
}

namespace Funny_ArrayTests
{
	TEST_CLASS(Funny_ArrayCreationTest)
	{
	public:
		TEST_METHOD(ConstructorWithNParams)
		{
			Funny_Array<int> d;
			Assert::IsTrue(d.size() == 0);
		}
		TEST_METHOD(ConstructorWithExactSize)
		{
			Funny_Array<int> d(10);
			Assert::IsTrue(d.size() == 0);
		}
		TEST_METHOD(CopyConstructor)
		{
			Funny_Array<int> f(2);
			f.insert(1);
			Funny_Array<int> t(f);
			Assert::IsTrue(t[0] == 1);
		}
		TEST_METHOD(MoveConstructor)
		{
			Funny_Array<int> t = createFunny_Array();
			Assert::IsTrue(t[0] == 1);
		}
	};

	TEST_CLASS(Funny_ArrayInsertionTest)
	{
	public:
		TEST_METHOD(PushBack)
		{
			Funny_Array<int> d;
			d.insert(0);
			d.insert(1);
			Assert::IsTrue(d[1] == 1);
		}
		TEST_METHOD(InsertSizeChanging)
		{
			Funny_Array<int> d;
			d.insert(0);
			d.insert(1);
			Assert::IsTrue(d.size() == 2);
		}
		TEST_METHOD(InsertIntoSpecificPosition)
		{
			Funny_Array<int> d;
			d.insert(0);
			d.insert(1);
			d.insert(1, 2);
			Assert::IsTrue(d[1] == 2);
		}
		TEST_METHOD(InsertWithResizing)
		{
			Funny_Array<int> d(2);
			d.insert(0);
			d.insert(1);
			d.insert(2);
			Assert::IsTrue(d[2] == 2);
		}
		TEST_METHOD(CheckPushBackIndex)
		{
			Funny_Array<int> d;
			d.insert(0);
			int test = d.insert(0);
			Assert::IsTrue(test == 1);
		}
		TEST_METHOD(CheckInsertionIndex)
		{
			Funny_Array<int> d;
			d.insert(0);
			d.insert(0);
			int test = d.insert(1, 0);
			Assert::IsTrue(test == 1);
		}
		TEST_METHOD(InsertOutOfRange)
		{
			Funny_Array<int> d;
			d.insert(0);
			d.insert(0);
			int test = d.insert(5, 0);
			Assert::IsTrue(test == -1);
		}
	};

	TEST_CLASS(Funny_ArrayRemoveTest)
	{
	public:
		TEST_METHOD(BasicRemove)
		{
			Funny_Array<int> d;
			d.insert(0);
			d.insert(1);
			d.insert(2);
			d.remove(1);
			Assert::IsTrue(d[1] == 2);
		}
		TEST_METHOD(RemoveLastElement)
		{
			Funny_Array<int> d;
			d.insert(0);
			d.insert(1);
			d.insert(2);
			d.remove(2);
			Assert::IsTrue(d.size() == 2);
		}
		TEST_METHOD(RemoveFirstElement)
		{
			Funny_Array<int> d;
			d.insert(0);
			d.insert(1);
			d.insert(2);
			d.remove(0);
			Assert::IsTrue(d[0] == 1);
		}
	};

	TEST_CLASS(Funny_ArrayIteratorTest)
	{
	public:
		TEST_METHOD(IteratorGet)
		{
			Funny_Array<int> d;
			d.insert(1);
			d.insert(2);
			auto it = d.iterator();
			Assert::IsTrue(it.get() == 1);
		}
		TEST_METHOD(ReverseIteratorGet)
		{
			Funny_Array<int> d;
			d.insert(1);
			d.insert(2);
			auto it = d.reverseIterator();
			Assert::IsTrue(it.get() == 2);
		}
		TEST_METHOD(IteratorSet)
		{
			Funny_Array<int> d;
			d.insert(1);
			d.insert(2);
			auto it = d.iterator();
			it.set(5);
			Assert::IsTrue(d[0] == 5);
		}
		TEST_METHOD(IteratorNext)
		{
			Funny_Array<int> d;
			d.insert(1);
			d.insert(2);
			auto it = d.iterator();
			it.next();
			Assert::IsTrue(it.get() == 2);
		}
		TEST_METHOD(ReverseIteratorNext)
		{
			Funny_Array<int> d;
			d.insert(1);
			d.insert(2);
			auto it = d.reverseIterator();
			it.next();
			Assert::IsTrue(it.get() == 1);
		}
		TEST_METHOD(IteratorHasNext)
		{
			Funny_Array<int> d;
			d.insert(1);
			d.insert(2);
			auto it = d.reverseIterator();
			it.next();
			Assert::IsFalse(it.hasNext());
		}
		TEST_METHOD(ReverseIteratorHasNext)
		{
			Funny_Array<int> d;
			d.insert(1);
			d.insert(2);
			auto it = d.reverseIterator();
			it.next();
			Assert::IsFalse(it.hasNext());
		}
	};
	TEST_CLASS(Funny_ArrayStringTest)
	{
	public:
		TEST_METHOD(StringInsert)
		{
			Funny_Array<std::string> d;
			d.insert("Test");
			Assert::IsTrue(d[0].compare("Test") == 0);
		}
		TEST_METHOD(StringInsertWithResize)
		{
			Funny_Array<std::string> d(2);
			d.insert("Test");
			d.insert("Test1");
			d.insert("Test2");
			Assert::IsTrue(d[2].compare("Test2") == 0);
		}
		TEST_METHOD(StringRemove)
		{
			Funny_Array<std::string> d;
			d.insert("Test");
			d.insert("Test1");
			d.remove(0);
			Assert::IsTrue(d[0].compare("Test1") == 0);
		}
		TEST_METHOD(StringIterator)
		{
			Funny_Array<std::string> d(4);
			d.insert("Test");
			d.insert("Test1");
			d.insert("Test2");
			auto it = d.iterator();
			it.next();
			Assert::IsTrue(it.get().compare("Test1") == 0);
		}
		TEST_METHOD(StringReverseIterator)
		{
			Funny_Array<std::string> d(4);
			d.insert("Test");
			d.insert("Test1");
			d.insert("Test2");
			d.insert("Test3");
			auto it = d.reverseIterator();
			it.next();
			Assert::IsTrue(it.get().compare("Test2") == 0);
		}
	};
}