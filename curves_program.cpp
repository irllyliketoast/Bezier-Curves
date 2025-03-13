#include "CImg.h"
#include <vector>
#include <iostream>

using namespace cimg_library;
using namespace std;

int main() {
    // Create an empty 500x500 image
    CImg<unsigned char> image(500, 500, 1, 3, 0);  // 500x500 image, 3 channels (RGB)
    CImgDisplay window(image, "Click to select control points");

    // Variables to store control points
    vector<int> coords_x;
    vector<int> coords_y;
    unsigned char color[] = {255, 128, 64};  // Initial color for control points
    
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
        if (window.is_keyESC()) break;  // Stop capturing points when ESC is pressed
    }

    // Function to compute Chaikin's curve points for one iteration
    auto chaikin_curve = [](const vector<int>& x, const vector<int>& y) { // googled this because I couldn't get it to work without it
        vector<int> new_x, new_y;
        for (size_t i = 0; i < x.size() - 1; ++i) {
            // Calculate new points
            int x1 = x[i];
            int y1 = y[i];
            int x2 = x[i + 1];
            int y2 = y[i + 1];
            // First new point (25% along the line)
            new_x.push_back(0.75 * x1 + 0.25 * x2);
            new_y.push_back(0.75 * y1 + 0.25 * y2);
            // Second new point (75% along the line)
            new_x.push_back(0.25 * x1 + 0.75 * x2);
            new_y.push_back(0.25 * y1 + 0.75 * y2);
        }
        return make_pair(new_x, new_y);
    };

    // Perform 6 iterations of the Chaikin curve
    vector<int> current_x = coords_x;
    vector<int> current_y = coords_y;
    for (int iteration = 0; iteration < 6; ++iteration) {
        // Change the color for each iteration
        color[0] = rand() % 255;
        color[1] = rand() % 255;
        color[2] = rand() % 255;

        // Draw the current line segments
        for (size_t i = 0; i < current_x.size() - 1; ++i) {
            image.draw_line(current_x[i], current_y[i], current_x[i + 1], current_y[i + 1], color);
        }

        // Display the updated image
        window.display(image);
        window.wait(500);  // Pause to visualize each iteration

        // Compute the next iteration using Chaikin's algorithm
        tie(current_x, current_y) = chaikin_curve(current_x, current_y);
    }

    // Wait for the user to close the window
    while (!window.is_closed()) {
        window.wait();
    }

    return 0;
}
