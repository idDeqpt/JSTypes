#include <iostream>
#include <JSTypes/JSTypes.hpp>


int main()
{
	jst::JSBoolean bol;
	std::cout << bol.toString() << std::endl;

	jst::JSBoolean bol1(false);
	std::cout << bol1.toString() << std::endl << std::endl;

	jst::JSNumber num;
	std::cout << num.toString() << std::endl;

	jst::JSNumber num1(7);
	std::cout << num1.toString() << std::endl;

	jst::JSNumber num2;
	num2 = 78;
	std::cout << num2.toString() << std::endl << std::endl;


	jst::JSString str;
	std::cout << str.toString() << std::endl;

	jst::JSString str1(13);
	std::cout << str1.toString() << std::endl;

	jst::JSString str2("stddy");
	std::cout << str2.toString() << std::endl;

	jst::JSString str3;
	str3 = "dsljf";
	std::cout << str3.toString() << std::endl << std::endl;


	jst::JSObject obj;
	std::cout << obj.toString() << std::endl;

	jst::JSObject obj1;
	obj1.addField("key1");
	obj1["key1"] = new jst::JSBaseType();
	obj1.addField("key2");
	obj1["key2"] = new jst::JSBoolean(true);
	obj1.addField("key3");
	obj1["key3"] = new jst::JSNumber(34);
	obj1.addField("key4");
	obj1["key4"] = new jst::JSString("abbebe");
	std::cout << obj1.toString() << std::endl;

	jst::JSObject obj2;
	obj2.addField("key2");
	obj2["key2"] = new jst::JSNumber(304);
	obj2.addField("key3");
	obj2["key3"] = new jst::JSNumber(34);
	obj2.removeField("key3");
	std::cout << obj2.toString() << std::endl;

	system("pause");
	return 0;
}