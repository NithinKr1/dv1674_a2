/*
Author: David Holmqvist <daae19@student.bth.se>
*/

#include "matrix.hpp"
#include "ppm.hpp"
#include <fstream>
#include <stdexcept>

// Constructor that initializes the matrix with color channels and size
Matrix::Matrix(unsigned char* R, unsigned char* G, unsigned char* B, unsigned x_size, unsigned y_size, unsigned color_max)
    : R { R }
    , G { G }
    , B { B }
    , x_size { x_size }
    , y_size { y_size }
    , color_max { color_max }
{
}

// Default constructor
Matrix::Matrix()
    : Matrix {
        nullptr,
        nullptr,
        nullptr,
        0,
        0,
        0,
    }
{
}

// Constructor for creating a matrix with a given dimension
Matrix::Matrix(unsigned dimension)
    : R { new unsigned char[dimension * dimension] }
    , G { new unsigned char[dimension * dimension] }
    , B { new unsigned char[dimension * dimension] }
    , x_size { dimension }
    , y_size { dimension }
    , color_max { 0 }
{
}

// Copy constructor (using manual loop for copying)
Matrix::Matrix(const Matrix& other)
    : R { new unsigned char[other.x_size * other.y_size] }
    , G { new unsigned char[other.x_size * other.y_size] }
    , B { new unsigned char[other.x_size * other.y_size] }
    , x_size { other.x_size }
    , y_size { other.y_size }
    , color_max { other.color_max }
{
    unsigned size = x_size * y_size;
    for (unsigned i = 0; i < size; i++) {
        R[i] = other.R[i];
        G[i] = other.G[i];
        B[i] = other.B[i];
    }
}

// Assignment operator (using manual loop for copying)
Matrix& Matrix::operator=(const Matrix other)
{
    if (this == &other) {
        return *this;
    }

    this->~Matrix();

    R = new unsigned char[other.x_size * other.y_size];
    G = new unsigned char[other.x_size * other.y_size];
    B = new unsigned char[other.x_size * other.y_size];
    
    x_size = other.x_size;
    y_size = other.y_size;
    color_max = other.color_max;

    unsigned size = x_size * y_size;
    for (unsigned i = 0; i < size; i++) {
        R[i] = other.R[i];
        G[i] = other.G[i];
        B[i] = other.B[i];
    }

    return *this;
}

// Destructor
Matrix::~Matrix()
{
    if (R) {
        delete[] R;
        R = nullptr;
    }
    if (G) {
        delete[] G;
        G = nullptr;
    }
    if (B) {
        delete[] B;
        B = nullptr;
    }

    x_size = y_size = color_max = 0;
}

// Getter functions for matrix dimensions and color max value
unsigned Matrix::get_x_size() const
{
    return x_size;
}

unsigned Matrix::get_y_size() const
{
    return y_size;
}

unsigned Matrix::get_color_max() const
{
    return color_max;
}

// Pixel accessor functions
unsigned char Matrix::r(unsigned x, unsigned y) const
{
    return R[y * x_size + x];  // Access red channel
}

unsigned char Matrix::g(unsigned x, unsigned y) const
{
    return G[y * x_size + x];  // Access green channel
}

unsigned char Matrix::b(unsigned x, unsigned y) const
{
    return B[y * x_size + x];  // Access blue channel
}

// Non-const versions for modifying pixel values
unsigned char& Matrix::r(unsigned x, unsigned y)
{
    return R[y * x_size + x];  // Modify red channel
}

unsigned char& Matrix::g(unsigned x, unsigned y)
{
    return G[y * x_size + x];  // Modify green channel
}

unsigned char& Matrix::b(unsigned x, unsigned y)
{
    return B[y * x_size + x];  // Modify blue channel
}

// Getter functions for R, G, B arrays (const versions)
unsigned char const* Matrix::get_R() const
{
    return R;
}

unsigned char const* Matrix::get_G() const
{
    return G;
}

unsigned char const* Matrix::get_B() const
{
    return B;
}
