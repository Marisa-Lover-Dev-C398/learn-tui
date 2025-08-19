#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include <sys/ioctl.h>
#include <termios.h>

// termios.hにてこいつが定義されてる。(in my env: /usr/include/asm-generic/termios.h)
//んで予測だが、sys/ioctlでinclude termios.hされてる説あり。
/*
struct winsize {
        unsigned short ws_row;
        unsigned short ws_col;
        unsigned short ws_xpixel;
        unsigned short ws_ypixel;
};
*/

int main(void)
{
  struct winsize ws;
  char* msg = "I love Kirisame Marisa!";
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
  //printf("row(縦):%d, cols(横) %d\n",ws.ws_row,ws.ws_col);
  printf("\033[2J\033[H\033[1m\033[31;31m");
  fflush(stdout);
  for(int i=1; i <= ws.ws_col; i++)
  {
    if(i==1 || i==ws.ws_col){
      printf("+");
    } else{
      printf("-");
    }
    fflush(stdout);
    usleep(10000);
  }
  printf("\n");
  for(int i=2; i< ws.ws_row; i++)
  {
    printf("\033[%d;1H|",i);
    fflush(stdout);
    usleep(50000);
    printf("\033[%d;%dH|", i, ws.ws_col);
    fflush(stdout);
    usleep(50000);
  }
  for(int i=1; i <= ws.ws_col; i++)
  {
    if(i==1 || i==ws.ws_col){
      printf("+");
    } else{
      printf("-");
    }
    fflush(stdout);
    usleep(10000);
  }
  printf("\033[0m");
  fflush(stdout);
  sleep(3);
  //文字出力テスト
  printf("\033[%d;%dH\033[33;47m",ws.ws_row/2,(ws.ws_col - strlen(msg)) / 2);
  while (*msg) {
      printf("%c", *msg);
      fflush(stdout);
      usleep(100000);
      msg++;
  }
  fflush(stdout);
  sleep(5);
  printf("\033[0m\033[H");
  return 0;
}
