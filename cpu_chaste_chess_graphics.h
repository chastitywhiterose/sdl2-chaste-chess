

void chess_grid_draw_highlight()
{
 int x,y;

 y=0;
 while(y<8)
 {
  x=0;
  while(x<8)
  {
   /*highlight[x+y*8]=0;*/

   rect.x=check_left+x*main_check.rectsize;
   rect.y=y*main_check.rectsize;
   rect.w=main_check.rectsize;
   rect.h=main_check.rectsize;

   if(highlight[x+y*8]!=0)
   {

    if(highlight[x+y*8]==1)
    {
     /*this space will be marked green meaning "go" because you can move here and it is blank*/
     SDL_FillRect(surface,&rect,SDL_MapRGB(surface->format,0x00,0xFF,0x00));
    }
    if(highlight[x+y*8]==-1)
    {
     /*this space will be marked red meaning "stop" because you can't move here and the piece is the same color as the piece you are moving*/
     SDL_FillRect(surface,&rect,SDL_MapRGB(surface->format,0xFF,0x00,0x00));
    }
    if(highlight[x+y*8]==2)
    {
     /*this space will be marked blue to indicate a piece can be captured*/
     SDL_FillRect(surface,&rect,SDL_MapRGB(surface->format,0x00,0x00,0xFF));
    }

   }

   x+=1;
  }
  y+=1;
 }

}




/*
 this function is not complete!
 the code for selection is not written!
*/
void chess_grid_promo_screen()
{
 int y=4*main_check.rectsize;

 SDL_Surface *texture; /*this texture variable points to a surface only for this function*/

 /*first, clear the screen*/
 SDL_FillRect(surface,NULL,SDL_MapRGB(surface->format,0,0,0));

 /*set up the initial source rectange*/
 rect_src.x=0;
 rect_src.y=0;
 rect_src.w=t_rect_size;
 rect_src.h=t_rect_size;

 /*set size of dest rectangle. location will change constantly*/
 rect.w=main_check.rectsize;
 rect.h=main_check.rectsize;

 rect.x=check_left+main_check.rectsize*0;
 rect.y=y;
 /*SDL_FillRect(surface,&rect,SDL_MapRGB(surface->format,0xFF,0x00,0x00));*/
 texture=rook_white;
 SDL_BlitSurface(texture,&rect_src,surface,&rect);

 rect.x=check_left+main_check.rectsize*2;
 rect.y=y;
 /*SDL_FillRect(surface,&rect,SDL_MapRGB(surface->format,0x00,0xFF,0x00));*/
 texture=knight_white;
 SDL_BlitSurface(texture,&rect_src,surface,&rect);


 rect.x=check_left+main_check.rectsize*4;
 rect.y=y;
 /*SDL_FillRect(surface,&rect,SDL_MapRGB(surface->format,0x00,0x00,0xFF));*/
 texture=bishop_white;
 SDL_BlitSurface(texture,&rect_src,surface,&rect);


 rect.x=check_left+main_check.rectsize*6;
 rect.y=y;
 /*SDL_FillRect(surface,&rect,SDL_MapRGB(surface->format,0xFF,0xFF,0xFF));*/
 texture=queen_white;
 SDL_BlitSurface(texture,&rect_src,surface,&rect);

 SDL_UpdateWindowSurface(window);

 /*wait for user input on this screen*/
 loop=1;
 while(loop)
 {
  while(SDL_PollEvent(&e))
  {
   if(e.type==SDL_QUIT){loop=0;}
   if(e.type==SDL_KEYUP){if(e.key.keysym.sym==SDLK_ESCAPE){loop=0;}}
  }
 }
 loop=1;

}
