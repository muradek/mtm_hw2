//
// Created by Yousef  Abuakell on 01/07/2020.
//

#include <string>
using std::ostream;
using std::iostream;

#include "Medic.h"
namespace mtm{
   // this function checks if its a legal move
    bool Medic::LegalMove(const GridPoint& source, const GridPoint& Destination,Matrix<std::shared_ptr<Character>> &Board) {
        if(source.row < 0 || source.col < 0 || Destination.row<0 || Destination.col<0){
            throw IllegalCell();
        }
        if(Board(source.row,source.col)== NULL){
            throw CellEmpty();
        }
        if(GridPoint::distance(source,Destination)> MAX_MOVES_MEDIC){
            throw MoveTooFar();
        }
        if(Board(Destination.row,Destination.col)!= NULL){
            throw CellOccupied();
        }
        return true;
    }
    void Medic::move(const mtm::GridPoint &source, const mtm::GridPoint &Destination,
                     Matrix<std::shared_ptr<Character>> &Board) {
        if(LegalMove(source,Destination,Board)){
            Board(Destination.row,Destination.col) = Board(source.row,source.col);
            Board(source.row,source.col) = NULL;
        }
    }
    std::shared_ptr<Character> Medic::clone() const {
        return std::shared_ptr<Medic>(new Medic(*this));
    } // this funcion checks if its a legal attack
    bool Medic::LegalAttack(const mtm::GridPoint &Current, const mtm::GridPoint &Destination,
                            mtm::Matrix<std::shared_ptr<Character>> &Board) {
        if(Current.row < 0 || Current.col < 0 || Destination.row<0 || Destination.col<0){
            throw IllegalCell();
        }
        if(GridPoint::distance(Current,Destination) > range){
            throw OutOfRange();
        }
        if(Current.row == Destination.row && Current.col == Destination.col){
            throw IllegalTarget();
        }
        if(Board(Current.row,Current.col)->GetAmmo() <= 0 &&Board(Current.row,Current.col)->GetTeam()!=Board(Destination.row,Destination.col)->GetTeam()) {
            throw OutOfAmmo();
        }
        if(Board(Destination.row,Destination.col)== NULL ){
            throw IllegalTarget();
        }

        return true;

    }
    void Medic::CheckHonesty(Matrix<std::shared_ptr<Character>> &Board){ // this function eliminates all the characters with 0 or less health bar
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
    void Medic::attack(const mtm::GridPoint &source, const mtm::GridPoint &Destination,
                       mtm::Matrix<std::shared_ptr<Character>> &Board) {
        if (LegalAttack(source, Destination, Board)) {
            int CurrentPower = Board(source.row, source.col)->GetPower();
            Team CurrentTeam = Board(source.row, source.col)->GetTeam();
            if (Board(Destination.row, Destination.col)->GetTeam() != CurrentTeam) {
                Board(source.row, source.col)->SetAmmo(-1);
                Board(Destination.row, Destination.col)->SetHealth(CurrentPower);

            } else {
                Board(Destination.row, Destination.col)->SetHealth(-(CurrentPower));
            }
            CheckHonesty(Board);
        }
    }
    void Medic::reload() {
        this->ammo += RELOAD_MEDIC;
    }

}
