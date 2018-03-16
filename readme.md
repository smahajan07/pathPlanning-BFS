## Standard install via command-line
```
git clone --recursive https://github.com/smahajan07/pathPlanning-BFS
cd pathPlanning-BFS
mkdir build
cd build
cmake ..
make
Run tests: ./test/cpp-test
Run program: ./app/shell-app
```

## Output

Sample output:  ![Sample Output](https://github.com/smahajan07/pathPlanning-BFS/blob/master/output/sampleOutput.png)

## Important side Notes

If you wish to change the start node or goal node, you can do it by editing the "main.cpp" file in "app folder" by by:

```
cd pathPlanning-BFS/app
nano main.cpp
```
The "goalNode" is a global variable and can be found in the beginning whereas the startX and startY variables can be changed to set the start node X and Y coordinates.
Also, the top left is considered (0,0). So please change accordingly.
