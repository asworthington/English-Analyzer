/*
File: EnglishLab.cpp
Author: Alex Worthington
This program prompts the user for a paragraph from a file and outputs the number of characters,
words, sentences, simple and complex sentences, "to be" verbs, and the average words in a sentence.
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <iomanip>
using namespace std;

const int MAX_WORD_CHARS = 50; // longest word = 50 chars
const int MAX_WORDS = 1000;    // longest paragraph = 100 words
const int MAX_SENTENCES = 100; 
const int NUM_PUNCTUATIONS = 3;  
const char PUNCTUATIONS[] = { '.', '?', '!' };
const int NUM_TO_BE_VERBS = 5;
const char TO_BE_VERBS[NUM_TO_BE_VERBS][MAX_WORD_CHARS] = 
   { "am", "are", "is", "was", "were" }; 
const int MAX_PARAGRAPH_CHARS = 50000; // 50 * 1000 // max number of sentences in paragraph 
const char BE[] = "be"; 
const char TO[] = "to"; 
const char COMMA[] = ","; 
const int NUM_CONJUNCTIONS = 7; // conjunctions 
const char CONJUNCTIONS[NUM_CONJUNCTIONS][5] = {"for", "and", "nor", "but", "or", "yet", "so" };

bool checkFile(const char* inputfile); 
int tokenizeParagraph(char p[], char tp[][MAX_WORD_CHARS]); 
int countSentences(char p[]); 
int countToBeVerbs(char tp[][MAX_WORD_CHARS], int numWords); 
int countComplexSentences( char tp[][MAX_WORD_CHARS], int numWords);

int main()
{
   ifstream input;
   char inputfile[256];
   char p[MAX_WORDS];
   char tp[MAX_WORDS][MAX_WORD_CHARS];
   char c;
   cout << "Welcome to the English Analyzer." << endl;
   cout << "Enter file name: ";
   cin >> inputfile;
  
   // check for empty/non-existent file
   if (checkFile(inputfile) == false)
   {
      cout << "Thank you for using the English Analyzer." << endl;
      return 0;
   }
   input.open(inputfile);
 
   // get data
   input.getline(p, MAX_PARAGRAPH_CHARS);
   int numChars = strlen(p);
   double numSentences = countSentences(p);
   double numWords = tokenizeParagraph(p, tp);
   double avgWords = numWords/numSentences; 
   int numComplex = countComplexSentences(tp, numWords);
   int numToBe = countToBeVerbs(tp, numWords);
   int numSimple = numSentences-numComplex;
                
   // prints data
   cout << "Number of characters: " << numChars << endl;
   cout << "Number of words: " << numWords << endl;
   cout << "Number of sentences: " << numSentences << endl;
   cout << "Average number words in a sentence: " << fixed << setprecision(1)<< avgWords << endl;
   cout << "Number of simple sentences: " << numSimple << endl;
   cout << "Number of complex sentences: " << numComplex << endl;
   cout << "Number of 'to be' verbs: " << numToBe << endl;
   input.close(); 
   cout << "Thank you for using the English Analyzer." << endl;
   return 0;
}

/* tokenizeParagraph: takes an array of sentences and splits them
   up by white space.
   Parameters:
        p: the array holding the paragraph
        tp: the "tokenized" paragraph. A 2D array of words with punctuation.
   Pre-condition: p has a valid paragraph in it and tp has been allocated space
   Post-condition: tp has been filled with all words/punctuation
       p no  longer has the paragraph in it
   Returns: the number of words in paragraph
*/
int tokenizeParagraph( char p[], char tp[][MAX_WORD_CHARS] )
{
   int i = 0;
   char* cPtr;
   cPtr = strtok( p, " \n\t");
   while( cPtr != NULL )
   {
      strcpy( tp[i], cPtr );
      i++;
      cPtr= strtok( NULL, " \n\t");
   }
   return( i );
}

/* checkFile: checks whether inputfile exists or if it's empty
   Parameter:
      inputfile: filename
   Returns: true if file contains no errors. false if file contains errors.
*/
bool checkFile(const char* inputfile)
{
   char c;
   ifstream input;
   input.open(inputfile);
   if(input.fail()) // check if file exists
   {
      cout << "Input file " << inputfile << " does not exist.\n";
      return false;
   }
   else 
   {
      input.get(c);
      if (input.eof()) // check if file is empty
      {
         cout << "Input file " << inputfile << " is empty.\n";
         input.close();
         return false;
      }
      return true;	
   }
}

/* countToBeVerbs: counts the number of to be verbs
   Parameters:
      tp: the "tokenized" paragraph. A 2D array of words with punctuation.
      numWords: number of words
   Returns: numToBe (number of to be verbs)
*/
int countToBeVerbs(char tp[][MAX_WORD_CHARS], int numWords)
{
   int numToBe = 0;
   for(int i=0; i<numWords; i++)
   {
      for(int j=0; j<NUM_TO_BE_VERBS; j++)
      {
         if(strcmp(tp[i], TO_BE_VERBS[j]) == 0 ||
            strcmp(tp[i], TO) == 0 || 
            strcmp(tp[i], BE) == 0)
         {
            numToBe++;
            break;
         }
      }
   }
   return numToBe;
}

/* countSentences: counts the number of sentences in paragraph
   Parameter:
      p: contains the inputfile paragraph
   Precondiiton: p contains the text from the inputfile
   Returns: numSentences (the number of sentences)
*/
int countSentences(char p[])
{
   int numSentences = 0;
   for(int i = 0; p[i] != '\0'; i++)
   {
      if(p[i] == '.' ||
         p[i] == '?' ||
         p[i] == '!')
      {
         numSentences++;
      }
   }
   return numSentences;
}

/* countComplexSentences: counts the number of complex sentences in a paragraph
   Parameters:
      tp: the "tokenized" paragraph. A 2D array of words with punctuation.
      numWords: number of words
   Returns: numComplex (number of complex sentences)
*/
int countComplexSentences( char tp[][MAX_WORD_CHARS], int numWords)
{
   int numComplex = 0;
   for(int i=0; i<numWords; i++)
   {
      for(int j=0; j<NUM_CONJUNCTIONS; j++)
      {
         if(strcmp(tp[i], CONJUNCTIONS[j]) == 0) // if conjunction
         {
            if(tp[i-1][strlen(tp[i-1])-1] == ',') // if the end of the previous word was a comma 
            {
               numComplex++;
            }
         }
      }    
   }
   return numComplex++;
}
