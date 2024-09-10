#include <string>
#include <iostream>
class MyString {
    std::string userStr;
public:
    MyString(std::string_view inputStr) : userStr{inputStr} {}
    const std::string_view operator()(std::size_t idx, std::size_t length) {
        std::string_view usv = userStr.substr(idx,length);
        return usv;
    }
    friend std::ostream& operator<<(std::ostream&, const MyString&);
};

std::ostream& operator<<(std::ostream& out, const MyString& myStr) {
    return out << myStr.userStr;
}

int main()
{
    MyString s { "Hello, world!" };
    std::cout << s(7, 5) << '\n'; // start at index 7 and return 5 characters

    return 0;
}