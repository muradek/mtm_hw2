#ifndef EXAMDETAILS_H_
#define EXAMDETAILS_H_

#include <string>
#include <iostream> 

class ExamDetails
{
    int course_id;
    int month;
    int day;
    double hour;
    int length;
    std::string link;

    public:
    ExamDetails(int course_id, int month, int day, double hour, int length, std::string link = "");
    ~ExamDetails() = default;
    ExamDetails(const ExamDetails& exam) = default;
    ExamDetails& operator=(const ExamDetails& exam) = default;
    std::string getLink();
    void setLink(std::string link);
    int operator- (ExamDetails exam);
    bool operator< (ExamDetails exam);
    friend std::ostream& operator<<(std::ostream& os, const ExamDetails& ed);
    static ExamDetails makeMatamExam();
    // exceptions
    class InvalidDateException{};
    class InvalidTimeException{};
    class InvalidArgsException{};
};

#endif // EXAMDETAILS_H_