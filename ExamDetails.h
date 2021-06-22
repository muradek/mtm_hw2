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
    // ExamDetails C'tor
    ExamDetails(int course_id, int month, int day, double hour, int length, std::string link = "");
    // ExamDetails D'tor
    ~ExamDetails() = default;
    // copy C'tor
    ExamDetails(const ExamDetails& exam) = default;
    // assignment operator
    ExamDetails& operator=(const ExamDetails& exam) = default;
    // returns exam's link
    std::string getLink() const;
    // sets exam's link
    void setLink(std::string link);
    // returns date difference between 2 exams
    int operator- (ExamDetails exam);
    // returns true if left exam is earlier than right exam
    bool operator< (ExamDetails exam);
    // printing method for ExamDetails
    friend std::ostream& operator<<(std::ostream& os, const ExamDetails& ed);
    // static MTM C'tor
    static ExamDetails makeMatamExam();
    // exceptions
    class InvalidDateException{};
    class InvalidTimeException{};
    class InvalidArgsException{};
};

#endif // EXAMDETAILS_H_
