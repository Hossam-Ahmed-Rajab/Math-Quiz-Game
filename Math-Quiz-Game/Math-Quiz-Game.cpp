#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

enum enOperation { Add = 1, Sub = 2, Mul = 3, Div = 4, MixOp = 5 };
enum enLevel { Easy = 1, Mid = 2, Hard = 3, Mix = 4 };

struct stQuestionInfo {
    int num1 = 0;
    int num2 = 0;
    int answer = 0;
    int result = 0;
    enOperation op;
    enLevel level;
    bool isTure = true;
};

struct stQuizInfo {
    int numberOfQuesionts = 0;
    stQuestionInfo questionList[100];
    enLevel quizLevel;
    enOperation quizOp;
    int numberOfRightAnswer = 0;
    int numberOfWrongAnswer = 0;
    bool isPassed = true;
};

bool isNumberInRange(int number, int from, int to) {
    return number >= from && number <= to;
}

int readPositiveNumber(string msg) {
    int number = 0;
    do {
        cout << msg << " ";
        cin >> number;

        while (cin.fail()) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Invalid Number, Enter a valid one:" << " ";
            cin >> number;
        }

    } while (!isNumberInRange(number, 1, 10));
    return number;
}

int readNumber() {
    int number = 0;
    cin >> number;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Invalid Number, Enter a valid one:" << " ";
        cin >> number;
    }
    return number;
}

enLevel readQuizLevel() {
    int level = 0;
    do {
        cout << "Enter Questions Level [1] Easy, [2] Med, [3] Hard, [4] Mix ? ";
        cin >> level;

        while (cin.fail()) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Invalid Number, Enter a valid one:" << " ";
            cin >> level;
        }

    } while (!isNumberInRange(level, 1, 4));
    return (enLevel)level;
}

enOperation readQuizOpType() {
    int op = 0;
    do {
        cout << "Enter Operation Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ";
        cin >> op;

        while (cin.fail()) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Invalid Number, Enter a valid one:" << " ";
            cin >> op;
        }

    } while (!isNumberInRange(op, 1, 5));
    return (enOperation)op;
}

string convertLevelToString(enLevel level) {
    switch (level) {
    case enLevel::Easy:
        return "Easy";
        break;
    case enLevel::Mid:
        return "Mid";
        break;
    case enLevel::Hard:
        return "Hard";
        break;
    case enLevel::Mix:
        return "Mix";
        break;
    default:
        return "UnKnown";
        break;
    }
}

string convertOperationToString(enOperation op) {
    switch (op) {
    case enOperation::Add:
        return "+";
        break;
    case enOperation::Sub:
        return "-";
        break;
    case enOperation::Mul:
        return "*";
        break;
    case enOperation::Div:
        return "/";
        break;
    case enOperation::MixOp:
        return "Mix Operation";
        break;
    default:
        return "UnKnown";
        break;
    }
}

int getRandomNumber(int from, int to) {
    int randomNumber = rand() % (to - from + 1) + from;
    return randomNumber;
}

int getQuestionResult(int num1, int num2, enOperation op) {
    switch (op) {
    case enOperation::Add:
        return num1 + num2;
        break;
    case enOperation::Sub:
        return num1 - num2;
        break;
    case enOperation::Mul:
        return num1 * num2;
        break;
    case enOperation::Div:
        while (num2 == 0) {
            cout << "Num 2 Can't be = 0 , Please Re Enter Num 2 : ";
            cin >> num2;
        }
        return num1 / num2;
        break;
    }

    return -1;
}

stQuestionInfo generateQuestion(enLevel level, enOperation op) {

    stQuestionInfo questionInfo;

    if (level == enLevel::Mix)
        level = (enLevel)getRandomNumber(1, 3);

    if (op == enOperation::MixOp)
        op = (enOperation)getRandomNumber(1, 4);

    questionInfo.op = op;
    questionInfo.level = level;

    switch (level) {
    case enLevel::Easy:
        questionInfo.num1 = getRandomNumber(1, 10);
        questionInfo.num2 = getRandomNumber(1, 10);
        break;
    case enLevel::Mid:
        questionInfo.num1 = getRandomNumber(10, 50);
        questionInfo.num2 = getRandomNumber(10, 50);
        break;
    case enLevel::Hard:
        questionInfo.num1 = getRandomNumber(50, 100);
        questionInfo.num2 = getRandomNumber(50, 100);
        break;
    }

    questionInfo.result = getQuestionResult(questionInfo.num1, questionInfo.num2, questionInfo.op);

    return questionInfo;
}

void generateQuestions(stQuizInfo& quizInfo) {

    for (int i = 0; i < quizInfo.numberOfQuesionts; i++) {
        quizInfo.questionList[i] = generateQuestion(quizInfo.quizLevel, quizInfo.quizOp);
    }

}

void printQuestion(stQuizInfo quizInfo, int numberOfQuestion) {
    cout << "\nQuestion [" << numberOfQuestion + 1 << "/" << quizInfo.numberOfQuesionts << "]\n" << endl;
    cout << quizInfo.questionList[numberOfQuestion].num1 << endl;
    cout << quizInfo.questionList[numberOfQuestion].num2 << " " << convertOperationToString(quizInfo.questionList[numberOfQuestion].op) << endl;
    cout << "__________" << endl;


}

void changeScreenColor(bool isPassed) {
    if (isPassed) {
        system("Color 2F");
    }
    else {
        cout << "\a";
        system("color 4F");
    }
}

void checkUserAnswer(stQuizInfo& quizInfo, int numberOfQuestion) {
    quizInfo.questionList[numberOfQuestion].answer = readNumber();

    if (quizInfo.questionList[numberOfQuestion].answer == quizInfo.questionList[numberOfQuestion].result) {

        quizInfo.questionList[numberOfQuestion].isTure = true;
        quizInfo.numberOfRightAnswer++;
        cout << "Right Answer :-)" << endl;

    }
    else {

        quizInfo.questionList[numberOfQuestion].isTure = false;
        quizInfo.numberOfWrongAnswer++;
        cout << "Wrong Answer :-(" << endl;
        cout << "The Right Answer Is : " << quizInfo.questionList[numberOfQuestion].result << endl;

    }

    changeScreenColor(quizInfo.questionList[numberOfQuestion].isTure);
}



void answerAllQuestions(stQuizInfo& quizInfo) {

    for (int i = 0; i < quizInfo.numberOfQuesionts; i++) {
        printQuestion(quizInfo, i);
        checkUserAnswer(quizInfo, i);
    }

    if (quizInfo.numberOfRightAnswer >= quizInfo.numberOfWrongAnswer)
        quizInfo.isPassed = true;
    else
        quizInfo.isPassed = false;

}

string getFinalResult(bool isPassed) {
    if (isPassed) {
        return "Pass :-)";
    }
    else {
        return "Fail :-(";
    }
    return "";
}

void printQuizInfo(stQuizInfo quizInfo) {
    changeScreenColor(quizInfo.isPassed);
    cout << "\n-------------------------------" << endl;
    cout << "Final Result Is " << getFinalResult(quizInfo.isPassed) << endl;
    cout << "-------------------------------" << endl;
    cout << endl;
    cout << "Number Of Questions : " << quizInfo.numberOfQuesionts << endl;
    cout << "Question Level : " << convertLevelToString(quizInfo.quizLevel) << endl;
    cout << "Op Type : " << convertOperationToString(quizInfo.quizOp) << endl;
    cout << "Number Of Right Answer : " << quizInfo.numberOfRightAnswer << endl;
    cout << "Number Of Worng Answer : " << quizInfo.numberOfWrongAnswer << endl;
    cout << endl;
    cout << "-------------------------------" << endl;
}

stQuizInfo playMathGame() {

    stQuizInfo quizInfo;
    quizInfo.numberOfQuesionts = readPositiveNumber("How many Questions do you want to answer ? ");
    quizInfo.quizLevel = readQuizLevel();
    quizInfo.quizOp = readQuizOpType();

    generateQuestions(quizInfo);
    answerAllQuestions(quizInfo);
    printQuizInfo(quizInfo);

    return quizInfo;

}

void clearScreen() {
    system("cls");
    system("color 0F");
}

void startMathGame() {

    char playAgain = 'y';

    do {

        clearScreen();

        stQuizInfo quizInfo;
        quizInfo = playMathGame();

        cout << "\nDo you want to play again? Y/N? ";
        cin >> playAgain;

    } while (playAgain == 'y' || playAgain == 'Y');

}


int main()
{
    srand((unsigned)time(NULL));
    startMathGame();
    return 0;
}

