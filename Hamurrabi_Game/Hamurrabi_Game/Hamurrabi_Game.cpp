#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>
#include <fstream>
#include <string>

using namespace std;

struct city {
	int people = 100;
	int wheat = 2800;
	int area = 1000;
};

struct iteration {
	int round = 1;
	int dead = 0;
	int migration = 0;
	bool plague = false;
	int harvest = 0;
	int harvestperacre = rand() % 6 + 1;
	int harvestratted = 0;
	int acreprice = rand() % 10 + 17;
	int starved = 0;
};

struct decisions {
	int acresbought;
	int food;
	int acrestowheat;
};

string input;

void report(city&, iteration&);
void ending(city&, iteration&);
decisions playerinput(city&, iteration&);
void savegame(city&, iteration&);
city isplague(city&);

std::string savePath = "Save.txt";


int main()
{
	setlocale(LC_ALL, "RU");
	setlocale(LC_NUMERIC, "C");
	srand(time(0));
	city babylon;
	iteration game_info;
	ifstream loadgame;
	decisions playerInput;
	loadgame.open(savePath);
	bool incorrect = true;
	if (loadgame) {
		while (incorrect) {
			printf("Повелитель, существует сохранённая игра, загрузить? (введите '1' - да/'0' - нет) \n");
			cin >> input;
			if (input.size() == 1) {
				if (input == "1") {
					loadgame >> babylon.people >> babylon.wheat >> babylon.area >> game_info.round >> game_info.starved;
					incorrect = false;
				}
				else if (input == "0") {
					incorrect = false;
				}
			}
			else {
				printf("Повелитель, я не понял тебя! \n");
			}
		}
	}
	loadgame.close();
	incorrect = true;
	for (game_info.round; game_info.round < 11; game_info.round++) {
		int round_pop = babylon.people;
		report(babylon, game_info);
		game_info.acreprice = rand() % 10 + 17;
		while (incorrect) {
			playerInput = playerinput(babylon, game_info);
			if (playerInput.acresbought*game_info.acreprice + playerInput.acrestowheat*0.5 > babylon.wheat) {
				printf("Повелитель, мы не можем себе это позволить, у нас всего %i жителей, %i бушелей пшеницы и %i акров земли!\n", babylon.people, babylon.wheat, babylon.area);
			}
			else if (playerInput.acrestowheat > babylon.area + playerInput.acresbought) {
				printf("Повелитель, мы не можем себе это позволить, у нас всего %i жителей, %i бушелей пшеницы и %i акров земли!\n", babylon.people, babylon.wheat, babylon.area);
			}
			else {
				incorrect = false;
			}
		}
		savegame(babylon, game_info);
		babylon.area += playerInput.acresbought;
		babylon.wheat = babylon.wheat - playerInput.acresbought - playerInput.acrestowheat*0.5;
		if (rand() % 100 < 15) {
			isplague(babylon);
			game_info.plague = true;
		}
		else {
			game_info.plague = false;
		}
		incorrect = true;
		game_info.harvestperacre = rand() % 6 + 1;
		if (babylon.people * 10 >= babylon.area) {
			game_info.harvest += game_info.harvestperacre*playerInput.acrestowheat;
		}
		else {
			game_info.harvest += game_info.harvestperacre * babylon.people * 10;
		};
		game_info.harvestratted = (babylon.wheat) * (rand() % 8) / 100;
		babylon.wheat += game_info.harvest - game_info.harvestratted;
		if (playerInput.food / 20 - babylon.people < 0) {
			game_info.dead = babylon.people - playerInput.food / 20;
			if (game_info.dead / babylon.people > 0.45  || babylon.people - game_info.dead <=0) {
				printf("Ваши жители умирали голодной смертью, им это не понравилось... \n");
				exit(0);
			}
			game_info.starved += game_info.dead;
		}
		babylon.wheat -= babylon.people * 20;
		game_info.migration = game_info.dead / 2 + (5 - game_info.harvestperacre) * babylon.wheat / 600 + 1;
		if (game_info.migration < 0) {
			game_info.migration = 0;
		}
		else if (game_info.migration > 50) {
			game_info.migration = 50;
		}
		babylon.people += game_info.migration - game_info.dead;
	};
	ending(babylon, game_info);
	remove("Save.txt");
	return 0;
}


void report(city& City, iteration& Iter) {
	printf("В году %i твоего высочайшего правления \n", Iter.round);
	printf("%i человек умерли с голоду, и %i человек прибыли в наш великий город \n", Iter.dead, Iter.migration);
	if (Iter.plague == 1) {
		printf("Чума уничтожила половину населения \n");
	}
	printf("Население города сейчас составляет %i человек \n", City.people);
	printf("Мы собрали %i бушелей пшеницы, по %i бушелей с акра\n", Iter.harvest, Iter.harvestperacre);
	printf("Крысы уничтожили %i бушелей пшеницы, оставив %i бушелей в амбарах\n", Iter.harvestratted, City.wheat);
	printf("Город сейчас занимает %i акров \n", City.area);
	printf("1 акр сейчас стоит %i бушелей \n \n", Iter.acreprice);
};

void ending(city& City, iteration& Iter) {
	printf("Мой повелитель, тебе удалось провести Вавилон через десять лет его жизни!\n \n");
	if ((Iter.starved / 10 > 0.33) && (City.area / City.people < 7)) {
		printf("Но при твоём правлении люди были несчастны, Твоё правление было тёмным временем для города. \n");
	}
	else if ((Iter.starved / 10 > 0.1) && (City.area / City.people < 9)) {
		printf("При твоём правлении люди были несчатны, но могли это претерпеть \n");
	}
	else if ((Iter.starved / 10 > 0.03) && (City.area / City.people < 9)) {
		printf("Твоё правление не запомнилось людям. Они не голодали, не бедствовали, но и не были счастливы.\n");
	}
	else
		printf("Поздравляю, Твоё правление было золотым веком для Вавилона. \n");
};

decisions playerinput(city& City,  iteration& Iter) {
	decisions changes;
	printf("Что пожелаешь, повелитель? (для выхода введите '0', для продолжения введите любой символ, кроме пробела или ноля)\n");
	cin >> input;
	if (input == "0") {
		savegame(City, Iter);
		exit(0);
	}
	bool incorrect = true;
	int convertedInput = 0;
	while (incorrect) {
		printf("\n Сколько акров земли пожелаешь купить?");
		cin >> input;
		for (int i = 0; i < input.size(); i++) {
			if (input[i] < '0', input[i]>'9') {
				printf("Повелитель, я тебя не понимаю, скажи мне число! \n \n");
			}
		}
		convertedInput = stoi(input);
		if (convertedInput > 2147483647) {
			printf("Повелитель, мы ещё не изобрели таких чисел! \n \n");
		}
		else {
			incorrect = false;
		}
	}
	changes.acresbought = convertedInput;
	incorrect = true;
	while (incorrect) {
		printf("\n Сколько бушелей пшеницы повелеваешь съесть?");
		cin >> input;
		int convertedInput;
		for (int i = 0; i < input.size(); i++) {
			if (input[i] < '0', input[i]>'9') {
				printf("Повелитель, я тебя не понимаю, скажи мне число! \n \n");
			}
		}
		convertedInput = stoi(input);
		if (convertedInput > 2147483647) {
			printf("Повелитель, мы ещё не изобрели таких чисел! \n \n");
		}
		else {
			incorrect = false;
			convertedInput = stoi(input);
		}
	}
	changes.food = convertedInput;
	incorrect = true;
	while (incorrect) {
		printf("\n Сколько акров земли повелеваешь засеять?");
		cin >> input;
		int convertedInput;
		for (int i = 0; i < input.size(); i++) {
			if (input[i] < '0', input[i]>'9') {
				printf("Повелитель, я тебя не понимаю, скажи мне число! \n \n");
			}
		}
		convertedInput = stoi(input);
		if (convertedInput > 2147483647) {
			printf("Повелитель, мы ещё не изобрели таких чисел! \n \n");
		}
		else {
			incorrect = false;
			convertedInput = stoi(input);
		}
	}
	changes.acrestowheat = convertedInput;
	return changes;
};

void savegame(city& City, iteration& Iter){
	ofstream save;
	save.open(savePath);
	save.clear();
	save << City.people << ' ' << City.wheat << ' ' << City.area << ' ' << Iter.round << ' ' << Iter.starved;
	save.close();
};

city isplague(city& City) {
	City.people /= 2;
	return City;
};