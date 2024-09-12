#include "CH53Utility.h"
#include <stdio.h>
#include <fstream>

std::ofstream log_file;

//void InitLogFile()
//{
//    time_t rawtime;
//    struct tm timeinfo;
//    WCHAR buffer[80];
//    time(&rawtime);
//    localtime_s(&timeinfo, &rawtime);
//    wcsftime(buffer, 80, L"%F_%H_%M_%S", &timeinfo);
//    WCHAR log_file_name[MAX_PATH];
//    wsprintfW(log_file_name, L"c:/ch53_%s.log", buffer);
//    log_file.open(log_file_name);
//    if (log_file.is_open())
//    {
//        log_file << "INIT\n";
//        log_file.flush();
//    }
//}
//
//void DeInitLogFile()
//{
//    //if (logfile) CloseHandle(logfile);
//    log_file << "DE-INIT\n";
//    log_file.flush();
//    log_file.close();
//}
//
//void WriteToLogFile(const char* str)
//{
//    // Write file, check for error
//    if (true) {
//        char tstr[4096];
//        DWORD dwBytesWritten;
//        time_t rawtime;
//        struct tm* timeinfo;
//        char buffer[80];
//        int a = 0;
//        time(&rawtime);
//        timeinfo = localtime(&rawtime);
//
//        strftime(buffer, 80, "%I:%M%p.", timeinfo);
//
//
//
//        if (log_file.is_open())
//        {
//
//            log_file << "[";
//            log_file << buffer;
//            log_file << "]";
//            log_file << str;
//            log_file << "\n";
//            log_file.flush();
//
//        }
//        sprintf(tstr, "[%s] %s \n", buffer, str);
//        printf(tstr);
//
//    }
//}

double limit(double input, double lower_limit, double upper_limit)
{
    if(input > upper_limit)
    {
        return upper_limit;
    }
    else if(input < lower_limit)
    {
        return lower_limit;
    }
    else
    {
        return input;
    }
}
