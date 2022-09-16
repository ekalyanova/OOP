#include "pch.h"
#include "../BubbleTemplate/BubbleTemplate.h"
#include <vector>

using namespace std;
bool Comp1(int a, int b) {
	return (a > b);
}
bool Comp2(vector<int> &v1, vector<int> &v2) {
	if (v1.size() > v2.size())
		return true;
	else{
		if (v1.size() == v2.size())
		{
			auto temp_it = v2.begin();
			int sum1 = 0, sum2=0;
			for (auto it = v1.begin(); it != v1.end(); it++)
			{
				sum1 += *it;
				sum2 += *temp_it;
				temp_it++;
			}
			if (sum1 > sum2)
				return true;
			else return false;
		}
		return false;
	}
}

TEST(WithComp, VectorOfInts) {
	vector<int> v = { 3, 4, 3, 1};
	Bsort(v.begin(), v.end(), Comp1);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[3], 4);
}
TEST(WithoutComp, VectorOfInts) {
	vector<int> v = { 3, 4, 3, 1 };
	Bsort(v.begin(), v.end());
	EXPECT_EQ(v[0], 1);
	EXPECT_EQ(v[3], 4);
}
TEST(WithoutComp, VectorOfDoubles) {
	vector<int> v = { 3, 4, 3, 1 };
	Bsort(v.begin(), v.end(), Comp1);
	EXPECT_EQ(v[0], 1);
	EXPECT_EQ(v[3], 4);
}
TEST(WithoutComp, VectorOfStr) {
	string str1 = "";
	string str2 = "er";
	vector<string> v = { str1, str2 };
	Bsort(v.begin(), v.end());
	EXPECT_EQ(v[0], "");
	EXPECT_EQ(v[1], "er");
}

TEST(WithComp, VectorOfVectors) {
	vector<int> v1 = { 2, 1 };
	vector<int> v2 = { 2, 3 };
	vector<vector<int>> v = { v2, v1 };
	Bsort(v.begin(), v.end(), Comp2);
	EXPECT_EQ(v[0], v1);
	EXPECT_EQ(v[1], v2);
}