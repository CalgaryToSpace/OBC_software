# CalgarytoSpace Software 

## Folder Structure
  [Workspace]  	- The Operating System for the Satellite
  
  [Examples] 	- Contains demo projects for specific functions such as UART, SPI,  Task Management, etc
  
  [Tools]	- Simulators and other testing tools

## Getting Started
  #### Downloads 
- [STM32 CubeIDE - Integrated Development Environment Download](https://www.st.com/en/development-tools/stm32cubeide.html)
- [Git Bash Download ](https://git-scm.com/downloads)
- [Visual Studio Code](https://code.visualstudio.com/) (Optional) 

#### Hardware
- STM32L4R5ZI Nucleo-144
- Micro-USB Cable

#### Guides
[GIT Tutorial](https://docs.google.com/presentation/d/1wr_xPIai-Gg8E0KEQzC6v0hETkPaw800/edit#slide=id.p1)
[STM32 Nucleo Guide](https://www.youtube.com/watch?v=hyZS2p1tW-g&list=PLEBQazB0HUyRYuzfi4clXsKUSgorErmBv) 
[STM32 - FreeRTOS Guide](https://www.digikey.ca/en/maker/projects/getting-started-with-stm32-introduction-to-freertos/ad275395687e4d85935351e16ec575b1)

## Code Push and Review Process

#### Creating and Submitting a Pull Request
1) Update your local repo with `git pull origin master` 
2) Create a working branch with `git checkout -b MyNewBranch`
3) Make your changes on your branch and stage them with `git add .` to stage all changes. 
4) Commit your changes locally with `git commit -m "description of your commit"`
5) Make as many commit as needed to implement the change/feature 
6) Upload the changes (including your new branch) to GitHub with `git push origin MyNewBranch`
7) Go to the main repo on GitHub where you should now see your new branch
8) Click on your branch name
9) Click on “Pull Request” button to 
10) Click on “Send Pull Request” to development/main 
11) Have Pull request reviewed by 3 people
12) Pull request is good to submit after 3 "Approves"

#### Commit Message Format:
- Short Title
- Concise Description
- Testing used to verify the change

#### Modifying an Existing Pull Request
1) Make changes and stage them with `git add .` 
2) Then use `git commit –-amend --no-edit` to modify the previous commit without changing the commit message
3) Upload the changes (including your new branch) to GitHub with `git push origin MyNewBranch`
4) Update the pull request with the new changes

#### Reviewing a Pull Request:
1) Look over the code and also the commit message. Ensure changes are not out of the scope of the commit message
2) Leave comments for any questions or things you think needs changing
3) If you think its good to submit, comment "Approved"
4) If you think its not good to submit, comment "Revise"
