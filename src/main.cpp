#include <iostream>
#include <Tokenizer.h>
#include<CSVReader.h>
#include<Executor.h>
#include<Parser.h>

int main() {
    std::string input= "SELECT name FROM sample.csv WHERE country = 'India' ";

    try{
        //Tokenize
        Tokenizer tokenizer(input);
        auto tokens=tokenizer.tokenize();

        //PARSE
        Parser parser(tokens);
        Query query=parser.parse();

        //LOAD csv data  
        // load csv dynamically

        CSVReader reader("data/"+ query.fromFile);
        reader.read();

        //execute all
        Executor executor(query,reader);
        executor.execute();

    }
    catch(const std::exception& e){
        std::cerr<<"ERROR "<<e.what()<<"\n";
    }

    return 0;
}

