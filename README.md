## One of my school projects which demonstrates fuzzy logic using my custom-built game engine

## Section 1
### Running the program

1. Download the zipped solution from distance.digipen.edu
2. Unzip the file 
3. Launch the solution using Microsoft Visual Studio
4. Compile the solution in Release Mode
5. Go to the file directory of the solution and open the Release folder
6. Place the glew32.dll in the same directory as the executable file
7. Place the folder File that contains the GeometryParametersFile.txt input file that the program will read
8. Place the folder Shaders that contains the CG files
9. Include all the compressed image file in the same directory as the executable file
10. Click on the executable file to launch the application 
<br />or <br />
1. You can directly run the executable file found in `\fuzzy-logic-demo\FuzzyLogic_Demo\win32-OpenGL.exe`

## Section 1.1
### Navigating and toggling display options

1. Press 'V' to toggle between showing the fills, lines and points of the geometry
2. Press 'C' to enable/disable backface culling
3. Press 'T' to enable/disable Anisotropic filtering
4. Press 'F' the texture minification filter mode
5. Press 'G' the texture magnificationfilter mode
6. Press 'P' to toggle between perspective and orthographic projections
7. Press 'N' to display wall normals
7. Press 'ESC' to close the application

## Section 1.2
### Toggling lighting and environment mapping effects

1. Press 'L' to toggle between the following lighting effects: directional light, point light, spot light
2. Press 'K' to toggle between the following environment mapping effects: reflection, refraction, chromatic dispersion and Fresnel effect
3. Press 'J' to toggle between vertex/fragment shader effects for lighting, reflection, refraction, chromatic dispersion and Fresnel effect
4. Press 'U' to turn on/off light attenuation
5. Press 'O' to turn on/off the projective texturing

## Section 1.3
### You can control the plane by doing the following:

1. Press 'W' to move the plane upward
2. Press 'S' to move the plane downward
3. Press 'A' to move the plane to the left
4. Press 'D' to move the plane to the right

## Section 1.4
### You can set-up the missile by doing the following:

1. Click the left-mouse button to set the starting position of the missile
2. Press 'A' to rotate missile launch angle counter clockwise
3. Press 'D' to rotate missile launch angle clockwise
4. Press 'RETURN' (enter) to launch the missile

## Section 1.5
### You can control the camera by doing the following:

1. Press 'UP ARROW KEY' to move the camera forward
2. Press 'DOWN ARROW KEY' to move the camera backward
3. Press 'LEFT ARROW KEY' to move the camera to the left
4. Press 'RIGHT ARROW KEY' to move the camera to the right
5. Press 'PAGE UP' to move the camera upward
6. Press 'PAGE DOWN' to move the camera downward
7. Hold the right-mouse button and drag the mouse to change the orientation of the camera
8. Press 'R' to reset the camera position


## Section 2
### Implementation and Features

1. The functions that contains the logic for the Fuzzy Logic algorithm can be found in:
FuzzyLogicMissile.h, FuzzyLogicMissile.cpp
2. The math functions created and used for the Fuzzy Logic can be found in:
MathUtility.h, MathUtility.cpp
3. The graphical user interface and game implementation of the Missile game can be found in:
MissileGameDriver.h, MissileGameDriver.cpp, MyGeometryState.h and MyGeometryState.cpp
4. You can change toggle the day and night effect by pressing 'U'.  You can refer to section 1 for other controls that you may want to try out.
5. The collision between the plane and the wall was implemented using real physics collision however, 
the plane may go out if you manually control it to force it out of the wall
6. The game is built using my 3D game engine that supports lighting and render effects.  
Feel free to move the camera and navigate through the 3D environment to enjoy the view.


