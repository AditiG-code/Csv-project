#include "Tokenizer.h"

#include<cctype> //for isalpha ,is digit
#include<stdexcept> //for runtime error

Tokenizer::Tokenizer(const std::string&query)
    : query(query), position(0) {}

char Tokenizer::peek() const{
    if(isAtEnd()) return '\0';
    return query[position];
}
char Tokenizer::advance() {
    if(isAtEnd()) return '\0';
    return query[position++];
}
bool Tokenizer::isAtEnd() const {
    return position>= query.length();
}

void Tokenizer::skipWhitespace(){
    while(!isAtEnd() && std::isspace(peek())){
        advance();
    }
}
//reading idenstifiers and keywords
Token Tokenizer::readIdentifierOrKeyword(){
    size_t start=position;
    while(!isAtEnd() && (std::isalnum(peek()) || peek()=='_' || peek()=='.')){
        advance();
    }
    std::string text=query.substr(start,position-start);

    if(text=="SELECT") return {TokenType::SELECT,text};
    if(text=="FROM") return {TokenType::FROM,text};
    if(text=="WHERE") return {TokenType::WHERE,text};
    if(text=="AND") return {TokenType::AND,text};
    if(text=="OR") return {TokenType::OR,text};

    return {TokenType::IDENTIFIER, text};

}

Token Tokenizer::readNumber(){
    size_t start=position;
    while(!isAtEnd() && std::isdigit(peek())){
        advance();
    }

std::string value=query.substr(start,position-start);
return {TokenType::NUMBER,value};

}

Token Tokenizer::readString(){
    advance(); //skip start quote
    size_t start=position;
    while(!isAtEnd() && peek()!='"'){
        //read content till closing quote
        advance();
    }
    if(isAtEnd()){
        throw std::runtime_error("Unterminated string literal");
    }
    
    std::string value=query.substr(start,position-start);
    advance(); //skip closing quote

    return {TokenType::STRING, value};

}
Token Tokenizer::readOperator(){
    char op=advance();
    std::string value(1,op);
    return {TokenType::OPERATOR,value};
}
//main function that will decide every word
std::vector<Token> Tokenizer::tokenize(){
    std::vector<Token>tokens;
    while(!isAtEnd()){
        skipWhitespace();
        if(isAtEnd()) break;

        char c=peek();

        if(std::isalpha(c)){
            tokens.push_back(readIdentifierOrKeyword());
        }
        else if(std::isdigit(c)){
            tokens.push_back(readNumber());
        }
        else if(c=='"'){
            tokens.push_back(readString());
        }
        else if(c==','){
            advance();
            tokens.push_back({TokenType::COMMA,","});
        }
        else if(c=='*'){
            advance();
            tokens.push_back({TokenType::STAR,"*"});
        }
        else if(c=='='||c=='<'||c=='>'){
            tokens.push_back(readOperator());
        }
        else {
            throw std::runtime_error(std::string("Unexpected character: ")+c);
        }
    }

    tokens.push_back({TokenType::END, ""});
    return tokens;
}
