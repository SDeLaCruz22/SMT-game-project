#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <cstdlib> // Provides size_t and NULL

//namespace MapClass{
    class Map{
        private:
            const char TownMap[19][20] = {
                {"..-_---_---_---_--+"},//1
                {"..| | | | | | | | |"},
                {"..|               |"},//3
                {"..|  _   _   _   _|"},
                {"+-| | | | | | | | |"},//5
                {"|A                |"},
                {"+-|        _      |"},//7
                {"| |       |E|     |"},
                {"|                 |"},//9
                {"| |               |"},
                {"+-|               |"},//11
                {"|W        |M|     |"},
                {"+-| +---+ +--+  +-+"},//13
                {"..| |...| |..|  |.."},
                {"..| |...| |..|  +-+"},//15
                {"..| |...| |..|   D|"},
                {"+-+ |...+-+..+----+"},//17
                {"|S  |.............."},
                {"+-+-+.............."},//19
            };

            char PlayerTownMap[19][20];

            const char MineshaftMap[28][40] = {
                {"...........+-+........................."},//1
                {"...........| |........................."},
                {"...........| |........... +--------+..."},//3
                {".....+-----+ +---+....... |        |..."},
                {".....|           |.+------+ +-+ +--+..."},//5
                {".....| +-+ +---+ |.|        | | |......"},
                {".....| |.| |...| +-+ +-+ +--+ | |......"},//7
                {".....| |.+-+...|     |.| |....| |......"},
                {".....| +-+..+--| +---+.| +-+..+-+......"},//9
                {".....|   |..|  | |.....|   |..........."},
                {".....+-+ |..|    |...+-+   |..........."},//11
                {".......| |..+----+...| +---+..+---+...."},
                {"...+---+ |.........+-+ +-+...++   ++..."},//13
                {"+--+     +---------+     +-+-+     +--+"},
                {"|U                   ---             B|"},//15
                {"+--+     +-----+ +-+     +-+-+     +--+"},
                {"...+---+ |.....| |.+---+ +....++   ++.."},//17
                {".......| |.+-+.| |.....| |....+---+...."},
                {".......| |.| |.| |.....| |............."},//19
                {".......| +-+ +-+ +-----+ +---+........."},
                {".......|                     |........."},//21
                {".......+-+ +-+ +-+--+ +----+ +-+ ......"},
                {".........| |.| |....| |....|   ++......"},//23
                {".........| |.+-+....| |....| |  |......"},
                {".........+-+........| |....+-+--+......"},//25
                {".................+--+ +--+............."},
                {".................|       |............."},//27
                {".................+-------+............."}
            };

            char PlayerMinshaftMap[28][40];

            size_t row, col;
            char PlayerIcon = 'o';
            const char* CurrentMap;

        public:
            Map(); //constructor
            void PlayerMove(); //adjusts the icon and checks if the movement is valid 
            void MapSurrounding();//updates the surrounding 8 tiles after a successful movement
            void PrintPlayerMap(); //activates when player wants to see the entire map
            //void PrintSmallPlayerMap(); //automatically called after each movement, only prints a 3x3 around the player
            //  SCRAPPED- THe small map was too small, having the large map be the default made it more legible
            size_t PlayerLocation(); //returns the location of the cursor, this is used for events and NPC dialogue
            bool RandomEncounterMap(); //used to see if random encounters are used for the map
            bool RandomEncounterTrigger();
    };
//}

#endif