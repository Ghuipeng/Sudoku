#include "pch.h"
#include "CppUnitTest.h"
#include "../myShudu/GenerateSuodekuFromFinal.h"
#include "../myShudu/GetAnswer.h"
#include "../myShudu/ProduceFinal.h"
#include "../myShudu/Read_Write_File.h"
#include "../myShudu/Unittest.h"
#define HIGH_LIMIT 55

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test
{
	TEST_CLASS(Test)
	{
	public:
		
		TEST_METHOD(TestMethod1)	//测试用例，测试函数：难度计算
		{
			int place[] = { 0, 1, 3, 5, 7, 8 };
			int length = 6;
			int place_2[] = { 0, 1, 3, 5,6, 7, 8,10,11,12,13,14,16,18,21,22,25,26,28,29,31,34,35,38,41,42,44,45,47,49,51,53,54,55,56,57,59,61,62,64,66,67,69,71,72,74,77,78,79,80 };
			int length_2 = 50;
			Assert::AreEqual(1, GetDiffcult(place, length));
			Assert::AreEqual(3, GetDiffcult(place_2, length_2));
		}
		TEST_METHOD(TestMethod2)	//测试用例，测试函数：生成挖空位置序列
		{
			int place[HIGH_LIMIT] = { 0 };
			int low = 20, high = 55;
			int length = GetBlankPlace(place, 0, low, high);
			Assert::IsTrue(length >= 20 && length <= 55);
		}
		TEST_METHOD(TestMethod3)	//测试用例，测试函数：main---生成数独终局
		{
			std::string error = "input param after '-c' error!\n";

			std::stringstream buffer;
			std::streambuf* sbuf = std::cout.rdbuf();
			std::cout.rdbuf(buffer.rdbuf());

			char* argv[] = { "./myShudu.exe", "-c", "6" };
			int argc = sizeof(argv) / sizeof(const char*);
			int result = unittest(argc, argv);

			std::cout.rdbuf(sbuf);
			std::cout << buffer.get();

			Assert::AreNotEqual(error, buffer.str());
		}
		TEST_METHOD(TestMethod4)	//测试用例，测试函数：main---读取数独并解答和保存
		{
			std::string error = "please input something after -s\n";

			std::stringstream buffer;
			std::streambuf* sbuf = std::cout.rdbuf();
			std::cout.rdbuf(buffer.rdbuf());

			char* argv[] = { "./myShudu.exe", "-s", "./game.txt" };
			int argc = sizeof(argv) / sizeof(const char*);
			int result = unittest(argc, argv);

			std::cout.rdbuf(sbuf);
			std::cout << buffer.get();

			Assert::AreNotEqual(error, buffer.str());
		}
		TEST_METHOD(TestMethod5)	//测试用例，测试函数：main---从终局生成数独游戏并保存（参数正确）
		{
			std::string error = "input param after '-n' error!\n";

			std::stringstream buffer;
			std::streambuf* sbuf = std::cout.rdbuf();
			std::cout.rdbuf(buffer.rdbuf());

			char* argv[] = { "./myShudu.exe", "-n", "6" };
			int argc = sizeof(argv) / sizeof(const char*);
			int result = unittest(argc, argv);

			std::cout.rdbuf(sbuf);
			std::cout << buffer.get();

			Assert::AreNotEqual(error, buffer.str());
		}
		TEST_METHOD(TestMethod6)	//测试用例，测试函数：main---从终局生成数独游戏并保存（参数超出范围）
		{
			std::string error = "input param after '-n' error!\n";

			std::stringstream buffer;
			std::streambuf* sbuf = std::cout.rdbuf();
			std::cout.rdbuf(buffer.rdbuf());

			char* argv[] = { "./myShudu.exe", "-n", "10001" };
			int argc = sizeof(argv) / sizeof(const char*);
			int result = unittest(argc, argv);

			std::cout.rdbuf(sbuf);
			std::cout << buffer.get();

			Assert::AreEqual(error, buffer.str());
		}
		TEST_METHOD(TestMethod7)	//测试用例，测试函数：main---从终局生成数独游戏并保存，且指定难度（参数正确）
		{
			std::string error = "params error!\n";

			std::stringstream buffer;
			std::streambuf* sbuf = std::cout.rdbuf();
			std::cout.rdbuf(buffer.rdbuf());

			char* argv[] = { "./myShudu.exe", "-n", "6", "-m", "2" };
			int argc = sizeof(argv) / sizeof(const char*);
			int result = unittest(argc, argv);

			std::cout.rdbuf(sbuf);
			std::cout << buffer.get();

			Assert::AreNotEqual(error, buffer.str());
		}
		TEST_METHOD(TestMethod8)	//测试用例，测试函数：main---从终局生成数独游戏并保存，且指定难度（参数超出范围）
		{
			std::string error = "params error!\n";

			std::stringstream buffer;
			std::streambuf* sbuf = std::cout.rdbuf();
			std::cout.rdbuf(buffer.rdbuf());

			char* argv[] = { "./myShudu.exe", "-n", "6", "-m", "4" };
			int argc = sizeof(argv) / sizeof(const char*);
			int result = unittest(argc, argv);

			std::cout.rdbuf(sbuf);
			std::cout << buffer.get();

			Assert::AreEqual(error, buffer.str());
		}
		TEST_METHOD(TestMethod9)	//测试用例，测试函数：main---从终局生成数独游戏并保存，且指定挖空数的范围（参数正确）
		{
			std::string error = "arg2[4] has no '~' symbol!\n";
			std::string error2 = "params error!\n";

			std::stringstream buffer;
			std::streambuf* sbuf = std::cout.rdbuf();
			std::cout.rdbuf(buffer.rdbuf());

			char* argv[] = { "./myShudu.exe", "-n", "6", "-r", "30~50" };
			int argc = sizeof(argv) / sizeof(const char*);
			int result = unittest(argc, argv);

			std::cout.rdbuf(sbuf);
			std::cout << buffer.get();

			Assert::IsTrue(buffer.str() != error && buffer.str() != error2);
		}
		TEST_METHOD(TestMethod10)	//测试用例，测试函数：main---从终局生成数独游戏并保存，且指定挖空数的范围（参数超出范围/ 参数格式有误）
		{
			std::string error = "arg2[4] has no '~' symbol!\n";
			std::string error2 = "params error!\n";

			std::stringstream buffer;
			std::streambuf* sbuf = std::cout.rdbuf();
			std::cout.rdbuf(buffer.rdbuf());

			char* argv[] = { "./myShudu.exe", "-n", "6", "-r", "30-50" };
			int argc = sizeof(argv) / sizeof(const char*);
			int result = unittest(argc, argv);

			std::cout.rdbuf(sbuf);
			std::cout << buffer.get();

			Assert::IsFalse(buffer.str() != error && buffer.str() != error2);
		}
		TEST_METHOD(TestMethod11)	//测试用例，测试函数：main---从终局生成数独游戏并保存，且这些游戏的解都需要唯一
		{
			std::string error = "param argv[3] error!\n";

			std::stringstream buffer;
			std::streambuf* sbuf = std::cout.rdbuf();
			std::cout.rdbuf(buffer.rdbuf());

			char* argv[] = { "./myShudu.exe", "-n", "6", "-u" };
			int argc = sizeof(argv) / sizeof(const char*);
			int result = unittest(argc, argv);

			std::cout.rdbuf(sbuf);
			std::cout << buffer.get();

			Assert::AreNotEqual(error, buffer.str());
		}
	};
}
