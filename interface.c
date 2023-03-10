#include "interface.h"

void textcolor (int iColor)
{
    HANDLE hl = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
    BOOL b = GetConsoleScreenBufferInfo(hl, &bufferInfo);
    bufferInfo.wAttributes &= 0x00F0;
    SetConsoleTextAttribute (hl, bufferInfo.wAttributes |= iColor);
}


void textbackground (int iColor)
{
    HANDLE hl = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
    BOOL b = GetConsoleScreenBufferInfo(hl, &bufferInfo);
    bufferInfo.wAttributes &= 0x000F;
    SetConsoleTextAttribute (hl, bufferInfo.wAttributes |= (iColor << 4));
}


void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}



void Borda(int x, int y, int largura, int altura, int tipo, int sombra){
    // EsqSup DirSup EsqInf DirInf LHoriz LVertical
    char C[][6] = {"\xda\xbf\xc0\xd9\xc4\xb3" ,
                    "\xc9\xbb\xc8\xbc\xcd\xba"};

    int i, j;
    gotoxy(x, y); printf("%c", C[tipo][0]);
    for(i = 0; i < largura; i++) printf("%c", C[tipo][4]);
    printf("%c", C[tipo][1]);
    for(j = 0; j < altura; j++){
        gotoxy(x, y+j+1); printf("%c", C[tipo][5]);
        for(i = 0; i < largura; i++) printf(" ");
        printf("%c", C[tipo][5]);
        if(sombra) printf("\xb2");
    }
    gotoxy(x, y+altura); printf("%c", C[tipo][2]);
    for(i = 0; i < largura; i++) printf("%c", C[tipo][4]);
    printf("%c", C[tipo][3]);
    if(sombra){
        gotoxy(x+1, y+altura+1);
        for(i = 0; i < largura+2; i++) printf("\xb2");
    }
}

int getTecla(){
  int ch;
  ch = getch();
  if(ch == 224){
      ch = getch() + 1000;
  }
  return ch;
}


int menu(char opcoes[][51], int x[], int y[], int opcao, int n){
  int i, tecla; textcolor(LIGHT_GRAY); textbackground(BLACK);
  for(i=0; i<n; i++){
      gotoxy(x[i],y[i]);printf("%s", opcoes[i]);
  }

do{
  textcolor(WHITE); textbackground(BLACK);
  gotoxy(x[opcao],y[opcao]);printf("%s", opcoes[opcao]);
  tecla = getTecla();
  textcolor(LIGHT_GRAY); textbackground(BLACK);
  gotoxy(x[opcao],y[opcao]);printf("%s", opcoes[opcao]);
  if(tecla == 13)return opcao;
  if(tecla == TEC_BAIXO)opcao++;
  if(tecla == TEC_DIR)opcao++;
  if(tecla == TEC_CIMA)opcao--;
  if(tecla == TEC_ESQ)opcao--;
  if(opcao < 0)opcao = n-1;
  if(opcao >= n)opcao = 0;
  if(tecla == 13)return opcao;
}while(tecla!=27);
return -1;

}

