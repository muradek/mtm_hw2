//
// Created by Yousef  Abuakell on 17/06/2021.
//

//
// Created by Yousef  Abuakell on 29/06/2020.
//
#include <cassert>
#include <string>
using std::ostream;
using std::iostream;
#include "Soldier.h"
#include "Character.h"
namespace mtm {

    void Soldier::reload()  {
        this->ammo += RELOAD_SOLDIER;
    }

    std::shared_ptr<Character> Soldier::clone() const {
        return std::shared_ptr<Soldier>(new Soldier(*this));
    }
    bool Soldier::LegalMove(const GridPoint& source, const GridPoint& Destination,Matrix<std::shared_ptr<Character>> &Board) {
        if(source.row < 0 || source.col < 0 || Destination.row<0 || Destination.col<0){
            throw IllegalCell();
        }
        if(Board(source.row,source.col)== NULL){
            throw CellEmpty();
        }
        if(GridPoint::distance(source,Destination)> MAX_MOVE_SOLDIER){
            throw MoveTooFar();
        }
        if(Board(Destination.row,Destination.col)!= NULL){
            throw CellOccupied();
        }
        return true;
    }

    void Soldier::move(const mtm::GridPoint &source, const mtm::GridPoint &Destination,
                       Matrix<std::shared_ptr<Character>> &Board) {
        if(LegalMove(source,Destination,Board)){
            Board(Destination.row,Destination.col) = Board(source.row,source.col);
            Board(source.row,source.col) = NULL;
        }
    }
    bool Soldier::LegalAttack(const GridPoint &Current, const GridPoint &Destination,Matrix<std::shared_ptr<Character>> &Board)
    {   if(Current.row < 0 || Current.col < 0 || Destination.row<0 || Destination.col<0){
            throw IllegalCell();
        }
        if(GridPoint::distance(Current,Destination) > range){
            throw OutOfRange();
        }

        if(Board(Current.row,Current.col)->GetAmmo() <= 0) {
            throw OutOfAmmo();
        }
        if(Current.row!=Destination.row && Current.col!=Destination.col){
            throw IllegalTarget();
        }

        return true;

    }
    void Soldier::CheckHonesty(mtm::Matrix<std::shared_ptr<Character>> &Board) {
        for(int i =0 ; i< Board.height();i++) {
            for (int j = 0; j < Board.width(); j++) {
                if (Board(i, j) != nullptr) {
                    if (Board(i, j)->GetHealth() <= 0) {
                        Board(i, j) = NULL;
                    }
                }
            }
        }
    }
    void Soldier::attack(const mtm::GridPoint &source, const mtm::GridPoint &Destination,
                         mtm::Matrix<std::shared_ptr<Character>> &Board) {

        if(LegalAttack(source,Destination,Board)){
            ammo--;
            if(Board(Destination.row,Destination.col)!= nullptr){
                if(Board(Destination.row,Destination.col)->GetTeam() != team){
                    Board(Destination.row,Destination.col)->SetHealth(power);
                }
            }
            int newRange ;
            int CurrentPower = Board(source.row,source.col)->GetPower();
            int NewPower ;
            if(range % 3){
                newRange = (range / 3 )+1;
            }
            else {
                newRange = range / 3 ;
            }
            if(power%2){
                NewPower = (CurrentPower /2)+1;
            }
            else {
                NewPower = CurrentPower/2;
            }
            Team CurrentTeam = Board(source.row,source.col)->GetTeam();
            for(int i =0 ; i<Board.height();i++){
                for (int j=0; j<Board.width();j++){
                    if((i == Destination.row && j == Destination.col) || Board(i,j)== nullptr){
                        continue;
                    }
                    else {
                        GridPoint CurrentPoint = GridPoint(i,j);
                        if( GridPoint::distance(CurrentPoint,Destination)<= newRange)
                        {
                            if(Board(i,j)->GetTeam() == CurrentTeam){
                                continue;
                            }
                            else {
                                Board(i, j)->SetHealth(NewPower);
                            }
                        }
                    }
                }
            }
            CheckHonesty(Board);



        }
    }
}

