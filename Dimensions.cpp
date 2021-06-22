
#include "Dimensions.h"
mtm::Dimensions::Dimensions( int row_t,  int col_t) : row(row_t), col(col_t) {}

bool mtm::Dimensions::operator==(const Dimensions& other) const {
    return (row==other.row) and (col==other.col);
}

bool mtm::Dimensions::operator!=(const Dimensions& other) const {
    return not(*this==other);
}

int mtm::Dimensions::getRow() const {
    return row;
}

int mtm::Dimensions::getCol() const {
    return col;
}

