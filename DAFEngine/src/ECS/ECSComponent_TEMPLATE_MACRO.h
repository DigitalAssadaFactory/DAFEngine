#pragma once

/*   MACRO FACTORY FUNCTION IF MORE VARIANTS ARE NEEDED
#include <fstream>
static void MakeECSComponentMacro(std::string fileName, size_t numMacros)
{
	std::ofstream out(fileName);
	std::string _register;

	for (size_t i = 1; i <= numMacros; ++i)
	{
		_register += "#define REGISTER_ECSComponent_";
		std::string _number;
		if (i < 10) _number = "0" + std::to_string(i);
		else _number = std::to_string(i);

		_register += _number + "\\\n(componentName";

		for (size_t j = 1; j <= i; ++j)
		{
			std::string _type = "type" + std::to_string(j);
			std::string _name = "name" + std::to_string(j);
			_register += ",\\\n" + _type + ", " + _name;
		}
		_register += ")\\\nnamespace ECS::Component {\\\nstruct componentName : ECSBase::ECSComponent<componentName> {\\\n";
		_register += "\\\nstruct Wrapper {\\\nWrapper(size_t index)\\\n";

		_register += ": name1(componentName::name1[index])";
		for (size_t j = 2; j <= i; ++j)
		{
			std::string _name = "name" + std::to_string(j);
			_register += ",\\\n" + _name + "(componentName::" + _name + "[index])";
		}
		_register += " {}";

		for (size_t j = 1; j <= i; ++j)
		{
			std::string _type = "type" + std::to_string(j);
			std::string _name = "name" + std::to_string(j);
			_register += "\\\n" + _type + "& " + _name + ";";
		}
		_register += "\\\n};";
		_register += "\\\n\\\nstatic size_t Create() {\\\n";
		_register += "if(free.empty())\\\n{";

		for (size_t j = 1; j <= i; ++j)
		{
			std::string _name = "name" + std::to_string(j);
			_register += "\\\n" + _name + ".resize(" + _name + ".size() + 1);";
		}
		_register += "\\\nreturn name1.size() - 1;\\\n}\\\nelse\\\n{\\\nsize_t index = free.front();\\\nfree.pop();\\\nreturn index;\\\n}\\\n}\\\n";

		_register += "\\\nstatic size_t Copy(const size_t & source) {";
		_register += "\\\n if(free.empty()) {\\\nsize_t newSize = name1.size() + 1;\\\nsize_t index = name1.size();";

		for (size_t j = 1; j <= i; ++j)
		{
			std::string _name = "name" + std::to_string(j);
			_register += "\\\n" + _name + ".resize(newSize);";
		}
		for (size_t j = 1; j <= i; ++j)
		{
			std::string _name = "name" + std::to_string(j);
			_register += "\\\n" + _name + "[index] = " + _name + "[source];";
		}
		_register += "\\\nreturn index;\\\n}\\\nelse {\\\nsize_t index = free.front();\\\nfree.pop();";
		for (size_t j = 1; j <= i; ++j)
		{
			std::string _name = "name" + std::to_string(j);
			_register += "\\\n" + _name + "[index] = " + _name + "[source];";
		}
		_register += "\\\nreturn index;\\\n}\\\n}\\\n";

		_register += "\\\nstatic void Delete(size_t index) {\\\nfree.push(index);\\\n}";

		_register += "\\\n\\\nstatic size_t Version;\\\nstatic std::queue<size_t> free;";

		for (size_t j = 1; j <= i; ++j)
		{
			std::string _type = "type" + std::to_string(j);
			std::string _name = "name" + std::to_string(j);
			_register += "\\\nstatic std::vector<" + _type + "> " + _name + ";";
		}

		_register += "\\\n};\\\n}\\\n\n\n";

		//------------------------ INIT ----------------------------------\\

		_register += "#define INIT_ECSComponent_";
		_register += _number + "\\\n(componentName";

		for (size_t j = 1; j <= i; ++j)
		{
			std::string _type = "type" + std::to_string(j);
			std::string _name = "name" + std::to_string(j);
			_register += ",\\\n" + _type + ", " + _name;
		}
		_register += ")\\\nnamespace ECS::Component {";
		_register += "\\\nsize_t componentName::Version(1);";
		_register += "\\\nstd::queue<size_t> componentName::free;";

		for (size_t j = 1; j <= i; ++j)
		{
			std::string _type = "type" + std::to_string(j);
			std::string _name = "name" + std::to_string(j);
			_register += "\\\nstd::vector<" + _type + "> componentName::" + _name + "(1);";
		}
		_register += "\\\n}\n\n\n\n\n\n\n\n";
	}

	out << _register;
	out.close();
}
*/



namespace DAF
{


#define REGISTER_ECSComponent_01\
(componentName,\
type1, name1)\
namespace ECS::Component {\
struct componentName : ECSBase::ECSComponent<componentName> {\
\
struct Wrapper {\
Wrapper(size_t index)\
: name1(componentName::name1[index]),\
id(index) {}\
type1& name1;\
const size_t id;\
};\
\
static size_t Create() {\
if(free.empty()) {\
size_t newSize = name1.size() + 1;\
size_t index = name1.size();\
name1.resize(newSize);\
return index;\
}\
else {\
size_t index = free.front();\
free.pop();\
return index;\
}\
}\
\
static size_t Copy(const size_t & source) {\
 if(free.empty()) {\
size_t newSize = name1.size() + 1;\
size_t index = name1.size();\
name1.resize(newSize);\
name1[index] = name1[source];\
return index;\
}\
else {\
size_t index = free.front();\
free.pop();\
name1[index] = name1[source];\
return index;\
}\
}\
\
static void Delete(size_t index) {\
if(index==0)return;\
free.push(index);\
}\
\
static std::queue<size_t> free;\
static std::vector<type1> name1;\
};\
}


#define INIT_ECSComponent_01\
(componentName,\
type1, name1)\
namespace ECS::Component {\
std::queue<size_t> componentName::free;\
std::vector<type1> componentName::name1(1);\
}







#define REGISTER_ECSComponent_02\
(componentName,\
type1, name1,\
type2, name2)\
namespace ECS::Component {\
struct componentName : ECSBase::ECSComponent<componentName> {\
\
struct Wrapper {\
Wrapper(size_t index)\
: name1(componentName::name1[index]),\
name2(componentName::name2[index]),\
id(index) {}\
type1& name1;\
type2& name2;\
const size_t id;\
};\
\
static size_t Create() {\
if(free.empty()) {\
size_t newSize = name1.size() + 1;\
size_t index = name1.size();\
name1.resize(newSize);\
name2.resize(newSize);\
return index;\
}\
else {\
size_t index = free.front();\
free.pop();\
return index;\
}\
}\
\
static size_t Copy(const size_t & source) {\
 if(free.empty()) {\
size_t newSize = name1.size() + 1;\
size_t index = name1.size();\
name1.resize(newSize);\
name2.resize(newSize);\
name1[index] = name1[source];\
name2[index] = name2[source];\
return index;\
}\
else {\
size_t index = free.front();\
free.pop();\
name1[index] = name1[source];\
name2[index] = name2[source];\
return index;\
}\
}\
\
static void Delete(size_t index) {\
if(index==0)return;\
free.push(index);\
}\
\
static std::queue<size_t> free;\
static std::vector<type1> name1;\
static std::vector<type2> name2;\
};\
}


#define INIT_ECSComponent_02\
(componentName,\
type1, name1,\
type2, name2)\
namespace ECS::Component {\
std::queue<size_t> componentName::free;\
std::vector<type1> componentName::name1(1);\
std::vector<type2> componentName::name2(1);\
}







#define REGISTER_ECSComponent_03\
(componentName,\
type1, name1,\
type2, name2,\
type3, name3)\
namespace ECS::Component {\
struct componentName : ECSBase::ECSComponent<componentName> {\
\
struct Wrapper {\
Wrapper(size_t index)\
: name1(componentName::name1[index]),\
name2(componentName::name2[index]),\
name3(componentName::name3[index]),\
id(index) {}\
type1& name1;\
type2& name2;\
type3& name3;\
const size_t id;\
};\
\
static size_t Create() {\
if(free.empty()) {\
size_t newSize = name1.size() + 1;\
size_t index = name1.size();\
name1.resize(newSize);\
name2.resize(newSize);\
name3.resize(newSize);\
return index;\
}\
else {\
size_t index = free.front();\
free.pop();\
return index;\
}\
}\
\
static size_t Copy(const size_t & source) {\
 if(free.empty()) {\
size_t newSize = name1.size() + 1;\
size_t index = name1.size();\
name1.resize(newSize);\
name2.resize(newSize);\
name3.resize(newSize);\
name1[index] = name1[source];\
name2[index] = name2[source];\
name3[index] = name3[source];\
return index;\
}\
else {\
size_t index = free.front();\
free.pop();\
name1[index] = name1[source];\
name2[index] = name2[source];\
name3[index] = name3[source];\
return index;\
}\
}\
\
static void Delete(size_t index) {\
if(index==0)return;\
free.push(index);\
}\
\
static std::queue<size_t> free;\
static std::vector<type1> name1;\
static std::vector<type2> name2;\
static std::vector<type3> name3;\
};\
}


#define INIT_ECSComponent_03\
(componentName,\
type1, name1,\
type2, name2,\
type3, name3)\
namespace ECS::Component {\
std::queue<size_t> componentName::free;\
std::vector<type1> componentName::name1(1);\
std::vector<type2> componentName::name2(1);\
std::vector<type3> componentName::name3(1);\
}







#define REGISTER_ECSComponent_04\
(componentName,\
type1, name1,\
type2, name2,\
type3, name3,\
type4, name4)\
namespace ECS::Component {\
struct componentName : ECSBase::ECSComponent<componentName> {\
\
struct Wrapper {\
Wrapper(size_t index)\
: name1(componentName::name1[index]),\
name2(componentName::name2[index]),\
name3(componentName::name3[index]),\
name4(componentName::name4[index]),\
id(index) {}\
type1& name1;\
type2& name2;\
type3& name3;\
type4& name4;\
const size_t id;\
};\
\
static size_t Create() {\
if(free.empty()) {\
size_t newSize = name1.size() + 1;\
size_t index = name1.size();\
name1.resize(newSize);\
name2.resize(newSize);\
name3.resize(newSize);\
name4.resize(newSize);\
return index;\
}\
else {\
size_t index = free.front();\
free.pop();\
return index;\
}\
}\
\
static size_t Copy(const size_t & source) {\
 if(free.empty()) {\
size_t newSize = name1.size() + 1;\
size_t index = name1.size();\
name1.resize(newSize);\
name2.resize(newSize);\
name3.resize(newSize);\
name4.resize(newSize);\
name1[index] = name1[source];\
name2[index] = name2[source];\
name3[index] = name3[source];\
name4[index] = name4[source];\
return index;\
}\
else {\
size_t index = free.front();\
free.pop();\
name1[index] = name1[source];\
name2[index] = name2[source];\
name3[index] = name3[source];\
name4[index] = name4[source];\
return index;\
}\
}\
\
static void Delete(size_t index) {\
if(index==0)return;\
free.push(index);\
}\
\
static std::queue<size_t> free;\
static std::vector<type1> name1;\
static std::vector<type2> name2;\
static std::vector<type3> name3;\
static std::vector<type4> name4;\
};\
}


#define INIT_ECSComponent_04\
(componentName,\
type1, name1,\
type2, name2,\
type3, name3,\
type4, name4)\
namespace ECS::Component {\
std::queue<size_t> componentName::free;\
std::vector<type1> componentName::name1(1);\
std::vector<type2> componentName::name2(1);\
std::vector<type3> componentName::name3(1);\
std::vector<type4> componentName::name4(1);\
}







#define REGISTER_ECSComponent_05\
(componentName,\
type1, name1,\
type2, name2,\
type3, name3,\
type4, name4,\
type5, name5)\
namespace ECS::Component {\
struct componentName : ECSBase::ECSComponent<componentName> {\
\
struct Wrapper {\
Wrapper(size_t index)\
: name1(componentName::name1[index]),\
name2(componentName::name2[index]),\
name3(componentName::name3[index]),\
name4(componentName::name4[index]),\
name5(componentName::name5[index]),\
id(index) {}\
type1& name1;\
type2& name2;\
type3& name3;\
type4& name4;\
type5& name5;\
const size_t id;\
};\
\
static size_t Create() {\
if(free.empty()) {\
size_t newSize = name1.size() + 1;\
size_t index = name1.size();\
name1.resize(newSize);\
name2.resize(newSize);\
name3.resize(newSize);\
name4.resize(newSize);\
name5.resize(newSize);\
return index;\
}\
else {\
size_t index = free.front();\
free.pop();\
return index;\
}\
}\
\
static size_t Copy(const size_t & source) {\
 if(free.empty()) {\
size_t newSize = name1.size() + 1;\
size_t index = name1.size();\
name1.resize(newSize);\
name2.resize(newSize);\
name3.resize(newSize);\
name4.resize(newSize);\
name5.resize(newSize);\
name1[index] = name1[source];\
name2[index] = name2[source];\
name3[index] = name3[source];\
name4[index] = name4[source];\
name5[index] = name5[source];\
return index;\
}\
else {\
size_t index = free.front();\
free.pop();\
name1[index] = name1[source];\
name2[index] = name2[source];\
name3[index] = name3[source];\
name4[index] = name4[source];\
name5[index] = name5[source];\
return index;\
}\
}\
\
static void Delete(size_t index) {\
if(index==0)return;\
free.push(index);\
}\
\
static std::queue<size_t> free;\
static std::vector<type1> name1;\
static std::vector<type2> name2;\
static std::vector<type3> name3;\
static std::vector<type4> name4;\
static std::vector<type5> name5;\
};\
}


#define INIT_ECSComponent_05\
(componentName,\
type1, name1,\
type2, name2,\
type3, name3,\
type4, name4,\
type5, name5)\
namespace ECS::Component {\
std::queue<size_t> componentName::free;\
std::vector<type1> componentName::name1(1);\
std::vector<type2> componentName::name2(1);\
std::vector<type3> componentName::name3(1);\
std::vector<type4> componentName::name4(1);\
std::vector<type5> componentName::name5(1);\
}







#define REGISTER_ECSComponent_06\
(componentName,\
type1, name1,\
type2, name2,\
type3, name3,\
type4, name4,\
type5, name5,\
type6, name6)\
namespace ECS::Component {\
struct componentName : ECSBase::ECSComponent<componentName> {\
\
struct Wrapper {\
Wrapper(size_t index)\
: name1(componentName::name1[index]),\
name2(componentName::name2[index]),\
name3(componentName::name3[index]),\
name4(componentName::name4[index]),\
name5(componentName::name5[index]),\
name6(componentName::name6[index]),\
id(index) {}\
type1& name1;\
type2& name2;\
type3& name3;\
type4& name4;\
type5& name5;\
type6& name6;\
const size_t id;\
};\
\
static size_t Create() {\
if(free.empty()) {\
size_t newSize = name1.size() + 1;\
size_t index = name1.size();\
name1.resize(newSize);\
name2.resize(newSize);\
name3.resize(newSize);\
name4.resize(newSize);\
name5.resize(newSize);\
name6.resize(newSize);\
return index;\
}\
else {\
size_t index = free.front();\
free.pop();\
return index;\
}\
}\
\
static size_t Copy(const size_t & source) {\
 if(free.empty()) {\
size_t newSize = name1.size() + 1;\
size_t index = name1.size();\
name1.resize(newSize);\
name2.resize(newSize);\
name3.resize(newSize);\
name4.resize(newSize);\
name5.resize(newSize);\
name6.resize(newSize);\
name1[index] = name1[source];\
name2[index] = name2[source];\
name3[index] = name3[source];\
name4[index] = name4[source];\
name5[index] = name5[source];\
name6[index] = name6[source];\
return index;\
}\
else {\
size_t index = free.front();\
free.pop();\
name1[index] = name1[source];\
name2[index] = name2[source];\
name3[index] = name3[source];\
name4[index] = name4[source];\
name5[index] = name5[source];\
name6[index] = name6[source];\
return index;\
}\
}\
\
static void Delete(size_t index) {\
if(index==0)return;\
free.push(index);\
}\
\
static std::queue<size_t> free;\
static std::vector<type1> name1;\
static std::vector<type2> name2;\
static std::vector<type3> name3;\
static std::vector<type4> name4;\
static std::vector<type5> name5;\
static std::vector<type6> name6;\
};\
}


#define INIT_ECSComponent_06\
(componentName,\
type1, name1,\
type2, name2,\
type3, name3,\
type4, name4,\
type5, name5,\
type6, name6)\
namespace ECS::Component {\
std::queue<size_t> componentName::free;\
std::vector<type1> componentName::name1(1);\
std::vector<type2> componentName::name2(1);\
std::vector<type3> componentName::name3(1);\
std::vector<type4> componentName::name4(1);\
std::vector<type5> componentName::name5(1);\
std::vector<type6> componentName::name6(1);\
}







#define REGISTER_ECSComponent_07\
(componentName,\
type1, name1,\
type2, name2,\
type3, name3,\
type4, name4,\
type5, name5,\
type6, name6,\
type7, name7)\
namespace ECS::Component {\
struct componentName : ECSBase::ECSComponent<componentName> {\
\
struct Wrapper {\
Wrapper(size_t index)\
: name1(componentName::name1[index]),\
name2(componentName::name2[index]),\
name3(componentName::name3[index]),\
name4(componentName::name4[index]),\
name5(componentName::name5[index]),\
name6(componentName::name6[index]),\
name7(componentName::name7[index]),\
id(index) {}\
type1& name1;\
type2& name2;\
type3& name3;\
type4& name4;\
type5& name5;\
type6& name6;\
type7& name7;\
const size_t id;\
};\
\
static size_t Create() {\
if(free.empty()) {\
size_t newSize = name1.size() + 1;\
size_t index = name1.size();\
name1.resize(newSize);\
name2.resize(newSize);\
name3.resize(newSize);\
name4.resize(newSize);\
name5.resize(newSize);\
name6.resize(newSize);\
name7.resize(newSize);\
return index;\
}\
else {\
size_t index = free.front();\
free.pop();\
return index;\
}\
}\
\
static size_t Copy(const size_t & source) {\
 if(free.empty()) {\
size_t newSize = name1.size() + 1;\
size_t index = name1.size();\
name1.resize(newSize);\
name2.resize(newSize);\
name3.resize(newSize);\
name4.resize(newSize);\
name5.resize(newSize);\
name6.resize(newSize);\
name7.resize(newSize);\
name1[index] = name1[source];\
name2[index] = name2[source];\
name3[index] = name3[source];\
name4[index] = name4[source];\
name5[index] = name5[source];\
name6[index] = name6[source];\
name7[index] = name7[source];\
return index;\
}\
else {\
size_t index = free.front();\
free.pop();\
name1[index] = name1[source];\
name2[index] = name2[source];\
name3[index] = name3[source];\
name4[index] = name4[source];\
name5[index] = name5[source];\
name6[index] = name6[source];\
name7[index] = name7[source];\
return index;\
}\
}\
\
static void Delete(size_t index) {\
if(index==0)return;\
free.push(index);\
}\
\
static std::queue<size_t> free;\
static std::vector<type1> name1;\
static std::vector<type2> name2;\
static std::vector<type3> name3;\
static std::vector<type4> name4;\
static std::vector<type5> name5;\
static std::vector<type6> name6;\
static std::vector<type7> name7;\
};\
}


#define INIT_ECSComponent_07\
(componentName,\
type1, name1,\
type2, name2,\
type3, name3,\
type4, name4,\
type5, name5,\
type6, name6,\
type7, name7)\
namespace ECS::Component {\
std::queue<size_t> componentName::free;\
std::vector<type1> componentName::name1(1);\
std::vector<type2> componentName::name2(1);\
std::vector<type3> componentName::name3(1);\
std::vector<type4> componentName::name4(1);\
std::vector<type5> componentName::name5(1);\
std::vector<type6> componentName::name6(1);\
std::vector<type7> componentName::name7(1);\
}







#define REGISTER_ECSComponent_08\
(componentName,\
type1, name1,\
type2, name2,\
type3, name3,\
type4, name4,\
type5, name5,\
type6, name6,\
type7, name7,\
type8, name8)\
namespace ECS::Component {\
struct componentName : ECSBase::ECSComponent<componentName> {\
\
struct Wrapper {\
Wrapper(size_t index)\
: name1(componentName::name1[index]),\
name2(componentName::name2[index]),\
name3(componentName::name3[index]),\
name4(componentName::name4[index]),\
name5(componentName::name5[index]),\
name6(componentName::name6[index]),\
name7(componentName::name7[index]),\
name8(componentName::name8[index]),\
id(index) {}\
type1& name1;\
type2& name2;\
type3& name3;\
type4& name4;\
type5& name5;\
type6& name6;\
type7& name7;\
type8& name8;\
const size_t id;\
};\
\
static size_t Create() {\
if(free.empty()) {\
size_t newSize = name1.size() + 1;\
size_t index = name1.size();\
name1.resize(newSize);\
name2.resize(newSize);\
name3.resize(newSize);\
name4.resize(newSize);\
name5.resize(newSize);\
name6.resize(newSize);\
name7.resize(newSize);\
name8.resize(newSize);\
return index;\
}\
else {\
size_t index = free.front();\
free.pop();\
return index;\
}\
}\
\
static size_t Copy(const size_t & source) {\
 if(free.empty()) {\
size_t newSize = name1.size() + 1;\
size_t index = name1.size();\
name1.resize(newSize);\
name2.resize(newSize);\
name3.resize(newSize);\
name4.resize(newSize);\
name5.resize(newSize);\
name6.resize(newSize);\
name7.resize(newSize);\
name8.resize(newSize);\
name1[index] = name1[source];\
name2[index] = name2[source];\
name3[index] = name3[source];\
name4[index] = name4[source];\
name5[index] = name5[source];\
name6[index] = name6[source];\
name7[index] = name7[source];\
name8[index] = name8[source];\
return index;\
}\
else {\
size_t index = free.front();\
free.pop();\
name1[index] = name1[source];\
name2[index] = name2[source];\
name3[index] = name3[source];\
name4[index] = name4[source];\
name5[index] = name5[source];\
name6[index] = name6[source];\
name7[index] = name7[source];\
name8[index] = name8[source];\
return index;\
}\
}\
\
static void Delete(size_t index) {\
if(index==0)return;\
free.push(index);\
}\
\
static std::queue<size_t> free;\
static std::vector<type1> name1;\
static std::vector<type2> name2;\
static std::vector<type3> name3;\
static std::vector<type4> name4;\
static std::vector<type5> name5;\
static std::vector<type6> name6;\
static std::vector<type7> name7;\
static std::vector<type8> name8;\
};\
}


#define INIT_ECSComponent_08\
(componentName,\
type1, name1,\
type2, name2,\
type3, name3,\
type4, name4,\
type5, name5,\
type6, name6,\
type7, name7,\
type8, name8)\
namespace ECS::Component {\
std::queue<size_t> componentName::free;\
std::vector<type1> componentName::name1(1);\
std::vector<type2> componentName::name2(1);\
std::vector<type3> componentName::name3(1);\
std::vector<type4> componentName::name4(1);\
std::vector<type5> componentName::name5(1);\
std::vector<type6> componentName::name6(1);\
std::vector<type7> componentName::name7(1);\
std::vector<type8> componentName::name8(1);\
}







#define REGISTER_ECSComponent_09\
(componentName,\
type1, name1,\
type2, name2,\
type3, name3,\
type4, name4,\
type5, name5,\
type6, name6,\
type7, name7,\
type8, name8,\
type9, name9)\
namespace ECS::Component {\
struct componentName : ECSBase::ECSComponent<componentName> {\
\
struct Wrapper {\
Wrapper(size_t index)\
: name1(componentName::name1[index]),\
name2(componentName::name2[index]),\
name3(componentName::name3[index]),\
name4(componentName::name4[index]),\
name5(componentName::name5[index]),\
name6(componentName::name6[index]),\
name7(componentName::name7[index]),\
name8(componentName::name8[index]),\
name9(componentName::name9[index]),\
id(index) {}\
type1& name1;\
type2& name2;\
type3& name3;\
type4& name4;\
type5& name5;\
type6& name6;\
type7& name7;\
type8& name8;\
type9& name9;\
const size_t id;\
};\
\
static size_t Create() {\
if(free.empty()) {\
size_t newSize = name1.size() + 1;\
size_t index = name1.size();\
name1.resize(newSize);\
name2.resize(newSize);\
name3.resize(newSize);\
name4.resize(newSize);\
name5.resize(newSize);\
name6.resize(newSize);\
name7.resize(newSize);\
name8.resize(newSize);\
name9.resize(newSize);\
return index;\
}\
else {\
size_t index = free.front();\
free.pop();\
return index;\
}\
}\
\
static size_t Copy(const size_t & source) {\
 if(free.empty()) {\
size_t newSize = name1.size() + 1;\
size_t index = name1.size();\
name1.resize(newSize);\
name2.resize(newSize);\
name3.resize(newSize);\
name4.resize(newSize);\
name5.resize(newSize);\
name6.resize(newSize);\
name7.resize(newSize);\
name8.resize(newSize);\
name9.resize(newSize);\
name1[index] = name1[source];\
name2[index] = name2[source];\
name3[index] = name3[source];\
name4[index] = name4[source];\
name5[index] = name5[source];\
name6[index] = name6[source];\
name7[index] = name7[source];\
name8[index] = name8[source];\
name9[index] = name9[source];\
return index;\
}\
else {\
size_t index = free.front();\
free.pop();\
name1[index] = name1[source];\
name2[index] = name2[source];\
name3[index] = name3[source];\
name4[index] = name4[source];\
name5[index] = name5[source];\
name6[index] = name6[source];\
name7[index] = name7[source];\
name8[index] = name8[source];\
name9[index] = name9[source];\
return index;\
}\
}\
\
static void Delete(size_t index) {\
if(index==0)return;\
free.push(index);\
}\
\
static std::queue<size_t> free;\
static std::vector<type1> name1;\
static std::vector<type2> name2;\
static std::vector<type3> name3;\
static std::vector<type4> name4;\
static std::vector<type5> name5;\
static std::vector<type6> name6;\
static std::vector<type7> name7;\
static std::vector<type8> name8;\
static std::vector<type9> name9;\
};\
}


#define INIT_ECSComponent_09\
(componentName,\
type1, name1,\
type2, name2,\
type3, name3,\
type4, name4,\
type5, name5,\
type6, name6,\
type7, name7,\
type8, name8,\
type9, name9)\
namespace ECS::Component {\
std::queue<size_t> componentName::free;\
std::vector<type1> componentName::name1(1);\
std::vector<type2> componentName::name2(1);\
std::vector<type3> componentName::name3(1);\
std::vector<type4> componentName::name4(1);\
std::vector<type5> componentName::name5(1);\
std::vector<type6> componentName::name6(1);\
std::vector<type7> componentName::name7(1);\
std::vector<type8> componentName::name8(1);\
std::vector<type9> componentName::name9(1);\
}







#define REGISTER_ECSComponent_10\
(componentName,\
type1, name1,\
type2, name2,\
type3, name3,\
type4, name4,\
type5, name5,\
type6, name6,\
type7, name7,\
type8, name8,\
type9, name9,\
type10, name10)\
namespace ECS::Component {\
struct componentName : ECSBase::ECSComponent<componentName> {\
\
struct Wrapper {\
Wrapper(size_t index)\
: name1(componentName::name1[index]),\
name2(componentName::name2[index]),\
name3(componentName::name3[index]),\
name4(componentName::name4[index]),\
name5(componentName::name5[index]),\
name6(componentName::name6[index]),\
name7(componentName::name7[index]),\
name8(componentName::name8[index]),\
name9(componentName::name9[index]),\
name10(componentName::name10[index]),\
id(index) {}\
type1& name1;\
type2& name2;\
type3& name3;\
type4& name4;\
type5& name5;\
type6& name6;\
type7& name7;\
type8& name8;\
type9& name9;\
type10& name10;\
const size_t id;\
};\
\
static size_t Create() {\
if(free.empty()) {\
size_t newSize = name1.size() + 1;\
size_t index = name1.size();\
name1.resize(newSize);\
name2.resize(newSize);\
name3.resize(newSize);\
name4.resize(newSize);\
name5.resize(newSize);\
name6.resize(newSize);\
name7.resize(newSize);\
name8.resize(newSize);\
name9.resize(newSize);\
name10.resize(newSize);\
return index;\
}\
else {\
size_t index = free.front();\
free.pop();\
return index;\
}\
}\
\
static size_t Copy(const size_t & source) {\
 if(free.empty()) {\
size_t newSize = name1.size() + 1;\
size_t index = name1.size();\
name1.resize(newSize);\
name2.resize(newSize);\
name3.resize(newSize);\
name4.resize(newSize);\
name5.resize(newSize);\
name6.resize(newSize);\
name7.resize(newSize);\
name8.resize(newSize);\
name9.resize(newSize);\
name10.resize(newSize);\
name1[index] = name1[source];\
name2[index] = name2[source];\
name3[index] = name3[source];\
name4[index] = name4[source];\
name5[index] = name5[source];\
name6[index] = name6[source];\
name7[index] = name7[source];\
name8[index] = name8[source];\
name9[index] = name9[source];\
name10[index] = name10[source];\
return index;\
}\
else {\
size_t index = free.front();\
free.pop();\
name1[index] = name1[source];\
name2[index] = name2[source];\
name3[index] = name3[source];\
name4[index] = name4[source];\
name5[index] = name5[source];\
name6[index] = name6[source];\
name7[index] = name7[source];\
name8[index] = name8[source];\
name9[index] = name9[source];\
name10[index] = name10[source];\
return index;\
}\
}\
\
static void Delete(size_t index) {\
if(index==0)return;\
free.push(index);\
}\
\
static std::queue<size_t> free;\
static std::vector<type1> name1;\
static std::vector<type2> name2;\
static std::vector<type3> name3;\
static std::vector<type4> name4;\
static std::vector<type5> name5;\
static std::vector<type6> name6;\
static std::vector<type7> name7;\
static std::vector<type8> name8;\
static std::vector<type9> name9;\
static std::vector<type10> name10;\
};\
}


#define INIT_ECSComponent_10\
(componentName,\
type1, name1,\
type2, name2,\
type3, name3,\
type4, name4,\
type5, name5,\
type6, name6,\
type7, name7,\
type8, name8,\
type9, name9,\
type10, name10)\
namespace ECS::Component {\
std::queue<size_t> componentName::free;\
std::vector<type1> componentName::name1(1);\
std::vector<type2> componentName::name2(1);\
std::vector<type3> componentName::name3(1);\
std::vector<type4> componentName::name4(1);\
std::vector<type5> componentName::name5(1);\
std::vector<type6> componentName::name6(1);\
std::vector<type7> componentName::name7(1);\
std::vector<type8> componentName::name8(1);\
std::vector<type9> componentName::name9(1);\
std::vector<type10> componentName::name10(1);\
}







#define REGISTER_ECSComponent_11\
(componentName,\
type1, name1,\
type2, name2,\
type3, name3,\
type4, name4,\
type5, name5,\
type6, name6,\
type7, name7,\
type8, name8,\
type9, name9,\
type10, name10,\
type11, name11)\
namespace ECS::Component {\
struct componentName : ECSBase::ECSComponent<componentName> {\
\
struct Wrapper {\
Wrapper(size_t index)\
: name1(componentName::name1[index]),\
name2(componentName::name2[index]),\
name3(componentName::name3[index]),\
name4(componentName::name4[index]),\
name5(componentName::name5[index]),\
name6(componentName::name6[index]),\
name7(componentName::name7[index]),\
name8(componentName::name8[index]),\
name9(componentName::name9[index]),\
name10(componentName::name10[index]),\
name11(componentName::name11[index]),\
id(index) {}\
type1& name1;\
type2& name2;\
type3& name3;\
type4& name4;\
type5& name5;\
type6& name6;\
type7& name7;\
type8& name8;\
type9& name9;\
type10& name10;\
type11& name11;\
const size_t id;\
};\
\
static size_t Create() {\
if(free.empty()) {\
size_t newSize = name1.size() + 1;\
size_t index = name1.size();\
name1.resize(newSize);\
name2.resize(newSize);\
name3.resize(newSize);\
name4.resize(newSize);\
name5.resize(newSize);\
name6.resize(newSize);\
name7.resize(newSize);\
name8.resize(newSize);\
name9.resize(newSize);\
name10.resize(newSize);\
name11.resize(newSize);\
return index;\
}\
else {\
size_t index = free.front();\
free.pop();\
return index;\
}\
}\
\
static size_t Copy(const size_t & source) {\
 if(free.empty()) {\
size_t newSize = name1.size() + 1;\
size_t index = name1.size();\
name1.resize(newSize);\
name2.resize(newSize);\
name3.resize(newSize);\
name4.resize(newSize);\
name5.resize(newSize);\
name6.resize(newSize);\
name7.resize(newSize);\
name8.resize(newSize);\
name9.resize(newSize);\
name10.resize(newSize);\
name11.resize(newSize);\
name1[index] = name1[source];\
name2[index] = name2[source];\
name3[index] = name3[source];\
name4[index] = name4[source];\
name5[index] = name5[source];\
name6[index] = name6[source];\
name7[index] = name7[source];\
name8[index] = name8[source];\
name9[index] = name9[source];\
name10[index] = name10[source];\
name11[index] = name11[source];\
return index;\
}\
else {\
size_t index = free.front();\
free.pop();\
name1[index] = name1[source];\
name2[index] = name2[source];\
name3[index] = name3[source];\
name4[index] = name4[source];\
name5[index] = name5[source];\
name6[index] = name6[source];\
name7[index] = name7[source];\
name8[index] = name8[source];\
name9[index] = name9[source];\
name10[index] = name10[source];\
name11[index] = name11[source];\
return index;\
}\
}\
\
static void Delete(size_t index) {\
if(index==0)return;\
free.push(index);\
}\
\
static std::queue<size_t> free;\
static std::vector<type1> name1;\
static std::vector<type2> name2;\
static std::vector<type3> name3;\
static std::vector<type4> name4;\
static std::vector<type5> name5;\
static std::vector<type6> name6;\
static std::vector<type7> name7;\
static std::vector<type8> name8;\
static std::vector<type9> name9;\
static std::vector<type10> name10;\
static std::vector<type11> name11;\
};\
}


#define INIT_ECSComponent_11\
(componentName,\
type1, name1,\
type2, name2,\
type3, name3,\
type4, name4,\
type5, name5,\
type6, name6,\
type7, name7,\
type8, name8,\
type9, name9,\
type10, name10,\
type11, name11)\
namespace ECS::Component {\
std::queue<size_t> componentName::free;\
std::vector<type1> componentName::name1(1);\
std::vector<type2> componentName::name2(1);\
std::vector<type3> componentName::name3(1);\
std::vector<type4> componentName::name4(1);\
std::vector<type5> componentName::name5(1);\
std::vector<type6> componentName::name6(1);\
std::vector<type7> componentName::name7(1);\
std::vector<type8> componentName::name8(1);\
std::vector<type9> componentName::name9(1);\
std::vector<type10> componentName::name10(1);\
std::vector<type11> componentName::name11(1);\
}







#define REGISTER_ECSComponent_12\
(componentName,\
type1, name1,\
type2, name2,\
type3, name3,\
type4, name4,\
type5, name5,\
type6, name6,\
type7, name7,\
type8, name8,\
type9, name9,\
type10, name10,\
type11, name11,\
type12, name12)\
namespace ECS::Component {\
struct componentName : ECSBase::ECSComponent<componentName> {\
\
struct Wrapper {\
Wrapper(size_t index)\
: name1(componentName::name1[index]),\
name2(componentName::name2[index]),\
name3(componentName::name3[index]),\
name4(componentName::name4[index]),\
name5(componentName::name5[index]),\
name6(componentName::name6[index]),\
name7(componentName::name7[index]),\
name8(componentName::name8[index]),\
name9(componentName::name9[index]),\
name10(componentName::name10[index]),\
name11(componentName::name11[index]),\
name12(componentName::name12[index]),\
id(index) {}\
type1& name1;\
type2& name2;\
type3& name3;\
type4& name4;\
type5& name5;\
type6& name6;\
type7& name7;\
type8& name8;\
type9& name9;\
type10& name10;\
type11& name11;\
type12& name12;\
const size_t id;\
};\
\
static size_t Create() {\
if(free.empty()) {\
size_t newSize = name1.size() + 1;\
size_t index = name1.size();\
name1.resize(newSize);\
name2.resize(newSize);\
name3.resize(newSize);\
name4.resize(newSize);\
name5.resize(newSize);\
name6.resize(newSize);\
name7.resize(newSize);\
name8.resize(newSize);\
name9.resize(newSize);\
name10.resize(newSize);\
name11.resize(newSize);\
name12.resize(newSize);\
return index;\
}\
else {\
size_t index = free.front();\
free.pop();\
return index;\
}\
}\
\
static size_t Copy(const size_t & source) {\
 if(free.empty()) {\
size_t newSize = name1.size() + 1;\
size_t index = name1.size();\
name1.resize(newSize);\
name2.resize(newSize);\
name3.resize(newSize);\
name4.resize(newSize);\
name5.resize(newSize);\
name6.resize(newSize);\
name7.resize(newSize);\
name8.resize(newSize);\
name9.resize(newSize);\
name10.resize(newSize);\
name11.resize(newSize);\
name12.resize(newSize);\
name1[index] = name1[source];\
name2[index] = name2[source];\
name3[index] = name3[source];\
name4[index] = name4[source];\
name5[index] = name5[source];\
name6[index] = name6[source];\
name7[index] = name7[source];\
name8[index] = name8[source];\
name9[index] = name9[source];\
name10[index] = name10[source];\
name11[index] = name11[source];\
name12[index] = name12[source];\
return index;\
}\
else {\
size_t index = free.front();\
free.pop();\
name1[index] = name1[source];\
name2[index] = name2[source];\
name3[index] = name3[source];\
name4[index] = name4[source];\
name5[index] = name5[source];\
name6[index] = name6[source];\
name7[index] = name7[source];\
name8[index] = name8[source];\
name9[index] = name9[source];\
name10[index] = name10[source];\
name11[index] = name11[source];\
name12[index] = name12[source];\
return index;\
}\
}\
\
static void Delete(size_t index) {\
if(index==0)return;\
free.push(index);\
}\
\
static std::queue<size_t> free;\
static std::vector<type1> name1;\
static std::vector<type2> name2;\
static std::vector<type3> name3;\
static std::vector<type4> name4;\
static std::vector<type5> name5;\
static std::vector<type6> name6;\
static std::vector<type7> name7;\
static std::vector<type8> name8;\
static std::vector<type9> name9;\
static std::vector<type10> name10;\
static std::vector<type11> name11;\
static std::vector<type12> name12;\
};\
}


#define INIT_ECSComponent_12\
(componentName,\
type1, name1,\
type2, name2,\
type3, name3,\
type4, name4,\
type5, name5,\
type6, name6,\
type7, name7,\
type8, name8,\
type9, name9,\
type10, name10,\
type11, name11,\
type12, name12)\
namespace ECS::Component {\
std::queue<size_t> componentName::free;\
std::vector<type1> componentName::name1(1);\
std::vector<type2> componentName::name2(1);\
std::vector<type3> componentName::name3(1);\
std::vector<type4> componentName::name4(1);\
std::vector<type5> componentName::name5(1);\
std::vector<type6> componentName::name6(1);\
std::vector<type7> componentName::name7(1);\
std::vector<type8> componentName::name8(1);\
std::vector<type9> componentName::name9(1);\
std::vector<type10> componentName::name10(1);\
std::vector<type11> componentName::name11(1);\
std::vector<type12> componentName::name12(1);\
}







#define REGISTER_ECSComponent_13\
(componentName,\
type1, name1,\
type2, name2,\
type3, name3,\
type4, name4,\
type5, name5,\
type6, name6,\
type7, name7,\
type8, name8,\
type9, name9,\
type10, name10,\
type11, name11,\
type12, name12,\
type13, name13)\
namespace ECS::Component {\
struct componentName : ECSBase::ECSComponent<componentName> {\
\
struct Wrapper {\
Wrapper(size_t index)\
: name1(componentName::name1[index]),\
name2(componentName::name2[index]),\
name3(componentName::name3[index]),\
name4(componentName::name4[index]),\
name5(componentName::name5[index]),\
name6(componentName::name6[index]),\
name7(componentName::name7[index]),\
name8(componentName::name8[index]),\
name9(componentName::name9[index]),\
name10(componentName::name10[index]),\
name11(componentName::name11[index]),\
name12(componentName::name12[index]),\
name13(componentName::name13[index]),\
id(index) {}\
type1& name1;\
type2& name2;\
type3& name3;\
type4& name4;\
type5& name5;\
type6& name6;\
type7& name7;\
type8& name8;\
type9& name9;\
type10& name10;\
type11& name11;\
type12& name12;\
type13& name13;\
const size_t id;\
};\
\
static size_t Create() {\
if(free.empty()) {\
size_t newSize = name1.size() + 1;\
size_t index = name1.size();\
name1.resize(newSize);\
name2.resize(newSize);\
name3.resize(newSize);\
name4.resize(newSize);\
name5.resize(newSize);\
name6.resize(newSize);\
name7.resize(newSize);\
name8.resize(newSize);\
name9.resize(newSize);\
name10.resize(newSize);\
name11.resize(newSize);\
name12.resize(newSize);\
name13.resize(newSize);\
return index;\
}\
else {\
size_t index = free.front();\
free.pop();\
return index;\
}\
}\
\
static size_t Copy(const size_t & source) {\
 if(free.empty()) {\
size_t newSize = name1.size() + 1;\
size_t index = name1.size();\
name1.resize(newSize);\
name2.resize(newSize);\
name3.resize(newSize);\
name4.resize(newSize);\
name5.resize(newSize);\
name6.resize(newSize);\
name7.resize(newSize);\
name8.resize(newSize);\
name9.resize(newSize);\
name10.resize(newSize);\
name11.resize(newSize);\
name12.resize(newSize);\
name13.resize(newSize);\
name1[index] = name1[source];\
name2[index] = name2[source];\
name3[index] = name3[source];\
name4[index] = name4[source];\
name5[index] = name5[source];\
name6[index] = name6[source];\
name7[index] = name7[source];\
name8[index] = name8[source];\
name9[index] = name9[source];\
name10[index] = name10[source];\
name11[index] = name11[source];\
name12[index] = name12[source];\
name13[index] = name13[source];\
return index;\
}\
else {\
size_t index = free.front();\
free.pop();\
name1[index] = name1[source];\
name2[index] = name2[source];\
name3[index] = name3[source];\
name4[index] = name4[source];\
name5[index] = name5[source];\
name6[index] = name6[source];\
name7[index] = name7[source];\
name8[index] = name8[source];\
name9[index] = name9[source];\
name10[index] = name10[source];\
name11[index] = name11[source];\
name12[index] = name12[source];\
name13[index] = name13[source];\
return index;\
}\
}\
\
static void Delete(size_t index) {\
if(index==0)return;\
free.push(index);\
}\
\
static std::queue<size_t> free;\
static std::vector<type1> name1;\
static std::vector<type2> name2;\
static std::vector<type3> name3;\
static std::vector<type4> name4;\
static std::vector<type5> name5;\
static std::vector<type6> name6;\
static std::vector<type7> name7;\
static std::vector<type8> name8;\
static std::vector<type9> name9;\
static std::vector<type10> name10;\
static std::vector<type11> name11;\
static std::vector<type12> name12;\
static std::vector<type13> name13;\
};\
}


#define INIT_ECSComponent_13\
(componentName,\
type1, name1,\
type2, name2,\
type3, name3,\
type4, name4,\
type5, name5,\
type6, name6,\
type7, name7,\
type8, name8,\
type9, name9,\
type10, name10,\
type11, name11,\
type12, name12,\
type13, name13)\
namespace ECS::Component {\
std::queue<size_t> componentName::free;\
std::vector<type1> componentName::name1(1);\
std::vector<type2> componentName::name2(1);\
std::vector<type3> componentName::name3(1);\
std::vector<type4> componentName::name4(1);\
std::vector<type5> componentName::name5(1);\
std::vector<type6> componentName::name6(1);\
std::vector<type7> componentName::name7(1);\
std::vector<type8> componentName::name8(1);\
std::vector<type9> componentName::name9(1);\
std::vector<type10> componentName::name10(1);\
std::vector<type11> componentName::name11(1);\
std::vector<type12> componentName::name12(1);\
std::vector<type13> componentName::name13(1);\
}







#define REGISTER_ECSComponent_14\
(componentName,\
type1, name1,\
type2, name2,\
type3, name3,\
type4, name4,\
type5, name5,\
type6, name6,\
type7, name7,\
type8, name8,\
type9, name9,\
type10, name10,\
type11, name11,\
type12, name12,\
type13, name13,\
type14, name14)\
namespace ECS::Component {\
struct componentName : ECSBase::ECSComponent<componentName> {\
\
struct Wrapper {\
Wrapper(size_t index)\
: name1(componentName::name1[index]),\
name2(componentName::name2[index]),\
name3(componentName::name3[index]),\
name4(componentName::name4[index]),\
name5(componentName::name5[index]),\
name6(componentName::name6[index]),\
name7(componentName::name7[index]),\
name8(componentName::name8[index]),\
name9(componentName::name9[index]),\
name10(componentName::name10[index]),\
name11(componentName::name11[index]),\
name12(componentName::name12[index]),\
name13(componentName::name13[index]),\
name14(componentName::name14[index]),\
id(index) {}\
type1& name1;\
type2& name2;\
type3& name3;\
type4& name4;\
type5& name5;\
type6& name6;\
type7& name7;\
type8& name8;\
type9& name9;\
type10& name10;\
type11& name11;\
type12& name12;\
type13& name13;\
type14& name14;\
const size_t id;\
};\
\
static size_t Create() {\
if(free.empty()) {\
size_t newSize = name1.size() + 1;\
size_t index = name1.size();\
name1.resize(newSize);\
name2.resize(newSize);\
name3.resize(newSize);\
name4.resize(newSize);\
name5.resize(newSize);\
name6.resize(newSize);\
name7.resize(newSize);\
name8.resize(newSize);\
name9.resize(newSize);\
name10.resize(newSize);\
name11.resize(newSize);\
name12.resize(newSize);\
name13.resize(newSize);\
name14.resize(newSize);\
return index;\
}\
else {\
size_t index = free.front();\
free.pop();\
return index;\
}\
}\
\
static size_t Copy(const size_t & source) {\
 if(free.empty()) {\
size_t newSize = name1.size() + 1;\
size_t index = name1.size();\
name1.resize(newSize);\
name2.resize(newSize);\
name3.resize(newSize);\
name4.resize(newSize);\
name5.resize(newSize);\
name6.resize(newSize);\
name7.resize(newSize);\
name8.resize(newSize);\
name9.resize(newSize);\
name10.resize(newSize);\
name11.resize(newSize);\
name12.resize(newSize);\
name13.resize(newSize);\
name14.resize(newSize);\
name1[index] = name1[source];\
name2[index] = name2[source];\
name3[index] = name3[source];\
name4[index] = name4[source];\
name5[index] = name5[source];\
name6[index] = name6[source];\
name7[index] = name7[source];\
name8[index] = name8[source];\
name9[index] = name9[source];\
name10[index] = name10[source];\
name11[index] = name11[source];\
name12[index] = name12[source];\
name13[index] = name13[source];\
name14[index] = name14[source];\
return index;\
}\
else {\
size_t index = free.front();\
free.pop();\
name1[index] = name1[source];\
name2[index] = name2[source];\
name3[index] = name3[source];\
name4[index] = name4[source];\
name5[index] = name5[source];\
name6[index] = name6[source];\
name7[index] = name7[source];\
name8[index] = name8[source];\
name9[index] = name9[source];\
name10[index] = name10[source];\
name11[index] = name11[source];\
name12[index] = name12[source];\
name13[index] = name13[source];\
name14[index] = name14[source];\
return index;\
}\
}\
\
static void Delete(size_t index) {\
if(index==0)return;\
free.push(index);\
}\
\
static std::queue<size_t> free;\
static std::vector<type1> name1;\
static std::vector<type2> name2;\
static std::vector<type3> name3;\
static std::vector<type4> name4;\
static std::vector<type5> name5;\
static std::vector<type6> name6;\
static std::vector<type7> name7;\
static std::vector<type8> name8;\
static std::vector<type9> name9;\
static std::vector<type10> name10;\
static std::vector<type11> name11;\
static std::vector<type12> name12;\
static std::vector<type13> name13;\
static std::vector<type14> name14;\
};\
}


#define INIT_ECSComponent_14\
(componentName,\
type1, name1,\
type2, name2,\
type3, name3,\
type4, name4,\
type5, name5,\
type6, name6,\
type7, name7,\
type8, name8,\
type9, name9,\
type10, name10,\
type11, name11,\
type12, name12,\
type13, name13,\
type14, name14)\
namespace ECS::Component {\
std::queue<size_t> componentName::free;\
std::vector<type1> componentName::name1(1);\
std::vector<type2> componentName::name2(1);\
std::vector<type3> componentName::name3(1);\
std::vector<type4> componentName::name4(1);\
std::vector<type5> componentName::name5(1);\
std::vector<type6> componentName::name6(1);\
std::vector<type7> componentName::name7(1);\
std::vector<type8> componentName::name8(1);\
std::vector<type9> componentName::name9(1);\
std::vector<type10> componentName::name10(1);\
std::vector<type11> componentName::name11(1);\
std::vector<type12> componentName::name12(1);\
std::vector<type13> componentName::name13(1);\
std::vector<type14> componentName::name14(1);\
}







#define REGISTER_ECSComponent_15\
(componentName,\
type1, name1,\
type2, name2,\
type3, name3,\
type4, name4,\
type5, name5,\
type6, name6,\
type7, name7,\
type8, name8,\
type9, name9,\
type10, name10,\
type11, name11,\
type12, name12,\
type13, name13,\
type14, name14,\
type15, name15)\
namespace ECS::Component {\
struct componentName : ECSBase::ECSComponent<componentName> {\
\
struct Wrapper {\
Wrapper(size_t index)\
: name1(componentName::name1[index]),\
name2(componentName::name2[index]),\
name3(componentName::name3[index]),\
name4(componentName::name4[index]),\
name5(componentName::name5[index]),\
name6(componentName::name6[index]),\
name7(componentName::name7[index]),\
name8(componentName::name8[index]),\
name9(componentName::name9[index]),\
name10(componentName::name10[index]),\
name11(componentName::name11[index]),\
name12(componentName::name12[index]),\
name13(componentName::name13[index]),\
name14(componentName::name14[index]),\
name15(componentName::name15[index]),\
id(index) {}\
type1& name1;\
type2& name2;\
type3& name3;\
type4& name4;\
type5& name5;\
type6& name6;\
type7& name7;\
type8& name8;\
type9& name9;\
type10& name10;\
type11& name11;\
type12& name12;\
type13& name13;\
type14& name14;\
type15& name15;\
const size_t id;\
};\
\
static size_t Create() {\
if(free.empty()) {\
size_t newSize = name1.size() + 1;\
size_t index = name1.size();\
name1.resize(newSize);\
name2.resize(newSize);\
name3.resize(newSize);\
name4.resize(newSize);\
name5.resize(newSize);\
name6.resize(newSize);\
name7.resize(newSize);\
name8.resize(newSize);\
name9.resize(newSize);\
name10.resize(newSize);\
name11.resize(newSize);\
name12.resize(newSize);\
name13.resize(newSize);\
name14.resize(newSize);\
name15.resize(newSize);\
return index;\
}\
else {\
size_t index = free.front();\
free.pop();\
return index;\
}\
}\
\
static size_t Copy(const size_t & source) {\
 if(free.empty()) {\
size_t newSize = name1.size() + 1;\
size_t index = name1.size();\
name1.resize(newSize);\
name2.resize(newSize);\
name3.resize(newSize);\
name4.resize(newSize);\
name5.resize(newSize);\
name6.resize(newSize);\
name7.resize(newSize);\
name8.resize(newSize);\
name9.resize(newSize);\
name10.resize(newSize);\
name11.resize(newSize);\
name12.resize(newSize);\
name13.resize(newSize);\
name14.resize(newSize);\
name15.resize(newSize);\
name1[index] = name1[source];\
name2[index] = name2[source];\
name3[index] = name3[source];\
name4[index] = name4[source];\
name5[index] = name5[source];\
name6[index] = name6[source];\
name7[index] = name7[source];\
name8[index] = name8[source];\
name9[index] = name9[source];\
name10[index] = name10[source];\
name11[index] = name11[source];\
name12[index] = name12[source];\
name13[index] = name13[source];\
name14[index] = name14[source];\
name15[index] = name15[source];\
return index;\
}\
else {\
size_t index = free.front();\
free.pop();\
name1[index] = name1[source];\
name2[index] = name2[source];\
name3[index] = name3[source];\
name4[index] = name4[source];\
name5[index] = name5[source];\
name6[index] = name6[source];\
name7[index] = name7[source];\
name8[index] = name8[source];\
name9[index] = name9[source];\
name10[index] = name10[source];\
name11[index] = name11[source];\
name12[index] = name12[source];\
name13[index] = name13[source];\
name14[index] = name14[source];\
name15[index] = name15[source];\
return index;\
}\
}\
\
static void Delete(size_t index) {\
if(index==0)return;\
free.push(index);\
}\
\
static std::queue<size_t> free;\
static std::vector<type1> name1;\
static std::vector<type2> name2;\
static std::vector<type3> name3;\
static std::vector<type4> name4;\
static std::vector<type5> name5;\
static std::vector<type6> name6;\
static std::vector<type7> name7;\
static std::vector<type8> name8;\
static std::vector<type9> name9;\
static std::vector<type10> name10;\
static std::vector<type11> name11;\
static std::vector<type12> name12;\
static std::vector<type13> name13;\
static std::vector<type14> name14;\
static std::vector<type15> name15;\
};\
}


#define INIT_ECSComponent_15\
(componentName,\
type1, name1,\
type2, name2,\
type3, name3,\
type4, name4,\
type5, name5,\
type6, name6,\
type7, name7,\
type8, name8,\
type9, name9,\
type10, name10,\
type11, name11,\
type12, name12,\
type13, name13,\
type14, name14,\
type15, name15)\
namespace ECS::Component {\
std::queue<size_t> componentName::free;\
std::vector<type1> componentName::name1(1);\
std::vector<type2> componentName::name2(1);\
std::vector<type3> componentName::name3(1);\
std::vector<type4> componentName::name4(1);\
std::vector<type5> componentName::name5(1);\
std::vector<type6> componentName::name6(1);\
std::vector<type7> componentName::name7(1);\
std::vector<type8> componentName::name8(1);\
std::vector<type9> componentName::name9(1);\
std::vector<type10> componentName::name10(1);\
std::vector<type11> componentName::name11(1);\
std::vector<type12> componentName::name12(1);\
std::vector<type13> componentName::name13(1);\
std::vector<type14> componentName::name14(1);\
std::vector<type15> componentName::name15(1);\
}







#define REGISTER_ECSComponent_16\
(componentName,\
type1, name1,\
type2, name2,\
type3, name3,\
type4, name4,\
type5, name5,\
type6, name6,\
type7, name7,\
type8, name8,\
type9, name9,\
type10, name10,\
type11, name11,\
type12, name12,\
type13, name13,\
type14, name14,\
type15, name15,\
type16, name16)\
namespace ECS::Component {\
struct componentName : ECSBase::ECSComponent<componentName> {\
\
struct Wrapper {\
Wrapper(size_t index)\
: name1(componentName::name1[index]),\
name2(componentName::name2[index]),\
name3(componentName::name3[index]),\
name4(componentName::name4[index]),\
name5(componentName::name5[index]),\
name6(componentName::name6[index]),\
name7(componentName::name7[index]),\
name8(componentName::name8[index]),\
name9(componentName::name9[index]),\
name10(componentName::name10[index]),\
name11(componentName::name11[index]),\
name12(componentName::name12[index]),\
name13(componentName::name13[index]),\
name14(componentName::name14[index]),\
name15(componentName::name15[index]),\
name16(componentName::name16[index]),\
id(index) {}\
type1& name1;\
type2& name2;\
type3& name3;\
type4& name4;\
type5& name5;\
type6& name6;\
type7& name7;\
type8& name8;\
type9& name9;\
type10& name10;\
type11& name11;\
type12& name12;\
type13& name13;\
type14& name14;\
type15& name15;\
type16& name16;\
const size_t id;\
};\
\
static size_t Create() {\
if(free.empty()) {\
size_t newSize = name1.size() + 1;\
size_t index = name1.size();\
name1.resize(newSize);\
name2.resize(newSize);\
name3.resize(newSize);\
name4.resize(newSize);\
name5.resize(newSize);\
name6.resize(newSize);\
name7.resize(newSize);\
name8.resize(newSize);\
name9.resize(newSize);\
name10.resize(newSize);\
name11.resize(newSize);\
name12.resize(newSize);\
name13.resize(newSize);\
name14.resize(newSize);\
name15.resize(newSize);\
name16.resize(newSize);\
return index;\
}\
else {\
size_t index = free.front();\
free.pop();\
return index;\
}\
}\
\
static size_t Copy(const size_t & source) {\
 if(free.empty()) {\
size_t newSize = name1.size() + 1;\
size_t index = name1.size();\
name1.resize(newSize);\
name2.resize(newSize);\
name3.resize(newSize);\
name4.resize(newSize);\
name5.resize(newSize);\
name6.resize(newSize);\
name7.resize(newSize);\
name8.resize(newSize);\
name9.resize(newSize);\
name10.resize(newSize);\
name11.resize(newSize);\
name12.resize(newSize);\
name13.resize(newSize);\
name14.resize(newSize);\
name15.resize(newSize);\
name16.resize(newSize);\
name1[index] = name1[source];\
name2[index] = name2[source];\
name3[index] = name3[source];\
name4[index] = name4[source];\
name5[index] = name5[source];\
name6[index] = name6[source];\
name7[index] = name7[source];\
name8[index] = name8[source];\
name9[index] = name9[source];\
name10[index] = name10[source];\
name11[index] = name11[source];\
name12[index] = name12[source];\
name13[index] = name13[source];\
name14[index] = name14[source];\
name15[index] = name15[source];\
name16[index] = name16[source];\
return index;\
}\
else {\
size_t index = free.front();\
free.pop();\
name1[index] = name1[source];\
name2[index] = name2[source];\
name3[index] = name3[source];\
name4[index] = name4[source];\
name5[index] = name5[source];\
name6[index] = name6[source];\
name7[index] = name7[source];\
name8[index] = name8[source];\
name9[index] = name9[source];\
name10[index] = name10[source];\
name11[index] = name11[source];\
name12[index] = name12[source];\
name13[index] = name13[source];\
name14[index] = name14[source];\
name15[index] = name15[source];\
name16[index] = name16[source];\
return index;\
}\
}\
\
static void Delete(size_t index) {\
if(index==0)return;\
free.push(index);\
}\
\
static std::queue<size_t> free;\
static std::vector<type1> name1;\
static std::vector<type2> name2;\
static std::vector<type3> name3;\
static std::vector<type4> name4;\
static std::vector<type5> name5;\
static std::vector<type6> name6;\
static std::vector<type7> name7;\
static std::vector<type8> name8;\
static std::vector<type9> name9;\
static std::vector<type10> name10;\
static std::vector<type11> name11;\
static std::vector<type12> name12;\
static std::vector<type13> name13;\
static std::vector<type14> name14;\
static std::vector<type15> name15;\
static std::vector<type16> name16;\
};\
}


#define INIT_ECSComponent_16\
(componentName,\
type1, name1,\
type2, name2,\
type3, name3,\
type4, name4,\
type5, name5,\
type6, name6,\
type7, name7,\
type8, name8,\
type9, name9,\
type10, name10,\
type11, name11,\
type12, name12,\
type13, name13,\
type14, name14,\
type15, name15,\
type16, name16)\
namespace ECS::Component {\
std::queue<size_t> componentName::free;\
std::vector<type1> componentName::name1(1);\
std::vector<type2> componentName::name2(1);\
std::vector<type3> componentName::name3(1);\
std::vector<type4> componentName::name4(1);\
std::vector<type5> componentName::name5(1);\
std::vector<type6> componentName::name6(1);\
std::vector<type7> componentName::name7(1);\
std::vector<type8> componentName::name8(1);\
std::vector<type9> componentName::name9(1);\
std::vector<type10> componentName::name10(1);\
std::vector<type11> componentName::name11(1);\
std::vector<type12> componentName::name12(1);\
std::vector<type13> componentName::name13(1);\
std::vector<type14> componentName::name14(1);\
std::vector<type15> componentName::name15(1);\
std::vector<type16> componentName::name16(1);\
}







#define REGISTER_ECSComponent_17\
(componentName,\
type1, name1,\
type2, name2,\
type3, name3,\
type4, name4,\
type5, name5,\
type6, name6,\
type7, name7,\
type8, name8,\
type9, name9,\
type10, name10,\
type11, name11,\
type12, name12,\
type13, name13,\
type14, name14,\
type15, name15,\
type16, name16,\
type17, name17)\
namespace ECS::Component {\
struct componentName : ECSBase::ECSComponent<componentName> {\
\
struct Wrapper {\
Wrapper(size_t index)\
: name1(componentName::name1[index]),\
name2(componentName::name2[index]),\
name3(componentName::name3[index]),\
name4(componentName::name4[index]),\
name5(componentName::name5[index]),\
name6(componentName::name6[index]),\
name7(componentName::name7[index]),\
name8(componentName::name8[index]),\
name9(componentName::name9[index]),\
name10(componentName::name10[index]),\
name11(componentName::name11[index]),\
name12(componentName::name12[index]),\
name13(componentName::name13[index]),\
name14(componentName::name14[index]),\
name15(componentName::name15[index]),\
name16(componentName::name16[index]),\
name17(componentName::name17[index]),\
id(index) {}\
type1& name1;\
type2& name2;\
type3& name3;\
type4& name4;\
type5& name5;\
type6& name6;\
type7& name7;\
type8& name8;\
type9& name9;\
type10& name10;\
type11& name11;\
type12& name12;\
type13& name13;\
type14& name14;\
type15& name15;\
type16& name16;\
type17& name17;\
const size_t id;\
};\
\
static size_t Create() {\
if(free.empty()) {\
size_t newSize = name1.size() + 1;\
size_t index = name1.size();\
name1.resize(newSize);\
name2.resize(newSize);\
name3.resize(newSize);\
name4.resize(newSize);\
name5.resize(newSize);\
name6.resize(newSize);\
name7.resize(newSize);\
name8.resize(newSize);\
name9.resize(newSize);\
name10.resize(newSize);\
name11.resize(newSize);\
name12.resize(newSize);\
name13.resize(newSize);\
name14.resize(newSize);\
name15.resize(newSize);\
name16.resize(newSize);\
name17.resize(newSize);\
return index;\
}\
else {\
size_t index = free.front();\
free.pop();\
return index;\
}\
}\
\
static size_t Copy(const size_t & source) {\
 if(free.empty()) {\
size_t newSize = name1.size() + 1;\
size_t index = name1.size();\
name1.resize(newSize);\
name2.resize(newSize);\
name3.resize(newSize);\
name4.resize(newSize);\
name5.resize(newSize);\
name6.resize(newSize);\
name7.resize(newSize);\
name8.resize(newSize);\
name9.resize(newSize);\
name10.resize(newSize);\
name11.resize(newSize);\
name12.resize(newSize);\
name13.resize(newSize);\
name14.resize(newSize);\
name15.resize(newSize);\
name16.resize(newSize);\
name17.resize(newSize);\
name1[index] = name1[source];\
name2[index] = name2[source];\
name3[index] = name3[source];\
name4[index] = name4[source];\
name5[index] = name5[source];\
name6[index] = name6[source];\
name7[index] = name7[source];\
name8[index] = name8[source];\
name9[index] = name9[source];\
name10[index] = name10[source];\
name11[index] = name11[source];\
name12[index] = name12[source];\
name13[index] = name13[source];\
name14[index] = name14[source];\
name15[index] = name15[source];\
name16[index] = name16[source];\
name17[index] = name17[source];\
return index;\
}\
else {\
size_t index = free.front();\
free.pop();\
name1[index] = name1[source];\
name2[index] = name2[source];\
name3[index] = name3[source];\
name4[index] = name4[source];\
name5[index] = name5[source];\
name6[index] = name6[source];\
name7[index] = name7[source];\
name8[index] = name8[source];\
name9[index] = name9[source];\
name10[index] = name10[source];\
name11[index] = name11[source];\
name12[index] = name12[source];\
name13[index] = name13[source];\
name14[index] = name14[source];\
name15[index] = name15[source];\
name16[index] = name16[source];\
name17[index] = name17[source];\
return index;\
}\
}\
\
static void Delete(size_t index) {\
if(index==0)return;\
free.push(index);\
}\
\
static std::queue<size_t> free;\
static std::vector<type1> name1;\
static std::vector<type2> name2;\
static std::vector<type3> name3;\
static std::vector<type4> name4;\
static std::vector<type5> name5;\
static std::vector<type6> name6;\
static std::vector<type7> name7;\
static std::vector<type8> name8;\
static std::vector<type9> name9;\
static std::vector<type10> name10;\
static std::vector<type11> name11;\
static std::vector<type12> name12;\
static std::vector<type13> name13;\
static std::vector<type14> name14;\
static std::vector<type15> name15;\
static std::vector<type16> name16;\
static std::vector<type17> name17;\
};\
}


#define INIT_ECSComponent_17\
(componentName,\
type1, name1,\
type2, name2,\
type3, name3,\
type4, name4,\
type5, name5,\
type6, name6,\
type7, name7,\
type8, name8,\
type9, name9,\
type10, name10,\
type11, name11,\
type12, name12,\
type13, name13,\
type14, name14,\
type15, name15,\
type16, name16,\
type17, name17)\
namespace ECS::Component {\
std::queue<size_t> componentName::free;\
std::vector<type1> componentName::name1(1);\
std::vector<type2> componentName::name2(1);\
std::vector<type3> componentName::name3(1);\
std::vector<type4> componentName::name4(1);\
std::vector<type5> componentName::name5(1);\
std::vector<type6> componentName::name6(1);\
std::vector<type7> componentName::name7(1);\
std::vector<type8> componentName::name8(1);\
std::vector<type9> componentName::name9(1);\
std::vector<type10> componentName::name10(1);\
std::vector<type11> componentName::name11(1);\
std::vector<type12> componentName::name12(1);\
std::vector<type13> componentName::name13(1);\
std::vector<type14> componentName::name14(1);\
std::vector<type15> componentName::name15(1);\
std::vector<type16> componentName::name16(1);\
std::vector<type17> componentName::name17(1);\
}







#define REGISTER_ECSComponent_18\
(componentName,\
type1, name1,\
type2, name2,\
type3, name3,\
type4, name4,\
type5, name5,\
type6, name6,\
type7, name7,\
type8, name8,\
type9, name9,\
type10, name10,\
type11, name11,\
type12, name12,\
type13, name13,\
type14, name14,\
type15, name15,\
type16, name16,\
type17, name17,\
type18, name18)\
namespace ECS::Component {\
struct componentName : ECSBase::ECSComponent<componentName> {\
\
struct Wrapper {\
Wrapper(size_t index)\
: name1(componentName::name1[index]),\
name2(componentName::name2[index]),\
name3(componentName::name3[index]),\
name4(componentName::name4[index]),\
name5(componentName::name5[index]),\
name6(componentName::name6[index]),\
name7(componentName::name7[index]),\
name8(componentName::name8[index]),\
name9(componentName::name9[index]),\
name10(componentName::name10[index]),\
name11(componentName::name11[index]),\
name12(componentName::name12[index]),\
name13(componentName::name13[index]),\
name14(componentName::name14[index]),\
name15(componentName::name15[index]),\
name16(componentName::name16[index]),\
name17(componentName::name17[index]),\
name18(componentName::name18[index]),\
id(index) {}\
type1& name1;\
type2& name2;\
type3& name3;\
type4& name4;\
type5& name5;\
type6& name6;\
type7& name7;\
type8& name8;\
type9& name9;\
type10& name10;\
type11& name11;\
type12& name12;\
type13& name13;\
type14& name14;\
type15& name15;\
type16& name16;\
type17& name17;\
type18& name18;\
const size_t id;\
};\
\
static size_t Create() {\
if(free.empty()) {\
size_t newSize = name1.size() + 1;\
size_t index = name1.size();\
name1.resize(newSize);\
name2.resize(newSize);\
name3.resize(newSize);\
name4.resize(newSize);\
name5.resize(newSize);\
name6.resize(newSize);\
name7.resize(newSize);\
name8.resize(newSize);\
name9.resize(newSize);\
name10.resize(newSize);\
name11.resize(newSize);\
name12.resize(newSize);\
name13.resize(newSize);\
name14.resize(newSize);\
name15.resize(newSize);\
name16.resize(newSize);\
name17.resize(newSize);\
name18.resize(newSize);\
return index;\
}\
else {\
size_t index = free.front();\
free.pop();\
return index;\
}\
}\
\
static size_t Copy(const size_t & source) {\
 if(free.empty()) {\
size_t newSize = name1.size() + 1;\
size_t index = name1.size();\
name1.resize(newSize);\
name2.resize(newSize);\
name3.resize(newSize);\
name4.resize(newSize);\
name5.resize(newSize);\
name6.resize(newSize);\
name7.resize(newSize);\
name8.resize(newSize);\
name9.resize(newSize);\
name10.resize(newSize);\
name11.resize(newSize);\
name12.resize(newSize);\
name13.resize(newSize);\
name14.resize(newSize);\
name15.resize(newSize);\
name16.resize(newSize);\
name17.resize(newSize);\
name18.resize(newSize);\
name1[index] = name1[source];\
name2[index] = name2[source];\
name3[index] = name3[source];\
name4[index] = name4[source];\
name5[index] = name5[source];\
name6[index] = name6[source];\
name7[index] = name7[source];\
name8[index] = name8[source];\
name9[index] = name9[source];\
name10[index] = name10[source];\
name11[index] = name11[source];\
name12[index] = name12[source];\
name13[index] = name13[source];\
name14[index] = name14[source];\
name15[index] = name15[source];\
name16[index] = name16[source];\
name17[index] = name17[source];\
name18[index] = name18[source];\
return index;\
}\
else {\
size_t index = free.front();\
free.pop();\
name1[index] = name1[source];\
name2[index] = name2[source];\
name3[index] = name3[source];\
name4[index] = name4[source];\
name5[index] = name5[source];\
name6[index] = name6[source];\
name7[index] = name7[source];\
name8[index] = name8[source];\
name9[index] = name9[source];\
name10[index] = name10[source];\
name11[index] = name11[source];\
name12[index] = name12[source];\
name13[index] = name13[source];\
name14[index] = name14[source];\
name15[index] = name15[source];\
name16[index] = name16[source];\
name17[index] = name17[source];\
name18[index] = name18[source];\
return index;\
}\
}\
\
static void Delete(size_t index) {\
if(index==0)return;\
free.push(index);\
}\
\
static std::queue<size_t> free;\
static std::vector<type1> name1;\
static std::vector<type2> name2;\
static std::vector<type3> name3;\
static std::vector<type4> name4;\
static std::vector<type5> name5;\
static std::vector<type6> name6;\
static std::vector<type7> name7;\
static std::vector<type8> name8;\
static std::vector<type9> name9;\
static std::vector<type10> name10;\
static std::vector<type11> name11;\
static std::vector<type12> name12;\
static std::vector<type13> name13;\
static std::vector<type14> name14;\
static std::vector<type15> name15;\
static std::vector<type16> name16;\
static std::vector<type17> name17;\
static std::vector<type18> name18;\
};\
}


#define INIT_ECSComponent_18\
(componentName,\
type1, name1,\
type2, name2,\
type3, name3,\
type4, name4,\
type5, name5,\
type6, name6,\
type7, name7,\
type8, name8,\
type9, name9,\
type10, name10,\
type11, name11,\
type12, name12,\
type13, name13,\
type14, name14,\
type15, name15,\
type16, name16,\
type17, name17,\
type18, name18)\
namespace ECS::Component {\
std::queue<size_t> componentName::free;\
std::vector<type1> componentName::name1(1);\
std::vector<type2> componentName::name2(1);\
std::vector<type3> componentName::name3(1);\
std::vector<type4> componentName::name4(1);\
std::vector<type5> componentName::name5(1);\
std::vector<type6> componentName::name6(1);\
std::vector<type7> componentName::name7(1);\
std::vector<type8> componentName::name8(1);\
std::vector<type9> componentName::name9(1);\
std::vector<type10> componentName::name10(1);\
std::vector<type11> componentName::name11(1);\
std::vector<type12> componentName::name12(1);\
std::vector<type13> componentName::name13(1);\
std::vector<type14> componentName::name14(1);\
std::vector<type15> componentName::name15(1);\
std::vector<type16> componentName::name16(1);\
std::vector<type17> componentName::name17(1);\
std::vector<type18> componentName::name18(1);\
}







#define REGISTER_ECSComponent_19\
(componentName,\
type1, name1,\
type2, name2,\
type3, name3,\
type4, name4,\
type5, name5,\
type6, name6,\
type7, name7,\
type8, name8,\
type9, name9,\
type10, name10,\
type11, name11,\
type12, name12,\
type13, name13,\
type14, name14,\
type15, name15,\
type16, name16,\
type17, name17,\
type18, name18,\
type19, name19)\
namespace ECS::Component {\
struct componentName : ECSBase::ECSComponent<componentName> {\
\
struct Wrapper {\
Wrapper(size_t index)\
: name1(componentName::name1[index]),\
name2(componentName::name2[index]),\
name3(componentName::name3[index]),\
name4(componentName::name4[index]),\
name5(componentName::name5[index]),\
name6(componentName::name6[index]),\
name7(componentName::name7[index]),\
name8(componentName::name8[index]),\
name9(componentName::name9[index]),\
name10(componentName::name10[index]),\
name11(componentName::name11[index]),\
name12(componentName::name12[index]),\
name13(componentName::name13[index]),\
name14(componentName::name14[index]),\
name15(componentName::name15[index]),\
name16(componentName::name16[index]),\
name17(componentName::name17[index]),\
name18(componentName::name18[index]),\
name19(componentName::name19[index]),\
id(index) {}\
type1& name1;\
type2& name2;\
type3& name3;\
type4& name4;\
type5& name5;\
type6& name6;\
type7& name7;\
type8& name8;\
type9& name9;\
type10& name10;\
type11& name11;\
type12& name12;\
type13& name13;\
type14& name14;\
type15& name15;\
type16& name16;\
type17& name17;\
type18& name18;\
type19& name19;\
const size_t id;\
};\
\
static size_t Create() {\
if(free.empty()) {\
size_t newSize = name1.size() + 1;\
size_t index = name1.size();\
name1.resize(newSize);\
name2.resize(newSize);\
name3.resize(newSize);\
name4.resize(newSize);\
name5.resize(newSize);\
name6.resize(newSize);\
name7.resize(newSize);\
name8.resize(newSize);\
name9.resize(newSize);\
name10.resize(newSize);\
name11.resize(newSize);\
name12.resize(newSize);\
name13.resize(newSize);\
name14.resize(newSize);\
name15.resize(newSize);\
name16.resize(newSize);\
name17.resize(newSize);\
name18.resize(newSize);\
name19.resize(newSize);\
return index;\
}\
else {\
size_t index = free.front();\
free.pop();\
return index;\
}\
}\
\
static size_t Copy(const size_t & source) {\
 if(free.empty()) {\
size_t newSize = name1.size() + 1;\
size_t index = name1.size();\
name1.resize(newSize);\
name2.resize(newSize);\
name3.resize(newSize);\
name4.resize(newSize);\
name5.resize(newSize);\
name6.resize(newSize);\
name7.resize(newSize);\
name8.resize(newSize);\
name9.resize(newSize);\
name10.resize(newSize);\
name11.resize(newSize);\
name12.resize(newSize);\
name13.resize(newSize);\
name14.resize(newSize);\
name15.resize(newSize);\
name16.resize(newSize);\
name17.resize(newSize);\
name18.resize(newSize);\
name19.resize(newSize);\
name1[index] = name1[source];\
name2[index] = name2[source];\
name3[index] = name3[source];\
name4[index] = name4[source];\
name5[index] = name5[source];\
name6[index] = name6[source];\
name7[index] = name7[source];\
name8[index] = name8[source];\
name9[index] = name9[source];\
name10[index] = name10[source];\
name11[index] = name11[source];\
name12[index] = name12[source];\
name13[index] = name13[source];\
name14[index] = name14[source];\
name15[index] = name15[source];\
name16[index] = name16[source];\
name17[index] = name17[source];\
name18[index] = name18[source];\
name19[index] = name19[source];\
return index;\
}\
else {\
size_t index = free.front();\
free.pop();\
name1[index] = name1[source];\
name2[index] = name2[source];\
name3[index] = name3[source];\
name4[index] = name4[source];\
name5[index] = name5[source];\
name6[index] = name6[source];\
name7[index] = name7[source];\
name8[index] = name8[source];\
name9[index] = name9[source];\
name10[index] = name10[source];\
name11[index] = name11[source];\
name12[index] = name12[source];\
name13[index] = name13[source];\
name14[index] = name14[source];\
name15[index] = name15[source];\
name16[index] = name16[source];\
name17[index] = name17[source];\
name18[index] = name18[source];\
name19[index] = name19[source];\
return index;\
}\
}\
\
static void Delete(size_t index) {\
if(index==0)return;\
free.push(index);\
}\
\
static std::queue<size_t> free;\
static std::vector<type1> name1;\
static std::vector<type2> name2;\
static std::vector<type3> name3;\
static std::vector<type4> name4;\
static std::vector<type5> name5;\
static std::vector<type6> name6;\
static std::vector<type7> name7;\
static std::vector<type8> name8;\
static std::vector<type9> name9;\
static std::vector<type10> name10;\
static std::vector<type11> name11;\
static std::vector<type12> name12;\
static std::vector<type13> name13;\
static std::vector<type14> name14;\
static std::vector<type15> name15;\
static std::vector<type16> name16;\
static std::vector<type17> name17;\
static std::vector<type18> name18;\
static std::vector<type19> name19;\
};\
}


#define INIT_ECSComponent_19\
(componentName,\
type1, name1,\
type2, name2,\
type3, name3,\
type4, name4,\
type5, name5,\
type6, name6,\
type7, name7,\
type8, name8,\
type9, name9,\
type10, name10,\
type11, name11,\
type12, name12,\
type13, name13,\
type14, name14,\
type15, name15,\
type16, name16,\
type17, name17,\
type18, name18,\
type19, name19)\
namespace ECS::Component {\
std::queue<size_t> componentName::free;\
std::vector<type1> componentName::name1(1);\
std::vector<type2> componentName::name2(1);\
std::vector<type3> componentName::name3(1);\
std::vector<type4> componentName::name4(1);\
std::vector<type5> componentName::name5(1);\
std::vector<type6> componentName::name6(1);\
std::vector<type7> componentName::name7(1);\
std::vector<type8> componentName::name8(1);\
std::vector<type9> componentName::name9(1);\
std::vector<type10> componentName::name10(1);\
std::vector<type11> componentName::name11(1);\
std::vector<type12> componentName::name12(1);\
std::vector<type13> componentName::name13(1);\
std::vector<type14> componentName::name14(1);\
std::vector<type15> componentName::name15(1);\
std::vector<type16> componentName::name16(1);\
std::vector<type17> componentName::name17(1);\
std::vector<type18> componentName::name18(1);\
std::vector<type19> componentName::name19(1);\
}







#define REGISTER_ECSComponent_20\
(componentName,\
type1, name1,\
type2, name2,\
type3, name3,\
type4, name4,\
type5, name5,\
type6, name6,\
type7, name7,\
type8, name8,\
type9, name9,\
type10, name10,\
type11, name11,\
type12, name12,\
type13, name13,\
type14, name14,\
type15, name15,\
type16, name16,\
type17, name17,\
type18, name18,\
type19, name19,\
type20, name20)\
namespace ECS::Component {\
struct componentName : ECSBase::ECSComponent<componentName> {\
\
struct Wrapper {\
Wrapper(size_t index)\
: name1(componentName::name1[index]),\
name2(componentName::name2[index]),\
name3(componentName::name3[index]),\
name4(componentName::name4[index]),\
name5(componentName::name5[index]),\
name6(componentName::name6[index]),\
name7(componentName::name7[index]),\
name8(componentName::name8[index]),\
name9(componentName::name9[index]),\
name10(componentName::name10[index]),\
name11(componentName::name11[index]),\
name12(componentName::name12[index]),\
name13(componentName::name13[index]),\
name14(componentName::name14[index]),\
name15(componentName::name15[index]),\
name16(componentName::name16[index]),\
name17(componentName::name17[index]),\
name18(componentName::name18[index]),\
name19(componentName::name19[index]),\
name20(componentName::name20[index]),\
id(index) {}\
type1& name1;\
type2& name2;\
type3& name3;\
type4& name4;\
type5& name5;\
type6& name6;\
type7& name7;\
type8& name8;\
type9& name9;\
type10& name10;\
type11& name11;\
type12& name12;\
type13& name13;\
type14& name14;\
type15& name15;\
type16& name16;\
type17& name17;\
type18& name18;\
type19& name19;\
type20& name20;\
const size_t id;\
};\
\
static size_t Create() {\
if(free.empty()) {\
size_t newSize = name1.size() + 1;\
size_t index = name1.size();\
name1.resize(newSize);\
name2.resize(newSize);\
name3.resize(newSize);\
name4.resize(newSize);\
name5.resize(newSize);\
name6.resize(newSize);\
name7.resize(newSize);\
name8.resize(newSize);\
name9.resize(newSize);\
name10.resize(newSize);\
name11.resize(newSize);\
name12.resize(newSize);\
name13.resize(newSize);\
name14.resize(newSize);\
name15.resize(newSize);\
name16.resize(newSize);\
name17.resize(newSize);\
name18.resize(newSize);\
name19.resize(newSize);\
name20.resize(newSize);\
return index;\
}\
else {\
size_t index = free.front();\
free.pop();\
return index;\
}\
}\
\
static size_t Copy(const size_t & source) {\
 if(free.empty()) {\
size_t newSize = name1.size() + 1;\
size_t index = name1.size();\
name1.resize(newSize);\
name2.resize(newSize);\
name3.resize(newSize);\
name4.resize(newSize);\
name5.resize(newSize);\
name6.resize(newSize);\
name7.resize(newSize);\
name8.resize(newSize);\
name9.resize(newSize);\
name10.resize(newSize);\
name11.resize(newSize);\
name12.resize(newSize);\
name13.resize(newSize);\
name14.resize(newSize);\
name15.resize(newSize);\
name16.resize(newSize);\
name17.resize(newSize);\
name18.resize(newSize);\
name19.resize(newSize);\
name20.resize(newSize);\
name1[index] = name1[source];\
name2[index] = name2[source];\
name3[index] = name3[source];\
name4[index] = name4[source];\
name5[index] = name5[source];\
name6[index] = name6[source];\
name7[index] = name7[source];\
name8[index] = name8[source];\
name9[index] = name9[source];\
name10[index] = name10[source];\
name11[index] = name11[source];\
name12[index] = name12[source];\
name13[index] = name13[source];\
name14[index] = name14[source];\
name15[index] = name15[source];\
name16[index] = name16[source];\
name17[index] = name17[source];\
name18[index] = name18[source];\
name19[index] = name19[source];\
name20[index] = name20[source];\
return index;\
}\
else {\
size_t index = free.front();\
free.pop();\
name1[index] = name1[source];\
name2[index] = name2[source];\
name3[index] = name3[source];\
name4[index] = name4[source];\
name5[index] = name5[source];\
name6[index] = name6[source];\
name7[index] = name7[source];\
name8[index] = name8[source];\
name9[index] = name9[source];\
name10[index] = name10[source];\
name11[index] = name11[source];\
name12[index] = name12[source];\
name13[index] = name13[source];\
name14[index] = name14[source];\
name15[index] = name15[source];\
name16[index] = name16[source];\
name17[index] = name17[source];\
name18[index] = name18[source];\
name19[index] = name19[source];\
name20[index] = name20[source];\
return index;\
}\
}\
\
static void Delete(size_t index) {\
if(index==0)return;\
free.push(index);\
}\
\
static std::queue<size_t> free;\
static std::vector<type1> name1;\
static std::vector<type2> name2;\
static std::vector<type3> name3;\
static std::vector<type4> name4;\
static std::vector<type5> name5;\
static std::vector<type6> name6;\
static std::vector<type7> name7;\
static std::vector<type8> name8;\
static std::vector<type9> name9;\
static std::vector<type10> name10;\
static std::vector<type11> name11;\
static std::vector<type12> name12;\
static std::vector<type13> name13;\
static std::vector<type14> name14;\
static std::vector<type15> name15;\
static std::vector<type16> name16;\
static std::vector<type17> name17;\
static std::vector<type18> name18;\
static std::vector<type19> name19;\
static std::vector<type20> name20;\
};\
}


#define INIT_ECSComponent_20\
(componentName,\
type1, name1,\
type2, name2,\
type3, name3,\
type4, name4,\
type5, name5,\
type6, name6,\
type7, name7,\
type8, name8,\
type9, name9,\
type10, name10,\
type11, name11,\
type12, name12,\
type13, name13,\
type14, name14,\
type15, name15,\
type16, name16,\
type17, name17,\
type18, name18,\
type19, name19,\
type20, name20)\
namespace ECS::Component {\
std::queue<size_t> componentName::free;\
std::vector<type1> componentName::name1(1);\
std::vector<type2> componentName::name2(1);\
std::vector<type3> componentName::name3(1);\
std::vector<type4> componentName::name4(1);\
std::vector<type5> componentName::name5(1);\
std::vector<type6> componentName::name6(1);\
std::vector<type7> componentName::name7(1);\
std::vector<type8> componentName::name8(1);\
std::vector<type9> componentName::name9(1);\
std::vector<type10> componentName::name10(1);\
std::vector<type11> componentName::name11(1);\
std::vector<type12> componentName::name12(1);\
std::vector<type13> componentName::name13(1);\
std::vector<type14> componentName::name14(1);\
std::vector<type15> componentName::name15(1);\
std::vector<type16> componentName::name16(1);\
std::vector<type17> componentName::name17(1);\
std::vector<type18> componentName::name18(1);\
std::vector<type19> componentName::name19(1);\
std::vector<type20> componentName::name20(1);\
}







#define REGISTER_ECSComponent_21\
(componentName,\
type1, name1,\
type2, name2,\
type3, name3,\
type4, name4,\
type5, name5,\
type6, name6,\
type7, name7,\
type8, name8,\
type9, name9,\
type10, name10,\
type11, name11,\
type12, name12,\
type13, name13,\
type14, name14,\
type15, name15,\
type16, name16,\
type17, name17,\
type18, name18,\
type19, name19,\
type20, name20,\
type21, name21)\
namespace ECS::Component {\
struct componentName : ECSBase::ECSComponent<componentName> {\
\
struct Wrapper {\
Wrapper(size_t index)\
: name1(componentName::name1[index]),\
name2(componentName::name2[index]),\
name3(componentName::name3[index]),\
name4(componentName::name4[index]),\
name5(componentName::name5[index]),\
name6(componentName::name6[index]),\
name7(componentName::name7[index]),\
name8(componentName::name8[index]),\
name9(componentName::name9[index]),\
name10(componentName::name10[index]),\
name11(componentName::name11[index]),\
name12(componentName::name12[index]),\
name13(componentName::name13[index]),\
name14(componentName::name14[index]),\
name15(componentName::name15[index]),\
name16(componentName::name16[index]),\
name17(componentName::name17[index]),\
name18(componentName::name18[index]),\
name19(componentName::name19[index]),\
name20(componentName::name20[index]),\
name21(componentName::name21[index]),\
id(index) {}\
type1& name1;\
type2& name2;\
type3& name3;\
type4& name4;\
type5& name5;\
type6& name6;\
type7& name7;\
type8& name8;\
type9& name9;\
type10& name10;\
type11& name11;\
type12& name12;\
type13& name13;\
type14& name14;\
type15& name15;\
type16& name16;\
type17& name17;\
type18& name18;\
type19& name19;\
type20& name20;\
type21& name21;\
const size_t id;\
};\
\
static size_t Create() {\
if(free.empty()) {\
size_t newSize = name1.size() + 1;\
size_t index = name1.size();\
name1.resize(newSize);\
name2.resize(newSize);\
name3.resize(newSize);\
name4.resize(newSize);\
name5.resize(newSize);\
name6.resize(newSize);\
name7.resize(newSize);\
name8.resize(newSize);\
name9.resize(newSize);\
name10.resize(newSize);\
name11.resize(newSize);\
name12.resize(newSize);\
name13.resize(newSize);\
name14.resize(newSize);\
name15.resize(newSize);\
name16.resize(newSize);\
name17.resize(newSize);\
name18.resize(newSize);\
name19.resize(newSize);\
name20.resize(newSize);\
name21.resize(newSize);\
return index;\
}\
else {\
size_t index = free.front();\
free.pop();\
return index;\
}\
}\
\
static size_t Copy(const size_t & source) {\
 if(free.empty()) {\
size_t newSize = name1.size() + 1;\
size_t index = name1.size();\
name1.resize(newSize);\
name2.resize(newSize);\
name3.resize(newSize);\
name4.resize(newSize);\
name5.resize(newSize);\
name6.resize(newSize);\
name7.resize(newSize);\
name8.resize(newSize);\
name9.resize(newSize);\
name10.resize(newSize);\
name11.resize(newSize);\
name12.resize(newSize);\
name13.resize(newSize);\
name14.resize(newSize);\
name15.resize(newSize);\
name16.resize(newSize);\
name17.resize(newSize);\
name18.resize(newSize);\
name19.resize(newSize);\
name20.resize(newSize);\
name21.resize(newSize);\
name1[index] = name1[source];\
name2[index] = name2[source];\
name3[index] = name3[source];\
name4[index] = name4[source];\
name5[index] = name5[source];\
name6[index] = name6[source];\
name7[index] = name7[source];\
name8[index] = name8[source];\
name9[index] = name9[source];\
name10[index] = name10[source];\
name11[index] = name11[source];\
name12[index] = name12[source];\
name13[index] = name13[source];\
name14[index] = name14[source];\
name15[index] = name15[source];\
name16[index] = name16[source];\
name17[index] = name17[source];\
name18[index] = name18[source];\
name19[index] = name19[source];\
name20[index] = name20[source];\
name21[index] = name21[source];\
return index;\
}\
else {\
size_t index = free.front();\
free.pop();\
name1[index] = name1[source];\
name2[index] = name2[source];\
name3[index] = name3[source];\
name4[index] = name4[source];\
name5[index] = name5[source];\
name6[index] = name6[source];\
name7[index] = name7[source];\
name8[index] = name8[source];\
name9[index] = name9[source];\
name10[index] = name10[source];\
name11[index] = name11[source];\
name12[index] = name12[source];\
name13[index] = name13[source];\
name14[index] = name14[source];\
name15[index] = name15[source];\
name16[index] = name16[source];\
name17[index] = name17[source];\
name18[index] = name18[source];\
name19[index] = name19[source];\
name20[index] = name20[source];\
name21[index] = name21[source];\
return index;\
}\
}\
\
static void Delete(size_t index) {\
if(index==0)return;\
free.push(index);\
}\
\
static std::queue<size_t> free;\
static std::vector<type1> name1;\
static std::vector<type2> name2;\
static std::vector<type3> name3;\
static std::vector<type4> name4;\
static std::vector<type5> name5;\
static std::vector<type6> name6;\
static std::vector<type7> name7;\
static std::vector<type8> name8;\
static std::vector<type9> name9;\
static std::vector<type10> name10;\
static std::vector<type11> name11;\
static std::vector<type12> name12;\
static std::vector<type13> name13;\
static std::vector<type14> name14;\
static std::vector<type15> name15;\
static std::vector<type16> name16;\
static std::vector<type17> name17;\
static std::vector<type18> name18;\
static std::vector<type19> name19;\
static std::vector<type20> name20;\
static std::vector<type21> name21;\
};\
}


#define INIT_ECSComponent_21\
(componentName,\
type1, name1,\
type2, name2,\
type3, name3,\
type4, name4,\
type5, name5,\
type6, name6,\
type7, name7,\
type8, name8,\
type9, name9,\
type10, name10,\
type11, name11,\
type12, name12,\
type13, name13,\
type14, name14,\
type15, name15,\
type16, name16,\
type17, name17,\
type18, name18,\
type19, name19,\
type20, name20,\
type21, name21)\
namespace ECS::Component {\
std::queue<size_t> componentName::free;\
std::vector<type1> componentName::name1(1);\
std::vector<type2> componentName::name2(1);\
std::vector<type3> componentName::name3(1);\
std::vector<type4> componentName::name4(1);\
std::vector<type5> componentName::name5(1);\
std::vector<type6> componentName::name6(1);\
std::vector<type7> componentName::name7(1);\
std::vector<type8> componentName::name8(1);\
std::vector<type9> componentName::name9(1);\
std::vector<type10> componentName::name10(1);\
std::vector<type11> componentName::name11(1);\
std::vector<type12> componentName::name12(1);\
std::vector<type13> componentName::name13(1);\
std::vector<type14> componentName::name14(1);\
std::vector<type15> componentName::name15(1);\
std::vector<type16> componentName::name16(1);\
std::vector<type17> componentName::name17(1);\
std::vector<type18> componentName::name18(1);\
std::vector<type19> componentName::name19(1);\
std::vector<type20> componentName::name20(1);\
std::vector<type21> componentName::name21(1);\
}







#define REGISTER_ECSComponent_22\
(componentName,\
type1, name1,\
type2, name2,\
type3, name3,\
type4, name4,\
type5, name5,\
type6, name6,\
type7, name7,\
type8, name8,\
type9, name9,\
type10, name10,\
type11, name11,\
type12, name12,\
type13, name13,\
type14, name14,\
type15, name15,\
type16, name16,\
type17, name17,\
type18, name18,\
type19, name19,\
type20, name20,\
type21, name21,\
type22, name22)\
namespace ECS::Component {\
struct componentName : ECSBase::ECSComponent<componentName> {\
\
struct Wrapper {\
Wrapper(size_t index)\
: name1(componentName::name1[index]),\
name2(componentName::name2[index]),\
name3(componentName::name3[index]),\
name4(componentName::name4[index]),\
name5(componentName::name5[index]),\
name6(componentName::name6[index]),\
name7(componentName::name7[index]),\
name8(componentName::name8[index]),\
name9(componentName::name9[index]),\
name10(componentName::name10[index]),\
name11(componentName::name11[index]),\
name12(componentName::name12[index]),\
name13(componentName::name13[index]),\
name14(componentName::name14[index]),\
name15(componentName::name15[index]),\
name16(componentName::name16[index]),\
name17(componentName::name17[index]),\
name18(componentName::name18[index]),\
name19(componentName::name19[index]),\
name20(componentName::name20[index]),\
name21(componentName::name21[index]),\
name22(componentName::name22[index]),\
id(index) {}\
type1& name1;\
type2& name2;\
type3& name3;\
type4& name4;\
type5& name5;\
type6& name6;\
type7& name7;\
type8& name8;\
type9& name9;\
type10& name10;\
type11& name11;\
type12& name12;\
type13& name13;\
type14& name14;\
type15& name15;\
type16& name16;\
type17& name17;\
type18& name18;\
type19& name19;\
type20& name20;\
type21& name21;\
type22& name22;\
const size_t id;\
};\
\
static size_t Create() {\
if(free.empty()) {\
size_t newSize = name1.size() + 1;\
size_t index = name1.size();\
name1.resize(newSize);\
name2.resize(newSize);\
name3.resize(newSize);\
name4.resize(newSize);\
name5.resize(newSize);\
name6.resize(newSize);\
name7.resize(newSize);\
name8.resize(newSize);\
name9.resize(newSize);\
name10.resize(newSize);\
name11.resize(newSize);\
name12.resize(newSize);\
name13.resize(newSize);\
name14.resize(newSize);\
name15.resize(newSize);\
name16.resize(newSize);\
name17.resize(newSize);\
name18.resize(newSize);\
name19.resize(newSize);\
name20.resize(newSize);\
name21.resize(newSize);\
name22.resize(newSize);\
return index;\
}\
else {\
size_t index = free.front();\
free.pop();\
return index;\
}\
}\
\
static size_t Copy(const size_t & source) {\
 if(free.empty()) {\
size_t newSize = name1.size() + 1;\
size_t index = name1.size();\
name1.resize(newSize);\
name2.resize(newSize);\
name3.resize(newSize);\
name4.resize(newSize);\
name5.resize(newSize);\
name6.resize(newSize);\
name7.resize(newSize);\
name8.resize(newSize);\
name9.resize(newSize);\
name10.resize(newSize);\
name11.resize(newSize);\
name12.resize(newSize);\
name13.resize(newSize);\
name14.resize(newSize);\
name15.resize(newSize);\
name16.resize(newSize);\
name17.resize(newSize);\
name18.resize(newSize);\
name19.resize(newSize);\
name20.resize(newSize);\
name21.resize(newSize);\
name22.resize(newSize);\
name1[index] = name1[source];\
name2[index] = name2[source];\
name3[index] = name3[source];\
name4[index] = name4[source];\
name5[index] = name5[source];\
name6[index] = name6[source];\
name7[index] = name7[source];\
name8[index] = name8[source];\
name9[index] = name9[source];\
name10[index] = name10[source];\
name11[index] = name11[source];\
name12[index] = name12[source];\
name13[index] = name13[source];\
name14[index] = name14[source];\
name15[index] = name15[source];\
name16[index] = name16[source];\
name17[index] = name17[source];\
name18[index] = name18[source];\
name19[index] = name19[source];\
name20[index] = name20[source];\
name21[index] = name21[source];\
name22[index] = name22[source];\
return index;\
}\
else {\
size_t index = free.front();\
free.pop();\
name1[index] = name1[source];\
name2[index] = name2[source];\
name3[index] = name3[source];\
name4[index] = name4[source];\
name5[index] = name5[source];\
name6[index] = name6[source];\
name7[index] = name7[source];\
name8[index] = name8[source];\
name9[index] = name9[source];\
name10[index] = name10[source];\
name11[index] = name11[source];\
name12[index] = name12[source];\
name13[index] = name13[source];\
name14[index] = name14[source];\
name15[index] = name15[source];\
name16[index] = name16[source];\
name17[index] = name17[source];\
name18[index] = name18[source];\
name19[index] = name19[source];\
name20[index] = name20[source];\
name21[index] = name21[source];\
name22[index] = name22[source];\
return index;\
}\
}\
\
static void Delete(size_t index) {\
if(index==0)return;\
free.push(index);\
}\
\
static std::queue<size_t> free;\
static std::vector<type1> name1;\
static std::vector<type2> name2;\
static std::vector<type3> name3;\
static std::vector<type4> name4;\
static std::vector<type5> name5;\
static std::vector<type6> name6;\
static std::vector<type7> name7;\
static std::vector<type8> name8;\
static std::vector<type9> name9;\
static std::vector<type10> name10;\
static std::vector<type11> name11;\
static std::vector<type12> name12;\
static std::vector<type13> name13;\
static std::vector<type14> name14;\
static std::vector<type15> name15;\
static std::vector<type16> name16;\
static std::vector<type17> name17;\
static std::vector<type18> name18;\
static std::vector<type19> name19;\
static std::vector<type20> name20;\
static std::vector<type21> name21;\
static std::vector<type22> name22;\
};\
}


#define INIT_ECSComponent_22\
(componentName,\
type1, name1,\
type2, name2,\
type3, name3,\
type4, name4,\
type5, name5,\
type6, name6,\
type7, name7,\
type8, name8,\
type9, name9,\
type10, name10,\
type11, name11,\
type12, name12,\
type13, name13,\
type14, name14,\
type15, name15,\
type16, name16,\
type17, name17,\
type18, name18,\
type19, name19,\
type20, name20,\
type21, name21,\
type22, name22)\
namespace ECS::Component {\
std::queue<size_t> componentName::free;\
std::vector<type1> componentName::name1(1);\
std::vector<type2> componentName::name2(1);\
std::vector<type3> componentName::name3(1);\
std::vector<type4> componentName::name4(1);\
std::vector<type5> componentName::name5(1);\
std::vector<type6> componentName::name6(1);\
std::vector<type7> componentName::name7(1);\
std::vector<type8> componentName::name8(1);\
std::vector<type9> componentName::name9(1);\
std::vector<type10> componentName::name10(1);\
std::vector<type11> componentName::name11(1);\
std::vector<type12> componentName::name12(1);\
std::vector<type13> componentName::name13(1);\
std::vector<type14> componentName::name14(1);\
std::vector<type15> componentName::name15(1);\
std::vector<type16> componentName::name16(1);\
std::vector<type17> componentName::name17(1);\
std::vector<type18> componentName::name18(1);\
std::vector<type19> componentName::name19(1);\
std::vector<type20> componentName::name20(1);\
std::vector<type21> componentName::name21(1);\
std::vector<type22> componentName::name22(1);\
}







#define REGISTER_ECSComponent_23\
(componentName,\
type1, name1,\
type2, name2,\
type3, name3,\
type4, name4,\
type5, name5,\
type6, name6,\
type7, name7,\
type8, name8,\
type9, name9,\
type10, name10,\
type11, name11,\
type12, name12,\
type13, name13,\
type14, name14,\
type15, name15,\
type16, name16,\
type17, name17,\
type18, name18,\
type19, name19,\
type20, name20,\
type21, name21,\
type22, name22,\
type23, name23)\
namespace ECS::Component {\
struct componentName : ECSBase::ECSComponent<componentName> {\
\
struct Wrapper {\
Wrapper(size_t index)\
: name1(componentName::name1[index]),\
name2(componentName::name2[index]),\
name3(componentName::name3[index]),\
name4(componentName::name4[index]),\
name5(componentName::name5[index]),\
name6(componentName::name6[index]),\
name7(componentName::name7[index]),\
name8(componentName::name8[index]),\
name9(componentName::name9[index]),\
name10(componentName::name10[index]),\
name11(componentName::name11[index]),\
name12(componentName::name12[index]),\
name13(componentName::name13[index]),\
name14(componentName::name14[index]),\
name15(componentName::name15[index]),\
name16(componentName::name16[index]),\
name17(componentName::name17[index]),\
name18(componentName::name18[index]),\
name19(componentName::name19[index]),\
name20(componentName::name20[index]),\
name21(componentName::name21[index]),\
name22(componentName::name22[index]),\
name23(componentName::name23[index]),\
id(index) {}\
type1& name1;\
type2& name2;\
type3& name3;\
type4& name4;\
type5& name5;\
type6& name6;\
type7& name7;\
type8& name8;\
type9& name9;\
type10& name10;\
type11& name11;\
type12& name12;\
type13& name13;\
type14& name14;\
type15& name15;\
type16& name16;\
type17& name17;\
type18& name18;\
type19& name19;\
type20& name20;\
type21& name21;\
type22& name22;\
type23& name23;\
const size_t id;\
};\
\
static size_t Create() {\
if(free.empty()) {\
size_t newSize = name1.size() + 1;\
size_t index = name1.size();\
name1.resize(newSize);\
name2.resize(newSize);\
name3.resize(newSize);\
name4.resize(newSize);\
name5.resize(newSize);\
name6.resize(newSize);\
name7.resize(newSize);\
name8.resize(newSize);\
name9.resize(newSize);\
name10.resize(newSize);\
name11.resize(newSize);\
name12.resize(newSize);\
name13.resize(newSize);\
name14.resize(newSize);\
name15.resize(newSize);\
name16.resize(newSize);\
name17.resize(newSize);\
name18.resize(newSize);\
name19.resize(newSize);\
name20.resize(newSize);\
name21.resize(newSize);\
name22.resize(newSize);\
name23.resize(newSize);\
return index;\
}\
else {\
size_t index = free.front();\
free.pop();\
return index;\
}\
}\
\
static size_t Copy(const size_t & source) {\
 if(free.empty()) {\
size_t newSize = name1.size() + 1;\
size_t index = name1.size();\
name1.resize(newSize);\
name2.resize(newSize);\
name3.resize(newSize);\
name4.resize(newSize);\
name5.resize(newSize);\
name6.resize(newSize);\
name7.resize(newSize);\
name8.resize(newSize);\
name9.resize(newSize);\
name10.resize(newSize);\
name11.resize(newSize);\
name12.resize(newSize);\
name13.resize(newSize);\
name14.resize(newSize);\
name15.resize(newSize);\
name16.resize(newSize);\
name17.resize(newSize);\
name18.resize(newSize);\
name19.resize(newSize);\
name20.resize(newSize);\
name21.resize(newSize);\
name22.resize(newSize);\
name23.resize(newSize);\
name1[index] = name1[source];\
name2[index] = name2[source];\
name3[index] = name3[source];\
name4[index] = name4[source];\
name5[index] = name5[source];\
name6[index] = name6[source];\
name7[index] = name7[source];\
name8[index] = name8[source];\
name9[index] = name9[source];\
name10[index] = name10[source];\
name11[index] = name11[source];\
name12[index] = name12[source];\
name13[index] = name13[source];\
name14[index] = name14[source];\
name15[index] = name15[source];\
name16[index] = name16[source];\
name17[index] = name17[source];\
name18[index] = name18[source];\
name19[index] = name19[source];\
name20[index] = name20[source];\
name21[index] = name21[source];\
name22[index] = name22[source];\
name23[index] = name23[source];\
return index;\
}\
else {\
size_t index = free.front();\
free.pop();\
name1[index] = name1[source];\
name2[index] = name2[source];\
name3[index] = name3[source];\
name4[index] = name4[source];\
name5[index] = name5[source];\
name6[index] = name6[source];\
name7[index] = name7[source];\
name8[index] = name8[source];\
name9[index] = name9[source];\
name10[index] = name10[source];\
name11[index] = name11[source];\
name12[index] = name12[source];\
name13[index] = name13[source];\
name14[index] = name14[source];\
name15[index] = name15[source];\
name16[index] = name16[source];\
name17[index] = name17[source];\
name18[index] = name18[source];\
name19[index] = name19[source];\
name20[index] = name20[source];\
name21[index] = name21[source];\
name22[index] = name22[source];\
name23[index] = name23[source];\
return index;\
}\
}\
\
static void Delete(size_t index) {\
if(index==0)return;\
free.push(index);\
}\
\
static std::queue<size_t> free;\
static std::vector<type1> name1;\
static std::vector<type2> name2;\
static std::vector<type3> name3;\
static std::vector<type4> name4;\
static std::vector<type5> name5;\
static std::vector<type6> name6;\
static std::vector<type7> name7;\
static std::vector<type8> name8;\
static std::vector<type9> name9;\
static std::vector<type10> name10;\
static std::vector<type11> name11;\
static std::vector<type12> name12;\
static std::vector<type13> name13;\
static std::vector<type14> name14;\
static std::vector<type15> name15;\
static std::vector<type16> name16;\
static std::vector<type17> name17;\
static std::vector<type18> name18;\
static std::vector<type19> name19;\
static std::vector<type20> name20;\
static std::vector<type21> name21;\
static std::vector<type22> name22;\
static std::vector<type23> name23;\
};\
}


#define INIT_ECSComponent_23\
(componentName,\
type1, name1,\
type2, name2,\
type3, name3,\
type4, name4,\
type5, name5,\
type6, name6,\
type7, name7,\
type8, name8,\
type9, name9,\
type10, name10,\
type11, name11,\
type12, name12,\
type13, name13,\
type14, name14,\
type15, name15,\
type16, name16,\
type17, name17,\
type18, name18,\
type19, name19,\
type20, name20,\
type21, name21,\
type22, name22,\
type23, name23)\
namespace ECS::Component {\
std::queue<size_t> componentName::free;\
std::vector<type1> componentName::name1(1);\
std::vector<type2> componentName::name2(1);\
std::vector<type3> componentName::name3(1);\
std::vector<type4> componentName::name4(1);\
std::vector<type5> componentName::name5(1);\
std::vector<type6> componentName::name6(1);\
std::vector<type7> componentName::name7(1);\
std::vector<type8> componentName::name8(1);\
std::vector<type9> componentName::name9(1);\
std::vector<type10> componentName::name10(1);\
std::vector<type11> componentName::name11(1);\
std::vector<type12> componentName::name12(1);\
std::vector<type13> componentName::name13(1);\
std::vector<type14> componentName::name14(1);\
std::vector<type15> componentName::name15(1);\
std::vector<type16> componentName::name16(1);\
std::vector<type17> componentName::name17(1);\
std::vector<type18> componentName::name18(1);\
std::vector<type19> componentName::name19(1);\
std::vector<type20> componentName::name20(1);\
std::vector<type21> componentName::name21(1);\
std::vector<type22> componentName::name22(1);\
std::vector<type23> componentName::name23(1);\
}







#define REGISTER_ECSComponent_24\
(componentName,\
type1, name1,\
type2, name2,\
type3, name3,\
type4, name4,\
type5, name5,\
type6, name6,\
type7, name7,\
type8, name8,\
type9, name9,\
type10, name10,\
type11, name11,\
type12, name12,\
type13, name13,\
type14, name14,\
type15, name15,\
type16, name16,\
type17, name17,\
type18, name18,\
type19, name19,\
type20, name20,\
type21, name21,\
type22, name22,\
type23, name23,\
type24, name24)\
namespace ECS::Component {\
struct componentName : ECSBase::ECSComponent<componentName> {\
\
struct Wrapper {\
Wrapper(size_t index)\
: name1(componentName::name1[index]),\
name2(componentName::name2[index]),\
name3(componentName::name3[index]),\
name4(componentName::name4[index]),\
name5(componentName::name5[index]),\
name6(componentName::name6[index]),\
name7(componentName::name7[index]),\
name8(componentName::name8[index]),\
name9(componentName::name9[index]),\
name10(componentName::name10[index]),\
name11(componentName::name11[index]),\
name12(componentName::name12[index]),\
name13(componentName::name13[index]),\
name14(componentName::name14[index]),\
name15(componentName::name15[index]),\
name16(componentName::name16[index]),\
name17(componentName::name17[index]),\
name18(componentName::name18[index]),\
name19(componentName::name19[index]),\
name20(componentName::name20[index]),\
name21(componentName::name21[index]),\
name22(componentName::name22[index]),\
name23(componentName::name23[index]),\
name24(componentName::name24[index]),\
id(index) {}\
type1& name1;\
type2& name2;\
type3& name3;\
type4& name4;\
type5& name5;\
type6& name6;\
type7& name7;\
type8& name8;\
type9& name9;\
type10& name10;\
type11& name11;\
type12& name12;\
type13& name13;\
type14& name14;\
type15& name15;\
type16& name16;\
type17& name17;\
type18& name18;\
type19& name19;\
type20& name20;\
type21& name21;\
type22& name22;\
type23& name23;\
type24& name24;\
const size_t id;\
};\
\
static size_t Create() {\
if(free.empty()) {\
size_t newSize = name1.size() + 1;\
size_t index = name1.size();\
name1.resize(newSize);\
name2.resize(newSize);\
name3.resize(newSize);\
name4.resize(newSize);\
name5.resize(newSize);\
name6.resize(newSize);\
name7.resize(newSize);\
name8.resize(newSize);\
name9.resize(newSize);\
name10.resize(newSize);\
name11.resize(newSize);\
name12.resize(newSize);\
name13.resize(newSize);\
name14.resize(newSize);\
name15.resize(newSize);\
name16.resize(newSize);\
name17.resize(newSize);\
name18.resize(newSize);\
name19.resize(newSize);\
name20.resize(newSize);\
name21.resize(newSize);\
name22.resize(newSize);\
name23.resize(newSize);\
name24.resize(newSize);\
return index;\
}\
else {\
size_t index = free.front();\
free.pop();\
return index;\
}\
}\
\
static size_t Copy(const size_t & source) {\
 if(free.empty()) {\
size_t newSize = name1.size() + 1;\
size_t index = name1.size();\
name1.resize(newSize);\
name2.resize(newSize);\
name3.resize(newSize);\
name4.resize(newSize);\
name5.resize(newSize);\
name6.resize(newSize);\
name7.resize(newSize);\
name8.resize(newSize);\
name9.resize(newSize);\
name10.resize(newSize);\
name11.resize(newSize);\
name12.resize(newSize);\
name13.resize(newSize);\
name14.resize(newSize);\
name15.resize(newSize);\
name16.resize(newSize);\
name17.resize(newSize);\
name18.resize(newSize);\
name19.resize(newSize);\
name20.resize(newSize);\
name21.resize(newSize);\
name22.resize(newSize);\
name23.resize(newSize);\
name24.resize(newSize);\
name1[index] = name1[source];\
name2[index] = name2[source];\
name3[index] = name3[source];\
name4[index] = name4[source];\
name5[index] = name5[source];\
name6[index] = name6[source];\
name7[index] = name7[source];\
name8[index] = name8[source];\
name9[index] = name9[source];\
name10[index] = name10[source];\
name11[index] = name11[source];\
name12[index] = name12[source];\
name13[index] = name13[source];\
name14[index] = name14[source];\
name15[index] = name15[source];\
name16[index] = name16[source];\
name17[index] = name17[source];\
name18[index] = name18[source];\
name19[index] = name19[source];\
name20[index] = name20[source];\
name21[index] = name21[source];\
name22[index] = name22[source];\
name23[index] = name23[source];\
name24[index] = name24[source];\
return index;\
}\
else {\
size_t index = free.front();\
free.pop();\
name1[index] = name1[source];\
name2[index] = name2[source];\
name3[index] = name3[source];\
name4[index] = name4[source];\
name5[index] = name5[source];\
name6[index] = name6[source];\
name7[index] = name7[source];\
name8[index] = name8[source];\
name9[index] = name9[source];\
name10[index] = name10[source];\
name11[index] = name11[source];\
name12[index] = name12[source];\
name13[index] = name13[source];\
name14[index] = name14[source];\
name15[index] = name15[source];\
name16[index] = name16[source];\
name17[index] = name17[source];\
name18[index] = name18[source];\
name19[index] = name19[source];\
name20[index] = name20[source];\
name21[index] = name21[source];\
name22[index] = name22[source];\
name23[index] = name23[source];\
name24[index] = name24[source];\
return index;\
}\
}\
\
static void Delete(size_t index) {\
if(index==0)return;\
free.push(index);\
}\
\
static std::queue<size_t> free;\
static std::vector<type1> name1;\
static std::vector<type2> name2;\
static std::vector<type3> name3;\
static std::vector<type4> name4;\
static std::vector<type5> name5;\
static std::vector<type6> name6;\
static std::vector<type7> name7;\
static std::vector<type8> name8;\
static std::vector<type9> name9;\
static std::vector<type10> name10;\
static std::vector<type11> name11;\
static std::vector<type12> name12;\
static std::vector<type13> name13;\
static std::vector<type14> name14;\
static std::vector<type15> name15;\
static std::vector<type16> name16;\
static std::vector<type17> name17;\
static std::vector<type18> name18;\
static std::vector<type19> name19;\
static std::vector<type20> name20;\
static std::vector<type21> name21;\
static std::vector<type22> name22;\
static std::vector<type23> name23;\
static std::vector<type24> name24;\
};\
}


#define INIT_ECSComponent_24\
(componentName,\
type1, name1,\
type2, name2,\
type3, name3,\
type4, name4,\
type5, name5,\
type6, name6,\
type7, name7,\
type8, name8,\
type9, name9,\
type10, name10,\
type11, name11,\
type12, name12,\
type13, name13,\
type14, name14,\
type15, name15,\
type16, name16,\
type17, name17,\
type18, name18,\
type19, name19,\
type20, name20,\
type21, name21,\
type22, name22,\
type23, name23,\
type24, name24)\
namespace ECS::Component {\
std::queue<size_t> componentName::free;\
std::vector<type1> componentName::name1(1);\
std::vector<type2> componentName::name2(1);\
std::vector<type3> componentName::name3(1);\
std::vector<type4> componentName::name4(1);\
std::vector<type5> componentName::name5(1);\
std::vector<type6> componentName::name6(1);\
std::vector<type7> componentName::name7(1);\
std::vector<type8> componentName::name8(1);\
std::vector<type9> componentName::name9(1);\
std::vector<type10> componentName::name10(1);\
std::vector<type11> componentName::name11(1);\
std::vector<type12> componentName::name12(1);\
std::vector<type13> componentName::name13(1);\
std::vector<type14> componentName::name14(1);\
std::vector<type15> componentName::name15(1);\
std::vector<type16> componentName::name16(1);\
std::vector<type17> componentName::name17(1);\
std::vector<type18> componentName::name18(1);\
std::vector<type19> componentName::name19(1);\
std::vector<type20> componentName::name20(1);\
std::vector<type21> componentName::name21(1);\
std::vector<type22> componentName::name22(1);\
std::vector<type23> componentName::name23(1);\
std::vector<type24> componentName::name24(1);\
}







#define REGISTER_ECSComponent_25\
(componentName,\
type1, name1,\
type2, name2,\
type3, name3,\
type4, name4,\
type5, name5,\
type6, name6,\
type7, name7,\
type8, name8,\
type9, name9,\
type10, name10,\
type11, name11,\
type12, name12,\
type13, name13,\
type14, name14,\
type15, name15,\
type16, name16,\
type17, name17,\
type18, name18,\
type19, name19,\
type20, name20,\
type21, name21,\
type22, name22,\
type23, name23,\
type24, name24,\
type25, name25)\
namespace ECS::Component {\
struct componentName : ECSBase::ECSComponent<componentName> {\
\
struct Wrapper {\
Wrapper(size_t index)\
: name1(componentName::name1[index]),\
name2(componentName::name2[index]),\
name3(componentName::name3[index]),\
name4(componentName::name4[index]),\
name5(componentName::name5[index]),\
name6(componentName::name6[index]),\
name7(componentName::name7[index]),\
name8(componentName::name8[index]),\
name9(componentName::name9[index]),\
name10(componentName::name10[index]),\
name11(componentName::name11[index]),\
name12(componentName::name12[index]),\
name13(componentName::name13[index]),\
name14(componentName::name14[index]),\
name15(componentName::name15[index]),\
name16(componentName::name16[index]),\
name17(componentName::name17[index]),\
name18(componentName::name18[index]),\
name19(componentName::name19[index]),\
name20(componentName::name20[index]),\
name21(componentName::name21[index]),\
name22(componentName::name22[index]),\
name23(componentName::name23[index]),\
name24(componentName::name24[index]),\
name25(componentName::name25[index]),\
id(index) {}\
type1& name1;\
type2& name2;\
type3& name3;\
type4& name4;\
type5& name5;\
type6& name6;\
type7& name7;\
type8& name8;\
type9& name9;\
type10& name10;\
type11& name11;\
type12& name12;\
type13& name13;\
type14& name14;\
type15& name15;\
type16& name16;\
type17& name17;\
type18& name18;\
type19& name19;\
type20& name20;\
type21& name21;\
type22& name22;\
type23& name23;\
type24& name24;\
type25& name25;\
const size_t id;\
};\
\
static size_t Create() {\
if(free.empty()) {\
size_t newSize = name1.size() + 1;\
size_t index = name1.size();\
name1.resize(newSize);\
name2.resize(newSize);\
name3.resize(newSize);\
name4.resize(newSize);\
name5.resize(newSize);\
name6.resize(newSize);\
name7.resize(newSize);\
name8.resize(newSize);\
name9.resize(newSize);\
name10.resize(newSize);\
name11.resize(newSize);\
name12.resize(newSize);\
name13.resize(newSize);\
name14.resize(newSize);\
name15.resize(newSize);\
name16.resize(newSize);\
name17.resize(newSize);\
name18.resize(newSize);\
name19.resize(newSize);\
name20.resize(newSize);\
name21.resize(newSize);\
name22.resize(newSize);\
name23.resize(newSize);\
name24.resize(newSize);\
name25.resize(newSize);\
return index;\
}\
else {\
size_t index = free.front();\
free.pop();\
return index;\
}\
}\
\
static size_t Copy(const size_t & source) {\
 if(free.empty()) {\
size_t newSize = name1.size() + 1;\
size_t index = name1.size();\
name1.resize(newSize);\
name2.resize(newSize);\
name3.resize(newSize);\
name4.resize(newSize);\
name5.resize(newSize);\
name6.resize(newSize);\
name7.resize(newSize);\
name8.resize(newSize);\
name9.resize(newSize);\
name10.resize(newSize);\
name11.resize(newSize);\
name12.resize(newSize);\
name13.resize(newSize);\
name14.resize(newSize);\
name15.resize(newSize);\
name16.resize(newSize);\
name17.resize(newSize);\
name18.resize(newSize);\
name19.resize(newSize);\
name20.resize(newSize);\
name21.resize(newSize);\
name22.resize(newSize);\
name23.resize(newSize);\
name24.resize(newSize);\
name25.resize(newSize);\
name1[index] = name1[source];\
name2[index] = name2[source];\
name3[index] = name3[source];\
name4[index] = name4[source];\
name5[index] = name5[source];\
name6[index] = name6[source];\
name7[index] = name7[source];\
name8[index] = name8[source];\
name9[index] = name9[source];\
name10[index] = name10[source];\
name11[index] = name11[source];\
name12[index] = name12[source];\
name13[index] = name13[source];\
name14[index] = name14[source];\
name15[index] = name15[source];\
name16[index] = name16[source];\
name17[index] = name17[source];\
name18[index] = name18[source];\
name19[index] = name19[source];\
name20[index] = name20[source];\
name21[index] = name21[source];\
name22[index] = name22[source];\
name23[index] = name23[source];\
name24[index] = name24[source];\
name25[index] = name25[source];\
return index;\
}\
else {\
size_t index = free.front();\
free.pop();\
name1[index] = name1[source];\
name2[index] = name2[source];\
name3[index] = name3[source];\
name4[index] = name4[source];\
name5[index] = name5[source];\
name6[index] = name6[source];\
name7[index] = name7[source];\
name8[index] = name8[source];\
name9[index] = name9[source];\
name10[index] = name10[source];\
name11[index] = name11[source];\
name12[index] = name12[source];\
name13[index] = name13[source];\
name14[index] = name14[source];\
name15[index] = name15[source];\
name16[index] = name16[source];\
name17[index] = name17[source];\
name18[index] = name18[source];\
name19[index] = name19[source];\
name20[index] = name20[source];\
name21[index] = name21[source];\
name22[index] = name22[source];\
name23[index] = name23[source];\
name24[index] = name24[source];\
name25[index] = name25[source];\
return index;\
}\
}\
\
static void Delete(size_t index) {\
if(index==0)return;\
free.push(index);\
}\
\
static std::queue<size_t> free;\
static std::vector<type1> name1;\
static std::vector<type2> name2;\
static std::vector<type3> name3;\
static std::vector<type4> name4;\
static std::vector<type5> name5;\
static std::vector<type6> name6;\
static std::vector<type7> name7;\
static std::vector<type8> name8;\
static std::vector<type9> name9;\
static std::vector<type10> name10;\
static std::vector<type11> name11;\
static std::vector<type12> name12;\
static std::vector<type13> name13;\
static std::vector<type14> name14;\
static std::vector<type15> name15;\
static std::vector<type16> name16;\
static std::vector<type17> name17;\
static std::vector<type18> name18;\
static std::vector<type19> name19;\
static std::vector<type20> name20;\
static std::vector<type21> name21;\
static std::vector<type22> name22;\
static std::vector<type23> name23;\
static std::vector<type24> name24;\
static std::vector<type25> name25;\
};\
}


#define INIT_ECSComponent_25\
(componentName,\
type1, name1,\
type2, name2,\
type3, name3,\
type4, name4,\
type5, name5,\
type6, name6,\
type7, name7,\
type8, name8,\
type9, name9,\
type10, name10,\
type11, name11,\
type12, name12,\
type13, name13,\
type14, name14,\
type15, name15,\
type16, name16,\
type17, name17,\
type18, name18,\
type19, name19,\
type20, name20,\
type21, name21,\
type22, name22,\
type23, name23,\
type24, name24,\
type25, name25)\
namespace ECS::Component {\
std::queue<size_t> componentName::free;\
std::vector<type1> componentName::name1(1);\
std::vector<type2> componentName::name2(1);\
std::vector<type3> componentName::name3(1);\
std::vector<type4> componentName::name4(1);\
std::vector<type5> componentName::name5(1);\
std::vector<type6> componentName::name6(1);\
std::vector<type7> componentName::name7(1);\
std::vector<type8> componentName::name8(1);\
std::vector<type9> componentName::name9(1);\
std::vector<type10> componentName::name10(1);\
std::vector<type11> componentName::name11(1);\
std::vector<type12> componentName::name12(1);\
std::vector<type13> componentName::name13(1);\
std::vector<type14> componentName::name14(1);\
std::vector<type15> componentName::name15(1);\
std::vector<type16> componentName::name16(1);\
std::vector<type17> componentName::name17(1);\
std::vector<type18> componentName::name18(1);\
std::vector<type19> componentName::name19(1);\
std::vector<type20> componentName::name20(1);\
std::vector<type21> componentName::name21(1);\
std::vector<type22> componentName::name22(1);\
std::vector<type23> componentName::name23(1);\
std::vector<type24> componentName::name24(1);\
std::vector<type25> componentName::name25(1);\
}







#define REGISTER_ECSComponent_26\
(componentName,\
type1, name1,\
type2, name2,\
type3, name3,\
type4, name4,\
type5, name5,\
type6, name6,\
type7, name7,\
type8, name8,\
type9, name9,\
type10, name10,\
type11, name11,\
type12, name12,\
type13, name13,\
type14, name14,\
type15, name15,\
type16, name16,\
type17, name17,\
type18, name18,\
type19, name19,\
type20, name20,\
type21, name21,\
type22, name22,\
type23, name23,\
type24, name24,\
type25, name25,\
type26, name26)\
namespace ECS::Component {\
struct componentName : ECSBase::ECSComponent<componentName> {\
\
struct Wrapper {\
Wrapper(size_t index)\
: name1(componentName::name1[index]),\
name2(componentName::name2[index]),\
name3(componentName::name3[index]),\
name4(componentName::name4[index]),\
name5(componentName::name5[index]),\
name6(componentName::name6[index]),\
name7(componentName::name7[index]),\
name8(componentName::name8[index]),\
name9(componentName::name9[index]),\
name10(componentName::name10[index]),\
name11(componentName::name11[index]),\
name12(componentName::name12[index]),\
name13(componentName::name13[index]),\
name14(componentName::name14[index]),\
name15(componentName::name15[index]),\
name16(componentName::name16[index]),\
name17(componentName::name17[index]),\
name18(componentName::name18[index]),\
name19(componentName::name19[index]),\
name20(componentName::name20[index]),\
name21(componentName::name21[index]),\
name22(componentName::name22[index]),\
name23(componentName::name23[index]),\
name24(componentName::name24[index]),\
name25(componentName::name25[index]),\
name26(componentName::name26[index]),\
id(index) {}\
type1& name1;\
type2& name2;\
type3& name3;\
type4& name4;\
type5& name5;\
type6& name6;\
type7& name7;\
type8& name8;\
type9& name9;\
type10& name10;\
type11& name11;\
type12& name12;\
type13& name13;\
type14& name14;\
type15& name15;\
type16& name16;\
type17& name17;\
type18& name18;\
type19& name19;\
type20& name20;\
type21& name21;\
type22& name22;\
type23& name23;\
type24& name24;\
type25& name25;\
type26& name26;\
const size_t id;\
};\
\
static size_t Create() {\
if(free.empty()) {\
size_t newSize = name1.size() + 1;\
size_t index = name1.size();\
name1.resize(newSize);\
name2.resize(newSize);\
name3.resize(newSize);\
name4.resize(newSize);\
name5.resize(newSize);\
name6.resize(newSize);\
name7.resize(newSize);\
name8.resize(newSize);\
name9.resize(newSize);\
name10.resize(newSize);\
name11.resize(newSize);\
name12.resize(newSize);\
name13.resize(newSize);\
name14.resize(newSize);\
name15.resize(newSize);\
name16.resize(newSize);\
name17.resize(newSize);\
name18.resize(newSize);\
name19.resize(newSize);\
name20.resize(newSize);\
name21.resize(newSize);\
name22.resize(newSize);\
name23.resize(newSize);\
name24.resize(newSize);\
name25.resize(newSize);\
name26.resize(newSize);\
return index;\
}\
else {\
size_t index = free.front();\
free.pop();\
return index;\
}\
}\
\
static size_t Copy(const size_t & source) {\
 if(free.empty()) {\
size_t newSize = name1.size() + 1;\
size_t index = name1.size();\
name1.resize(newSize);\
name2.resize(newSize);\
name3.resize(newSize);\
name4.resize(newSize);\
name5.resize(newSize);\
name6.resize(newSize);\
name7.resize(newSize);\
name8.resize(newSize);\
name9.resize(newSize);\
name10.resize(newSize);\
name11.resize(newSize);\
name12.resize(newSize);\
name13.resize(newSize);\
name14.resize(newSize);\
name15.resize(newSize);\
name16.resize(newSize);\
name17.resize(newSize);\
name18.resize(newSize);\
name19.resize(newSize);\
name20.resize(newSize);\
name21.resize(newSize);\
name22.resize(newSize);\
name23.resize(newSize);\
name24.resize(newSize);\
name25.resize(newSize);\
name26.resize(newSize);\
name1[index] = name1[source];\
name2[index] = name2[source];\
name3[index] = name3[source];\
name4[index] = name4[source];\
name5[index] = name5[source];\
name6[index] = name6[source];\
name7[index] = name7[source];\
name8[index] = name8[source];\
name9[index] = name9[source];\
name10[index] = name10[source];\
name11[index] = name11[source];\
name12[index] = name12[source];\
name13[index] = name13[source];\
name14[index] = name14[source];\
name15[index] = name15[source];\
name16[index] = name16[source];\
name17[index] = name17[source];\
name18[index] = name18[source];\
name19[index] = name19[source];\
name20[index] = name20[source];\
name21[index] = name21[source];\
name22[index] = name22[source];\
name23[index] = name23[source];\
name24[index] = name24[source];\
name25[index] = name25[source];\
name26[index] = name26[source];\
return index;\
}\
else {\
size_t index = free.front();\
free.pop();\
name1[index] = name1[source];\
name2[index] = name2[source];\
name3[index] = name3[source];\
name4[index] = name4[source];\
name5[index] = name5[source];\
name6[index] = name6[source];\
name7[index] = name7[source];\
name8[index] = name8[source];\
name9[index] = name9[source];\
name10[index] = name10[source];\
name11[index] = name11[source];\
name12[index] = name12[source];\
name13[index] = name13[source];\
name14[index] = name14[source];\
name15[index] = name15[source];\
name16[index] = name16[source];\
name17[index] = name17[source];\
name18[index] = name18[source];\
name19[index] = name19[source];\
name20[index] = name20[source];\
name21[index] = name21[source];\
name22[index] = name22[source];\
name23[index] = name23[source];\
name24[index] = name24[source];\
name25[index] = name25[source];\
name26[index] = name26[source];\
return index;\
}\
}\
\
static void Delete(size_t index) {\
if(index==0)return;\
free.push(index);\
}\
\
static std::queue<size_t> free;\
static std::vector<type1> name1;\
static std::vector<type2> name2;\
static std::vector<type3> name3;\
static std::vector<type4> name4;\
static std::vector<type5> name5;\
static std::vector<type6> name6;\
static std::vector<type7> name7;\
static std::vector<type8> name8;\
static std::vector<type9> name9;\
static std::vector<type10> name10;\
static std::vector<type11> name11;\
static std::vector<type12> name12;\
static std::vector<type13> name13;\
static std::vector<type14> name14;\
static std::vector<type15> name15;\
static std::vector<type16> name16;\
static std::vector<type17> name17;\
static std::vector<type18> name18;\
static std::vector<type19> name19;\
static std::vector<type20> name20;\
static std::vector<type21> name21;\
static std::vector<type22> name22;\
static std::vector<type23> name23;\
static std::vector<type24> name24;\
static std::vector<type25> name25;\
static std::vector<type26> name26;\
};\
}


#define INIT_ECSComponent_26\
(componentName,\
type1, name1,\
type2, name2,\
type3, name3,\
type4, name4,\
type5, name5,\
type6, name6,\
type7, name7,\
type8, name8,\
type9, name9,\
type10, name10,\
type11, name11,\
type12, name12,\
type13, name13,\
type14, name14,\
type15, name15,\
type16, name16,\
type17, name17,\
type18, name18,\
type19, name19,\
type20, name20,\
type21, name21,\
type22, name22,\
type23, name23,\
type24, name24,\
type25, name25,\
type26, name26)\
namespace ECS::Component {\
std::queue<size_t> componentName::free;\
std::vector<type1> componentName::name1(1);\
std::vector<type2> componentName::name2(1);\
std::vector<type3> componentName::name3(1);\
std::vector<type4> componentName::name4(1);\
std::vector<type5> componentName::name5(1);\
std::vector<type6> componentName::name6(1);\
std::vector<type7> componentName::name7(1);\
std::vector<type8> componentName::name8(1);\
std::vector<type9> componentName::name9(1);\
std::vector<type10> componentName::name10(1);\
std::vector<type11> componentName::name11(1);\
std::vector<type12> componentName::name12(1);\
std::vector<type13> componentName::name13(1);\
std::vector<type14> componentName::name14(1);\
std::vector<type15> componentName::name15(1);\
std::vector<type16> componentName::name16(1);\
std::vector<type17> componentName::name17(1);\
std::vector<type18> componentName::name18(1);\
std::vector<type19> componentName::name19(1);\
std::vector<type20> componentName::name20(1);\
std::vector<type21> componentName::name21(1);\
std::vector<type22> componentName::name22(1);\
std::vector<type23> componentName::name23(1);\
std::vector<type24> componentName::name24(1);\
std::vector<type25> componentName::name25(1);\
std::vector<type26> componentName::name26(1);\
}







#define REGISTER_ECSComponent_27\
(componentName,\
type1, name1,\
type2, name2,\
type3, name3,\
type4, name4,\
type5, name5,\
type6, name6,\
type7, name7,\
type8, name8,\
type9, name9,\
type10, name10,\
type11, name11,\
type12, name12,\
type13, name13,\
type14, name14,\
type15, name15,\
type16, name16,\
type17, name17,\
type18, name18,\
type19, name19,\
type20, name20,\
type21, name21,\
type22, name22,\
type23, name23,\
type24, name24,\
type25, name25,\
type26, name26,\
type27, name27)\
namespace ECS::Component {\
struct componentName : ECSBase::ECSComponent<componentName> {\
\
struct Wrapper {\
Wrapper(size_t index)\
: name1(componentName::name1[index]),\
name2(componentName::name2[index]),\
name3(componentName::name3[index]),\
name4(componentName::name4[index]),\
name5(componentName::name5[index]),\
name6(componentName::name6[index]),\
name7(componentName::name7[index]),\
name8(componentName::name8[index]),\
name9(componentName::name9[index]),\
name10(componentName::name10[index]),\
name11(componentName::name11[index]),\
name12(componentName::name12[index]),\
name13(componentName::name13[index]),\
name14(componentName::name14[index]),\
name15(componentName::name15[index]),\
name16(componentName::name16[index]),\
name17(componentName::name17[index]),\
name18(componentName::name18[index]),\
name19(componentName::name19[index]),\
name20(componentName::name20[index]),\
name21(componentName::name21[index]),\
name22(componentName::name22[index]),\
name23(componentName::name23[index]),\
name24(componentName::name24[index]),\
name25(componentName::name25[index]),\
name26(componentName::name26[index]),\
name27(componentName::name27[index]),\
id(index) {}\
type1& name1;\
type2& name2;\
type3& name3;\
type4& name4;\
type5& name5;\
type6& name6;\
type7& name7;\
type8& name8;\
type9& name9;\
type10& name10;\
type11& name11;\
type12& name12;\
type13& name13;\
type14& name14;\
type15& name15;\
type16& name16;\
type17& name17;\
type18& name18;\
type19& name19;\
type20& name20;\
type21& name21;\
type22& name22;\
type23& name23;\
type24& name24;\
type25& name25;\
type26& name26;\
type27& name27;\
const size_t id;\
};\
\
static size_t Create() {\
if(free.empty()) {\
size_t newSize = name1.size() + 1;\
size_t index = name1.size();\
name1.resize(newSize);\
name2.resize(newSize);\
name3.resize(newSize);\
name4.resize(newSize);\
name5.resize(newSize);\
name6.resize(newSize);\
name7.resize(newSize);\
name8.resize(newSize);\
name9.resize(newSize);\
name10.resize(newSize);\
name11.resize(newSize);\
name12.resize(newSize);\
name13.resize(newSize);\
name14.resize(newSize);\
name15.resize(newSize);\
name16.resize(newSize);\
name17.resize(newSize);\
name18.resize(newSize);\
name19.resize(newSize);\
name20.resize(newSize);\
name21.resize(newSize);\
name22.resize(newSize);\
name23.resize(newSize);\
name24.resize(newSize);\
name25.resize(newSize);\
name26.resize(newSize);\
name27.resize(newSize);\
return index;\
}\
else {\
size_t index = free.front();\
free.pop();\
return index;\
}\
}\
\
static size_t Copy(const size_t & source) {\
 if(free.empty()) {\
size_t newSize = name1.size() + 1;\
size_t index = name1.size();\
name1.resize(newSize);\
name2.resize(newSize);\
name3.resize(newSize);\
name4.resize(newSize);\
name5.resize(newSize);\
name6.resize(newSize);\
name7.resize(newSize);\
name8.resize(newSize);\
name9.resize(newSize);\
name10.resize(newSize);\
name11.resize(newSize);\
name12.resize(newSize);\
name13.resize(newSize);\
name14.resize(newSize);\
name15.resize(newSize);\
name16.resize(newSize);\
name17.resize(newSize);\
name18.resize(newSize);\
name19.resize(newSize);\
name20.resize(newSize);\
name21.resize(newSize);\
name22.resize(newSize);\
name23.resize(newSize);\
name24.resize(newSize);\
name25.resize(newSize);\
name26.resize(newSize);\
name27.resize(newSize);\
name1[index] = name1[source];\
name2[index] = name2[source];\
name3[index] = name3[source];\
name4[index] = name4[source];\
name5[index] = name5[source];\
name6[index] = name6[source];\
name7[index] = name7[source];\
name8[index] = name8[source];\
name9[index] = name9[source];\
name10[index] = name10[source];\
name11[index] = name11[source];\
name12[index] = name12[source];\
name13[index] = name13[source];\
name14[index] = name14[source];\
name15[index] = name15[source];\
name16[index] = name16[source];\
name17[index] = name17[source];\
name18[index] = name18[source];\
name19[index] = name19[source];\
name20[index] = name20[source];\
name21[index] = name21[source];\
name22[index] = name22[source];\
name23[index] = name23[source];\
name24[index] = name24[source];\
name25[index] = name25[source];\
name26[index] = name26[source];\
name27[index] = name27[source];\
return index;\
}\
else {\
size_t index = free.front();\
free.pop();\
name1[index] = name1[source];\
name2[index] = name2[source];\
name3[index] = name3[source];\
name4[index] = name4[source];\
name5[index] = name5[source];\
name6[index] = name6[source];\
name7[index] = name7[source];\
name8[index] = name8[source];\
name9[index] = name9[source];\
name10[index] = name10[source];\
name11[index] = name11[source];\
name12[index] = name12[source];\
name13[index] = name13[source];\
name14[index] = name14[source];\
name15[index] = name15[source];\
name16[index] = name16[source];\
name17[index] = name17[source];\
name18[index] = name18[source];\
name19[index] = name19[source];\
name20[index] = name20[source];\
name21[index] = name21[source];\
name22[index] = name22[source];\
name23[index] = name23[source];\
name24[index] = name24[source];\
name25[index] = name25[source];\
name26[index] = name26[source];\
name27[index] = name27[source];\
return index;\
}\
}\
\
static void Delete(size_t index) {\
if(index==0)return;\
free.push(index);\
}\
\
static std::queue<size_t> free;\
static std::vector<type1> name1;\
static std::vector<type2> name2;\
static std::vector<type3> name3;\
static std::vector<type4> name4;\
static std::vector<type5> name5;\
static std::vector<type6> name6;\
static std::vector<type7> name7;\
static std::vector<type8> name8;\
static std::vector<type9> name9;\
static std::vector<type10> name10;\
static std::vector<type11> name11;\
static std::vector<type12> name12;\
static std::vector<type13> name13;\
static std::vector<type14> name14;\
static std::vector<type15> name15;\
static std::vector<type16> name16;\
static std::vector<type17> name17;\
static std::vector<type18> name18;\
static std::vector<type19> name19;\
static std::vector<type20> name20;\
static std::vector<type21> name21;\
static std::vector<type22> name22;\
static std::vector<type23> name23;\
static std::vector<type24> name24;\
static std::vector<type25> name25;\
static std::vector<type26> name26;\
static std::vector<type27> name27;\
};\
}


#define INIT_ECSComponent_27\
(componentName,\
type1, name1,\
type2, name2,\
type3, name3,\
type4, name4,\
type5, name5,\
type6, name6,\
type7, name7,\
type8, name8,\
type9, name9,\
type10, name10,\
type11, name11,\
type12, name12,\
type13, name13,\
type14, name14,\
type15, name15,\
type16, name16,\
type17, name17,\
type18, name18,\
type19, name19,\
type20, name20,\
type21, name21,\
type22, name22,\
type23, name23,\
type24, name24,\
type25, name25,\
type26, name26,\
type27, name27)\
namespace ECS::Component {\
std::queue<size_t> componentName::free;\
std::vector<type1> componentName::name1(1);\
std::vector<type2> componentName::name2(1);\
std::vector<type3> componentName::name3(1);\
std::vector<type4> componentName::name4(1);\
std::vector<type5> componentName::name5(1);\
std::vector<type6> componentName::name6(1);\
std::vector<type7> componentName::name7(1);\
std::vector<type8> componentName::name8(1);\
std::vector<type9> componentName::name9(1);\
std::vector<type10> componentName::name10(1);\
std::vector<type11> componentName::name11(1);\
std::vector<type12> componentName::name12(1);\
std::vector<type13> componentName::name13(1);\
std::vector<type14> componentName::name14(1);\
std::vector<type15> componentName::name15(1);\
std::vector<type16> componentName::name16(1);\
std::vector<type17> componentName::name17(1);\
std::vector<type18> componentName::name18(1);\
std::vector<type19> componentName::name19(1);\
std::vector<type20> componentName::name20(1);\
std::vector<type21> componentName::name21(1);\
std::vector<type22> componentName::name22(1);\
std::vector<type23> componentName::name23(1);\
std::vector<type24> componentName::name24(1);\
std::vector<type25> componentName::name25(1);\
std::vector<type26> componentName::name26(1);\
std::vector<type27> componentName::name27(1);\
}







#define REGISTER_ECSComponent_28\
(componentName,\
type1, name1,\
type2, name2,\
type3, name3,\
type4, name4,\
type5, name5,\
type6, name6,\
type7, name7,\
type8, name8,\
type9, name9,\
type10, name10,\
type11, name11,\
type12, name12,\
type13, name13,\
type14, name14,\
type15, name15,\
type16, name16,\
type17, name17,\
type18, name18,\
type19, name19,\
type20, name20,\
type21, name21,\
type22, name22,\
type23, name23,\
type24, name24,\
type25, name25,\
type26, name26,\
type27, name27,\
type28, name28)\
namespace ECS::Component {\
struct componentName : ECSBase::ECSComponent<componentName> {\
\
struct Wrapper {\
Wrapper(size_t index)\
: name1(componentName::name1[index]),\
name2(componentName::name2[index]),\
name3(componentName::name3[index]),\
name4(componentName::name4[index]),\
name5(componentName::name5[index]),\
name6(componentName::name6[index]),\
name7(componentName::name7[index]),\
name8(componentName::name8[index]),\
name9(componentName::name9[index]),\
name10(componentName::name10[index]),\
name11(componentName::name11[index]),\
name12(componentName::name12[index]),\
name13(componentName::name13[index]),\
name14(componentName::name14[index]),\
name15(componentName::name15[index]),\
name16(componentName::name16[index]),\
name17(componentName::name17[index]),\
name18(componentName::name18[index]),\
name19(componentName::name19[index]),\
name20(componentName::name20[index]),\
name21(componentName::name21[index]),\
name22(componentName::name22[index]),\
name23(componentName::name23[index]),\
name24(componentName::name24[index]),\
name25(componentName::name25[index]),\
name26(componentName::name26[index]),\
name27(componentName::name27[index]),\
name28(componentName::name28[index]),\
id(index) {}\
type1& name1;\
type2& name2;\
type3& name3;\
type4& name4;\
type5& name5;\
type6& name6;\
type7& name7;\
type8& name8;\
type9& name9;\
type10& name10;\
type11& name11;\
type12& name12;\
type13& name13;\
type14& name14;\
type15& name15;\
type16& name16;\
type17& name17;\
type18& name18;\
type19& name19;\
type20& name20;\
type21& name21;\
type22& name22;\
type23& name23;\
type24& name24;\
type25& name25;\
type26& name26;\
type27& name27;\
type28& name28;\
const size_t id;\
};\
\
static size_t Create() {\
if(free.empty()) {\
size_t newSize = name1.size() + 1;\
size_t index = name1.size();\
name1.resize(newSize);\
name2.resize(newSize);\
name3.resize(newSize);\
name4.resize(newSize);\
name5.resize(newSize);\
name6.resize(newSize);\
name7.resize(newSize);\
name8.resize(newSize);\
name9.resize(newSize);\
name10.resize(newSize);\
name11.resize(newSize);\
name12.resize(newSize);\
name13.resize(newSize);\
name14.resize(newSize);\
name15.resize(newSize);\
name16.resize(newSize);\
name17.resize(newSize);\
name18.resize(newSize);\
name19.resize(newSize);\
name20.resize(newSize);\
name21.resize(newSize);\
name22.resize(newSize);\
name23.resize(newSize);\
name24.resize(newSize);\
name25.resize(newSize);\
name26.resize(newSize);\
name27.resize(newSize);\
name28.resize(newSize);\
return index;\
}\
else {\
size_t index = free.front();\
free.pop();\
return index;\
}\
}\
\
static size_t Copy(const size_t & source) {\
 if(free.empty()) {\
size_t newSize = name1.size() + 1;\
size_t index = name1.size();\
name1.resize(newSize);\
name2.resize(newSize);\
name3.resize(newSize);\
name4.resize(newSize);\
name5.resize(newSize);\
name6.resize(newSize);\
name7.resize(newSize);\
name8.resize(newSize);\
name9.resize(newSize);\
name10.resize(newSize);\
name11.resize(newSize);\
name12.resize(newSize);\
name13.resize(newSize);\
name14.resize(newSize);\
name15.resize(newSize);\
name16.resize(newSize);\
name17.resize(newSize);\
name18.resize(newSize);\
name19.resize(newSize);\
name20.resize(newSize);\
name21.resize(newSize);\
name22.resize(newSize);\
name23.resize(newSize);\
name24.resize(newSize);\
name25.resize(newSize);\
name26.resize(newSize);\
name27.resize(newSize);\
name28.resize(newSize);\
name1[index] = name1[source];\
name2[index] = name2[source];\
name3[index] = name3[source];\
name4[index] = name4[source];\
name5[index] = name5[source];\
name6[index] = name6[source];\
name7[index] = name7[source];\
name8[index] = name8[source];\
name9[index] = name9[source];\
name10[index] = name10[source];\
name11[index] = name11[source];\
name12[index] = name12[source];\
name13[index] = name13[source];\
name14[index] = name14[source];\
name15[index] = name15[source];\
name16[index] = name16[source];\
name17[index] = name17[source];\
name18[index] = name18[source];\
name19[index] = name19[source];\
name20[index] = name20[source];\
name21[index] = name21[source];\
name22[index] = name22[source];\
name23[index] = name23[source];\
name24[index] = name24[source];\
name25[index] = name25[source];\
name26[index] = name26[source];\
name27[index] = name27[source];\
name28[index] = name28[source];\
return index;\
}\
else {\
size_t index = free.front();\
free.pop();\
name1[index] = name1[source];\
name2[index] = name2[source];\
name3[index] = name3[source];\
name4[index] = name4[source];\
name5[index] = name5[source];\
name6[index] = name6[source];\
name7[index] = name7[source];\
name8[index] = name8[source];\
name9[index] = name9[source];\
name10[index] = name10[source];\
name11[index] = name11[source];\
name12[index] = name12[source];\
name13[index] = name13[source];\
name14[index] = name14[source];\
name15[index] = name15[source];\
name16[index] = name16[source];\
name17[index] = name17[source];\
name18[index] = name18[source];\
name19[index] = name19[source];\
name20[index] = name20[source];\
name21[index] = name21[source];\
name22[index] = name22[source];\
name23[index] = name23[source];\
name24[index] = name24[source];\
name25[index] = name25[source];\
name26[index] = name26[source];\
name27[index] = name27[source];\
name28[index] = name28[source];\
return index;\
}\
}\
\
static void Delete(size_t index) {\
if(index==0)return;\
free.push(index);\
}\
\
static std::queue<size_t> free;\
static std::vector<type1> name1;\
static std::vector<type2> name2;\
static std::vector<type3> name3;\
static std::vector<type4> name4;\
static std::vector<type5> name5;\
static std::vector<type6> name6;\
static std::vector<type7> name7;\
static std::vector<type8> name8;\
static std::vector<type9> name9;\
static std::vector<type10> name10;\
static std::vector<type11> name11;\
static std::vector<type12> name12;\
static std::vector<type13> name13;\
static std::vector<type14> name14;\
static std::vector<type15> name15;\
static std::vector<type16> name16;\
static std::vector<type17> name17;\
static std::vector<type18> name18;\
static std::vector<type19> name19;\
static std::vector<type20> name20;\
static std::vector<type21> name21;\
static std::vector<type22> name22;\
static std::vector<type23> name23;\
static std::vector<type24> name24;\
static std::vector<type25> name25;\
static std::vector<type26> name26;\
static std::vector<type27> name27;\
static std::vector<type28> name28;\
};\
}


#define INIT_ECSComponent_28\
(componentName,\
type1, name1,\
type2, name2,\
type3, name3,\
type4, name4,\
type5, name5,\
type6, name6,\
type7, name7,\
type8, name8,\
type9, name9,\
type10, name10,\
type11, name11,\
type12, name12,\
type13, name13,\
type14, name14,\
type15, name15,\
type16, name16,\
type17, name17,\
type18, name18,\
type19, name19,\
type20, name20,\
type21, name21,\
type22, name22,\
type23, name23,\
type24, name24,\
type25, name25,\
type26, name26,\
type27, name27,\
type28, name28)\
namespace ECS::Component {\
std::queue<size_t> componentName::free;\
std::vector<type1> componentName::name1(1);\
std::vector<type2> componentName::name2(1);\
std::vector<type3> componentName::name3(1);\
std::vector<type4> componentName::name4(1);\
std::vector<type5> componentName::name5(1);\
std::vector<type6> componentName::name6(1);\
std::vector<type7> componentName::name7(1);\
std::vector<type8> componentName::name8(1);\
std::vector<type9> componentName::name9(1);\
std::vector<type10> componentName::name10(1);\
std::vector<type11> componentName::name11(1);\
std::vector<type12> componentName::name12(1);\
std::vector<type13> componentName::name13(1);\
std::vector<type14> componentName::name14(1);\
std::vector<type15> componentName::name15(1);\
std::vector<type16> componentName::name16(1);\
std::vector<type17> componentName::name17(1);\
std::vector<type18> componentName::name18(1);\
std::vector<type19> componentName::name19(1);\
std::vector<type20> componentName::name20(1);\
std::vector<type21> componentName::name21(1);\
std::vector<type22> componentName::name22(1);\
std::vector<type23> componentName::name23(1);\
std::vector<type24> componentName::name24(1);\
std::vector<type25> componentName::name25(1);\
std::vector<type26> componentName::name26(1);\
std::vector<type27> componentName::name27(1);\
std::vector<type28> componentName::name28(1);\
}







#define REGISTER_ECSComponent_29\
(componentName,\
type1, name1,\
type2, name2,\
type3, name3,\
type4, name4,\
type5, name5,\
type6, name6,\
type7, name7,\
type8, name8,\
type9, name9,\
type10, name10,\
type11, name11,\
type12, name12,\
type13, name13,\
type14, name14,\
type15, name15,\
type16, name16,\
type17, name17,\
type18, name18,\
type19, name19,\
type20, name20,\
type21, name21,\
type22, name22,\
type23, name23,\
type24, name24,\
type25, name25,\
type26, name26,\
type27, name27,\
type28, name28,\
type29, name29)\
namespace ECS::Component {\
struct componentName : ECSBase::ECSComponent<componentName> {\
\
struct Wrapper {\
Wrapper(size_t index)\
: name1(componentName::name1[index]),\
name2(componentName::name2[index]),\
name3(componentName::name3[index]),\
name4(componentName::name4[index]),\
name5(componentName::name5[index]),\
name6(componentName::name6[index]),\
name7(componentName::name7[index]),\
name8(componentName::name8[index]),\
name9(componentName::name9[index]),\
name10(componentName::name10[index]),\
name11(componentName::name11[index]),\
name12(componentName::name12[index]),\
name13(componentName::name13[index]),\
name14(componentName::name14[index]),\
name15(componentName::name15[index]),\
name16(componentName::name16[index]),\
name17(componentName::name17[index]),\
name18(componentName::name18[index]),\
name19(componentName::name19[index]),\
name20(componentName::name20[index]),\
name21(componentName::name21[index]),\
name22(componentName::name22[index]),\
name23(componentName::name23[index]),\
name24(componentName::name24[index]),\
name25(componentName::name25[index]),\
name26(componentName::name26[index]),\
name27(componentName::name27[index]),\
name28(componentName::name28[index]),\
name29(componentName::name29[index]),\
id(index) {}\
type1& name1;\
type2& name2;\
type3& name3;\
type4& name4;\
type5& name5;\
type6& name6;\
type7& name7;\
type8& name8;\
type9& name9;\
type10& name10;\
type11& name11;\
type12& name12;\
type13& name13;\
type14& name14;\
type15& name15;\
type16& name16;\
type17& name17;\
type18& name18;\
type19& name19;\
type20& name20;\
type21& name21;\
type22& name22;\
type23& name23;\
type24& name24;\
type25& name25;\
type26& name26;\
type27& name27;\
type28& name28;\
type29& name29;\
const size_t id;\
};\
\
static size_t Create() {\
if(free.empty()) {\
size_t newSize = name1.size() + 1;\
size_t index = name1.size();\
name1.resize(newSize);\
name2.resize(newSize);\
name3.resize(newSize);\
name4.resize(newSize);\
name5.resize(newSize);\
name6.resize(newSize);\
name7.resize(newSize);\
name8.resize(newSize);\
name9.resize(newSize);\
name10.resize(newSize);\
name11.resize(newSize);\
name12.resize(newSize);\
name13.resize(newSize);\
name14.resize(newSize);\
name15.resize(newSize);\
name16.resize(newSize);\
name17.resize(newSize);\
name18.resize(newSize);\
name19.resize(newSize);\
name20.resize(newSize);\
name21.resize(newSize);\
name22.resize(newSize);\
name23.resize(newSize);\
name24.resize(newSize);\
name25.resize(newSize);\
name26.resize(newSize);\
name27.resize(newSize);\
name28.resize(newSize);\
name29.resize(newSize);\
return index;\
}\
else {\
size_t index = free.front();\
free.pop();\
return index;\
}\
}\
\
static size_t Copy(const size_t & source) {\
 if(free.empty()) {\
size_t newSize = name1.size() + 1;\
size_t index = name1.size();\
name1.resize(newSize);\
name2.resize(newSize);\
name3.resize(newSize);\
name4.resize(newSize);\
name5.resize(newSize);\
name6.resize(newSize);\
name7.resize(newSize);\
name8.resize(newSize);\
name9.resize(newSize);\
name10.resize(newSize);\
name11.resize(newSize);\
name12.resize(newSize);\
name13.resize(newSize);\
name14.resize(newSize);\
name15.resize(newSize);\
name16.resize(newSize);\
name17.resize(newSize);\
name18.resize(newSize);\
name19.resize(newSize);\
name20.resize(newSize);\
name21.resize(newSize);\
name22.resize(newSize);\
name23.resize(newSize);\
name24.resize(newSize);\
name25.resize(newSize);\
name26.resize(newSize);\
name27.resize(newSize);\
name28.resize(newSize);\
name29.resize(newSize);\
name1[index] = name1[source];\
name2[index] = name2[source];\
name3[index] = name3[source];\
name4[index] = name4[source];\
name5[index] = name5[source];\
name6[index] = name6[source];\
name7[index] = name7[source];\
name8[index] = name8[source];\
name9[index] = name9[source];\
name10[index] = name10[source];\
name11[index] = name11[source];\
name12[index] = name12[source];\
name13[index] = name13[source];\
name14[index] = name14[source];\
name15[index] = name15[source];\
name16[index] = name16[source];\
name17[index] = name17[source];\
name18[index] = name18[source];\
name19[index] = name19[source];\
name20[index] = name20[source];\
name21[index] = name21[source];\
name22[index] = name22[source];\
name23[index] = name23[source];\
name24[index] = name24[source];\
name25[index] = name25[source];\
name26[index] = name26[source];\
name27[index] = name27[source];\
name28[index] = name28[source];\
name29[index] = name29[source];\
return index;\
}\
else {\
size_t index = free.front();\
free.pop();\
name1[index] = name1[source];\
name2[index] = name2[source];\
name3[index] = name3[source];\
name4[index] = name4[source];\
name5[index] = name5[source];\
name6[index] = name6[source];\
name7[index] = name7[source];\
name8[index] = name8[source];\
name9[index] = name9[source];\
name10[index] = name10[source];\
name11[index] = name11[source];\
name12[index] = name12[source];\
name13[index] = name13[source];\
name14[index] = name14[source];\
name15[index] = name15[source];\
name16[index] = name16[source];\
name17[index] = name17[source];\
name18[index] = name18[source];\
name19[index] = name19[source];\
name20[index] = name20[source];\
name21[index] = name21[source];\
name22[index] = name22[source];\
name23[index] = name23[source];\
name24[index] = name24[source];\
name25[index] = name25[source];\
name26[index] = name26[source];\
name27[index] = name27[source];\
name28[index] = name28[source];\
name29[index] = name29[source];\
return index;\
}\
}\
\
static void Delete(size_t index) {\
if(index==0)return;\
free.push(index);\
}\
\
static std::queue<size_t> free;\
static std::vector<type1> name1;\
static std::vector<type2> name2;\
static std::vector<type3> name3;\
static std::vector<type4> name4;\
static std::vector<type5> name5;\
static std::vector<type6> name6;\
static std::vector<type7> name7;\
static std::vector<type8> name8;\
static std::vector<type9> name9;\
static std::vector<type10> name10;\
static std::vector<type11> name11;\
static std::vector<type12> name12;\
static std::vector<type13> name13;\
static std::vector<type14> name14;\
static std::vector<type15> name15;\
static std::vector<type16> name16;\
static std::vector<type17> name17;\
static std::vector<type18> name18;\
static std::vector<type19> name19;\
static std::vector<type20> name20;\
static std::vector<type21> name21;\
static std::vector<type22> name22;\
static std::vector<type23> name23;\
static std::vector<type24> name24;\
static std::vector<type25> name25;\
static std::vector<type26> name26;\
static std::vector<type27> name27;\
static std::vector<type28> name28;\
static std::vector<type29> name29;\
};\
}


#define INIT_ECSComponent_29\
(componentName,\
type1, name1,\
type2, name2,\
type3, name3,\
type4, name4,\
type5, name5,\
type6, name6,\
type7, name7,\
type8, name8,\
type9, name9,\
type10, name10,\
type11, name11,\
type12, name12,\
type13, name13,\
type14, name14,\
type15, name15,\
type16, name16,\
type17, name17,\
type18, name18,\
type19, name19,\
type20, name20,\
type21, name21,\
type22, name22,\
type23, name23,\
type24, name24,\
type25, name25,\
type26, name26,\
type27, name27,\
type28, name28,\
type29, name29)\
namespace ECS::Component {\
std::queue<size_t> componentName::free;\
std::vector<type1> componentName::name1(1);\
std::vector<type2> componentName::name2(1);\
std::vector<type3> componentName::name3(1);\
std::vector<type4> componentName::name4(1);\
std::vector<type5> componentName::name5(1);\
std::vector<type6> componentName::name6(1);\
std::vector<type7> componentName::name7(1);\
std::vector<type8> componentName::name8(1);\
std::vector<type9> componentName::name9(1);\
std::vector<type10> componentName::name10(1);\
std::vector<type11> componentName::name11(1);\
std::vector<type12> componentName::name12(1);\
std::vector<type13> componentName::name13(1);\
std::vector<type14> componentName::name14(1);\
std::vector<type15> componentName::name15(1);\
std::vector<type16> componentName::name16(1);\
std::vector<type17> componentName::name17(1);\
std::vector<type18> componentName::name18(1);\
std::vector<type19> componentName::name19(1);\
std::vector<type20> componentName::name20(1);\
std::vector<type21> componentName::name21(1);\
std::vector<type22> componentName::name22(1);\
std::vector<type23> componentName::name23(1);\
std::vector<type24> componentName::name24(1);\
std::vector<type25> componentName::name25(1);\
std::vector<type26> componentName::name26(1);\
std::vector<type27> componentName::name27(1);\
std::vector<type28> componentName::name28(1);\
std::vector<type29> componentName::name29(1);\
}







#define REGISTER_ECSComponent_30\
(componentName,\
type1, name1,\
type2, name2,\
type3, name3,\
type4, name4,\
type5, name5,\
type6, name6,\
type7, name7,\
type8, name8,\
type9, name9,\
type10, name10,\
type11, name11,\
type12, name12,\
type13, name13,\
type14, name14,\
type15, name15,\
type16, name16,\
type17, name17,\
type18, name18,\
type19, name19,\
type20, name20,\
type21, name21,\
type22, name22,\
type23, name23,\
type24, name24,\
type25, name25,\
type26, name26,\
type27, name27,\
type28, name28,\
type29, name29,\
type30, name30)\
namespace ECS::Component {\
struct componentName : ECSBase::ECSComponent<componentName> {\
\
struct Wrapper {\
Wrapper(size_t index)\
: name1(componentName::name1[index]),\
name2(componentName::name2[index]),\
name3(componentName::name3[index]),\
name4(componentName::name4[index]),\
name5(componentName::name5[index]),\
name6(componentName::name6[index]),\
name7(componentName::name7[index]),\
name8(componentName::name8[index]),\
name9(componentName::name9[index]),\
name10(componentName::name10[index]),\
name11(componentName::name11[index]),\
name12(componentName::name12[index]),\
name13(componentName::name13[index]),\
name14(componentName::name14[index]),\
name15(componentName::name15[index]),\
name16(componentName::name16[index]),\
name17(componentName::name17[index]),\
name18(componentName::name18[index]),\
name19(componentName::name19[index]),\
name20(componentName::name20[index]),\
name21(componentName::name21[index]),\
name22(componentName::name22[index]),\
name23(componentName::name23[index]),\
name24(componentName::name24[index]),\
name25(componentName::name25[index]),\
name26(componentName::name26[index]),\
name27(componentName::name27[index]),\
name28(componentName::name28[index]),\
name29(componentName::name29[index]),\
name30(componentName::name30[index]),\
id(index) {}\
type1& name1;\
type2& name2;\
type3& name3;\
type4& name4;\
type5& name5;\
type6& name6;\
type7& name7;\
type8& name8;\
type9& name9;\
type10& name10;\
type11& name11;\
type12& name12;\
type13& name13;\
type14& name14;\
type15& name15;\
type16& name16;\
type17& name17;\
type18& name18;\
type19& name19;\
type20& name20;\
type21& name21;\
type22& name22;\
type23& name23;\
type24& name24;\
type25& name25;\
type26& name26;\
type27& name27;\
type28& name28;\
type29& name29;\
type30& name30;\
const size_t id;\
};\
\
static size_t Create() {\
if(free.empty()) {\
size_t newSize = name1.size() + 1;\
size_t index = name1.size();\
name1.resize(newSize);\
name2.resize(newSize);\
name3.resize(newSize);\
name4.resize(newSize);\
name5.resize(newSize);\
name6.resize(newSize);\
name7.resize(newSize);\
name8.resize(newSize);\
name9.resize(newSize);\
name10.resize(newSize);\
name11.resize(newSize);\
name12.resize(newSize);\
name13.resize(newSize);\
name14.resize(newSize);\
name15.resize(newSize);\
name16.resize(newSize);\
name17.resize(newSize);\
name18.resize(newSize);\
name19.resize(newSize);\
name20.resize(newSize);\
name21.resize(newSize);\
name22.resize(newSize);\
name23.resize(newSize);\
name24.resize(newSize);\
name25.resize(newSize);\
name26.resize(newSize);\
name27.resize(newSize);\
name28.resize(newSize);\
name29.resize(newSize);\
name30.resize(newSize);\
return index;\
}\
else {\
size_t index = free.front();\
free.pop();\
return index;\
}\
}\
\
static size_t Copy(const size_t & source) {\
 if(free.empty()) {\
size_t newSize = name1.size() + 1;\
size_t index = name1.size();\
name1.resize(newSize);\
name2.resize(newSize);\
name3.resize(newSize);\
name4.resize(newSize);\
name5.resize(newSize);\
name6.resize(newSize);\
name7.resize(newSize);\
name8.resize(newSize);\
name9.resize(newSize);\
name10.resize(newSize);\
name11.resize(newSize);\
name12.resize(newSize);\
name13.resize(newSize);\
name14.resize(newSize);\
name15.resize(newSize);\
name16.resize(newSize);\
name17.resize(newSize);\
name18.resize(newSize);\
name19.resize(newSize);\
name20.resize(newSize);\
name21.resize(newSize);\
name22.resize(newSize);\
name23.resize(newSize);\
name24.resize(newSize);\
name25.resize(newSize);\
name26.resize(newSize);\
name27.resize(newSize);\
name28.resize(newSize);\
name29.resize(newSize);\
name30.resize(newSize);\
name1[index] = name1[source];\
name2[index] = name2[source];\
name3[index] = name3[source];\
name4[index] = name4[source];\
name5[index] = name5[source];\
name6[index] = name6[source];\
name7[index] = name7[source];\
name8[index] = name8[source];\
name9[index] = name9[source];\
name10[index] = name10[source];\
name11[index] = name11[source];\
name12[index] = name12[source];\
name13[index] = name13[source];\
name14[index] = name14[source];\
name15[index] = name15[source];\
name16[index] = name16[source];\
name17[index] = name17[source];\
name18[index] = name18[source];\
name19[index] = name19[source];\
name20[index] = name20[source];\
name21[index] = name21[source];\
name22[index] = name22[source];\
name23[index] = name23[source];\
name24[index] = name24[source];\
name25[index] = name25[source];\
name26[index] = name26[source];\
name27[index] = name27[source];\
name28[index] = name28[source];\
name29[index] = name29[source];\
name30[index] = name30[source];\
return index;\
}\
else {\
size_t index = free.front();\
free.pop();\
name1[index] = name1[source];\
name2[index] = name2[source];\
name3[index] = name3[source];\
name4[index] = name4[source];\
name5[index] = name5[source];\
name6[index] = name6[source];\
name7[index] = name7[source];\
name8[index] = name8[source];\
name9[index] = name9[source];\
name10[index] = name10[source];\
name11[index] = name11[source];\
name12[index] = name12[source];\
name13[index] = name13[source];\
name14[index] = name14[source];\
name15[index] = name15[source];\
name16[index] = name16[source];\
name17[index] = name17[source];\
name18[index] = name18[source];\
name19[index] = name19[source];\
name20[index] = name20[source];\
name21[index] = name21[source];\
name22[index] = name22[source];\
name23[index] = name23[source];\
name24[index] = name24[source];\
name25[index] = name25[source];\
name26[index] = name26[source];\
name27[index] = name27[source];\
name28[index] = name28[source];\
name29[index] = name29[source];\
name30[index] = name30[source];\
return index;\
}\
}\
\
static void Delete(size_t index) {\
if(index==0)return;\
free.push(index);\
}\
\
static std::queue<size_t> free;\
static std::vector<type1> name1;\
static std::vector<type2> name2;\
static std::vector<type3> name3;\
static std::vector<type4> name4;\
static std::vector<type5> name5;\
static std::vector<type6> name6;\
static std::vector<type7> name7;\
static std::vector<type8> name8;\
static std::vector<type9> name9;\
static std::vector<type10> name10;\
static std::vector<type11> name11;\
static std::vector<type12> name12;\
static std::vector<type13> name13;\
static std::vector<type14> name14;\
static std::vector<type15> name15;\
static std::vector<type16> name16;\
static std::vector<type17> name17;\
static std::vector<type18> name18;\
static std::vector<type19> name19;\
static std::vector<type20> name20;\
static std::vector<type21> name21;\
static std::vector<type22> name22;\
static std::vector<type23> name23;\
static std::vector<type24> name24;\
static std::vector<type25> name25;\
static std::vector<type26> name26;\
static std::vector<type27> name27;\
static std::vector<type28> name28;\
static std::vector<type29> name29;\
static std::vector<type30> name30;\
};\
}


#define INIT_ECSComponent_30\
(componentName,\
type1, name1,\
type2, name2,\
type3, name3,\
type4, name4,\
type5, name5,\
type6, name6,\
type7, name7,\
type8, name8,\
type9, name9,\
type10, name10,\
type11, name11,\
type12, name12,\
type13, name13,\
type14, name14,\
type15, name15,\
type16, name16,\
type17, name17,\
type18, name18,\
type19, name19,\
type20, name20,\
type21, name21,\
type22, name22,\
type23, name23,\
type24, name24,\
type25, name25,\
type26, name26,\
type27, name27,\
type28, name28,\
type29, name29,\
type30, name30)\
namespace ECS::Component {\
std::queue<size_t> componentName::free;\
std::vector<type1> componentName::name1(1);\
std::vector<type2> componentName::name2(1);\
std::vector<type3> componentName::name3(1);\
std::vector<type4> componentName::name4(1);\
std::vector<type5> componentName::name5(1);\
std::vector<type6> componentName::name6(1);\
std::vector<type7> componentName::name7(1);\
std::vector<type8> componentName::name8(1);\
std::vector<type9> componentName::name9(1);\
std::vector<type10> componentName::name10(1);\
std::vector<type11> componentName::name11(1);\
std::vector<type12> componentName::name12(1);\
std::vector<type13> componentName::name13(1);\
std::vector<type14> componentName::name14(1);\
std::vector<type15> componentName::name15(1);\
std::vector<type16> componentName::name16(1);\
std::vector<type17> componentName::name17(1);\
std::vector<type18> componentName::name18(1);\
std::vector<type19> componentName::name19(1);\
std::vector<type20> componentName::name20(1);\
std::vector<type21> componentName::name21(1);\
std::vector<type22> componentName::name22(1);\
std::vector<type23> componentName::name23(1);\
std::vector<type24> componentName::name24(1);\
std::vector<type25> componentName::name25(1);\
std::vector<type26> componentName::name26(1);\
std::vector<type27> componentName::name27(1);\
std::vector<type28> componentName::name28(1);\
std::vector<type29> componentName::name29(1);\
std::vector<type30> componentName::name30(1);\
}


}