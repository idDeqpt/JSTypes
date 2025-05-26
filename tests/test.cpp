#include <iostream>
#include <JSTypes/JSTypes.hpp>


int main()
{
	jst::JSNumber num;
	jst::JSNumber num1(7);
	jst::JSNumber num2;
	num2 = 78;

	jst::JSString str;
	jst::JSString str1(13);
	jst::JSString str2("stddy");
	jst::JSString str3;
	str3 = "dsljf";

	std::cout << num.toString() << std::endl;
	std::cout << num1.toString() << std::endl;
	std::cout << num2.toString() << std::endl;
	std::cout << str.toString() << std::endl;
	std::cout << str1.toString() << std::endl;
	std::cout << str2.toString() << std::endl;
	std::cout << str3.toString() << std::endl;

	system("pause");
	return 0;
}