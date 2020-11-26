#include <iostream>

#include "EntityClass.h"
#include "EntityStruct.h"
#include "SkillStruct.h"

//THIS CODE USES USES A PLAYER CLASS THAT HASN'T BEEN CREATED


class Encounter{
    private:
        EntityClass *Party;
        EntityClass *EnemyDemon;

    public:
    //INITIAL SETUP
    Encounter(PlayerCharacter Player, FriendlyDemon *PartyDemon){
        //ss
        int countParty = 0;
        for(int i=0; i<3; i++){
            if(PartyDemon[i].Entity.name.empty()) countParty++;
        }
        Party = new EntityClass[1 + countParty]
        Party[0] = Player;
        for(int i=1; PartyDemon[i-1]; i++){
            Party[i] = PartyDemon[i-1];
        }

        int NumberofDemons = rand()%3 +1;
        EnemyDemon = new Entity[NumberofDemons];
    }

    Encounter(PlayerCharacter Player, FriendlyDemon PartyDemon[3], EntityStruct Boss){ //the boss encounter
        int countParty = 0;
        for(int i=0; i<3; i++){
            if(PartyDemon[i].Entity.name.empty()) countParty++;
        }
        Party = new EntityClass[1 + countParty];
        Party[0] = Player;
        for(int i=1; PartyDemon[i-1]; i++){
            Party[i] = PartyDemon[i-1];
        }
         
        EnemyDemon = Boss;
    }

    void RandomEncounter(){
        if(!RandomEncounterTrigger())
            return;
        OrganizeParty(); //organize each party by the members' agility
        int MaxDemonNumber = Player.lvl *2.5;
        if(MaxDemonNumber == 25) MaxDemonNumber = 24;
        int MinDemonNumber = (Player.lvl - 5)*2.5;
        if(MinDemonNumber < 0) MinDemonNumber = 0;

        for(int i=0; EnemyDemon[i]; i++){
            int DemonNumber = rand()%MaxDemonNumber + MinDemonNumber;
            EnemyDemon[i] = DemonInfo[DemonNumber];
            cout << "It's " <<EnemyDemon[i].name <<"!" <<endl;
        }

        if(PlayerGoesFirst())
            PlayerTurn();
        else
            EnemyTurn();
    }

    bool PlayerGoesFirst(){//pointer or something
        double EnemyAgility = 0;
        double PlayerAgility = 0;
        int i;

        for(i=0; EnemyDemon[i]; i++)
            EnemyAgility += EnemyDemon[i].Entity.agi + .25*EnemyDemon[i].Entity.luck;
        EnemyAgility /= i+1;

        for(i=0; Player[i]; i++)
            PlayerAgility += Player[i].Entity.agi + .25*Player[i].Entity.luck;
        PlayerAgility /= i+1;

        if(PlayerAgility >= EnemyAgility)
            return true;
        return false;
    }

    void OrganizeParty(){
        EntityClass temp;
        for(int i=0; i<sizeof(Party)-1; i++){
            for(int j=0; j<sizeof(Party)-1; j++){
                if(Party[j].Entity.agi < Party[j+1].Entity.agi){
                    temp = Party[j+1];
                    Party[j+1] = Party[j];
                    party[j] = temp;
                }
            }
        }
        for(int i=0; i<sizeof(EnemyDemon)-1; i++){
            for(int j=0; j<sizeof(EnemyDemon)-1; j++){
                if(EnemyDemon[j].agi < EnemyDemon[j+1].Entity.agi){
                    temp = EnemyDemon[j+1];
                    EnemyDemon[j+1] = EnemyDemon[j];
                    EnemyDemon[j] = temp;
                }
            }
        }
    }







    //PLAYER FUNCTIONS

    void DisplayParty(){
        for(int i=0; Player[i]; i++){
            cout <<Player[i].Entity.name <<"\t" <<Player[i].hp <<"\t" <<Player[i].mp <<endl;
        }
    }

    //MAIN PARTY FUNCTIONS (the one that leads to all other functions)
    void PlayerTurn(){
        //
        DisplayParty();
        char PlayerChoice;
        int target, skillChosen;
        for(int i=0; Player[i]; i++){
            PLAYERCHOICE:
            cout <<"What will " <<Player[i].Entity.name <<" do? (Press 'a' to attack, 's' to use a skill, 'd' to talk, & 'f' to flee, then press enter" <<endl;
            cin >> PlayerChoice;
            switch(PlayerChoice){
                case 'a':   
                    //ss
                    if(!TargetEnemyParty(0, i)) goto PLAYERCHOICE;
                    break;

                case 's':
                    CHOOSESKILLL:
                    skillChosen = SkillToUse();
                    if(!skillChosen) goto PLAYERCHOICE; //they wish to go back
                    if(!CanCastSkill(skillChosen, i)); goto PLAYERCHOICE;

                    if(!TargetEnemyParty(skillChosen)) goto CHOOSESKILL;
                    break;

                case 'd': // T A L K
                    break;

                case 'f': Flee(); break;

                default: goto PLAYERCHOICE:
            }
        }
    }

    //SKILL SPECIFIC USER CONTROLLED FUNCTIONS (these are menus)
    int SkillToUse(){
        int SkillChosen;
        cout <<"Which skill will yoou use? (Type 0 to go back)" <<endl;
        for(int i=1; Member.Skills[i]; i++){
            cout <<i+1 <<" " <<SkillInfo[Member.Skills[i]].name <<" " <<SkillInfo[Member.Skills[i]].cost;
            if(SkillInfo[Member.Skills[i]].costType == "HP ") cout <<"%hp ";
            else cout <<"MP ";
            cout <<SkillInfo[Member.Skills[i]].description <<endl;
        }
        cin >> SkillChosen;
        return SkillChosen; //the return value is the index of the skill + 1
    }

    bool TargetEnemyParty(int skillChosen, int user){
        int target, NumOfHits;
//        if(skillChosen == -1) goto NORMALATTACK;

        switch(StringToInt(SkillInfo[skillChosen].target)){
            case 1830: //single hitting
                cout <<"Who will you target? (Type the number to target the target, 0 to go back)" <<endl;
               
               //who to target
                if(SkillInfo[skillChosen].type == "heal"){ //who will you heal
                    for(int i=0; Party[i]; i++)
                        cout <<i+1 <<". " <<Party[i].name <<endl;
                }
                else{
                    for(int i=0; EnemyDemon[i]; i++)
                        cout <<i+1 <<". " <<EnemyDemon[i].name <<endl;
                }
                cin >> target; //this is the only time "target" is actually important, the other 2 cases its just there as confirmation
               
               //the back option
                if(!target) return false;
                
                //iniitate the skill
                if(SkillInfo[skillChosen].type == "Heal")
                    InitiateAction(skillChosen, Party, user, EnemyDemon, target-1);
                else
                    InitiateAttack(skillChosen, Party, user, EnemyDemon, target-1);

                break;

            case 1827: //random hitting
                cout <<"This will hit randomly. Continue? (Press 0 then Enter to cancel, otherwise 1 then Enter)" <<endl;
                cin >> target;
                
                //the back option
                if(!target) return false;
                
                //there are no random hitting support/heals...yet
                InitiateAttack(skillChosen, Party, user, EnemyDemon, 0);
                break;

            case 1584: //party hitting
                if(SkillInfo[skillChosen].type == "Heal" || skillChosen > 22)
                    cout <<"This will affect the ally party. Continue? (Press 0 then Enter to cancel, otherwise 1 then Enter)" <<endl;
                else //just slight difference in wording
                    cout <<"This will target the enemy party. Continue? (Press 0 then Enter to cancel, otherwise 1 then Enter)" <<endl;
                cin >> target;

                //the back option
                if(!target) return false;
                
                //initiatte the skill
                if(SkillInfo[skillChosen].type == "Heal" || SkillInfo[skillChosen].type == "Support")
                    InitiateAction(skillChosen, Party, user, EnemyDemon, 0);
                else //any offensive skill
                    InitiateAttack(skillChosen, Party, user, EnemyDemon, 0);
                break;

            default: cout <<"YOU'RE NOT SUPPOSED TO READ THIS MESSAGE" <<endl;
                return false;
        }
        return true;
    }



    //ENEMY FUNCTIONS

    void EnemyTurn(){
        //s
        int target;
        for(int i=0; EnemyDemon[i]; i++){
            //choosing what to do
            EnemyDemonSkillBracket(i);
            int EnemySkill = EnemySkillGenerator(i);
            //acquire the target if needed
            if(SkillInfo[EnemySkill].target == "Single")
                target = EnemyTarget(EnemySkill);

            //perform the appropiate action
            if(SkillInfo[EnemySkill].type == "Heal" || SkillInfo[EnemySkill].type == "Support")
                InitiateAction(EnemySkill, EnemyDemon, i, Party, target)
            else
                InitiateAttack(EnemySkill, EnemyDemon, i, Party, target);
        }
    }

    void EnemyDemonSkillBracket(int member){
        for(int i=1; EnemyDemon[member].Entity.SkillWeight[i]; i++){
            EnemyDemon[member].Entity.SkillWeight[i] += EnemyDemon[member].Entity.SkillWeight[i-1];
        }
    }

    int EnemySkillGenerator(int member){
        skill = rand()%10;
        for(int i=0; i < sizeof(EnemyDemon[member].Entity.SkillWeight[i]); i++){
            if(skill < EnemyDemon[member].Entity.SkillWeight[i])
                return EnemyDemon[member].Entity.Skills[i];
        }
        return 0; //normal attack
    }

    int EnemyTarget(int skill){
        int target;
        if(SkillInfo[skill].type == "Heal")
            target = rand() % sizeof(EnemyDemon);
        else
            target = rand() % sizeof(Party);
        return target;
    }





    //SKILL SPECIFIC UNIVERSAL FUNCTIONS

    bool CanCastSkill(int skillChosen, int user){ //make this universal
        if(SkillInfo[skillChosen].costType == "HP"){
            if(Party[user].hp < Part[user].maxhp*SkillInfo[skillChosen].cost/100){
                cout << "Not enough hp!" <<endl;
                return false;
            }
        }
        else{
            if(Party[user].mp < SkillInfo[skillChosen].cost){
                cout <<"Not enough mp!"  <<endl;
                return false;
            }
        }
        return true;
    }

    int NumberOfHits(int skillChosen, EntityClass *TargetParty, EntityClass User){
        int NumOfHits = 0;
        if(SkillInfo[skillChosen].MaxHits != 0){ //this big boy, the multihitter
            int HitDifference = SkillInfo[skillChosen].MaxHits - SkillInfo[skillChosen].MinHits;
            int *Hits = new int[HitDifference];
            int Modular = (exp(2, (HitDifference + 1)) - 1 ) * 10;
            
            int AvgTargetPartyAgi = 0;
            for(int i=0; TargetParty[i]; i++)
                AvgTargetPartyAgi += TargetParty[i].Entity.agi;
            AvgTargetPartyAgi /= sizeof(TargetParty);
            
            int AgiDifference = (User.Entity.agi - AvgTargetPartyAgi)*2; //this *2 is so that the player can feel the effects of an agility build

            for(int i=0; i < HitDifference; i++){ //the benchmark of values. For a 2-4 hit it would be [0]-40, [1]-60. 0-39 is 2 hits, 40-59 is 3 hits, 60+ is 4 hits
                Hits[i] = exp(2, HitDifference - i) * 10;
                if(i) Hits[i] += Hits[i-1]; //when i isn't 0, add the previous number
            }

            REROLL:
            int x = rand()%Modular;
            if(x < AgiDifference) goto REROLL;
            x+= AgiDifference;
                
            for(int i=HitDifference-1; i>=0; i--){
                if(x >= Hits[i]) 
                    NumOfHits = SkillInfo[skillChosen].MinHits + i + 1; //minHits + 1 + i
            }
            if(NumOfHits == 0)
                NumOfHits = SkillInfo[skillChosen].MinHits; //the minimum
            //return SkillInfo[skillChosen].MaxHits; //THIS SHOULDN'T HAPPEN
        }

        else
            NumOfHits = SkillInfo[skillChosen].MinHits;
        
        return NumOfHits;
    }

    bool AccuracyCheck(int skillChosen, EntityClass Target, EntityClass User){
        //[Skill Hit + (User Agi - Target Agi) + (User Luck - Enemy Luck)/5] * (1 + .125(User Agility (suk) - Target Agility))
        if(SkillInfo[skillChosen].hitChance == 100) //only heals and support skills
            return true;
        double Accuracy = (SkillInfo[skillChosenn].hitChance + (User.agi - Target.agi)*2 + (User.luck - Target.luck)/5); // 
        if(Accuracy > 90) Accuracy = 90; //max accuracy is 90%
        if(rand()%100 > Accuracy){
            cout <<User.name <<" missed!" <<endl;
            return false;
        }
        return true;
    }

    void InitiateAction(int skill, EntityClass *UserParty, int User, EntityClass *TargetParty, int Target){ //only used for multi hits
        
        if(SkillInfo[skill].target == "Single"){ //the only single non offensive abilities are the healing
            Heal(skill, UserParty[Target], UserParty[User]);
            return;
        }
        
        switch(StringToInt(SkillInfo[skill].type)){
            case 1134: //Heal
                for(int i=0; UserParty[i]; i++)
                    Heal(skill, UserParty[i], UserParty[User]);
                break;
            case 2295: //Support
                if(skill > 22){
                    for(int i=0; UserParty[i], i++)
                        Support(skill, UserParty[i]);
                }
                else{
                    for(int i=0; TargetParty[i], i++)
                        Support(skill, TargetParty[i]);   
                }
                break;
            default: cout <<"YOURE NOT SUPPOSED TO READ THIS MESSAGE" <<endl;
        }

        UserParty[User].mp -= SkillInfo[skill].cost;
    }

    void InitiateAttack(int skill, EntityClass *UserParty, int User, EntityClass *TargetParty, int Target){
        int NumOfHits = NumberOfHits(skill, TargetParty, Party[user]);

        switch(StringToInt(SkillInfo[skill].target)){
            case 1830: //single hit
                AttackLoop(skill, NumOfHits, TargetParty[Target], UserParty[User]); //this is the only time we actually use int Target
                //InitiateAttack(skillChosen, NumOfHits, EnemyDemon[target-1], Party[user]);
                break;
            case 1827: //random hit
                for(int i=0; i<NumOfHits; i++){ //this method applies one hit per target, though it can hit the same target more than once
                    int RandomTarget = rand()% sizeof(TargetParty); //
                    AttackLoop(skill, 1, TargetParty[RandomTarget], UserParty[User]);
                }
                break;
            case 1584: //party wide
                for(int i=0; TargetParty[i]; i++)
                    AttackLoop(skill, NumOfHits, TargetParty[i], UserParty[User])
                break;
            default: cout <<"You shouldn't see this message\n"; break;
        }

        if(SkillInfo[skill].type == "Physical") //the cost is based on total max health
            UserParty[User].hp -= UserParty[User].maxhp*SkillInfo[skill].cost/100;
        else //magic attaks
            UserParty[User].mp -= SkillInfo[skill].cost;
        
    }

    void AttackLoop(int skill, int NumOfHits, EntityClass Target, EntityClass User){
        for(int i=0; i< NumOfHits; i++){
            if(!AccuracyCheck(skill, Target, User))
                return; //missed the hit, no damage is done
            Damage(skill, Target, User);
        }
        return;
    }

    int StringToInt(string source){ //Single 1830 Random 1827 Party 1584,||| Heal 1134 Support 2295
        int val=0;
        for(int i=0; source[i]; i++)
            val+= source[i]*3;
        return val;
    }






    //DAMAGE, HEALING, & SUPPORT FUNCTIONS

    void Heal(int skill, EntityClass Target, EntityClass User){
        int heal = SkillInfo[skill].damage * (1 + .05*User.mag);
        if(heal > Target.maxhp - Target.hp)
            Target.hp += Target.maxhp - Target.hp;
        Target.hp += heal;
    }

    void Support(int skill, EntityClass Target){
        switch(skill){
            case tarukaja: Target[i].taru += 1; if(Target[i].taru >2){taru = 2; cout <<"It had no effect" <<endl;}
            case tarunda: Target[i].taru -= 1; if(Target[i].taru < -2){taru = -2; cout <<"It had no effect" <<endl;}
            case Rakukaja: Target[i].raku += 1; if(Target[i].raku >2){raku = 2; cout <<"It had no effect" <<endl;}
            case Raukunda: Target[i].raku -= 1;  if(Target[i].raku < -2){raku = -2; cout <<"It had no effect" <<endl;}
            case Sukukaja: Target[i].suku += 1; if(Target[i].suku >2){suku = 2; cout <<"It had no effect" <<endl;}
            case Sukunda: Target[i].suku -= 1;  if(Target[i].suku < -2){suku = -2; cout <<"It had no effect" <<endl;}
        }
        return;
    }

    void Damage(int skill, EntityClass Target, EntityClass User){
        if(VoidHit(skill, Target)){
            cout <<Target.Entity.name <<" didn't take any damage from that attack!" <<endl;
            //normal attack damage == 0
            return;
        }
        //(LVL + ATK - DEF/4)*base dmg/15 * CRIT MOD/WEAKNESS MOD * (1 + .25(user attack (taru) - target defense (raku)))
        int ATK, DEF;
        int dmg;
        if(SkillInfo[skill].type == "Physical"){
            ATK = User.Entity.str; DEF = Target.Entity.vit + Target.Entity.lvl;
        }
        else{
            ATK = User.Entity.mag; DEF = Target.Entity.vit + Target.Entity.lvl;
        }

        dmg = (User.lvl + ATK - DEF/2.5)*SkillInfo[skill].damage/15 * (1 + .125*(User.taru - Target.raku)); //well fuck
        if(CriticalChance(skill, Target, User) || WeaknessHit(skill, Target)) //weakness AND crit aint happening either.
            dmg *= 1.5;
        if(ResistHit(skill Target, User))
            dmg *= .5;
        
        if(dmg < 0) dmg == 0; //if for some reason the def is more than 250% greater than the atk, just negate it

        Target.hp -= dmg;
        //normal attack damage == 0
        PartyMemberDeath(Target);
        return;
    }

    bool CriticalChance(int skill, EntityClass Target, EntityClass User){
        //Base crit chance + (User luck - Target Luck)*3 + (User agi - target agi)/4 (0 if negative)
        if(SkillInfo[skill].type != "Physical") return false; //no magic crit shenanigans
        CritChance = SkillInfo[skill].critChance + (User.luck - Target.luck)*3 + (User.agi - Target.agi)/4;
        if(rand()%100 > CritChance)
            return false;
        cout <<"Landed a critcal hit!" <<endl;
        return true;
    }

    bool WeaknessHit(int skill, EntityClass Target){
        //for(int i=0; Target.Weakness[i]; i++){
        if(SkillInfo[skill].type == Target.Weakness[i]){
            cout <<"Weakness hit!" <<endl;
            return true;
        }
        //}
        return false;
    }

    bool ResistHit(int skill, EntityClass Target){
        //for(int i=0; Target.Resist[i]; i++){
            if(SkillInfo[skill].type == Target.Resist[i]){
                cout <<"They resisted that attack!" <<endl;
                return true;
            }
        //}
        return false;
    }

    bool VoidHit(int skill, EntityClass Target){
        //for(int i=0; Target.Void[i]; i++){
            if(SkillInfo[skill].type == Target.Void[i])
                return true;
        //}
        return false;
    }

    //after battle functions idk

    void PartyMemberDeath(EntityClass Target){
        if(Target.Entity.hp > 0)
            return;
        
        if(Target == ) GameOver();

        EntityClass *TargetParty = FindMemberParty(Target);
        int i;
        for(i= ReturnMemberLocation(TargetParty, Target); TargetParty[i+1]; i++){
            TargetParty[i] = Target[i+1];
        }
        delete TargetParty[i]; //this should be the last one
        //organize the targetted party here

        if(TargetParty == EnemyDemon){
            //exp gain goes up
            //money value goes up
            if(EnemyDemon is empty)
                //end the encounter
        }
    }

    EntityClass* FindMemberParty(EntityClass Source){
        for(int i=0; Party[i]; i++){
            if(Source == Party[i])
                return Party;
        }
        return EnemyDemon;
    }

    int ReturnMemberLocation(EntityClass *TargetParty, EntityClass Target){
        for(int i=0; TargetParty[i]; i++){
            if(Target == TargetParty[i])
                return i;
        }
        return -1; //THIS SHOULDN'T HAPPEN
    }
};