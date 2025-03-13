#include "CImg.h"
#include <vector>
#include <utility> // for std::pair
#include <iostream>

using namespace cimg_library;
using namespace std;

// De Casteljau's algorithm to calculate a point on the Bezier curve
std::pair<float, float> de_casteljau(const std::vector<int>& x, const std::vector<int>& y, float t) {
    // Create float vectors to store x and y coordinates
    vector<float> temp_x(x.size());
    vector<float> temp_y(y.size());

    // Copy values from integer vectors to float vectors
    for (size_t i = 0; i < x.size(); ++i) {
        temp_x[i] = static_cast<float>(x[i]);  // Convert int to float
    }
    for (size_t i = 0; i < y.size(); ++i) {
        temp_y[i] = static_cast<float>(y[i]);  // Convert int to float
    }

    int n = x.size() - 1;  // The number of control points - 1
    for (int r = 1; r <= n; ++r) {
        for (int i = 0; i <= n - r; ++i) {
            temp_x[i] = (1 - t) * temp_x[i] + t * temp_x[i + 1];  // Linear interpolation for x
            temp_y[i] = (1 - t) * temp_y[i] + t * temp_y[i + 1];  // Linear interpolation for y
        }
    }

    return { temp_x[0], temp_y[0] };  // Return the final interpolated point
}

int main() {
    // Create an empty 500x500 image
    CImg<unsigned char> image(500, 500, 1, 3, 0);  // Width, height, depth, channels, initial color
    unsigned char color[] = { 255, 128, 64 };      // Color for points and lines
    CImgDisplay window(image, "Click control points for Bezier curve");

    vector<int> coords_x, coords_y;

    // Capture user clicks for control points
    while (!window.is_closed()) {
        window.wait();
        if (window.button()) {
            int x = window.mouse_x();
            int y = window.mouse_y();
            cout << "Selected point: (" << x << ", " << y << ")" << endl;
            coords_x.push_back(x);
            coords_y.push_back(y);
            // Draw a small circle at the selected control point
            image.draw_circle(x, y, 5, color);
            window.display(image);
        }

        // Press ESC to start drawing the Bezier curve
        if (window.is_keyESC()) {
            break;  // Break out of the loop to compute the curve
        }
    }

    // Ensure there are enough control points for a curve
    if (coords_x.size() < 2) {
        cerr << "At least 2 control points are needed to draw a Bezier curve." << endl;
        return 1;
    }

    // Draw Bezier curve using de Casteljau's algorithm
    for (float t = 0; t <= 1; t += 0.01) {  // Iterate over t from 0 to 1 in steps of 0.01
        auto [bx, by] = de_casteljau(coords_x, coords_y, t);
        image.draw_circle(bx, by, 2, color);  // Draw a small circle at the Bezier point
        window.display(image);
    }

    // Wait for the user to close the window
    while (!window.is_closed()) {
        window.wait();
    }

    return 0;
}
