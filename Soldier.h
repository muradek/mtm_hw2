//
// Created by Yousef  Abuakell on 29/06/2020.
//

#ifndef HW3MTM_SOLDIER_H
#define HW3MTM_SOLDIER_H
#include <cassert>
#include <ostream>
#include <iostream>
#include "Character.h"
#include "Auxiliaries.h"

namespace mtm {
    class Soldier : public Character {

    public:
        std::shared_ptr<Character> clone() const override ;

        static const units_t MAX_MOVE_SOLDIER = 3;

        static const units_t RELOAD_SOLDIER = 3;

        // constructor for Soldier
        Soldier(units_t health, units_t ammo, units_t range, units_t power,Team team,CharacterType type):Character(health,ammo,range,power,team,type){};

        //destructor for soldier
        ~Soldier() override = default ;

        // this function Eliminates all the characters with 0 or less health
        void CheckHonesty(Matrix<std::shared_ptr<Character>> &Board) override ;

        // this fucntion checks if the move is legal move based on the character type
        bool LegalMove(const GridPoint &source, const GridPoint &Destination, Matrix<std::shared_ptr<Character>> &Board)override ;

        // this funcion makes the attack, it changes the healths and the ammo of every character in the attack based on the type
        void attack(const GridPoint& source, const GridPoint& Destination,Matrix<std::shared_ptr<Character>> &Board) override ;

        // this func moves the curr characther to a destination character, after we check if its a legal move
        void move(const GridPoint& source, const GridPoint& Destination,Matrix<std::shared_ptr<Character>> &Board) override ;


        Soldier(const Soldier& Soldier)=default;
        void reload() override ;

        // this function checks if its a legal attack, based on the character type in this case its soldier
        bool  LegalAttack(const GridPoint& Current,const GridPoint& Destination,Matrix<std::shared_ptr<Character>> &Board) override ;
        char  GetLetter() override{
            if(team == CROSSFITTERS){
                return 's';
            }
            return 'S';
        }


    };
}
#endif //HW3MTM_SOLDIER_H
