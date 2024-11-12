#include "pch.h"
#include "CppUnitTest.h"
#include "../LB10.2B/main.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
            const int N = 3;
            Students S[N];

            S[0] = { "Ivanenko", 2, KN, 4, 5 };
            S[0].grade_program = 3;

            S[1] = { "Petrenko", 1, ITIS, 3, 4 };
            S[1].grade_nm = 5;

            S[2] = { "Shevchenko", 3, TN, 5, 5 };
            S[2].grade_ped = 4;

            int* sorted_indices = i_sort(S, N);

            // Check if the highest physics grade is first
            Assert::AreEqual(2, sorted_indices[0], L"Highest grade in physics should come first.");
            // Check if the second in list has a lower physics grade
            Assert::AreEqual(0, sorted_indices[1], L"Second student should have next highest physics grade.");
            // Check if the third in list has the lowest physics grade
            Assert::AreEqual(1, sorted_indices[2], L"Lowest grade in physics should come last.");

            delete[] sorted_indices;
			}
		};
	};