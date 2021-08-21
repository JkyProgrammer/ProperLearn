#include "guimain.h"
#include "FeedForwardNeuralNet.h"

#include <math.h>
#include <algorithm>
#include <iostream>

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "../deps/raygui.h"
#include "../deps/ricons.h"

using namespace std;

int gui_main () {
    
    SetTraceLogLevel (LOG_WARNING | LOG_ERROR);
    InitWindow(800, 800, "ProperLearn Neural Net Visualiser");
    SetWindowState (FLAG_WINDOW_RESIZABLE);
    SetWindowMinSize(600, 400);  
    SetTargetFPS(30);

    FeedForwardNeuralNet ffnn;
    ffnn.initialise(5, new int[5]{3, 8, 9, 6, 3});

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        int verticalCentre = GetScreenHeight ()/2;
        int layers = ffnn.count_layers();
        int maxnodes = 0;
        for (int l = 0; l < layers; l++) {
            int nodes = 0;
            if (l == 0) nodes = ffnn.count_inputs();
            else nodes = ffnn.count_nodes(l-1);
            if (nodes > maxnodes) maxnodes = nodes;
        }

        int nseparation = (GetScreenHeight ()-60)/(maxnodes-1);
        int lseparation = (GetScreenWidth ()-60)/(layers-1);
        for (int l = 0; l < layers; l++) {
            int nodes = 0;
            if (l == 0) nodes = ffnn.count_inputs();
            else nodes = ffnn.count_nodes(l-1);

            int lastnodes = 0;
            if (l == 0) lastnodes = -1;
            else if (l == 1) lastnodes = ffnn.count_inputs();
            else if (l > 1) lastnodes = ffnn.count_nodes(l-2);
            int lastInitialYOffset = verticalCentre - (((float)(lastnodes-1)/(float)2)*nseparation);
            int initialYOffset = verticalCentre - (((float)(nodes-1)/(float)2)*nseparation);
            for (int n = 0; n < nodes; n++) {
                int nodex = 30+(l*lseparation);
                int nodey = initialYOffset+(n*nseparation);
                DrawCircle (nodex, nodey, 6, BLUE);
                if (lastnodes == -1) continue;
                for (int n2 = 0; n2 < lastnodes; n2++) {
                    float weight = ffnn.getWeights (l-1, n)[n2];
                    DrawLineEx ({30+((l-1)*lseparation), lastInitialYOffset+(n2*nseparation)}, {nodex, nodey}, abs(weight)*5, weight >= 0 ? GREEN : RED);
                }
            }
        }
        // // Draw the rendered image      
        // Vector2 v {0,0};
        // DrawTextureEx (tex, v, 0, (float)imageDimension/(float)tex.height, WHITE);
        // // Draw Console
        // int buttonOffset = 0;
        // GuiTextBox((Rectangle){(float)imageDimension, BUTTON_HEIGHT*(float)buttonOffset, (float)controlPanelWidth, BUTTON_HEIGHT}, (char*)consoleText.c_str(), 1, false);
        // // Draw "Render Image" button
        // buttonOffset++;
        // buttonStates[0] = GuiButton((Rectangle){(float)imageDimension, BUTTON_HEIGHT*(float)buttonOffset, (float)controlPanelWidth, BUTTON_HEIGHT}, "Render Image");
        // // Draw render progress bar
        // buttonOffset++;
        // GuiProgressBar ((Rectangle){(float)imageDimension, BUTTON_HEIGHT*(float)buttonOffset, (float)controlPanelWidth, BUTTON_HEIGHT}, "", "", percent, 0, 100);
        // // Draw zoom buttons
        
        EndDrawing();
    }

    //UnloadImage (bufferImage);
    //UnloadTexture (tex);
    CloseWindow();
    return 0;
}