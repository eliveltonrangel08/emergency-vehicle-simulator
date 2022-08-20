# urban_mobility_simulator

(TODO: Improve this tutorial)

This project is a start to SUMO/VEINS/OMNETPP simulation environment.

Follows this tutorial to set-up your entire environment in a Docker image and run a container to use it.


Step 1: setup your SSH-KEY to this repository following these tutorials: 
 - [Generating public and private ssh keys](https://docs.github.com/en/authentication/connecting-to-github-with-ssh/generating-a-new-ssh-key-and-adding-it-to-the-ssh-agent)
 - [setting-up your public key-gen on the project](https://docs.github.com/en/authentication/connecting-to-github-with-ssh/adding-a-new-ssh-key-to-your-github-account)
 
Step 2: clone the repository in your computer:
 - `cd <path_to_your_project_directory>`
 - `git clone git@github.com:eliveltonrangel08/urban_mobility_simulator.git`
 
Step 3: build the project image:
 - Open your terminal and run the command:
 - `make setup`
 
Step 4: create an docker container and run it:
 - `make run-bash`
 
Step 5: run the omnetpp simulator:
 - `./scripts/entrypoints.sh omnet`
 
Step 6: run the sumo_veins interface simulator:
 - `./scripts/entrypoints.sh sumo_veins`
 
 
========== Map of files ==========

- Projects: responsibe do store the projects
- scripts: responsible to map and run some applications inside the docker container
- Dockerfile:
- Makefile: 

========== Creating new projects ==========

[IN PROGRESS...]

To create a new veins-based project you need to start it using the 'cookiecutter approach', as recommended in the [Veins tutorial](https://veins.car2x.org/tutorial/).
So, follow the steps above:
- `cd projects`
- `python3 -m cookiecutter gh:veins/cookiecutter-veins-project`
- Inform the values requireds and the frameworks that you would like to use in your new project 

