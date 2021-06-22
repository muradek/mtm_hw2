#include "ExamDetails.h"
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

 std::string ExamDetails::getLink() const
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

std::ostream& operator<<(std::ostream& os, const ExamDetails& exam)
{
    std::string number = "Course Number: " + std::to_string(exam.course_id);

    std::string date = std::to_string(exam.day)  + "." + std::to_string(exam.month);
    std::string minutes = exam.hour - (int)exam.hour == 0.5 ? "30" : "00";
    std::string hour_str = std::to_string((int)exam.hour) + ":" + minutes;
    std::string time = "Time: " + date + " at " + hour_str;

    std::string duration = "Duration: " + std::to_string(exam.length) + ":" + "00";

    std::string zoom_link = "Zoom Link: " + exam.link;

    return os << number << std::endl << time << std::endl << duration << std::endl << zoom_link << std::endl;
}
