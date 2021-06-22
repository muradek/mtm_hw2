//
// Created by Yousef  Abuakell on 17/06/2021.
//

//
// Created by Yousef  Abuakell on 01/07/2020.
//

#include <cassert>
#include <string>
using std::ostream;
using std::iostream;
#include "Sniper.h"

namespace mtm {


    void Sniper::reload() {
        this->ammo += RELOAD_SNIPER;
    }
    bool Sniper::LegalMove(const GridPoint& source, const GridPoint& Destination,Matrix<std::shared_ptr<Character>> &Board) {
        if(source.row < 0 || source.col < 0 || Destination.row<0 || Destination.col<0){
            throw IllegalCell();
        }
        if(Board(source.row,source.col)== NULL){
            throw CellEmpty();
        }
        if(GridPoint::distance(source,Destination)> MAX_MOVE_SNIPER){
            throw MoveTooFar();
        }
        if(Board(Destination.row,Destination.col)!= NULL){
            throw CellOccupied();
        }
        return true;
    }
    void Sniper::move(const mtm::GridPoint &source, const mtm::GridPoint &Destination,
                      Matrix<std::shared_ptr<Character>> &Board) {
        if(LegalMove(source,Destination,Board)){
            Board(Destination.row,Destination.col) = Board(source.row,source.col);
            Board(source.row,source.col) = NULL;
        }
    }

    std::shared_ptr<Character> Sniper::clone() const {
        return std::shared_ptr<Sniper>(new Sniper(*this));
    }
    bool Sniper::LegalAttack(const mtm::GridPoint &Current, const mtm::GridPoint &Destination,
                             mtm::Matrix<std::shared_ptr<Character>> &Board) {
        if(Current.row < 0 || Current.col < 0 || Destination.row<0 || Destination.col<0){
            throw IllegalCell();
        }
        if(GridPoint::distance(Current,Destination) > range){
            throw OutOfRange();
        }


        int NewRange;
        if(range % 2){
            NewRange = (range / 2 )+1;
        }
        else {
            NewRange = range / 2 ;
        }
        if(GridPoint::distance(Current,Destination) < NewRange) {
            throw OutOfRange();
        }
        if(Board(Current.row,Current.col)->GetAmmo() <= 0) {
            throw OutOfAmmo();
        }
        if(Board(Destination.row,Destination.col)== nullptr ){
            throw IllegalTarget();
        }

        if(Board(Current.row,Current.col)->GetTeam() == Board(Destination.row,Destination.col)->GetTeam()) {
            throw IllegalTarget();
        }
        return true;

    }
    void Sniper::CheckHonesty(mtm::Matrix<std::shared_ptr<Character>> &Board) {
        for(int i =0 ; i< Board.height();i++){
            for(int j =0 ; j< Board.width();j++){
                if(Board(i,j)!= nullptr){
                    if(Board(i,j)->GetHealth() <= 0){
                        Board(i,j)= NULL;
                    }
                }
            }
        }
    }
    void Sniper::attack(const GridPoint& source, const GridPoint& Destination,Matrix<std::shared_ptr<Character>> &Board) {
        if(LegalAttack(source,Destination,Board)){
            int DoubleDamage;
            int CurretPower = Board(source.row,source.col)->GetPower();
            if(!(Counter%3)){
                DoubleDamage = CurretPower*2;
            }
            else {
                DoubleDamage = CurretPower;
            }
            Counter++;
            ammo--;
            if(Board(Destination.row,Destination.col)!= nullptr){
                Board(Destination.row,Destination.col)->SetHealth(DoubleDamage);
            }
            CheckHonesty(Board);
        }

    }

}
