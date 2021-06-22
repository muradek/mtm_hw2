#include <iostream>
#include <string>

#include <cmath>
namespace mtm {

// this class refers to the dimensions of the matrix we are building ( the Board of the game)
    class Dimensions {
        int row, col;
    public:
        Dimensions(int row_t, int col_t);

        bool operator==(const Dimensions &other) const;

        bool operator!=(const Dimensions &other) const;

        int getRow() const;

        int getCol() const;
    };

}