/*
 sdl_chaste_chess.h

a file for representing what the chess pieces are and controlling their movements 

*/


char chess_board_pieces[]=
{
 "RNBQKBNR"
 "PPPPPPPP"
 "00000000"
 "00000000"
 "00000000"
 "00000000"
 "PPPPPPPP"
 "RNBQKBNR"
};

char chess_board_pieces_color[]=
{
 "BBBBBBBB"
 "BBBBBBBB"
 "00000000"
 "00000000"
 "00000000"
 "00000000"
 "WWWWWWWW"
 "WWWWWWWW"
};


void chess_board_print()
{
 
 /*printf("%s\n",chess_board_pieces);*/

 printf("\n"); 

 y=0;
 while(y<8)
 {
  x=0;
  while(x<8)
  {
   printf(" %c",chess_board_pieces[x+y*8]);
   x+=1;
  }
  printf("\n"); 
  y+=1;
 }
 
 printf("\n"); 

}




struct chess_piece
{
 char color;
 char id;
 int moves;
 int x,y;
};

/*global chess piece that will be used for analyzing all data about the recently clicked piece*/
struct chess_piece p,pt;

/*global chess piece that will be used for analyzing all data about the currently selected piece if it was clicked last time*/
struct chess_piece ps;

/*global chess piece that will be used for the en_passant rule*/
struct chess_piece en_passant;

struct chess_move
{
 int source_x,source_y; /*where on the grid the piece is moving from*/
 int dest_x,dest_y; /*where on the grid the piece is moving to*/
 struct chess_piece moving_piece,captured_piece; /* for saving the piece data of the moving piece and which piece was captured. If the id of the piece is '0', then it is assumed there was no piece there*/

 int capture_x,capture_y; /*location the captured pieces was. It is important to consider that in the case of en passant, the captured pawn may be in a different location than where the capturing pawn moves to! This Chess rule makes the programming more difficult to account for.*/
};

/*global array of structure to record every move played in the game. Theoretically, this could be used to output standard Chess notation.*/
struct chess_move move_data_array[0x100];
int move_data_index=0;


struct chess_grid
{
 struct chess_piece array[64];
};

struct chess_grid main_grid;

void init_main_grid()
{

 y=0;
 while(y<8)
 {
  x=0;
  while(x<8)
  {
   main_grid.array[x+y*8].id=chess_board_pieces[x+y*8];
   main_grid.array[x+y*8].color=chess_board_pieces_color[x+y*8];
   main_grid.array[x+y*8].moves=0;
   x+=1;
  }
  y+=1;
 }

}

int view_flipped=0;
int starting_view_flip=0;

void flip_main_grid()
{
 struct chess_grid temp_grid;

 temp_grid=main_grid;

 y=0;
 while(y<8)
 {
  x=0;
  while(x<8)
  {
   main_grid.array[x+y*8]=temp_grid.array[(7-x)+(7-y)*8];
   x+=1;
  }
  y+=1;
 }

 view_flipped^=1;
}



void chess_grid_print()
{
 
 /*struct chess_piece p;*/

 y=0;
 while(y<8)
 {
  x=0;
  while(x<8)
  {
   p=main_grid.array[x+y*8];
   /*printf(" %c%c",p.color,p.id);*/
   printf(" %c",p.id);
   x+=1;
  }
  printf("\n"); 
  y+=1;
 }
 
}



/*more global variables*/

int dir=-1; /*the direction for pawn movements can be 1 or -1*/
char turn='W'; /*whose turn it is. W for white and B for black*/

/*
in the context of Chaste Chess, highlight refers to marking the spots on the board based on whether pieces can move to those spots or not.

0 Can't move
1 Can move to this blank space
2 Can move and capture a piece
-1 Could move and capture the piece here if it was the opposite color but it's the same.

The following functions keep track of the data but do not actually draw the highlights. It is only to internally represent the places the last selected piece can move to. There is a function which draws squares color coded according to their meaning in the graphics header for the game
*/

char highlight[64];

void init_highlight()
{
 int x,y;

 y=0;
 while(y<8)
 {
  x=0;
  while(x<8)
  {
   highlight[x+y*8]=0;
   x+=1;
  }
  y+=1;
 }

}

int highloop=0; /*highlight loop control*/

void chess_grid_highlight(int x,int y)
{

 if(x<0){ /*printf("Error: Negative X\n");*/ return;}
 if(y<0){ /*printf("Error: Negative Y\n");*/ return;}
 if(x>=8){/*printf("Error: X too high.\n");*/ return;}
 if(y>=8){/*printf("Error: Y too high.\n");*/ return;}

 if(main_grid.array[x+y*8].id=='0')
 {
  /*this space will be marked green meaning "go" because you can move here and it is blank*/
  /*SDL_SetRenderDrawColor(renderer,0x00,0xFF,0x00,255);*/
  highlight[x+y*8]=1;
 }
 else 
{
 /*this condition happens if there is a piece and the space is not blank*/

 if(main_grid.array[x+y*8].color==p.color)
 {
  /*this space will be marked red meaning "stop" because you can't move here and the piece is the same color as the piece you are moving*/
  /*SDL_SetRenderDrawColor(renderer,0xFF,0x00,0x00,255);*/
  /*
   same color as moving piece
   can't capture this piece or move beyond it
  */
  highlight[x+y*8]=-1;
  highloop=0;
 }

 if(main_grid.array[x+y*8].color!=p.color)
 {
  /*this space will be marked blue to indicate a piece can be captured*/
  /*SDL_SetRenderDrawColor(renderer,0x00,0x00,0xFF,255);*/
  /*
   same color as moving piece
   can capture this piece
  */
  highlight[x+y*8]=2;
  highloop=0;
 }

}

 /*highlight the square which was clicked*/
 /*rect.x=x*main_check.rectsize;
 rect.y=y*main_check.rectsize;
 rect.w=main_check.rectsize;
 rect.h=main_check.rectsize;*/
 
 /*SDL_RenderFillRect(renderer,&rect);*/

}

/*
 the next set of function deal with all the moves and highlight squares accordingly to where they can legally move
*/

void check_moves_rook()
{
     highloop=1;
     x1=x+1;
     y1=y;
     while(x1<8 && highloop)
     {
      chess_grid_highlight(x1,y1);
      x1++;
     }
    
     highloop=1;
     x1=x-1;
     y1=y;
     while(x1>=0 && highloop)
     {
      chess_grid_highlight(x1,y1);
      x1--;
     }

     highloop=1;
     x1=x;
     y1=y+1;
     while(y1<8 && highloop)
     {
      chess_grid_highlight(x1,y1);
      y1++;
     }
    
     highloop=1;
     x1=x;
     y1=y-1;
     while(y1>=0 && highloop)
     {
      chess_grid_highlight(x1,y1);
      y1--;
     }
}


void check_moves_bishop()
{
	 highloop=1;
	 x1=x+1;
     y1=y+1;
     while(x1<8&&y1<8 && highloop)
     {
      chess_grid_highlight(x1,y1);
      x1++;
      y1++;
     }
    
	highloop=1;
     x1=x-1;
     y1=y-1;
     while(x1>=0&&y1>=0 && highloop)
     {
      chess_grid_highlight(x1,y1);
      x1--;
      y1--;
     }

highloop=1;
     x1=x+1;
     y1=y-1;
     while(x1<8&&y1>=0 && highloop)
     {
      chess_grid_highlight(x1,y1);
      x1++;
      y1--;
     }
    
	highloop=1;
     x1=x-1;
     y1=y+1;
     while(x1>=0&&y1<=8 && highloop)
     {
      chess_grid_highlight(x1,y1);
      x1--;
      y1++;
     }
}

void check_moves_of_clicked_piece()
{
    /*check all legal pawn moves*/
    if(p.id=='P')
    {

     /*set direction of pawn based on whose turn it is*/
     if(p.color=='B'){dir=1;} 
     if(p.color=='W'){dir=-1;}

     /*but if view is flipped, reverse the direction so it is correct*/
     if(view_flipped)(dir=-dir);

     /*these next two sections of conditionals make sure that pawns move forward only onto blank spaces but can't capture pieces directly in front of them because this is not legal in chess.*/

     /*if the space in front of pawn is empty, mark it*/
     if(main_grid.array[x+(y+dir)*8].id=='0')
     {
      chess_grid_highlight(x,y+dir);

     /*and if that space is empty and the pawn hasn't moved, allow it to move two spaces forward*/
     if(p.moves==0)
     {
      if(main_grid.array[x+(y+dir*2)*8].id=='0')
      {
       chess_grid_highlight(x,y+dir*2);
      }
     }
     
     }



   /*end of pawn moving forward section*/

   /*begin pawn capturing section*/

    if(main_grid.array[x+1+(y+dir)*8].id!='0')
    {
     chess_grid_highlight(x+1,y+dir);
    }

    if(main_grid.array[x-1+(y+dir)*8].id!='0')
    {
     chess_grid_highlight(x-1,y+dir);
    }

   /*end pawn capturing section*/

    }

    if(p.id=='N')
    {
     chess_grid_highlight(x+1,y-2);
     chess_grid_highlight(x+2,y-1);

     chess_grid_highlight(x+1,y+2);
     chess_grid_highlight(x+2,y+1);

     chess_grid_highlight(x-1,y-2);
     chess_grid_highlight(x-2,y-1);

     chess_grid_highlight(x-1,y+2);
     chess_grid_highlight(x-2,y+1);
    }

    if(p.id=='R')
    {
     check_moves_rook();
    }


    if(p.id=='B')
    {
     check_moves_bishop();
    }


    if(p.id=='K')
    {
     chess_grid_highlight(x-1,y-1);
     chess_grid_highlight(x  ,y-1);
     chess_grid_highlight(x+1,y-1);

     chess_grid_highlight(x-1,y);
     chess_grid_highlight(x+1,y);

     chess_grid_highlight(x-1,y+1);
     chess_grid_highlight(x  ,y+1);
     chess_grid_highlight(x+1,y+1);
    }

    /*
     the queen inherits the moves of both the rook and the bishop
     so they have been copy pasted from their sections
    */
    if(p.id=='Q')
    {
     check_moves_rook();
     check_moves_bishop();
    }
	
}



/*
the following function is for debugging castling.
it removes all pieces except for the kings and rooks so that I can test if castling works correctly
*/


void debug_castle()
{
 struct chess_piece t;

 y=0;
 while(y<8)
 {
  x=0;
  while(x<8)
  {
   t=main_grid.array[x+y*8];
   if(t.id=='B'||t.id=='N'||t.id=='Q')
   {
    main_grid.array[x+y*8].id='0';
   }

   x+=1;
  }
  y+=1;
 }

}


void swap_turn()
{
     if(turn=='W')
      {
       turn='B';
       printf("White has moved. It is now Black's turn.\n");
      }
      else
      {
       turn='W';
       printf("Black has moved. It is now White's turn.\n");
      }
}