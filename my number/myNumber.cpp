#include "myNumber.h"


myNumber::myNumber() : rez(0), winner(0), bestRez(0), playRez(0) {};

void myNumber::addNumber(int number) {
	this->numbers.push_back(number);
}

void myNumber::setRez(int rezultat) {
	this->rez = rezultat;
}
std::vector<int> myNumber::getNumbers() {
	return this->numbers;
}

void myNumber::printNum() {
	std::vector<int>::iterator numIter;
	for (numIter = numbers.begin(); numIter != numbers.end(); numIter++) {
		std::cout << *numIter << " ";
	}
}

int myNumber::getRez() {
	return this->rez;
}

std::string myNumber::getBestCombination() {
	return bestCombination;
}
double myNumber::getBestRez() {
	return bestRez;
}
int myNumber::getWinner() {
	return winner;
}


std::vector<std::string> myNumber::getPlayersExp() {
	return expressionPlayer;
}
void myNumber::addPlayerExp(std::string exp)
{
	expressionPlayer.push_back(exp);
}
std::vector<double> myNumber::getPlayerResult() {
	return playerResults;
}
void myNumber::addPlayerResult(double res)
{
	playerResults.push_back(res);
}
void myNumber::setWinner(int player) {
	this->winner = player;
}


void myNumber::calculateCombinationsRec(const int k, std::vector<int>& tmp, const int nextIndex) {			//pommocna funkcija generisanja svih kombinacija k 
	tmp.push_back(numbers[nextIndex]);																		// koja se rekurzivno poziva

	if (k == tmp.size())
	{
		this->allCombinations.push_back(tmp);

		tmp.pop_back();

		return;
	}
	for (size_t i = nextIndex + 1; i < numbers.size(); i++)
	{
		calculateCombinationsRec(k, tmp, i);
	}
	tmp.pop_back();
}


void myNumber::calculateCombinations()					//funkcija generisanja svih kombinacija k elemenata redom od 6 elemenata 
{
	for (int i = 0; i < 6; i++) {

		for (size_t rootIdx = 0; rootIdx < numbers.size(); rootIdx++)
		{

			std::vector<int> tmp;
			calculateCombinationsRec(i + 1, tmp, rootIdx);
		}

	}

}

double myNumber::pushingStek(char x) {				//pomocna funkcija koja vraca vrednost broja u zavisnosti koja je operacija
	if (x == '+') {
		return sum;
	}
	else if (x == '-') {
		return sub;
	}
	else if (x == '*') {
		return mul;
	}
	else if (x == '/') {
		return divv;
	}
	else if (x == 's') {
		return ssum;
	}
	else if (x == 'a') {
		return ssub;
	}
	else if (x == 'm') {
		return mmul;
	}
	else if (x == 'd') {
		return ddiv;
	}
}


std::string myNumber::transformSigns(double broj) {			//pomocna funkciija koja vraca vrednost zatvorena ili otvorena zagrada u zavisnosti oznake broja

	if (broj == brackC) {
		return ")";
	}
	else if (broj == brackO) {
		return "(";
	}

	return  "n";
}

void myNumber::checkNumbers(std::string expression) {			//funkcija validacije unosa koja proverava da ne ide operacija za operacijom, da su svi brojevi
	int n = expression.size();									// iz opsega datih brojeva, da ne ide na pocetku operacija ...
	int num = 0;
	std::vector<int> playerNumbers;

	for (int i = 0; i < n; i++) {
		char x = expression[i];

		if (x >= '0' && x <= '9') {

			num = x - '0';
			while (i + 1 < n && expression[i + 1] >= '0' && expression[i + 1] <= '9') {
				i++;
				num = (num * 10) + (expression[i] - '0');
			}
			playerNumbers.push_back(num);
			num = 0;


		}
		else if (x == ' ') {
			continue;
		}
		else if (x == '+' || x == '-' || x == '*' || x == '/' || x == 's' || x == 'a' || x == 'm' || x == 'd') {
			if (i == 0) {
				throw std::runtime_error("Invalid input!\n");
			}
			continue;
		}
		else {
			throw std::runtime_error("Invalid input!\n");
		}
	}
	if (playerNumbers.empty()) {
		throw std::runtime_error("Invalid input!\n");
	}
	sort(playerNumbers.begin(), playerNumbers.end());
	sort(numbers.begin(), numbers.end());


	if (!includes(numbers.begin(), numbers.end(), playerNumbers.begin(), playerNumbers.end())) {
		throw std::runtime_error("Invalid input!\n");
	}

}

std::string myNumber::transformRez(std::string rezultat) {				//funkcija koja pretvara izraz iz izvornog(sa pomocnim slovima) u kod sa zagradama
	int n = rezultat.size();											//upotrebom steka
	std::vector<int> stek;
	std::vector<char> stekOper;
	int num = 0;

	for (int i = 0; i < n; i++) {
		char x = rezultat[i];

		if (x >= '0' && x <= '9') {
			num = x - '0';
			while (i + 1 < n && rezultat[i + 1] >= '0' && rezultat[i + 1] <= '9') {
				i++;
				num = (num * 10) + (rezultat[i] - '0');
			}
			stek.push_back(num);
			num = 0;
		}
		else if (x == '+' || x == '-') {
			if (stekOper.size() == 0) {
				stekOper.push_back(x);
			}
			else {
				if (stekOper.back() == '+' || stekOper.back() == '-' || stekOper.back() == '*' || stekOper.back() == '/') {
					stekOper.push_back(x);
				}
				else {
					stek.push_back(1111111);
					stekOper.push_back(x);
				}
			}
		}
		else if (x == '*' || x == '/') {
			if (stekOper.size() == 0) {
				stekOper.push_back(x);
			}
			else {
				if (stekOper.back() == '+' || stekOper.back() == '-' || stekOper.back() == '*' || stekOper.back() == '/') {
					stekOper.push_back(x);
				}
				else {
					stek.push_back(1111111);
					stekOper.push_back(x);

				}
			}
		}
		else if (x == 's' || x == 'a') {
			if (stekOper.size() == 0) {
				int num = stek.back();
				stek.pop_back();
				stek.push_back(111111);
				stek.push_back(num);
				stekOper.push_back(x);
			}
			else {
				if (stekOper.back() == '+' || stekOper.back() == '-' || stekOper.back() == '*' || stekOper.back() == '/') {
					int temp = stek.back();
					stek.pop_back();
					stek.push_back(111111);
					stek.push_back(temp);
					stekOper.push_back(x);

				}
				else {
					stekOper.push_back(x);

				}
			}
		}
		else if (x == 'm' || x == 'd') {
			if (stekOper.size() == 0) {
				int num = stek.back();
				stek.pop_back();
				stek.push_back(111111);
				stek.push_back(num);
				stekOper.push_back(x);
			}
			else {
				if (stekOper.back() == '+' || stekOper.back() == '-' || stekOper.back() == '*' || stekOper.back() == '/') {
					int temp = stek.back();
					stek.pop_back();
					stek.push_back(111111);
					stek.push_back(temp);
					stekOper.push_back(x);

				}
				else {
					stekOper.push_back(x);

				}
			}
		}

	}
	if (stekOper.back() == 's' || stekOper.back() == 'a' || stekOper.back() == 'm' || stekOper.back() == 'd') {
		stek.push_back(1111111);

	}
	std::vector<char>::iterator opIter;
	for (opIter = stekOper.begin(); opIter != stekOper.end(); opIter++) {
		if (*opIter == 's') {
			*opIter = '+';
		}
		else if (*opIter == 'a') {
			*opIter = '-';
		}
		else if (*opIter == 'm') {
			*opIter = '*';
		}
		else if (*opIter == 'd') {
			*opIter = '/';
		}
	}

	stekOper.push_back(' ');

	std::vector<int>::iterator iter;
	int i = 0;
	std::string expression;
	for (iter = stek.begin(); iter != stek.end(); iter++) {

		std::string zagrada = transformSigns(*iter);
		if (zagrada == "(") {
			iter++;
			expression += zagrada + std::to_string(*iter);
			expression += stekOper[i];
			i++;
		}
		else if (zagrada == ")") {
			char op = expression.back();
			expression.pop_back();
			expression += zagrada;
			expression += op;
		}
		else {
			expression += std::to_string(*iter);
			expression += stekOper[i];
			i++;
		}
	}
	return expression;
}

void myNumber::operand1(std::vector<int> v) {			//sve operan1-5 funkcije koriste se za generisanje svih mogucih kombinacija sa operacijama u zavisnosti 
	std::vector<char>::iterator it1;					// da li su upitanju 2,3,4... broja izmedju kojih se operacije ubacuju
	for (it1 = operations.begin(); it1 != operations.end(); it1++) {
		std::string combination = std::to_string(v[0]) + *it1 + std::to_string(v[1]);
		double newRez;
		try
		{
			newRez = calculate<double>(combination);
		}
		catch (const std::exception&)
		{
			continue;
		}
		if (newRez == rez) {
			bestRez = rez;
			bestCombination = combination;
			break;
		}
		if (abs(rez - newRez) < abs(rez - bestRez)) {
			bestCombination = combination;
			bestRez = newRez;
		}

	}
}

void myNumber::operand2(std::vector<int> v) {
	std::vector<char>::iterator it1;
	std::vector<char>::iterator it2;
	for (it1 = operations.begin(); it1 != operations.end(); it1++) {
		for (it2 = operations.begin(); it2 != operations.end(); it2++) {
			std::string combination = std::to_string(v[0]) + *it1 + std::to_string(v[1]) + *it2 + std::to_string(v[2]);
			double newRez;
			try
			{
				newRez = calculate<double>(combination);
			}
			catch (const std::exception&)
			{
				continue;
			}
			if (newRez == rez) {
				bestRez = rez;
				bestCombination = combination;
				break;
			}
			if (abs(rez - newRez) < abs(rez - bestRez)) {
				bestCombination = combination;
				bestRez = newRez;
			}
		}
	}
}

void myNumber::operand3(std::vector<int> v) {
	std::vector<char>::iterator it1;
	std::vector<char>::iterator it2;
	std::vector<char>::iterator it3;
	for (it1 = operations.begin(); it1 != operations.end(); it1++) {
		for (it2 = operations.begin(); it2 != operations.end(); it2++) {
			for (it3 = operations.begin(); it3 != operations.end(); it3++) {
				std::string combination = std::to_string(v[0]) + *it1 + std::to_string(v[1]) + *it2 + std::to_string(v[2]) + *it3 + std::to_string(v[3]);
				double newRez;
				try
				{
					newRez = calculate<double>(combination);
				}
				catch (const std::exception&)
				{
					continue;
				}
				if (newRez == rez) {
					bestCombination = combination;
					bestRez = rez;
					break;
				}
				if (abs(rez - newRez) < abs(rez - bestRez)) {
					bestCombination = combination;
					bestRez = newRez;
				}
			}
		}
	}
}

void myNumber::operand4(std::vector<int> v) {
	std::vector<char>::iterator it1;
	std::vector<char>::iterator it2;
	std::vector<char>::iterator it3;
	std::vector<char>::iterator it4;
	for (it1 = operations.begin(); it1 != operations.end(); it1++) {
		for (it2 = operations.begin(); it2 != operations.end(); it2++) {
			for (it3 = operations.begin(); it3 != operations.end(); it3++) {
				for (it4 = operations.begin(); it4 != operations.end(); it4++) {
					std::string combination = std::to_string(v[0]) + *it1 + std::to_string(v[1]) + *it2 + std::to_string(v[2]) + *it3 + std::to_string(v[3]) + *it4 + std::to_string(v[4]);
					double newRez;
					//brojjac++;
					try
					{
						newRez = calculate<double>(combination);
					}
					catch (const std::exception&)
					{
						continue;
					}
					if (newRez == rez) {
						bestCombination = combination;
						bestRez = rez;
						break;
					}
					if (abs(rez - newRez) < abs(rez - bestRez)) {
						bestCombination = combination;
						bestRez = newRez;
					}
				}
			}
		}
	}
}
void myNumber::operand4Parallel(std::vector<int> v) {
	std::vector<char>::iterator it1;
	std::vector<char>::iterator it2;
	std::vector<char>::iterator it3;
	std::vector<char>::iterator it4;
	for (int i = 0; i < operations.size(); i++) {
		for (int j = 0; j < operations.size(); j++) {
			for (int k = 0; k < operations.size(); k++) {
				for (int m = 0; m < operations.size(); m++) {
					std::string combination = std::to_string(v[0]) + operations[i] + std::to_string(v[1]) + operations[j] + std::to_string(v[2]) + operations[k]
						+ std::to_string(v[3]) + operations[m] + std::to_string(v[4]);
					double newRez;
					try
					{
						newRez = calculate<double>(combination);
					}
					catch (const std::exception&)
					{
						continue;
					}
					if (newRez == rez) {
						bestCombination = combination;
						bestRez = rez;
						break;
					}
					if (abs(rez - newRez) < abs(rez - bestRez)) {
						bestCombination = combination;
						bestRez = newRez;
					}
				}
			}
		}
	}
}

void myNumber::operand5(std::vector<int> v) {
	std::vector<char>::iterator it1;
	std::vector<char>::iterator it2;
	std::vector<char>::iterator it3;
	std::vector<char>::iterator it4;
	std::vector<char>::iterator it5;

	for (it1 = operations.begin(); it1 != operations.end(); it1++) {
		for (it2 = operations.begin(); it2 != operations.end(); it2++) {
			for (it3 = operations.begin(); it3 != operations.end(); it3++) {
				for (it4 = operations.begin(); it4 != operations.end(); it4++) {
					for (it5 = operations.begin(); it5 != operations.end(); it5++) {
						std::string combination = std::to_string(v[0]) + *it1 + std::to_string(v[1]) + *it2 + std::to_string(v[2]) + *it3 + std::to_string(v[3]) + *it4 + std::to_string(v[4]) + *it5 + std::to_string(v[5]);
						double newRez;
						brojjac++;
						try
						{
							newRez = calculate<double>(combination);
						}
						catch (const std::exception&)
						{
							continue;
						}
						if (newRez == rez) {
							bestCombination = combination;
							bestRez = rez;
							break;
						}
						if (abs(rez - newRez) < abs(rez - bestRez)) {
							bestCombination = combination;
							bestRez = newRez;
						}
					}
				}
			}
		}
	}
}

void myNumber::calculatePermutations() {			//funkcija koja prolazi kroz sve generisane kombinacije i od njih dodatno pravi permutacije 
	calculateCombinations();						//izmedju kojih ubacuje operacije i generise string koji posle racuna i poredi sa trazenim rezultatom
	std::vector<std::vector<int>>::iterator iter;
	for (iter = this->allCombinations.begin(); iter != this->allCombinations.end(); iter++) {

		if (iter->size() == 1) {
			if (bestRez == 0) {
				bestRez = iter->at(0);
			}
			else if (iter->at(0) == rez) {
				bestRez = iter->at(0);
				break;
			}
			else if ((rez - iter->at(0)) < (rez - bestRez)) {
				bestRez = iter->at(0);

			}

		}

		if (iter->size() == 2) {
			sort(iter->begin(), iter->end());
			do {
				operand1(*iter);
				if (bestRez == rez) {
					break;
				}
			} while (next_permutation(iter->begin(), iter->end()));			//postupak pravljenja permutacija koji se ponavlja za svaku kombinaciju

			if (bestRez == rez) {
				break;
			}

		}
		else if (iter->size() == 3) {
			sort(iter->begin(), iter->end());
			do {
				operand2(*iter);
				if (bestRez == rez) {
					break;
				}
			} while (next_permutation(iter->begin(), iter->end()));
			if (bestRez == rez) {
				break;
			}



		}
		else if (iter->size() == 4) {
			sort(iter->begin(), iter->end());
			do {
				operand3(*iter);
				if (bestRez == rez) {
					break;
				}

			} while (next_permutation(iter->begin(), iter->end()));
			if (bestRez == rez) {
				break;
			}

		}
		else if (iter->size() == 5) {
			sort(iter->begin(), iter->end());
			do {
				operand4(*iter);
				if (bestRez == rez) {
					break;
				}
			} while (next_permutation(iter->begin(), iter->end()));
			if (bestRez == rez) {
				break;
			}

		}
		else if (iter->size() == 6) {
			sort(iter->begin(), iter->end());
			do {
				operand5(*iter);
				if (bestRez == rez) {
					break;
				}
			} while (next_permutation(iter->begin(), iter->end()));
			if (bestRez == rez) {
				break;
			}

		}

	}
	std::string comb = transformRez(bestCombination);
	bestCombination = comb;
}

