/* cpu_chaste_chess_input.h */


void input_get_rank_and_file(int x,int y)
{
 if(view_flipped!=0)
 {
  square_rank=y+'1';
  square_file='H'-x;
 }
 else
 {
  square_rank='8'-y;
  square_file='A'+x;
 }
}

/*
 dummy function just to test if we can get the mouse and keyboard input correct
 prints to the terminal but has no effect on the actual game
*/
void chaste_chess_check_input_dummy()
{

while(SDL_PollEvent(&e))
  {

   if(e.type == SDL_QUIT){loop=0;}
   if(e.type == SDL_KEYUP)
   {
    if(e.key.keysym.sym==SDLK_ESCAPE){loop=0;}
   }

   mouse_state=0;

   if(e.type == SDL_MOUSEBUTTONDOWN)
   {
    x=e.button.x;
    y=e.button.y;
    mouse_state=1;
    keyboard_shown=0;

    if(x<check_left){printf("Mouse clicked too far left outside of board\n");return;}
    if(x>check_left+check_size){printf("Mouse clicked too far right outside of board\n");return;}

    /*printf("Mouse clicked at position X=%d Y=%d ",x,y);*/

    /*if(e.button.button==SDL_BUTTON_LEFT){printf("SDL_BUTTON_LEFT");}
    if(e.button.button==SDL_BUTTON_RIGHT){printf("SDL_BUTTON_RIGHT");}
    if(e.button.button==SDL_BUTTON_MIDDLE){printf("SDL_BUTTON_MIDDLE");}
    printf("\n");*/


    x=(x-check_left)/main_check.rectsize;
    y=y/main_check.rectsize;

    input_get_rank_and_file(x,y);


    printf("Cartesian Square clicked: X=%d Y=%d\n",x,y);
    printf("Chess Square clicked: %c%c\n",square_file,square_rank);
   }

  }

}


/*moves the piece by calling the new function which is defined in cpu_chaste_chess_moves.h*/
void move_piece()
{


move_data_array[move_data_index].source_x=ps.x;
move_data_array[move_data_index].source_y=ps.y;
move_data_array[move_data_index].dest_x=x;
move_data_array[move_data_index].dest_y=y;

move_data_array[move_data_index].moving_piece=main_grid.array[ps.x+ps.y*8];

move_data_array[move_data_index].captured_piece=main_grid.array[x+y*8]; /*be default, we assume that the location the piece moves to is the same as the piece that is captured. The move_xy function will overwrite this value in the special case of en passant*/

move_data_array[move_data_index].capture_x=x;
move_data_array[move_data_index].capture_y=y;

 move_xy(ps.x,ps.y,x,y); /* now actually call the function to move the piece*/

 move_data_index++; /*increment the move counter now that the movement is done*/

 /*move saved to memory*/


 init_highlight();
}



/*moves the piece by calling the new function which is defined in cpu_chaste_chess_moves.h*/
void undo_move_piece()
{

 printf("move_data_index==%d\n",move_data_index);
 if(move_data_index==0){return;}

 move_data_index--;

 x=move_data_array[move_data_index].source_x;
 y=move_data_array[move_data_index].source_y;
 x1=move_data_array[move_data_index].dest_x;
 y1=move_data_array[move_data_index].dest_y;

 printf("undoing last move: move_xy(%d,%d,%d,%d);\n",x,y,x1,y1);

 /*
 calling the move function will automatically increment the move counter
 even though we are undoing a move instead of creating a new one.
 */
 move_xy(x1,y1,x,y);

 main_grid.array[x+y*8].moves-=2; /*since we undid the move, reduce piece move count*/

 /*and restore the piece that would have been there before the original move*/

 x=move_data_array[move_data_index].capture_x;
 y=move_data_array[move_data_index].capture_y;

 main_grid.array[x+y*8]=move_data_array[move_data_index].captured_piece;

 move_render();

 init_highlight();
}






/*moves the piece by calling the new function which is defined in cpu_chaste_chess_moves.h*/
void undo_move_piece_old()
{
 struct chess_piece last_piece_captured;

 printf("xy_move_index==%d\n",xy_move_index);
 if(xy_move_index==0){return;}

 /*go back 4 ints to get last move info*/
 xy_move_index-=4;

 last_piece_captured=pieces_captured[xy_move_index];

 x=xy_move_log[xy_move_index];
 y=xy_move_log[xy_move_index+1];
 x1=xy_move_log[xy_move_index+2];
 y1=xy_move_log[xy_move_index+3];

 printf("undoing last move: move_xy(%d,%d,%d,%d);\n",x,y,x1,y1);

 /*
 calling the move function will automatically increment the move counter
 even though we are undoing a move instead of creating a new one.
 */
 move_xy(x1,y1,x,y);

 /*therefore go back 4 ints to get index before the move would have occurred*/
 /*xy_move_index-=4;*/

 main_grid.array[x+y*8].moves-=2; /*since we undid the move, reduce piece move count*/

 /*and restore the piece that would have been there before the original move*/
 main_grid.array[x1+y1*8]=last_piece_captured;

 move_render();




 init_highlight();
}




void chess_square_select()
{

  /*select piece on clicked square. This includes an empty piece of '0' which is considered invalid for moving*/
  p=main_grid.array[x+y*8];

  /*set the location of the piece based on which grid square was clicked*/
    p.x=x;
    p.y=y;

    /*print information on the square selected, including what piece.*/

    printf("%c%c: ",square_file,square_rank);

    if(p.id=='0')
    {
     printf("Blank Space\n");
    }
    else
    {

     if(p.color=='B'){printf("Black ");} 
     if(p.color=='W'){printf("White ");}

     if(p.id=='P'){printf("Pawn");}
     if(p.id=='R'){printf("Rook");}
     if(p.id=='N'){printf("kNight");}
     if(p.id=='B'){printf("Bishop");}
     if(p.id=='Q'){printf("Queen");}
     if(p.id=='K'){printf("King");}

     printf("\n");
    }
    /*printf(" %c%c",p.color,p.id);*/

 
   

    /*
	 no piece is selected. we will try to select this piece and check the moves it might make
     now that we know which square was clicked and what piece is there
     the major step is to highlight which squares it is possible to move it to
    */

		
 
	

        /*if the color of clicked piece is the same as who's turn it is, then we will selecte it and highlight the moves it can make*/
	if(p.color==turn && p.id!='0')
	{
		ps=p;
		printf("This piece has been selected for possible move\n");

		square_file_source=square_file;
		square_rank_source=square_rank;
		square_file_dest='?';
		square_rank_dest='?';


        init_highlight();
        check_moves_of_clicked_piece();
	}

/*special case for en passant*/
if(ps.id=='P' && en_passant.id=='P')
{
 int xdiff=0,ydiff=0;

 xdiff=abs(en_passant.x-ps.x);
 ydiff=en_passant.y-ps.y;

 /*printf("Difference between selected piece and en_passant mark is %d %d\n",xdiff,ydiff);*/


 /*this conditional makes sure that only the correct pawns capture on the en_passant square*/
 if(xdiff==1&&ydiff==dir)
 {

 if(x==en_passant.x && y==en_passant.y)
 {
  ps.moves++; /*must add to move counter for piece or pawns will not be correct*/

  move_piece();
  printf("Moving piece to valid space\n");



  /*
   the following two statements are commented out because move_piece takes care of them. I keep them for special legacy reasons though.
  */

  /*main_grid.array[x+y*8]=ps;*/ /*move piece to new square*/
  /*main_grid.array[ps.x+ps.y*8].id='0';*/ /*clear previous square*/
  /*swap_turn();*/

  main_grid.array[x+(y-dir)*8].id='0';

  en_passant.id='0';
  
  init_highlight();

  }

 }

}
/*end of en passant*/


/*special case for castling*/
if(p.id=='0'&&ps.id=='K')
{
 int xdiff=0,ydiff=0;
 int rx;

 xdiff=x-ps.x;
 ydiff=y-ps.y;

 printf("Difference between selected space and selected king is %d %d\n",xdiff,ydiff);

 if(xdiff==2&&ydiff==0)
 {
  rx=7;
  pt=main_grid.array[rx+y*8];
  if(pt.moves==0&&ps.moves==0)
  {
   main_grid.array[rx+y*8].id='0';
   rx=5;
   main_grid.array[rx+y*8]=pt;
   main_grid.array[ps.x+ps.y*8].id='0';
   ps.moves++;
   main_grid.array[x+y*8]=ps;
   swap_turn();
   init_highlight();
  }
 }

 if(xdiff==-2&&ydiff==0)
 {
  rx=0;
  pt=main_grid.array[rx+y*8];
  if(pt.moves==0&&ps.moves==0)
  {
   main_grid.array[rx+y*8].id='0';
   rx=3;
   main_grid.array[rx+y*8]=pt;
   main_grid.array[ps.x+ps.y*8].id='0';
   ps.moves++;
   main_grid.array[x+y*8]=ps;
   swap_turn();
   init_highlight();
  }
 }



}
/*end of castling*/

	
   if(p.color!=turn || p.id=='0')
   {
     /*
	 if piece has been selected previously
	 move it there if it has been highlighted as valid move!
	 */
	if(ps.id!='0')
	{
	 if(highlight[x+y*8]>0)
	 {
      move_piece();

      printf("Moving piece to valid space\n");



	 }
	 else
	 {
		 /*printf("piece can't move there\n");*/
	 }
	}
   }

      
	
 SDL_FillRect(surface,NULL,SDL_MapRGB(surface->format,0,0,0));
 chaste_checker();
 chess_grid_draw_highlight();
 chess_draw_pieces();

  /*draw_en_passant();*/

 write_move_rank_file();

 SDL_UpdateWindowSurface(window);

}



















/*
 the real input function which has more code for specific cases and can affect the game
*/
void chaste_chess_check_input()
{

while(SDL_PollEvent(&e))
  {

   if(e.type == SDL_QUIT){loop=0;}
   if(e.type == SDL_KEYUP)
   {
    if(e.key.keysym.sym==SDLK_ESCAPE){loop=0;}

    if(e.key.keysym.sym==SDLK_r)
    {
     init_main_grid();
     turn='W';
     view_flipped=0;
     move_render();
     xy_move_index=0;
    }

    if(e.key.keysym.sym==SDLK_v)
    {
     flip_main_grid();
     move_render();

     /*optionally, print to the move log*/
     fprintf(fp,"flip_main_grid();\nmove_render();\n");
    }

    /*allow undo of previous move*/
    if(e.key.keysym.sym==SDLK_BACKSPACE)
    {
     undo_move_piece();
    }

   }

   mouse_state=0;

   if(e.type == SDL_MOUSEBUTTONDOWN)
   {
    x=e.button.x;
    y=e.button.y;
    mouse_state=1;
    keyboard_shown=0;

    if(x<check_left){printf("Mouse clicked too far left outside of board\n");return;}
    if(x>check_left+check_size){printf("Mouse clicked too far right outside of board\n");return;}

    /*printf("Mouse clicked at position X=%d Y=%d ",x,y);*/

    /*if(e.button.button==SDL_BUTTON_LEFT){printf("SDL_BUTTON_LEFT");}
    if(e.button.button==SDL_BUTTON_RIGHT){printf("SDL_BUTTON_RIGHT");}
    if(e.button.button==SDL_BUTTON_MIDDLE){printf("SDL_BUTTON_MIDDLE");}
    printf("\n");*/


    x=(x-check_left)/main_check.rectsize;
    y=y/main_check.rectsize;

    input_get_rank_and_file(x,y);


    printf("Cartesian Square clicked: X=%d Y=%d\n",x,y);
    printf("Chess Square clicked: %c%c\n",square_file,square_rank);
   }

   if(mouse_state)
   {
    chess_square_select();
   }

  }

}