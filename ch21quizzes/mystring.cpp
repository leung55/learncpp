#include <string>
#include <iostream>
#include <cassert>
class MyString {
    std::string userStr;
public:
    MyString(std::string_view inputStr) : userStr{inputStr} {}
    // const MyString operator()(std::size_t idx, std::size_t length) {
    //     assert(idx >= 0);
    //     assert(idx + length <= std::size(userStr));
    //     return MyString{userStr.substr(static_cast<std::string::size_type>(idx),static_cast<std::string::size_type>(length))};
    // }
    std::string_view operator()(std::size_t idx, std::size_t length) {
        // assert(idx >= 0);
        // assert(idx + length <= std::size(userStr));
        // const std::string_view usv = userStr.substr(idx,length);
        return std::string_view{userStr}.substr(idx,length);
    }
    friend std::ostream& operator<<(std::ostream&, const MyString&);
};

std::ostream& operator<<(std::ostream& out, const MyString& myStr) {
    return out << myStr.userStr;
}

int main()
{
    MyString s { "Hello, world!" };
    std::cout << s(7, 5) << "hi" << '\n'; // start at index 7 and return 5 characters

    return 0;
}