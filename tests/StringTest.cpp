#include "String.h"

#include <iostream>
#include <cassert>

void testConstructors();
void testCompare();
void testFind();
void testReplace();
void testRemove();
void testInsert();
void testSplit();
void testUtils();
void testOperatots();
void testIterators();

std::string strTestA = "testA";
std::string strTestB = "testB";
std::string strTestC = "testC";
std::string strTestCC = "testCC";

int main()
{
    testConstructors();
    testCompare();
    testFind();
    testReplace();
    testRemove();
    testInsert();
    testSplit();
    testUtils();
    testOperatots();
    testIterators();
}

void testIterators()
{
    String str1(strTestA);
    std::string str;

    for (char &ch : str1)
        str += ch;
    assert(str == strTestA);

    str = "";
    for (auto it = str1.end() - 1; it >= str1.begin(); --it)
        str += *it;
    assert(str == "Atset");

    auto it = str1.begin();
    assert(it[2] == 's');

    std::cout << "testIterators OK" << std::endl;
}

void testOperatots()
{
    String str1(strTestA);
    String str2(strTestB);
    String str3(strTestC);

    assert(str1[1] == 'e');
    assert((str3 + 'C').toString() == strTestCC);
    assert((str1 + str2).toString() == str1.append(str2).toString());

    assert(str1 == str1);
    assert(str1 != str2);
    assert(str1 >= str1);
    assert(str1 <= str2);
    assert(str3 > str2);
    assert(str1 < str2);

    str1[0] = 'a';
    assert(str1.toString() == "aestA");

    std::cout << "testOperators OK" << std::endl;
}

void testUtils()
{
    String str1(strTestA);
    String str2(strTestB);
    String str3;

    assert(str1.hash() != str2.hash());
    assert(str1.toLower().toString() == "testa");
    assert(str2.toUpper().toString() == "TESTB");
    auto temp = str1.toCharArray();
    assert(std::string(temp.first, temp.second) == str1.toString());
    assert(!str2.empty());
    assert(str3.empty());
    assert(str1.size() == 5);
    assert(str3.size() == 0);

    std::cout << "testUtils OK" << std::endl;
}

void testSplit()
{
    String str1(strTestA);
    String str2(strTestB);
    str1 = str1.append(str2);

    auto strs = str1.split('e');
    assert(strs.size() == 3);
    assert(strs[0].toString() == "stB");
    strs = str1.split(new char[2] { 'e', 'A'}, 2);
    assert(strs.size() == 4);
    assert(strs[3].toString() == "t");

    std::cout << "testSplit OK" << std::endl;
}

void testInsert()
{
    String str1(strTestA);
    String str2(strTestB);
    String str3(strTestC);
    String str4(strTestCC);

    assert(str1.insert(4, str2).toString() == "testtestBA");
    assert(str1.append(str3).toString() == "testAtestC");
    assert(str4.append('4').toString() == "testCC4");

    std::cout << "testInsert OK" << std::endl;
}

void testRemove()
{
    String str3(strTestC);
    String str4(strTestCC);

    assert(str4.remove(0, 3).toString() == "tCC");
    assert(str3.remove(4, 6).toString() == "test");

    std::cout << "testRemove OK" << std::endl;
}

void testReplace()
{
    String str2(strTestB);
    String str3(strTestC);
    String str4(strTestCC);

    assert(str4.replace('C', 'A').toString() == "testAA");
    assert(str4.replace(str3, str2).toString() == "testBC");

    std::cout << "testReplace OK" << std::endl;
}

void testFind()
{
    String str3(strTestC);
    String str4(strTestCC);

    assert(str4.contains(str3));
    assert(str4.find('C') == 4);
    assert(str3.find(str3) == 0);

    std::cout << "testFind OK" << std::endl;
}

void testCompare()
{
    String str1(strTestA);
    String str2(strTestB);
    String str3(strTestC);
    String str4(strTestCC);

    assert(!str1.equals(str2));
    assert(str1.equals(str1));
    assert(str1.compareTo(str2) < 0);
    assert(str3.compareTo(str4) > 0);
    assert(str2.compareTo(str2) == 0);

    std::cout << "testCompare OK" << std::endl;
}

void testConstructors()
{
    String str1(strTestA);
    String str2(strTestA.c_str(), strTestA.size());
    String str3(str1);
    String str4 = str1;

    assert(&str1 != &str3);
    assert(&str1 != &str4);
    assert(str1 == str2);
    assert(str1 == str3);
    assert(str1 == str4);

    String str0;
    String str5(std::move(str1));
    String str6 = std::move(str2);
    String str7(str0);

    assert(str5.toString() == strTestA);
    assert(str6.toString() == strTestA);
    assert(str1.empty());
    assert(str2.toString() == "");
    assert(str7.empty());

    std::cout << "testConstructors OK" << std::endl;
}