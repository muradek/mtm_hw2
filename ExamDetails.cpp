#include "examDetails.h"
#include <iostream> 

ExamDetails::ExamDetails(int course_id, int month, int day, double hour, int length, std::string link = ""):
    course_id(course_id)
{
    // exceptions
    if (month < 1 || month > 12 || day < 1 || day > 30)
        throw ExamDetails::InvalidDateException;

    if (hour < 0 || hour >= 24 || ((hour%1 != 0) && (hour%1 != 0.5))
        throw ExamDetails::InvalidTimeException;
    
    if (length%1 != 0)
        throw ExamDetails::InvalidArgsException;

    // assigning the values
    this->month = month;
    this->day = day;
    this->hour = hour;
    this->length = length;
    this.link = link;
}


int main()
{
    ExamDetails e(104032, 7, 11, 9.5, 3);
    return 0;
}

/*
std::string ExamDetails::getLink()
{
    return this->link;
}
*/
