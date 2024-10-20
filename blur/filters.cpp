#include "filters.hpp"
#include "matrix.hpp"
#include "ppm.hpp"
#include <cmath>
#include <algorithm>

namespace Filter
{
    namespace Gauss
    {
        // Reuse weights to avoid recalculation
        void get_weights(int n, double *weights_out)
        {
            for (auto i { 0 }; i <= n; i++) {
                double x { static_cast<double>(i) * max_x / n };
                weights_out[i] = exp(-x * x * pi);
            }
        }
    }

    Matrix blur(Matrix m, const int radius)
    {
        // Create scratch matrix for intermediate results
        Matrix scratch { PPM::max_dimension };
        auto dst { m };

        double w[Gauss::max_radius] {};
        Gauss::get_weights(radius, w);

        // Processing the x direction
        for (auto x { 0 }; x < static_cast<int>(dst.get_x_size()); ++x) {
            for (auto y { 0 }; y < static_cast<int>(dst.get_y_size()); ++y) {
                double r = 0.0, g = 0.0, b = 0.0, n = w[0];

                // Use local variables for frequently accessed pixel values
                r = w[0] * dst.r(x, y);
                g = w[0] * dst.g(x, y);
                b = w[0] * dst.b(x, y);

                // Unroll loop to process 2 neighbors at a time
                for (auto wi { 1 }; wi <= radius - 1; wi += 2) {
                    auto wc1 { w[wi] };
                    auto wc2 { w[wi + 1] };

                    int x1 = std::max(0, x - wi);
                    int x2 = std::min(static_cast<int>(dst.get_x_size() - 1), x + wi);

                    // Fetch and accumulate pixel values for red, green, blue channels
                    r += wc1 * dst.r(x1, y) + wc2 * dst.r(x2, y);
                    g += wc1 * dst.g(x1, y) + wc2 * dst.g(x2, y);
                    b += wc1 * dst.b(x1, y) + wc2 * dst.b(x2, y);
                    n += wc1 + wc2;
                }

                // Handle edge case where radius is odd
                if (radius % 2 != 0) {
                    int last_x = std::max(0, x - radius);
                    r += w[radius] * dst.r(last_x, y);
                    g += w[radius] * dst.g(last_x, y);
                    b += w[radius] * dst.b(last_x, y);
                    n += w[radius];
                }

                // Normalize and assign values to scratch matrix
                scratch.r(x, y) = r / n;
                scratch.g(x, y) = g / n;
                scratch.b(x, y) = b / n;
            }
        }

        // Processing the y direction (same as x)
        for (auto x { 0 }; x < static_cast<int>(dst.get_x_size()); ++x) {
            for (auto y { 0 }; y < static_cast<int>(dst.get_y_size()); ++y) {
                double r = 0.0, g = 0.0, b = 0.0, n = w[0];

                // Use local variables for frequently accessed pixel values
                r = w[0] * scratch.r(x, y);
                g = w[0] * scratch.g(x, y);
                b = w[0] * scratch.b(x, y);

                // Unroll loop to process 2 neighbors at a time
                for (auto wi { 1 }; wi <= radius - 1; wi += 2) {
                    auto wc1 { w[wi] };
                    auto wc2 { w[wi + 1] };

                    int y1 = std::max(0, y - wi);
                    int y2 = std::min(static_cast<int>(dst.get_y_size() - 1), y + wi);

                    // Fetch and accumulate pixel values for red, green, blue channels
                    r += wc1 * scratch.r(x, y1) + wc2 * scratch.r(x, y2);
                    g += wc1 * scratch.g(x, y1) + wc2 * scratch.g(x, y2);
                    b += wc1 * scratch.b(x, y1) + wc2 * scratch.b(x, y2);
                    n += wc1 + wc2;
                }

                // Handle edge case where radius is odd
                if (radius % 2 != 0) {
                    int last_y = std::max(0, y - radius);
                    r += w[radius] * scratch.r(x, last_y);
                    g += w[radius] * scratch.g(x, last_y);
                    b += w[radius] * scratch.b(x, last_y);
                    n += w[radius];
                }

                // Normalize and assign values to destination matrix
                dst.r(x, y) = r / n;
                dst.g(x, y) = g / n;
                dst.b(x, y) = b / n;
            }
        }

        return dst;
    }
}
