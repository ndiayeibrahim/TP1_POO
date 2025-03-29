#include "entrypoint.h"
#include "raylib.h"
#include <time.h>
#include <vector>

#define RECT_SIZE 40
#define MAX_COL 20
#define MAX_ROW 20
#define WIN_W MAX_COL * RECT_SIZE
#define WIN_H MAX_ROW * RECT_SIZE

class Grille {
private:
    bool zombies[MAX_ROW][MAX_COL] = {0}; 
public:
    Grille(){
        zombies[5][5] = true;
        zombies[5][6] = true;
        zombies[5][7] = true;
        
    
        
    }
    void mettreAJour(){
        bool nouvelleGrille[MAX_ROW][MAX_COL] = {0};
        for( int y =0; y < MAX_ROW; ++y){
            for(int x = 0; x < MAX_COL; ++x){
                int voisinsVivants = compterVoisinsVivants(y,x);
                if(zombies[y][x]){
                    nouvelleGrille[y][x] = ( voisinsVivants == 2 || voisinsVivants == 3);
                }else{
                    nouvelleGrille[y][x] = ( voisinsVivants == 3);
                }
            }
        }
        
        for( int y =0; y < MAX_ROW; ++y){
            for(int x = 0; x < MAX_COL; ++x){
                zombies[y][x] = nouvelleGrille[y][x];
            }
        }
    }
    int compterVoisinsVivants ( int y, int x ){
        int count = 0;
        for(int i = -1; i <= 1; ++i){
            for( int j = -1; j <=1; ++j){
                if(i==0 && j==0)continue;
                int VoisinY = y + i;
                int VoisinX = x + j;

                // Vérifier les limites de la grille
                if(VoisinY >= 0 && VoisinY < MAX_ROW && VoisinX >= 0 && VoisinX < MAX_COL){
                    if(zombies[VoisinY][VoisinX]){
                        count++;
                    }
                }
            }
        }
        return count;

    }

    void afficher(){
        Vector2 mousePos = GetMousePosition();
        for(int y = 0; y < MAX_ROW;y++){
            for(int x = 0; x < MAX_COL;++x){
                Rectangle get_rekt = CLITERAL(Rectangle){
                    .x=(float)(x*RECT_SIZE ),.y=(float)(y*RECT_SIZE),
                    .width=RECT_SIZE,.height=RECT_SIZE
                };
                // J'ai pu utiliser le souris grace a duck.ia pour que quand je tape sur une case avec le souris il apparait un cellule vivantes
                // ce qui permettra les cellules de se propager

                if(IsMouseButtonDown(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePos, get_rekt)){
                    zombies[y][x] = true;


                }
                
                DrawRectangle( get_rekt.x, get_rekt.y, get_rekt.width, get_rekt.height , WHITE);
                // Color  borderColor = (x % 2 == 0) ? DARKGRAY : LIGHTGRAY;
                DrawRectangleLinesEx(
                    get_rekt,
                    2,
                    DARKGRAY
                );
                
                if(zombies[y][x]){
                    DrawRectangle( get_rekt.x, get_rekt.y, get_rekt.width, get_rekt.height , BLACK);
                }    
                
            }
        }
    }
    void toggleCell( int mouseX, int mouseY){
        int x = mouseX / RECT_SIZE;
        int y = mouseY / RECT_SIZE;

        // vérifier si les coordonée sont dans les limites de la grille 
        if( x >= 0 && x < MAX_COL && y >= 0 && y < MAX_ROW){
            zombies[y][x] = !zombies[y][x];
        }

    
    }

};




void raylib_start(void){
    InitWindow(WIN_W,WIN_H,"conways test");
    SetTargetFPS(5);
    Grille grille; // créer une instance de la classe grille
    while(!WindowShouldClose()){
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            Vector2 mousePos = GetMousePosition();
            grille.toggleCell(mousePos.x, mousePos.y); // inverser l'etat de la cellule sous le souris 
        }

        grille.mettreAJour();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        grille.afficher();
        

        EndDrawing();
    }
    CloseWindow();
}