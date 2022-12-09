#include "pch.h"
#include "CppUnitTest.h"
#include "..\Lab3_quicksort\SortingMess.h"
#include <vector>
#include <ctime>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace QuickSortUnitTest
{
	TEST_CLASS(QuickSortUnitTest)
	{
	public:

		TEST_METHOD(OneIntSortAscending)
		{
			int a = 5;
			QuickSort(&a, &a, [](auto a, auto b) { return a < b; });
			Assert::IsTrue(a == 5);
		}

		TEST_METHOD(FifteenIntSortAscending)
		{
			size_t const size = 15;
			int a[size];

			srand(time(nullptr));
			for (size_t i = 0; i < size; i++) {
				a[i] = rand() % 100;
			}

			QuickSort(&a[0], &a[size-1], [](int a, int b) { return a < b; });

			for (size_t i = 0; i < size - 1; i++)
				Assert::IsTrue(a[i] <= a[i + 1]);
		}

		TEST_METHOD(HundredIntSortAscending)
		{
			size_t const size = 100;
			int a[size];

			srand(time(nullptr));
			for (size_t i = 0; i < size; i++) {
				a[i] = rand() % 100;
			}

			QuickSort(&a[0], &a[size - 1], [](auto a, auto b) { return a < b; });

			for (size_t i = 0; i < size - 1; i++)
				Assert::IsTrue(a[i] <= a[i + 1]);
		}

		TEST_METHOD(OneIntSortDescending)
		{
			int a = 5;
			QuickSort(&a, &a, [](auto a, auto b) { return a > b; });
			Assert::IsTrue(a == 5);
		}

		TEST_METHOD(FifteenIntSortDescending)
		{
			size_t const size = 15;
			int a[size];

			srand(time(nullptr));
			for (size_t i = 0; i < size; i++) {
				a[i] = rand() % 100;
			}

			QuickSort(&a[0], &a[size - 1], [](auto a, auto b) { return a > b; });

			for (size_t i = 0; i < size - 1; i++)
				Assert::IsTrue(a[i] >= a[i + 1]);
		}

		TEST_METHOD(HundredIntSortDescending)
		{
			size_t const size = 100;
			int a[size];

			srand(time(nullptr));
			for (size_t i = 0; i < size; i++) {
				a[i] = rand() % 100;
			}

			QuickSort(&a[0], &a[size - 1], [](auto a, auto b) { return a > b; });

			for (size_t i = 0; i < size - 1; i++)
				Assert::IsTrue(a[i] >= a[i + 1]);
		}

		TEST_METHOD(OneFloatSortAscending)
		{
			float a = 5.0f;
			QuickSort(&a, &a, [](auto a, auto b) { return a < b; });
			Assert::IsTrue(a == 5);
		}

		TEST_METHOD(FifteenFloatSortAscending)
		{
			size_t const size = 15;
			float a[size];

			srand(time(nullptr));
			for (size_t i = 0; i < size; i++) {
				a[i] = rand() % 100;
			}

			QuickSort(&a[0], &a[size - 1], [](auto a, auto b) { return a < b; });

			for (size_t i = 0; i < size - 1; i++)
				Assert::IsTrue(a[i] <= a[i + 1]);
		}

		TEST_METHOD(HundredFloatSortAscending)
		{
			size_t const size = 100;
			float a[size];

			srand(time(nullptr));
			for (size_t i = 0; i < size; i++) {
				a[i] = rand() % 100;
			}

			QuickSort(&a[0], &a[size - 1], [](auto a, auto b) { return a < b; });

			for (size_t i = 0; i < size - 1; i++)
				Assert::IsTrue(a[i] <= a[i + 1]);
		}

		TEST_METHOD(OneFloatSortDescending)
		{
			float a = 5.0f;
			QuickSort(&a, &a, [](auto a, auto b) { return a > b; });
			Assert::IsTrue(a == 5);
		}

		TEST_METHOD(FifteenFloatSortDescending)
		{
			size_t const size = 15;
			float a[size];

			srand(time(nullptr));
			for (size_t i = 0; i < size; i++) {
				a[i] = rand() % 100;
			}

			QuickSort(&a[0], &a[14], [](auto a, auto b) { return a > b; });

			for (size_t i = 0; i < size - 1; i++)
				Assert::IsTrue(a[i] >= a[i + 1]);
		}

		TEST_METHOD(HundredFloatSortDescending)
		{
			size_t const size = 100;
			float a[size];

			srand(time(nullptr));
			for (size_t i = 0; i < size; i++) {
				a[i] = rand() % 100;
			}

			QuickSort(&a[0], &a[size - 1], [](auto a, auto b) { return a > b; });

			for (size_t i = 0; i < size - 1; i++)
				Assert::IsTrue(a[i] >= a[i + 1]);
		}

	};
}