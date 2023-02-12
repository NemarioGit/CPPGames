#include <iostream>

using namespace std;

int main()
{
    int number = 0, guessedNumber = 0, attemptsNum = 0;

    srand(time(NULL));
    number = rand() % 100 + 1;
    cout << "Guess the number from 1 to 100!" << endl;

    do {
        attemptsNum++;
        cout << "Enter your guess: ";
        cin >> guessedNumber;

        while (1) //Validating input
        {
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Ignoring rest of the input
                cout << "You have entered wrong input!" << endl;
                cin >> guessedNumber;
            }
            if (!cin.fail())
                break;
        }

        if (guessedNumber > number) cout << "Too high!\n" << endl;
        else if (guessedNumber < number) cout << "Too low!\n" << endl;
        else {
            cout << "That's right! It took you " << attemptsNum << " attempts!";
            exit(0);
        }

    } while (guessedNumber != number);
}