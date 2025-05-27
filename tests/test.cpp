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
	obj1.addField("key1", std::make_shared<jst::JSBaseType>());
	obj1.addField("key2", std::make_shared<jst::JSBoolean>(true));
	obj1.addField("key3", std::make_shared<jst::JSNumber>(34));
	obj1.addField("key4", std::make_shared<jst::JSString>("abbebe"));
	obj1.addField("key5", std::make_shared<jst::JSNumber>());
	std::cout << obj1.toString() << std::endl;

	jst::JSObject obj2;
	obj2.addField("key2", std::make_shared<jst::JSNumber>(304));
	obj2.addField("key3", std::make_shared<jst::JSNumber>(34));
	obj2.removeField("key3");
	std::cout << obj2.toString() << std::endl;

	jst::JSObject obj3;
	obj3.addField("key1", std::make_shared<jst::JSObject>(obj1));
	obj3.addField("key2", std::make_shared<jst::JSObject>(obj3));
	std::cout << obj3.toString() << std::endl << std::endl;


	jst::JSArray arr;
	std::cout << arr.toString() << std::endl;

	jst::JSArray arr1;
	arr1.pushBack(std::make_shared<jst::JSBaseType>());
	arr1.pushBack(std::make_shared<jst::JSNumber>());
	arr1.pushBack(std::make_shared<jst::JSNumber>(45));
	arr1.pushBack(std::make_shared<jst::JSObject>(obj1));
	std::cout << arr1.toString() << std::endl;

	jst::JSArray arr2;
	arr2.pushBack(std::make_shared<jst::JSNumber>(45));
	arr2.pushBack(std::make_shared<jst::JSNumber>(405));
	arr2.pushBack(std::make_shared<jst::JSNumber>(45));
	arr2.popBack();
	std::cout << arr2.toString() << std::endl;

	jst::JSArray arr3;
	arr3.pushBack(std::make_shared<jst::JSArray>(arr2));
	arr3.pushBack(std::make_shared<jst::JSArray>(arr3));
	arr3.popBack();
	std::cout << arr2.toString() << arr3.toString() << std::endl;




	system("pause");
	return 0;
}