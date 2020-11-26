/*
the implementation of the demoninfo
we will use a structure that is capcable of the following
- Fast searches given name
- Fixed amount of total demons
- Will only hold the data for each demon

What type of data will we want to store?
- Name - string
- HP - int
- MP - int
- STR/MAG/VIT/AGI/LUCK - ints
- Skills - this will require its own structure

What specifically will we want to do?
- Retreive Information of a specfic demon
- Show basic information of ALL Demons
- Incorporate the information for battle and recruitment
    -this means being able to have the information be relayed to somewhere else


Class DemonInfo
- The first class object will be used to hold the demon info for the rest of the game
- A new object will be created for encounters
    - we want the size of the contents to be dynamic

    
*/
#ifndef ENTITYSTRUCT_H
#define ENTITYSTRUCT_H

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib> // Provides size_t and NULL

using namespace std;

//namespace EntityClass{
/*class Entity{
    public:
        string name; //we may need spaces. pretty sure char* doesn't allow for it
        int lvl;
        int hp;
        int maxhp;
        int mp;
        int str;
        int mag;
        int vit;
        int agi;
        int luck;
        string* Weakness;
        string* Resist;
        string* Void;
        //string* Skills;
        int* Skills; //
        int* SkillWeight; //this willhellp out when making enemy ai
        int expgain;//exp gained

        Entity();
        void FinalSetup();
        void operator = (const Entity& source);//copy from one entity to other}
};*/
//}

/*
struct EntityStruct{
    string name;
    int lvl;
    int str;
    int mag;
    int vit;
    int agi;
    int luck;
    string *Weakness = new string[4];
    string *Resist = new string[4];
    string *Void = new string[4];
    int* Skills = new int[4];
    int* SkillWeight = new int[4];
}
*/

struct EntityStruct{
    string name;
    int lvl;
    int str;
    int mag;
    int vit;
    int agi;
    int luck;
    /*string *Weakness = new string[4];
    string *Resist = new string[4];
    string *Void = new string[4];
    int* Skills = new int[4];
    int* SkillWeight = new int[4];
    */
    string Weakness[4]; //if we want to conserve space, we should use std::vector, for now this will be fine
    string Resist[4];
    string Void[4];
    int Skills[4];
    int SkillWeight[4];
};

EntityStruct DemonInfo[26]{
//0  
    {"Pixie", 1, 3, 6, 3, 3, 6, {"Fire", "End", " ", " "}, {"Electric", "End", " ", " "}, {"None", "End", " ", " "}, {18, 12, 0, 0}, {2, 5, 0, 0} },

    {"Slime", 1, 5, 4, 7, 2, 4, {"Physical", "Fire", "Light", "End"}, {"None", "End", " ", " "}, {"Dark", "End", " ", " "}, {2, 0, 0, 0}, {5, 0, 0, 0} },
//2
    {"Knocker", 2, 4, 4, 5, 4, 5, {"Ice", "Fire", "End", " "}, {"None", "End", " ", " "}, {"None", "End", " ", " "}, {20, 2, 0, 0}, {3, 4, 0, 0} },

    {"Goblin", 2, 5, 4, 5, 4, 4, {"Electric", "End", " ", " "}, {"Force", "End", " ", " "}, {"None", "End", " ", " "}, {9, 2, 0, 0}, {4, 4, 0, 0} },
//4
    {"Kobold", 3, 6, 4, 5, 3, 5, {"Electric", "Force", "End", " "}, {"Physical", "End", " ", " "}, {"None", "End", " ", " "}, {1, 3, 0, 0}, {3, 3, 0, 0} },

    {"Jack Frost", 4, 4, 6, 4, 5, 5, {"Fire", "End", " ", " "}, {"None", "End", " ", " "}, {"Ice", "End", " ", " "}, {7, 8, 0, 0}, {5, 3, 0, 0} },
//6
    {"Pyro Jack", 4, 4, 5, 5, 6, 4, {"Ice", "End", " ", " "}, {"None", "End", " ", " "}, {"Fire", "End", " ", " "}, {5, 6, 0, 0}, {4, 4, 0, 0} },

    {"Cu Sith ", 5, 5, 4, 5, 7, 4, {"Force", "End", " ", " "}, {"None", "End", " ", " "}, {"None", "End", " ", " "}, {1, 22, 0, 0}, {5, 3, 0, 0} },
//8
    {"Hua Po", 5, 4, 7, 4, 6, 4, {"Fire", "End", " ", " "}, {"None", "End", " ", " "}, {"None", "End", " ", " "}, {5, 6, 21, 0}, {4, 3, 2, 0} },

    {"Mokoi", 5, 6, 4, 6, 5, 4, {"Ice", "End", " ", " "}, {"Electric", "End", " ", " "}, {"None", "End", " ", " "}, {2, 12, 0, 0}, {4, 3, 0, 0} },
//10
    {"Ghoul", 6, 6, 3, 6, 6, 5, {"Light", "End", " ", " "}, {"Physical", "End", " ", " "}, {"Dark", "End", " ", " "}, {1, 16, 0, 0}, {5, 2, 0, 0} },

    {"Angel", 6, 4, 7, 4, 5, 6, {"Ice", "End", " ", " "}, {"Electric", "End", " ", " "}, {"Light", "End", " ", " "}, {18, 14, 9, 0}, {2, 3, 5, 0} },
//12
    {"Leanan Sidhe", 7, 6, 7, 5, 6, 3, {"Force", "End", " ", " "}, {"Ice", "End", " ", " "}, {"None", "End", " ", " "}, {8, 19, 0, 0}, {4, 2, 0, 0} },

    {"Azumi", 7, 5, 6, 6, 5, 5, {"Fire", "End", " ", " "}, {"None", "End", " ", " "}, {"Ice", "End", " ", " "}, {2, 7, 18, 0}, {4, 4, 1, 0} },
//14
    {"Koppa Tengu", 8, 5, 7, 6, 6, 4, {"Electric", "End", " ", " "}, {"None", "End", " ", " "}, {"Force", "End", " ", " "}, {10, 25, 24, 0}, {3, 3, 3, 0} },

    {"Oni", 8, 8, 4, 7, 5, 4, {"Electric", "Force", "End", " "}, {"Physical", "End", " ", " "}, {"None", "End", " ", " "}, {2, 3, 24, 0}, {4, 3, 3, 0} },
//16
    {"Nekomata", 8, 5, 6, 5, 7, 5, {"Ice", "End", " ", " "}, {"Force", "End", " ", " "}, {"None", "End", " ", " "}, {1, 9, 22, 0}, {3, 3, 2, 0} },

    {"Apsaras", 9, 2, 8, 6, 8, 5, {"Fire", "Dark", "End", " "}, {"None", "End", " ", " "}, {"Ice", "End", " ", " "}, {8, 19, 21, 0}, {3, 2, 4, 0} },
//18
    {"Naga", 9, 7, 2, 6, 7, 7, {"Ice", "End", " ", " "}, {"Electric", "End", " ", " "}, {"None", "End", " ", " "}, {1, 6, 25, 0}, {3, 3, 2, 0} },

    {"Okiku Mushi", 9, 5, 5, 6, 4, 9, {"Fire", "Light", "End", " "}, {"Physical", "End", " ", " "}, {"Dark", "End", " ", " "}, {3, 17, 23, 0}, {3, 3, 2, 0} },
//20
    {"Mothman", 9, 4, 4, 5, 8, 8, {"Force", "End", " ", " "}, {"Electric", "End", " ", " "}, {"None", "End", " ", " "}, {13, 22, 2, 0}, {3, 2, 4, 0} },

    {"Lillim", 10, 4, 9, 5, 8, 4, {"Fire", "Light", "End", " "}, {"None", "End", " ", " "}, {"Electric", "Dark", "End", " "}, {19, 12, 13, 0}, {2, 4, 3, 0} },
//22
    {"Momunofu", 10, 7, 5, 8, 6, 4, {"Fire", "End", " ", " "}, {"Force", "End", " ", " "}, {"None", "End", " ", " "}, {1, 20, 3, 0}, {3, 3, 3, 0} },

    {"Kodama", 10, 7, 7, 6, 6, 7, {"Ice,", "Electric", "End", " "}, {"None", "End", " ", " "}, {"Force", "End", " ", " "}, {21, 23, 9, 0}, {2, 2, 5, 0} },
//24
    {"Archangel", 10, 7, 7, 7, 5, 4, {"Dark", "End", " ", " "}, {"None", "End", " ", " "}, {"Light", "End", " ", " "}, {20, 15, 1, 0}, {2, 2, 5, 0} },

    {"Cu Chulainn", 15, 10, 8, 7, 5, 5, {"None", "End", " ", " "}, {"None", "End", " ", " "}, {"Force", "Light", "Dark", "End"}, {11, 4, 0, 0}, {3, 6, 0, 0} },

};



/*
Use a class for 
Player - needs equipment, gold, exp, hp/max hp, mp/max mp
Demon Party -  all of EntityStruct, hp/max hp, mp/max mp, 

*/

#endif