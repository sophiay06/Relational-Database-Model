# The Relational Data Model

This project implements a simple database system using the relational data model. 
It provides basic functionality for operations like insertion, deletion, and lookup 
of tuples in a database. Additionally, the project demonstrates the use of relational 
algebra operations such as selection, projection, and join, following the requirements 
specified in the course textbook.

## Features
1. **Basic Database Operations:**
- Insert tuples into relations. 
- Delete tuples based on criteria. 
- Lookup tuples using wildcards.
2. **Query Functions:**
- Query to find a participant's race time. 
- Query to find race dates based on participant and sponsor.
3. **Relational Algebra Operations:**
- Selection, projection, and join implemented for specific queries.

## Build and Run Instructions
- **Build**: Use gcc with C99 standards and necessary flags:
```
gcc -std=c99 -Wall -Werror -o EXECUTABLE *.c
```
- **Run**: Execute the program using the compiled executable:
```
./EXECUTABLE
```

## How It Works
- Data Storage: Tuples for each relation are stored in hash tables, enabling efficient operations like insertion, deletion, and lookup. 
- Operations: Basic database operations (insert, delete, lookup) manipulate the relations, while relational algebra operations (selection, projection, join) allow advanced queries. 
- Query Navigation: Queries traverse relations using foreign key relationships to fetch and combine relevant data.