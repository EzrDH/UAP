#include <iostream>
#include <curses.h>
#include <windows.h>
#include <cstdlib>		

using namespace std;	

int lebar = 120;
int tinggi = 20;
int x, y, makan_x, makan_y, score;
bool gameOver;

enum arah_ular {STOP=0, LEFT, RIGHT, UP, DOWN};
arah_ular arah;

int ekor_x[100], ekor_y[100];
int EKOR;
    

void pengaturan() {
    
    initscr();
    clear();
    curs_set(0);	                 
    gameOver = false;
    arah = STOP;
    x = lebar/2;
    y = tinggi/2;
    makan_x = (rand() % lebar) + 1;
    makan_y = (rand() % tinggi) + 1;
    score = 0;
}

void jendela() {
    clear();	
    
    for(int i = 0; i < tinggi + 2; i++) {
        for(int j = 0; j < lebar + 2; j++) {
            if (i == 0 || i == 21) {
                mvprintw(i,j,"  ");
            } else if (j == 0 || j == 117) {
                mvprintw(i,j,"  ");
            } else if (i == y && j == x) {
                mvprintw(i,j,"O");
            } else if (i == makan_y && j == makan_x) {
                mvprintw(i,j,"+");
            } else {
                for(int k = 0; k < EKOR; k++) {
                    if (ekor_x[k] == j && ekor_y[k] == i) {
                        mvprintw(i,j,"o");
                    }
                }
            }
        }
    }
    init_pair(2,COLOR_WHITE,COLOR_GREEN);
    attron(COLOR_PAIR(2));
	attroff(COLOR_PAIR(1));
	
    mvprintw(23,50,"Score : %d",score);
    
    refresh();
    return;
}  

void input() {
    
    keypad(stdscr, TRUE);  
    
    switch(getch()) {
        case 97:
            
            if (arah != RIGHT) {
                arah = LEFT;
            }
            break;
        case 100:
            if (arah != LEFT) {
                arah = RIGHT;
            }
            break;
        case 115:
            if (arah != UP) {
                arah = DOWN;
            }
            break;
        case 119:
            if (arah != DOWN) {
                arah = UP;
            }
            break;
        case KEY_LEFT:
            if (arah != RIGHT) {
                arah = LEFT;
            }
            break;
        case KEY_RIGHT:
            if (arah != LEFT) {
                arah = RIGHT;
            }
            break;
        case KEY_DOWN:
            if (arah != UP) {
                arah = DOWN;
            }
            break;
        case KEY_UP:
            if (arah != DOWN) {
                arah = UP;
            }
            break;
        
        case 113:
            gameOver = true;
            break;
    }
}

void ular() {
	start_color();		
	init_pair(1,COLOR_RED,COLOR_CYAN);
	attron(COLOR_PAIR(1));
	
	initscr();
    
    int baris = ekor_x[0];
    int kolom = ekor_y[0];
    int baris2, kolom2;
    ekor_x[0] = x;
    ekor_y[0] = y;

    
    for(int i = 1; i < EKOR; i++) {
        baris2 = ekor_x[i];
        kolom2 = ekor_y[i];
        ekor_x[i] = baris;
        ekor_y[i] = kolom;
        baris = baris2;
        kolom = kolom2;
    }
    
    switch(arah) {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        default:
            break;
    }		
	    
	if (x > lebar || x < 1 || y < 1 || y > tinggi) {
        gameOver = true;
		init_pair(3,COLOR_WHITE,COLOR_GREEN);
		attron(COLOR_PAIR(3));
        attroff(COLOR_PAIR(2));	
		clear();
            mvprintw(10,18,"===================================> GAME OVER <===================================");
    }
    
    for(int i = 0; i < EKOR; i++) {
        if (ekor_x[i] == x && ekor_y[i] == y) {
            gameOver = true;
			init_pair(3,COLOR_WHITE,COLOR_GREEN);
            attron(COLOR_PAIR(3));
			attroff(COLOR_PAIR(2));
			clear();
         mvprintw(10,18,"===================================> GAME OVER <===================================");
        }
    }
    
    if (x == makan_x && y == makan_y) {
        score++;
        makan_x = (rand() % lebar) + 1;
        makan_y = (rand() % tinggi) + 1;
        
        
        for(int i = 0; i < EKOR; i++) {
            while (ekor_x[i] == makan_x && ekor_y[i] == makan_y) {
                makan_x = (rand() % lebar) + 1;
                makan_y = (rand() % tinggi) + 1;
            }
        }
        EKOR++;
    }
}

int main() {
	char nama[50];	
	string player[3] = {"Ezra", "Yunnisa", "Mitha"};  
	
	system("color 7C");
	initscr();
	
	printw("ketikkan Ezra, Yunnisa, atau Mitha");
	
	mvprintw(1, 0, "Pilih Pemain : ");
	getstr(nama);
	
	if(nama == player[0] || nama == player[1] || nama == player[2]){
    pengaturan();
    
    while(!gameOver) {
        jendela();
        input();
        ular();
    }
	}else {	
	clear();
	mvprintw (10,35,"~~~~ UNREGISTERED  ~~~~");
}

    getch();  
    endwin(); 
    return 0;
}		


