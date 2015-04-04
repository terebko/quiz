#include "questions.h"
#include <windows.h>
#include <sstream>
#include <fstream>
#include <assert.h>
template<typename T>
void pop_front(std::vector<T>& vec)
{
    assert(!vec.empty());
    vec.erase(vec.begin());
}
Question::Question(){
    std::cout << "Podaj tresc pytania: ";
    std::string theSentence;
    std::getline(std::cin, theSentence);
    this->question = theSentence;

    std::cout << "Teraz mozesz dodawac mozliwe odpowiedzi, kazda z nich musisz zakonczyc "
              << "enterem, a jesli chcesz zakonczyc dodawanie odpowiedzi napisz 'koniec'"
              << std::endl;
    std::string answer;
    int i = 1;
    while(true){
        std::cout << i << "): ";
        std::getline(std::cin, answer);
        ++i;
        std::transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
        if(answer == "koniec"){
            break;
        }
        else{
            this->answers.push_back(answer);
            continue;
        }
    }
    std::cout << "Podaj numer prawidlowej odpowiedzi: ";
    int correct;
    std::cin >> correct;
    this->correctAnswer = correct - 1;
    std::string clearBuffer;
    std::getline(std::cin, clearBuffer);
    this->userAnswer = -1;
}

void const Question::print(){
    std::cout << "Pytanko: " << std::endl;
    std::cout << question << std::endl;

    for(int i = 1; i <= answers.size(); ++i){
        std::cout << i << ") " << answers[i-1] << std::endl;
    }
    std::cout << correctAnswer << std::endl;
}


std::vector<Question> Question::loadQuestionsFromFile(std::string fileName){
    std::fstream source;
    source.open(fileName, std::ios::in);
    std::vector<Question> questions;
    if(source.good()){
        while(!source.eof()){
            std::string question;
            std::vector<std::string> answers;
            int correctAnswer;
      //      std::cout << "Question: " << question << std::endl;
            std::string buffer; // Buffer stores whole question, including
                                // questions, answers, correctAnswer
            std::getline(source, buffer, ';');

            // Reading question from buffer

         //   std::cout << buffer;
          //  Sleep(2000);
            question = buffer.substr(0, buffer.find('\n'));
            buffer.erase(0, buffer.find('\n'));


            // Reading correctAnswer
            correctAnswer = atoi(buffer.substr(buffer.find_last_of('\n')).c_str());
            //buffer.erase(buffer.find_last_of('\n'));
            // Reading answers
            buffer.erase(0,1);
          //  buffer.erase(buffer.find_last_of('\n'));
            while(buffer != "" && !source.eof()){
                std::string oneAnswer;
                if(buffer.find('\n') != std::string::npos){
                    oneAnswer = buffer.substr(0, buffer.find('\n'));
                    buffer.erase(0, buffer.find('\n') + 1);
                }
                else{
                    oneAnswer = buffer.substr();
                    buffer.clear();
                }
                answers.push_back(oneAnswer);
            }
            Question oneQuestion(question, answers, correctAnswer);
            questions.push_back(oneQuestion);
            }

        }
    for(int i = 1; i != questions.size()-1; ++i){
        questions[i].question = questions[i].answers[0];
        pop_front(questions[i].answers);
        questions[i].answers.pop_back();
    }
    questions[0].answers.pop_back();
    questions.pop_back();
    return questions;
}

void const Question::saveQuestionsToFile(std::vector<Question> questions, std::string fileName){
    std::fstream destination;
    destination.open(fileName, std::ios::out);
    if(destination.good()){
        for(Question question : questions){
            destination << question.question << std::endl;
            for(std::string answer : question.answers){
                destination << answer << std::endl;
            }
            destination << question.correctAnswer << ';' << std::endl;
        }
    }
    else{
        std::cout << "Cos poszlo nie tak!" << std::endl;
    }
}

Question::Question(std::string mainSentence, std::vector<std::string> answers, int correctAnswer){
    this->question = mainSentence;
    this->answers = answers;
    this->correctAnswer = correctAnswer;
    this->userAnswer = -1;
}
