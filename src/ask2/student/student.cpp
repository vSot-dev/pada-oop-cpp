#include <iostream>
#include <iomanip>
#include <cstring>

#include "student.h"

namespace ask2
{

    Student::Student(const char *AM, std::string fullName, unsigned int currentSemester = 1)
    {
        m_AM = new char[strlen(AM) + 1];
        strcpy(m_AM, AM);
        m_fullName = fullName;
        m_currentSemester = currentSemester;
    }

    Student::Student(const Student& other)
    {
        m_AM = new char[strlen(other.m_AM) + 1];
        strcpy(m_AM, other.m_AM);
        m_fullName = other.m_fullName;
        m_currentSemester = other.m_currentSemester;
    }

    Student::~Student() { delete[] m_AM; }

    void Student::setAM(const char *AM)
    {
        delete[] m_AM;
        m_AM = new char[strlen(AM) + 1];
        strcpy(m_AM, AM);
    }
    void Student::setFullName(std::string fullName) { m_fullName = fullName; }
    void Student::setCurrentSemester(unsigned int currentSemester) { m_currentSemester = currentSemester; }

    char* Student::getAM() const { return m_AM; }
    std::string Student::getFullName() const { return m_fullName; }
    unsigned int Student::getCurrentSemester() const { return m_currentSemester; }

    inline void Student::incrementSemester(unsigned int amount) { m_currentSemester += amount; }
    inline void Student::decrementSemester(unsigned int amount) { m_currentSemester -= amount; }

    void Student::print() const { std::cout << *this; }

    Student& Student::operator ++ ()
    {
        ++m_currentSemester;
        return *this;
    }

    Student Student::operator ++ (int)
    {
        Student tmp(*this);
        ++m_currentSemester;
        return tmp;
    }

    Student& Student::operator += (unsigned int value)
    {
        incrementSemester(value);
        return *this;
    }
    Student& Student::operator -= (unsigned int value)
    {
        decrementSemester(value);
        return *this;
    }

    std::ostream& operator << (std::ostream& os, const Student& student)
    {
        return os
            << std::endl
            << "--------------------------------------------\n"
            << "              Στοιχεία Φοιτητή              \n"
            << "--------------------------------------------\n"
            << std::left << "ΑΜ: "
            << std::right << std::setw(40) << std::setfill('.') << student.getAM() << "\n"
            << std::left << "Ονομ/Επώνυμο: "
            << std::right << std::setw(30) <<  std::setfill('.') << student.getFullName()  << "\n"
            << std::left << "Τρέχ/Εξάμηνο: "
            << std::right << std::setw(30) <<  std::setfill('.') << student.getCurrentSemester() << '\n'
            << std::endl;
    }
    
} // namespace ask2
