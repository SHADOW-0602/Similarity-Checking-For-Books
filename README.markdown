# Book Similarity Analysis

This project contains a C++ program designed to analyze the similarity between multiple text files (books) based on word frequency. It calculates a similarity index between pairs of books and reports the top 10 most similar pairs.

## Overview

The program processes a list of text files, counts word frequencies (excluding common stop words), and computes a similarity index between each pair of files. The similarity index is based on the normalized frequency of shared words. The top 10 pairs with the highest similarity indices are then displayed in a formatted table.

## Features

- **Word Frequency Counting**: Reads text files, converts words to uppercase, removes punctuation, and excludes stop words (e.g., "A", "AN", "THE").
- **Similarity Index Calculation**: Computes a similarity score for each pair of files based on shared word frequencies.
- **Top 10 Similar Pairs**: Sorts and displays the 10 most similar file pairs with their similarity indices.

## Prerequisites

- **C++ Compiler**: A C++ compiler supporting C++11 or later (e.g., g++, clang++).
- **Text Files**: The text files listed in the `files` vector in `main()` must be accessible in the same directory as the executable or provide the correct file paths.

## File Structure

- **Code.cpp**: The main C++ source file containing the implementation.
- **Text Files**: A collection of `.txt` files (e.g., "Cats by Moncrif.txt", "Foxes Book of Martyrs Part 1.txt") to be analyzed.

## How to Run

1. **Compile the Program**:
   ```bash
   g++ -o book_similarity Code.cpp -std=c++11
   ```

2. **Prepare Text Files**:
   Ensure all text files listed in the `files` vector in `Code.cpp` are in the same directory as the executable or update the file paths in the code.

3. **Run the Program**:
   ```bash
   ./book_similarity
   ```

4. **Output**:
   The program will output a table of the top 10 similar book pairs, including their filenames and similarity indices.

## Code Details

- **Key Functions**:
  - `topFrequentWords`: Returns the top N frequent words from a word count map.
  - `totalWords`: Counts the total number of valid words (excluding stop words) in a file.
  - `countWords`: Counts word frequencies in a file, ignoring stop words.
  - `calculateSimilarityIndex`: Computes the similarity index between two files based on normalized word frequencies.
  - `reportTopTenSimilarPairs`: Sorts and displays the top 10 similar file pairs.

- **Stop Words**: Common words like "A", "AN", "THE", "AND", "OF", "IN" are excluded from analysis.
- **Text Processing**: Words are converted to uppercase and stripped of punctuation for consistency.
- **Similarity Metric**: The similarity index is the sum of normalized frequencies of shared words between two files.

## Example Output

```
                           Top 10 Similar Pairs
------------------------------------------------------------------------------------------
|            Book 1               |            Book 2                 | Similarity Index |
------------------------------------------------------------------------------------------
Cats by Moncrif.txt             | Les Chats par Moncrif.txt         | 0.8923
Foxes Book of Martyrs Part 1.txt| Foxes Book of Martyrs Part 2.txt  | 0.8756
...
------------------------------------------------------------------------------------------
```

## Notes

- The program assumes all text files are in a readable format and exist in the specified paths.
- The similarity index is a simple metric and may not capture semantic similarity. It is based solely on word frequency.
- Modify the `files` vector in `main()` to analyze different sets of text files.

## Limitations

- The program is case-insensitive and ignores punctuation but does not handle more complex text processing (e.g., stemming or lemmatization).
- Large text files may increase memory usage due to the storage of word frequency maps.
- The similarity index may be less meaningful for files with significantly different lengths.

## Future Improvements

- Add support for more sophisticated text preprocessing (e.g., stemming, lemmatization).
- Implement parallel processing for faster analysis of large datasets.
- Enhance the similarity metric to account for semantic relationships or context.