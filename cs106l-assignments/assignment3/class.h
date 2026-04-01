#include<string>

class Class{
    private:
        std::string name;
        std::string teacher;
        int studentsNumber;
        void toNewSemester();
    public:
        Class(const std::string &name,const std::string &teacher,const int studentsNumber):name(name),teacher(teacher),studentsNumber(studentsNumber){};
        Class():studentsNumber(0){};
        int getNumber()const;
        void setNumber(int number);
};