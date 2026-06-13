# Inverted-Search
Inverted Search Engine in C using hash tables and linked lists for efficient keyword indexing and retrieval.

The Inverted Search Engine is a C-based application that creates an inverted index from multiple text files, enabling fast and efficient keyword-based searches. Instead of scanning every file for each search query, the application builds a data structure that maps words to the files in which they appear, significantly improving search performance.

This project demonstrates the practical use of data structures such as hash tables and linked lists, along with file handling and string processing techniques in C.

## Features

* Create an inverted index from multiple text files
* Search for keywords efficiently
* Display files containing the searched keyword
* Store word occurrences and file information
* Handle multiple files dynamically
* Fast retrieval using hash-based indexing

## Technologies Used

* C Programming
* Hash Tables
* Linked Lists
* File Handling
* String Manipulation
* Dynamic Memory Allocation

## How It Works

1. Reads data from multiple text files.
2. Extracts and processes individual words.
3. Creates an inverted index mapping words to corresponding files.
4. Searches keywords using the generated index.
5. Displays matching file information and occurrence details.

## Compilation

gcc *.c -o inverted_search

## Execution

./inverted_search file1.txt file2.txt file3.txt

## Learning Outcomes

* Implementation of hash tables and linked lists
* Efficient searching and indexing techniques
* File handling and text processing in C
* Dynamic memory management
* Real-world application of data structures

## Future Enhancements

* Case-insensitive searching
* Phrase-based search support
* Index persistence using files
* Ranking search results based on keyword frequency
* Graphical User Interface (GUI)
