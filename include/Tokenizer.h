#ifndef TOKENIZER_H
#define TOKENIZER_H

#include<string>
#include<vector>

//defining types of tokens 
enum class TokenType{
    //BASIC
    SELECT,
    FROM,
    WHERE,
    AND,
    OR,

    IDENTIFIER, //COL NAME ,FILE NAME
    NUMBER, //NUMERIC VALUS
    STRING,

    OPERATOR, //=,> ETC
    COMMA,
    STAR, 

    END     //end of input
};

//to represent a single token
struct Token {
    TokenType type;
    std::string value;
};

//defining token class
class Tokenizer {
public:
    explicit Tokenizer(const std::string& query);

    //convert input query into tokens
    std::vector<Token>tokenize();

private:
    std::string query;
    size_t position;
    
    //character helpers
    char peek() const; //to check the current position of cursor ,if at end ,return end ,else return current position 
    
    char advance(); // moves to next postion ->same as next++
    bool isAtEnd() const;  //to check the current position is at end /to save out of bound cases

    //token readers
    void skipWhitespace();
    Token readIdentifierOrKeyword();
    Token readNumber();
    Token readString();
    Token readOperator();

};

#endif


