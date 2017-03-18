#include <stdio.h>
#include <graphics.h>
#include<vector>
#include<stdlib.h>
#include<time.h>
#include <iostream>
using namespace std;


void drawBar(int color, int height, int i, int db) {
	setfillstyle(SOLID_FILL, color);
	bar(i * 640 / db, 480 - height, (i + 1) * 640 / db, 480);
}
void csere(int a, int b, vector<int> &vec) {
	int temp = vec[a];
	vec[a] = vec[b];
	vec[b] = temp;
}

void draw(vector<int> vec, vector<bool> sorted) {
	int i;
	int db = vec.size();
	for (i = 0; i < db; i++) {
		if (sorted[i]) {
			drawBar(2, vec[i], i, db);
		}
		else {
			drawBar(3, vec[i], i, db);
		}
	}
	Sleep(1);
}

vector<int> bubblesort(vector<int> vec, int wid1, int wid2) {
	vector<bool> sorted;

	int db = vec.size();
	int x = 1;

	for (int k = 0; k < db; k++) { sorted.push_back(false); }

	for (int j = 1; j <= db; j++) {
		for (int i = 0; i < db - x; i++) {
			draw(vec, sorted);
			swapbuffers();
			cleardevice();

			if (vec[i] > vec[i + 1]) { csere(i, i + 1, vec); }
		}
		sorted[db - j] = true;
		x += 1;
	}

	draw(vec, sorted);
	swapbuffers();
	cleardevice();

	return vec;
}

vector<int> quicksort(vector<int> vec, vector<bool> &sorted, int wid1, int wid2, int from, int to) {
	int pivi = from;
	int x = 0;
	if (from < to) {
		for (int i = from + 1; i <= to; i++) {
			if (vec[i] <= vec[pivi]) {
				for (int j = 0; j <= x; j++) {
					draw(vec, sorted);
					swapbuffers();
					cleardevice();
					csere(pivi + x - j, pivi + x - j + 1, vec);
				}
				pivi += 1;
			}
			else {
				x += 1;
			}
		}
		sorted[pivi] = true;
		draw(vec, sorted);
		swapbuffers();
		cleardevice();


		vec = quicksort(vec, sorted, wid1, wid2, from, pivi - 1);
		vec = quicksort(vec, sorted, wid1, wid2, pivi + 1, to);
	}
	else {
		sorted[from] = true;
		draw(vec, sorted);
		swapbuffers();
		cleardevice();
	}
	return vec;
}

int main() {
	int db;
	char rend = 'a';
	cout << "Hany elemu legyen a rendezni kivant halmaz?\n>";
	cin >> db;

	cout << "\nMilyen rendezest hasznaljunk?\nbubblesort=b\nquicksort=q\n>";
	while (rend != 'q' && rend != 'b') {
		cin >> rend;
		if (rend != 'q' && rend != 'b') { cout << "probald ujra\n>"; }
	}

	vector<bool> sorted;
	for (int k = 0; k <= db; k++) { sorted.push_back(false); }

	vector<int> magassagok;

	srand(time(NULL));
	for (int i = 0; i < db; i++) { magassagok.push_back(40 + rand() % 440); }


	int wid1, wid2;

	wid1 = initwindow(640, 480, "sorba_rendezes");
	wid2 = initwindow(640, 480, "sorba_rendezes");
	setcurrentwindow(wid2);

	setbkcolor(BLACK);
	cleardevice();

	if (rend == 'b') {
		magassagok = bubblesort(magassagok, wid1, wid2);
	}
	if (rend == 'q') {
		magassagok = quicksort(magassagok, sorted, wid1, wid2, 0, db - 1);
	}


	while (!kbhit());
	closegraph();

	return(0);
}

void drawsin(int wid1, int wid2) {
	for (int i = 0; i < 640; i++) {
		putpixel(480 * sin(i / 480), i, WHITE);
	}

}