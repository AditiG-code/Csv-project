#ifndef CSV_READER_H
#define CSV_READER_H

#include<string>
#include<vector>

class CSVReader{
public:
    //TAKES CSV FILE PATH
    // constructor
    CSVReader(const std::string& filePath);
    
    //read ,parse the csv file
    void read();
    //getters
    const std::vector<std::string>& getHeaders() const;
    const std::vector<std::vector<std::string>>& getRows() const;


private:
    std::string filePath;
    std::vector<std::string> headers;
    std::vector<std::vector<std::string>> rows;
    // helper func top split csv line
    std::vector<std::string> split(const std::string& line,char delimiter) const;
};
#endif

