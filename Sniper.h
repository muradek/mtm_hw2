//
// Created by Yousef  Abuakell on 01/07/2020.
//

#ifndef HW3MTM_SNIPER_H
#define HW3MTM_SNIPER_H
#include <cassert>
#include <ostream>
#include <iostream>
#include "Character.h"
#include "Auxiliaries.h"

namespace mtm {
    class Sniper : public Character {
        int Counter;
    public:
        std::shared_ptr<Character> clone() const override;

        static const units_t MAX_MOVE_SNIPER = 4;
        static const units_t RELOAD_SNIPER = 2;

        Sniper(units_t health, units_t ammo, units_t range, units_t power, Team team, CharacterType type) : Character(
                health, ammo, range, power, team, type), Counter(1) {};

        ~Sniper() override = default;

        void CheckHonesty(Matrix<std::shared_ptr<Character>> &Board) override;

        Sniper(const Sniper &Sniper) = default;

        bool LegalMove(const GridPoint &source, const GridPoint &Destination,
                       Matrix<std::shared_ptr<Character>> &Board) override;

        void attack(const GridPoint &source, const GridPoint &Destination,
                    Matrix<std::shared_ptr<Character>> &Board) override;

        void reload() override;

        bool LegalAttack(const GridPoint &Current, const GridPoint &Destination,
                         Matrix<std::shared_ptr<Character>> &Board) override;

        void
        move(const GridPoint &source, const GridPoint &Destination, Matrix<std::shared_ptr<Character>> &Board) override;

        char GetLetter() override {
            if (team == CROSSFITTERS) {
                return 'n';
            }
            return 'N';
        }

    };
}

#endif //HW3MTM_SNIPER_H
