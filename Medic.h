//
// Created by Yousef  Abuakell on 01/07/2020.
//

#ifndef HW3MTM_MEDIC_H
#define HW3MTM_MEDIC_H
#include <cassert>
#include <ostream>
#include <iostream>
#include "Character.h"
#include "Auxiliaries.h"

namespace mtm {
    class Medic : public Character {
    public:
        static const int MAX_MOVES_MEDIC = 5;
        static const int RELOAD_MEDIC = 5;

        std::shared_ptr<Character> clone() const override;

        Medic(units_t health, units_t ammo, units_t range, units_t power, Team team, CharacterType type):Character(health,ammo,range,power,team,type){};

        ~Medic() override = default;

        Medic(const Medic &Medic) = default;

        void CheckHonesty(Matrix<std::shared_ptr<Character>> &Board) override;

        bool LegalMove(const GridPoint &source, const GridPoint &Destinaton,
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
                return 'm';
            }
            return 'M';
        }

    };
}
#endif //HW3MTM_MEDIC_H
