#include <iostream>
#include <fstream>
#include "myNumber.h"


std::vector<myNumber> allNumbers;
std::vector<int> numbers;
std::vector<std::vector<int>> brojevi;

void loadNumbers(std::string inputfile);
void playGame();
void writeData(std::string end_file);

void main(int argc, char* argv[]) {

	std::string default_path_numbers = "myNumber.txt";
	std::string default_path_results = "results.txt";
	std::string input_file;
	std::string end_file;
	if (argc > 1) {
		input_file = argv[1];
		std::cout << "File for reading: " << input_file << std::endl;
	}
	else {
		input_file = default_path_numbers;
	}

	if (argc > 2) {
		end_file = argv[2];
		std::cout << "File for writing: " << end_file << std::endl;
	}
	else {
		end_file = default_path_results;
	}
	loadNumbers(input_file);
	playGame();
	writeData(end_file);

	return;
}


void loadNumbers(std::string input_file) {						//funkcija za ucitavanje podataka iz .txt datoteke 
	std::ifstream in(input_file);

	if (!in) {
		std::cerr << "Error";
	}
	while (!in.eof()) {
		myNumber myNum;

		for (int i = 0; i < 6; i++) {
			std::string number;
			in >> number;
			numbers.push_back(std::stoi(number));
			myNum.addNumber(std::stoi(number));
		}
		std::string rez;
		in >> rez;
		myNum.setRez(std::stoi(rez));


		brojevi.push_back(numbers);
		allNumbers.push_back(myNum);
	}
}


void printVector(std::vector<int> vec) {
	std::vector<int>::iterator iter;
	for (iter = vec.begin(); iter != vec.end(); iter++) {
		std::cout << " " << *iter;
	}
	std::cout << std::endl;
}
void writeData(std::string end_file) {						// function that writes round game data to a txt file
	std::ofstream out;
	out.open(end_file);
	std::vector<myNumber>::iterator iter;
	int i = 1;
	int player1 = 0;
	int player2 = 0;
	for (iter = allNumbers.begin(); iter != allNumbers.end(); iter++) {
		out << "Round " << i << "\n";
		out << "Numbers for calculation: " << iter->getNumbers().at(0) << " " << iter->getNumbers().at(1) << " " << iter->getNumbers().at(2) << " " << iter->getNumbers().at(3) << " " << iter->getNumbers().at(4) << " " << iter->getNumbers().at(5) << " \n";
		out << "Target three-digit number: " << iter->getRez() << "\n";
		out << "Procedure and number found by computer: " << iter->getBestCombination() << "=" << iter->getBestRez() << "\n";
		out << "Result, deviation and expression of player 1: " << iter->getPlayerResult().at(0) << " , " << abs(iter->getRez() - iter->getPlayerResult().at(0)) << " , " << iter->getPlayersExp().at(0) << "\n";
		out << "Result, deviation and expression of player 2: " << iter->getPlayerResult().at(1) << " , " << abs(iter->getRez() - iter->getPlayerResult().at(1)) << " , " << iter->getPlayersExp().at(1) << "\n";
		if (iter->getWinner() == 1) {
			out << "The winner of the round is: player " << iter->getWinner() << "\n";
			player1 += 1;
		}
		else if (iter->getWinner() == 2) {
			out << "The winner of the round is: player " << iter->getWinner() << "\n";
			player2 += 1;
		}
		else {
			out << "The round is tied." << "\n";
		}
		out << "==============================\n";


		i++;
	}
	out << "Player 1 won rounds: " << player1 << "\n";
	out << "Player 2 won rounds: " << player2 << "\n";
	if (player1 > player2) {
		out << "The winner is: player 1" << "\n";
		out << "==============================";
	}
	else if (player2 > player1) {
		out << "The winner is: player 2" << "\n";
		out << "==============================";
	}
	else {
		out << "It is tied" << "\n";
		out << "==============================";
	}
	out.close();
}


void playGame() {										// function where the entire game takes place and all other helper functions are called
	std::vector<myNumber>::iterator krozigru;
	int i = 0;
	std::cout << "\n==========WELCOME to the game My Number==========" << std::endl;
	for (krozigru = allNumbers.begin(); krozigru != allNumbers.end(); krozigru++) {
		std::cout << "\n===== ROUND " << i + 1 << " =====" << std::endl;
		std::cout << "Available numbers for round " << i + 1 << " are: ";
		printVector(krozigru->getNumbers());
		std::cout << "Solution to find: " << krozigru->getRez() << std::endl;
		std::cout << "\n";
		std::cout << "Letters that change operations in parentheses: addition-s, subtraction-a, multiplication-m, division-d\n" << std::endl;
		std::vector<double> results;
		for (int i = 0; i < 2; i++) {
			std::string izraz;
			while (true) {
				std::cout << "PLAYER " << i + 1 << " is on turn." << std::endl;
				std::cout << "Enter your expression: ";
				getline(std::cin, izraz);
				try
				{
					krozigru->checkNumbers(izraz);
					double rezultat = krozigru->calculate<double>(izraz);
					if (rezultat == krozigru->getRez()) {
						i++;
						std::cout << "You got the correct number: " << rezultat << " congratulations!" << std::endl;
						krozigru->addPlayerResult(rezultat);
						krozigru->addPlayerExp(izraz);
						krozigru->addPlayerResult(0);
						krozigru->addPlayerExp("");
						break;
					}
					krozigru->addPlayerExp(izraz);
					krozigru->addPlayerResult(rezultat);
					std::cout << "You got the number: " << rezultat << std::endl;
					break;
				}
				catch (const std::exception& e)
				{
					std::cout << e.what() << std::endl;
					continue;
				}

			}
			std::cout << "\n";

		}
		if ((abs(krozigru->getRez() - krozigru->getPlayerResult().at(0)) < abs(krozigru->getRez() - krozigru->getPlayerResult().at(1)))) {
			std::cout << "\n=====WINNER OF ROUND " << i + 1 << " is PLAYER 1=====\n" << std::endl;
			krozigru->setWinner(1);
		}
		else if ((abs(krozigru->getRez() - krozigru->getPlayerResult().at(0)) > abs(krozigru->getRez() - krozigru->getPlayerResult().at(1)))) {
			std::cout << "\n=====WINNER OF ROUND " << i + 1 << " is PLAYER 2=====\n" << std::endl;
			krozigru->setWinner(2);
		}
		else {
			std::cout << "\n=====IT'S A TIE=====" << std::endl;
			krozigru->setWinner(3);
		}
		krozigru->calculatePermutations();

		std::cout << "The best solution the computer got is: " << krozigru->getBestRez() << std::endl;
		std::cout << "The calculation procedure is: " << krozigru->getBestCombination() << std::endl;
		std::cout << "\n";
		i++;
	}
	std::cout << "\n===== END OF GAME =====" << std::endl;
}
