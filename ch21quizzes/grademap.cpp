#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
struct StudentGrade {
    std::string name{};
    char grade{};
};

class GradeMap {
    std::vector<StudentGrade> m_map;

public:
    GradeMap() {}
    char& operator[](std::string_view key) {
        auto student{std::find_if(m_map.begin(), m_map.end(), 
            [&key] (const StudentGrade& stdt) {
                return key == stdt.name;
            })};
        if(student == m_map.end()) {
            return (m_map.emplace_back(std::string{key})).grade;
        }
        return student->grade;
    }
};


int main()
{
	GradeMap grades{};

	grades["Joe"] = 'A';
	grades["Frank"] = 'B';

	std::cout << "Joe has a grade of " << grades["Joe"] << '\n';
	std::cout << "Frank has a grade of " << grades["Frank"] << '\n';

	return 0;
}