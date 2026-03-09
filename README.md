
# CSV-SQL Engine (C++)

A lightweight SQL-like query engine written in C++ that executes SELECT queries on CSV file using only the C++ Standard Library.

This project demonstrates how a basic query engine works internally using:
-Tokenization
-Parsing
-Query execution
-CSV data processing

## Features
- SELECT specific columns
- Select *
- WHERE clause with comparison operators
- Numeric comparisons
- String comparisons
- CSV file parsing

```md
## Example
```sql
SELECT name, FROM sample.csv WHERE age > 21;
