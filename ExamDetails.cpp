#include "examDetails.h"
#include <iostream> 
#include <string>

ExamDetails::ExamDetails(int course_id, int month, int day, double hour, int length, std::string link):
    course_id(course_id)
{
    // exceptions
    if (month < 1 || month > 12 || day < 1 || day > 30)
        throw ExamDetails::InvalidDateException();

    if (hour < 0 || hour >= 24 || ((hour - (int)hour != 0) && (hour - (int)hour != 0.5)))
        throw ExamDetails::InvalidTimeException();
    
    if (length%1 != 0)
        throw ExamDetails::InvalidArgsException();

    // assigning the values
    this->month = month;
    this->day = day;
    this->hour = hour;
    this->length = length;
    this->link = link;
}

std::string ExamDetails::getLink()
{
    return this->link;
}

void ExamDetails::setLink(std::string link)
{
    this->link = link;
}

int ExamDetails::operator- (ExamDetails exam)
{
    int months_difference = this->month - exam.month;
    int days_difference = this->day - exam.day;
    int toatal_difference = months_difference*30 + days_difference;
    return toatal_difference;
}

bool ExamDetails::operator< (ExamDetails exam)
{
    return (((*this)-exam) < 0);
}

ExamDetails ExamDetails::makeMatamExam()
{
    ExamDetails new_exam(234124, 7, 28, 13, 3, "https://tinyurl.com/59hzps6m");
    return new_exam;
}



int main()
{
    ExamDetails exam1 = ExamDetails::makeMatamExam();
    ExamDetails exam2(104032, 7, 11, 9.5, 3);
    ExamDetails exam3 = exam1;
    std::cout << "the difference between MATAM and infi 2m is " << (exam1-exam2) << " days" << std::endl;
    ExamDetails& closest = (exam1 < exam2) ? exam1 : exam2;
    std::cout << "your closest exam is:" << std::endl;
    std::cout << closest.course_id << std::endl;
    std::cout << closest.month << std::endl;
    std::cout << closest.day << std::endl;
    std::cout << closest.hour << std::endl;
    std::cout << closest.length << std::endl;
    std::cout << closest.link << std::endl;
}

/*
std::string ExamDetails::getLink()
{
    return this->link;
}
*/
