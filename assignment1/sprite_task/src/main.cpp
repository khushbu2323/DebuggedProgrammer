#include <SDL2/SDL.h>
#include <cmath>
#include <vector>

class sprite_Framework{
public:
 
    sprite_Framework(int window_height, int window_width): sprite_height(window_height), sprite_width(window_width){
        SDL_Init(SDL_INIT_VIDEO);      
        SDL_CreateWindowAndRenderer(sprite_width, sprite_height, 0, &sprite_window, &window_renderer);
        SDL_SetRenderDrawColor(window_renderer, 0, 0, 0, 0);    
        SDL_RenderClear(window_renderer);      
        SDL_RenderPresent(window_renderer);   
                                        
    }


    ~sprite_Framework(){
        SDL_DestroyRenderer(window_renderer);
        SDL_DestroyWindow(sprite_window);
        SDL_Quit();
    }

    void design_circle(int x_cord, int y_cord, int circle_radius){
        SDL_SetRenderDrawColor(window_renderer, 10, 140+x_cord,72 + x_cord,x_cord*y_cord);
        for(int x=x_cord-circle_radius; x<=x_cord+circle_radius; x++){
            for(int y=y_cord-circle_radius; y<=y_cord+circle_radius; y++){
                if((std::pow(y_cord-y,2)+std::pow(x_cord-x,2)) <= 
                    std::pow(circle_radius,2)){
                    SDL_RenderDrawPoint(window_renderer, x, y);
                }
            }
        }
        SDL_RenderPresent(window_renderer);
    }

    void animate_circle(){
        
        
        SDL_Event method;  
        while(!(method.type == SDL_QUIT)){

            for(int i=0; i<sprite_height; i++){
                SDL_Delay(10);  
                SDL_PollEvent(&method);  
                if(method.type == SDL_QUIT) return;
                SDL_SetRenderDrawColor(window_renderer, 0, 0, 0, 0);
                SDL_RenderClear(window_renderer);
                for(int k=1 ;k<5;k++)
                {
                design_circle(sprite_width/k, i, 20+k);
                }

            }

            for(int i=sprite_height; i>0; i--){
                SDL_Delay(10);  
                SDL_PollEvent(&method); 
                if(method.type == SDL_QUIT) return;
                SDL_SetRenderDrawColor(window_renderer, 0, 0, 0, 0);
                SDL_RenderClear(window_renderer);
                  for(int k=1 ;k<5;k++)
                {
                design_circle(sprite_width/k, i, 20+k);
                }

            }
        }
        
    }

private:
    int sprite_height;   
    int sprite_width;    
    SDL_Renderer *window_renderer = NULL;    
    SDL_Window *sprite_window = NULL;      
};

int main(int argc, char * argv[]){

  
    sprite_Framework fw(400, 400);
    fw.animate_circle();
    
    return 1;
}
