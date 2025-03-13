# Bezier Curves
Report on Implementation of De Casteljau’s Algorithm for Bézier Curves
Explain the concepts used in this programming assignment as you would to someone not in CSC 370

1. Introduction
Bézier curves are a fundamental tool in computer graphics – most commonly used for modeling smooth curves that can be scaled indefinitely. This report focuses on the implementation of De Casteljau’s algorithm, which provides a numerical method for calculating points on Bézier curves. The algorithm is efficient and offers a geometrical interpretation of the curve's construction, making it an excellent choice for graphical applications.
Chaikin's algorithm is a subdivision scheme used to generate smooth curves from a set of control points. It iteratively refines the control polygon by adding new points along the polygon edges, producing a curve that closely approximates the original shape. This algorithm does not directly compute curve points like De Casteljau's for Bézier curves but instead refines the polygon with a simpler approach. Chaikin's algorithm is popular due to its simplicity and ability to generate smooth, visually appealing curves without the complexity of other techniques like Bézier curves.

2. Objectives
To implement De Casteljau’s algorithm to draw Bézier curves based on user-defined control points. To develop an interactive GUI that allows users to click and define control points, after which the Bézier curve is drawn.

3. Methodology
3.1 Tools and Libraries
CImg library
3.2 Implementation Steps
1. Initialization: Created a blank image and a display window using the CImg library.
2. User Input: Captured mouse clicks to allow users to specify control points for both curves. Each click recorded the coordinates and drew small circles at those points for visual feedback.
3. De Casteljau’s Algorithm: Implemented the algorithm to interpolate points along both curves. The algorithm uses linear interpolation between points in a recursive manner until it converges on a single point.
4. Drawing the Curve: After the user presses the ESC key, the program calculates points along both curves and draws them on the image.
5. Event Loop: Maintained an event loop to continuously check for user inputs until the window is closed.
3.3 De Casteljau’s Algorithm
The algorithm operates by recursively dividing the set of control points until a single point is computed:
- Given control points defined by their x and y coordinates, the algorithm iteratively computes new sets of points through linear interpolation until it produces a single point that represents the Bézier curve at a particular parameter \( t \) ranging from 0 to 1.
3.4 Code Structure
The core functionality is encapsulated within the `de_casteljau` function, which accepts vectors of control point coordinates and the parameter \( t \). The main function manages user interaction and the graphical display.
3.5 Unfamiliar Code
	`auto`: This keyword allows the compiler to automatically deduce the type of a variable at compile time. It simplifies code by reducing the need to specify the type explicitly, which is especially useful when dealing with complex data types or when the type is obvious from the context. For example, when iterating through a vector, using `auto` saves time and keeps the code clean – I honestly could only get the code to work this way.
	`pair`: A `pair` is a standard library utility in C++ that holds two related values, making it convenient for managing coordinate pairs (like x and y for points). Using `pair` clearly indicates that two values belong together.
	`const`: This keyword signifies that a variable's value cannot be changed after its initialization. In my code, using `const` for function parameters ensured that the control points were protected from accidental modification during calculations.
I gained a better understanding of these concepts through a YouTube video that explained C++ syntax and best practices, as well as through discussions with a friend who is an experienced coder. Their advice helped me grasp how to apply these features effectively in my implementation.

4. Results
- Users can create as many control points as they desire, with visual feedback provided for each point.
- Upon pressing the ESC key, the program draws the Bézier curve based on the control points provided.




4.1 Sample Outputs


Figure 1: Bézier Curve with 3 Control Points
Figure 2: Bézier Curve with 4 Control Points 
Figure 3: Bézier Curve with 5 Control Points


















Figure 1: Chaikin's Algorithm Applied on a Polygon with 3 Control Points After 1 Iterations
Figure 2: Chaikin's Algorithm Applied on a Polygon with 3 Control Points After 2 Iterations
Figure 3: Chaikin's Algorithm Applied on a Polygon with 3 Control Points After ALL Iterations

5. Discussion
The implementation of De Casteljau’s algorithm allowed for the successful rendering of Bézier curves based on user-selected control points. Through interactive user input, participants were able to visualize the effect of varying control points on the shape of the curve. The results demonstrated that the smoothness and characteristics of the curve are influenced by the number of control points. With three to four points, the curves displayed a graceful arc, while an increased number of control points resulted in tighter curves that adhered closely to the points. This behavior illustrates how Bézier curves can be finely tuned by user input, making them versatile tools in computer graphics.
In contrast, implementing Chaikin's algorithm revealed its unique properties in generating smooth curves from a polygon defined by control points. As the algorithm iteratively refined the control points, the resulting curves became progressively smoother and more visually appealing. The ease of use of Chaikin's algorithm makes it an attractive option for applications where simplicity and aesthetic quality are paramount. The visual results demonstrated that as iterations increased, the curves approached a smoother approximation of the original shape.
This project highlighted the strengths and weaknesses of both algorithms: De Casteljau's method excels in precision and control, while Chaikin's algorithm offers a straightforward approach to curve refinement. Understanding both techniques broadens the range of tools available for curve modeling, emphasizing the importance of selecting the appropriate algorithm based on specific graphical needs.
6. Difficulties Encountered
The development of the project was not easy. Initially, one of the issues I had was managing data types in the implementation of De Casteljau’s algorithm. Specifically, when creating the vectors for `x` and `y` coordinates, the code was written to initialize `int` types, which led to an error when trying to assign them to `float` vectors in the De Casteljau function. This caused repeated error messages like `conversion from 'vector<int>' to non-scalar type 'vector<float>' requested`. After debugging and reflecting on the issue for a while, I realized that the root of the problem was mismatching data types. 
Another issue was trying to reconcile the graphic output with the algorithm’s functioning. While the algorithm was correctly calculating points, nothing was visually happening on the display at first. I initially thought this was due to a bug, but after rechecking, it became clear that the issue was in the timing and how user input was processed. It was frustrating to have the code logically correct, but not see the curve drawn. The breakthrough came when I realized that the curve would only render after the user pressed ESC, and I hadn’t communicated this clearly in the interface. Once this was addressed, the program worked as expected. I also had to look up the line of code for automatic iteration through the points. 
Lastly, I was trying to process user inputs, but the curved generation logic was buried in a separate function. Taking a break and having my friend explain the code mistake out loud helped me and allowed me to reorganize the structure so that both parts (user input and curve rendering) worked together.
TA DA!

