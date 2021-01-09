#pragma once


#define REGISTER_ECSComponent_01(componentName, type1, name1)      \
namespace ECS::Component {                                         \
struct componentName : ECSBase::ECSComponent<componentName> {      \
                                                                   \
   struct Wrapper {                                                \
	  Wrapper(size_t index)                                      \
            : name1(componentName::name1[index]) {}                \
      type1& name1;                                                \
   };                                                              \
                                                                   \
   static size_t Create() {                                      \
       if(free.empty())                                            \
       {                                                           \
           name1.resize(name1.size() + 1);                         \
           return name1.size() - 1;                                \
	   }                                                           \
       else                                                        \
	   {                                                           \
           size_t index = free.front();                          \
           free.pop();                                             \
           return index;                                           \
	   }                                                           \
   }                                                               \
                                                                   \
   static size_t Copy(const size_t & source) {                 \
        if(free.empty()) {                                         \
            size_t newSize = name1.size() + 1;                   \
            size_t index = name1.size();                         \
            name1.resize(newSize);                                 \
            name1[index] = name1[source];                          \
            return index;                                          \
        }                                                          \
        else {                                                     \
            size_t index = free.front();                         \
            free.pop();                                            \
            name1[index] = name1[source];                          \
            return index;                                          \
        }                                                          \
   }                                                               \
                                                                   \
   static void Delete(size_t index) {                            \
   	   free.push(index);                                           \
   }                                                               \
                                                                   \
   static size_t               Version;                          \
   static std::queue<size_t>   free;                             \
   static std::vector<type1>     name1;                            \
};                                                                 \
}\

#define INIT_ECSComponent_01(componentName, type1, name1)      \
namespace ECS::Component {                                     \
    size_t                componentName::Version(1);         \
    std::queue<size_t>    componentName::free;               \
    std::vector<type1>      componentName::name1(1);           \
}\



#define REGISTER_ECSComponent_02(componentName, type1, name1,      \
                                                type2, name2)      \
namespace ECS::Component {                                         \
struct componentName : ECSBase::ECSComponent<componentName> {      \
                                                                   \
   struct Wrapper {                                                \
	  Wrapper(size_t index)                                      \
            : name1(componentName::name1[index]),                  \
              name2(componentName::name2[index]) {}                \
      type1& name1;                                                \
      type2& name2;                                                \
   };                                                              \
                                                                   \
   static size_t Create() {                                      \
       if(free.empty())                                            \
       {                                                           \
           name1.resize(name1.size() + 1);                         \
           name2.resize(name2.size() + 1);                         \
           return name1.size() - 1;                                \
	   }                                                           \
       else                                                        \
	   {                                                           \
           size_t index = free.front();                          \
           free.pop();                                             \
           return index;                                           \
	   }                                                           \
   }                                                               \
                                                                   \
   static size_t Copy(const size_t & source) {                 \
        if(free.empty()) {                                         \
            size_t newSize = name1.size() + 1;                   \
            size_t index = name1.size();                         \
            name1.resize(newSize);                                 \
            name2.resize(newSize);                                 \
            name1[index] = name1[source];                          \
            name2[index] = name2[source];                          \
            return index;                                          \
        }                                                          \
        else {                                                     \
            size_t index = free.front();                         \
            free.pop();                                            \
            name1[index] = name1[source];                          \
            name2[index] = name2[source];                          \
            return index;                                          \
        }                                                          \
   }                                                               \
                                                                   \
   static void Delete(size_t index) {                            \
   	   free.push(index);                                           \
   }                                                               \
                                                                   \
   static size_t               Version;                          \
   static std::queue<size_t>   free;                             \
   static std::vector<type1>     name1;                            \
   static std::vector<type2>     name2;                            \
};                                                                 \
}\

#define INIT_ECSComponent_02(componentName, type1, name1,      \
                                            type2, name2)      \
namespace ECS::Component {                                     \
    size_t                componentName::Version(1);         \
    std::queue<size_t>    componentName::free;               \
    std::vector<type1>      componentName::name1(1);           \
    std::vector<type2>      componentName::name2(1);           \
}\



#define REGISTER_ECSComponent_03(componentName, type1, name1,      \
                                                type2, name2,      \
                                                type3, name3)      \
namespace ECS::Component {                                         \
struct componentName : ECSBase::ECSComponent<componentName> {      \
                                                                   \
   struct Wrapper {                                                \
	  Wrapper(size_t index)                                      \
            : name1(componentName::name1[index]),                  \
              name2(componentName::name2[index]),                  \
              name3(componentName::name3[index]) {}                \
      type1& name1;                                                \
      type2& name2;                                                \
      type3& name3;                                                \
   };                                                              \
                                                                   \
   static size_t Create() {                                      \
       if(free.empty())                                            \
       {                                                           \
           name1.resize(name1.size() + 1);                         \
           name2.resize(name2.size() + 1);                         \
           name3.resize(name3.size() + 1);                         \
           return name1.size() - 1;                                \
	   }                                                           \
       else                                                        \
	   {                                                           \
           size_t index = free.front();                          \
           free.pop();                                             \
           return index;                                           \
	   }                                                           \
   }                                                               \
                                                                   \
   static size_t Copy(const size_t & source) {                 \
        if(free.empty()) {                                         \
            size_t newSize = name1.size() + 1;                   \
            size_t index = name1.size();                         \
            name1.resize(newSize);                                 \
            name2.resize(newSize);                                 \
            name3.resize(newSize);                                 \
            name1[index] = name1[source];                          \
            name2[index] = name2[source];                          \
            name3[index] = name3[source];                          \
            return index;                                          \
        }                                                          \
        else {                                                     \
            size_t index = free.front();                         \
            free.pop();                                            \
            name1[index] = name1[source];                          \
            name2[index] = name2[source];                          \
            name3[index] = name3[source];                          \
            return index;                                          \
        }                                                          \
   }                                                               \
                                                                   \
   static void Delete(size_t index) {                            \
   	   free.push(index);                                           \
   }                                                               \
                                                                   \
   static size_t               Version;                          \
   static std::queue<size_t>   free;                             \
   static std::vector<type1>     name1;                            \
   static std::vector<type2>     name2;                            \
   static std::vector<type3>     name3;                            \
};                                                                 \
}\

#define INIT_ECSComponent_03(componentName, type1, name1,      \
                                            type2, name2,      \
                                            type3, name3)      \
namespace ECS::Component {                                     \
    size_t                componentName::Version(1);         \
    std::queue<size_t>    componentName::free;               \
    std::vector<type1>      componentName::name1(1);           \
    std::vector<type2>      componentName::name2(1);           \
    std::vector<type3>      componentName::name3(1);           \
}\




#define REGISTER_ECSComponent_04(componentName, type1, name1,      \
                                                type2, name2,      \
                                                type3, name3,      \
                                                type4, name4)      \
namespace ECS::Component {                                         \
struct componentName : ECSBase::ECSComponent<componentName> {      \
                                                                   \
   struct Wrapper {                                                \
	  Wrapper(size_t index)                                      \
            : name1(componentName::name1[index]),                  \
              name2(componentName::name2[index]),                  \
              name3(componentName::name3[index]),                  \
              name4(componentName::name4[index]) {}                \
      type1& name1;                                                \
      type2& name2;                                                \
      type3& name3;                                                \
      type4& name4;                                                \
   };                                                              \
                                                                   \
   static size_t Create() {                                      \
       if(free.empty())                                            \
       {                                                           \
           name1.resize(name1.size() + 1);                         \
           name2.resize(name2.size() + 1);                         \
           name3.resize(name3.size() + 1);                         \
           name4.resize(name4.size() + 1);                         \
           return name1.size() - 1;                                \
	   }                                                           \
       else                                                        \
	   {                                                           \
           size_t index = free.front();                          \
           free.pop();                                             \
           return index;                                           \
	   }                                                           \
   }                                                               \
                                                                   \
   static size_t Copy(const size_t & source) {                 \
        if(free.empty()) {                                         \
            size_t newSize = name1.size() + 1;                   \
            size_t index = name1.size();                         \
            name1.resize(newSize);                                 \
            name2.resize(newSize);                                 \
            name3.resize(newSize);                                 \
            name4.resize(newSize);                                 \
            name1[index] = name1[source];                          \
            name2[index] = name2[source];                          \
            name3[index] = name3[source];                          \
            name4[index] = name4[source];                          \
            return index;                                          \
        }                                                          \
        else {                                                     \
            size_t index = free.front();                         \
            free.pop();                                            \
            name1[index] = name1[source];                          \
            name2[index] = name2[source];                          \
            name3[index] = name3[source];                          \
            name4[index] = name4[source];                          \
            return index;                                          \
        }                                                          \
   }                                                               \
                                                                   \
   static void Delete(size_t index) {                            \
   	   free.push(index);                                           \
   }                                                               \
                                                                   \
   static size_t               Version;                          \
   static std::queue<size_t>   free;                             \
   static std::vector<type1>     name1;                            \
   static std::vector<type2>     name2;                            \
   static std::vector<type3>     name3;                            \
   static std::vector<type4>     name4;                            \
};                                                                 \
}\

#define INIT_ECSComponent_04(componentName, type1, name1,      \
                                            type2, name2,      \
                                            type3, name3,      \
                                            type4, name4)      \
namespace ECS::Component {                                     \
    size_t                componentName::Version(1);         \
    std::queue<size_t>    componentName::free;               \
    std::vector<type1>      componentName::name1(1);           \
    std::vector<type2>      componentName::name2(1);           \
    std::vector<type3>      componentName::name3(1);           \
    std::vector<type4>      componentName::name4(1);           \
}\





#define REGISTER_ECSComponent_05(componentName, type1, name1,      \
                                                type2, name2,      \
                                                type3, name3,      \
                                                type4, name4,      \
                                                type5, name5)      \
namespace ECS::Component {                                         \
struct componentName : ECSBase::ECSComponent<componentName> {      \
                                                                   \
   struct Wrapper {                                                \
	  Wrapper(size_t index)                                      \
            : name1(componentName::name1[index]),                  \
              name2(componentName::name2[index]),                  \
              name3(componentName::name3[index]),                  \
              name4(componentName::name4[index]),                  \
              name5(componentName::name5[index]) {}                \
      type1& name1;                                                \
      type2& name2;                                                \
      type3& name3;                                                \
      type4& name4;                                                \
      type5& name5;                                                \
   };                                                              \
                                                                   \
   static size_t Create() {                                      \
       if(free.empty())                                            \
       {                                                           \
           name1.resize(name1.size() + 1);                         \
           name2.resize(name2.size() + 1);                         \
           name3.resize(name3.size() + 1);                         \
           name4.resize(name4.size() + 1);                         \
           name5.resize(name5.size() + 1);                         \
           return name1.size() - 1;                                \
	   }                                                           \
       else                                                        \
	   {                                                           \
           size_t index = free.front();                          \
           free.pop();                                             \
           return index;                                           \
	   }                                                           \
   }                                                               \
                                                                   \
   static size_t Copy(const size_t & source) {                 \
        if(free.empty()) {                                         \
            size_t newSize = name1.size() + 1;                   \
            size_t index = name1.size();                         \
            name1.resize(newSize);                                 \
            name2.resize(newSize);                                 \
            name3.resize(newSize);                                 \
            name4.resize(newSize);                                 \
            name5.resize(newSize);                                 \
            name1[index] = name1[source];                          \
            name2[index] = name2[source];                          \
            name3[index] = name3[source];                          \
            name4[index] = name4[source];                          \
            name5[index] = name5[source];                          \
            return index;                                          \
        }                                                          \
        else {                                                     \
            size_t index = free.front();                         \
            free.pop();                                            \
            name1[index] = name1[source];                          \
            name2[index] = name2[source];                          \
            name3[index] = name3[source];                          \
            name4[index] = name4[source];                          \
            name5[index] = name5[source];                          \
            return index;                                          \
        }                                                          \
   }                                                               \
                                                                   \
   static void Delete(size_t index) {                            \
   	   free.push(index);                                           \
   }                                                               \
                                                                   \
   static size_t               Version;                          \
   static std::queue<size_t>   free;                             \
   static std::vector<type1>     name1;                            \
   static std::vector<type2>     name2;                            \
   static std::vector<type3>     name3;                            \
   static std::vector<type4>     name4;                            \
   static std::vector<type5>     name5;                            \
};                                                                 \
}\

#define INIT_ECSComponent_05(componentName, type1, name1,      \
                                            type2, name2,      \
                                            type3, name3,      \
                                            type4, name4,      \
                                            type5, name5)      \
namespace ECS::Component {                                     \
    size_t                componentName::Version(1);         \
    std::queue<size_t>    componentName::free;               \
    std::vector<type1>      componentName::name1(1);           \
    std::vector<type2>      componentName::name2(1);           \
    std::vector<type3>      componentName::name3(1);           \
    std::vector<type4>      componentName::name4(1);           \
    std::vector<type5>      componentName::name5(1);           \
}\




#define REGISTER_ECSComponent_06(componentName, type1, name1,      \
                                                type2, name2,      \
                                                type3, name3,      \
                                                type4, name4,      \
                                                type5, name5,      \
                                                type6, name6)      \
namespace ECS::Component {                                         \
struct componentName : ECSBase::ECSComponent<componentName> {      \
                                                                   \
   struct Wrapper {                                                \
	  Wrapper(size_t index)                                      \
            : name1(componentName::name1[index]),                  \
              name2(componentName::name2[index]),                  \
              name3(componentName::name3[index]),                  \
              name4(componentName::name4[index]),                  \
              name5(componentName::name5[index]),                  \
              name6(componentName::name6[index]) {}                \
      type1& name1;                                                \
      type2& name2;                                                \
      type3& name3;                                                \
      type4& name4;                                                \
      type5& name5;                                                \
      type6& name6;                                                \
   };                                                              \
                                                                   \
   static size_t Create() {                                      \
       if(free.empty())                                            \
       {                                                           \
           name1.resize(name1.size() + 1);                         \
           name2.resize(name2.size() + 1);                         \
           name3.resize(name3.size() + 1);                         \
           name4.resize(name4.size() + 1);                         \
           name5.resize(name5.size() + 1);                         \
           name6.resize(name6.size() + 1);                         \
           return name1.size() - 1;                                \
	   }                                                           \
       else                                                        \
	   {                                                           \
           size_t index = free.front();                          \
           free.pop();                                             \
           return index;                                           \
	   }                                                           \
   }                                                               \
                                                                   \
   static size_t Copy(const size_t & source) {                 \
        if(free.empty()) {                                         \
            size_t newSize = name1.size() + 1;                   \
            size_t index = name1.size();                         \
            name1.resize(newSize);                                 \
            name2.resize(newSize);                                 \
            name3.resize(newSize);                                 \
            name4.resize(newSize);                                 \
            name5.resize(newSize);                                 \
            name6.resize(newSize);                                 \
            name1[index] = name1[source];                          \
            name2[index] = name2[source];                          \
            name3[index] = name3[source];                          \
            name4[index] = name4[source];                          \
            name5[index] = name5[source];                          \
            name6[index] = name6[source];                          \
            return index;                                          \
        }                                                          \
        else {                                                     \
            size_t index = free.front();                         \
            free.pop();                                            \
            name1[index] = name1[source];                          \
            name2[index] = name2[source];                          \
            name3[index] = name3[source];                          \
            name4[index] = name4[source];                          \
            name5[index] = name5[source];                          \
            name6[index] = name6[source];                          \
            return index;                                          \
        }                                                          \
   }                                                               \
                                                                   \
   static void Delete(size_t index) {                            \
   	   free.push(index);                                           \
   }                                                               \
                                                                   \
   static size_t               Version;                          \
   static std::queue<size_t>   free;                             \
   static std::vector<type1>     name1;                            \
   static std::vector<type2>     name2;                            \
   static std::vector<type3>     name3;                            \
   static std::vector<type4>     name4;                            \
   static std::vector<type5>     name5;                            \
   static std::vector<type6>     name6;                            \
};                                                                 \
}\

#define INIT_ECSComponent_06(componentName, type1, name1,      \
                                            type2, name2,      \
                                            type3, name3,      \
                                            type4, name4,      \
                                            type5, name5,      \
                                            type6, name6)      \
namespace ECS::Component {                                     \
    size_t                componentName::Version(1);         \
    std::queue<size_t>    componentName::free;               \
    std::vector<type1>      componentName::name1(1);           \
    std::vector<type2>      componentName::name2(1);           \
    std::vector<type3>      componentName::name3(1);           \
    std::vector<type4>      componentName::name4(1);           \
    std::vector<type5>      componentName::name5(1);           \
    std::vector<type6>      componentName::name6(1);           \
}\




#define REGISTER_ECSComponent_07(componentName, type1, name1,      \
                                                type2, name2,      \
                                                type3, name3,      \
                                                type4, name4,      \
                                                type5, name5,      \
                                                type6, name6,      \
                                                type7, name7)      \
namespace ECS::Component {                                         \
struct componentName : ECSBase::ECSComponent<componentName> {      \
                                                                   \
   struct Wrapper {                                                \
	  Wrapper(size_t index)                                      \
            : name1(componentName::name1[index]),                  \
              name2(componentName::name2[index]),                  \
              name3(componentName::name3[index]),                  \
              name4(componentName::name4[index]),                  \
              name5(componentName::name5[index]),                  \
              name6(componentName::name6[index]),                  \
              name7(componentName::name7[index]) {}                \
      type1& name1;                                                \
      type2& name2;                                                \
      type3& name3;                                                \
      type4& name4;                                                \
      type5& name5;                                                \
      type6& name6;                                                \
      type7& name7;                                                \
   };                                                              \
                                                                   \
   static size_t Create() {                                      \
       if(free.empty())                                            \
       {                                                           \
           name1.resize(name1.size() + 1);                         \
           name2.resize(name2.size() + 1);                         \
           name3.resize(name3.size() + 1);                         \
           name4.resize(name4.size() + 1);                         \
           name5.resize(name5.size() + 1);                         \
           name6.resize(name6.size() + 1);                         \
           name7.resize(name7.size() + 1);                         \
           return name1.size() - 1;                                \
	   }                                                           \
       else                                                        \
	   {                                                           \
           size_t index = free.front();                          \
           free.pop();                                             \
           return index;                                           \
	   }                                                           \
   }                                                               \
                                                                   \
   static size_t Copy(const size_t & source) {                 \
        if(free.empty()) {                                         \
            size_t newSize = name1.size() + 1;                   \
            size_t index = name1.size();                         \
            name1.resize(newSize);                                 \
            name2.resize(newSize);                                 \
            name3.resize(newSize);                                 \
            name4.resize(newSize);                                 \
            name5.resize(newSize);                                 \
            name6.resize(newSize);                                 \
            name7.resize(newSize);                                 \
            name1[index] = name1[source];                          \
            name2[index] = name2[source];                          \
            name3[index] = name3[source];                          \
            name4[index] = name4[source];                          \
            name5[index] = name5[source];                          \
            name6[index] = name6[source];                          \
            name7[index] = name7[source];                          \
            return index;                                          \
        }                                                          \
        else {                                                     \
            size_t index = free.front();                         \
            free.pop();                                            \
            name1[index] = name1[source];                          \
            name2[index] = name2[source];                          \
            name3[index] = name3[source];                          \
            name4[index] = name4[source];                          \
            name5[index] = name5[source];                          \
            name6[index] = name6[source];                          \
            name7[index] = name7[source];                          \
            return index;                                          \
        }                                                          \
   }                                                               \
                                                                   \
   static void Delete(size_t index) {                            \
   	   free.push(index);                                           \
   }                                                               \
                                                                   \
   static size_t               Version;                          \
   static std::queue<size_t>   free;                             \
   static std::vector<type1>     name1;                            \
   static std::vector<type2>     name2;                            \
   static std::vector<type3>     name3;                            \
   static std::vector<type4>     name4;                            \
   static std::vector<type5>     name5;                            \
   static std::vector<type6>     name6;                            \
   static std::vector<type7>     name7;                            \
};                                                                 \
}\

#define INIT_ECSComponent_07(componentName, type1, name1,      \
                                            type2, name2,      \
                                            type3, name3,      \
                                            type4, name4,      \
                                            type5, name5,      \
                                            type6, name6,      \
                                            type7, name7)      \
namespace ECS::Component {                                     \
    size_t                componentName::Version(1);         \
    std::queue<size_t>    componentName::free;               \
    std::vector<type1>      componentName::name1(1);           \
    std::vector<type2>      componentName::name2(1);           \
    std::vector<type3>      componentName::name3(1);           \
    std::vector<type4>      componentName::name4(1);           \
    std::vector<type5>      componentName::name5(1);           \
    std::vector<type6>      componentName::name6(1);           \
    std::vector<type7>      componentName::name7(1);           \
}\




#define REGISTER_ECSComponent_08(componentName, type1, name1,      \
                                                type2, name2,      \
                                                type3, name3,      \
                                                type4, name4,      \
                                                type5, name5,      \
                                                type6, name6,      \
                                                type7, name7,      \
                                                type8, name8)      \
namespace ECS::Component {                                         \
struct componentName : ECSBase::ECSComponent<componentName> {      \
                                                                   \
   struct Wrapper {                                                \
	  Wrapper(size_t index)                                      \
            : name1(componentName::name1[index]),                  \
              name2(componentName::name2[index]),                  \
              name3(componentName::name3[index]),                  \
              name4(componentName::name4[index]),                  \
              name5(componentName::name5[index]),                  \
              name6(componentName::name6[index]),                  \
              name7(componentName::name7[index]),                  \
              name8(componentName::name8[index]) {}                \
      type1& name1;                                                \
      type2& name2;                                                \
      type3& name3;                                                \
      type4& name4;                                                \
      type5& name5;                                                \
      type6& name6;                                                \
      type7& name7;                                                \
      type8& name8;                                                \
   };                                                              \
                                                                   \
   static size_t Create() {                                      \
       if(free.empty())                                            \
       {                                                           \
           name1.resize(name1.size() + 1);                         \
           name2.resize(name2.size() + 1);                         \
           name3.resize(name3.size() + 1);                         \
           name4.resize(name4.size() + 1);                         \
           name5.resize(name5.size() + 1);                         \
           name6.resize(name6.size() + 1);                         \
           name7.resize(name7.size() + 1);                         \
           name8.resize(name8.size() + 1);                         \
           return name1.size() - 1;                                \
	   }                                                           \
       else                                                        \
	   {                                                           \
           size_t index = free.front();                          \
           free.pop();                                             \
           return index;                                           \
	   }                                                           \
   }                                                               \
                                                                   \
   static size_t Copy(const size_t & source) {                 \
        if(free.empty()) {                                         \
            size_t newSize = name1.size() + 1;                   \
            size_t index = name1.size();                         \
            name1.resize(newSize);                                 \
            name2.resize(newSize);                                 \
            name3.resize(newSize);                                 \
            name4.resize(newSize);                                 \
            name5.resize(newSize);                                 \
            name6.resize(newSize);                                 \
            name7.resize(newSize);                                 \
            name8.resize(newSize);                                 \
            name1[index] = name1[source];                          \
            name2[index] = name2[source];                          \
            name3[index] = name3[source];                          \
            name4[index] = name4[source];                          \
            name5[index] = name5[source];                          \
            name6[index] = name6[source];                          \
            name7[index] = name7[source];                          \
            name8[index] = name8[source];                          \
            return index;                                          \
        }                                                          \
        else {                                                     \
            size_t index = free.front();                         \
            free.pop();                                            \
            name1[index] = name1[source];                          \
            name2[index] = name2[source];                          \
            name3[index] = name3[source];                          \
            name4[index] = name4[source];                          \
            name5[index] = name5[source];                          \
            name6[index] = name6[source];                          \
            name7[index] = name7[source];                          \
            name8[index] = name8[source];                          \
            return index;                                          \
        }                                                          \
   }                                                               \
                                                                   \
   static void Delete(size_t index) {                            \
   	   free.push(index);                                           \
   }                                                               \
                                                                   \
   static size_t               Version;                          \
   static std::queue<size_t>   free;                             \
   static std::vector<type1>     name1;                            \
   static std::vector<type2>     name2;                            \
   static std::vector<type3>     name3;                            \
   static std::vector<type4>     name4;                            \
   static std::vector<type5>     name5;                            \
   static std::vector<type6>     name6;                            \
   static std::vector<type7>     name7;                            \
   static std::vector<type8>     name8;                            \
};                                                                 \
}\

#define INIT_ECSComponent_08(componentName, type1, name1,      \
                                            type2, name2,      \
                                            type3, name3,      \
                                            type4, name4,      \
                                            type5, name5,      \
                                            type6, name6,      \
                                            type7, name7,      \
                                            type8, name8)      \
namespace ECS::Component {                                     \
    size_t                componentName::Version(1);         \
    std::queue<size_t>    componentName::free;               \
    std::vector<type1>      componentName::name1(1);           \
    std::vector<type2>      componentName::name2(1);           \
    std::vector<type3>      componentName::name3(1);           \
    std::vector<type4>      componentName::name4(1);           \
    std::vector<type5>      componentName::name5(1);           \
    std::vector<type6>      componentName::name6(1);           \
    std::vector<type7>      componentName::name7(1);           \
    std::vector<type8>      componentName::name8(1);           \
}\




#define REGISTER_ECSComponent_09(componentName, type1, name1,      \
                                                type2, name2,      \
                                                type3, name3,      \
                                                type4, name4,      \
                                                type5, name5,      \
                                                type6, name6,      \
                                                type7, name7,      \
                                                type8, name8,      \
                                                type9, name9)      \
namespace ECS::Component {                                         \
struct componentName : ECSBase::ECSComponent<componentName> {      \
                                                                   \
   struct Wrapper {                                                \
	  Wrapper(size_t index)                                      \
            : name1(componentName::name1[index]),                  \
              name2(componentName::name2[index]),                  \
              name3(componentName::name3[index]),                  \
              name4(componentName::name4[index]),                  \
              name5(componentName::name5[index]),                  \
              name6(componentName::name6[index]),                  \
              name7(componentName::name7[index]),                  \
              name8(componentName::name8[index]),                  \
              name9(componentName::name9[index]) {}                \
      type1& name1;                                                \
      type2& name2;                                                \
      type3& name3;                                                \
      type4& name4;                                                \
      type5& name5;                                                \
      type6& name6;                                                \
      type7& name7;                                                \
      type8& name8;                                                \
      type9& name9;                                                \
   };                                                              \
                                                                   \
   static size_t Create() {                                      \
       if(free.empty())                                            \
       {                                                           \
           size_t newSize = name1.size() + 1;                    \
           name1.resize(newSize);                                  \
           name2.resize(newSize);                                  \
           name3.resize(newSize);                                  \
           name4.resize(newSize);                                  \
           name5.resize(newSize);                                  \
           name6.resize(newSize);                                  \
           name7.resize(newSize);                                  \
           name8.resize(newSize);                                  \
           name9.resize(newSize);                                  \
           return name1.size() - 1;                                \
	   }                                                           \
       else                                                        \
	   {                                                           \
           size_t index = free.front();                          \
           free.pop();                                             \
           return index;                                           \
	   }                                                           \
   }                                                               \
                                                                   \
   static size_t Copy(const size_t & source) {                 \
        if(free.empty()) {                                         \
            size_t newSize = name1.size() + 1;                   \
            size_t index = name1.size();                         \
            name1.resize(newSize);                                 \
            name2.resize(newSize);                                 \
            name3.resize(newSize);                                 \
            name4.resize(newSize);                                 \
            name5.resize(newSize);                                 \
            name6.resize(newSize);                                 \
            name7.resize(newSize);                                 \
            name8.resize(newSize);                                 \
            name9.resize(newSize);                                 \
            name1[index] = name1[source];                          \
            name2[index] = name2[source];                          \
            name3[index] = name3[source];                          \
            name4[index] = name4[source];                          \
            name5[index] = name5[source];                          \
            name6[index] = name6[source];                          \
            name7[index] = name7[source];                          \
            name8[index] = name8[source];                          \
            name9[index] = name9[source];                          \
            return index;                                          \
        }                                                          \
        else {                                                     \
            size_t index = free.front();                         \
            free.pop();                                            \
            name1[index] = name1[source];                          \
            name2[index] = name2[source];                          \
            name3[index] = name3[source];                          \
            name4[index] = name4[source];                          \
            name5[index] = name5[source];                          \
            name6[index] = name6[source];                          \
            name7[index] = name7[source];                          \
            name8[index] = name8[source];                          \
            name9[index] = name9[source];                          \
            return index;                                          \
        }                                                          \
   }                                                               \
                                                                   \
   static void Delete(const size_t & index) {                    \
       name1[index] = type1();                                     \
       name2[index] = type2();                                     \
       name3[index] = type3();                                     \
       name4[index] = type4();                                     \
       name5[index] = type5();                                     \
       name6[index] = type6();                                     \
       name7[index] = type7();                                     \
       name8[index] = type8();                                     \
       name9[index] = type9();                                     \
   	   free.push(index);                                           \
   }                                                               \
                                                                   \
   static size_t               Version;                          \
   static std::queue<size_t>   free;                             \
   static std::vector<type1>     name1;                            \
   static std::vector<type2>     name2;                            \
   static std::vector<type3>     name3;                            \
   static std::vector<type4>     name4;                            \
   static std::vector<type5>     name5;                            \
   static std::vector<type6>     name6;                            \
   static std::vector<type7>     name7;                            \
   static std::vector<type8>     name8;                            \
   static std::vector<type9>     name9;                            \
};                                                                 \
}\

#define INIT_ECSComponent_09(componentName, type1, name1,      \
                                            type2, name2,      \
                                            type3, name3,      \
                                            type4, name4,      \
                                            type5, name5,      \
                                            type6, name6,      \
                                            type7, name7,      \
                                            type8, name8,      \
                                            type9, name9)      \
namespace ECS::Component {                                     \
    size_t                componentName::Version(1);         \
    std::queue<size_t>    componentName::free;               \
    std::vector<type1>      componentName::name1(1);           \
    std::vector<type2>      componentName::name2(1);           \
    std::vector<type3>      componentName::name3(1);           \
    std::vector<type4>      componentName::name4(1);           \
    std::vector<type5>      componentName::name5(1);           \
    std::vector<type6>      componentName::name6(1);           \
    std::vector<type7>      componentName::name7(1);           \
    std::vector<type8>      componentName::name8(1);           \
    std::vector<type9>      componentName::name9(1);           \
}\



//---------------------------------------------------------
//           IMPLEMENT 10 - 11 - 12 - 13
//-------------------------------------------------------




#define REGISTER_ECSComponent_14(componentName, type1, name1,      \
                                                type2, name2,      \
                                                type3, name3,      \
                                                type4, name4,      \
                                                type5, name5,      \
                                                type6, name6,      \
                                                type7, name7,      \
                                                type8, name8,      \
                                                type9, name9,      \
                                                type10, name10,    \
                                                type11, name11,    \
                                                type12, name12,    \
                                                type13, name13,    \
                                                type14, name14)    \
namespace ECS::Component {                                         \
struct componentName : ECSBase::ECSComponent<componentName> {      \
                                                                   \
   struct Wrapper {                                                \
	  Wrapper(size_t index)                                      \
            : name1(componentName::name1[index]),                  \
              name2(componentName::name2[index]),                  \
              name3(componentName::name3[index]),                  \
              name4(componentName::name4[index]),                  \
              name5(componentName::name5[index]),                  \
              name6(componentName::name6[index]),                  \
              name7(componentName::name7[index]),                  \
              name8(componentName::name8[index]),                  \
              name9(componentName::name9[index]),                  \
              name10(componentName::name10[index]),                \
              name11(componentName::name11[index]),                \
              name12(componentName::name12[index]),                \
              name13(componentName::name13[index]),                \
              name14(componentName::name14[index]) {}              \
      type1& name1;                                                \
      type2& name2;                                                \
      type3& name3;                                                \
      type4& name4;                                                \
      type5& name5;                                                \
      type6& name6;                                                \
      type7& name7;                                                \
      type8& name8;                                                \
      type9& name9;                                                \
      type10& name10;                                              \
      type11& name11;                                              \
      type12& name12;                                              \
      type13& name13;                                              \
      type14& name14;                                              \
   };                                                              \
                                                                   \
   static size_t Create() {                                      \
       if(free.empty())                                            \
       {                                                           \
           size_t newSize = name1.size() + 1;                    \
           name1.resize(newSize);                                  \
           name2.resize(newSize);                                  \
           name3.resize(newSize);                                  \
           name4.resize(newSize);                                  \
           name5.resize(newSize);                                  \
           name6.resize(newSize);                                  \
           name7.resize(newSize);                                  \
           name8.resize(newSize);                                  \
           name9.resize(newSize);                                  \
           name10.resize(newSize);                                 \
           name11.resize(newSize);                                 \
           name12.resize(newSize);                                 \
           name13.resize(newSize);                                 \
           name14.resize(newSize);                                 \
           return name1.size() - 1;                                \
	   }                                                           \
       else                                                        \
	   {                                                           \
           size_t index = free.front();                          \
           free.pop();                                             \
           return index;                                           \
	   }                                                           \
   }                                                               \
                                                                   \
   static size_t Copy(const size_t & source) {                 \
        if(free.empty()) {                                         \
            size_t newSize = name1.size() + 1;                   \
            size_t index = name1.size();                         \
            name1.resize(newSize);                                 \
            name2.resize(newSize);                                 \
            name3.resize(newSize);                                 \
            name4.resize(newSize);                                 \
            name5.resize(newSize);                                 \
            name6.resize(newSize);                                 \
            name7.resize(newSize);                                 \
            name8.resize(newSize);                                 \
            name9.resize(newSize);                                 \
            name10.resize(newSize);                                \
            name11.resize(newSize);                                \
            name12.resize(newSize);                                \
            name13.resize(newSize);                                \
            name14.resize(newSize);                                \
            name1[index] = name1[source];                          \
            name2[index] = name2[source];                          \
            name3[index] = name3[source];                          \
            name4[index] = name4[source];                          \
            name5[index] = name5[source];                          \
            name6[index] = name6[source];                          \
            name7[index] = name7[source];                          \
            name8[index] = name8[source];                          \
            name9[index] = name9[source];                          \
            name10[index] = name10[source];                        \
            name11[index] = name11[source];                        \
            name12[index] = name12[source];                        \
            name13[index] = name13[source];                        \
            name14[index] = name14[source];                        \
            return index;                                          \
        }                                                          \
        else {                                                     \
            size_t index = free.front();                         \
            free.pop();                                            \
            name1[index] = name1[source];                          \
            name2[index] = name2[source];                          \
            name3[index] = name3[source];                          \
            name4[index] = name4[source];                          \
            name5[index] = name5[source];                          \
            name6[index] = name6[source];                          \
            name7[index] = name7[source];                          \
            name8[index] = name8[source];                          \
            name9[index] = name9[source];                          \
            name10[index] = name10[source];                        \
            name11[index] = name11[source];                        \
            name12[index] = name12[source];                        \
            name13[index] = name13[source];                        \
            name14[index] = name14[source];                        \
            return index;                                          \
        }                                                          \
   }                                                               \
                                                                   \
   static void Delete(const size_t & index) {                    \
       name1[index] = type1();                                     \
       name2[index] = type2();                                     \
       name3[index] = type3();                                     \
       name4[index] = type4();                                     \
       name5[index] = type5();                                     \
       name6[index] = type6();                                     \
       name7[index] = type7();                                     \
       name8[index] = type8();                                     \
       name9[index] = type9();                                     \
       name10[index] = type10();                                   \
       name11[index] = type11();                                   \
       name12[index] = type12();                                   \
       name13[index] = type13();                                   \
       name14[index] = type14();                                   \
   	   free.push(index);                                           \
   }                                                               \
                                                                   \
   static size_t               Version;                          \
   static std::queue<size_t>   free;                             \
   static std::vector<type1>     name1;                            \
   static std::vector<type2>     name2;                            \
   static std::vector<type3>     name3;                            \
   static std::vector<type4>     name4;                            \
   static std::vector<type5>     name5;                            \
   static std::vector<type6>     name6;                            \
   static std::vector<type7>     name7;                            \
   static std::vector<type8>     name8;                            \
   static std::vector<type9>     name9;                            \
   static std::vector<type10>    name10;                           \
   static std::vector<type11>    name11;                           \
   static std::vector<type12>    name12;                           \
   static std::vector<type13>    name13;                           \
   static std::vector<type14>    name14;                           \
};                                                                 \
}\

#define INIT_ECSComponent_14(componentName, type1, name1,      \
                                            type2, name2,      \
                                            type3, name3,      \
                                            type4, name4,      \
                                            type5, name5,      \
                                            type6, name6,      \
                                            type7, name7,      \
                                            type8, name8,      \
                                            type9, name9,      \
                                            type10, name10,    \
                                            type11, name11,    \
                                            type12, name12,    \
                                            type13, name13,    \
                                            type14, name14)    \
namespace ECS::Component {                                     \
    size_t                componentName::Version(1);         \
    std::queue<size_t>    componentName::free;               \
    std::vector<type1>      componentName::name1(1);           \
    std::vector<type2>      componentName::name2(1);           \
    std::vector<type3>      componentName::name3(1);           \
    std::vector<type4>      componentName::name4(1);           \
    std::vector<type5>      componentName::name5(1);           \
    std::vector<type6>      componentName::name6(1);           \
    std::vector<type7>      componentName::name7(1);           \
    std::vector<type8>      componentName::name8(1);           \
    std::vector<type9>      componentName::name9(1);           \
    std::vector<type10>     componentName::name10(1);          \
    std::vector<type11>     componentName::name11(1);          \
    std::vector<type12>     componentName::name12(1);          \
    std::vector<type13>     componentName::name13(1);          \
    std::vector<type14>     componentName::name14(1);          \
}\

