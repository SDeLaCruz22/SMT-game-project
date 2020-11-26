#ifndef ENTITYCLASS_H
#define ENTITYCLASS_H

#include <iostream>
#include <string>

#include "EntityStruct.h"
#include "SkillStruct.h"

class EntityClass{
    public:
        EntityStruct Entity;
        int hp; int maxhp;
        int mp; int maxmp;
        //int expgain;//exp gained
        int taru; int raku; int suku;

        EntityClass();
        void FinalSetup();
        void operator = (const EntityStruct& source);//copy from one entity to other}
        void operator = (const EntityClass& source); //uhhhh we'll think of a way to just have the address be carried
};

class PlayerCharacter: public EntityClass{
    public:
        int exp;
        int NextExp;
        int gold;
        //equipment
        //items

        PlayerCharacter();
        void LevelUp();
        void GainExp(int expgain);
        bool NextLvlReached();
        void SeeStats();
};

//PlayerCharacter Player; //WOWZA

class FriendlyDemon: public EntityClass{
    public:
        int exp;
        int NextExp;
        bool HasLeveledUp; //skill whisper only activates on the first level up
        void LevelUp();
        void SkillWhisper(); //this is how the main character learns new skills
        void GainExp(int expgain);
        bool NextLvlReached();
        void SeeStats();
        void Swap(const FriendlyDemon &source);
        void operator = (const FriendlyDemon &source);//swapping party demons
};






//------------------------------------ENTITY CLASS------------------------------------
EntityClass::EntityClass(){}

void EntityClass::FinalSetup(){ //only to be used for leveling up since mp and hp is restored
    maxhp = (Entity.lvl + Entity.vit)*6 + Entity.str*2; hp = maxhp;
    maxmp = (Entity.lvl + Entity.mag)*3; mp = maxmp;
    taru = 0; raku = 0; suku = 0;
}

void EntityClass::operator = (const EntityStruct &source){
    Entity =  source; //EntityCLass::Entity, do note that if we use a dynamic array in Entity Struct, we will need to manually do this
    FinalSetup();
}






//---------------------------------------PlayerCharacter---------------------------------
PlayerCharacter::PlayerCharacter(){
    //set up them stats
    char check;
    int statpoint;
    cout <<"You are about to distribute 6 points. Would you like to know what each stat does? (Y (yes) or N (no))\n";
    cin >> check;
    if(check =='y'||check =='Y')
        cout <<"Str (strength) affects your physical damage and slightly increases your health (hp)\n
                Mag (magic) affects your magic effectiveness, magic resistance, and slightly increases your mana (mp)\n
                Vit (vitality) affects your health and your physical damage resistance\n
                Agi (agility) affects your party's chances of going first, your turn order in the party, your accuracy & evasioin, and multi hit skills\n
                Luck affects your critical rate, aliment rate, gold earned, & minorly affects agility effects\n";

    Entity.lvl = 1;
    exp =0; gold=0; NextExp = 5*exp(Entity.lvl, 1.9);

    STATCHOICE:
    Entity.str = 3;
    Entity.mag = 3;
    Entity.vit = 3;
    Entity.agi = 3;
    Entity.luck =3;
    for(int i=6; i>0; i--){
        PICKSTAT:
        cout <<"Please Distribute " <<i <<" points. Enter the corresponding number to put a point into the stat\n Str = 1, Mag = 2, Vit = 3, Agi = 4, Luck = 5\n";
        FinalSetup();
        SeeStats();
        cin >> statpoint;
        switch(statpoint){
            case 1: Entity.str += 1; break;
            case 2: Entity.mag += 1; break;
            case 3: Entity.vit += 1; break;
            case 4: Entity.agi +=1; break;
            case 5: Entity.luck +=1; break;
            default: cout <<"Please enter a valid number\n" goto PICKSTAT; break;
        }
    }
    cout <<endl <<endl;
    FinalSetup();
    SeeStat();
    cout <<"Is this okay? (Y (yes) or N (no)" <<endl;
    cin >> check;
    if(check == 'n' || check == 'N') goto STATCHOICE;
}

void PlayerCharacter::SeeStats(){
    cout <<"Your currents stats are:\n";
    cout <<"Level:\t" <<Entity.lvl <<endl;
    cout <<"HP:\t" <<hp <<"\tMP:\t" <<mp <<endl;
    cout <<"Exp:\t" <<exp <<"\tNext:\t" <<NextExp <<endl;
    cout <<"Str:\t" <<Entity.str <<endl;
    cout <<"Mag:\t" <<Entity.mag <<endl;
    cout <<"Vit:\t" <<Entity.vit <<endl;
    cout <<"Agi:\t" <<Entity.agi <<endl;
    cout <<"Luck:\t" <<Entity.luck <<endl;
    //equipment
}

void PlayerCharacter::GainExp(int expgain){
    exp += expgain;
    for(int i=0; NextLvlReached(); i++)
        LevelUp();//this will account for multiple level ups
}

bool PlayerCharacter::NextLvlReached(){        
    if(exp < NextExp)
        return false;
    exp = exp - NextExp;
    Entity.lvl +=1;
    NextExp = 5* exp(Entity.lvl, 1.9); //next exp could be a private variable that is updated once
    return true;
}

void PlayerCharacter::LevelUp(){
    int StatIncrease;
    SeeStats();
    cout <<"You leveled up! Please increase a stat by entering the corresponding number & 'enter'" <<endl;
    CHOOSESTAT:
    cout <<"1. Strength\n2. Magic\n3. Vitality\n4. Agility\n5. Luck\n";
    cin >> StatIncrease;

    switch(StatIncrease){
        case 1: Player.str +=1;
        case 2: Player.mag +=1;
        case 3: Player.vit +=1;
        case 4: Player.agi +=1;
        case 5: Player.luck +=1;
        default: cout <<"Please choose a number between 1 and 5\n"; goto CHOOOSESTAT;
    }
    FinalSetup();
    SeeStats();
}





//-------------------------------FRIENDLY DEMON-----------------------------------------


FriendlyDemon::FriendlyDemon(){}

void FriendlyDemon::GainExp(int expgain){
    exp += expgain;
    for(int i=0; NextLvlReached(); i++)
        LevelUp();//this will account for multiple level ups
}

bool FriendlyDemon::NextLvlReached(){
    if(exp < NextExp)
        return false;
    exp = exp - NextExp;
    Entity.Lvl +=1;
    NextExp = 5* exp(Entity.Lvl+3, 1.9);
    return true;
}

void FriendlyDemon::LevelUp(){ //the higher the stat, the more likely it is to increase
    cout <<Entity.name <<" has leveled up!\n";
    int totalStatPoints = 20 + Entity.lvl;
    int leveledStat = rand()%totalStatPoints + 1;
    int StatBenchmark[5];

    //stat tier
    int i;
    StatBenchmark[0] = Entity.str;
    StatBenchmark[1] = StatBenchmark[0] + Entity.mag;
    StatBenchmark[2] = StatBenchmark[1] + Entity.vit;
    StatBenchmark[3] = StatBenchmark[2] + Entity.agi;
    StatBenchmark[4] = StatBenchmark[3] + Entity.luck;

    for(i=4; i>=0; i--){
        if(leveledStat >= StatBenchmark[i]) break;
    }
    switch(i){
        case 0: Entity.str += 1; cout <<Entity.name <<"'s stength went up!\n"; break;
        case 1: Entity.mag += 1; cout <<Entity.name <<"'s magic went up!\n"; break;
        case 2: Entity.vit += 1; cout <<Entity.name <<"'s vitality went up!\n"; break;
        case 3: Entity.agi += 1; cout <<Entity.name <<"'s agility went up!\n"; break;
        case 4: Entity.luck +=1; cout <<Entity.name <<"'s luck went up!\n"; break;
    }
    FinalSetup();
    SeeStats();

    if(HasLeveledUp == false){
        HasLeveledUp = true;
        SkillWhisper();
    }
}

void FriendlyDemon::SkillWhisper(){ //this is how the main character learns new skills
    //
    cout <<Entity.name <<" is whispering something to you...\nWhat skill will you let it teach you?" <<endl;
    cout <<
}

void FriendlyDemon::SeeStats(){
    cout <<Entity.name <<" currents stats are:\n";
    cout <<"Level:\t" <<Entity.lvl <<endl;
    cout <<"HP:\t" <<hp <<"\tMP:\t" <<mp <<endl;
    cout <<"Exp:\t" <<exp <<"\tNext:\t" <<NextExp <<endl;
    cout <<"Str:\t" <<Entity.str <<endl;
    cout <<"Mag:\t" <<Entity.mag <<endl;
    cout <<"Vit:\t" <<Entity.vit <<endl;
    cout <<"Agi:\t" <<Entity.agi <<endl;
    cout <<"Luck:\t" <<Entity.luck <<endl;
}

void FriendlyDemon::Swap(const FriendlyDemon &source){
    if(Entity.name.empty()){ //the current position is empty
        this = source;
        return;
    }
    FriendlyDemon temp;
    temp = this;
    this = source;
    source = temp; //we might need a destructor, but we don't have heap memory yet...
}

void FriendlyDemon::operator = (const FriendlyDemon &source){//swapping party demons
    Entity = source.Entity; //pretty sure this will work, will need to rewrite if we have heap memory
    hp = source.hp; maxhp = source.maxhp;
    mp = source.mp; maxmp = source.maxmp;
    exp = source.exp; NextExp = source.NextExp;
    HasLeveledUp = source.HasLeveledUp;
}

#endif

/*
Party class
-We want it to be general enough so that both parties can fall under the same class 
    meaning we want
    - The Demon Info
    - 
-THe only problem is the playable MC
    -MC has the gold
    -MC get experience (we could make the demons gain exp too)
    -MC has equipment
    -MC has items
so we dont want togive everyone unecessary features so we could make a derived class specfically for the player
When encounter launches we can put the MC and the rest of the current party into an array

When the battle ends we call on the MC specifically to apply the exp gold and what not

Class Party{}

Class Player: Class Party{
    private: 
        int gold;
        int exp;
}
Now the next problem is figuring out how the weapon is going to add to damage.We can be lazy and just add
str points, but we'll probably want to incorporate flat resistance and damage values for the MC. 4

What we can do is whenever the player chooses to normal attack, we modify the normal attack damage to be
equal to the weapon damage, after the player does the damage calculation (but before the encounter ends) 
the normal attack damage is reverted back to 30


regarding equipment:
Shoes - increase agi
body armor - increase vit
Weapon - increases str (+ normal attack damage modifier)
accessory - increases luck or magic

PlayerCharacter{
    GainExp(){
        exp += expgain;
        for(int i=0; NextLvlReached(); i++)
            LevelUp();//this will account for multiple level ups
    }

    bool NextLvlReached(){        
        if(exp < NextExp)
            return false;
        Player.Exp = Player.Exp - NextExp;
        Player.Lvl +=1;
        NextExp = 5* exp(Player.Lvl, 1.9); //next exp could be a private variable that is updated once
        return true;
    }

    void LevelUp(){
        int StatIncrease;
        cout <<"You leveled up! Please increase a stat by entering the corresponding number & 'enter'" <<endl;
        CHOOSESTAT:
        cout <<"1. Strength\n2. Magic\n3. Vitality\n4. Agility\n5. Luck\n";
        cin >> StatIncrease;

        switch(StatIncrease){
            case 1: Player.str +=1;
            case 2: Player.mag +=1;
            case 3: Player.vit +=1;
            case 4: Player.agi +=1;
            case 5: Player.luck +=1;
            default: cout <<"Please choose a number between 1 and 5\n"; goto CHOOOSESTAT;
        }

        Player.hp = (Player.lvl + Player.vit)*6 + 2*Player.str;
        Player.mp = (Player.lvl + Player.mag)*3;
        Player.maxhp = Player.hp;
        Player.mp = Player.mp;

        if(Player.lvl ==5 || Player.lvl == 10) //for now. Thnking about doing a demon whisper skill. 
            NewSkill();
    }

    void NewSkill(){
        //swsss
    }
}

//we will continue to make an Entity Class that will be used for the demon party and the player party
there will be a dervied class 'PlayerCharacter' that will carry the gold

Demon Entity
- Demon Level Up
    - Demon whisper
- ability to return

Player
- different level up
- carries gold, items, equipment etc
- ability to summon

*/