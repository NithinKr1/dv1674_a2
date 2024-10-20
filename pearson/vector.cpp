/*
 * Author: David Holmqvist <daae19@student.bth.se>
 */

#include "vector.hpp"
#include <cmath>
#include <algorithm>
#include <numeric>

Vector::Vector() : size(0), data(nullptr) {}

Vector::Vector(unsigned size) : size(size), data(new doublesize) {}

Vector::Vector(unsigned size, double* data) : size(size), data(new double[size])
{
    std::copy(data, data + size, this->data);
}

Vector::Vector(const Vector& other) : size(other.size), data(new double[other.size])
{
    std::copy(other.data, other.data + other.size, data);
}

Vector::~Vector()
{
    delete[] data;
}

double Vector::magnitude() const
{
    return std::sqrt(std::inner_product(data, data + size, data, 0.0));
}

double Vector::mean() const
{
    return std::accumulate(data, data + size, 0.0) / size;
}

double Vector::dot(Vector rhs) const
{
    return std::inner_product(data, data + size, rhs.data, 0.0);
}

unsigned Vector::get_size() const
{
    return size;
}

double* Vector::get_data()
{
    return data;
}

Vector Vector::operator/(double div)
{
    Vector result(size);
    std::transform(data, data + size, result.data, div { return val / div; });
    return result;
}

Vector Vector::operator-(double sub)
{
    Vector result(size);
    std::transform(data, data + size, result.data, sub { return val - sub; });
    return result;
}

double Vector::operator const
{
    return data[i];
}

double& Vector::operator
{
    return data[i];
}
