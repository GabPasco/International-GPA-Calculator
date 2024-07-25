#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector> // I need this to make the Subjects array dynamic
#include "Tools.h"

const char* Subjects_Base[] = { "Math",  "Biology", "Chemistry",
                                "Physics", "History", "Geography",
                                "Sociology", "Philosophy", "Native Language",
                                "Extra Language"};

std::vector<std::string> Subjects;

void GetSubjects()
{
    if (!std::filesystem::exists("Subjects.txt"))
    {
        std::ofstream Subjects_File_Write("Subjects.txt"); //Creates and opens the file to write the base subjects

        Subjects_File_Write << "-"; //To make it look better at the file

        for (int i = 0; i < std::size(Subjects_Base); i++) //Writing the base subjects
        {
            Subjects_File_Write << Subjects_Base[i];
            Subjects.push_back(Subjects_Base[i]);

            Subjects_File_Write << "-";
        }

        Subjects_File_Write.close();
    }
    else
    {
        std::ifstream Subjects_File_Read("Subjects.txt"); //Open the existing file to read

        std::string Line; //Buffer
        bool check = false; // To compensate the first -
        while (std::getline(Subjects_File_Read, Line, '-'))
        {
            if (check && Line != "\n")
                Subjects.push_back(Line);
            else
                check = true;
        }

        Subjects_File_Read.close();
    }
}

int main()
{
    GetSubjects();

    float Grade_Highest_Possible;
    float Grade_Sum = 0.f;
    float Grade_Weight_Sum = 0.f;

    Tools::ClearConsole();
    std::cout << "Welcome to the GPA calculator!\n";
    std::cout << "Enter the highest grade you can possibily get (numbers only):\n";
    std::cin >> Grade_Highest_Possible;

    for (int i = 0; i < Subjects.size(); i++)
    {
        Tools::ClearConsole();

        float GradeTemp = 0;
        float WeightTemp = 0;
        
        std::cout << "What is the weight of " << Subjects[i] << "?\n";
        std::cin >> WeightTemp;

        Tools::ClearConsole();

        while(true)
        {
            std::cout << "Type your " << Subjects[i] << " grades one by one and press enter each time. (Enter -1 once you have finished)\n";
            std::cin >> GradeTemp;
            
            if (GradeTemp == -1)
                break;

            GradeTemp = Tools::ConvertGrades(GradeTemp, Grade_Highest_Possible);
            
            Grade_Sum += GradeTemp*WeightTemp;
            Grade_Weight_Sum += WeightTemp;
            Tools::ClearConsole();
        }
    }

    std::cout << "Your GPA is " << Grade_Sum/Grade_Weight_Sum;
    #if _WIN32
        system("pause");
    #endif
}