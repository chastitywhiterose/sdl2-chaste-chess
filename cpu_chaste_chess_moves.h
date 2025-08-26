/*cpu_chaste_chess_moves.h*/



/*
redraw the screen after the move
*/


void get_rank_and_file(int x,int y)
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


void write_move_rank_file()
{

 text_color=0xFFFFFF;
 text_scale=4;
 sprintf(text,"%c%c->%c%c\n",square_file_source,square_rank_source,square_file_dest,square_rank_dest);
 chaste_font_draw_string_scaled_alpha(text,main_font.char_width*text_scale*1,main_check.rectsize*4,text_scale);

 text_scale=5;

 chaste_palette_index=chaste_palette_index1;

 chaste_font_draw_string_scaled_special("Chaste\nChess",16,32,text_scale);

 chaste_palette_index1++;
 if(chaste_palette_index1>=chaste_palette_length)
 {
  chaste_palette_index1=0;
 }

}

void move_render()
{
 /*SDL_SetRenderDrawColor(renderer,0,0,0,255);
 SDL_RenderFillRect(renderer,NULL);*/
 SDL_FillRect(surface,NULL,SDL_MapRGB(surface->format,0,0,0));
 chaste_checker();
 chess_draw_pieces();
 /*SDL_RenderPresent(renderer);*/

 write_move_rank_file();

 SDL_UpdateWindowSurface(window);
}


void move(char *move)
{
 int x=-1,y=-1,x1,y1;
 char *p=move;
 struct chess_piece main_piece;


 printf("%s\n",move);

 /*move processing begin*/
 
 if(islower(*p))
 {
  printf("letter '%c' implies pawn move\n",*p);

  x=*p-'a';

  y=0;
  while(y<8)
  {
   main_piece=main_grid.array[x+y*8];
   if(main_piece.color==turn&&main_piece.id=='P'){break;}
   y++;
  }

  printf("coordinate of source pawn is: %d,%d\n",x,y);

  p++;

  if(isdigit(*p))
  {
   printf("number %c impies target location\n",*p);
  }

  x1=x;
  y1=8-(*p-'0');

  printf("destination for pawn is coord %d,%d\n", x1,y1);

  /*now perform the movement!*/

  main_grid.array[x+y*8].id='0';
  main_grid.array[x1+y1*8]=main_piece;

 }

 /*move processing end*/

 /*swap whose turn it is*/
  if(turn=='W')
  {
   turn='B';
  }
  else
  {
   turn='W';
  }

 chess_grid_print();
 move_render();
}






void move_xy(int x,int y,int x1,int y1)
{
 Uint32 pixel,r,g,b;
 int x_src,y_src,x_dst,y_dst;
 int xdiff=0,ydiff=0;
 struct chess_piece main_piece;

 SDL_Surface *texture;

 get_rank_and_file(x,y);
 square_file_source=square_file;
 square_rank_source=square_rank;

 get_rank_and_file(x1,y1);
 square_file_dest=square_file;
 square_rank_dest=square_rank;

  main_piece=main_grid.array[x+y*8];

  main_grid.array[x+y*8].id='0';

    /*
     beginning of piece source selection
     select the image drawn based on id of source piece only once
    */
    if(main_piece.color=='B')
    {
     if(main_piece.id=='P')
     {
      texture=pawn_black;
     }
     if(main_piece.id=='R')
     {
      texture=rook_black;
     }
     if(main_piece.id=='N')
     {
      texture=knight_black;
     }
     if(main_piece.id=='B')
     {
      texture=bishop_black;
     }
     if(main_piece.id=='Q')
     {
      texture=queen_black;
     }
     if(main_piece.id=='K')
     {
      texture=king_black;
     }
    }

    if(main_piece.color=='W')
    {
     if(main_piece.id=='P')
     {
      texture=pawn_white;
     }
     if(main_piece.id=='R')
     {
      texture=rook_white;
     }
     if(main_piece.id=='N')
     {
      texture=knight_white;
     }
     if(main_piece.id=='B')
     {
      texture=bishop_white;
     }
     if(main_piece.id=='Q')
     {
      texture=queen_white;
     }
     if(main_piece.id=='K')
     {
      texture=king_white;
     }
    }
    /*end of piece source selection*/


x_src=check_left+x*main_check.rectsize;
y_src=y*main_check.rectsize;
x_dst=check_left+x1*main_check.rectsize;
y_dst=y1*main_check.rectsize; 

/*printf("From pixel location %d,%d\n",x_src,y_src);
printf("To pixel location %d,%d\n",x_dst,y_dst);*/

x_step=x1-x;
y_step=y1-y;
/*printf("x_step = %d y_step = %d\n",x_step,y_step);*/

 rect_src.x=0;
 rect_src.y=0;
 rect_src.w=t_rect_size;
 rect_src.h=t_rect_size;

 rect_dst.x=x_src;
 rect_dst.y=y_src;
 rect_dst.w=t_rect_size;
 rect_dst.h=t_rect_size;

 delay=1000/fps;

  /*redraw the whole scene before each piece animation.*/
  move_render();

 while(rect_dst.x!=x_dst || rect_dst.y!=y_dst)
 {
  sdl_time = SDL_GetTicks();
  sdl_time1 = sdl_time+delay;

  rect_dst.x+=x_step;
  rect_dst.y+=y_step;

  /*printf("rectangle at = %d,%d\n",rect_dst.x,rect_dst.y);*/






  /*start of special color section*/
      pixel=chaste_palette[chaste_palette_index];
      
      r=(pixel&0xFF0000)>>16;
      g=(pixel&0x00FF00)>>8;
      b=(pixel&0x0000FF);
      
      /*SDL_SetRenderDrawColor(renderer,r,g,b,255);*/
      chaste_next_color();
  /*end of special color section*/

  /*the next line is the renderer way to draw the colored squares*/
  /*SDL_RenderFillRect(renderer,&rect_dst);*/

  /*the next line draws squares directly to the window surface. It is identical to the above.*/
  SDL_FillRect(surface,&rect_dst,SDL_MapRGB(surface->format,r,g,b));


  /*SDL_RenderCopy(renderer, texture, &rect_src, &rect_dst);*/
  /*SDL_RenderPresent(renderer);*/

  SDL_BlitSurface(texture,&rect_src,surface,&rect_dst);
  SDL_UpdateWindowSurface(window);

  /*time loop used to slow the game down so users can see it*/
  while(loop==1 && sdl_time<sdl_time1)
  {
   sdl_time=SDL_GetTicks();
   while(SDL_PollEvent(&e))
   {
    if(e.type==SDL_QUIT){loop=0;}
    if(e.type==SDL_KEYDOWN){if(e.key.keysym.sym==SDLK_ESCAPE){loop=0;}}
   }
  }

 }

  main_piece.moves++; /*must add to move counter for piece or pawns will not be correct*/

  /*handle promotion of a pawn*/
  if(main_piece.id=='P')
  {
   /*chess_grid_promo_screen();*/
   if(y1==0||y1==7){main_piece.id=promo_id;}
  }

  pieces_captured[xy_move_index]=main_grid.array[x1+y1*8]; /*whatever was here will be saved as a captured piece*/
  main_grid.array[x1+y1*8]=main_piece;

 /*section for en passant correction*/

  /*set direction of pawn based on whose turn it is*/
  if(turn=='B'){dir=1;} 
  if(turn=='W'){dir=-1;}

  xdiff=abs(x-x1);
  ydiff=abs(y-y1);

  /*printf("xdiff=%d ydiff=%d\n",xdiff,ydiff);*/

  /*if pawn has moved two spaces, set the en passant value*/
  if(xdiff==0&&ydiff==2)
  {
   en_passant.id='P';
   en_passant.color=turn;
   en_passant.x=x1;
   en_passant.y=y1-dir;
   /*printf("en_passant marked at %d,%d\n",en_passant.x,en_passant.y);*/
  }
  else
  {

   if(en_passant.id=='P') /*pawn has captured empty square that is marked for en passant*/
   {

    if(x1==en_passant.x&&y1==en_passant.y)
    {
     main_grid.array[x1+(y1-dir)*8].id='0';
     /*printf("en_passant captured at %d,%d\n",en_passant.x,en_passant.y);*/
    }
   }

   en_passant.id='0';
  }
  

  /*printf("direction==%d\n",dir);*/

 /*end of en passant correction section*/

  move_render();


 /*move processing end*/




 /*swap whose turn it is*/
  if(turn=='W')
  {
   turn='B';
  }
  else
  {
   turn='W';
  }

 /*optionally, print to the file move log*/
 fprintf(fp,"move_xy(%d,%d,%d,%d);\n",x,y,x1,y1);

 /*optionally, print a text form of the board to the terminal*/
 /*chess_grid_print();*/

}
