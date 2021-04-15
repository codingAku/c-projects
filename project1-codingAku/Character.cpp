#include "Character.h"
#include <list>
#include <string>
#include <iostream>
//character constructor
Character::Character(string _name, string _type, int _attack, int _defense, int _remainingHealth, int _nMaxRounds) {
this->name = _name;
this->type = _type;
this->attack = _attack;
this->defense = _defense;
this->remainingHealth = _remainingHealth;
this->nMaxRounds = _nMaxRounds;
this->healthHistory = new int[_nMaxRounds+1];
this->nRoundsSinceSpecial = 0;
this->isAlive = true;

}

Character::Character(const Character& character) {
this->name = character.name;
this->type = character.type;
this->attack = character.attack;
this->defense = character.defense;
this->remainingHealth = character.remainingHealth;
this->nMaxRounds = character.nMaxRounds;
this->nRoundsSinceSpecial = character.nRoundsSinceSpecial;
this->healthHistory = new int[character.nMaxRounds+1];
this->isAlive = character.isAlive;
for (int i = 0; i < character.nMaxRounds+1; i++)
{
this->healthHistory[i] = character.healthHistory[i];
}



}

Character& Character::operator=(const Character& character) {
if (this->healthHistory != NULL)
{
delete[] this->healthHistory;
}
this->name = character.name;
this->type = character.type;
this->attack = character.attack;
this->defense = character.defense;
this->remainingHealth = character.remainingHealth;
this->nMaxRounds = character.nMaxRounds;
this->isAlive = character.isAlive;
this->nRoundsSinceSpecial = character.nRoundsSinceSpecial;
this->healthHistory = new int[character.nMaxRounds+1];
for (int i = 0; i < character.nMaxRounds+1; i++)
{
this->healthHistory[i] = character.healthHistory[i];
}
return *this;

}

bool Character::operator<(const Character& other) {
int i = 0;
while (other.name[i] == this->name[i])
{
i++;
}
if (other.name[i] > this->name[i])
{
return true;
}
else if (other.name[i] < this->name[i]) {
return false;
}

}

Character::~Character() {
if (this->healthHistory != NULL)
{
delete[] this->healthHistory;
}

}