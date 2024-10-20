/*
Author: David Holmqvist <daae19@student.bth.se>
*/

#include "vector.hpp"
#include <cmath>
#include <stdexcept>

Vector::Vector() : size(0), data(nullptr) {}

Vector::Vector(unsigned size) : size(size), data(new double[size]()) {}

Vector::Vector(unsigned size, double* data) : size(size), data(new double[size]) {
    std::copy(data, data + size, this->data);
}

Vector::Vector(const Vector& other) : size(other.size), data(new double[other.size]) {
    std::copy(other.data, other.data + other.size, this->data);
}

Vector::~Vector() {
    delete[] data;
}

double Vector::magnitude() const {
    double sum = 0.0;
    for (unsigned i = 0; i < size; ++i) {
        sum += data[i] * data[i];
    }
    return std::sqrt(sum);
}

double Vector::mean() const {
    if (size == 0) return 0.0;
    double sum = 0.0;
    for (unsigned i = 0; i < size; ++i) {
        sum += data[i];
    }
    return sum / size;
}

double Vector::dot(const Vector& rhs) const {
    if (size != rhs.size) {
        throw std::invalid_argument("Vectors must be the same size for dot product.");
    }

    double result = 0.0;
    unsigned i = 0;

    // Loop unrolling to improve performance
    for (; i + 3 < size; i += 4) {
        result += data[i] * rhs[i] +
                  data[i + 1] * rhs[i + 1] +
                  data[i + 2] * rhs[i + 2] +
                  data[i + 3] * rhs[i + 3];
    }

    // Handle remaining elements
    for (; i < size; i++) {
        result += data[i] * rhs[i];
    }

    return result;
}

unsigned Vector::get_size() const {
    return size;
}

double* Vector::get_data() {
    return data;
}

Vector Vector::operator/(double div) const {
    Vector result(size);
    for (unsigned i = 0; i < size; ++i) {
        result[i] = data[i] / div;
    }
    return result;
}

Vector Vector::operator-(double sub) const {
    Vector result(size);
    for (unsigned i = 0; i < size; ++i) {
        result[i] = data[i] - sub;
    }
    return result;
}

double Vector::operator[](unsigned i) const {
    return data[i];
}

double& Vector::operator[](unsigned i) {
    return data[i];
}
