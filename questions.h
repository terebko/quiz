#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
/** It's preferred to store all questions in a vector or a list **/
class Question {
public:
    void edit(); // Allows to edit everything in the question
    void const print();    // Prints to output the question, possible answers, and the
                           // number which inidicates the correct answer in vector answers
    void ask();
    static void const saveQuestionsToFile(std::vector<Question> questions, std::string fileName = "lista_pytan.txt"); // Saves question to file

    static std::vector<Question> loadQuestionsFromFile(std::string fileName = "lista_pytan.txt");

    Question(); // Opens The Question creator and creates the question
    Question(std::string mainSentence, std::vector<std::string> answers, int correctAnswer);
    void setUserAnswer();
    void setUserAnswer(int answer);


private:
    std::string question; // It's the sentence which appears firstly
    std::vector<std::string> answers; // Store all possible answers in question
    int correctAnswer; // It's an number from 0 - (answers.length() - 1) which is an index
                       // of answers and indicates correct answer
    int userAnswer;
};
