# lyrebird-new

A few years back I had a very interesting assignment at school. The assignment was split into 4 parts:
1. A cryptology function that decrypts tweets using some formulas
2. Running the same function on multiple processes
3. Having a server hand the file to a client, and the client would run the same function
4. Having the server hand the file to multiple clients

The project was done in C, and aimed for the Unix OS. You can find my old assignment here: https://github.com/AbdullahJasim/lyrebird-new
I wanted to redo the project using C++ and for the Windows OS. For the sake of time and since I will be the only one using this project, I decided to ignore several corner cases and invalid scenarios (nobody is grading me after all). There is a chance that I will go back and create some guards for them later on.

Some corner cases to implement guards / test for later:
1. Empty config file
2. More than 2 files specified
3. Invalid input/out files
4. Empty input file
5. Very long directory for input file
6. Invalid characters in tweet
7. Extremely long tweet
8. Tweet length not multiple of 6
9. Client disconnecting before receiving file
10. Client disconnecting before sending decrypted file
11. Server disconnecting
12. Server sends message longer than buffer
13. Client sends message longer than buffer
14. Too many clients connecting to server
15. No clients connecting to server

Currently I feel like the project is more or less done. Overall I am very happy with my code. This time I had a clear plan from the
beginning, and it helped make my code very modular. Some parts were more difficult, such as the Winsock library which was significantly 
more difficult to use than the Unix C one. However, building modular code helped me make changes and refactor the code easily.

I plan to use most of these classes in a later project. My aim is to create a raytracer to understand graphics and their pipeline. Then to create a simple game engine in DirectX to learn the low level concepts of game engines. Hopefully I can eventually bring all the ideas together.

My next two projects can be found here:
https://github.com/AbdullahJasim/Raytracer
https://github.com/AbdullahJasim/FishEatFish-new
