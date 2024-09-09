#include <iostream>
#include <typeinfo>
#include <string_view>

template <typename T>
constexpr auto type_name() {
  std::string_view name, prefix, suffix;
#ifdef __clang__
  name = __PRETTY_FUNCTION__;
  prefix = "auto type_name() [T = ";
  suffix = "]";
#elif defined(__GNUC__)
  name = __PRETTY_FUNCTION__;
  prefix = "constexpr auto type_name() [with T = ";
  suffix = "]";
#elif defined(_MSC_VER)
  name = __FUNCSIG__;
  prefix = "auto __cdecl type_name<";
  suffix = ">(void)";
#endif
  name.remove_prefix(prefix.size());
  name.remove_suffix(suffix.size());
  return name;
}

int main () {

    int x { 7 }; // non-constant
    int (*array1)[5] { new int[x][5] }; // rightmost dimension must be constexpr

    int* *array2 { new int*[10] }; // allocate an array of 10 int pointers — these are our rows

    int* arr3[5];
    int (*arr4)[5];

    std::cout << type_name<decltype(arr3)>() << '\n';
    std::cout << type_name<decltype(arr4)>() << '\n';
    // for(std::size_t i{0}; i < 5; ++i) {
    //     arr3[i] = {new int[i+6]};
    //     arr4[i] = {new int[i+6]};
    // }
    for (int count { 0 }; count < 10; ++count)
        array2[count] = new int[count + 1]; // these are our columns
    
    for(int i{0}; i < 10; ++i) {
        for(int j{0}; j < i + 1; ++j) {
            (*(*(array2 + i) + j)) = i*(i+1)/2 + j + 1;
        }
    }

    for(int i{0}; i < 10; ++i) {
        for(int j{0}; j < i + 1; ++j) {
            std::cout << (*((*(array2 + i)) + j)) << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';

    for(int i{0}; i < 10; ++i) {
        for(int j{0}; j < 20; ++j) {
            std::cout << *((*(array2 + i)) + j) << ' ';
        }
        std::cout << '\n';
    }
      return 0;
}