#include "questions.h"

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

}






void const Question::print(){
    std::cout << question << std::endl;

    for(int i = 1; i <= answers.size(); ++i){
        std::cout << i << ") " << answers[i-1] << std::endl;
    }
}
