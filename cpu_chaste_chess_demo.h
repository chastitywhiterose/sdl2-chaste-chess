/*pgn_chaste_chess_demo.h*/

/*
 a simple but useful function to pause until the user presses escape or clicks the x in the window.
 I use this so that I can wait until OBS studio is recording my game before a demo starts playing.
 the global loop variable is used to control the loop and break out of it. It must be set back to 1 after the loop exits to be
 correct for the timing code later.
*/
void wait_for_input()
{
 loop=1;
 while(loop)
 {
  while(SDL_PollEvent(&e))
  {
   if(e.type==SDL_QUIT){loop=0;}
   if(e.type==SDL_KEYDOWN){if(e.key.keysym.sym==SDLK_ESCAPE){loop=0;}}
  }
 }
 loop=1;
}

void pgn_chaste_chess_demo()
{
 int x=0;
 char c=1;
 char demo_string[]="1. e4 e6 2. d4 d5 3. Nc3 Bb4";
 char *s=demo_string;
 char move[100];

 printf("%s\n\n",demo_string);

 c=*s;
 x=0;
 while(c!=0)
 {

  c=*s;

  /*if character is not space, add to move string*/
  if(!isspace(c))
  {
   move[x]=c;
   x++;
   /*printf("%c",c);*/
  }
  if(isspace(c)||c==0)
  {
   /*printf("\n");*/
   move[x]=0;
   x=0;

   /*printf("strlen(move)=%u\n",(int)strlen(move));*/

   if(move[1]!='.')
   {
    printf("move = %s\n",move);
   }
  }
  
  s++;

 }

 /*printf("last char = %d",c);*/

}





void pgn_chaste_chess_demo_1()
{
 move("d4");
 move("d5");
 move("c4");
 move("Nf6");
}

/*
using the easy API that ignores standard notation

This example shows the Queen's Gambit Old Variation Trap where black defends the c4 pawn with b5. This puts black in a position of losing material one way or another. This example is good so I am keeping it.

*/
void pgn_chaste_chess_demo_2()
{
move_xy(3,6,3,4);
move_xy(3,1,3,3);
move_xy(2,6,2,4);
move_xy(3,3,2,4);
move_xy(4,6,4,5);
move_xy(1,1,1,3);
move_xy(0,6,0,4);
move_xy(2,1,2,2);
move_xy(0,4,1,3);
move_xy(2,2,1,3);
move_xy(3,7,5,5);
move_xy(1,0,2,2);
move_xy(5,5,2,2);

}

/* this example starts with queen's gambit but includes an en-passant.*/
void pgn_chaste_chess_demo_3()
{

move_xy(3,6,3,4);
move_xy(3,1,3,3);
move_xy(2,6,2,4);
move_xy(4,1,4,2);
move_xy(2,4,2,3);
move_xy(1,1,1,3);
move_xy(2,3,1,2);

}


/*
a replay of an actual game that happened

https://lichess.org/I1gkSCRJuPxD
*/

/* this example starts with queen's gambit but includes an en-passant.*/
void pgn_chaste_chess_demo_4()
{

move_xy(3,6,3,4);
move_xy(6,0,5,2);
move_xy(2,7,6,3);
move_xy(7,1,7,2);
move_xy(6,3,7,4);
move_xy(6,1,6,3);
move_xy(7,4,6,5);
move_xy(5,2,4,4);
move_xy(6,5,4,3);
move_xy(5,1,5,2);
move_xy(4,6,4,5);
move_xy(5,2,4,3);
move_xy(3,7,7,3);


}

/*


[Event "Casual correspondence game"]
[Site "https://lichess.org/UoFLugyE"]
[Date "2025.02.20"]
[Round "?"]
[White "Judena"]
[Black "chastitywhiterose"]
[Result "0-1"]
[WhiteElo "1500"]
[BlackElo "1789"]
[ECO "D00"]
[TimeControl "-"]
[UTCDate "2025.02.20"]
[UTCTime "01:09:11"]
[Variant "Standard"]
[Termination "Normal"]
[GameId "UoFLugyE"]

1. d4 d5 2. e4 dxe4 3. c4 h5 4. Be2 Bg4 5. Qa4+ c6 6. Bg5 f6 7. Bf4 Qxd4 8.
Be3 Qxb2 9. f3 exf3 10. gxf3 Bd7 11. f4 Qxa1 12. Bxh5+ Rxh5 13. h4 Qxb1+
14. Bc1 Qxc1+ 15. Kf2 Qxf4+ 16. Nf3 c5 17. Qd1 e5 18. Qd5 Bc6 19. Qxg8 Bxf3
20. Qe6+ Kd8 21. Qf7 Bd5+ 22. Ke2 Bxf7 23. Rf1 Bxc4+ 24. Kd1 Qxf1+ 25. Kd2
Qd3+ 26. Ke1 Qe2# 0-1


*/


/* this example is an actual game I played with my mom on February 20 of 2025.*/
void pgn_chaste_chess_demo_5()
{

flip_main_grid();
move_render();
wait_for_input();

move_xy(4,1,4,3);
move_xy(4,6,4,4);
move_xy(3,1,3,3);
move_xy(4,4,3,3);
move_xy(5,1,5,3);
move_xy(0,6,0,4);
move_xy(2,0,3,1);
move_xy(5,7,1,3);
move_xy(4,0,7,3);
move_xy(5,6,5,5);
move_xy(5,0,1,4);
move_xy(2,6,2,5);
move_xy(1,4,2,3);
move_xy(4,7,4,3);
move_xy(2,3,3,2);
move_xy(4,3,6,1);
move_xy(2,1,2,2);
move_xy(3,3,2,2);
move_xy(1,1,2,2);
move_xy(1,3,4,6);
move_xy(2,2,2,3);
move_xy(6,1,7,0);
move_xy(3,1,0,4);
move_xy(0,7,0,4);
move_xy(0,1,0,3);
move_xy(7,0,6,0);
move_xy(3,2,5,0);
move_xy(6,0,5,0);
move_xy(3,0,2,1);
move_xy(5,0,2,3);
move_xy(1,0,2,2);
move_xy(5,5,5,4);
move_xy(7,3,4,0);
move_xy(3,6,3,4);
move_xy(4,0,4,4);
move_xy(4,6,5,5);
move_xy(4,4,1,7);
move_xy(5,5,2,2);
move_xy(1,7,3,5);
move_xy(3,7,4,7);
move_xy(3,5,2,6);
move_xy(2,2,4,4);
move_xy(2,1,3,1);
move_xy(4,4,2,6);
move_xy(0,0,2,0);
move_xy(2,6,5,3);
move_xy(3,1,4,0);
move_xy(2,3,2,0);
move_xy(4,0,4,1);
move_xy(2,0,4,2);
move_xy(4,1,3,0);
move_xy(4,2,3,1);

wait_for_input();
}