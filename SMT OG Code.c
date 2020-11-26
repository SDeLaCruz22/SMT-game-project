#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

char *party[5]={"Tatsuhiro", '\0', '\0', '\0', '\0'};//name of party memeber
char *heroine[1]={"Misaki"};
int party_stats[5][7]=  {       {0,0,0,50,10,1,0}, //str, mag, def, hp, mp, lvl, current xp this will have to be initalized in the main
                                {0,0,0,0,0,0,0},   
                                {0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0}, };
int party_skills[5][10]={       {1,0,0,0,0,0,0,0,0,0},//1=skill inherited
                                {1,0,0,0,0,0,0,0,0,0},
                                {1,0,0,0,0,0,0,0,0,0},
                                {1,0,0,0,0,0,0,0,0,0},
                                {1,0,0,0,0,0,0,0,0,0},};
int equipment[6]=           {0,0,0,0,0,0};//weapon, head, arm, chest, legs. Nihil
int macca=0; //macca carrying

void SMT_player_stats();//is called to increase stats and gain skills

void SMT_player(char map[25][18], int row, int col);//intakes the player's direction
void SMT_map(char map[25][18], char dungeon[25][18], int row, int col);//prints the map after every step
void SMT_event(char ap[25][18], char dungeon[25][18], int row, int col);//checks to see if the current space the player is on activates an event. Places a character for shops 

void SMT_Status();

void SMT_encounter(int boss);//happens after each step,presents the option to talk, battle, or flee
int SMT_flee(int demon);
void SMT_talk(char *enemy[11], int demon, int EnemyStats[11][7], int EnemySkills[11][10]);
void SMT_heal(char *enemy[11], int media, int mag, int taru, int healto);
void SMT_battle(char *enemy[11], int demon, int EnemyStats[11][7], char *skills[10], int skillcost[10], int EnemySkills[11][10], int taru, int raku);//player's turn to battle
int SMT_damage(int str, int mag, int hp, int def, int skill, int taru, int raku, float DEFEND, int turn);//damage step. used by both enemy and player. returns remaining health of recepient
void SMT_enemy(char *enemy[11], int demon, int EnemyStats[11][7], char *skills[10], int skillcost[10], int EnemySkills[11][10], int taru, int raku, float defend[5]);//enemy's turn to battle
void SMT_GameOver(int member);

int main(void){//this will just become void SMT() in the overall capstone
   char check;
   int xp=0;
    printf("Welcome to Shin Megami Tensei: Exodus. Would you like to read the background of the plot?(type y for yes or n for no)");
    scanf(" %c", &check);
    if(check=='y'||check=='Y'){
        printf("The world was struck with what is known as the Great Calamity, an event in which only the eldest have witnessed.");
        getchar();//will be using alot of these. Avoiding auto scroll text
        printf(" ");
        getchar();
        printf("It was a time where the progress of civilization was reverted back to its barebones.");
        getchar();
        printf("And though the cause of the Great Calamity remains unknown,  from it came entitities of the supernatural who arose from the unknown- demons.");
        getchar();
        printf("They have come upon mankind to claim this world as theirs.");
        getchar();
        printf("However, factions within the demons were created and have been fighting a war amongst each other with mankind being caught in the crossfire.");
        getchar();
        printf("Some factions chose not to participate in the conflict of inheriting the new world and took it upon themselves to guide humanity back in power.");
        getchar();
        printf("These small pockets of humanity's remaining hope are scattered around the world, waiting for the oppurtunity to come back. ");
        getchar();
    }
    SMT_player_stats();
    getchar();
    printf("Voice from afar: ..ert...mons....uary");
    getchar();
    printf("Feminine voice: ...st leave here.....");
    getchar();
    printf("Distorted voice: ...ill the...iah..."); 
    getchar();
    printf("Feminine voice: see...xt life");
    getchar();
    printf("Looming voice: Wandering human, identify yourself!");
    getchar();
    printf("The default name is: %s. Would you like to go by something else? (y or n)\n", party[0]);
    scanf(" %c", &check);
    if(check=='y'||check=='Y'){
        NAME:
        printf("What name will you put? (Max character 10)\n");
        party[0]=malloc(10*sizeof(char));
        scanf("%s", party[0]);
        if(strlen(party[0])>10)
            goto NAME;
    }        
    getchar();
    printf("Looming voice: You are no longer what you were.");
    getchar();
    printf("Looming voice: A new era is upon us to rid of these dark times.");
    getchar();
    printf("Looming voice: The Goddess awaits your prescence, Hear her calls!");
    getchar();
    printf("Goddess: %s. Call out my name! Make my destiny be entertwined with yours!", party[0]);
    getchar();
    printf("The default name is: %s. Would you like her to go by something else? (y or n)\n", heroine[0]);
    scanf(" %c", &check);
    if(check=='y'||check=='Y'){
        printf("What name will you put? (Max character 10)\n");
        heroine[0]=malloc(10*sizeof(char));
        scanf("%s", heroine[0]);
    }   
    getchar();
    printf("Looming voice: Now awake yourself, and march towards your baptism to begin your new life!");
    getchar();
    printf("You awake from the dream and find yourself in the middle of a barren wasteland.");
    getchar();
    printf("The view is still as you remembered, a broken artifact of a past almost forgotten.");
    getchar();
    printf("Despite not knowing where you are, you walk knowing what path to take.");
    getchar();
    printf("A cave appears to you and you walk into it...\n\n\n");
    getchar();
    char map[27][18];
    int row=23, col=1;
    //int row=3, col=9; //checking for Cu stuff
    for(int i=0; i<27;i++){
        for(int j=0;j<18;j++){
            map[i][j]=' ';
        }
    }
    for(int j=0;j<3;j++){
        if(j==0){
            map[23][j]='|';
        }
        if(j==1){
            map[23][1]='O';
            map[24][1]='-';
        }
        if(j==2){
            map[23][j]='|';
        }
        printf("%c", map[23][j]);
    }
    printf("\n %c", map[24][1]);
    map[23][1]=' ';
    printf("\n");
    SMT_player(map, row, col);
return(0);
}

void SMT_player_stats(){//comes back after battle is finished to check if player levels up 
    char stat, skillQ;
    int ability, boss=0;
    int player_exp[9]={10, 25, 45, 70, 100, 135, 175, 220, 270};//lvl=2+element [exp[0] is for level 2 threshhold)
    if(party_stats[0][0]==0 && party_stats[0][1]==0 && party_stats[0][2]==0){
        printf("\n\nPlease allocate 4 points to your stats\n");
        for(int i=0;i<4;i++){
            FIRSTSTATS:
            printf("\n\nWhat stat will you put a point in?\nStrength(s)\nMagic(m)\nDefense(d)\n");
            scanf(" %c", &stat);
            switch(stat){
                case 's':
                        party_stats[0][0]+=1;
                        break;
                case 'm':
                        party_stats[0][1]+=1;
                        break;
                case 'd':
                        party_stats[0][2]+=1;
                        break;
                default:
                        goto FIRSTSTATS;
                        break;
            }
            party_stats[0][3]=50+5*party_stats[0][5]+5*party_stats[0][2]; //50+5*lvl+5*def
            party_stats[0][4]=10+2*party_stats[0][5]+2*party_stats[0][1]; //10+2*lvl+2*mag we still need armor and weapons
        }
    }
    for(int i=8; i>=0;i--){
        if(party_stats[0][6]>=player_exp[i] && party_stats[0][5]!=10 && party_stats[0][5]==(i+1)){
            STATALLOCATION:
            party_stats[0][5]+=1;
            party_stats[0][3]=50+5*party_stats[0][5]+5*party_stats[0][2]+equipment[1]+equipment[2]+equipment[3]+equipment[4]; //50+5*lvl+5*def
            party_stats[0][4]=10+2*party_stats[0][5]+2*party_stats[0][1]; //10+2*lvl+2*mag we still need armor and weapons
            printf("Please allocate a point to your stats\n");
            printf("\n\nWhat stat will you put a point in?\nStrength(s)\nMagic(m)\nDefense(d)\n");
            scanf(" %c", &stat);
            switch(stat){
                case 's':
                        party_stats[0][0]+=1;
                        break;
                case 'm':
                        party_stats[0][1]+=1;
                        break;
                case 'd':
                        party_stats[0][2]+=1;
                        break;
                default:        
                        goto STATALLOCATION;
                        break;
            }
            break;
        }
    }
    if(party_stats[0][6]==0||party_stats[0][6]>=70||party_stats[0][6]>=270){
        printf("You are about to learn a skill. Would you like to know the effects of the skills? (y or n)\n");
        scanf(" %c", &skillQ);
        if(skillQ=='y'||skillQ=='Y'){
            getchar();
            printf("Slash lets you use an empowered physical based attack.\nAgi lets you summon a magical fire onto your enemies\nBufu lets you summon a magical wave of ice onto your enemies\nDia lets you heal a single member substantially\nMedia lets you mildly heal the party\nTarukaja raises the attack and effectiveness of all abilities for the party\nRakukaja raises defenses of the party\n");
            getchar();
        }
        LEARNSKILL:
        printf("\n\nYou may learn a skill. Enter the number that corresponds to the skill number\n1.Slash   2.Agi   3.Bufu   4.Dia   5.Media   6.Tarukaja   7.Rakukaja\n");
        scanf("%d", &ability);
        printf("\n");
        if(ability==1){
            if(party_skills[0][ability]==1){
                printf("Skill already learned!\n");
                goto LEARNSKILL;
            } 
        }
        if(ability>=2){
            if(party_skills[0][ability+2]==1){
                printf("Skill already learned!\n");
                goto LEARNSKILL;
            }    
        }
        switch(ability){
            case 1:
                    party_skills[0][1]=1;
                    break;
            case 2:
                    party_skills[0][4]=1;
                    break;
            case 3:
                    party_skills[0][5]=1;
                    break;
            case 4:
                    party_skills[0][6]=1;
                    break;
            case 5:
                    party_skills[0][7]=1;
                    break;
            case 6:
                    party_skills[0][8]=1;
                    break;
            case 7:
                    party_skills[0][9]=1;
                    break;
            default:
                    goto LEARNSKILL;
                    break;
        }
    }
}

void SMT_player(char map[25][18], int row, int col){
    int boss=0;
    char dungeon[25][18]={
	    		{".----------------."},//1
		    	{"|D      |B|C     |"},//[1] A= Nihil C=Demon who gives suggestions
			    {"|-----  | |----- |"},//3
			    {"|         |      |"},//[3] 
			    {"|  ---------  ---|"}, //5
			    {"|                |"},
			    {"|  ------------. |"},//7
			    {"|     |9 |7   8| |"},//9 treasure 50 macca
			    {"|  -  |- |   .-| |"},//9
			    {"| |6| |  |-  | | |"},//6 scathach
			    {"|     | -| | | | |"},//11
		    	{"|        |       |"},
			    {"|--------------- |"},//13
			    {"|   |H|    |3|   |"}, 
			    {"| | |        | --|"}, //15
			    {"| |4|    |1|2|   |"},//4=armor treasure
			    {"| +-+-   +---|-- |"},//17
			    {"|  A|W       |   |"},
			    {"|  -+-       | --|"},//19
			    {"|          |G|   |"},
			    {"| .--------+ |   |"},//21
			    {"| |    |     | | |"},
			    {"|S| |  | ------+ |"},//23
			    {"| | |            |"},//(23)
			    {"|----------------|"},//25 (24)
	};
    char direction;
    printf("\n\nWhich direction will you go? Alternatively, you could check the COMP (w=up,a=left,s=down, d=right, c=COMP)\n");
    scanf(" %c", &direction);
    switch(direction){
        case 'w': //goes up array row decreases
                if(row==0||dungeon[row-1][col]=='-'||dungeon[row-1][col]=='|'||dungeon[row-1][col]=='.'||dungeon[row-1][col]=='+')//not using !=' ' due to events on certain arrays
                    SMT_player(map, row, col);
                row-=1;
                break;
        case 'a'://goes left col dec
                if(col==0||dungeon[row][col-1]=='-'||dungeon[row][col-1]=='|'||dungeon[row][col-1]=='.'||dungeon[row][col-1]=='+')
                    SMT_player(map, row, col);
                col-=1;
                break;
        case 's'://goes down row inc
                if(row==23||dungeon[row+1][col]=='-'||dungeon[row+1][col]=='|'||dungeon[row+1][col]=='.'||dungeon[row+1][col]=='+')
                    SMT_player(map, row, col);
                row+=1;
                break;
        case 'd'://goes right incr
                if(col==18||dungeon[row][col+1]=='-'||dungeon[row][col+1]=='|'||dungeon[row][col+1]=='.'||dungeon[row][col+1]=='+')
                    SMT_player(map, row, col);
                col+=1;
                break;
        case 'c':SMT_Status();
        default:
                SMT_player(map, row, col);
                break;
    }
    SMT_event(map, dungeon, row, col);
    SMT_encounter(boss);
    SMT_map(map, dungeon, row, col);
}

void SMT_Status(){
    char dismissQ;
    int dismiss;
    PARTYVIEW:
    printf("  Party\t\tHP\tMP\tStr\tMag\tDef\tLvl\tMacca\tExp\n");
    for(int i=0;i<5;i++){
        if(party[i]!='\0'){ 
            if(strlen(party[i])>=6){
                printf("%d.%s\t%d\t%d\t%d\t%d\t%d", i+1, party[i], party_stats[i][3], party_stats[i][4], party_stats[i][0], party_stats[i][1], party_stats[i][2]);
                if(i==0){
                    printf("\t%d\t%d\t%d\n", party_stats[i][5], macca, party_stats[i][6]);
                    continue;
                }
                printf("\n");
                continue;
            }
            printf("%d.%s\t\t%d\t%d\t%d\t%d\t%d", i+1, party[i], party_stats[i][3], party_stats[i][4], party_stats[i][0], party_stats[i][1], party_stats[i][2]);
            if(i==0){
                printf("\t%d\t%d\t%d\n", party_stats[i][5], macca, party_stats[i][6]);
                continue;
            }
            printf("\n");
        }
    }
    if(strlen(party[0])<=6)
        printf("%s's equipment:\tWeapon\tHelmet\tArms\tChest\tLeggings\n\t\t\t%d\t%d\t%d\t%d\t%d\n", party[0], equipment[0], equipment[1], equipment[2], equipment[3], equipment[4]);
    else
        printf("%s's equipment:Weapon\tHelmet\tArms\tChest\tLeggings\n\t\t\t%d\t%d\t%d\t%d\t%d\n", party[0], equipment[0], equipment[1], equipment[2], equipment[3], equipment[4]);
    printf("Will you dismiss a demon?(y or n)\n");
    scanf(" %c", &dismissQ);
    if(dismissQ=='y'||dismissQ=='Y'){
        printf("Who will you dismiss? (enter their number position)\n");
        scanf("%d", &dismiss);
        if(dismiss==1){
            printf("Can't dismiss party leader!\n");
            return;
        }
        for(int i=dismiss-1;i<5;i++){
            if(party[i]=='\0')
                break;
            if(i==4)
                party[i]='\0';
            party[i]=party[i+1];
            for(int j=0;j<7;j++){
                party_stats[i][j]=party_stats[i+1][j];
            }
            for(int k=0;k<10;k++){
                party_skills[i][k]=party_skills[i+1][k];
            }
        }
        goto PARTYVIEW;
    }
    else
        return;
}

void SMT_map(char map[25][18], char dungeon[25][18], int row, int col){
	map[row][col]='O';
	for(int i=(row-1);i<(row+2); i++){
	    for(int j=(col-1); j<(col+2);j++){
	       if(dungeon[i][j]=='-'||dungeon[i][j]=='|'||dungeon[i][j]=='.'||dungeon[i][j]=='+'){
	                map[i][j]=dungeon[i][j];
	       }
	    }
	}
	for(int i=0;i<25;i++){
        for(int j=0;j<18;j++){
            printf("%c", map[i][j]);
        }
        printf("\n");
	}
    map[row][col]=' ';
    SMT_player(map, row, col);
}

void SMT_event(char map[25][18], char dungeon[25][18], int row, int col){
    char square, continueshop;
    int shop;
    if(dungeon[row][col]!=' '){
        square=dungeon[row][col];
        switch(square){
            case 'A':
                    getchar();
                    printf("\n\nArmorer: What a scrawny kid you are");
                    getchar();
                    printf("Armorer: Hey have you seen some armor lying around these parts? Some punk ran off with my stuff, but I don't think he got very far.");
                    getchar();
                    printf("Armorer: Anyways, what can I do you for?");
                    getchar();//enter armor shop
                    int armorcost[]={25,25,50,25};
                    int armorrate[]={5,5,10,5};
                    ARMORSHOP:
                    printf("Armor\t\tMacca\tDef\n1.Helmet\t\t25\t5\n2.Armguard\t\t25\t5\n3.Chest\t\t50\t10\n4.Leggings\t\t25\t5\nCurrent Macca:%d\nPress the number correlated to the armor to purchase or press 0 to leave\n", macca);
                    scanf("%d", &shop);
                    if(shop==0){
                        ENDASHOP:
                        printf("\nArmorer: Drop in anytime\n");
                        return;
                    }    
                    if(macca>=armorcost[shop-1]){
                        if(equipment[shop]!=0){
                            getchar();
                            printf("\nArmorer: Oh, it seems you already have this\n");
                            getchar();
                            goto ARMORSHOP;
                        }
                        macca-=armorcost[shop-1];
                        equipment[shop]=armorrate[shop-1];
                        party_stats[0][3]=50+5*party_stats[0][5]+5*party_stats[0][2]+equipment[1]+equipment[2]+equipment[3]+equipment[4];
                        printf("\nArmorer: Thank you for your purchase.\nAnything else? (y or n)\n");
                        scanf(" %c", &continueshop);
                        if(continueshop=='y'||continueshop=='Y')
                            goto ARMORSHOP;
                        else    
                            goto ENDASHOP;
                    }
                    else{
                        getchar();
                        printf("\nArmorer: Sorry kid, bring more macca\n\n");
                        getchar();
                        goto ARMORSHOP;
                    }
                    break;
            case 'S':
                    getchar();
                    printf("\n\n\nAs you wandered inside the cave you find yourself surrounded by many armed men with guns. ");
                    getchar();
                    printf("Town Guard: STOP! Are you human?");
                    getchar();
                    printf("You nod your head");
                    getchar();
                    printf("Town Guard: Prove it! Show us if you bleed!");//too awkward sounding
                    getchar();
                    printf("The town gaurd throws a small pick at your feet. You pick it up and you slowly stab the palm of your hand, enough to show the blood spilling from it");
                    getchar();
                    printf("Town Guard: What a relief. At ease, boys. You! Come over here");
                    getchar();
                    printf("Town Guard: Where do you come from?");
                    getchar();
                    printf("You shrug, saying that you don't remember anything about yourself");
                    getchar();
                    printf("Town Guard: Hmmm....");
                    getchar();
                    printf("Town Guard: Hey, is that a COMP? Where did you find such a thing? No matter, you should hang onto that. I hear you can talk to demons with that, it might prove useful.");
                    getchar();
                    printf("Town Guard: Are you not carrying a weapon with you? Please, take my spare knife. You can't be walking around without being able to defend yourself");
                    getchar();
                    printf("Town Guard: I would give you a gun, but these days finding ammo and a gun is rare. Only guards like me are allowed to carry them to fight off the demons");
                    getchar();
                    printf("Town Guard: Up ahead is the sanctuary Stix. You should be able to find some people who can help you out.");
                    getchar();
                    printf("Town Guard: Hey Kid! Before you go, what's your name?");
                    getchar();
                    printf("Town Guard: %s...I see. Go ahead %s, hope to see you alive next time.", party[0], party[0]);
                    getchar();
                    equipment[0]=10;
                    break;
            case 'W':
                    getchar();
                    printf("\n\nWeaponsmith: Ever since the Great Calamity, you can't seem to find a person who isn't carrying a weapon around here");
                    getchar();
                    printf("Weaponsmith: Speaking of which, how can I be of service to you?");//enter weapon shop
                    getchar();
                    int weaponcost[]={25,75,200};
                    int weaponrate[]={15,20,25};
                    WEAPONSHOP:
                    printf("Weapon\t\t\tMacca\tDef\n1.Short sword\t\t25\t15\n2.Short Sword\t\t75\t20\n3.Great Sword\t\t200\t25\nCurrent Macca:%d\nPress number for weapon or press 0 to leave\n", macca);
                    scanf("%d", &shop);
                    if(shop==0){
                        ENDWSHOP:
                        printf("\nWeaponsmit: Drop in anytime\n");
                        return;
                    }    
                    if(macca>=weaponcost[shop-1]){
                        if(equipment[0]==weaponrate[shop-1]){
                            getchar();
                            printf("\nWeaponsmit: Oh, it seems you already have this\n");
                            getchar();
                            goto WEAPONSHOP;
                        }
                        macca-=weaponcost[shop-1];
                        equipment[0]=weaponrate[shop-1];
                        getchar();
                        printf("\nWeaponsmith: Thank you for your purchase.\nAnything else? (y or n)\n");
                        scanf(" %c", &continueshop);
                        if(continueshop=='y'||continueshop=='Y')
                            goto WEAPONSHOP;
                        else    
                            goto ENDWSHOP;
                    }
                    else{
                        getchar();
                        printf("\nWeaponsmith: Sorry kid, bring more macca\n\n");
                        getchar();
                        goto WEAPONSHOP;
                    }
                    break;
            case 'H':
                    getchar();
                    printf("\n\nAme no Uzume: The Amatsukami sent me here to provide assistance to a potential messiah in rising.");
                    getchar();
                    printf("Ame no Uzume: Here let me heal your wounds and replenish your energy.");
                    getchar();
                    party_stats[0][3]=50+5*party_stats[0][5]+5*party_stats[0][2]; //50+5*lvl+5*def
                    party_stats[0][4]=10+2*party_stats[0][5]+2*party_stats[0][1]; //10+2*lvl+2*mag we still need armor and weapons
                    for(int i=1;i<5;i++){//might make this a seperate function
                        char holder[20];
                        if(party[i]!='\0'){
                            strcpy(holder,party[i]);
                            switch(holder[0]){
                                case 'P':
                                        if(holder[1]=='I'){
                                            party_stats[i][3]=60;
                                            party_stats[i][4]=50;
                                        }
                                         if(holder[1]=='Y'){
                                            party_stats[i][3]=75;
                                            party_stats[i][4]=15;
                                        }
                                        break;
                                case 'J':
                                        party_stats[i][3]=70;
                                        party_stats[i][4]=20;
                                        break;
                                case 'M':
                                        if(holder[2]=='T'){
                                            party_stats[i][3]=70;
                                            party_stats[i][4]=25;
                                        }
                                        if(holder[2]=='C'){
                                            party_stats[i][3]=70;
                                            party_stats[i][4]=20;
                                        }
                                         if(holder[1]=='M'){
                                            party_stats[i][3]=90;
                                            party_stats[i][4]=10;
                                        }
                                        break;
                                case 'N':
                                        party_stats[i][3]=70;
                                        party_stats[i][4]=15;
                                        break;
                                case 'L':
                                        if(holder[1]=='I'){
                                            party_stats[i][3]=65;
                                            party_stats[i][4]=40;
                                        }
                                         if(holder[1]=='E'){
                                            party_stats[i][3]=70;
                                            party_stats[i][4]=20;
                                        }
                                        break;
                                case 'O':
                                        party_stats[i][3]=80;
                                        party_stats[i][4]=15;
                                        break;
                            }
                        }    
                    }
                    printf("Ame no Uzume: Farewell");
                    getchar();
                    break;
            case 'M'://i prob wont do this
                    getchar();
                    printf("\n\nMerchant: A lot of things died during the Great Calamity, but money is still king");
                    getchar();
                    printf("Merchant: What do you want?");
                    getchar();
                    break;
            case '1':
                    getchar();
                    printf("\n\nOld Man: In one life, I was a man very much like you and I committed the ultimate sin, but I don't remember what I did.");
                    getchar();
                    printf("Old Man: In another life, I vaguely remember helping out a kid who had become a demon on the outside, but a human inside. I feel regret for that life, and again, I don't remember what happened.");
                    getchar();
                    printf("Old Man: I hope I make this life less tiresome.");
                    getchar();
                    printf("Woman: Stop talking crazy! Sorry about him, he is a little delusional.");
                    getchar();
                    break;
            case '2':
                    getchar();
                    printf("\n\nLittle Girl: Ever since daddy went out, I've been living with my doggy Pascal and he is my best friend. He protects me from the demons, but he isn't very nice to others.");
                    getchar();
                    printf("Pascal *bark *bark*.");
                    getchar();
                    printf("Little Girl: Thats weird, Pascal likes you. I wonder why...?");
                    getchar();
                    if(equipment[5]==1){
                        printf("Little Girl: Is that...daddy's sword...");
                        getchar();
                        printf("Realizing this is the girl the traveler mentioned as his last word, you give her the necklace");
                        getchar();
                        printf("Little Girl: *sob*...*sob*...");
                        getchar();
                        printf("Little Girl:...");
                        getchar();
                        printf("You see the dog, Pascal, grow in size. It stares into your eyes, as if its valuing your soul. You hear a voice inside your head");
                        getchar();
                        printf("Voice: I am Cerberus");
                        getchar();
                        printf("Cerberus: She may be crying right now, but it is for the better that she knows");
                        getchar();
                        printf("Cerberus: That man was a former master of mine, I've been serving him for several lifetimes");
                        getchar();
                        printf("Cerberus: Thank you for your empathy. As a token of my appreciation, I will restore the power of that sword, Nihil, for your wielding");
                        getchar();
                        printf("You obtained Nihil");
                        getchar();
                        printf("Cerberus: You may go, I will watch over this girl");
                        getchar();
                        equipment[0]=30;
                    }
                    break;
            case '3':
                    getchar();
                    printf("\n\nMan in wheel chair: Ah, its you. You must be %s correct? I am Stephen, creator of that COMP you are wielding.", party[0]);
                    getchar();
                    printf("Stephen: The COMP uses the demon summoning program which was created by a young man similar to you, though you won't find him in this universe.");
                    getchar();
                    printf("Stephen: If you haven't noticed already, the COMP allows you to learn abilities that a normal human could never be able to learn.");
                    getchar();
                    printf("Stephen: The COMP is actually making so that the user imitates a demon, which is also why you are able to talk to them and recruit them.");
                    getchar();
                    printf("Stephen: The COMP combined with the potential of a human makes for a formidable foe against the demons.");
                    getchar();
                    printf("Stephen: %s, your current task is to continue beyond this sanctuary, and there you should find the purpose of your being.", party[0]);
                    getchar();
                    printf("Stephen: There you should know the Great Will");
                    getchar();
                    break;
            case '4':
                    getchar();
                    printf("\n\nAs you walk, you trip over something. You checked out what you tripped over and find a helmet in mint condition!");
                    getchar();
                    printf("Helemt equipped");
                    getchar();
                    equipment[1]=5;
                    party_stats[0][3]+=5;
                    break;
            case '6':
                    getchar();
                    printf("\n\nDemoness: Well, if it isn't a human.");
                    getchar();
                    printf("Demoness: Don't worry I won't kill you. I am Scathach.");
                    getchar();
                    printf("Scathach: I've sent my best pupil to guard this sanctuary. He has done a splendid job at preventing the worst of the demons to come through.");
                    getchar();
                    printf("Scathach: Though, knowing him, he is dying to receive a good challenge.");
                    getchar();
                    printf("Scathach: Hmmm.");
                    getchar();
                    printf("Scathach: You have potential. Maybe he'll be thrilled to fight you.");
                    getchar();
                    printf("Scathach: Be warned though, he is quite adept to using magic and his fancy lance.");
                    getchar();
                    printf("Scathach: Oh and between you and me, I think the way he talks is too cheesy HAHAHA!");
                    getchar();
                    //printf("Come back to me when you are at your strongest");
                    break;
            //case '5':
            case '7':
                    getchar();
                    printf("\n\nDemon: Listen to me, boy! The angels have brainwashed you humans for a long time!");
                    getchar();
                    printf("Demon: You don't even know how noble master Lucifer's mission is!");
                    getchar();
                    printf("Demon: Besides, they call themselves angels even though they are still demons like us!");
                    getchar();
                    printf("Demon: If you side them, I hope you have fun living under their tyrannical rule for the rest of eternity!");
                    getchar();
                    break;
            case '8':
                    getchar();
                    printf("\n\nAngel: Don't taint your ears from the likes of a demon.");
                    getchar();
                    printf("Angel: We offer peace and stability to those who believe in our cause.");
                    getchar();
                    printf("Angel: We want to avoid the savage ways of the demons and instead create a Eutopia under the Creator.");
                    getchar();
                    break;
            case '9':
                    getchar();
                    printf("\n\nWhile wandering, you found some macca lying around.");
                    getchar();
                    printf("Obtained 50 macca!");
                    getchar();
                    macca+=50;
                    break;
            case 'D':
                    getchar();
                    printf("\n\nWhile wandering, you find a traveler, gravely injured");
                    getchar();
                    printf("Traveler:...you...look strong *cough*");
                    getchar();
                    printf("Traveler:...please...take...Nihil");
                    getchar();
                    printf("The traveler slowly pushes his sword towards you, you notice that it's blade is shattered");
                    getchar();
                    printf("Traveler: ...it will...do you good...");
                    getchar();
                    printf("You hold the sword and knee beside the traveler. With his last strength, he hands you a necklace");
                    getchar();
                    printf("Traveler:...Suzie...");
                    getchar();
                    printf("The traveler dies, you take his broken sword and necklace to uphold his honor");
                    getchar();
                    equipment[5]=1;
                    break;
            case 'C':
                    getchar();
                    printf("You see a demon up ahead, but it doesn't seem to want to fight");
                    getchar();
                    printf("Demon: Behind this wall is a strong one. If you were to fight him unprepared, you would most certainly die");
                    getchar();
                    printf("Demon: But if you were too somehow make yourself stronger...then maybe");
                    getchar();
                    break;
            case 'B':
                    getchar();
                    printf("\n\nWhat venturous soul enters the realm of the demons?");
                    getchar();
                    printf("I am Cu Chulainn, protector of this sanctuary, and you must be the %s I've been hearing so much about from my teacher.", party[0]); 
                    getchar();
                    printf("Cu Chulainn: For the past several decades, I have seen the damage done by both Lucifer's army as well as the Angelic forces sent from the Creator.");
                    getchar();
                    printf("Cu Chulainn: This war will never end by the forces of Law or Chaos themselves.");
                    getchar();
                    printf("Cu Chulainn: As determined by the Great Will, it is only up to mankind where the balance will be tipped, and I stand here to protect the realm where the foretold messiah will emerge from.");
                    getchar();
                    printf("Cu Chulainn: If you dare to change the fate of mankind, you must prove your worthiness with your life!");
                    getchar();
                    int boss=1;
                    SMT_encounter(boss);
                    getchar();
                    printf("Cu Chulainn: Hmph...well done. You have proven your worthiness to me and I shall let you pass.");
                    getchar();
                    printf("Cu Chulainn: Let this be a warning though, your road is to be full of tribulations.");
                    getchar();
                    printf("Cu Chulainn: Don't let that deter you. You must be strong.");
                    getchar();
                    printf("Cu Chulainn: Your choice is the one that all of mankind will be living under by.");
                    getchar();
                    printf("Cu Chulainn: Now...go off!");
                    getchar();
                    printf("...");
                    getchar();
                    printf("Cu Chulainn: Messiah.");
                    getchar();
                    printf("\n\n\n\nThank You for playing Shin Megami Tensei: Exodus\n\n\n\n");
                    getchar();
                    printf("Voice: Tatsuhiro, is that you?");
                    getchar();
                    printf("A woman stands there, she seems familiar but you've never seen her before");
                    getchar();
                    printf("Woman: I told you I was going to see you in the next life. You dont remember...?");
                    getchar();
                    printf("...");
                    getchar();
                    printf("%s: ...%s...", party[0], heroine[0]);
                    getchar();
                    printf("%s smiles.", heroine[0]);
                    getchar();
                    printf("%s: I've been waiting for you...", heroine[0]);
                    getchar();
                    printf("%s: %s", heroine[0], party[0]);
                    getchar();
                    //main of capstone
                    //game over scren
                    break;
        }
    }
}

void SMT_encounter(int boss){//encounter should be the one to house all the paramaters that any battle related function will use 
	int taru=0, raku=0;
	char *enemy[]= {"PIXIE", "JACK FROST", "PYRO JACK", "MOTHMAN", "NEKOMATA", "LILLIM", "LEANAN SIDHE", "MACABRE", "MOMUNOFU", "OSE", "CU CHULAINN"}; //Cu is [10] #11
	int EnemyStats[11][7]={ //[demon]
	    {2, 6, 3, 60, 50, 5, 5}, 
	    {4, 4, 5, 70, 20, 9, 7}, 
	    {4, 4, 6, 75, 15, 8, 10}, 
	    {5, 5, 5, 70, 25, 9, 10}, 
	    {6, 3, 5, 70, 15, 10, 15}, 
	    {2, 7, 4, 65, 40, 10, 8}, 
	    {5, 4, 5, 70, 20, 11, 12}, 
	    {5, 5, 5, 70, 20, 12, 15}, 
	    {6, 2, 7, 90, 10, 15, 20}, 
	    {7, 2, 5, 80, 15, 15, 25}, 
	    {8, 12, 8, 1500, 1000, 75, 100} }; //str, mag, def, hp, mp, exp gain, macca gain
	int EnemySkills[11][10]={ //[demon][skill]
		{1, 0, 0, 0, 0, 0, 0, 1, 0, 1}, //pixie
		{1, 0, 0, 0, 0, 1, 0, 0, 1, 0}, //JF
		{1, 0, 0, 0, 1, 0, 0, 0, 0, 1}, //PJ
		{1, 0, 0, 0, 0, 0, 1, 0, 0, 1}, //Moth
		{1, 1, 0, 0, 0, 0, 1, 0, 0, 0}, //Neko
		{1, 0, 0, 0, 0, 0, 0, 1, 0, 1},  //Lillim
		{1, 0, 0, 0, 0, 0, 1, 0, 1, 0},  //Leanan Sidhe
		{1, 1, 0, 0, 1, 0, 0, 0, 0, 0},  //Macabre
		{1, 1, 0, 0, 0, 0, 0, 0, 1, 0},  //Momunofu
		{1, 1, 0, 0, 0, 0, 0, 0, 1, 0},   //Ose
		{1, 0, 1, 1, 0, 0, 0, 0, 0, 0},};//Cu
	char *skills[]={"Normal Attack", "Slash", "Deathbound",  "Floral Gust", "Agi", "Bufu", "Dia", "Media", "Tarukaja", "Rakukaja"};
    int skillcost[10]={0,3,3,3,3,3,2,6,3,3};	
	int spawn, demon;
	char option;
    int flee;
	if(boss==1){
	    demon=10;
	    goto ENEMYENCOUNTER;
	}
	//spawn=rand()%5;//change encounter rate or increase variety. 5 will be the test??
	spawn=rand()%8;
	if(spawn==0){
		demon=rand()%10;
		ENEMYENCOUNTER:
		printf("Enemy Encountered! It's %s!\n", enemy[demon]);
		printf("Party\t\tHP\tMP\n");
        for(int i=0;i<5;i++){
            if(party[i]!='\0'){
                if(strlen(party[i])>=8){
                    printf("%s\t%d\t%d\n", party[i], party_stats[i][3], party_stats[i][4]);
                    continue;
                }    
                printf("%s\t\t%d\t%d", party[i], party_stats[i][3], party_stats[i][4]);
            }
            printf("\n");
        }
		PREBATTLE:
	    printf("What will you do?\tBattle (b)\tTalk (t)\tFlee (f)\n");	
	    scanf(" %c", &option);
	    switch(option){
	        case 'b':
	        case 'B':
	            SMT_battle(enemy, demon, EnemyStats, skills, skillcost, EnemySkills, taru, raku); 
	            break;
	        case 't':
	        case 'T':
	            if(demon==10){
	                printf("%s is concentrated on the battle!\n", enemy[demon]);
	                goto PREBATTLE;
	            }
	            SMT_talk(enemy, demon, EnemyStats, EnemySkills);
	            break;
	        case 'f':
	        case 'F':
	                flee=SMT_flee(demon);
	                if(flee==1)
	                    return;
	               else
	                    goto PREBATTLE;
	               break;
	        default:
	                goto PREBATTLE;
	                break;
	}
	return;
	}
}

int SMT_flee(int demon){
    int flee;
    if(demon==10){
        getchar();
	    printf("You can't flee from this battle!\n");
	    getchar();
	    return(0);
	}
	flee=rand()%2;
	if(flee==1){
	    getchar();
	    printf("You've fleed from battle!\n");
	    getchar();
	    return(1);
	}     
	else{
	    getchar();
	    printf("You couldn't escape!\n");
	    getchar();
	    return(0);          
	}
}

void SMT_talk(char *enemy[11], int demon, int EnemyStats[11][7], int EnemySkills[11][10]){
    int space=4, choice;
    switch(demon){
        case 0://pixie dialogue
                printf("Pixie: Hey, will you protect me with your life?\n");
                printf("What will you say?\n1.I will treasure you\t2.I live a dangerous life\n");
                scanf("%d", &choice);
                if(choice==2){
                    printf("Pixie: Thank you for being honest with me. Will you let me join your party?\n1.Yes.2.Get away from me\n");
                    scanf("%d", &choice);
                    if(choice==1){
                        printf("Pixie: Now to be on an adventure together\n");
                    } 
                    else{
                        getchar();
                        printf("Pixie: ...Disappointing\n%s fled!", enemy[demon]);
                        getchar();
                        return;
                    }
                }
                else{
                    getchar();
                    printf("...Disappointing\n%s fled!", enemy[demon]);
                    getchar();
                    return;
                }
                break;
        case 1:
                printf("Jack Frost: I'll pound the hee outta you, ho");
                printf("What will you say?\n1.Good luck, punk\t2.Oh...I'm sorry...\n");
                scanf("%d", &choice);
                if(choice==1){
                    printf("Jack Frost: Oh you think you are tough? If you're such hot shit then crush this rock with you bare hands!");
                    getchar();
                    if(party_stats[0][0]>=4){
                        printf("\nYou took the rock and smashed into little pieces!\n");
                        printf("Jack Frost: WHOAH! From this day forward, you and I are hee ho bros");
                        getchar();
                        break;
                    }
                    else{
                        getchar();
                        printf("%s struggled with a rock in hand!\nJack Frost: I'll beat the hee outta ho later!\n%s fled!", party[0], enemy[demon]);
                        getchar();
                        return;
                    }
                }
                else{
                        getchar();
                        printf("Jack Frost: You aren't worth my time! Hee you later, ho!\n%s fled!", enemy[demon]);
                        getchar();
                        return;
                }
                break;
        case 2://PJ
                printf("Pyro Jack: Oh a low life human. You got 5 seconds to convince me your worth\n");
                printf("What will you say?\n1.How about you prove yourself to me\t2.In 5 seconds you won't be alive\n");
                scanf("%d", &choice);
                if(choice==1){
                    printf("Pyro Jack: Perhaps we should settle this with a fight\nWhat Will you do?\n1.Stare at him menacingly\t2.Battle Stance\n");
                    scanf("%d", &choice);
                    if(choice==1){
                        printf("Pyro Jack: You're a cold one, just like my brother ho.\n");
                        break;
                    }
                    else{
                        getchar();
                        printf("Pyro Jack: Brutes are fools\n%s fled!", enemy[demon]);
                        getchar();
                        return;
                    }
                }
                else{
                        getchar();
                        printf("Pyro Jack: Pathetic...\n%s fled!", enemy[demon]);
                        getchar();
                        return;
                }
                break;
        case 3://mothman-innocent dark personality
                printf("Mothman: Is it true that when humans die, they gain eternal peace?\n");
                printf("What will you say?\n1.Uh...no\t2.Actually we spill out sunshine and rainbows\n");
                scanf("%d", &choice);
                if(choice==2){
                    printf("Mothman: Will you show me how it looks like?\nWhat Will you say?\n1.Of course!\t2.Not if you show me first\n");
                    scanf("%d", &choice);
                    if(choice==1){
                        printf("Mothman: I like you. Lets spread peace to everyone!\n");
                        break;
                    }
                    else{
                        getchar();
                        printf("Mothman: Ah! That's too much commitment!\n%s fled!", enemy[demon]);
                        getchar();
                        return;
                    }
                }
                else{
                        getchar();
                        printf("Mothman: Booooorinnnng!\n%s fled!", enemy[demon]);
                        getchar();
                        return;
                }
                break;
        case 4://Nekomata- cool aloof quiet sexy||expressionless tsundere?
               printf("Nekomata: Do...you...want me?\n");
                printf("What will you say?\n1.Yes, please!\t2.I dont need you\n");
                scanf("%d", &choice);
                if(choice==2){
                    printf("Nekomata: Then, what do you want..?\n1.An ally\t2.An alliance\n");
                    scanf("%d", &choice);
                    if(choice==2){
                        printf("Nekomata: Very well...\n");
                        break;
                    }
                    else{
                        getchar();
                        printf("Nekomata: Eek!\n%s fled!", enemy[demon]);
                        getchar();
                        return;
                    }
                }
                else{
                        getchar();
                        printf("Nekomata: You're...disgusting.\n%s fled!", enemy[demon]);
                        getchar();
                        return;
                }
                break;
        case 5://lillim
                printf("Lillim: Why don't we have a fun time together <3\n");
                printf("What will you say?\n1.Ignore her\t2.Ante up\n");
                scanf("%d", &choice);
                if(choice==2){
                    printf("Lillim: BWAHAHAHA! You're funny human! Hey, can demons be beautiful?\n1.Beauty is in the eyes of the beholder\t2.No.");
                    scanf("%d", &choice);
                    if(choice==2){
                        printf("Lillim: *chuckle*. Let me change your mind.\n");
                        break;
                    }
                    else{
                        getchar();
                        printf("Lillim: If it's a no, be honest about it!\n%s fled!", enemy[demon]);
                        getchar();
                        return;
                    }
                }
                else{
                        getchar();
                        printf("Lillim: You stupid jerk!\n%s fled!", enemy[demon]);
                        getchar();
                        return;
                }
                break;
        case 6://Leanan Sidhe
               printf("Leanan Sidhe: What does a child want with me?\n");
                printf("What will you say?\n1.I need your power\t2.I need your wisdom\n");
                scanf("%d", &choice);
                if(choice==1){
                    printf("Leanan Sidhe: Then become my slave!\n1.Resist her gaze\t2.Glare in her eyes\n");
                    scanf("%d", &choice);
                    if(choice==2){
                        printf("Leanan Sidhe: What? It seems my abilities don't affect you. You're strong.\n");
                        break;
                    }
                    else{
                        getchar();
                        printf("Leanan Sidhe: How predictable\n%s fled!", enemy[demon]);
                        getchar();
                        return;
                    }
                }
                else{
                        getchar();
                        printf("Leanan Sidhe: How dare you call me old!\n%s fled!", enemy[demon]);
                        getchar();
                        return;
                }
                break;
        case 7://Macabre
                printf("Macabre: Tell me, do you fear death?\n");
                printf("What will you say?\n1.Yes.\t2.No.\n");
                scanf("%d", &choice);
                if(choice==1){
                    printf("Macabre: Your affirmation speaks volumes to me! Yes! Dance with me!\n");
                    if(party_stats[0][2]>=3){
                        printf("Macabre: You are full of vitality and spirit! Embrace it with me!\n");
                        break;
                    }
                    else{
                        getchar();
                        printf("Macabre: Are you sure  you are living your life? Dont waste such a thing!\n%s fled!", enemy[demon]);
                        getchar();
                        return;
                    }
                }
                else{
                        getchar();
                        printf("Macabre: Your body tells me that you lie. Begone!\n%s fled!", enemy[demon]);
                        getchar();
                        return;
                }
                break;
        case 8://Momounofu
                printf("Momounofu: Tell me young warrior, are you strong?\n");
                printf("What will you say?\n1.I am strong\t2.I am weak\n");
                scanf("%d", &choice);
                if(choice==2){
                    printf("Momounofu: It takes courage to admit one's own weakness. How will you get stronger?\n1.With my own hands\t2.Using others\n");
                    scanf("%d", &choice);
                    if(choice==2){
                        printf("Momounofu: Yes! How can you improve if no one can help you? Let me show you the ways of the warrior!\n");
                        break;
                    }
                    else{
                        getchar();
                        printf("Momounofu: A weakling will remain a weakling!\n%s fled!", enemy[demon]);
                        getchar();
                        return;
                    }
                }
                else{
                        getchar();
                        printf("Momounofu: Don't get cocky!\n%s fled!", enemy[demon]);
                        getchar();
                        return;
                }
                break;
        case 9://Ose
                printf("Ose: What are you looking at kid?\n");
                printf("What will you say?\n1.I am looking at you!\t2.A corpse\n");
                scanf("%d", &choice);
                if(choice==2){
                    printf("Ose: Oh, a fighter, eh? Let's see who is stronger!\n1.Laugh\t2.Battle stance");
                    scanf("%d", &choice);
                    if(choice==1){
                        printf("Ose: What an interesting kid! Tell you what, I'll join you for humoring me!\n");
                        break;
                    }
                    else{
                        getchar();
                        printf("Ose: This kid is crazy!\n%s fled!", enemy[demon]);
                        getchar();
                        return;
                    }
                }
                else{
                        getchar();
                        printf("Ose: You think that's gonna threaten me?%s fled!", enemy[demon]);
                        getchar();
                        return;
                }
                break;
    }
    for(int i=1;i<5;i++){
        if(party[i]=='\0'){
            getchar();
            printf("\n%s joined your party!\n", enemy[demon]);
            getchar();
            space--;
            party[i]=enemy[demon];
            for(int j=0;j<7;j++){
                party_stats[i][j]=EnemyStats[demon][j];
            }
            for(int k=0;k<10;k++){
                party_skills[i][k]=EnemySkills[demon][k];
            }
            return;
        }
    }
    if(space==4){
        getchar();
        printf("Can not recruit %s, COMP space is full!\n", enemy[demon]);
        getchar();
        return;
    }
}


void SMT_battle(char *enemy[11], int demon, int EnemyStats[11][7], char *skills[10], int skillcost[10], int EnemySkills[11][10], int taru, int raku){//defend, taru, and raku aren't implemented
    int skill, str, mag, def, hp, mp, ability=9, turn=0, media=0, healto, flee;
    float defend[5]={0,0,0,0,0};
    float DEFEND=0;
    char magic, command;
    hp=EnemyStats[demon][3];
    printf("Party\t\tHP\tMP\n");
    for(int i=0;i<5;i++){
        if(party[i]!='\0'){
            if(strlen(party[i])>=8){
                    printf("%s\t%d\t%d\n", party[i], party_stats[i][3], party_stats[i][4]);
                    continue;
            } 
            printf("%s\t\t%d\t%d", party[i], party_stats[i][3], party_stats[i][4]);
        }
        printf("\n");
    }
    for(int member=0; party[member]!='\0' && member<5; member++){
        SELECTION:
        str= party_stats[member][0];//member is whoever in the party is attacking
        mag= party_stats[member][1];
        def= EnemyStats[demon][2];
        hp= EnemyStats[demon][3];
        printf("What will %s do? Normal Attack(a)\tUse a skill(s)\tDefend\tFlee(f)\n", party[member]);
        scanf(" %c", &command);
        switch(command){
            case 'a':
            case 'A':
        	    skill=0;
        	    getchar();
        	    printf("%s used %s!\n", party[member], skills[skill]);
        	    getchar();
                EnemyStats[demon][3]=SMT_damage(str, mag, hp, def, skill, taru, raku, DEFEND, turn);//<- takes in the attacker's str and the command
                break;
            case 's':
            case 'S':
                printf("What skill will you use? (press s for slash, m for media etc)\n");
                for(int i=1; i<10; i++){
                    if(party_skills[member][i]!=0){
                        printf(" %s,", skills[i]);
                        ability--;
                    }
                }
                printf("\n");
                if(ability==9){
                    printf("\nThere are no skills available!\n");
                    goto SELECTION;
                }
                scanf(" %c", &magic);
                switch(magic){
                    case 's':
                    case 'S':
                            if(party_skills[member][1]!=1){
                                printf("skill not learned!\n");
                                goto SELECTION; 
                            }
                            if(party_stats[member][4]>skillcost[1]){
                                party_stats[member][4]-=3;
                                skill=1;
                                getchar();
                                printf("%s used %s\n", party[member], skills[skill]);
                                getchar();
                                EnemyStats[demon][3]=SMT_damage(str, mag, hp, def, skill, taru, raku, DEFEND, turn);
                            }
                            else{
                                printf("Not enough mp!\n");
                                goto SELECTION;
                            }
                            break;
                    case 'a':
                    case 'A':
                            if(party_skills[member][4]!=1){
                                printf("skill not learned!\n");
                                goto SELECTION; 
                            }
                            if(party_stats[member][4]>skillcost[4]){
                                party_stats[member][4]-=3;
                                skill=4;
                                getchar();
                                printf("%s used %s\n", party[member], skills[skill]);
                                getchar();
                                EnemyStats[demon][3]=SMT_damage(str, mag, hp, def, skill, taru, raku, DEFEND, turn);
                            }
                            else{
                                printf("Not enough mp!\n");
                                goto SELECTION;
                            }
                            break;
                    case 'b':
                    case 'B':
                            if(party_skills[member][5]!=1){
                                printf("skill not learned!\n");
                                goto SELECTION; 
                            }
                           if(party_stats[member][4]>skillcost[5]){
                                party_stats[member][4]-=3;
                                skill=5;
                                getchar();
                                printf("%s used %s\n", party[member], skills[skill]);
                                getchar();
                                EnemyStats[demon][3]=SMT_damage(str, mag, hp, def, skill, taru, raku, DEFEND, turn);
                            }
                            else{
                                printf("Not enough mp!\n");
                                goto SELECTION;
                            }
                            break;
                    case 'd':
                    case 'D'://we need healing implementation
                            if(party_skills[member][6]!=1){
                                printf("skill not learned!\n");
                                goto SELECTION; 
                            }
                           if(party_stats[member][4]>skillcost[6]){
                                party_stats[member][4]-=2;
                                printf("Who will you use it on? (enter number)\n");
                                for(int i=0;i<5;i++){
                                    if(party[i]!='\0')
                                    printf("%d. %s ", i+1, party[i]);
                                }
                                HEALSELECT:
                                scanf("%d", &healto);
                                if(party[healto-1]=='\0'){
                                    goto HEALSELECT;
                                }    
                                SMT_heal(enemy, media, mag, taru, healto);
                            }
                            else{
                                printf("Not enough mp!\n");
                                goto SELECTION;
                            }
                            break;
                    case 'm':
                    case 'M':
                            if(party_skills[member][7]!=1){
                                printf("skill not learned!\n");
                                goto SELECTION; 
                            }
                            if(party_stats[member][4]>skillcost[7]){
                                party_stats[member][4]-=6;
                                media=1;
                                for(healto=1;healto<6;healto++){
                                    SMT_heal(enemy, media, mag, taru, healto);
                                }
                            }
                            else{
                                printf("Not enough mp!\n");
                                goto SELECTION;
                            };
                            break;
                    case 't':
                    case 'T':
                            if(party_skills[member][8]!=1){
                                printf("skill not learned!\n");
                                goto SELECTION; 
                            }
                           if(party_stats[member][4]>skillcost[8]){
                               if(taru==3){
                                   printf("Limit reached!\n");
                                   goto SELECTION;
                               }
                                party_stats[member][4]-=3;
                                getchar();
                                printf("%s used raised the party's offense!\n", party[member]);
                                getchar();
                                taru+=1;//include a thingy that says taru cant exceed 3
                            }
                            else{
                                printf("Not enough mp!\n");
                                goto SELECTION;
                            }
                            break;
                    case 'r':
                    case 'R':
                            if(party_skills[member][9]!=1){
                                printf("skill not learned!\n");
                                goto SELECTION; 
                            }
                            if(party_stats[member][4]>skillcost[9]){
                                if(taru==3){
                                   printf("Limit reached!\n");
                                   goto SELECTION;
                                }
                                party_stats[member][4]-=3;
                                raku+=1;
                                getchar();
                                printf("%s raised the party's defense!\n", party[member]);
                                getchar();
                            }
                            else{
                                printf("Not enough mp!\n");
                                goto SELECTION;
                            }
                            break;
                    default:
                            goto SELECTION;
                            break;
                }
                break;    
                
            case 'd':
            case 'D':
                    defend[member]=.50;
                    break;
            case 'f':
            case 'F':
                    flee=SMT_flee(demon);
                    if(flee==1)
                        return;
                    else
                        break;
            default: 
                    goto SELECTION;
                    break;
        }  
        if(EnemyStats[demon][3]<=0){
            getchar();
            printf("%s defeated!\nYou gained %d experience and %d macca\n", enemy[demon], EnemyStats[demon][5], EnemyStats[demon][6]);
            getchar();
            party_stats[0][6]+=EnemyStats[demon][5];
            macca+=EnemyStats[demon][6];
            SMT_player_stats();
            return;
        }
    }
    SMT_enemy(enemy, demon, EnemyStats, skills, skillcost, EnemySkills, taru, raku, defend);
}


void SMT_heal(char *enemy[11], int media, int mag, int taru, int healto){
//this function is a mess
    int hp, heal;
    if(healto==1){
        hp=50+5*party_stats[0][5]+5*party_stats[0][2];
        goto healcalc;
    }
    for(int i=0;i<10;i++){
        if(party[healto-1]==enemy[i]){
            switch(i){
                case 0: hp=60;
                break;
                case 1: hp=70;
                        break;
                case 2: hp=75;
                        break;
                case 3: hp=70;
                        break;
                case 4: hp=70;
                        break;
                case 5: hp=65;
                        break;
                case 6: hp=70;
                        break;
                case 7: hp=70;
                        break;
                case 8: hp=90;
                        break;
                case 9: hp=80;
                        break;
            }
            healcalc:
            heal=50*(1+.05*mag)*pow(1.2,taru);
            if(heal>(hp-party_stats[healto-1][3])){
                if(healto==1){
                    printf("%s was healed for %d health!\n", party[0], hp-party_stats[0][3]);
                    getchar();
                    party_stats[0][3]=hp;
                    break;
                }
                getchar();
                printf("%s was healed for %d health!\n", party[healto-1], hp - party_stats[healto-1][3]);
                getchar();
                party_stats[healto-1][3]=hp;
                break;
            }
            printf("%s was healed for %d health!\n", party[healto-1], heal);
            getchar();
            party[healto-1]+=heal;
            break;
        }
    }
}


int SMT_damage(int str, int mag, int hp, int def, int skill, int taru, int raku, float DEFEND, int turn){//this is repeated twice for some reason
    int damage;
    switch(skill){
        case 0:
                if(turn==0){
                    damage=(5*str+equipment[0])*(1+.05*str)*(1-.05*def)*pow(1.2, taru);//raku isn't include since this is player induced. enemies don't buff themselves
                }
                else{
                    damage=(5*str)*(1+.05*str)*(1-.05*def)*(1-DEFEND)*pow(.85, raku);//this is the default, this comes from enemy to player
                }
                break;
        case 1:
                if(turn==0){
                    damage=(5*str+equipment[0])*pow(1+.05*str, 2)*(1-.05*def)*pow(1.2,taru);
                }
                else{
                    damage=(5*str)*pow(1+.05*str, 2)*(1-.05*def)*(1-DEFEND)*pow(.85, raku);
                }
                break;
        case 2:
                damage=(5*str)*pow(1+.05*str, 2)*(1-.05*def)*(1-DEFEND)*pow(.85, raku);//CU exclusive skill. party wiper
                break;
        case 3:
                    damage=80*(1+.05*mag)*(1-.05*def)*(1-DEFEND)*pow(.85, raku);//cu exclusive skill
                break;
        case 4:
        case 5:
                if(turn==0){
                damage=50*(1+.05*mag)*(1-.05*def)*pow(1.2, taru);
                }
                else{
                    damage=50*(1+.05*mag)*(1-.05*def)*(1-DEFEND)*pow(.85, raku);
                }
                break;
    }
    if(skill==2){
        printf("It dealt %d damage ", damage);
    }
    else{
        printf("It dealt %d damage!\n", damage);
    }
    hp-=damage;
    return (hp);
}

void SMT_enemy(char *enemy[11], int demon, int EnemyStats[11][7], char *skills[10], int skillcost[10], int EnemySkills[11][10], int taru, int raku, float defend[5]){//this should probably be the enemy turn
    int move, count=1, hp, hpcurr, str, mag, def, target, heal, turn=1;
    float DEFEND;
    str=EnemyStats[demon][0];
    mag=EnemyStats[demon][1];
    for(int i=0;i<count;i++){
        move=rand()%10;
        //printf("move %d\n", move);
        if(EnemySkills[demon][move]==1){
            if(EnemyStats[demon][4]>=skillcost[move]){
                if(move==0||move==1||move==2||move==3||move==4||move==5){//all offensive moves deathbound should be a didff thing
                    for(int j=0; j<count;j++){
                        if(move==2){
                            printf("%s used %s on the party!\n", enemy[demon], skills[move]);
                            getchar();
                            for(int k=0;k<5;k++){
                                if(party[k]!='\0'){
                                    hp=party_stats[k][3];
                                    def=party_stats[k][2];
                                    DEFEND=defend[k];
                                    EnemyStats[demon][4]-=skillcost[move];
                                    getchar();
                                    party_stats[k][3]=SMT_damage(str, mag, hp, def, move, taru, raku, DEFEND, turn);
                                    printf("to %s!\n", party[k]);
                                    getchar();
                                    SMT_GameOver(k);
                                }
                            }
                            goto ENEMYTURNEND;
                        }
                        
                        target=rand()%5;
                        if(party[target]!='\0'){//any offense skill
                            hp=party_stats[target][3];
                            def=party_stats[target][2];
                            DEFEND=defend[target];
                            EnemyStats[demon][4]-=skillcost[move];
                            getchar();
                            printf("%s used %s on %s!\n", enemy[demon], skills[move], party[target]);
                            getchar();
                            party_stats[target][3]=SMT_damage(str, mag, hp, def, move, taru, raku, DEFEND, turn);
                            getchar();
                            SMT_GameOver(target);
                            goto ENEMYTURNEND;
                        }
                    count++;
                    }
                }    
                EnemyStats[demon][4]-=skillcost[move];
                if(move==6||move==7){
                    switch(demon){
                        case 0:
                                hp=60;
                                break;
                        case 3:
                                hp=70;
                                break;
                        case 4:
                                hp=70;
                                break;
                        case 5:
                                hp=65;
                                break;
                        case 6:
                                hp=70;
                                break;
                    }   
                    heal=20*(1+.05*mag);//random encounter heal is actually a lot so I nerfed enemy healing so that they actually die
                    if(heal>(hp-EnemyStats[demon][3])){
                        heal=hp-EnemyStats[demon][3];
                    }
                    EnemyStats[demon][3]+=heal;
                    getchar();
                    printf("%s used %s!\n", enemy[demon], skills[move]);
                    getchar();
                    printf("It healed for %d damage!\n", heal);
                    getchar();
                    goto ENEMYTURNEND;
                }
                if(move==8||move==9){
                    getchar();
                    printf("%s stood there and did nothing!\n", enemy[demon]);
                    getchar();
                    goto ENEMYTURNEND;
                }
            }
        }
        count++;
    }
    ENEMYTURNEND:
    printf("\n\n\n");
    SMT_battle(enemy, demon, EnemyStats, skills, skillcost, EnemySkills, taru, raku);
}

void SMT_GameOver(int member){
    if(party_stats[member][3]<=0){//death of a party member
        getchar();
        printf("%s died!", party[member]);
        getchar();
        for(int i=member;i<5;i++){
            if(party[i]=='\0')
                break;
            if(i==4)
                party[i]='\0';
            party[i]=party[i+1];
            for(int j=0;j<7;j++){
                party_stats[i][j]=party_stats[i+1][j];
            }
            for(int k=0;k<10;k++){
                party_skills[i][k]=party_skills[i+1][k];
            }
        }
        if(member==0){//game over sequence
            getchar();
            printf("The comfort of death will come, for  men and demon alike...");
            getchar();
            printf("by the guidance of the Great Will\n");
            getchar();            
            printf("Game Over");
            getchar();
            main();
        }
    }
}