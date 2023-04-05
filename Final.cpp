#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <cstdio>
#include <limits>

//? SKIP THIS: Για καλύτερο debugging έφτιαξα εναν custom logger
//? Η Κλάση Student ξεκινάει στην γραμμή 54
enum LState { Testing, Production };
enum LType { Default, Info, Success, Warning, Error, Debug };
enum LColor { None, White, Green, Yellow, Red, Blue, Grey };

//? Να ρωτήσω αν υπάρχει καλύτερος τρόπος
// #define LInfo Logger::setType(LType::Info)
// #define LSuccess Logger::setType(LType::Success)
// #define LWarning Logger::setType(LType::Warning)
// #define LError Logger::setType(LType::Error)
// #define LDebug Logger::setType(LType::Debug)

class Logger
{
    private:
        const char* types[6] = {"\u001b[0m", "\u001b[37;1m[Info]: \u001b[0m", "\u001b[32;1m[Success]: ", "\u001b[33;1m[Warning]: ", "\u001b[31m[Error]: ", "\u001b[36;1m[Debug]: "};
        const char* colors[7] = {"\u001b[0m", "\u001b[37;1m", "\u001b[32;1m", "\u001b[33;1m", "\u001b[31m", "\u001b[36;1m", "\u001b[30m"};

    private:
        const LState mState;
        std::ostream& mStream;
        LType mType;
        LColor mColor;
        bool mTyped, mPrefixed, mColored;

    public:
        Logger(std::ostream& stream, LState state);
        ~Logger();

        Logger& setType(const LType& type);
        Logger& operator << (const LType& type);

        Logger& setColor(const LColor& color);
        Logger& operator << (const LColor& color);

        Logger& operator << (std::ostream& (*data)(std::ostream&));

        template<typename T>           
        Logger& operator << (const T& data);
};

//!IMPORTANT: Ρυθμήσεις του logger (Production εμφανήζει μόνο Info, Success, Warning) (Testing εμφανίζει Error, Debug)
//!Keep this global
Logger lout = Logger(std::cout, LState::Testing);

class Student 
{
	private:
		char* AM;
		std::string fullName;
		unsigned int currentSemester;
		
	public:
		Student(const char* AM, const std::string fullName, unsigned int currentSemester);
		Student(const Student& otherStudent);

        ~Student();
		
		void setAM(const char* AM);
		void setFullName(const std::string fullName);
		void setCurrentSemester(const unsigned int currentSemester);
		
		char* getAM() const;
		std::string getFullName() const;
		unsigned int getCurrentSemester() const;

        Student& incrementSemester();
        Student& incrementSemesterBy(const unsigned int amount);
        Student& decrementSemesterBy(const unsigned int amount);

        Student& operator ++ ();
        const Student operator ++ (int);

        Student& operator += (const unsigned int amount);
        Student& operator -= (const unsigned int amount);

        void printAll() const;

        friend std::ostream& operator << (std::ostream& output, const Student& student);
        friend std::istream& operator >> (std::istream& input, Student& student);
};

//?SKIP THIS: Επισης ευτιαξα ενα custom menu για την καλυτερη παρουσιαση των δυνατοτητων του προγραμματος και της κλασης Student
//?Το implementation της κλασης Student συνεχιζει στη γραμη 126
enum MPage { Home, CreateStudent, ChangeStudent, ShowStudent, CopyStudent, Exit };

class Menu
{
    private:
        int mCurrentPage, mStudentsCount;
        Student** mStudentsArray;

    public:
        Menu();
        ~Menu();

        int getCurrentPage() const;
        void setCurrentPage(const int page);

        template <typename Type>
        Type InputOfType() const;
        int Selection() const;
        bool Confirm() const;

        Student createStudent();
        int selectStudent() const;
        bool hasStudents() const;
        bool addStudent();
        bool addStudent(Student& student);
        bool copyStudent(int student);
        bool changeStudent(int student);
        void showStudent(int student) const;
};

//!Keep this global
Menu menu = Menu();

Student::Student(const char* AM, const std::string fullName, unsigned int currentSemester = 1)
{
    lout << LType::Debug << "(Student: " << AM << ") " << " Constructor" << std::endl;
    this->AM = new char[strlen(AM) + 1];
	strcpy(this->AM, AM);
	this->fullName = fullName;
	this->currentSemester = currentSemester;
};

Student::Student(const Student& otherStudent)
{
    lout << LType::Debug << "(Student: " << AM << ") " << " Copy Constructor" << std::endl;
	memcpy(this, &otherStudent, sizeof(Student));
};

Student::~Student()
{
    lout << LType::Debug << "(Student: " << AM << ") " << " Destructor" << std::endl;
    delete[] AM;
}

void Student::setAM(const char* AM)
{
    delete[] this->AM;
	this->AM = new char[strlen(AM) + 1];
	strcpy(this->AM, AM);
};

void Student::setFullName(const std::string fullName)
{
	this->fullName = fullName;
};

void Student::setCurrentSemester(const unsigned int currentSemester)
{
	this->currentSemester = currentSemester;
};

char* Student::getAM() const
{
	return AM;
};

std::string Student::getFullName() const
{
	return fullName;
};

unsigned int Student::getCurrentSemester() const
{
	return currentSemester;
};

Student& Student::incrementSemester()
{
    currentSemester++;
    return *this;
};

Student& Student::incrementSemesterBy(const unsigned int amount)
{
    currentSemester += amount;
    return *this;
};

Student& Student::decrementSemesterBy(const unsigned int amount)
{
    currentSemester -= amount;
    return *this;
}

Student& Student::operator ++ ()
{
    return incrementSemester();
};

const Student Student::operator ++ (int)
{
    const Student oldStudent = *this;
    currentSemester++;
    return oldStudent;
};

Student& Student::operator += (const unsigned int amount)
{
    return incrementSemesterBy(amount);
};

Student& Student::operator -= (const unsigned int amount)
{
    return decrementSemesterBy(amount);
};

void Student::printAll() const {
    std::cout << *this;
};

std::ostream& operator << (std::ostream& output, const Student& student)
{
    return output
        << std::endl
        << "-------------------------------------\n"
        << std::right << std::setw(26) << std::setfill(' ') << "Στιχοία Φοιτητή" << "\n"
        << "-------------------------------------\n"
        << std::left << "ΑΜ: " << std::right << std::setw(33) << std::setfill('.') << student.getAM() << "\n"
        << std::left << "Ονομ/νυμο: " << std::right << std::setw(26) <<  std::setfill('.') << student.getFullName()  << "\n"
        << std::left << "Τρέχων Εξάμηνο: " << std::right << std::setw(21) <<  std::setfill('.') << student.getCurrentSemester() << std::endl;
};

std::istream& operator >> (std::istream& input, Student& student)
{
    lout << LColor::White << "Παρακαλώ εισάγετε ΑΜ: ";
    std::string tmpAM = menu.InputOfType<std::string>();

    lout << LColor::White << "Παρακαλώ εισάγετε Ονομ/νυμο: ";
    std::string fullName = menu.InputOfType<std::string>();

    lout << LType::Info << "Θέλετε να εισάγετε Τρέχων Εξάμηνο? (Προ/εγμένο 1)" << std::endl;
    unsigned int currentSemester = 1;

    if (menu.Confirm())
    {
        lout << LColor::White  << "Παρακαλώ εισάγετε Τρέχων Εξάμηνο: ";
        currentSemester = menu.InputOfType<unsigned int>();
    }

    const char* AM = tmpAM.c_str();
    student.setAM(AM);
    student.setFullName(fullName);
    student.setCurrentSemester(currentSemester);

    return input;            
}

int main()
{
    system ("chcp 1253");

    do
    {
        menu.setCurrentPage(menu.Selection());
        switch(menu.getCurrentPage())
        {
            case MPage::CreateStudent:
            {
                if (menu.addStudent())
                    lout << LType::Success << "Ο Φοιτητής προστέθηκε με επυτηχία!" << std::endl;
                else
                    lout << LType::Error << "Failed to add student" << std::endl;
            }
            break;

            case MPage::ChangeStudent:
            {
                if (menu.hasStudents())
                {
                    if (menu.changeStudent(menu.selectStudent()))
                        lout << LType::Success << "Ο Φοιτητής άλλαξε με επυτηχία!" << std::endl;
                    else
                        lout << LType::Error << "Failed to change student" << std::endl;
                }
                else
                    lout
                    << LType::Warning << "Δεν υπάρχουν φοιτητές!" << std::endl
                    << LType::Info << "δημιουργήστε εναν φοιτητή και δοκιμάστε ξανά." << std::endl;
            }
            break;

            case MPage::ShowStudent:
            {
                if (menu.hasStudents())
                    menu.showStudent(menu.selectStudent());
                else
                    lout
                    << LType::Warning << "Δεν υπάρχουν φοιτητές!" << std::endl
                    << LType::Info << "δημιουργήστε εναν φοιτητή και δοκιμάστε ξανά." << std::endl;
            }
            break;

            case MPage::CopyStudent:
            {
                if (menu.hasStudents())
                    if (menu.copyStudent(menu.selectStudent()))
                        lout << LType::Success << "Οι Φοιτητές αντιγράφηκαν με επυτηχία!" << std::endl;
                    else
                        lout << LType::Error << "Failed to add student" << std::endl;
                else
                    lout
                    << LType::Warning << "Δεν υπάρχουν φοιτητές!" << std::endl
                    << LType::Info << "δημιουργήστε εναν φοιτητή και δοκιμάστε ξανά." << std::endl;
            }
            break;

            case MPage::Exit:
                return 0;
            
            default:
                break;
        }
    }
    while (true);

    return 0;
}

Logger::Logger(std::ostream& stream = std::cout, LState state = LState::Production)
    : mStream(stream),
    mState(state),
    mTyped(false),
    mPrefixed(false),
    mColored(false),
    mType(LType::Default),
    mColor(LColor::None)
{
    lout << LType::Debug << "(Logger) Constructor" << std::endl;
}

Logger::~Logger()
{
    lout << LType::Debug << "(Logger) Destructor" << std::endl;
}

Logger& Logger::setType(const LType& type)
{
    mTyped = true;
    mType = type;
    mPrefixed = false;
    return *this;
}

Logger& Logger::operator << (const LType& type)
{
    return setType(type);
}

Logger& Logger::setColor(const LColor& color)
{
    mColored = true;
    mColor = color;
    return *this;
}

Logger& Logger::operator << (const LColor& color)
{
    return setColor(color);
}


Logger& Logger::operator << (std::ostream& (*data)(std::ostream&))
{
    if (mTyped) {
        mTyped = false;
        mType = LType::Default;
        mStream << colors[LColor::None] << data;
    }
    else
        mStream << data;

    return *this;
}

template<typename T>           
Logger& Logger::operator << (const T& data) 
{
    if (mColored && !mTyped) {
        mStream << colors[mColor] << data;
        mColored = false;
        return *this;
    }

    if (mState == LState::Production && mType >= LType::Error) {
        return *this;
    }

    //TODO: Check for (\n std::flush) instead of std::endl
    if (mTyped && !mPrefixed)
    {
        mStream << types[mType] << data;
        mPrefixed = true;
    }
    else
        mStream << data;
    
    return *this;
}

Menu::Menu()
    :mCurrentPage(MPage::Home),
    mStudentsCount(0)
{
    lout << LType::Debug << "(Menu) Constructor" << std::endl;
}

Menu::~Menu()
{
    if (mStudentsCount > 0)
    {
        lout << LType::Debug << "(Menu) Destructor" << std::endl;
        //? Ερώτηση αν χρειάζετε να κάνω delete κάθε φοιτητή ξεχωριστά ή μόνο όλο το array
        // for (int i = 0; i < mStudentsCount; i++)
        // {
        //     delete[] &mStudentsArray[i];
        // }
        delete[] mStudentsArray;
    }
}
int Menu::getCurrentPage() const
{
    return mCurrentPage;
}

void Menu::setCurrentPage(const int page)
{
    mCurrentPage = page;
}

bool Menu::addStudent()
{
    if (mStudentsCount > 0)
    {
        Student** tmpArray = mStudentsArray;
        //? Ερώτηση αν χρειάζετε να κάνω delete το array πρίν το ξανά κάνω
        // delete[] mStudentsArray;
        mStudentsArray = new Student*[++mStudentsCount];
        mStudentsArray = tmpArray;
        //? Ερώτηση αν χρειάζετε να κάνω delete το temp array
        // delete[] *tmpArray;
        mStudentsArray[mStudentsCount-1] = new Student(createStudent());
        return true;
    }
    else
    {
        mStudentsArray = new Student*[++mStudentsCount];
        mStudentsArray[mStudentsCount-1] = new Student(createStudent());
        return true;
    }
    return false;
}

bool Menu::addStudent(Student& student)
{
    if (mStudentsCount > 0)
    {
        Student** tmpArray = mStudentsArray;
        //? Ερώτηση αν χρειάζετε να κάνω delete το array πρίν το ξανά κάνω
        // delete[] mStudentsArray;
        mStudentsArray = new Student*[++mStudentsCount];
        mStudentsArray = tmpArray;
        //? Ερώτηση αν χρειάζετε να κάνω delete το temp array
        // delete[] *tmpArray;
        mStudentsArray[mStudentsCount-1] = new Student(student);
        return true;
    }
    else
    {
        mStudentsArray = new Student*[++mStudentsCount];
        mStudentsArray[mStudentsCount-1] = new Student(student);
        return true;
    }
    return false;
}

bool Menu::hasStudents() const
{
    return (mStudentsCount > 0);
}

int Menu::Selection() const
{
    lout
    << std::endl << LColor::White
    << "-------------------------------------\n"
    << std::right << std::setw(22) << std::setfill(' ') << "’σκηση 2" << "\n"
    << "-------------------------------------\n" << LColor::None
    << std::left << "Προσθήκη φοιτητή" << std::right << std::setw(22) << std::setfill('.') << "(1)\n";

    if (!menu.hasStudents())
    {
        lout << LColor::Grey;
    }

    lout
    << std::left << "Αλλαγή στοιχείων φοιτητή" << std::right << std::setw(14) <<  std::setfill('.') << "(2)\n"
    << std::left << "Εμφάνηση στοιχείων φοιτητή" << std::right << std::setw(12) <<  std::setfill('.') << "(3)\n"
    << std::left << "Αντιγραφή φοιτητή" << std::right << std::setw(21) <<  std::setfill('.') << "(4)\n";

    lout
    << LColor::None
    << std::left << "Έξοδος" << std::right << std::setw(32) <<  std::setfill('.') << "(5)\n"
    << std::endl
    << LType::Info << "Επιλέξτε ενέργεια: ";

    return InputOfType<int>();
}

template <typename Type>
Type Menu::InputOfType() const
{
    Type input;
    while (!(std::cin >> input))
    {
        lout << LType::Warning << "Μη αποδεκτή τιμή!" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return input;
}

bool Menu::Confirm() const
{
    lout << LType::Info << "Παρακαλώ εισάγετε (y|n): " << LType::Default;
    std::string input = InputOfType<std::string>();
    while (input != "y" && input != "n")
    {
        lout << LType::Warning << "Αποδεκτές τημές (y|n): " << std::endl;
        input = InputOfType<std::string>();
    }
    return input == "y" ? true : false;
}

Student Menu::createStudent()
{
    lout 
    << std::endl << LColor::Green
    << "-------------------------------------\n"
    << std::right << std::setw(28) << std::setfill(' ') << "Δημιουργεία Φοιτητή" << "\n"
    << "-------------------------------------\n" << LColor::None << std::endl;

    Student student = Student("","");
    std::cin >> student;
    
    return student;
}

void Menu::showStudent(int student) const
{
    if (student == mStudentsCount)
    {
        for (int i = 0; i < mStudentsCount; i++)
        {
            lout << *mStudentsArray[i];
        }
    }
    else
    {
        lout << *mStudentsArray[student];
    }
}

int Menu::selectStudent() const
{
    lout
    << std::endl << LColor::White
    << "-------------------------------------\n"
    << std::right << std::setw(28) << std::setfill(' ') << "Διαθέσημοι Φοιτητές" << "\n"
    << "-------------------------------------\n" << LColor::None;

    std::string strCount;
    for (int i = 0; i < mStudentsCount; i++)
    {
        strCount = std::to_string(i);
        char* tmpAM = mStudentsArray[i]->getAM();
        lout << std::left << "ΑΜ: " << tmpAM << std::right << std::setw(32-strlen(tmpAM)-strCount.length()) <<  std::setfill('.') << "(" << i << ")\n";
        //? Ερώτηση αν πρέπει να κάνω delete το tmpAM
        // delete[] tmpAM;
    }

    strCount = std::to_string(mStudentsCount);
    lout
    << std::left << "Επιλογή όλων" << std::right << std::setw(24-strCount.length()) <<  std::setfill('.') << "(" << mStudentsCount << ")" << std::endl
    << LType::Info << "Επιλέξτε ενέργεια: ";

    return InputOfType<int>();;
}

bool Menu::changeStudent(int student)
{
    lout 
    << std::endl << LColor::Green
    << "-------------------------------------\n"
    << std::right << std::setw(26) << std::setfill(' ') << "Αλλαγή Φοιτητητών" << "\n"
    << "-------------------------------------\n" << LColor::None << std::endl;

    if (student == mStudentsCount)
    {
        for (int i = 0; i < mStudentsCount; i++)
        {
            lout << LType::Info << "(Φοιτητής) ΑΜ: " << mStudentsArray[i]->getAM() << std::endl;
            if(std::cin >> *mStudentsArray[student])
                return true;
            else
                return false;
        }
    }
    else
    {
        lout << LType::Info << "(Φοιτητής) ΑΜ: " << mStudentsArray[student]->getAM() << std::endl;
        if(std::cin >> *mStudentsArray[student])
            return true;
    }
    return false;
}

bool Menu::copyStudent(int student)
{
    lout 
    << std::endl << LColor::Green
    << "-------------------------------------\n"
    << std::right << std::setw(26) << std::setfill(' ') << "Αντιγραφή Φοιτητητών" << "\n"
    << "-------------------------------------\n" << LColor::None << std::endl;

    if (student < mStudentsCount)
    {
        lout << LType::Info << "(Αντιγραφή Φοιτητή) ΑΜ: " << mStudentsArray[student]->getAM() << std::endl;
        if(addStudent(*mStudentsArray[student]))
            return true;
        else
            return false;
    }

    const int tmpSize = mStudentsCount;
    const int newSize = mStudentsCount * 2;
    
    Student** tmpArray = mStudentsArray;
    //? Ερώτηση αν χρειάζετε να κάνω delete το array πρίν το ξανά κάνω
    // delete[] mStudentsArray;
    mStudentsArray = new Student*[newSize];
    mStudentsArray = tmpArray;
    //? Ερώτηση αν χρειάζετε να κάνω delete το temp array
    // delete[] *tmpArray;
    for (int i = 0; i < tmpSize; ++i)
    {
        lout << LType::Info << "(Αντιγραφή Φοιτητή) ΑΜ: " << mStudentsArray[i]->getAM() << std::endl;

        mStudentsArray[mStudentsCount] = new Student((Student&)(*mStudentsArray[i]));
        mStudentsCount++;
    }

    return true;
}
