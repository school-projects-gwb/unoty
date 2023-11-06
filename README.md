# Unoty Engine

<div align="center">

[Project Collaborators](#project-collaborators) •
[Project Description](#project-description) •
[Rules](#rules) 

</div> 
  
## Project Collaborators
| **Naam**                  | **GitHub id**     | **E-mail address**              | **Studentennummer** |
|---------------------------|-------------------|---------------------------------|---------------------|
| Josh van Houts            | gunwunbun         | jpt.vanhouts@student.avans.nl   | 2182446             |
| Wessel van Dorsten        | raintje           | w.vandorsten@student.avans.nl   | 2153442             |
| Sjoerd van der Bok        | DoCNL             | sa.vanderbok@student.avans.nl   | 2113474             |
| Jacky Zheng               | GXZheng312        | gx.zheng@student.avans.nl       | 2164239             |
| Devlin van Asperdt        | Schooldoid        | daj.vanasperdt@student.avans.nl | 2187902             |
  
## Project Description
This repository serves to host the source code of the Unoty engine, our interpretation of the main assignment at
the center of the C++ minor, as presented by Avans Hogeschool.

## Getting Started

### Prerequisites
* C++ 17
* CMake 3.26.x
* CLion 2023.x

### Installation
CMake will automatically build the project and manage any required dependencies in a `cmake-build-debug` directory.

You can directly run the binary from there, or have your IDE of choice run it for you.

View INSTALL.md for more detailed instructions.

## Usage
The Unoty engine strives to provide a developer experience that is as close as possible to Unity, using C++ instead of C#.

This project is still in the early stage of development, and this section will be updated with concrete examples once we
have implemented some of the desired functionality.

## Rules

### Project Management
See our [JIRA board](https://unoty.atlassian.net/jira/software/projects/UNOTY/boards/1).

### Git Conventions
- Our main branch serves as our "release branch", and will be updated at the conclusion of every sprint.
  - This branch is protected, and requires 2 approvals on a pull request.
- Our develop branch is an unstable environment where you can find the most recent changes.
  - This branch is also protected, and requires 1 approval on a pull request.
- We use feature branches when working on on user stories. The name of these branches must be equal to their respective JIRA ticket, i.e. UNOTY-1.
  - When working on subtasks, we base our new branches on said feature branches and adhere to the same naming convention.
- Merge commits from feature branches must be squashed, to ensure that our commit history remains organized.

### Coding Conventions

#### Style guide
This project adheres to the [Google C++ style guide](https://google.github.io/styleguide/cppguide.html).

#### Core guidelines
Our code makes use of the [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines) as
described by Stroustrup and Sutter.

### Documenting code guidelines
Since Google Coding Standards recommend a comment format that's different from the recommended format of Doxygen, a slightly different style is used:
- Comments to describe classes and functions, both single and multi-line, start with `///`
  - This way it gets picked up by Doxygen when generating the documentation. 
- **Examples:** 
```c++
/// @brief Does Foo by performing x, y and z  
void Foo();

/// @brief I'm a pretty big, complicated function
///
/// This is an extended description
/// Even more descriptive text here
///
/// @param x Parameter description
void Bar(Foo x);

/// @brief I'm a short class description
class Foo;
```

### Documenting headers and functions
- Document public header classes and its functions, not implementation
  -  If there is a header that is non-public, also document it. 
- Not every function or class necessarily has to be documented unless it is not obvious or non-standard.
  - I.e. its generally not useful to document getters and setters.
- Try to document `how` some function does its logic instead of `what` it does.
- For example, the below @brief is not very useful and redundant:
```c++
/// @brief Processes Foo
void ProcessFoo()
```
- This would be a lot more useful:
```c++
/// @brief Processes Foo using Bar algorithm
void ProcessFoo()
```

### Documenting implementation
- Use `//` when doing regular code comments inside a function so that it gets excluded from Doxygen.
- **For example:**
```c++
void Foo(Bar x) {
  // Perform Foo on Bar
  x.Foo();
}
```
