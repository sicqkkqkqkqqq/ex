#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
using namespace std;

class Game
{
	vector<string> words;
	string encrypted_word;
	string choosed_word;
public:
	void PrintEncryptedWord()
	{
		for (int i = 0; i < encrypted_word.size(); i++)
			cout << encrypted_word.at(i);
		cout << endl;
	}
	bool WordCheker()
	{
		for (int i = 0; i < encrypted_word.size(); i++)
		{
			if (choosed_word.compare(encrypted_word))
			{
				return false;
			}
		}
	}
	void ChooseWord()
	{
		srand(time(0));
		fstream wordfs;

		wordfs.open("words.txt", fstream::in | fstream::out | fstream::app);
		if (!wordfs.is_open())
			cout << "Error";
		else
		{
			string word;
			while (wordfs >> word)
				words.push_back(word);
			int i = rand() % words.size();
			choosed_word = words.at(i);
			for (int j = 0; j < words.at(i).size(); j++)
			{
				encrypted_word.push_back('_');
			}
			cout << "Word: ";
			PrintEncryptedWord();
		}
	}
	void SetWords()
	{
		fstream wordfs;
		wordfs.open("words.txt", fstream::in | fstream::out | fstream::app);
		string word;
		int o;
		do
		{
			cout << "1 - Set word\n0 - Play\nChoose: ";
			cin >> o;
			switch (o)
			{
			case 1:
			{
				cout << "Enter word: ";
				cin >> word;
				wordfs << word << " ";
				break;
			}
			case 0:
				break;
			default:
				cout << "Error.Wrong option\n";
				break;
			}

		} while (o != 0);

	}
	void GamePlay()
	{
		SetWords();
		ChooseWord();
		char letter;
		int attempts = 6;
		cout << "Number of attempts: " << attempts << endl;
		clock_t start, end;
		start = clock();
		while (!WordCheker())
		{
			cout << "Enter letter: ";
			cin >> letter;
			for (int j = 0; j < choosed_word.size(); j++)
			{
				if (letter == choosed_word[j])
				{
					encrypted_word[j] = letter;
					PrintEncryptedWord();
					attempts++;
				}
			}
			attempts--;
			if (attempts == 0)
			{
				cout << "You Lose\n";
				cout << "Word: " << choosed_word;
				exit(EXIT_SUCCESS);
			}
		}
		end = clock();
		double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
		cout << "You guessed the word for " << time_taken << " seconds" << endl;
	}
};

int main()
{
	Game game;
	game.GamePlay();
}