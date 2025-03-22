# OpenGL Superbible 6 (Personal Learning Project)
This is a personal project that I'm working on along with the book
OpenGL Superbible 6th edition.

## How to Compile:

**Clone The Project:**
```
git clone https://github.com/babaliaris/learnWithOpenGL_Superbible6.git
```

Generate the project files using [premake5](https://premake.github.io/). How to use premake: [Using Premake](https://premake.github.io/docs/Using-Premake/) 
```
cd <repo_dir>
premake5 <action>
```
Then open your project solution or whatever file(s) you generate with premake and compile.

### Linux Example:
First, change the directory `cd <$repo_dir>` to your cloned repository directory, and then:

```
premake5 gmake2 && make
```

The above line will generate GNU's makefiles and will execute "make" in order to build the project.

### Cleaning
```
make clean
```
You can also manually delete the **<$repo_dir>/builds** and **<$repo_dir>/obj** directories.

## How To Run:
**Unix Systems:** `./sandbox.sh`.
