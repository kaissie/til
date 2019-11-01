# Undestanding
## Start own repository
~~~
git init
~~~
This will create a hidden .git folder inside my current folder:this is the "**repository**"(or **repo**) where git sotres all of its internal tracking data.

:sparkles: The current folder is now referred to as our **working directory**.
## **Clone** an exisiting repo
~~~
git clone https://github.com/kaissie/desktop-tutorial.git
~~~
This will download .git repository from the internet (GitHub) and extract the latest snapshot of the repo(all the files).

:sparkles: The URL I specify here is called the **remote origin**.
## View the current **status** of my project
~~~
git status
~~~
This will print some basic information.C
## Create a new **branch** name
~~~
git branch <new-branch-name>
~~~
I can think of this like <u>creating a local checkpoint</u> (technically called a **reference**) and giving it a name.<br>
It's similar to doing **File > Save as...** in a text editor.

:sparkles: That's really the core function of git: To save checkpoints(revisions) and share them with other people.
## **Check out** a particular branch
~~~
git check out <existing-branch-name>
~~~
This is like "resuming" from an existing checkpoint. 

:grey_exclamation: This command can use the -b flag as a shortcut to `git branch <new-branch>` and then `git checkout <new-branch>` all in one step.
~~~
git checkout -b <new-branch>
~~~
## View the **differences** between checkpoints
~~~
git diff <branch-name> <other-branch-name>
~~~
After editing some files, you can simply type git diff to view a list of the changes you've made.
## **Stage** your changes to prepare for committing them
~~~
git add <files>
~~~
After editing some files, this command will mark any changes you've made as "staged"(or "ready to be committed").
## **Commit** your staged changes
~~~
git commit
~~~
This will saveyour changes to the local repository.

:grey_exclamation: This command can use the -m flag as a shortcut to write a message.
~~~
git commit -m "Add a new feature"
~~~


### References

[ステージを理解して git をもっと便利に使う - 誰得UNIX](http://daretoku-unix.blogspot.com/2009/08/git.html)
[Understanding Git (part 1) — Explain it Like I’m Five](https://hackernoon.com/understanding-git-fcffd87c15a3)
