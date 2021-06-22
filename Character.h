//
// Created by Yousef  Abuakell on 29/06/2020.
//

#ifndef HW3MTM_CHARACTER_H
#define HW3MTM_CHARACTER_H
#include "Auxiliaries.h"
#include <cassert>
#include <ostream>
#include <iostream>
#include "Matrix.h"
#include "Exceptions.h"
#include <memory>
namespace mtm {
    class Character {
    protected:
        units_t health, ammo, range, power;
        CharacterType type;
        Team team;
    public:
        //Constructor for Character
        Character(units_t health, units_t ammo, units_t range, units_t power, Team team, CharacterType type)
                : health(health), ammo(ammo), range(range), power(power), type(type), team(team) {}

                //Destructor
        virtual ~Character() = default;

        // clone function to clone a pointer
        virtual std::shared_ptr<Character> clone() const = 0;

        //this func checks if its a legal move (Depends of the type)
        virtual bool LegalMove(const GridPoint &source, const GridPoint &Destination,
                               Matrix <std::shared_ptr<Character>> &Board) = 0;

        virtual void reload() = 0;

        // this function does the attack, based on the character type
        virtual void attack(const GridPoint &source, const GridPoint &Destination, Matrix <std::shared_ptr<Character>> &Board) = 0;

        // checks if its a legal attack depends on the type of the character
        virtual bool LegalAttack(const GridPoint &Current, const GridPoint &Destination,
                                 Matrix <std::shared_ptr<Character>> &Board) = 0;

        virtual char GetLetter() = 0;

        //
        virtual void
        move(const GridPoint &source, const GridPoint &Destination, Matrix <std::shared_ptr<Character>> &Board) = 0;

        int GetAmmo() const {
            return ammo;
        }

        // this funcion checks if there is isnt any Characters with 0 health or less, if does, it removes it
        virtual void CheckHonesty(Matrix <std::shared_ptr<Character>> &Board) = 0;


        int GetHealth() const {
            return health;
        }

        Team GetTeam() {
            return team;
        }

        CharacterType getType() {
            return type;
        }

        void SetHealth(const units_t NewHealth) {
            health -= NewHealth;
        }

        void SetAmmo(const int NewAmmo) {
            ammo += NewAmmo;
        };

        units_t GetPower() {
            return power;
        }


    };
}

#endif //HW3MTM_CHARACTER_H
