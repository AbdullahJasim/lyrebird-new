# lyrebird-new

A few years back I had a very interesting assignment at school. The assignment was split into 4 parts:
1. A cryptology function that decrypts tweets using some formulas
2. Running the same function on multiple processes
3. Having a server hand the file to a client, and the client would run the same function
4. Having the server hand the file to multiple clients

The project was done in C, and aimed for the Unix OS. You can find my old assignment here: https://github.com/AbdullahJasim/lyrebird-new

I wanted to redo the project using C++ and for the Windows OS. For the sake of time and since I will be the only one using this project, I
decided to ignore several corner cases and invalid scenarios. There is a chance that I will go back and create some guards for them later
on.


Currently I feel like the project is more or less done. Overall I am very happy with my code. This time I had a clear plan from the
beginning, and it helped make my code very modular. Some parts were more difficult, such as the Winsock library which was significantly 
more difficult to use than the Unix C one. However, building modular code helped me make changes and refactor the code easily.

I plan to use most of these classes in a later project. My aim is to create a raycaster to render objects in OpenGL. Then to use
that raycaster to make a simple game, and finally use this project to handle server and client communication to transfer game data.

My next two projects can be found here:
https://github.com/AbdullahJasim/RayCaster
https://github.com/AbdullahJasim/FishEatFish-new
