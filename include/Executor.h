#ifndef EXECUTOR_H
#define EXECUTOR_H

#include<vector>
#include<string>

#include "Parser.h"
#include "CSVReader.h"

class Executor{
public:
    Executor(const Query& query,const CSVReader&reader);

    //run query and print result
    void execute() const;

private:
    const Query& query;
    const CSVReader& reader;

    //helpers
    std::vector<int> getSelectedColumnIndexes(
        const std::vector<std::string>& headers
    ) const;

    bool evaluateWhereCondition(
        const std::vector<std::string>& row,
        const std::vector<std::string>& headers
    ) const;
}; 

#endif