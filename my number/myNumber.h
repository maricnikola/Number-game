#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

#include <chrono>


const double sum = 1000000;
const double sub = 1000001;
const double mul = 1000010;
const double divv = 1000011;
const double ssum = 1000100;
const double ssub = 1000101;
const double mmul = 1001000;
const double ddiv = 1001001;

const double brackO = 111111;
const double brackC = 1111111;


class myNumber {
private:
	std::vector<int> numbers;
	double rez;
	std::string bestCombination;
	std::vector<char> operations = { '+','-','*','/','s','a','m','d' };
	std::vector<std::vector<int>> allCombinations;
	std::vector<int> currentCombination;
	int winner;
	std::vector<double> playerResults;
	double bestRez;
	double playRez;
	std::vector<std::string> expressionPlayer;

	void calculateCombinations();
	void calculateCombinationsRec(const int k, std::vector<int>& tmp, const int nextIndex);
	void operand1(std::vector<int> v);
	void operand2(std::vector<int> v);
	void operand3(std::vector<int> v);
	void operand4(std::vector<int> v);
	void operand5(std::vector<int> v);
	void operand4Parallel(std::vector<int> v);

public:
	myNumber();
	void addNumber(int number);
	void setRez(int rez);
	std::vector<int> getNumbers();
	int getRez();
	void printNum();
	int brojjac;


	std::vector<std::string> getPlayersExp();
	void addPlayerExp(std::string exp);
	double getBestRez();
	std::vector<double> getPlayerResult();
	void addPlayerResult(double res);
	std::string getBestCombination();
	int getWinner();
	void setWinner(int player);

	void calculatePermutations();
	double calc(double a, double b, double c);
	double pushingStek(char x);
	std::string transformRez(std::string rezultat);
	std::string transformSigns(double broj);
	void checkNumbers(std::string combination);

	template<typename T>
	T calc(T x, T o, T y) {					// pomocna funkcija koja prepoznaje na osnovu broja koja je operacija na steku i vraca 
		if (o == sum) {						// proracunatu vrednost dva broja sa tom operacijom
			return x + y;
		}
		else if (o == sub) {
			return x - y;
		}
		else if (o == mul) {
			return x * y;
		}
		else if (o == divv) {
			if (y == 0) {
				throw std::runtime_error("Nemoguce deljenje nulom");
			}
			return x / y;
		}
		else if (o == ssum) {
			return x + y;
		}
		else if (o == ssub) {
			return x - y;
		}
		else if (o == mmul) {
			return x * y;
		}
		else if (o == ddiv) {
			if (y == 0) {
				throw std::runtime_error("Nemoguce deljenje nulom");
			}
			return x / y;
		}

		return 16;
	}

	template<typename T>
	T calculate(std::string expression) {					// funkcija racunanja izraza za prosledjeni string upotrebom steka

		std::stack<T> stek;
		T num = 0;
		int n = expression.size();


		for (int i = 0; i < expression.size(); i++) {

			char x = expression[i];

			if (x >= '0' && x <= '9') {						//generise broj od charova 

				num = x - '0';
				while (i + 1 < n && expression[i + 1] >= '0' && expression[i + 1] <= '9') {
					i++;
					num = (num * 10) + (expression[i] - '0');
				}

				stek.push(num);
				num = 0;
			}
			else if (x == ' ') {				//provera da li je razmak
				continue;
			}
			else if (x == '+' || x == '-') {
				T o = pushingStek(x);
				if (stek.top() >= 1000000) {
					throw std::runtime_error("Nepravilan unos!");
				}
				if (stek.size() < 2) {
					stek.push(o);
				}
				else {
					T temp = stek.top();
					stek.pop();
					if (o - stek.top() > 1) {
						stek.push(temp);
						stek.push(o);
					}
					else {
						stek.push(temp);
						while (stek.size() != 1) {			//prazni stek dok ne dodje do operacije sa vecim ili istim prioritetom  
							temp = stek.top();				//tako sto ga racuna sa vec postojecim vrednostima i to resenje upisuje na stek 
							stek.pop();						// pa upisuje operaciju sa vecim prioritetom
							T operation = stek.top();
							if (o > operation) {
								stek.push(temp);
								break;
							}
							stek.pop();

							num = calc<T>(stek.top(), operation, temp);
							stek.pop();
							stek.push(num);
							num = 0;

						}
						stek.push(o);
					}
				}


			}
			else if (x == '*' || x == '/') {
				T o = pushingStek(x);
				if (stek.top() >= 1000000) {
					throw std::runtime_error("Nepravilan unos!");

				}
				if (stek.size() < 2) {
					stek.push(o);
				}
				else {
					double temp = stek.top();
					stek.pop();

					if (o - stek.top() > 1) {
						stek.push(temp);
						stek.push(o);
					}
					else {
						stek.push(temp);
						while (stek.size() != 1) {
							temp = stek.top();
							stek.pop();
							T operation = stek.top();
							if (o > operation) {
								stek.push(temp);
								break;
							}
							stek.pop();

							num = calc<T>(stek.top(), operation, temp);
							stek.pop();
							stek.push(num);
							num = 0;

						}
						stek.push(o);
					}
				}
			}

			else if (x == 's' || x == 'a') {
				T o = pushingStek(x);
				if (stek.top() >= 1000000) {
					throw std::runtime_error("Nepravilan unos!");
				}
				if (stek.size() < 2) {
					stek.push(o);
				}
				else {
					T temp = stek.top();
					stek.pop();
					if (o - stek.top() > 1) {
						stek.push(temp);
						stek.push(o);
					}
					else {
						stek.push(temp);
						while (stek.size() != 1) {
							temp = stek.top();
							stek.pop();
							T operation = stek.top();
							if (o > operation) {
								stek.push(temp);
								break;
							}
							stek.pop();

							num = calc<T>(stek.top(), operation, temp);
							stek.pop();
							stek.push(num);
							num = 0;

						}
						stek.push(o);
					}
				}

			}
			else if (x == 'm' || x == 'd') {
				T o = pushingStek(x);
				if (stek.top() >= 1000000) {
					throw std::runtime_error("Nepravilan unos!");
				}
				if (stek.size() < 2) {
					stek.push(o);
				}
				else {
					T temp = stek.top();
					stek.pop();
					if (o - stek.top() > 1) {
						stek.push(temp);
						stek.push(o);
					}
					else {
						stek.push(temp);
						while (stek.size() != 1) {
							temp = stek.top();
							stek.pop();
							T operation = stek.top();
							if (o > operation) {
								stek.push(temp);
								break;
							}
							stek.pop();

							num = calc<T>(stek.top(), operation, temp);
							stek.pop();
							stek.push(num);
							num = 0;

						}
						stek.push(o);
					}
				}
			}
			else {
				throw std::runtime_error("Nepravilan unos!");
			}

		}
		if (stek.size() < 2) {
			num = stek.top();
			return num;
		}
		else {
			while (stek.size() != 1) {			//prazni stek i konacno racuna resenje
				T temp = stek.top();
				stek.pop();
				T operation = stek.top();
				stek.pop();
				T number = stek.top();
				num = calc<T>(number, operation, temp);
				stek.pop();
				stek.push(num);
				num = 0;

			}
			num = stek.top();
			return num;
		}

	}


};