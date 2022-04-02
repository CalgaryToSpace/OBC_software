Code Review Process

Creating and Submitting a Pull Request
1) Update your local repo with git pull origin master,
2) Create a working branch with git checkout -b MyNewBranch
3) Make your changes on your branch and stage them with git add . to stage all changes. 
4) Commit your changes locally with git commit -m "description of your commit"
5) Upload the changes (including your new branch) to GitHub with git push origin MyNewBranch
6) Go to the main repo on GitHub where you should now see your new branch
7) Click on your branch name
8) Click on “Pull Request” button to 
9) Click on “Send Pull Request” to development/main 
10) Have Pull request reviewed by 3 people
11) Pull request is good to submit after 3 "Approves"

Commit Message Format:
-Short Title
-Concise Description
-Testing used to verify the change

Modifying an Existing Pull Request
1) Make changes and stage them with git add . 
2) Then use git commit –-amend --no-edit to modify the previous commit without changing the commit message
3) Upload the changes (including your new branch) to GitHub with git push origin MyNewBranch
4) Update the pull request with the new changes

Reviewing a Pull Request:
1) Look over the code and also the commit message. Ensure changes are not out of the scope of the commit message
2) Leave comments for any questions or things you think needs changing
3) If you think its good to submit, comment "Approved"
4) If you think its not good to submit, comment "Revise"
