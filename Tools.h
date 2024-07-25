
class Tools
{
public:
    static void ClearConsole()
    {
        #if _WIN32
            system("cls");
        #elif __linux__
            system("clear");
        #endif
    }
    static float ConvertGrades(float value, float highestValue) //Convert the grades to the american system
    {
        value = (value * 10) / highestValue; //Convert to 10

        if (value >= 9) //Convert to American Grade System
            return 4;
        else if (value >= 8 && value < 9)
            return 3.7;
        else if (value >= 7 && value < 8)
            return 3;
        else if (value >= 6 && value < 7)
            return 2;
        else if (value >= 5 && value < 6)
            return 1;
        else if (value < 5)
            return 0;
    }
};
