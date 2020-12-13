#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

int main()
{
	int x = 0, y, lvl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),3);
	printf("Enter the number of tiles: ");
	scanf_s("%d", &y);
	x += (2 * y);
	printf("Enter the amount of level you want to play: ");
	scanf_s("%d", &lvl);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),3);
	printf("\n> Use wasd to move, or WASD to move faster\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),9);
	printf("      >~Press eny key to continue~<"); (void)_getch();
	int i = 0, j = 0, py = y / 2, px = x / 2;
	int sy = rand() % (y - 1) + 1, sx = rand() % (x - 1) + 1;
	int scr = 0, t, life = 3, level = 250;
	int tx[100] = { 0 }, ty[100] = { 0 }, tn = 1, print = 0, replay = 1;
	char plr = 'j', last_key = 'j';
	do{
		while(life&&scr<lvl){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),165);
			for (t = 0; t < x / 12; t++)printf("  "); printf("> Your score is: %d <", scr);
			for (t = 0; t < x / 10; t++)printf(" "); printf("> Life left: %d <\n\n", life);
			for (i = 0; i < y; i++) {
				for (j = 0; j < x; j++) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
					if (!i || i == y - 1 || !j || j == x - 1) {
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
						printf("#");
					}
					//Score and logic
					if (py == sy && px == sx) { //Snake eat apple
						scr++;
						level -= 10;
						sy = rand() % (y - 1) + 1;
						sx = rand() % (x - 1) + 1;
						tn++;
						Beep(750, 300);
					}
					else if (i == sy && j == sx) { //food drawing
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
						printf("@");
					}
					else if (i == py && j == px) { //Snake figure
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
						printf("0");
					}
					else {
						print = 0;
						for (int k = 0; k < tn; k++) { //Snake tail
							if (tx[k] == j && ty[k] == i) {
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
								printf("o");
								print = 1;
							}
						}
						if (i > 0 && i < y - 1 && j>0 && j < x && !print) printf(" ");
					}
				}
				printf("\n");
			}
			//Controls
			if(_kbhit()){
				switch(_getch()){
			case 'j': plr = 'j'; break;
			case 'w': plr = 'w'; break;
			case 's': plr = 's'; break;
			case 'd': plr = 'd'; break;
			case 'a': plr = 'a'; break;
			case 'W': plr = 'W'; break;
			case 'S': plr = 'S'; break;
			case 'D': plr = 'D'; break;
			case 'A': plr = 'A'; break;
			case 'x': case 'X': plr = 'X'; break;
			case 'p': case 'P': plr = 'P'; break;
				}
			}
			if(plr != 'p' && plr != 'P'){
				last_key = plr;
			}
			switch (plr)
			{
				case 'j': px = px, py = py; break;
				case 'w': py--; break;
				case 's': py++; break;
				case 'd': px++; break;
				case 'a': px--; break;
				case 'W': py -= 2; break;
				case 'S': py += 2; break;
				case 'D': px += 4; break;
				case 'A': px -= 4; break;
				case 'x': case 'X': life = 0; break;
				case 'p': case 'P':
				{
					for (i = 0; i < (x - 3) / 2; i++) printf(" ");
					printf("Pause\n");
					for (i = 0; i < (x - 25) / 2; i++) printf(" ");
					printf("Press eny key to continue");
					(void)_getch();
					plr = last_key;
				} break;
			}
			//Fail score system
			if(px>x-2||px<2||py>y-2||py<1) {
				life--;
				px = x/2;
				py = y/2;
				sy = rand()% (y-1) + 1;
				sx = rand()% (x-1) + 1;
				Beep(1050,150);/*********/
				Beep(750,150); /* System*/
				Beep(550,150); /* Sound */
				Beep(350,150); /*********/
			}
			for (i = 1; i < tn; i++) {
				if (px == tx[i] && py == ty[i]) {
					life--;
					px = x / 2;
					py = y / 2;
					sy = rand() % (y - 1) + 1;
					sx = rand() % (x - 1) + 1;
				}
			}
			//Snake tail
			int prevx = tx[0], prevy = ty[0];
			int prev2x, prev2y;
			tx[0] = px;
			ty[0]= py;
			for (i = 1; i < tn; i++) {
				prev2x = tx[i];
				prev2y = ty[i];
				tx[i] = prevx;
				ty[i] = prevy;
				prevx = prev2x;
				prevy = prev2y;
			}
			//printf("random x:%d y:%d ",sx,sy);
			Sleep(level);
			system("cls");
		}
		if (!life) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			printf("GAME OVER!");
			Beep(311, 200); Beep(300, 200); /*********/
			Beep(279, 200); Beep(260, 200); /* System*/
			Beep(243, 200); Beep(230, 200); /* Sound */
			Beep(215, 500); Beep(200, 1000);/*********/
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
			printf("\nPlay again? Y/N: ");
			if (_getch() == 'y' || _getch() == 'Y') {
				life = 3;
				scr = 0;
				tn = 0;
				py = y / 2;
				px = x / 2;
				replay = 1;
				plr = 'j';
			}
			else replay = 0;
		}
		else {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
			printf("You Win!");
			Beep(215, 200); Beep(415, 200);
			Beep(715, 200); Beep(1050, 500);/* System*/
			Beep(715, 200); Beep(1050, 500); /* Sound */
			printf("\nPlay again? Y/N: ");
			if (_getch() == 'y' || _getch() == 'Y') {
				life = 3;
				scr = 0;
				tn = 0;
				py = y / 2;
				px = x / 2;
				replay = 1;
				plr = 'j';
			}
			else replay = 0;
		}
	}while (replay);
	(void)_getch();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}
