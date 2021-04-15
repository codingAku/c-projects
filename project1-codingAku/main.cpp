#include "Character.h"
#include <string>
#include <iostream>
#include <fstream>


using namespace std;

void updateHealthHistory(Character* community1, Character* community2, int index)
{
    for (int i = 0; i < 5; i++)
    {
        community1[i].healthHistory[index] = community1[i].remainingHealth;
        community2[i].healthHistory[index] = community2[i].remainingHealth;
    }
}
void updateSpecialRound(Character* community1, Character* community2)
{
    for (int i = 0; i < 5; i++) {
        community1[i].nRoundsSinceSpecial++;
        community2[i].nRoundsSinceSpecial++;
    }
}

Character* getCharacter(string name, Character* community)
{
    for (int i = 0; i < 5; i++)
    {
        if (community[i].name == name)
        {
            return community + i;
        }
    }

}
string nextAlive(Character* current, Character* community1)
{
    Character a = community1[0];
    Character x = community1[1];
    Character c = community1[2];
    Character d = community1[3];
    Character e = community1[4];

    Character community[] = { a, x, c, d, e };
    for (int i = 0; i < 5; i++)
    {
        for (int k = i + 1; k < 5; k++)
        {
            if (community[i] < community[k])
            {
                Character temp = community[i];
                community[i] = community[k];
                community[k] = temp;
            }
        }
    }
    int k;
    for (int i = 0; i < 5; i++)
    {
        if (community[i].name == current->name)
        {
            k = i;
            while (community[k].isAlive == false)
            {
                k--;
                if (k == -1) {
                    k = i;
                    while (community[k].isAlive == false)
                    {
                        k++;
                    }
                }
            }
            break;
        }


    }
    return community[k].name;
 
   

}
void attack(Character* attacker, Character* defender, Character** corpses, int* dead)
{
    int damage = defender->defense - attacker->attack;
    if (damage < 0)
    {
        defender->remainingHealth += damage;
    }
    if (defender->remainingHealth < 0)
    {
     
        defender->remainingHealth = 0;
    }
    if (defender->remainingHealth == 0)
    {
        defender->isAlive = false;
        (*dead)++;
        *corpses = defender;
    }
       
}

Character* getCharacterbyType(string type, Character* community)
{
    for (int i = 0; i < 5; i++)
    {
        if (community[i].type == type)
        {
           
            return community + i;
        }
    }
}
string didWarEnd(Character* community1, Character* community2, int maxRound, int currentRound, bool* flag)
{
   
    if (!getCharacterbyType("Hobbit", community1)->isAlive)
    {
        *flag = true;
        return "Community-1";
    }
    else if (!getCharacterbyType("Hobbit", community2)->isAlive)
    {
        *flag = true;
        return "Community-2";
    }
    else if (!getCharacterbyType("Elves", community1)->isAlive && !getCharacterbyType("Wizards", community1)->isAlive
        && !getCharacterbyType("Men", community1)->isAlive && !getCharacterbyType("Dwarfs", community1)->isAlive)
    {
        *flag = true;
        return "Community-2";
    }
    else if (!getCharacterbyType("Elves", community2)->isAlive && !getCharacterbyType("Wizards", community2)->isAlive
        && !getCharacterbyType("Men", community2)->isAlive && !getCharacterbyType("Dwarfs", community2)->isAlive)
    {
        *flag = true;
        return "Community-1";
    }
    else if (currentRound == maxRound)
    {
         *flag = true;
         return "Draw";
    }
    else
    {
        return "dewam";
    }

}

int main(int argc, char* argv[]) {


   

    ifstream reader(argv[1]);
    string info = "";
    int numOfRounds=0;
    int numOfCasualties = 0;
    int numOfMaxRounds;
    bool warEnds = false;


    reader >> info;
    numOfMaxRounds = stoi(info);

    info = "";

    Character c11("", "", 0, 0, 0, numOfMaxRounds);
    Character c12("", "", 0, 0, 0, numOfMaxRounds);
    Character c13("", "", 0, 0, 0, numOfMaxRounds);
    Character c14("", "", 0, 0, 0, numOfMaxRounds);
    Character c15("", "", 0, 0, 0, numOfMaxRounds);

    Character c21("", "", 0, 0, 0, numOfMaxRounds);
    Character c22("", "", 0, 0, 0, numOfMaxRounds);
    Character c23("", "", 0, 0, 0, numOfMaxRounds);
    Character c24("", "", 0, 0, 0, numOfMaxRounds);
    Character c25("", "", 0, 0, 0, numOfMaxRounds);
   

    Character community1[] = { c11, c12, c13, c14, c15 };
    Character community2[] = { c21, c22, c23, c24, c25 };

    for (int k = 0; k < 5; k++)
    {

        for (int i = 0; i < 5; i++)
        {
            switch (i)
            {
            case 0:
                reader >> info;
                community1[k].name = info;
                info = "";
                break;
            case 1:
                reader >> info;
                community1[k].type = info;
                info = "";
                break;
            case 2:
                reader >> info;
                community1[k].attack = stoi(info);
                info = "";
                break;
            case 3:
                reader >> info;
                community1[k].defense = stoi(info);
                info = "";
                break;
            case 4:
                reader >> info;
                community1[k].remainingHealth = stoi(info);
                community1[k].healthHistory[0] = stoi(info);
                info = "";
                break;
            }
           
        }
       
       

    }
   
   
    for (int k = 0; k < 5; k++)
    {

        for (int i = 0; i < 5; i++)
        {
            switch (i)
            {
            case 0:
                reader >> info;
                community2[k].name = info;
                info = "";
                break;
            case 1:
                reader >> info;
                community2[k].type = info;
                info = "";
                break;
            case 2:
                reader >> info;
                community2[k].attack = stoi(info);
                info = "";
                break;
            case 3:
                reader >> info;
                community2[k].defense = stoi(info);
                info = "";
                break;
            case 4:
                reader >> info;
                community2[k].remainingHealth = stoi(info);
                community2[k].healthHistory[0] = stoi(info);
                info = "";
                break;
            }
           
        }
       

    }
   
   

   
    int orderr;
    string attacker = "";
    string defender = "";
    string special = "";
    string winner = "";
    bool finishFlag = false;
    Character* corpse = nullptr;
   
   
S
    while (!finishFlag)
    {
       
        numOfRounds++;
        Character* attacking = nullptr;
        Character* defending = nullptr;
        reader >> attacker;
        orderr = numOfRounds % 2;
     
            switch (order)
            {
               case 1:
                   attacking = community1;
                   defending = community2;
                   break;
               case 0:
                   attacking = community2;
                   defending = community1;
                   break;
            }
            reader >> defender;
            reader >> special;
            if (getCharacter(attacker, attacking)->isAlive == false)
            {
               
                attacker = nextAlive(getCharacter(attacker, attacking), attacking);
               
             
            }
            if (getCharacter(defender, defending)->isAlive == false)
            {

                defender = nextAlive(getCharacter(defender, defending), defending);


            }
            if (special == "NO-SPECIAL")
            {

                attack(getCharacter(attacker, attacking) , getCharacter(defender, defending), &corpse, &numOfCasualties);
               
               
            }
            else if (special == "SPECIAL")
            {
                if (getCharacter(attacker, attacking)->type == "Men" || getCharacter(attacker, attacking)->type == "Hobbit")
                {
                    attack(getCharacter(attacker, attacking), getCharacter(defender, defending), &corpse, &numOfCasualties);
                }
               
                if (getCharacter(attacker, attacking)->type == "Elves")
                {
                    if (getCharacter(attacker, attacking)->nRoundsSinceSpecial > 10)
                    {

                        int add = (int)getCharacter(attacker, attacking)->remainingHealth / 2;
                        getCharacterbyType("Hobbit", attacking)->remainingHealth += add;
                       
                        getCharacter(attacker, attacking)->remainingHealth -= add;
                       
                        attack(getCharacter(attacker, attacking), getCharacter(defender, defending), &corpse, &numOfCasualties);
                     
                        getCharacter(attacker, attacking)->nRoundsSinceSpecial = -1;

                    }
                    else
                    {
                        attack(getCharacter(attacker, attacking), getCharacter(defender, defending), &corpse, &numOfCasualties);
                    }
                }
               
                else if (getCharacter(attacker, attacking)->type == "Dwarfs")
                {
                    if (getCharacter(attacker, attacking)->nRoundsSinceSpecial > 20)
                    {
                        Character dwarfCopy = *getCharacter(attacker, attacking);
                        attack(getCharacter(attacker, attacking), getCharacter(defender, defending), &corpse, &numOfCasualties);
                       
                        attack(&dwarfCopy, getCharacter(defender, defending), &corpse, &numOfCasualties);
                     
                        getCharacter(attacker, attacking)->nRoundsSinceSpecial = -1;
                    }
                    else
                    {
                        attack(getCharacter(attacker, attacking), getCharacter(defender, defending), &corpse, &numOfCasualties);
                    }

                }
                else if (getCharacter(attacker, attacking)->type == "Wizards")
                {
                    if (getCharacter(attacker, attacking)->nRoundsSinceSpecial > 50)
                    {
                       
                        if (corpse == nullptr)
                        {
                            attack(getCharacter(attacker, attacking), getCharacter(defender, defending), &corpse, &numOfCasualties);
                        }
                        else
                        {
                           
                            corpse->remainingHealth = corpse->healthHistory[0];
                            if (corpse->isAlive == false) {
                                corpse->isAlive = true;
                                corpse->nRoundsSinceSpecial = -1;
                                numOfCasualties--;
                            }
                            getCharacter(attacker, attacking)->nRoundsSinceSpecial = -1;
                            attack(getCharacter(attacker, attacking), getCharacter(defender, defending), &corpse, &numOfCasualties);
                        }
                    }
                    else
                    {
                        attack(getCharacter(attacker, attacking), getCharacter(defender, defending), &corpse, &numOfCasualties);
                    }
                }

            }
            updateSpecialRound(attacking, defending);
            updateHealthHistory(community1, community2, numOfRounds);
            winner = didWarEnd(community1, community2, numOfMaxRounds, numOfRounds, &finishFlag);
       
       
    }
    //now print the results of war
    ofstream writer(argv[2]);
    writer << winner << endl;
    writer << numOfRounds << endl;
    writer << numOfCasualties << endl;
    for (int i = 0; i < 5; i++)
    {
        writer << community1[i].name << " ";
        for (int k = 0; k < numOfRounds+1; k++)
        {
            writer<< community1[i].healthHistory[k] << " ";

        }
        writer << endl;
    }
    for (int i = 0; i < 5; i++)
    {
        writer << community2[i].name << " ";
        for (int b = 0; b < numOfRounds+1; b++)
        {
            writer << community2[i].healthHistory[b] << " ";
        }
        writer << endl;
    }

}