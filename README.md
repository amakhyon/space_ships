# space_ships
3D drawn game using 2D physics built from scratch using openGL


for sound
download wav file "aliens.wav" and save it then change the directory in the function playSound to directory you have the sound in 


Description
Battle of spaceships is a 3D graphics, 2D physics multiplayer game where each player has a different mission, player 1 or the white spaceship scores a point whenever it catches a falling diamond it is the slower one , player 2 the red spaceship has more restrictions, if it touched a falling diamond it loses a score point and it has a counter for if it touched 3 consecutive falling diamonds it will respawn back to it’s original place, however if it managed to dodge falling diamonds and collide with player 1, it will gain 7 score points and player 1 will lose 7 score points, Scores of both players appear on top 
Whoever reaches 30 points first will win and a winning screen will appear declaring the winner.

Design

Spaceship
It consisted of a sphere, two cones and a torus encircling the sphere to mimic a spaceship.



Diamond

First a pyramid is drawn by drawing four different triangles in 3D space, then that pyramid is copied and reflected on z-axis to mimc a diamond, this diamond rotates clockwise, and another diamond is created with the same dimentions and coordinates but it rotates counter clockwise to give it a psychedelic effect.

Implementation
It was elementary that in order to produce all the falling diamonds and have collision detection at the same time, the diamonds had to be aware of both player’s positions all the time and to do that it had to be made into a class and later generate objects from it, these objects would then generate a few random aspects including: x-position, size, falling and speed then a few collision detection metrics had to be taken into consideration like when the diamond reaches the bottom of the screen it respawns up, and whenever it touches a player it also respawns up in the maximum Y coordinates, testing were done to get the right ranges of these random numbers that allows the game to be playable.
Collision detection in diamonds was implanted by using equations of opposite corners of an imaginary rectangle around each diamond and if a player is anywhere within that rectangle, an event is fired and suitable measures are taken.
Winning states, inorder to achieve them there was 2 flags, each one belonged to each player and it represented if that player won or not, if no one won yet then the game loop will continue rendering the game scene, if a player won however, a different winning screen will be shown and the game will no longer be rendered.
Scenery, after all objects were rendered, a screen-wide rectangle is generated with the dark blue to black gradient mimicking a sky as background, and random white points are generated presenting stars. 

