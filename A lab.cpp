#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <iomanip>

class Student {
public:
    std::string first_name;
    std::string last_name;
    std::string student_id;
    std::map<std::string, int> grades;

    Student(std::string first, std::string last, std::string id)
        : first_name(first), last_name(last), student_id(id) {}
};

class Assignment {
public:
    std::string assignment_name;
    int total_points;

    Assignment(std::string name, int points)
        : assignment_name(name), total_points(points) {}
};

class Gradebook {
private:
    std::vector<Student> students;
    std::vector<Assignment> assignments;

public:
    void add_student(const std::string& first, const std::string& last, const std::string& id) {
        students.push_back(Student(first, last, id));
    }

    void add_assignment(const std::string& name, int total_points) {
        assignments.push_back(Assignment(name, total_points));
    }

    void enter_grade(const std::string& student_name, const std::string& assignment_name, int grade) {
        for (auto& student : students) {
            if (student.first_name + " " + student.last_name == student_name) {
                for (const auto& assignment : assignments) {
                    if (assignment.assignment_name == assignment_name) {
                        if (grade <= assignment.total_points) {
                            student.grades[assignment_name] = grade;
                        } else {
                            std::cerr << "Grade exceeds total points for " << assignment_name << std::endl;
                        }
                        return;
                    }
                }
                std::cerr << "Assignment not found: " << assignment_name << std::endl;
                return;
            }
        }
        std::cerr << "Student not found: " << student_name << std::endl;
    }

    std::string report() const {
        std::string report_output;
        report_output += "Last_Name,First_Name,Student_Id";

        for (const auto& assignment : assignments) {
            report_output += "," + assignment.assignment_name;
        }
        report_output += "\n";

        for (const auto& student : students) {
            report_output += student.last_name + "," + student.first_name + "," + student.student_id;
            for (const auto& assignment : assignments) {
                if (student.grades.find(assignment.assignment_name) != student.grades.end()) {
                    report_output += "," + std::to_string(student.grades.at(assignment.assignment_name));
                } else {
                    report_output += ",none";  
                }
            }
            report_output += "\n";
        }
        return report_output;
    }
};

int main() {
    Gradebook gradebook;

    gradebook.add_student("Bob", "Bobberson", "ABC123");
    gradebook.add_student("Sam", "Sammerson", "DEF456");
    gradebook.add_student("Jess", "Jesserson", "HIJ789");

    gradebook.add_assignment("Quiz 1", 100);
    gradebook.add_assignment("Lab 1", 50);

    gradebook.enter_grade("Sam Sammerson", "Quiz 1", 95);
    gradebook.enter_grade("Bob Bobberson", "Quiz 1", 85);
    gradebook.enter_grade("Jess Jesserson", "Lab 1", 49);
    gradebook.enter_grade("Jess Jesserson", "Quiz 1", 93);
    gradebook.enter_grade("Bob Bobberson", "Lab 1", 0);

    std::cout << gradebook.report();
    return 0;
}