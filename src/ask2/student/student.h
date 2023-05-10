#ifndef _student_h
#define _student_h

#include <ostream>
#include <string>

namespace ask2
{
    
    class Student
    {
    private:
        char *m_AM;
        std::string m_fullName;
        unsigned int m_currentSemester;

    public:
        Student(const char *AM, std::string fullName, unsigned int currentSemester);
        Student(const Student& other);

        ~Student();

        void setAM(const char *AM);
        void setFullName(std::string fullName);
        void setCurrentSemester(unsigned int currentSemester);

        char* getAM() const;
        std::string getFullName() const;
        unsigned int getCurrentSemester() const;

        inline void incrementSemester(unsigned int amount);
        inline void decrementSemester(unsigned int amount);

        void print() const;

        Student& operator ++ ();
        Student operator ++ (int);

        Student& operator += (unsigned int value);
        Student& operator -= (unsigned int value);

        friend std::ostream& operator << (std::ostream& os, const Student& student);
    };

} // namespace ask2

#endif
