#include "raylib.h"
#include <string>

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runntingTime;
};

bool isOnGround(AnimData data, int windowHeight)
{
   return data.pos.y >= (windowHeight - 80) - data.rec.height;
}
AnimData updateAnimData(AnimData data, float dT, int maxFrame)
{
    data.runntingTime += dT;
    if (data.runntingTime >= data.updateTime)
    {
        data.runntingTime = 0.0;
        data.rec.x = data.frame * data.rec.width;
        data.frame++;
        if (data.frame > maxFrame)
        {
            data.frame = 0;
        }
    }
    return data;
}

int main()
{
    int WindowDimensions [2];
    WindowDimensions [0] = 1280;
    WindowDimensions [1] = 720;

    //window dimensions
    const int windowWidth {WindowDimensions [0]};
    const int windowHeight {WindowDimensions [1]};

    InitWindow(WindowDimensions[0], WindowDimensions[1], "Glino");
       
    //Sounds
    InitAudioDevice();
    Sound Jump = LoadSound("Sounds/jump.wav");
    Sound melonPickUp = LoadSound("Sounds/pickupCoin.wav");
    Sound kill = LoadSound("Sounds/hitHurt.wav");
    Music PixelKing = LoadMusicStream("Sounds/Pixel Kings.wav");

    // Texture Backround
    Texture2D mountain =LoadTexture("textures/mountain.png");
    AnimData mountainData;
    mountainData.rec.width = mountain.width;
    mountainData.rec.height = mountain.height;
    mountainData.rec.x = 0;
    mountainData.rec.y = 0;
    mountainData.pos.x = 0;
    mountainData.pos.y = 0;
    mountainData.frame = 0;
    mountainData.runntingTime = 0;
    mountainData.updateTime =0;

    Texture2D birds =LoadTexture("textures/birds.png");
    AnimData birdsData;
    birdsData.rec.width = birds.width;
    birdsData.rec.height = birds.height;
    birdsData.rec.x = 0;
    birdsData.rec.y = 0;
    birdsData.pos.x = 0;
    birdsData.pos.y = 0;
    birdsData.frame = 0;
    birdsData.runntingTime = 0;
    birdsData.updateTime =0;

    Texture2D treesBack =LoadTexture("textures/treesBack.png");
    AnimData treesBackData;
    treesBackData.rec.width = treesBack.width;
    treesBackData.rec.height = treesBack.height;
    treesBackData.rec.x = 0;
    treesBackData.rec.y = 0;
    treesBackData.pos.x = treesBack.width;
    treesBackData.pos.y = 0;
    treesBackData.frame = 0;
    treesBackData.runntingTime = 0;
    treesBackData.updateTime =0;

Texture2D treesFront =LoadTexture("textures/treesFront.png");
    AnimData treesFrontData;
    treesFrontData.rec.width = treesFront.width;
    treesFrontData.rec.height = treesFront.height;
    treesFrontData.rec.x = 0;
    treesFrontData.rec.y = 0;
    treesFrontData.pos.x = treesFront.width;
    treesFrontData.pos.y = 0;
    treesFrontData.frame = 0;
    treesFrontData.runntingTime = 0;
    treesFrontData.updateTime =0;


    
    //Textures Dino
    
    Texture2D Dino = LoadTexture("textures/dino.png");
    AnimData dinoData;
    dinoData.rec.width = Dino.width/4;
    dinoData.rec.height = Dino.height;
    dinoData.rec.x = 0;
    dinoData.rec.y = 0;
    dinoData.pos.x = windowWidth/3 - dinoData.rec.width/2;
    dinoData.pos.y = ((windowHeight - 80) - dinoData.rec.height);
    dinoData.frame = 0;
    dinoData.runntingTime = 0;
    dinoData.updateTime =  0.1;

    
    //Texture Laeva
    Texture2D Laeva = LoadTexture("textures/LAEVA.png");
    const int NumOfLaevas{6};
    int LaevaDist{100};
           
    AnimData Laevas[NumOfLaevas];
    for (int i = 0; i < NumOfLaevas; i++)
    {
        Laevas[i].rec.x = 0.0;
        Laevas[i].rec.y = 0.0;
        Laevas[i].rec.width = Laeva.width/4;
        Laevas[i].rec.height = Laeva.height;
        Laevas[i].pos.x = windowWidth + LaevaDist;
        Laevas[i].pos.y = (windowHeight - 100) - Laeva.height;
        Laevas[i].frame = 0.0;
        Laevas[i].runntingTime = 0.0;
        Laevas[i].updateTime = 0.2;
        LaevaDist += 10000;
    }
    
    //Texture Watermelon
    Texture2D melon = LoadTexture("textures/Yellow Watermelon2.png");
    const int NumOfMelon{1};
    int MelonDist{1000};
            
    AnimData Melons[NumOfMelon];
    for (int i = 0; i < NumOfMelon; i++)
    {
        Melons[i].rec.x = 0.0;
        Melons[i].rec.y = 0.0;
        Melons[i].rec.width = melon.width;
        Melons[i].rec.height = melon.height;
        Melons[i].pos.x = windowWidth + MelonDist;
        Melons[i].pos.y = (windowHeight - 200) - melon.height;
        Melons[i].frame = 0.0;
        Melons[i].runntingTime = 0.0;
        Melons[i].updateTime = 0.2;
        MelonDist += 2000;
    }
    //Dino Is ducking
    bool DinoIsDuck{false};
    // Dino Velocity 
    int Dino_velocity{0};    
    // Dino Jump Hight (pixels/s/s)/frame
    const int jump_hight{800};
    //Gravity (pixels/s/s)/frame
    const int gravity{2'000};
    //Object Speed
    float ObjectSpeed{300};
    //Back speed
    float mountainSpeed{30};
    float birdsSpeed{20};
    float treesFrontSpeed{100};
    float treesBackSpeed{70};
    //points
    int pointNum{0};
    float pointRunningTime{0};
    float pointUpdateTime {1};
    //Duck cooldown
    float DuckRunningTime{0};
    float DuckUpdateTime {0.45};
    //Collisions
    bool LaevaCollisions{false};
    bool MelonCollisions{false};
    //Menu
    bool Menu{true};
    bool MusicOn{true};
  
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
    if(Menu)
    {
            DrawText("Welcome to the Story of Glino!", 
            100, 100, 40, BLACK);
            DrawText("It wasn't asteriods that killed the Dinos...", 
            100, 150, 40, BLACK);
            DrawText("It was an axe called Laeva!", 
            100, 200, 40, RED);
            DrawText("Help Glino avoiding avoiding certain DEATH!", 
            100, 250, 40, BLACK);
            DrawTextureRec(Dino, dinoData.rec, dinoData.pos, WHITE);
            DrawText("CONTROLS", 
            850, 450, 40, RED);
            DrawText(">>SPACE<< TO JUMP OVER AXES", 
            800, 500, 20, BLUE);
            DrawText(">>S<< TO DUCK UNDER AXES", 
            800, 550, 20, BLUE);
            DrawText(">>Q<< TO TURN MUSIC OFF",
            800, 600, 20, BLUE);
            DrawText(">>E<< TO TURN MUSIC ON",
            800, 650, 20, BLUE);
            DrawText("ENTER TO START", 
            100, 400, 60, RED);

            if (IsKeyPressed(KEY_ENTER))
            {Menu = false;
            }
            if (IsKeyPressed(KEY_Q))
            {
                MusicOn = false;
            }
            
    }
    else
    {
        


        if (LaevaCollisions)
        {
            

            DrawText("Game Over, Glino Died :(", windowWidth/2 - 200, 200, 60, RED);
            std::string points = "Score: ";
            DrawText("ENTER TO RESTART", windowWidth/2 - 200, 300, 60, RED);
            points.append(std::to_string(pointNum), 0, 999); 
            DrawText(points.c_str(), windowWidth/2 - 200, 400, 30, BLUE);
            StopMusicStream(PixelKing);   
            DrawText("CONTROLS", 
            850, 450, 40, RED);
            DrawText(">>SPACE<< TO JUMP OVER AXES", 
            800, 500, 20, BLUE);
            DrawText(">>S<< TO DUCK UNDER AXES", 
            800, 550, 20, BLUE);
            DrawText(">>Q<< TO TURN MUSIC OFF", 
            800, 600, 20, BLUE);
            DrawText(">>E<< TO TURN MUSIC ON",
            800, 650, 20, BLUE);
            
            if (IsKeyPressed(KEY_ENTER))
            {
                LaevaCollisions = false;
                pointNum = 0;

                int LaevaDist = 100;
                for (int i = 0; i < NumOfLaevas; i++)
                {
                    Laevas[i].rec.x = 0.0;
                    Laevas[i].rec.y = 0.0;
                    Laevas[i].rec.width = Laeva.width/4;
                    Laevas[i].rec.height = Laeva.height;
                    Laevas[i].pos.x = windowWidth + LaevaDist;
                    Laevas[i].pos.y = (windowHeight - 100) - Laeva.height;
                    Laevas[i].frame = 0.0;
                    Laevas[i].runntingTime = 0.0;
                    Laevas[i].updateTime = 0.2;
                    LaevaDist += 10000;
                }                           
                
                for (int i = 0; i < NumOfMelon; i++)
                {
                Melons[i].pos.x = windowWidth + GetRandomValue(2000,20000) ;
                }
                ObjectSpeed = 300;
                mountainSpeed = 30;
                birdsSpeed = 20;
                treesFrontSpeed =100;
                treesBackSpeed = 70;
            }
        }
    
                
        else
        {
        if (dinoData.pos.y > (windowHeight - 80) - dinoData.rec.height)
        {
            dinoData.pos.y = (windowHeight - 80) - dinoData.rec.height;
        }

        //Music Logic
        if (MusicOn)
        {
        PlayMusicStream(PixelKing);  
        UpdateMusicStream(PixelKing);
        }

        if (IsKeyPressed(KEY_Q)&& MusicOn)
        {
                MusicOn = false;
        }
        if (IsKeyPressed(KEY_E)&& !MusicOn)
        {
                MusicOn = true;
        } 

        //Delta Time
        float dt{GetFrameTime()};
        
                
        //Game Logic

        //Points Health
        pointRunningTime += dt;
        if (pointRunningTime >= pointUpdateTime)
        {   
        pointRunningTime = 0.0;
        pointNum++;
        if (ObjectSpeed<700)
        {
            ObjectSpeed+=10;
            mountainSpeed+=2;
            treesBackSpeed+=4;
            treesFrontSpeed+=6;
        }
        
        }
        
        
        
        std::string points = "Score: ";
        points.append(std::to_string(pointNum), 0, 999);
        DrawText(points.c_str(), windowWidth/2 - 200, 100, 30, RED);    

                
        
        // Ground check
        if (isOnGround(dinoData, windowHeight))
        {
            Dino_velocity = 0;
        }
        else{
            //Apply gravity
        Dino_velocity += gravity * dt;
        
        }
                
        for (AnimData Laeva :Laevas)
        {
            float Laevpad{30};
            Rectangle LaevRec {
                Laeva.pos.x + Laevpad,
                Laeva.pos.y + Laevpad,
                Laeva.rec.width - 2*Laevpad,
                Laeva.rec.height - 2*Laevpad
            };
            float DinoPad{30};            
            Rectangle dinoRec {
                dinoData.pos.x + DinoPad,
                dinoData.pos.y + DinoPad,
                dinoData.rec.width - 2*DinoPad,
                dinoData.rec.height - 2*DinoPad
            };
                        
            if (CheckCollisionRecs(LaevRec, dinoRec) && !DinoIsDuck)
            {
                LaevaCollisions = true;
                PlaySound(kill);
            }
            
        }
        //Duck
        if ((IsKeyPressed(KEY_S)))
        {
            DinoIsDuck = true;      
        }
        if (DinoIsDuck && DuckRunningTime < DuckUpdateTime)
        {
            DuckRunningTime += dt;

            dinoData.rec.x = 3*dinoData.rec.width;
        }
        else
        {
        DuckRunningTime = 0.0;
        DinoIsDuck =false;

        //update animData Dino
        dinoData = updateAnimData(dinoData, dt, 2);
        }
         
        //update AnimData Laeva
        for (int i = 0; i < NumOfLaevas; i++)
        {
            Laevas[i] = updateAnimData(Laevas[i], dt, 3);
        }
        
        //Jump
        if ((IsKeyPressed(KEY_SPACE) && isOnGround(dinoData, windowHeight))||(IsKeyPressed(KEY_W) && isOnGround(dinoData, windowHeight)))
        {
            Dino_velocity -= jump_hight;
            PlaySound(Jump);
        }
        //Collisions Check
        for (AnimData Melon :Melons)
        {
            float MelonPad{5};
            Rectangle MelonRec {
                Melon.pos.x + MelonPad,
                Melon.pos.y + MelonPad,
                Melon.rec.width - 2*MelonPad,
                Melon.rec.height - 2*MelonPad
            };
            float DinoPad{30};
            Rectangle dinoRec {
                dinoData.pos.x + DinoPad,
                dinoData.pos.y + DinoPad,
                dinoData.rec.width - 2*DinoPad,
                dinoData.rec.height - 2*DinoPad
            };
            
            if (CheckCollisionRecs(MelonRec, dinoRec))
            {
                PlaySound(melonPickUp);
                pointNum += 10;
                Melons[0].pos.x = windowWidth + GetRandomValue(2000,20000);
            }
        }
        
        
        //update position DINO
        dinoData.pos.y += Dino_velocity * dt;

        
        //Update position LAEVA
        for (int i = 0; i < NumOfLaevas; i++)
        {
            
            if (Laevas[i].pos.x <= 0)
            {
                Laevas[i].pos.x = windowWidth + i*GetRandomValue(100,500);                        
            }
            else{
            Laevas[i].pos.x -= (ObjectSpeed) * dt;
            }
        }

        //Update position Melon
        for (int i = 0; i < NumOfMelon; i++)
        {
            
            if (Melons[i].pos.x <= 0)
            {
                Melons[i].pos.x = windowWidth + GetRandomValue(2000,20000) ;
            }
            else{
            Melons[i].pos.x -= (ObjectSpeed) * dt;
            }
        }

        
        //update position Back
        if (mountainData.pos.x <= -mountain.width)
        {
            mountainData.pos.x = mountain.width;
        }
        else
        {
            mountainData.pos.x -= mountainSpeed * dt;
        }

        if (birdsData.pos.x <= -200)
        {
            birdsData.pos.x = 10000;
        }
        else
        {
            birdsData.pos.x -= birdsSpeed*dt;
        }

        if (treesFrontData.pos.x <= -treesFront.width)
        {
            treesFrontData.pos.x = treesFront.width;
        }
        else
        {
            treesFrontData.pos.x -= ObjectSpeed*dt;
        }
        
        if (treesBackData.pos.x <= -treesBack.width)
        {
            treesBackData.pos.x = treesBack.width;
        }
        else
        {
            treesBackData.pos.x -= treesBackSpeed*dt;
        }
        
        DrawLine(0, (windowHeight - 350) + dinoData.rec.height, windowWidth, (windowHeight - 350) + dinoData.rec.height, BLACK);
        DrawTextureRec(mountain, mountainData.rec, mountainData.pos, WHITE);
        DrawTextureRec(birds,birdsData.rec, birdsData.pos, WHITE);
        DrawTextureRec(treesBack, treesBackData.rec, treesBackData.pos, WHITE);
        DrawTextureRec(treesFront, treesFrontData.rec, treesFrontData.pos, WHITE);
        
        DrawLine(0, (windowHeight - 250) + dinoData.rec.height, windowWidth, (windowHeight - 250) + dinoData.rec.height, BLACK);

        DrawTextureRec(Dino, dinoData.rec, dinoData.pos, WHITE);

        for (int i = 0; i < NumOfLaevas; i++)
        {
            DrawTextureRec(Laeva, Laevas[i].rec, Laevas[i].pos, WHITE);
        }
        for (int i = 0; i < NumOfMelon; i++)
        {
            DrawTextureRec(melon, Melons[i].rec, Melons[i].pos, WHITE);
        }
        
        
        

    }
    }
        
           

        EndDrawing();
        
        
        
        
    }
    UnloadTexture(Dino);
    UnloadTexture(Laeva);
    UnloadTexture(melon);
    CloseWindow();


}