//
// Created by Yousef  Abuakell on 29/06/2020.
//

#ifndef HW3MTM_GAME_H
#define HW3MTM_GAME_H

#include "Auxiliaries.h"
#include <cassert>
#include <ostream>
#include <iostream>
#include "Matrix.h"
#include "Character.h"
#include <memory>
#include "Exceptions.h"
#include <stdbool.h>
#include "string.h"

namespace mtm {

    class Game {
        Matrix<std::shared_ptr<Character>> Board;
    public:
        explicit Game(int width, int height);
        ~Game() = default;
        Game(const Game& other);
        Game& operator=(const Game& other);
        void move(const GridPoint& src_coordinates, const GridPoint& dst_coordinates);
        void reload(const GridPoint& coordinates);
        static std::shared_ptr<Character> makeCharacter(CharacterType type, Team team,
                                                        units_t health, units_t ammo, units_t range, units_t power);
        void attack(const GridPoint& src_coordinates, const GridPoint& dst_coordinates);
        void addCharacter(const GridPoint& coordinates, std::shared_ptr<Character> character);
        friend std::ostream& operator<<(std::ostream& os, const Game& game) {
            int rows = game.Board.height();
            int cols = game.Board.width();
            int size = rows * cols;
            char* NewMatrix = new char [rows*cols];
            for (int m = 0; m < rows; m++) {
                for (int n = 0; n < cols; n++) {
                    if (game.Board(m, n) == nullptr)
                        NewMatrix[cols * m + n] = ' ';
                    else
                    {
                        char letter = game.Board(m, n)->GetLetter();
                        NewMatrix[cols * m + n] = letter;
                    }

                }
            }
            char* end = &NewMatrix[size - 1];
            printGameBoard(os, NewMatrix, end+1, cols);
            delete[] NewMatrix;
            return os;
        }

        bool isOver(Team* winningTeam = NULL) const;
    };

}
#endif //HW3MTM_GAME_H
