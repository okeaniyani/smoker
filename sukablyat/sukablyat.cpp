#include <iostream>
#include <ctime>
#include <random>
#include <thread>
#include <chrono>


//счетчики курильщика
struct Smoker														
{
	int smokedСigg;
	int cash;
	int dolg;
};

bool playAgain()
{
	char ch;
	do
	{
		std::cout << "\nWould you like to play again(y / n)? ";
		std::cin >> ch;
	} while (ch != 'y' && ch != 'n');
	return(ch == 'y');
}

int getRandomNumb(int min, int max)
{
	std::random_device rd;
	std::mt19937 rand(rd());
	std::uniform_int_distribution<> dist(min, max);
	return(dist(rand));
}

// докурил 20 сигарету и смотрит на cash
Smoker doPokupki(Smoker smoker, int zP)                                    
{
	int choice = getRandomNumb(1, zP);

	if (choice <= 5 && smoker.cash == 0)                        // банкрот опиздюлился
	{
		std::cout << "777 Hova UMER NAXUI(POVESILSYA) 777\n\n";
		return(smoker);
	}

	if (choice > 5 && choice <= 50 && smoker.cash == 0)                        //занял долг+100 cash+100
	{
		if (smoker.dolg >= 400)
		{
			std::cout << "Hovu ubili cigane za dolgi\n\n";
			return(smoker);
		} 
		else
		{
			smoker.cash += 100;
			smoker.dolg += 100;
			return(smoker);
		}
	}

	if (choice > 50)                                          //пошабашил в сарае cash+200
	{
		smoker.cash += 800;
		return(smoker);
	}
	return(smoker);
}

// вывод итогов
void summStatOut(int suka, int blyat, int days)
{
	std::cout << "For a " << days << " days Hova said the word \"blyat\" " << blyat << " times\n";
	std::cout << "For a " << days << " days Hova said the word \"suka\" " << suka << " times\n";
}

// вывод каждого дня
void eachDayOut(Smoker smoker, int day)
{
	std::cout << "Day " << day << '\n';
	std::cout << "Sigaret vikuril: " << smoker.smokedСigg << '\n';
	std::cout << "Pa4ek vikuril: " << smoker.smokedСigg/20.0 << '\n';
	std::cout << "Cash: " << smoker.cash << " rub\n";
	std::cout << "Dolg ciganam: " << smoker.dolg << " rub\n";
	std::cout << '\n';
}


int main()
{
	do
	{
		std::cout << "\nEnter days ";
		int days;
		std::cin >> days;
		int planCig = days * 24;

		int blyat = 0;
		int suka = 0;
		int haveCig = 0;
		int day = 0;
		int zP = 100;
		Smoker Hova = { 0, 300, 0 };


		while (Hova.smokedСigg < planCig)
		{
			if (haveCig == 0)
			{
				zP = 100 - (int)(50 * (float)Hova.cash / 1000.0);

				Hova = doPokupki(Hova, zP);

				if (Hova.cash == 0)
				{
					break;
				}

				Hova.cash -= 100;					//покупает пачку
				haveCig += 20;
			}

			haveCig -= 1;							//курит сигарету
			Hova.smokedСigg += 1;




			if (haveCig == 3)
				++blyat;
			if (haveCig == 2)
				blyat += 2;
			if (haveCig == 1)
			{
				++blyat;
				++suka;
			}

			if (Hova.smokedСigg % 24 == 0)
			{
				day++;
				eachDayOut(Hova, day);
				std::this_thread::sleep_for(std::chrono::milliseconds(5));
			}

			int choiceRak = getRandomNumb(1, 30);

			if (Hova.smokedСigg % 1000 == 0 && choiceRak == 1)

			{
				std::cout << "777 Hova UMER NAXUI sdoh ot raka :^) 777\n\n";
				break;
			}
			if (Hova.smokedСigg % 1000 == 0 && choiceRak > 1)
			{
				std::cout << "----- Poveslo suka -----\n\n";
			}

		}
		summStatOut(suka, blyat, day);
		if (day == days)
		{
			std::cout << "\n-----666--- Pozdravlyaem! Hova vijil ---666-----\n\n";
		}
	} while (playAgain());
	std::cout << "\nPOSHEL NAHUY\n";
	return(0);
}