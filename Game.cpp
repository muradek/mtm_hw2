//
// Created by Yousef  Abuakell on 29/06/2020.
//

#include "Game.h"
#include <string>
#include "Soldier.h"
#include "Medic.h"
#include "Sniper.h"
#include <memory>
#include "Character.h"
#include "Exceptions.h"
#include "Auxiliaries.h"

namespace mtm {

    Game::Game(int height, int width) :Board(Dimensions(height <= 0 ? throw IllegalArgument() : height, width <= 0 ? throw IllegalArgument() : width), NULL) {
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                Board(i, j) = NULL;
    } // we initalize the board with all null

    Game::Game(const Game& other) : Board(other.Board) { // copy constructor
        int rows = other.Board.height();
        int cols = other.Board.width();

        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                if (Board(i, j)) {
                    std::shared_ptr<Character> pointer(Board(i,j)->clone());
                    Board(i, j) = pointer;
                }else{
                    Board(i,j)==NULL;
                }
    }

    Game& Game::operator=(const Game& Game) { // assignment operator
        int rows = Game.Board.height();
        int cols = Game.Board.width();

            this->Board = Game.Board;
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                if (Game.Board(i, j)) {
                    std::shared_ptr<Character> pointer(Game.Board(i,j)->clone());
                    Board(i, j) = pointer;
                }else{
                    Board(i,j)==NULL;
                }
            return *this;
        }
    void Game::attack(const mtm::GridPoint& src_coordinates, const mtm::GridPoint& dst_coordinates) {
        if(src_coordinates.row<0 || src_coordinates.col<0 || dst_coordinates.row<0 || dst_coordinates.col<0){
            throw IllegalCell();
        }
        if(src_coordinates.row>Board.height()-1 || src_coordinates.col>Board.width()-1 || dst_coordinates.row>Board.height()-1 || dst_coordinates.col>Board.width()-1){
            throw IllegalCell();
        }

        if(Board(src_coordinates.row,src_coordinates.col) == NULL ){
            throw CellEmpty();
        }
        if (Board(src_coordinates.row, src_coordinates.col)->LegalAttack(src_coordinates, dst_coordinates, Board)) {
            Board(src_coordinates.row, src_coordinates.col)->attack(src_coordinates, dst_coordinates, Board);
        } // we check the Errors First, then we go the right function depends of the Type of the character
    }
    std::shared_ptr<Character> Game::makeCharacter(CharacterType type, Team team,
                                                   units_t health, units_t ammo, units_t range, units_t power) {

        if (ammo < 0 || power < 0 || health <= 0 || range < 0) {
            throw IllegalArgument();
        }
        std::shared_ptr<Character> ptr_soldier(new Soldier(health, ammo, range, power, team, type));
        std::shared_ptr<Character> ptr_Medic(new Medic(health, ammo, range, power, team, type));
        std::shared_ptr<Character> ptr_sniper(new Sniper(health, ammo, range, power, team, type));
        if (type == CharacterType::SOLDIER) {
            return ptr_soldier;
        }
        if (type == CharacterType::MEDIC) {
            return ptr_Medic;
        }

        if (type == CharacterType::SNIPER) {
            return ptr_sniper;
        }
        return NULL;

    }

    void Game::addCharacter(const GridPoint& coordinates, std::shared_ptr<Character> character) {
        int row = coordinates.row;
        int col = coordinates.col;

        if (row >= Board.height() || col >= Board.width() || row < 0 || col < 0) {

            throw IllegalCell();
        }
        if (Board(row, col) != nullptr) {
            throw CellOccupied();
        }
        std::shared_ptr<Character> ptr(character->clone());
        Board(row, col) = ptr;
    }
    void Game::move(const GridPoint& src_coordinates, const GridPoint& dst_coordinates) {
        if(src_coordinates.row < 0 || src_coordinates.col < 0 || dst_coordinates.row<0 || dst_coordinates.col<0){
            throw IllegalCell();
        }
        if(src_coordinates.row>Board.height()-1 || src_coordinates.col>Board.width()-1 || dst_coordinates.row>Board.height()-1 || dst_coordinates.col>Board.width()-1){
            throw IllegalCell();
        }
        if(Board(src_coordinates.row,src_coordinates.col) == NULL){
            throw CellEmpty();
        }
        Board(src_coordinates.row, src_coordinates.col)->move(src_coordinates, dst_coordinates, Board);
    }
    void Game::reload(const mtm::GridPoint& coordinates) {
        if (coordinates.row < 0 || coordinates.col <0 || coordinates.row > Board.height() || coordinates.col > Board.width()) {
            throw IllegalCell();
        }
        if (Board(coordinates.row, coordinates.col) == nullptr) {
            throw CellEmpty();
        }
        Board(coordinates.row, coordinates.col)->reload();
    }


    bool Game::isOver(Team* winningTeam) const{

        bool Current_cpp = false;
        bool Current_python = false;
        for(typename mtm::Matrix<std::shared_ptr<Character>>::const_iterator it = Board.begin(); it != Board.end(); ++it){
            if(*it == nullptr){
                continue;
            }
            if ((*it)->GetTeam() == POWERLIFTERS){
                Current_cpp = true;
            }
            else {
                Current_python = true;
            }
        }

        if((Current_cpp && Current_python) || (!Current_cpp && !Current_python)){
            return false;
        }
        if(Current_cpp && winningTeam != NULL){
            *winningTeam = POWERLIFTERS;
            return true;
        }
        else if(Current_python && winningTeam!=NULL){
            *winningTeam = CROSSFITTERS;
        }
        if(winningTeam==NULL){
           return true;
        }
        return true;
    }
}



