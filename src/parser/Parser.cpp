#include "Parser.h"

Parser::Parser(const std::vector<Token>& tokens)
    : tokens(tokens),current(0) {}

const Token& Parser::peek() const{
    return tokens[current];
}
bool Parser::isAtEnd() const {
    return peek().type ==TokenType::END;
}

const Token& Parser::advance() {
    if(!isAtEnd()){
        current++;
    }
    return tokens[current-1];
}

bool Parser::match(TokenType type){
    if(peek().type==type){
        advance();
        return true;
    }
    return false;
}

const Token& Parser::consume(TokenType type,const std::string& errorMessage){
    if(peek().type==type){
        return advance();
    }
    throw std::runtime_error(errorMessage);
}

Query Parser::parse(){
    Query query;

    parseSelect(query);
    parseFrom(query);
    parseWhere(query);

    if(!isAtEnd()){
        throw std::runtime_error("Unexpected tokens after query");
    }
    return query;
}

void Parser::parseSelect(Query& query){
    consume(TokenType::SELECT,"Expected SELECT at beginning of query");

    if(match(TokenType::STAR)){
        query.selectColumns.push_back("*");
        return ;
    }
    do{
        Token column=consume(
            TokenType::IDENTIFIER,
            "Expected column name in SELECT clause"
        );
        query.selectColumns.push_back(column.value);
    
    } 
    while(match(TokenType::COMMA));
}

void Parser::parseFrom(Query& query){
    consume(TokenType::FROM,"Expected FROM after SELECT clause");
    Token file=consume(
        TokenType::IDENTIFIER,
        "Expected file name after FROM"
    );
    query.fromFile=file.value;
}

void Parser::parseWhere(Query& query){
    if(!match(TokenType::WHERE)){
        return ;
    }
    query.hasWhere=true;
    Token column=consume(
        TokenType::IDENTIFIER,
        "Expected column name in WHERE clause"
    );
    Token op=consume(
        TokenType::OPERATOR,
        "Expected operator in WHERE clause"
    );
    Token value=consume(
        TokenType::NUMBER,
        "Expected value in WHERE clause"
    );

    query.whereColumn=column.value;
    query.whereOperator=op.value;
    query.whereValue=value.value;
}



