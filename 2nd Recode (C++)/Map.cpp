/*
Since I don't know how else to implement this this
will be in ASCII...

Cave Village
..-_---_---_---_--+
..| | | | | | | | |
..|               |
..|  _   _   _   _|
+-| | | | | | | | |
|A                |
+-|        _      |
| |       |E|     |
|                 |
| |               |
+-|               |
|W        |M|     |
+-| +---+ +--+  +-+
..| |...| |..|  |..
..| |...| |..|  +-+
..| |...| |..|   D|
+-+ |...+-+..+----+
|S  |..............
+-+-+..............

Abandoned Minshaft
...........+-+.........................
...........| |.........................
...........| |........... +--------+...
.....+-----+ +---+....... |        |...
.....|           |.+------+ +-+ +--+...
.....| +-+ +---+ |.|        | | |......
.....| |.| |...| +-+ +-+ +--+ | |......
.....| |.+-+...|     |.| |....| |......
.....| +-+..+--| +---+.| +-+..+-+......
.....|   |..|  | |.....|   |...........
.....+-+ |..|    |...+-+   |...........
.......| |..+----+...| +---+..+---+....
...+---+ |.........+-+ +-+...++   ++...
+--+     +---------+     +-+-+     +--+
|U                   ---             B|
+--+     +-----+ +-+     +-+-+     +--+
...+---+ |.....| |.+---+ +....++   ++..
.......| |.+-+.| |.....| |....+---+....
.......| |.| |.| |.....| |.............
.......| +-+ +-+ +-----+ +---+.........
.......|                     |.........
.......+-+ +-+ +-+--+ +----+ +-+ ......
.........| |.| |....| |....|   ++......
.........| |.+-+....| |....| |  |......
.........+-+........| |....+-+--+......
.................+--+ +--+.............
.................|       |.............
.................+-------+.............


*/
#include <iostream>
#include <cstdlib>
#include "Map.h"

//using namespace MapClass;

//namespace MapClass{

        Map::Map(){
            for(int i=0; i<19; i++){
                for(int j=0; j<20; j++)
                    PlayerTownMap[i][j] = '.';
            }
            for(int i=0; i<28; i++){
                for(int j=0; j<40; j++)
                    PlayerMineshaftMap[i][j] = '.';
            }

            row = 17; col = 1;
            mapnumber = 1;
            // CurrentPlayerMap = PlayerTownMap;
            MapSurrounding();
            PlayerTownMap[row][col] = PlayerIcon;
            PrintPlayerMap();
        }

        void Map::PlayerMove(){
            int rowshift, colshift;
            char direction; 

            INPUT:
            rowshift = 0; colshift = 0;
            cout <<"Press W to move forward, S to move backwards, D to move left, A to move right, Press M to view Map\n";
            cin >> direction;

            switch (direction){
                case 'w':rowshift= -1; break;
                case 's': rowshift = 1; break;
                case 'a': colshift = -1; break;
                case 'd': colshift = 1; break;
                default: cout <<"Invalid Input"; goto INPUT;
            }

            //yeah this is kinda ghetto preferably woulda used pointers. I can use this because I only have 2 maps
            if(mapnumber == 1){
                if(TownMap[row + rowshift][col + colshift] == '+' || TownMap[row + rowshift][col + colshift] == '|' || TownMap[row + rowshift][col + colshift] == '-' || TownMap[row + rowshift][col + colshift] == '_' || TownMap[row + rowshift][col + colshift] == '.')
                    goto INPUT;
                if(row==15 && col ==17){
                    //prompt elevator
                    mapnumber = 2; row =14; col = 2; //we will put them right outside the elevator
                    MapSurrounding();
                    PlayerMineshaftMap[row][col] = PlayerIcon;
                    PrintPlayerMap();
                    return;
                }
                //PlayerTownMap[row + rowshift][col + colshift] = PlayerIcon;
            }
            else{
                if(MineshaftMap[row + rowshift][col + colshift] == '+' || MineshaftMap[row + rowshift][col + colshift] == '|' || MineshaftMap[row + rowshift][col + colshift] == '-' || MineshaftMap[row + rowshift][col + colshift] == '_' || MineshaftMap[row + rowshift][col + colshift] == '.')
                    goto INPUT;
                if(row == 14 && col == 1){
                    //prompt elevator
                    mapnumber = 1; row = 15; col = 16;
                    MapSurrounding();
                    PlayerTownMap[row][col] = PlayerIcon;
                    PrintPlayerMap();
                    return;
                }
                //PlayerMineshaftMap[row + rowshift][col + colshift] = PlayerIcon;
            }
            
            row+=rowshift;
            col+=colshift;
            MapSurrounding();
            if(mapnumber==1)
                PlayerTownMap[row][col] = PlayerIcon;
            else
                PlayerMineshaftMap[row][col] = PlayerIcon;
            //RandomEncounterTrigger();
            PrintPlayerMap();
        }

        void Map::MapSurrounding(){
            int i, j;
            //cout <<PlayerTownMap[row][col-1] <<" " <<PlayerTownMap[row][col] <<" " <<PlayerTownMap[row][col+1] <<endl;
            for(i=-1; i<2; i++){
                for(j=-1; j<2; j++){
                    if(mapnumber == 1){
                        PlayerTownMap[row + i][col + j] = TownMap[row+i][col+j];
                    }
                    else
                        PlayerMineshaftMap[row+i][col+j] = MineshaftMap[row+i][col+j];
                }
            }
        }

        void Map::PrintPlayerMap(){
            size_t width, height;
            if(mapnumber == 1){ //using ghetoo method again
                width = 19; height = 19;}
            else{
                width =39; height = 28;}
            
            for(int i=0; i<height; i++){
                for(int j=0; j<width; j++){
                    if(mapnumber ==1)
                        cout <<PlayerTownMap[i][j];
                    else
                        cout <<PlayerMineshaftMap[i][j];
                }
                cout <<endl;
            }
            
        }

        /*void PrintSmallPlayerMap(){
            int i, j;
            for(i=-1; i<2; i++){
                for(j=-1; j<2; j++){
                    if(mapnumber == 1)
                        cout <<PlayerTownMap[row+i][col+j];
                    else
                        cout <<PlayerMineshaftMap[row+i][col+j];
                }
                cout <<endl;
            }
        }*/

        size_t Map::PlayerLocation(){
            size_t width, height;
            if(mapnumber == 1)
                width =19;
            else
                width = 39;
            return row*width + col + 1;
        }
        
        bool Map::RandomEncounterMap(){
            if(mapnumber<2)
                return false;
            return true;
        }

        bool Map::RandomEncounterTrigger() {
            if(!RandomEncounterMap())
                return false;
            if(rand()%5 == 0)
                return true;
            return false; 
        }
//}