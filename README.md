# apworks
my game development framework structure

- Pre compile for Linux(Client)：
    - sudo apt-get install libx11-dev（for glew）
	- sudo apt-get install libxext-dev (for SDL2)

- Compile:
    - your g++/msvc/clang must suport c++11
	- install cmake (version 3.0+)
	- compile client:
		- cd apworks/client
		- mkdir build
		- run command ``` "cmake .." ```
		- run command ``` "make" ```

- Run ``` client ```:
    - cd apworks/bin
    - run  command ``` "./nario" ``` (``` "./nario.exe" ``` for windows)

- Platform:
    - now: windows, linux, osx
    - <b>TODO</b>: android, iphone