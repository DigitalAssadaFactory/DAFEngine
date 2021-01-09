#pragma once
#include <vector>

/*   MACRO FACTORY FUNCTION IF MORE VARIANTS ARE NEEDED
static void MakeDynamicArrayMacro(std::string fileName, size_t numMacros)
{
	std::ofstream out(fileName);

	for (int i = 1; i < numMacros; ++i)
	{
		static std::string dim;
		static std::string array;
		static std::string init;
		static const std::string pre = "std::vector<";
		static const std::string post = ">";

		if (i < 10) dim = "0" + std::to_string(i);
		else dim = std::to_string(i);


		array = "#define DYNAMIC_ARRAY_" + dim + "(type) ";
		for (int j = 0; j < i; ++j)
			array += pre;

		array += "type";

		for (int j = 0; j < i; ++j)
			array += post;


		init = "#define DYNAMIC_ARRAY_" + dim + "_INIT(type";
		for (int j = 0; j < i; ++j)
			init += ", d" + std::to_string(j);
		init += ") DYNAMIC_ARRAY_" + dim + "(type)";
		int k = 0;
		for (; k < i - 2; ++k)
			init += "(d" + std::to_string(k) + ", std::vector";

		init += "(d" + std::to_string(k) + ", std::vector<type>(d" + std::to_string(k + 1);

		for (int j = 0; j < i; ++j)
			init += ")";

		out << array + "\n";
		out << init + "\n";
		out << "\n";
	}

	out.close();
}
*/


#define DYNAMIC_ARRAY_02(type) std::vector<std::vector<type>>
#define DYNAMIC_ARRAY_02_INIT(type, d0, d1) DYNAMIC_ARRAY_02(type)(d0, std::vector<type>(d1))

#define DYNAMIC_ARRAY_03(type) std::vector<std::vector<std::vector<type>>>
#define DYNAMIC_ARRAY_03_INIT(type, d0, d1, d2) DYNAMIC_ARRAY_03(type)(d0, std::vector(d1, std::vector<type>(d2)))

#define DYNAMIC_ARRAY_04(type) std::vector<std::vector<std::vector<std::vector<type>>>>
#define DYNAMIC_ARRAY_04_INIT(type, d0, d1, d2, d3) DYNAMIC_ARRAY_04(type)(d0, std::vector(d1, std::vector(d2, std::vector<type>(d3))))

#define DYNAMIC_ARRAY_05(type) std::vector<std::vector<std::vector<std::vector<std::vector<type>>>>>
#define DYNAMIC_ARRAY_05_INIT(type, d0, d1, d2, d3, d4) DYNAMIC_ARRAY_05(type)(d0, std::vector(d1, std::vector(d2, std::vector(d3, std::vector<type>(d4)))))

#define DYNAMIC_ARRAY_06(type) std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<type>>>>>>
#define DYNAMIC_ARRAY_06_INIT(type, d0, d1, d2, d3, d4, d5) DYNAMIC_ARRAY_06(type)(d0, std::vector(d1, std::vector(d2, std::vector(d3, std::vector(d4, std::vector<type>(d5))))))

#define DYNAMIC_ARRAY_07(type) std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<type>>>>>>>
#define DYNAMIC_ARRAY_07_INIT(type, d0, d1, d2, d3, d4, d5, d6) DYNAMIC_ARRAY_07(type)(d0, std::vector(d1, std::vector(d2, std::vector(d3, std::vector(d4, std::vector(d5, std::vector<type>(d6)))))))

#define DYNAMIC_ARRAY_08(type) std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<type>>>>>>>>
#define DYNAMIC_ARRAY_08_INIT(type, d0, d1, d2, d3, d4, d5, d6, d7) DYNAMIC_ARRAY_08(type)(d0, std::vector(d1, std::vector(d2, std::vector(d3, std::vector(d4, std::vector(d5, std::vector(d6, std::vector<type>(d7))))))))

#define DYNAMIC_ARRAY_09(type) std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<type>>>>>>>>>
#define DYNAMIC_ARRAY_09_INIT(type, d0, d1, d2, d3, d4, d5, d6, d7, d8) DYNAMIC_ARRAY_09(type)(d0, std::vector(d1, std::vector(d2, std::vector(d3, std::vector(d4, std::vector(d5, std::vector(d6, std::vector(d7, std::vector<type>(d8)))))))))

#define DYNAMIC_ARRAY_10(type) std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<type>>>>>>>>>>
#define DYNAMIC_ARRAY_10_INIT(type, d0, d1, d2, d3, d4, d5, d6, d7, d8, d9) DYNAMIC_ARRAY_10(type)(d0, std::vector(d1, std::vector(d2, std::vector(d3, std::vector(d4, std::vector(d5, std::vector(d6, std::vector(d7, std::vector(d8, std::vector<type>(d9))))))))))

#define DYNAMIC_ARRAY_11(type) std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<type>>>>>>>>>>>
#define DYNAMIC_ARRAY_11_INIT(type, d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10) DYNAMIC_ARRAY_11(type)(d0, std::vector(d1, std::vector(d2, std::vector(d3, std::vector(d4, std::vector(d5, std::vector(d6, std::vector(d7, std::vector(d8, std::vector(d9, std::vector<type>(d10)))))))))))

#define DYNAMIC_ARRAY_12(type) std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<type>>>>>>>>>>>>
#define DYNAMIC_ARRAY_12_INIT(type, d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11) DYNAMIC_ARRAY_12(type)(d0, std::vector(d1, std::vector(d2, std::vector(d3, std::vector(d4, std::vector(d5, std::vector(d6, std::vector(d7, std::vector(d8, std::vector(d9, std::vector(d10, std::vector<type>(d11))))))))))))

#define DYNAMIC_ARRAY_13(type) std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<type>>>>>>>>>>>>>
#define DYNAMIC_ARRAY_13_INIT(type, d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12) DYNAMIC_ARRAY_13(type)(d0, std::vector(d1, std::vector(d2, std::vector(d3, std::vector(d4, std::vector(d5, std::vector(d6, std::vector(d7, std::vector(d8, std::vector(d9, std::vector(d10, std::vector(d11, std::vector<type>(d12)))))))))))))

#define DYNAMIC_ARRAY_14(type) std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<type>>>>>>>>>>>>>>
#define DYNAMIC_ARRAY_14_INIT(type, d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13) DYNAMIC_ARRAY_14(type)(d0, std::vector(d1, std::vector(d2, std::vector(d3, std::vector(d4, std::vector(d5, std::vector(d6, std::vector(d7, std::vector(d8, std::vector(d9, std::vector(d10, std::vector(d11, std::vector(d12, std::vector<type>(d13))))))))))))))

#define DYNAMIC_ARRAY_15(type) std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<type>>>>>>>>>>>>>>>
#define DYNAMIC_ARRAY_15_INIT(type, d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14) DYNAMIC_ARRAY_15(type)(d0, std::vector(d1, std::vector(d2, std::vector(d3, std::vector(d4, std::vector(d5, std::vector(d6, std::vector(d7, std::vector(d8, std::vector(d9, std::vector(d10, std::vector(d11, std::vector(d12, std::vector(d13, std::vector<type>(d14)))))))))))))))

#define DYNAMIC_ARRAY_16(type) std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<type>>>>>>>>>>>>>>>>
#define DYNAMIC_ARRAY_16_INIT(type, d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15) DYNAMIC_ARRAY_16(type)(d0, std::vector(d1, std::vector(d2, std::vector(d3, std::vector(d4, std::vector(d5, std::vector(d6, std::vector(d7, std::vector(d8, std::vector(d9, std::vector(d10, std::vector(d11, std::vector(d12, std::vector(d13, std::vector(d14, std::vector<type>(d15))))))))))))))))

#define DYNAMIC_ARRAY_17(type) std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<type>>>>>>>>>>>>>>>>>
#define DYNAMIC_ARRAY_17_INIT(type, d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16) DYNAMIC_ARRAY_17(type)(d0, std::vector(d1, std::vector(d2, std::vector(d3, std::vector(d4, std::vector(d5, std::vector(d6, std::vector(d7, std::vector(d8, std::vector(d9, std::vector(d10, std::vector(d11, std::vector(d12, std::vector(d13, std::vector(d14, std::vector(d15, std::vector<type>(d16)))))))))))))))))

#define DYNAMIC_ARRAY_18(type) std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<type>>>>>>>>>>>>>>>>>>
#define DYNAMIC_ARRAY_18_INIT(type, d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17) DYNAMIC_ARRAY_18(type)(d0, std::vector(d1, std::vector(d2, std::vector(d3, std::vector(d4, std::vector(d5, std::vector(d6, std::vector(d7, std::vector(d8, std::vector(d9, std::vector(d10, std::vector(d11, std::vector(d12, std::vector(d13, std::vector(d14, std::vector(d15, std::vector(d16, std::vector<type>(d17))))))))))))))))))

#define DYNAMIC_ARRAY_19(type) std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<type>>>>>>>>>>>>>>>>>>>
#define DYNAMIC_ARRAY_19_INIT(type, d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18) DYNAMIC_ARRAY_19(type)(d0, std::vector(d1, std::vector(d2, std::vector(d3, std::vector(d4, std::vector(d5, std::vector(d6, std::vector(d7, std::vector(d8, std::vector(d9, std::vector(d10, std::vector(d11, std::vector(d12, std::vector(d13, std::vector(d14, std::vector(d15, std::vector(d16, std::vector(d17, std::vector<type>(d18)))))))))))))))))))

#define DYNAMIC_ARRAY_20(type) std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<type>>>>>>>>>>>>>>>>>>>>
#define DYNAMIC_ARRAY_20_INIT(type, d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19) DYNAMIC_ARRAY_20(type)(d0, std::vector(d1, std::vector(d2, std::vector(d3, std::vector(d4, std::vector(d5, std::vector(d6, std::vector(d7, std::vector(d8, std::vector(d9, std::vector(d10, std::vector(d11, std::vector(d12, std::vector(d13, std::vector(d14, std::vector(d15, std::vector(d16, std::vector(d17, std::vector(d18, std::vector<type>(d19))))))))))))))))))))

#define DYNAMIC_ARRAY_21(type) std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<type>>>>>>>>>>>>>>>>>>>>>
#define DYNAMIC_ARRAY_21_INIT(type, d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20) DYNAMIC_ARRAY_21(type)(d0, std::vector(d1, std::vector(d2, std::vector(d3, std::vector(d4, std::vector(d5, std::vector(d6, std::vector(d7, std::vector(d8, std::vector(d9, std::vector(d10, std::vector(d11, std::vector(d12, std::vector(d13, std::vector(d14, std::vector(d15, std::vector(d16, std::vector(d17, std::vector(d18, std::vector(d19, std::vector<type>(d20)))))))))))))))))))))

#define DYNAMIC_ARRAY_22(type) std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<type>>>>>>>>>>>>>>>>>>>>>>
#define DYNAMIC_ARRAY_22_INIT(type, d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21) DYNAMIC_ARRAY_22(type)(d0, std::vector(d1, std::vector(d2, std::vector(d3, std::vector(d4, std::vector(d5, std::vector(d6, std::vector(d7, std::vector(d8, std::vector(d9, std::vector(d10, std::vector(d11, std::vector(d12, std::vector(d13, std::vector(d14, std::vector(d15, std::vector(d16, std::vector(d17, std::vector(d18, std::vector(d19, std::vector(d20, std::vector<type>(d21))))))))))))))))))))))

#define DYNAMIC_ARRAY_23(type) std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<type>>>>>>>>>>>>>>>>>>>>>>>
#define DYNAMIC_ARRAY_23_INIT(type, d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22) DYNAMIC_ARRAY_23(type)(d0, std::vector(d1, std::vector(d2, std::vector(d3, std::vector(d4, std::vector(d5, std::vector(d6, std::vector(d7, std::vector(d8, std::vector(d9, std::vector(d10, std::vector(d11, std::vector(d12, std::vector(d13, std::vector(d14, std::vector(d15, std::vector(d16, std::vector(d17, std::vector(d18, std::vector(d19, std::vector(d20, std::vector(d21, std::vector<type>(d22)))))))))))))))))))))))

#define DYNAMIC_ARRAY_24(type) std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<type>>>>>>>>>>>>>>>>>>>>>>>>
#define DYNAMIC_ARRAY_24_INIT(type, d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23) DYNAMIC_ARRAY_24(type)(d0, std::vector(d1, std::vector(d2, std::vector(d3, std::vector(d4, std::vector(d5, std::vector(d6, std::vector(d7, std::vector(d8, std::vector(d9, std::vector(d10, std::vector(d11, std::vector(d12, std::vector(d13, std::vector(d14, std::vector(d15, std::vector(d16, std::vector(d17, std::vector(d18, std::vector(d19, std::vector(d20, std::vector(d21, std::vector(d22, std::vector<type>(d23))))))))))))))))))))))))

#define DYNAMIC_ARRAY_25(type) std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<type>>>>>>>>>>>>>>>>>>>>>>>>>
#define DYNAMIC_ARRAY_25_INIT(type, d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24) DYNAMIC_ARRAY_25(type)(d0, std::vector(d1, std::vector(d2, std::vector(d3, std::vector(d4, std::vector(d5, std::vector(d6, std::vector(d7, std::vector(d8, std::vector(d9, std::vector(d10, std::vector(d11, std::vector(d12, std::vector(d13, std::vector(d14, std::vector(d15, std::vector(d16, std::vector(d17, std::vector(d18, std::vector(d19, std::vector(d20, std::vector(d21, std::vector(d22, std::vector(d23, std::vector<type>(d24)))))))))))))))))))))))))

#define DYNAMIC_ARRAY_26(type) std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<type>>>>>>>>>>>>>>>>>>>>>>>>>>
#define DYNAMIC_ARRAY_26_INIT(type, d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25) DYNAMIC_ARRAY_26(type)(d0, std::vector(d1, std::vector(d2, std::vector(d3, std::vector(d4, std::vector(d5, std::vector(d6, std::vector(d7, std::vector(d8, std::vector(d9, std::vector(d10, std::vector(d11, std::vector(d12, std::vector(d13, std::vector(d14, std::vector(d15, std::vector(d16, std::vector(d17, std::vector(d18, std::vector(d19, std::vector(d20, std::vector(d21, std::vector(d22, std::vector(d23, std::vector(d24, std::vector<type>(d25))))))))))))))))))))))))))

#define DYNAMIC_ARRAY_27(type) std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<type>>>>>>>>>>>>>>>>>>>>>>>>>>>
#define DYNAMIC_ARRAY_27_INIT(type, d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26) DYNAMIC_ARRAY_27(type)(d0, std::vector(d1, std::vector(d2, std::vector(d3, std::vector(d4, std::vector(d5, std::vector(d6, std::vector(d7, std::vector(d8, std::vector(d9, std::vector(d10, std::vector(d11, std::vector(d12, std::vector(d13, std::vector(d14, std::vector(d15, std::vector(d16, std::vector(d17, std::vector(d18, std::vector(d19, std::vector(d20, std::vector(d21, std::vector(d22, std::vector(d23, std::vector(d24, std::vector(d25, std::vector<type>(d26)))))))))))))))))))))))))))

#define DYNAMIC_ARRAY_28(type) std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<type>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#define DYNAMIC_ARRAY_28_INIT(type, d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27) DYNAMIC_ARRAY_28(type)(d0, std::vector(d1, std::vector(d2, std::vector(d3, std::vector(d4, std::vector(d5, std::vector(d6, std::vector(d7, std::vector(d8, std::vector(d9, std::vector(d10, std::vector(d11, std::vector(d12, std::vector(d13, std::vector(d14, std::vector(d15, std::vector(d16, std::vector(d17, std::vector(d18, std::vector(d19, std::vector(d20, std::vector(d21, std::vector(d22, std::vector(d23, std::vector(d24, std::vector(d25, std::vector(d26, std::vector<type>(d27))))))))))))))))))))))))))))

#define DYNAMIC_ARRAY_29(type) std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<type>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#define DYNAMIC_ARRAY_29_INIT(type, d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28) DYNAMIC_ARRAY_29(type)(d0, std::vector(d1, std::vector(d2, std::vector(d3, std::vector(d4, std::vector(d5, std::vector(d6, std::vector(d7, std::vector(d8, std::vector(d9, std::vector(d10, std::vector(d11, std::vector(d12, std::vector(d13, std::vector(d14, std::vector(d15, std::vector(d16, std::vector(d17, std::vector(d18, std::vector(d19, std::vector(d20, std::vector(d21, std::vector(d22, std::vector(d23, std::vector(d24, std::vector(d25, std::vector(d26, std::vector(d27, std::vector<type>(d28)))))))))))))))))))))))))))))

#define DYNAMIC_ARRAY_30(type) std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<type>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#define DYNAMIC_ARRAY_30_INIT(type, d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29) DYNAMIC_ARRAY_30(type)(d0, std::vector(d1, std::vector(d2, std::vector(d3, std::vector(d4, std::vector(d5, std::vector(d6, std::vector(d7, std::vector(d8, std::vector(d9, std::vector(d10, std::vector(d11, std::vector(d12, std::vector(d13, std::vector(d14, std::vector(d15, std::vector(d16, std::vector(d17, std::vector(d18, std::vector(d19, std::vector(d20, std::vector(d21, std::vector(d22, std::vector(d23, std::vector(d24, std::vector(d25, std::vector(d26, std::vector(d27, std::vector(d28, std::vector<type>(d29))))))))))))))))))))))))))))))
