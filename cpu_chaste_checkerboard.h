/*
sdl_chaste_checkerboard.h

This file shows my own personal method of drawing a checkerboard in SDL2 using a renderer.
*/

struct checkerboard
{
 int x_begin,y_begin,x_end,y_end;
 int rectsize;
};

struct checkerboard main_check;

/*set up initial state to allow drawing checkerboard to whole screen*/
void init_checkerboard()
{
 main_check.x_begin=0;
 main_check.y_begin=0;
 main_check.x_end=width;
 main_check.y_end=height;
 main_check.rectsize=32;
}




/*
 this function draws a checkerboard. it is highly optimized because it does not switch colors during the function. it only draws half of the checkerboard squares and leaves the remaining areas the same as the background
*/
void chaste_checker()
{
 int x,y,index,index1;
 index=0;

 rect.w=main_check.rectsize;
 rect.h=main_check.rectsize;

 y=main_check.y_begin;
 while(y<main_check.y_end)
 {
  index1=index;
  x=main_check.x_begin;
  while(x<main_check.x_end)
  {

   rect.x=x;
   rect.y=y;
   if(index==1)
   {
    /*SDL_SetRenderDrawColor(renderer,g0,g0,g0,255);
    SDL_RenderFillRect(renderer,&rect);*/
    SDL_FillRect(surface,&rect,SDL_MapRGB(surface->format,g0,g0,g0));
   }
   if(index==0)
   {
    /*SDL_SetRenderDrawColor(renderer,g1,g1,g1,255);
    SDL_RenderFillRect(renderer,&rect);*/
    SDL_FillRect(surface,&rect,SDL_MapRGB(surface->format,g1,g1,g1));
   }
   index^=1;
   x+=main_check.rectsize;
  }
  index=index1^1;
  y+=main_check.rectsize;
 }

}
























