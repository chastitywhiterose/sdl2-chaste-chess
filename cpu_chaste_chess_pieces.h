/*

sdl_chaste_chess_pieces.h

This file is meant to be used for loading each chess piece from its own file. Keeping them separate makes things easier to code even those it is more verbose


*/

/*variable to store how big one square of the checkerboard in loaded image is.*/
int t_rect_size=0;

/*variable to store difference between texture squares and program squares*/
int t_rect_diff=0;

struct chess_piece_image
{
 char color;
 char id;
 int moves;
 int x,y;
};







SDL_Surface *load_piece(char *filename)
{
 int w,h;
 SDL_Surface *temp_surface;


 /* Open the image file */

 temp_surface = IMG_Load(filename);
 if (!temp_surface)
 {
  SDL_Log("Couldn't load %s: %s\n", filename, SDL_GetError());
  return 0;
 }
 else
 {
  /*SDL_QueryTexture(temp_texture, NULL, NULL, &w, &h);*/
  w=temp_surface->w;
  h=temp_surface->h;
  printf("Image '%s' loaded\n",filename);
  printf("Surface dimensions w=%d,h=%d\n",w,h);

  t_rect_size=w;
  printf("Square size of texture is %d\n",t_rect_size);

  t_rect_diff=main_check.rectsize-t_rect_size;
  printf("Square size difference is %d\n",t_rect_diff);
  printf("If this value is zero, it fits correctly into a square on the Chessboard.\n");

 }
 return temp_surface;
}


SDL_Surface *pawn_white;
SDL_Surface *pawn_black;

void load_pawns()
{
 pawn_white=load_piece("./piece/90/wP.png");
 pawn_black=load_piece("./piece/90/bP.png");
}

SDL_Surface *rook_white;
SDL_Surface *rook_black;

void load_rooks()
{
 rook_white=load_piece("./piece/90/wR.png");
 rook_black=load_piece("./piece/90/bR.png");
}

SDL_Surface *knight_white;
SDL_Surface *knight_black;

void load_knights()
{
 knight_white=load_piece("./piece/90/wN.png");
 knight_black=load_piece("./piece/90/bN.png");
}

SDL_Surface *bishop_white;
SDL_Surface *bishop_black;

void load_bishops()
{
 bishop_white=load_piece("./piece/90/wB.png");
 bishop_black=load_piece("./piece/90/bB.png");
}


SDL_Surface *queen_white;
SDL_Surface *queen_black;

void load_queens()
{
 queen_white=load_piece("./piece/90/wQ.png");
 queen_black=load_piece("./piece/90/bQ.png");
}

SDL_Surface *king_white;
SDL_Surface *king_black;

void load_kings()
{
 king_white=load_piece("./piece/90/wK.png");
 king_black=load_piece("./piece/90/bK.png");
}








void chess_draw_pieces()
{
 int x,y,x1,y1;
 struct chess_piece p;
 SDL_Rect rect_dst;
 SDL_Surface *texture;

 /*printf("t_rect_size=%d\n",t_rect_size);*/

 rect_dst.w=t_rect_size;
 rect_dst.h=t_rect_size;

 rect_src.x=0;
 rect_src.y=0;
 rect_src.w=t_rect_size;
 rect_src.h=t_rect_size;





 y=0;
 while(y<8)
 {
  x=0;
  while(x<8)
  {
   p=main_grid.array[x+y*8];

   if(p.id!='0')
   {

   /*printf(" %c%c",p.color,p.id);*/
   /*printf(" %c",p.id);*/
   
    sprintf(text,"%c",p.id);

    x1=x*main_check.rectsize;
    y1=y*main_check.rectsize;

    /*beginning of piece source selection*/
    if(p.color=='B')
    {
     if(p.id=='P')
     {
      texture=pawn_black;
     }
     if(p.id=='R')
     {
      texture=rook_black;
     }
     if(p.id=='N')
     {
      texture=knight_black;
     }
     if(p.id=='B')
     {
      texture=bishop_black;
     }
     if(p.id=='Q')
     {
      texture=queen_black;
     }
     if(p.id=='K')
     {
      texture=king_black;
     }
    }

    if(p.color=='W')
    {
     if(p.id=='P')
     {
      texture=pawn_white;
     }
     if(p.id=='R')
     {
      texture=rook_white;
     }
     if(p.id=='N')
     {
      texture=knight_white;
     }
     if(p.id=='B')
     {
      texture=bishop_white;
     }
     if(p.id=='Q')
     {
      texture=queen_white;
     }
     if(p.id=='K')
     {
      texture=king_white;
     }
    }
    /*end of piece source selection*/
 
    rect_dst.x=check_left+x1+t_rect_diff/2;
    rect_dst.y=y1+t_rect_diff/2;

    /*SDL_RenderCopy(renderer, texture, &rect_src, &rect_dst);*/

    SDL_BlitSurface(texture,&rect_src,surface,&rect_dst);

   }

   x+=1;
  }
  y+=1;
 }

}