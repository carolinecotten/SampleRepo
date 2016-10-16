#include "lliststring.h"
#include "gtest/gtest.h"

TEST(LListStringTest, Nominal) {
	LListString list1; 
	list1.insert(0, "Hello");
	LListString list2 = LListString(list1); 
	EXPECT_EQ("Hello", list2.get(0));
	std::cout << "Copy Test" << std::endl; 

	//testing operator=
	LListString list3; 
	list3.insert(0, "Caroline"); 
	list3.insert(1, "is");
	list3.insert(2, "cool");
	list2 = list3; 
	EXPECT_EQ("cool", list2.get(2)); 
	std::cout << "= Test" << std::endl; 


	//testing operator+
	LListString list4; 
	list4 = list1 + list3; 
	EXPECT_EQ("Hello", list4.get(0));
	EXPECT_EQ("cool", list4.get(3)); 
	std::cout << "+ Test" << std::endl; 

}
/*
TEST(LListStringTest, Boundary) {
	Fibonacci f;
	EXPECT_EQ(1, f.get(1));
	EXPECT_EQ(1, f.get(2));
}

TEST(LListStringTest, OffNominal) {
	Fibonacci f;
	EXPECT_EQ(0, f.get(0));
	EXPECT_EQ(0, f.get(-7));
}*/