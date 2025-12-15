/*
 Project Name : Chapter 7 Program 1 Exam Grader
 File Name : Chapter7Program1ExamGrader.cpp
 Programmer : Gabriel Cabral
 Date : 12/15/25
 Requirements:
 Read and process data from multiple files into arrays.
 Compare arrays to identify incorrect answers.
 Use parallel arrays to store both correct and student answers.
 Calculate percentage scores and determine pass/fail outcomes.
 Generate a formatted report showing results and missed questions.
*/

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

const int num_questions = 20;

// Functions
void getAnswers(const string& fileName, char answers[]);
void gradeExam(const char key[],
    const char student[],
    int missedQuestions[],
    char missedAnswers[][2],
    int& numMissed);
void writeReport(const int missedQuestions[],
    const char missedAnswers[][2],
    int numMissed);

int main()
{
    char correct[num_questions];
    char student[num_questions];

    int missedQuestions[num_questions];
    char missedAnswers[num_questions][2];

    int numMissed = 0;

    //key and student answers
    getAnswers("CorrectAnswers.txt", correct);
    getAnswers("StudentAnswers.txt", student);

    //compare arrays and missed question
    gradeExam(correct, student, missedQuestions, missedAnswers, numMissed);

    //formatted report
    writeReport(missedQuestions, missedAnswers, numMissed);
    return 0;
}
// gets answers
// Reads exam answers from file into array of chars
// Aborts 
void getAnswers(const string& fileName, char answers[])
{
    ifstream inFile;
    inFile.open(fileName);

    if (!inFile)
    {
        cout << "Error: could not open file " << fileName << endl;
        exit(1);
    }

    for (int i = 0; i < num_questions && inFile; i++)
    {
        inFile >> answers[i];
    }

    inFile.close();
}
// gradeExam
// Compares answer key to student answers
// Stores missed question numbers in missedQuestions
// stores correct and student answers 
// numMissed is updated with the total number of misses
void gradeExam(const char key[],
    const char student[],
    int missedQuestions[],
    char missedAnswers[][2],
    int& numMissed)
{
    numMissed = 0;

    for (int i = 0; i < num_questions; i++)
    {
        if (key[i] != student[i])
        {
            missedQuestions[numMissed] = i + 1;
            missedAnswers[numMissed][0] = key[i];      // correct
            missedAnswers[numMissed][1] = student[i];  // student
            numMissed++;
        }
    }
}
// writeReport
// Calculates the score, prints total missed, percentage
// pass/fail, and a list of all missed questions
void writeReport(const int missedQuestions[],
    const char missedAnswers[][2],
    int numMissed)
{
    int numCorrect = num_questions - numMissed;
    double percentCorrect = (numCorrect * 100.0) / num_questions;

    cout << fixed << setprecision(1);

    cout << "Exam Grader Report" << endl;
    cout << "------------------" << endl;
    cout << "Total questions : " << num_questions << endl;
    cout << "Questions missed: " << numMissed << endl;
    cout << "Questions correct: " << numCorrect << endl;
    cout << "Percentage: " << percentCorrect << "%" << endl;

    if (percentCorrect >= 70.0)
        cout << "Result: PASS" << endl;
    else
        cout << "Result: FAIL" << endl;

    if (numMissed > 0)
    {
        cout << endl;
        cout << "Missed Questions" << endl;
        cout << "----------------" << endl;
        cout << left << setw(6) << "Q#"
            << setw(10) << "Correct"
            << setw(10) << "Student" << endl;
        cout << "-------------------------" << endl;

        for (int i = 0; i < numMissed; i++)
        {
            cout << left << setw(6) << missedQuestions[i]
                << setw(10) << missedAnswers[i][0]
                << setw(10) << missedAnswers[i][1]
                << endl;
        }
    }
}

