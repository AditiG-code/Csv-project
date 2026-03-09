#include "Executor.h"
#include<iostream>
#include<algorithm>
#include<stdexcept> //throws runtime error for invalid req

Executor::Executor(const Query& query,const CSVReader& reader) :query(query),reader(reader){}
void Executor::execute() const{
    const auto& headers=reader.getHeaders();
    const auto& rows=reader.getRows();

    //map index to headers ,this vector will return required col name index
    std::vector<int>selectedIndexes=getSelectedColumnIndexes(headers);

    // now to print name of that ind
    for(int ind:selectedIndexes){
        std::cout<<headers[ind]<<"\t"; //"\t" print tab space btw results (name     age)
        
    }
    std::cout<<"\n";

    //to check where condition iterate overs rows
    //so that we can filter which row has the req answer
    for(const auto& row:rows){
        if(query.hasWhere){ //query has where condition then evaluate this condition
            if(!evaluateWhereCondition(row,headers)) continue; //if where cond not match skip 
        }
        // else keep all rows since no where condition is there in query
        for(const auto& ind:selectedIndexes){
        std::cout<<row[ind]<<"\t";
        }
        std::cout<<"\n";
    }
    //print rows value using ind
    
}
std::vector<int>Executor::getSelectedColumnIndexes(
    const std::vector<std::string>&headers)const{

        std::vector<int>indexes;
        //select *
        if(query.selectColumns.size()==1 && query.selectColumns[0]=="*"){
           
            for(size_t i=0;i<headers.size();i++){
                indexes.push_back(i);
            }
            return indexes;
        }
            
        for(const auto& col:query.selectColumns){
            auto it=std::find(headers.begin(),headers.end(),col);
            if(it==headers.end()){
                throw std::runtime_error("Unknown column in SELECT "+col);
            }
            indexes.push_back(it-headers.begin());
        }
        return indexes;
}
    
        //where condition
    bool Executor::evaluateWhereCondition(
        const std::vector<std::string>& row,const std::vector<std::string>& headers) const{
            //find col index
            auto it=std::find(headers.begin(),headers.end(),query.whereColumn);

            if(it==headers.end()){
                throw std::runtime_error("Unknown column in WHERE "+query.whereColumn);
            }
            int colIndex=it-headers.begin();
            //cell value to compare with given value from query
            const std::string& cellValue=row[colIndex];

            const std::string &op=query.whereOperator;
            const std::string& value=query.whereValue;

            if(op=="=") return cellValue==value;

            if(op==">") return std::stod(cellValue)>std::stod(value);

            if(op=="<") return std::stod(cellValue)<std::stod(value);

            //stod -string to double conversion req for numeric comparison

            throw std::runtime_error("Unknown operator in query: "+op);

    }
        
    

