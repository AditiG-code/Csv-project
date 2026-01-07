#ifndef PARSER_H
#define PARSER_H

#include<vector>
#include<string>

#include "Tokenizer.h"

struct Query{
    std::vector<std::string>selectColumns;
    std::string fromFile;

    bool hasWhere =false;
    std::string whereColumn;
    std::string whereOperator;
    std:: string whereValue;
};

//parser class
class Parser{
public:
    explicit Parser(const std::vector<Token>& tokens);

    //full sql query parser
    Query parse();

private:
    //token steam
    const std::vector<Token>& tokens;
    size_t current;

    //grammar parsing
    void parseSelect(Query& query);
    void parseFrom(Query& query);
    void parseWhere(Query& query);

    //token helpers
    const Token& peek() const;
    const Token& advance();
    bool isAtEnd() const;

    bool match(TokenType type);//mathc with declared tokens
    const Token& consume(TokenType type,const std::string& errorMessage);
};

#endif