#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <iostream>
#include <string>

const std::string student_name = "Sundeep Kumar";
const int student_id = 00152529;

void printStudentInfo() {
    std::cout << "Student Name: " << student_name << std::endl;
    std::cout << "Student ID: " << student_id << std::endl;
}

#endif // STUDENT_HPP
