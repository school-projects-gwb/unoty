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
* CMake 3.26 or higher
* C++ 17
* CLion 2023.x

### Installation
CMake will automatically build the project and manage any required dependencies in a `cmake-build-debug` directory.

You can directly run the binary from there, or have your IDE of choice run it for you.

## Usage
The Unoty engine strives to provide a developer experience that is as close as possible to Unity, using C++ instead of C#.

This project is still in the early stage of development, and this section will be updated with concrete examples once we
have implemented some of the desired functionality.

## Rules

### Git Conventions
- Our main- and development branches are protected. 
    - Pushes to these branches require a pull request with 2 and 1 approvals, respectively.
      - When assigning reviewers, try to pick people who haven't worked on the feature in question.
- We use feature branches when working on user stories. These will be appended with the specific task being worked on.
  - Example: When working on input, create a branch called `input`, based on `develop`. When working on a specific task, i.e. controller support, create a branch based on the `input` branch called `input/controller`.
- Merge commits from feature branches must be squashed, to ensure that our commit history remains organized.

### Coding Conventions

#### Style guide
This project adheres to the [Google C++ style guide](https://google.github.io/styleguide/cppguide.html).

You can set this up in CLion by opening settings, going to Editor > Code Style > C/C++ and clicking the "Set from"
dropdown in the top right, and selecting Google from this list.

#### Core guidelines
Our code makes use of the [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines) as
described by Stroustrup and Sutter.

