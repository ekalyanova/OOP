#include "pch.h"
#include "../skip list/SkipList.h"
#include "../skip list/gtest-memleak.h"
#include <map>
#include <iostream>

//TEST(ConstructorWithArgs, AvarageValues) {
//	std::pair<int, int> p(1, 0);
//	skip_list<int, int> l(p);
//	auto i = l.begin();
//	std::cout<< (*i).first<<std::endl;
//	EXPECT_EQ((*i).first, 1);
//}
TEST(ConstructorWithoutArgs, IntEmpty) {
	skip_list<int, int> l;
	auto i = l.begin();
	EXPECT_EQ((*i).second, 0);
}
TEST(Rrandomlvl, IntAvarageValues) {
	skip_list<int, int> l;
	auto t = l.random_level();
	size_t max_lvl = l.get_max_lvl();
	EXPECT_TRUE(t <= max_lvl); 
}

TEST(Insert, IntAvarageValues) {
	skip_list<int, int> l;
	auto it = l.insert(std::make_pair(1, 0));
	if (it.second == true) {
		EXPECT_EQ((*it.first).first, 1);
		EXPECT_EQ((*it.first).second, 0);
	}
}
TEST(Insert, IntTheSameValues) {
	skip_list<int, int> l;
	auto i = l.insert(std::make_pair(1, 0));
	auto it = l.insert(std::make_pair(1, 1));
	EXPECT_TRUE(it.first == i.first);
	if (it.second == true) {
		EXPECT_EQ((*it.first).first, 1);
		EXPECT_EQ((*it.first).second, 1);
	}	
}
TEST(Insert, IntTwoAvarageValues) {
	skip_list<int, int> l;
	l.insert(std::make_pair(1, 0));
	auto it = l.insert(std::make_pair(2, 0));
	if (it.second == true) {
		EXPECT_EQ((*it.first).first, 2);
		EXPECT_EQ((*it.first).second, 0);
	}
}
TEST(Insert, IntTwoAvarageValuesPositNegat) {
	skip_list<int, int> l;
	l.insert(std::make_pair(1, 0));
	auto i = l.insert(std::make_pair(-1, 0));
	if (i.second == true) {
		EXPECT_EQ((*i.first).first, -1);
		EXPECT_EQ((*i.first).second, 0);
	}
}
TEST(Insert, IntInsertInHead) {
	skip_list<int, int> l;
	auto i = l.insert(std::make_pair(1, 1));
	auto it = l.insert(std::make_pair(0, 1));

	if (it.second == true) {
		EXPECT_EQ((*it.first).first, 0);
		EXPECT_EQ((*it.first).second, 1);
		EXPECT_EQ(it.first, l.begin());
	}
}

TEST(IteratorTest, IntFourAvarageValues) {
	skip_list<int, int> l;
	l.insert(std::make_pair(1, 1));
	l.insert(std::make_pair(2, 1));
	l.insert(std::make_pair(3, 1));
	l.insert(std::make_pair(0, 1));
	int counter = 0;
	for (auto it = l.begin(); it != l.end(); ++it) {
		counter++;
	}
	EXPECT_EQ(counter, 4);
}

TEST(OperatorSqBrackets, IntAvarageValues) {
	skip_list<int, int> l;
	auto it = l.insert(std::make_pair(1, 1));
	if (it.second == true) {
		EXPECT_TRUE(l[1]== 1);
		EXPECT_FALSE(l[1]== 0);
	}
}
TEST(OperatorSqBrackets, IntEmpty) {
	skip_list<int, int> l;
	///l[1];
	EXPECT_TRUE(l[1] == 0);
}
TEST(AtTest, IntAvarageValues) {
	skip_list<int, int> l;
	l.insert(std::make_pair(1, 0));
	EXPECT_TRUE(l.at(1) == 0);
}
TEST(AtTest, IntEmpty) {
	skip_list<int, int> l;
	try {
		l.at(3) = 'x';
	}
	catch (std::out_of_range const& exc) {
		std::cout << exc.what() << '\n';
	}
}

TEST(EmptyTest, IntEmptySList) {
	skip_list<int, int> l;
	EXPECT_TRUE(l.empty());
}
TEST(EmptyTest, IntNotEmptySList) {
	skip_list<int, int> l;
	l.insert(std::make_pair(1, 0));
	EXPECT_FALSE(l.empty());
}
TEST(SizeTest, IntSListWith3Val) {
	skip_list<int, int> l;
	l.insert(std::make_pair(0, 0));
	l.insert(std::make_pair(2, 0));
	l.insert(std::make_pair(-1, 0));
	EXPECT_FALSE(l.empty());
	EXPECT_EQ(l.size(), 3);
}
TEST(SizeTest, IntEmptySList) {
	skip_list<int, int> l;
	EXPECT_EQ(l.size(), 0);
}
TEST(SizeTest, IntNotEmptySList) {
	skip_list<int, int> l;
	l.insert(std::make_pair(1, 0));
	EXPECT_FALSE(l.empty());
	EXPECT_EQ(l.size(), 1);
}

TEST(FindTest, IntAvarageValues) {
	skip_list<int, int> l;
	auto i = l.insert(std::make_pair(1, 0));
	if (i.second == true) {
		auto it = l.find(1);
		EXPECT_EQ(1, (*it).first);
		EXPECT_EQ(0, (*it).second);
	}
}
TEST(FindTest, IntNoValuesSought) {
	skip_list<int, int> l;
	auto i = l.insert(std::make_pair(1, 0));
	if (i.second == true) {
		auto it = l.find(0);
		EXPECT_TRUE(it == l.end());
	}
}
TEST(ConstFindTest, IntAvarageValues) {
	skip_list<int, int> l;
	auto i = l.insert(std::make_pair(1, 0));
	if (i.second == true) {
		auto const it = l.find(1);
		EXPECT_EQ(1, (*it).first);
		EXPECT_EQ(0, (*it).second);
	}
}
TEST(ConstFindTest, IntNoValuesSought) {
	skip_list<int, int> l;
	auto i = l.insert(std::make_pair(1, 0));
	if (i.second == true) {
		auto const it = l.find(0);
		EXPECT_TRUE(it == l.end());
	}
}

TEST(EraseByKey, IntTwoAvarageValues) {
	skip_list<int, int> l;
	l.insert(std::make_pair(1, 0));
	l.insert(std::make_pair(-1, 0));
	auto result = l.erase(-1);
	EXPECT_EQ(1, result);
	auto it = l.begin();
	EXPECT_EQ(1, (*it).first);
	EXPECT_EQ(0, (*it).second);
}
TEST(EraseByKey, IntNoValuesSought) {
	skip_list<int, int> l;
	l.insert(std::make_pair(1, 0));
	auto result = l.erase(0);
	EXPECT_EQ(0, result);
	auto it = l.begin();
	EXPECT_EQ(1, (*it).first);
	EXPECT_EQ(0, (*it).second);
}
TEST(EraseByIter, IntTwoAvarageValues) {
	skip_list<int, int> l;
	l.insert(std::make_pair(0, 0));
	l.insert(std::make_pair(-1, 0));
	l.erase(l.begin());
	auto it = l.begin();
	EXPECT_EQ(0, (*it).first);
	EXPECT_EQ(0, (*it).second);
}
TEST(EraseByRangeOfIter, IntTwoAvarageValues) {
	skip_list<int, int> l;
	l.insert(std::make_pair(0, -1));
	l.insert(std::make_pair(-1, 0));
	auto it = l.begin();
	auto it2 = l.begin();
	++it2;
	l.erase(it, it2);
	EXPECT_TRUE(l.empty());
}

TEST(ClearTest, IntNoValue) {
	skip_list<int, int> l;
	l.clear();
	EXPECT_TRUE(l.begin() == l.end());
}
TEST(ClearTest, IntAvarageValue) {
	skip_list<int, int> l;
	l.insert(std::make_pair(1, 0));
	l.clear();
	EXPECT_TRUE(l.empty());
}
TEST(ClearTest, IntTwoAvarageValues) {
	skip_list<int, int> l;
	l.insert(std::make_pair(0, -1));
	l.insert(std::make_pair(-1, 0));
	l.clear();
	EXPECT_TRUE(l.empty());
}

TEST(SwapTest, IntOneWithValue) {
	skip_list<int, int> l1;
	skip_list<int, int> l2;
	l1.insert(std::make_pair(1, 0));
	l1.swap(l2);
	EXPECT_TRUE(l1.empty());
}



TEST(ConstructorWithoutArgs, FloatEmpty) {
	skip_list<float, float> l;
	auto i = l.begin();
	EXPECT_EQ((*i).second, 0);
}
TEST(Rrandomlvl, FloatAvarageValues) {
	skip_list<float, float> l;
	auto t = l.random_level();
	size_t max_lvl = l.get_max_lvl();
	EXPECT_TRUE(t <= max_lvl);
}

TEST(Insert, FloatAvarageValues) {
	skip_list<float, float> l;
	auto it = l.insert(std::make_pair(1, 0));
	if (it.second == true) {
		EXPECT_EQ((*it.first).first, 1);
		EXPECT_EQ((*it.first).second, 0);
	}
}
TEST(Insert, FloatTheSameValues) {
	skip_list<float, float> l;
	auto i = l.insert(std::make_pair(1, 0));
	auto it = l.insert(std::make_pair(1, 1));
	EXPECT_TRUE(it.first == i.first);
	if (it.second == true) {
		EXPECT_EQ((*it.first).first, 1);
		EXPECT_EQ((*it.first).second, 1);
	}
}
TEST(Insert, FloatTwoAvarageValues) {
	skip_list<float, float> l;
	l.insert(std::make_pair(1, 0));
	auto it = l.insert(std::make_pair(2, 0));
	if (it.second == true) {
		EXPECT_EQ((*it.first).first, 2);
		EXPECT_EQ((*it.first).second, 0);
	}
}
TEST(Insert, FloatTwoAvarageValuesPositNegat) {
	skip_list<float, float> l;
	l.insert(std::make_pair(1, 0));
	auto i = l.insert(std::make_pair(-1, 0));
	if (i.second == true) {
		EXPECT_EQ((*i.first).first, -1);
		EXPECT_EQ((*i.first).second, 0);
	}
}
TEST(Insert, FloatInsertInHead) {
	skip_list<float, float> l;
	auto i = l.insert(std::make_pair(1, 1));
	auto it = l.insert(std::make_pair(0, 1));

	if (it.second == true) {
		EXPECT_EQ((*it.first).first, 0);
		EXPECT_EQ((*it.first).second, 1);
		EXPECT_EQ(it.first, l.begin());
	}
}

TEST(IteratorTest, FloatFourAvarageValues) {
	skip_list<float, float> l;
	l.insert(std::make_pair(1, 1));
	l.insert(std::make_pair(2, 1));
	l.insert(std::make_pair(3, 1));
	l.insert(std::make_pair(0, 1));
	float counter = 0;
	for (auto it = l.begin(); it != l.end(); ++it) {
		counter++;
	}
	EXPECT_EQ(counter, 4);
}

TEST(OperatorSqBrackets, FloatAvarageValues) {
	skip_list<float, float> l;
	auto it = l.insert(std::make_pair(1, 1));
	if (it.second == true) {
		EXPECT_TRUE(l[1] == 1);
		EXPECT_FALSE(l[1] == 0);
	}
}
TEST(OperatorSqBrackets, FloatEmpty) {
	skip_list<float, float> l;
	l[1];
	EXPECT_TRUE(l[1] == 0);
}
TEST(AtTest, FloatAvarageValues) {
	skip_list<float, float> l;
	l.insert(std::make_pair(1, 0));
	EXPECT_TRUE(l.at(1) == 0);
}
TEST(AtTest, FloatEmpty) {
	skip_list<float, float> l;
	try {
		l.at(3) = 'x';
	}
	catch (std::out_of_range const& exc) {
		std::cout << exc.what() << '\n';
	}
}

TEST(EmptyTest, FloatEmptySList) {
	skip_list<float, float> l;
	EXPECT_TRUE(l.empty());
}
TEST(EmptyTest, FloatNotEmptySList) {
	skip_list<float, float> l;
	l.insert(std::make_pair(1, 0));
	EXPECT_FALSE(l.empty());
}
TEST(SizeTest, FloatSListWith3Val) {
	skip_list<float, float> l;
	l.insert(std::make_pair(0, 0));
	l.insert(std::make_pair(2, 0));
	l.insert(std::make_pair(-1, 0));
	EXPECT_FALSE(l.empty());
	EXPECT_EQ(l.size(), 3);
}
TEST(SizeTest, FloatEmptySList) {
	skip_list<float, float> l;
	EXPECT_EQ(l.size(), 0);
}
TEST(SizeTest, FloatNotEmptySList) {
	skip_list<float, float> l;
	l.insert(std::make_pair(1, 0));
	EXPECT_FALSE(l.empty());
	EXPECT_EQ(l.size(), 1);
}

TEST(FindTest, FloatAvarageValues) {
	skip_list<float, float> l;
	auto i = l.insert(std::make_pair(1, 0));
	if (i.second == true) {
		auto it = l.find(1);
		EXPECT_EQ(1, (*it).first);
		EXPECT_EQ(0, (*it).second);
	}
}
TEST(FindTest, FloatNoValuesSought) {
	skip_list<float, float> l;
	auto i = l.insert(std::make_pair(1, 0));
	if (i.second == true) {
		auto it = l.find(0);
		EXPECT_TRUE(it == l.end());
	}
}
TEST(ConstFindTest, FloatAvarageValues) {
	skip_list<float, float> l;
	auto i = l.insert(std::make_pair(1, 0));
	if (i.second == true) {
		auto const it = l.find(1);
		EXPECT_EQ(1, (*it).first);
		EXPECT_EQ(0, (*it).second);
	}
}
TEST(ConstFindTest, FloatNoValuesSought) {
	skip_list<float, float> l;
	auto i = l.insert(std::make_pair(1, 0));
	if (i.second == true) {
		auto const it = l.find(0);
		EXPECT_TRUE(it == l.end());
	}
}

TEST(EraseByKey, FloatTwoAvarageValues) {
	skip_list<float, float> l;
	l.insert(std::make_pair(1, 0));
	l.insert(std::make_pair(-1, 0));
	auto result = l.erase(-1);
	EXPECT_EQ(1, result);
	auto it = l.begin();
	EXPECT_EQ(1, (*it).first);
	EXPECT_EQ(0, (*it).second);
}
TEST(EraseByKey, FloatNoValuesSought) {
	skip_list<float, float> l;
	l.insert(std::make_pair(1, 0));
	auto result = l.erase(0);
	EXPECT_EQ(0, result);
	auto it = l.begin();
	EXPECT_EQ(1, (*it).first);
	EXPECT_EQ(0, (*it).second);
}
TEST(EraseByIter, FloatTwoAvarageValues) {
	skip_list<float, float> l;
	l.insert(std::make_pair(0, 0));
	l.insert(std::make_pair(-1, 0));
	l.erase(l.begin());
	auto it = l.begin();
	EXPECT_EQ(0, (*it).first);
	EXPECT_EQ(0, (*it).second);
}
TEST(EraseByRangeOfIter, FloatTwoAvarageValues) {
	skip_list<float, float> l;
	l.insert(std::make_pair(0, -1));
	l.insert(std::make_pair(-1, 0));
	auto it = l.begin();
	auto it2 = l.begin();
	++it2;
	l.erase(it, it2);
	EXPECT_TRUE(l.empty());
}

TEST(ClearTest, FloatNoValue) {
	skip_list<float, float> l;
	l.clear();
	EXPECT_TRUE(l.begin() == l.end());
}
TEST(ClearTest, FloatAvarageValue) {
	skip_list<float, float> l;
	l.insert(std::make_pair(1, 0));
	l.clear();
	EXPECT_TRUE(l.empty());
}
TEST(ClearTest, FloatTwoAvarageValues) {
	skip_list<float, float> l;
	l.insert(std::make_pair(0, -1));
	l.insert(std::make_pair(-1, 0));
	l.clear();
	EXPECT_TRUE(l.empty());
}

TEST(SwapTest, FloatOneWithValue) {
	skip_list<float, float> l1;
	skip_list<float, float> l2;
	l1.insert(std::make_pair(1, 0));
	l1.swap(l2);
	EXPECT_TRUE(l1.empty());
}



TEST(ConstructorWithoutArgs, VectorSecondEmpty) {
	skip_list<float, std::vector<int>> l;
	EXPECT_EQ(l.size(), 0);
}
TEST(Rrandomlvl, VectorSecondAvarageValues) {
	skip_list<float, std::vector<int>> l;
	auto t = l.random_level();
	size_t max_lvl = l.get_max_lvl();
	EXPECT_TRUE(t <= max_lvl);
}

TEST(Insert, VectorSecondAvarageValues) {
	skip_list<float, std::vector<int>> l;
	std::vector<int> v = { 1 };
	auto it = l.insert(std::make_pair(1, v));
	if (it.second == true) {
		EXPECT_EQ((*it.first).first, 1);
		EXPECT_EQ((*it.first).second[0], 1);
	}
}
TEST(Insert, VectorSecondTheSameValues) {
	skip_list<float, std::vector<int>> l;
	std::vector<int> v = { 1 };
	auto i = l.insert(std::make_pair(1, v));
	auto it = l.insert(std::make_pair(1, v));
	EXPECT_TRUE(it.first == i.first);
	if (it.second == true) {
		EXPECT_EQ((*it.first).first, 1);
		EXPECT_EQ((*it.first).second[0], 1);
	}
}
TEST(Insert, VectorSecondTwoAvarageValues) {
	skip_list<float, std::vector<int>> l;
	std::vector<int> v = { 1 };
	std::vector<int> v2 = { 0 };
	l.insert(std::make_pair(1, v));
	auto it = l.insert(std::make_pair(2, v2));
	if (it.second == true) {
		EXPECT_EQ((*it.first).first, 2);
		EXPECT_EQ((*it.first).second[0], 0);
	}
}
TEST(Insert, VectorSecondTwoAvarageValuesPositNegat) {
	skip_list<float, std::vector<int>> l;
	std::vector<int> v = { 1 };
	l.insert(std::make_pair(1, v));
	auto i = l.insert(std::make_pair(-1, v));
	if (i.second == true) {
		EXPECT_EQ((*i.first).first, -1);
		EXPECT_EQ((*i.first).second[0], 1);
	}
	auto iter = l.begin();
	EXPECT_EQ((*iter).first, -1);
}
TEST(Insert, VectorSecondInsertInHead) {
	skip_list<float, std::vector<int>> l;
	std::vector<int> v = { 1 };
	auto i = l.insert(std::make_pair(1, v));
	auto it = l.insert(std::make_pair(0, v));

	if (it.second == true) {
		EXPECT_EQ((*it.first).first, 0);
		EXPECT_EQ((*it.first).second[0], 1);
		EXPECT_EQ(it.first, l.begin());
	}
}

TEST(IteratorTest, VectorSecondFourAvarageValues) {
	skip_list<float, std::vector<int>> l;
	std::vector<int> v = { 1 };
	l.insert(std::make_pair(1, v));
	l.insert(std::make_pair(2, v));
	l.insert(std::make_pair(3, v));
	l.insert(std::make_pair(0, v));
	int counter = 0;
	for (auto it = l.begin(); it != l.end(); ++it) {
		counter++;
	}
	EXPECT_EQ(counter, 4);
}

TEST(OperatorSqBrackets, VectorSecondAvarageValues) {
	skip_list<int, std::vector<int>> l;
	std::vector<int> v = { 1 };
	auto it = l.insert(std::make_pair(1, v));
	if (it.second == true) {
		EXPECT_EQ(l[1][0], 1);
		//EXPECT_FALSE(l[1][0] == 0);
	}
}
TEST(OperatorSqBrackets, VectorSecondEmpty) {
	skip_list<float, std::vector<int>> l;
	l[1];
	EXPECT_TRUE(l[1].empty());
}
TEST(AtTest, VectorSecondAvarageValues) {
	skip_list<float, std::vector<int>> l;
	std::vector<int> v = { 0 };
	l.insert(std::make_pair(1, v));
	std::vector<int> v2 = l.at(1);
	//EXPECT_TRUE((l.at(1))[0] == 0);
	EXPECT_TRUE(v2[0] == 0);
}
TEST(AtTest, VectorSecondEmpty) {
	skip_list<float, std::vector<int>> l;
	try {
		l.at(3)[0] = '2';
	}
	catch (std::out_of_range const& exc) {
		std::cout << exc.what() << '\n';
	}
}

TEST(EmptyTest, VectorSecondEmptySList) {
	skip_list<float, std::vector<int>> l;
	EXPECT_TRUE(l.empty());
}
TEST(EmptyTest, VectorSecondNotEmptySList) {
	skip_list<float, std::vector<int>> l;
	std::vector<int> v = { 1 };
	l.insert(std::make_pair(1, v));
	EXPECT_FALSE(l.empty());
}
TEST(SizeTest, VectorSecondSListWith3Val) {
	skip_list<float, std::vector<int>> l;
	std::vector<int> v = { 1 };
	l.insert(std::make_pair(0, v));
	l.insert(std::make_pair(2, v));
	l.insert(std::make_pair(-1, v));
	EXPECT_FALSE(l.empty());
	EXPECT_EQ(l.size(), 3);
}
TEST(SizeTest, VectorSecondEmptySList) {
	skip_list<float, std::vector<int>> l;
	EXPECT_EQ(l.size(), 0);
}
TEST(SizeTest, VectorSecondNotEmptySList) {
	skip_list<float, std::vector<int>> l;
	std::vector<int> v = { 1 };
	l.insert(std::make_pair(1, v));
	EXPECT_FALSE(l.empty());
	EXPECT_EQ(l.size(), 1);
}

TEST(FindTest, VectorSecondAvarageValues) {
	skip_list<float, std::vector<int>> l;
	std::vector<int> v = { 0 };
	auto i = l.insert(std::make_pair(1, v));
	if (i.second == true) {
		auto it = l.find(1);
		EXPECT_EQ(1, (*it).first);
		EXPECT_EQ(0, (*it).second[0]);
	}
}
TEST(FindTest, VectorSecondNoValuesSought) {
	skip_list<float, std::vector<int>> l;
	std::vector<int> v = { 0 };
	auto i = l.insert(std::make_pair(1, v));
	if (i.second == true) {
		auto it = l.find(0);
		EXPECT_TRUE(it == l.end());
	}
}
TEST(ConstFindTest, VectorSecondAvarageValues) {
	skip_list<float, std::vector<int>> l;
	std::vector<int> v = { 1 };
	auto i = l.insert(std::make_pair(1, v));
	if (i.second == true) {
		auto const it = l.find(1);
		EXPECT_EQ(1, (*it).first);
		EXPECT_EQ(1, (*it).second[0]);
	}
}
TEST(ConstFindTest, VectorSecondNoValuesSought) {
	skip_list<float, std::vector<int>> l;
	std::vector<int> v = { 1 };
	auto i = l.insert(std::make_pair(1, v));
	if (i.second == true) {
		auto const it = l.find(0);
		EXPECT_TRUE(it == l.end());
	}
}

TEST(EraseByKey, VectorSecondTwoAvarageValues) {
	skip_list<float, std::vector<int>> l;
	std::vector<int> v = { 0 };
	l.insert(std::make_pair(1, v));
	l.insert(std::make_pair(-1, v));
	auto result = l.erase(-1);
	EXPECT_EQ(1, result);
	auto it = l.begin();
	EXPECT_EQ(1, (*it).first);
	EXPECT_EQ(0, (*it).second[0]);
}
TEST(EraseByKey, VectorSecondNoValuesSought) {
	skip_list<float, std::vector<int>> l;
	std::vector<int> v = { 0 };
	l.insert(std::make_pair(1, v));
	auto result = l.erase(0);
	EXPECT_EQ(0, result);
	auto it = l.begin();
	EXPECT_EQ(1, (*it).first);
	EXPECT_EQ(0, (*it).second[0]);
}
TEST(EraseByIter, VectorSecondTwoAvarageValues) {
	skip_list<float, std::vector<int>> l;
	std::vector<int> v = { 0 };
	l.insert(std::make_pair(0, v));
	l.insert(std::make_pair(-1, v));
	l.erase(l.begin());
	auto it = l.begin();
	EXPECT_EQ(0, (*it).first);
	EXPECT_EQ(0, (*it).second[0]);
}
TEST(EraseByRangeOfIter, VectorSecondTwoAvarageValues) {
	skip_list<float, std::vector<int>> l;
	std::vector<int> v = { -1 };
	std::vector<int> v2 = { 0 };
	l.insert(std::make_pair(0, v));
	l.insert(std::make_pair(-1, v2));
	auto it = l.begin();
	auto it2 = l.begin();
	++it2;
	l.erase(it, it2);
	EXPECT_TRUE(l.empty());
}

TEST(ClearTest, VectorSecondNoValue) {
	skip_list<float, std::vector<int>> l;
	l.clear();
	EXPECT_TRUE(l.begin() == l.end());
}
TEST(ClearTest, VectorSecondAvarageValue) {
	skip_list<float, std::vector<int>> l;
	std::vector<int> v = { 1 };
	l.insert(std::make_pair(1, v));
	l.clear();
	EXPECT_TRUE(l.empty());
}
TEST(ClearTest, VectorSecondTwoAvarageValues) {
	skip_list<float, std::vector<int>> l;
	std::vector<int> v = { 1 };
	l.insert(std::make_pair(0, v));
	l.insert(std::make_pair(-1, v));
	l.clear();
	EXPECT_TRUE(l.empty());
}

TEST(SwapTest, VectorSecondOneWithValue) {
	skip_list<float, std::vector<int>> l1;
	skip_list<float, std::vector<int>> l2;
	std::vector<int> v = { 1 };
	l1.insert(std::make_pair(1, v));
	l1.swap(l2);
	EXPECT_TRUE(l1.empty());
}



TEST(ConstructorWithoutArgs, VectorKeyEmpty) {
	skip_list<std::vector<int>, int> l;
	EXPECT_EQ(l.size(), 0);
}
TEST(Rrandomlvl, VectorKeyAvarageValues) {
	skip_list<std::vector<int>, int> l;
	auto t = l.random_level();
	size_t max_lvl = l.get_max_lvl();
	EXPECT_TRUE(t <= max_lvl);
}

TEST(Insert, VectorKeyAvarageValues) {
	skip_list<std::vector<int>, int> l;
	std::vector<int> v = { 1 };
	auto it = l.insert(std::make_pair(v, 1));
	if (it.second == true) {
		EXPECT_EQ((*it.first).first[0], 1);
		EXPECT_EQ((*it.first).second, 1);
	}
}
TEST(Insert, VectorKeyTheSameValues) {
	skip_list<std::vector<int>, int> l;
	std::vector<int> v = { 1 };
	auto i = l.insert(std::make_pair(v, 1));
	auto it = l.insert(std::make_pair(v, 1));
	EXPECT_TRUE(it.first == i.first);
	if (it.second == true) {
		EXPECT_EQ((*it.first).first[0], 1);
		EXPECT_EQ((*it.first).second, 1);
	}
}
TEST(Insert, VectorKeyTwoAvarageValues) {
	skip_list<std::vector<int>, int> l;
	std::vector<int> v = { 1 };
	std::vector<int> v2 = { 2 };
	l.insert(std::make_pair(v, 1));
	auto it = l.insert(std::make_pair(v2, 0));
	if (it.second == true) {
		EXPECT_EQ((*it.first).first[0], 2);
		EXPECT_EQ((*it.first).second, 0);
	}
}
TEST(Insert, VectorKeyTwoAvarageValuesPositNegat) {
	skip_list<std::vector<int>, int> l;
	std::vector<int> v = { 1 };
	l.insert(std::make_pair(v, 1));
	std::vector<int> v2 = { -1 };
	auto i = l.insert(std::make_pair(v2, 1));
	if (i.second == true) {
		EXPECT_EQ((*i.first).first[0], -1);
		EXPECT_EQ((*i.first).second, 1);
	}
	auto iter = l.begin();
	EXPECT_EQ((*iter).first[0], -1);
}
TEST(Insert, VectorKeyInsertInHead) {
	skip_list<std::vector<int>, int> l;
	std::vector<int> v = { 1 };
	std::vector<int> v2 = { 0 };
	auto i = l.insert(std::make_pair(v, 1));
	auto it = l.insert(std::make_pair(v2, 1));
	if (it.second == true) {
		EXPECT_EQ((*it.first).first[0], 0);
		EXPECT_EQ((*it.first).second, 1);
		EXPECT_EQ(it.first, l.begin());
	}
}

TEST(IteratorTest, VectorKeyThreeAvarageValues) {
	skip_list<std::vector<int>, int> l;
	std::vector<int> v = { 1 };
	std::vector<int> v2 = { 2 };
	std::vector<int> v3 = { 0 };
	l.insert(std::make_pair(v, 1));
	l.insert(std::make_pair(v2, 1));
	l.insert(std::make_pair(v3, 1));
	int counter = 0;
	for (auto it = l.begin(); it != l.end(); ++it) {
		counter++;
	}
	EXPECT_EQ(counter, 3);
}

TEST(OperatorSqBrackets, VectorKeyAvarageValues) {
	skip_list<std::vector<int>, int> l;
	std::vector<int> v = { 1 };
	auto it = l.insert(std::make_pair(v, 1));
	if (it.second == true) {
		EXPECT_EQ(l[v], 1);
		//EXPECT_FALSE(l[1][0] == 0);
	}
}
TEST(AtTest, VectorKeyAvarageValues) {
	skip_list<std::vector<int>, int> l;
	std::vector<int> v = { 1 };
	l.insert(std::make_pair(v, 0));
	int i  = l.at(v);
	//EXPECT_TRUE((l.at(1))[0] == 0);
	EXPECT_EQ(i, 0);
}
TEST(AtTest, VectorKeyEmpty) {
	skip_list<std::vector<int>, int> l;
	std::vector<int> v = { 1 };
	try {
		l.at(v) = 2;
	}
	catch (std::out_of_range const& exc) {
		std::cout << exc.what() << '\n';
	}
}

TEST(EmptyTest, VectorKeyEmptySList) {
	skip_list<std::vector<int>, int> l;
	EXPECT_TRUE(l.empty());
}
TEST(EmptyTest, VectorKeyNotEmptySList) {
	skip_list<std::vector<int>, int> l;
	std::vector<int> v = { 1 };
	l.insert(std::make_pair(v, 0));
	EXPECT_FALSE(l.empty());
}
TEST(SizeTest, VectorKeySListWith3Val) {
	skip_list<std::vector<int>, int> l;
	std::vector<int> v = { 1 };
	std::vector<int> v2 = { 2 };
	std::vector<int> v3 = { 0 };
	l.insert(std::make_pair(v, 1));
	l.insert(std::make_pair(v2, 1));
	l.insert(std::make_pair(v3, 1));
	EXPECT_FALSE(l.empty());
	EXPECT_EQ(l.size(), 3);
}
TEST(SizeTest, VectorKeyEmptySList) {
	skip_list<std::vector<int>, int> l;
	EXPECT_EQ(l.size(), 0);
}
TEST(SizeTest, VectorKeyNotEmptySList) {
	skip_list<std::vector<int>, int> l;
	std::vector<int> v = { 1 };
	l.insert(std::make_pair(v, 1));
	EXPECT_FALSE(l.empty());
	EXPECT_EQ(l.size(), 1);
}

TEST(FindTest, VectorKeyAvarageValues) {
	skip_list<std::vector<int>, int> l;
	std::vector<int> v = { 1 };
	auto i = l.insert(std::make_pair(v, 1));
	if (i.second == true) {
		auto it = l.find(v);
		EXPECT_EQ(1, (*it).first[0]);
		EXPECT_EQ(1, (*it).second);
	}
}
TEST(FindTest, VectorKeyNoValuesSought) {
	skip_list<std::vector<int>, int> l;
	std::vector<int> v = { 0 };
	std::vector<int> v2 = { 1 };
	auto i = l.insert(std::make_pair(v, 1));
	if (i.second == true) {
		auto it = l.find(v2);
		EXPECT_TRUE(it == l.end());
	}
}
TEST(ConstFindTest, VectorKeyAvarageValues) {
	skip_list<std::vector<int>, int> l;
	std::vector<int> v = { 1 };
	auto i = l.insert(std::make_pair(v, 1));
	if (i.second == true) {
		auto const it = l.find(v);
		EXPECT_EQ(1, (*it).first[0]);
		EXPECT_EQ(1, (*it).second);
	}
}
TEST(ConstFindTest, VectorKeyNoValuesSought) {
	skip_list<std::vector<int>, int> l;
	std::vector<int> v = { 1 };
	std::vector<int> v2 = { -1 };
	auto i = l.insert(std::make_pair(v, 1));
	if (i.second == true) {
		auto const it = l.find(v2);
		EXPECT_TRUE(it == l.end());
	}
}

TEST(EraseByKey, VectorKeyTwoAvarageValues) {
	skip_list<std::vector<int>, int> l;
	std::vector<int> v = { 1 };
	std::vector<int> v2 = { -1 };
	l.insert(std::make_pair(v, 1));
	l.insert(std::make_pair(v2, 1));
	auto result = l.erase(v2);
	EXPECT_EQ(1, result);
	auto it = l.begin();
	EXPECT_EQ(1, (*it).first[0]);
	EXPECT_EQ(1, (*it).second);
}
TEST(EraseByKey, VectorKeyNoValuesSought) {
	skip_list<std::vector<int>, int> l;
	std::vector<int> v = { 1 };
	std::vector<int> v2 = { -1 };
	l.insert(std::make_pair(v, 1));
	auto result = l.erase(v2);
	EXPECT_EQ(0, result);
	auto it = l.begin();
	EXPECT_EQ(1, (*it).first[0]);
	EXPECT_EQ(1, (*it).second);
}
TEST(EraseByIter, VectorKeyTwoAvarageValues) {
	skip_list<std::vector<int>, int> l;
	std::vector<int> v = { 0 };
	std::vector<int> v2 = { -1 };
	l.insert(std::make_pair(v, 0));
	l.insert(std::make_pair(v2, 1));
	l.erase(l.begin());
	auto it = l.begin();
	EXPECT_EQ(0, (*it).first[0]);
	EXPECT_EQ(0, (*it).second);
}
TEST(EraseByRangeOfIter, VectorKeyTwoAvarageValues) {
	skip_list<std::vector<int>, int> l;
	std::vector<int> v = { -1 };
	std::vector<int> v2 = { 0 };
	l.insert(std::make_pair(v, 0));
	l.insert(std::make_pair(v2, 1));
	auto it = l.begin();
	auto it2 = l.begin();
	++it2;
	l.erase(it, it2);
	EXPECT_TRUE(l.empty());
}

TEST(ClearTest, VectorKeyNoValue) {
	skip_list<std::vector<int>, int> l;
	l.clear();
	EXPECT_TRUE(l.begin() == l.end());
}
TEST(ClearTest, VectorKeyAvarageValue) {
	skip_list<std::vector<int>, int> l;
	std::vector<int> v = { 1 };
	l.insert(std::make_pair(v, 0));
	l.clear();
	EXPECT_TRUE(l.empty());
}
TEST(ClearTest, VectorKeyTwoAvarageValues) {
	skip_list<std::vector<int>, int> l;
	std::vector<int> v = { -1 };
	std::vector<int> v2 = { 0 };
	l.insert(std::make_pair(v, 0));
	l.insert(std::make_pair(v2, 1));
	l.clear();
	EXPECT_TRUE(l.empty());
}

TEST(SwapTest, VectorKeyOneWithValue) {
	skip_list<std::vector<int>, int> l1;
	skip_list<std::vector<int>, int> l2;
	std::vector<int> v = { 1 };
	l1.insert(std::make_pair(v, 0));
	l1.swap(l2);
	EXPECT_TRUE(l1.empty());
}

GTEST_API_ int main(int argc, char* argv[])
{
	if (argc > 0)
	{
		testing::internal::FilePath arg(argv[0]);
		const auto name = arg.RemoveDirectoryName().RemoveExtension("exe").string();
		testing::GTEST_FLAG(output) = std::string("xml:") + name + ".xml";
	}
	testing::InitGoogleTest(&argc, argv);
#if defined(_MSC_VER)
	testing::UnitTest::GetInstance()->listeners().Append(new testing::MSVCMemoryLeakListener());
#endif // defined(_MSC_VER)
	return RUN_ALL_TESTS();
}