//
// Created by adan_ on 6/27/2020.
//

#ifndef LASTHW_MATRIX_H
#define LASTHW_MATRIX_H

#include <ostream>
#include <iostream>
#include <cassert>
#include "Auxiliaries.h"
#include "Dimensions.h"
#include "Exceptions.h"
using std::string;
using std::to_string;
namespace mtm {
    template<class T>
    class Matrix {
        Dimensions dim;
        T** matrice;
    public:
        explicit Matrix(const Dimensions &dims, const T &num = T());
        ~Matrix();
        Matrix(const Matrix<T>& matrix);
        static Matrix<T> Diagonal(int dim, T num=T());
        Matrix<T> &operator=(const Matrix &mat);
        Matrix<T> transpose() const;
        Matrix<T> &operator+=(const T num);
        T& operator()(const int row, const int col);
        T& operator()(const int row, const int col) const;
        Matrix<T> operator-() const;
        class AccessIllegalElement;
        class IllegalInitialization;
        class DimensionMismatch;
        void SetValue(int row, int column, T num);
        Matrix<bool> operator==(const T& num);
        Matrix<bool> operator!=(const T& num);
        Matrix<bool> operator<=(const T& num);
        Matrix<bool> operator>=(const T& num);
        Matrix<bool> operator>(const T& num);
        Matrix<bool> operator<(const T& num);
        int width() const{ //The function returns the width of the matrix
            return this->dim.getCol();
        }
        int height()const{ //The function returns the height of the matrix
            return this->dim.getRow();
        }

        int size()const { //The function returns the size of the matrix
            int width = this->dim.getCol();
            int height = this->dim.getRow();
            return height*width;
        }
        template <class condition>
        Matrix<T> apply(condition d)const;
        class iterator;
        iterator begin();
        iterator end();
        class const_iterator;
        const_iterator end() const;
        const_iterator begin() const;
        friend Matrix<T> operator+(const Matrix<T>& mat,const T& num) { //For a type T object, adding the object with a matrix will add the same object to all the elements of the matrix
            // parameters: int num, matrix from type Matrix
            //we suppose that cctor dtor ctor are implemented
            return num+mat;
        }
        friend Matrix<T> operator+( const T& num,const Matrix<T> &mat) { //For a type T object, adding the object with a matrix will add the same object to all the elements of the matrix
            // parameters: int num, matrix from type Matrix
            //we suppose that cctor dtor ctor are implemented
            Matrix<T> matrix_b(mat.dim);
            for (int i = 0; i < mat.height(); i++) {
                for (int j = 0; j < mat.width(); j++)
                    matrix_b.SetValue(i, j, num + mat(i, j));
            }
            return matrix_b;
        }
        friend Matrix<T> operator-(const Matrix<T>& mat,const Matrix<T>& mat2){ //Subtracting the elements of the matrices.we will use subtraction only for matrices of the same dimension
            //DimensionMismatch exception if the dimensions of the matrices do not match.
            //Parameters: mat from type Matrix and mat2 from type Matrix
            //We assume that operator =, ctor, cctor, dtor are implemented
            if(mat.height()!=mat2.height() || mat.width()!=mat2.width()){
                throw Matrix<T>::DimensionMismatch(mat.height(),mat.width(),mat2.height(),mat2.width());
            }
            Matrix<T> newMat(mat);
            const int  rows = mat.height();
            const int cols = mat.width();
            for(int i=0;i<rows;i++){
                for(int j=0; j<cols;j++){
                    newMat.matrice[i][j] = mat.matrice[i][j] - mat2.matrice[i][j];
                }
            }
            return newMat;
        };//done

    };
    template <class T>
    class Matrix<T>::const_iterator {
        const Matrix<T>* CurrentConstMatrix;
        int index;
        const_iterator(const Matrix<T>* mat, int index);
        friend class Matrix<T>;
    public:
        const T* operator->() const;
        const T& operator*() const;
        const_iterator& operator++();
        const_iterator operator++(int);
        bool operator==(const const_iterator& it) const;
        bool operator!=(const const_iterator& it) const;
        const_iterator(const const_iterator&) = default ;
        const_iterator& operator=(const const_iterator&) = default;
    };
    template <class T>
    class Matrix<T>::iterator {
        friend class Matrix<T>;
        Matrix<T>* CurrentMatrix;
        int index;
        iterator( Matrix<T>* mat, int index);
    public:
        T& operator*() const;
        const T* operator->() const;
        iterator& operator++();
        iterator operator++(int);
        bool operator!=(const iterator& it) const;
        bool operator==(const iterator& it) const;
        iterator& operator=(const iterator&) = default;
        iterator(const iterator&) = default;
    };
    template <class T>
    class Matrix<T>::AccessIllegalElement { //The function returns exception of AccessIllegalElement
    public:
        string what() {
            return "Mtm matrix error: An attempt to access an illegal element" ;
        }
    };
    template <class T>
    class Matrix<T>::IllegalInitialization { //The function returns exception of IllegalInitialization
    public:
        string what() {
            return  "Mtm matrix error: Illegal initialization values" ;
        }
    };
    template <class T>
    class Matrix<T>::DimensionMismatch { //The function returns exception of DimensionMismatch
        int row1,col1,row2,col2;
    public:
        DimensionMismatch(int row1,int col1,int row2,int col2):row1(row1),col1(col1),row2(row2),col2(col2){
        }
        string what() {
            return  "Mtm matrix error: Dimension mismatch: ("+to_string(row1)+","+to_string(col1)+")"" ("+to_string(row2)+","+to_string(col2)+")";
        }
    };


    template <class T>
    Matrix<T> operator+(const Matrix<T> &mat,const Matrix<T> &mat2) { //The function adds to matrices (matrixes) connects them element by element we can assume that we will use the connection only for matrices of the same dimension
        //Parameters: two matrixes from type Matrix
        //we suppose that operator += and operator =, cctor,dtor,ctor and operator() are implemented
        if (mat.height() !=mat2.height() || mat.width() != mat2.width()) {
            throw typename Matrix<T>:: DimensionMismatch(mat.height(),mat.width(),mat2.height(),mat2.width());
        }
        Matrix<T> resMat(mat);
        const int rows = mat2.height();
        const int cols = mat2.width();
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                resMat(i,j) += mat2(i,j);
            }
        }
        return resMat;
    }


    template<class T>
    Matrix<T>::Matrix(const Dimensions &dims, const T &num) : dim(dims) { // Constructor for Matrixe<T> .The first argument defines the dimensions of the matrix, and the second argument
        //Is the value to which all the organs of the matrix (type T. object) will be initialized if no second argument is provided
        //Of the matrix will be initialized to the value returned from the default constructor of T.
        //An IllegalInitialization exception will be thrown if the dimensions are not a positive number
        //An bad::alloc::std exception will be thrown in case of memory allocation failure.
        //Parameters: dims from type Dimensions and num from T type
        int rows = dims.getRow();
        int cols = dims.getCol();
        if (cols <= 0 || rows <= 0) {
            throw Matrix<T>::IllegalInitialization();
        }

        matrice = new T*[rows];
        if (matrice == NULL) {
            throw std::bad_alloc();
        }
        for (int i = 0; i < rows; i++) {
            matrice[i] = new T[cols];
            if (matrice[i] == NULL) {
                throw std::bad_alloc();
            }
        }
        for(int j =0;j<rows;j++){
            for(int m =0; m<cols;m++){
                matrice[j][m] = num;
            }
        }
    }

    template <class T>
    std::ostream& operator<<(std::ostream& os, const Matrix<T> mat){ //The function rints the output channel matrix
        return printMatrix(os,mat.begin(),mat.end(),mat.width());
    }

    template<class T>
    Matrix<T>::Matrix(const Matrix<T>  &mat): dim(mat.dim) { //Copy constructor which copies the argument matrix to the current matrix (copies all the elements)
        //Parameters:mat- Matrix type
        //We assume that ctor,cctor,dtor and operator= are implemented
        const int cols = mat.dim.getCol();
        const int rows = mat.dim.getRow();
        if (cols <= 0 || rows <= 0) {
            throw Matrix<T>::IllegalInitialization();
        }
        matrice = new T *[rows];
        if (matrice == NULL) {
            throw std::bad_alloc();
        }
        for (int i = 0; i < rows; i++) {
            matrice[i] = new T[cols];
            if (matrice[i] == NULL) {
                throw std::bad_alloc();
            }
        }
        for(int m =0 ; m<rows;m++){
            for (int j = 0; j < cols; j++){
                matrice[m][j] = mat.matrice[m][j];
            }
        }
    }

    template<class T>
    Matrix<T>::~Matrix(){ //Destructor for Matrix<T> which deletes the memory allocation of the Matrix<T> object
        const int rows = dim.getRow();
        for(int i = 0; i <rows ; ++i) {
            delete [] matrice[i];
        }
        delete [] matrice;
    }

    template<class T>
    Matrix<T> Matrix<T>::Diagonal(int dim, T num) { //The function creates diagonal matrice. The dimension of the matrix is passed as the first argument.
        //The non-diagonal matrix will begin to be the value returned from the T parameterless constructor, and
        //The diagonal will begin to be the value passed on as a second argument.
        //IllegalInitialization exception should be thrown if the dimension is not a positive number.
        //A bad_alloc :: std exception should be thrown in case of memory allocation failure.
        //Parameters: dim-int type, num-T type
        //We assume that ctor,cctor,dtor and operator =, operator() are implemented

        if (dim <= 0) {
            throw Matrix<T>::IllegalInitialization();
        }
        Dimensions newDim = Dimensions(dim, dim);
        Matrix<T> diagonalMat = Matrix(newDim);
        for (int i = 0; i < dim; i++) {
            diagonalMat.SetValue(i, i, num);
        }
        return diagonalMat;
    }

    template<class T>
    Matrix<T> Matrix<T>::transpose()const { //The function returns the copied transposed matrix, without changing the object on which it was triggered.
        //  for matrix A, in transient execution is denoted as
        //A[i][j] element with alternating A[j][i] element
        // Notice that for the non-square matrix, the alternation matrix changes the dimensions of the matrix.
        //Parameters:target matrix
        //We assume that ctor,cctor,dtor and operator= are implemented
        const int rows = this->width();
        const int cols = this->height();
        Dimensions newDim = Dimensions(rows,cols);
        Matrix<T> res = Matrix(newDim);
        for(int i=0;i<rows;i++){
            for(int j=0;j<cols;j++){
                res.matrice[i][j] = this->matrice[j][i];
            }
        }
        return res;
    }

    template<class T>
    Matrix<T> &Matrix<T>::operator=(const Matrix &mat) { //Replace the target matrix elements
        //which will be identical to the origin matrix elements (regardless of the dimensions of the matrices).
        //Parameters: mat from Matrix type
        //We assume that ctor,cctor,dtor and operator() are implemented
        if (this == &mat) {
            return *this;
        }
        const int rows = dim.getRow();

        const int matRows = mat.height();
        const int matCols = mat.width();
        for (int i = 0; i < rows; i++) {
            delete[] matrice[i];
        }
        delete[] matrice;
        this->dim= mat.dim;

        matrice = new T *[matRows];
        if(matrice==NULL){
            throw std::bad_alloc();
        }
        for (int j = 0; j < matRows; j++) {
            matrice[j] = new T[matCols];
            if(matrice[j]==NULL){
                throw std::bad_alloc();
            }
        }
        for (int i = 0; i < matRows; i++) {
            for (int m = 0; m < matCols; m++) {
                matrice[i][m] = mat(i,m);
            }
        }
        return *this;
    }

    template<class T>
    Matrix<T> &Matrix<T>::operator+=(const T num) { //The function adds the object  to all the elements of the matrix
        //Parameters: num-T type
        //We assume that operator += is implemented
        const int rows = dim.getRow();
        const int cols = dim.getCol();
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++)
                matrice[i][j] += num;
        }
        return *this;
    }

    template<class T>
    void Matrix<T>::SetValue(int row, int col, T num) { //The function changes or sets the value of given element in the matrix to a given int scalar num
        //Parameters: row-int tyoe, col-int type, num-T type
        if ((row > this->height()) || (col > this->width())) {
            throw Matrix<T>::AccessIllegalElement();
        }
        matrice[row][col] = num;
    }

    template<class T>
    T& Matrix<T>::operator()(const int row, const int col)  { //The function gives access to the two-index matrix elements for reading and writing.
        //Parameters: row, col-int type
        int height = this->height();
        int width = this->width();
        if(row < 0 || row > height || col < 0 || col > width){
            throw Matrix<T>::AccessIllegalElement();
        }
        return this->matrice[row][col];
    }

    template<class T>
    T &Matrix<T>::operator()(const int row, const int column) const{ //The function gives access to the two-index matrix elements for reading and writing.
        //Parameters: row-int type, column-int type
        int height = this->height();
        int width = this->width();
        if(row < 0 || row >= height || column < 0 || column >= width){

        }

        return this->matrice[row][column];
    }

    template<class T>
    Matrix<bool> Matrix<T>::operator==(const T& num) { //Between a <T> Matrix type object and a T type object
        //Comparison of a matrix with an object will be defined as a matrix whose boolean elements (i.e., the <bool <Matrix, type) having
        //Dimensions are the same as the original matrix, where the organs that make the comparison in the original matrix are replaced by true,
        //While the other organs will be replaced by a false value.
        //Parameters: num-T type
        //We assume that cctor,dtor,ctor and operator() and bool are implemented
        const int rows = dim.getRow();
        const int cols = dim.getCol();
        Dimensions NewDim = dim;
        Matrix<bool> res(NewDim);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++)
            {
                if(matrice[i][j]==num){
                    res(i,j)=true;
                } else{
                    res(i,j)=false;
                }

            }

        }
        return res;
    }

    template<class T>
    Matrix<T> Matrix<T>::operator-() const{ //Provide an unary version of -operator for matrices.
        //DimensionMismatch exception if the dimensions of the matrices do not match.
        //Parameters: target matrix
        //We assume that ctor,cctor,dtor are implemented
        Dimensions newDim(dim);
        Matrix<T> res(newDim);
        const int  rows = this->dim.getRow();
        const int cols = this->dim.getCol();
        for(int i=0;i<rows;i++){
            for(int j=0; j<cols;j++){
                res.matrice[i][j] = -matrice[i][j];
            }
        }
        return res;

    }

    template<class T>
    Matrix<bool> Matrix<T>::operator<=(const T& num) { //Between a <T> Matrix type object and a T type object
        //Comparison of a matrix with an object will be defined as a matrix whose boolean elements (i.e., the <bool <Matrix, type) having
        //Dimensions are the same as the original matrix, where the organs that make the comparison in the original matrix are replaced by true,
        //While the other organs will be replaced by a false value.
        //Parameters: num-type T
        //We assume that bool, ctor,cctor operator() are implemented
        const int rows = dim.getRow();
        const int cols = dim.getCol();
        Dimensions NewDim = dim;
        Matrix<bool> resMat(NewDim);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++){
                if(matrice[i][j]<=num){
                    resMat(i,j)=true;
                } else{
                    resMat(i,j)=false;
                }
            }

        }
        return resMat;
    }




    template<class T>
    Matrix<bool> Matrix<T>::operator!=(const T& num) { //Between a <T> Matrix type object and a T type object
        //Comparison of a matrix with an object will be defined as a matrix whose boolean elements (i.e., the <bool <Matrix, type) having
        //Dimensions are the same as the original matrix, where the organs that make the comparison in the original matrix are replaced by true,
        //While the other organs will be replaced by a false value.
        //Parameters: num-type T
        //We assume that bool, ctor,cctor operator() are implemented
        const int rows = dim.getRow();
        const int cols = dim.getCol();
        Dimensions NewDim = dim;
        Matrix<bool> resMat(NewDim);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++){
                if(matrice[i][j]!=num){
                    resMat(i,j)=true;
                } else{
                    resMat(i,j)=false;
                }
            }

        }
        return resMat;
    }

    template<class T>
    Matrix<bool> Matrix<T>::operator>=(const T& num) { //Between a <T> Matrix type object and a T type object
        //Comparison of a matrix with an object will be defined as a matrix whose boolean elements (i.e., the <bool <Matrix, type) having
        //Dimensions are the same as the original matrix, where the organs that make the comparison in the original matrix are replaced by true,
        //While the other organs will be replaced by a false value.
        //Parameters: num-type T
        //We assume that bool, ctor,cctor operator() are implemented
        const int rows = dim.getRow();
        const int cols = dim.getCol();
        Dimensions NewDim = dim;
        Matrix<bool> resMat(NewDim);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++){
                if(matrice[i][j]>=num){
                    resMat(i,j)=true;
                } else{
                    resMat(i,j)=false;
                }
            }

        }
        return resMat;
    }

    template<class T>
    Matrix<bool> Matrix<T>::operator>(const T& num) { //Between a <T> Matrix type object and a T type object
        //Comparison of a matrix with an object will be defined as a matrix whose boolean elements (i.e., the <bool <Matrix, type) having
        //Dimensions are the same as the original matrix, where the organs that make the comparison in the original matrix are replaced by true,
        //      While the other organs will be replaced by a false value.
        //Parameters: num-type T
        //We assume that bool, ctor,cctor operator() are implemented
        const int rows = dim.getRow();
        const int cols = dim.getCol();
        Dimensions NewDim = dim;
        Matrix<bool> resMat(NewDim);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++){
                if(matrice[i][j]>num){
                    resMat(i,j)=true;
                } else{
                    resMat(i,j)=false;
                }
            }

        }
        return resMat;
    }

    template<class T>
    Matrix<bool> Matrix<T>::operator<(const T& num) { //Between a <T> Matrix type object and a T type object
        //Comparison of a matrix with an object will be defined as a matrix whose boolean elements (i.e., the <bool <Matrix, type) having
        //Dimensions are the same as the original matrix, where the organs that make the comparison in the original matrix are replaced by true,
        //      While the other organs will be replaced by a false value.

        //Parameters: num-type T
        //We assume that bool, ctor,cctor operator() are implemented
        const int rows = dim.getRow();
        const int cols = dim.getCol();
        Dimensions NewDim = dim;
        Matrix<bool> resMat(NewDim);
        for (int l = 0; l < rows; l++) {
            for (int k = 0; k < cols; k++){
                if(matrice[l][k]<num){
                    resMat(l,k)=true;
                }
                else{
                    resMat(l,k)=false;
                }
            }

        }
        return resMat;
    }



    template<class T>
    bool all( const Matrix<T>& mat){  //The all function returns true if
        //all the organs of the matrix it receives are true as true values (that is, when converted to bool.)
        //Parameters: mat-Matrix type
        //We assume that operator(), cctor, ctor are implemented
        bool all = true;
        const int rows = mat.height();
        const int cols = mat.width();
        for(int i = 0;i<rows;i++){
            for(int j=0;j<cols;j++){
                if(mat(i,j)==false){
                    all = false;
                }
            }
        }
        return all;
    }
    template<class T>
    bool any( const Matrix<T>& mat){  //The function any returns true if there is at least one organ in the matrix whose value is true as a true value.
        //Parameters: mat-Matrix type
        //We assume that operator(), cctor, ctor are implemented
        bool any = false;
        const int rows = mat.height();
        const int cols = mat.width();
        for(int i = 0;i<rows;i++){
            for(int j=0;j<cols;j++){
                if(mat(i,j)!= false){
                    any=true;
                }
            }
        }
        return any;
    }
    template<class T>
    const T* Matrix<T>::iterator::operator->() const {  //The function returns the value of the element of the iterator (reference)
        assert(index < CurrentMatrix->getSize() && index >= 0);
        return &(CurrentMatrix->data[index]);
    }
    template<class T>
    const T* Matrix<T>::const_iterator::operator->() const { //The the function operator-> returns the value of the element of the index of the const_iterator(by reference)
        assert((index >= 0) && (index < CurrentConstMatrix->getSize()));
        return &(CurrentConstMatrix->data[index]);
    }
    template <class T>
    Matrix<T>::iterator::iterator( Matrix<T>* mat, int index) :
            CurrentMatrix(mat),
            index(index)
    { } //Constructor for iterator which receives Matrix<T> object and index from int type
    template <class T>
    T& Matrix<T>::iterator::operator*() const { //AccessIllegalElement exception should be thrown if trying to execute operator * on non iterator
        //Pointer to a valid organ. Iterator will not point to a valid organ if:
        // The iterator was returned from the end function.
        // Previous iterator beyond the boundary of the matrix.
        if(index<0 || index>= CurrentMatrix->size()){
            throw AccessIllegalElement();
        }
        int rows = index/CurrentMatrix->width();
        int cols = index%CurrentMatrix->width();
        return CurrentMatrix->matrice[rows][cols];
    }
    template <class T>
    class Matrix<T>::iterator& Matrix<T>::iterator::operator++() { //The function returns the next iterator
        ++index;
        return *this;
    }

    template <class T>
    bool Matrix<T>::iterator::operator==(const iterator& i) const { //Checks if the value of the element's index equals to the given matrice if true, it changes to the index of the given argument (the iterator) and returns the current index of the matrice
        assert(CurrentMatrix == i.CurrentMatrix);
        if(index == i.index){
            return true;
        }
        return false;
    }

    template <class T>
    class Matrix<T>::iterator Matrix<T>::iterator::operator++(int) { //The function returns the iterator and it advances the current iterator to the next one
        iterator res = *this;
        ++*this;
        return res;
    }
    template <class T>
    bool Matrix<T>::iterator::operator!=(const iterator& i) const {  //The function returns true if the cuurent matrice equals to the given i argument, if not return false
        if(!(*this == i)){
            return true;
        }
        return false;
    }
    template <class T>
    class Matrix<T>::iterator Matrix<T>::begin() { //The function returns an "iterator" to the first organ of the structure
        return iterator(this, 0);
    }
    template <class T>
    class Matrix<T>::iterator Matrix<T>::end() {//The function returns an "iterator" indicating that the transition to the structure is complete
        return iterator(this,size());
    }

    template <class T>
    Matrix<T>::const_iterator::const_iterator(const Matrix* mat, int index) :
            CurrentConstMatrix(mat),
            index(index)
    { } //Constructor to const_iterator which receives an argument ConstMatrix which it's type is IntMatrix*, and an index which it's type is int
    template <class T>
    const T& Matrix<T>::const_iterator::operator*() const { //The function returns the value of given index of element
        if( index<0 || index >= CurrentConstMatrix->size()){
            throw AccessIllegalElement();
        }
        int rows = index/CurrentConstMatrix->width();
        int cols = index%CurrentConstMatrix->width();
        return CurrentConstMatrix->matrice[rows][cols];
    }
    template <class T>
    class Matrix<T>::const_iterator& Matrix<T>::const_iterator::operator++() { //The function returns the next const_iterator iterator
        ++index;
        return *this;
    }
    template <class T>
    template <class condition>
    Matrix<T> Matrix<T>::apply(condition c)const { //apply function receives a parameter as an object
        //With parentheses (C or object function), and activates it on all the elements of the matrix while returning the matrix
        //Parameters: condition c
        //We assume that ctor,cctor,dtor,operator= are implemented
        Matrix<T> mat(*this);
        for(typename Matrix<T>::iterator it=mat.begin();it!=mat.end();++it){
            *it=c(*it);
        }
        return mat;
    }
    template <class T>
    class Matrix<T>::const_iterator Matrix<T>::const_iterator::operator++(int){ //The function returns the const_iterator iterator and it advances the current iterator to the next one
        const_iterator result = *this;
        ++*this;
        return result;
    }
    template <class T>
    bool Matrix<T>::const_iterator::operator==(const Matrix<T>::const_iterator& i) const { //Checks if the value of the element's index equals to the given matrice if true, it changes to the index of the given argument (the iterator) and returns the current index of the matrice
        assert(CurrentConstMatrix == i.CurrentConstMatrix);
        if(index == i.index){
            return true;
        }
        return false;
    }


    template <class T>
    bool Matrix<T>::const_iterator::operator!=(const Matrix<T>::const_iterator& i) const { //The function returns true if the current matrice equals to the given i argument, if not return false
        if(!(*this == i)) {
            return true;
        }
        return false;
    }
    template <class T>
    class Matrix<T>::const_iterator Matrix<T>::end() const{ //The function returns an "const_iterator" indicating that the transition to the structure is complete
        return const_iterator(this,size());
    }

    template <class T>
    class Matrix<T>::const_iterator Matrix<T>::begin() const { //The function returns an "const_iterator" to the first organ of the structure
        return const_iterator(this, 0);
    }

}


#endif //LASTHW_MATRIX_H
