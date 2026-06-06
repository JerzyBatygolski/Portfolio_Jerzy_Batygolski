# Portfolio Jerzy Batygolski

Hello, this is portfolio of my programming projects. Let's check it out :)

## AI/ML

1. A production-grade AI/ML system that classifies household waste images into one of **10 categories** using deep learning. Built end-to-end — from model training to cloud deployment — as a full-stack ML engineering project.

<img width="1920" height="1632" alt="Glass" src="https://github.com/user-attachments/assets/500ab8ab-f05d-4bf8-9f4b-cb9aa5d40141" />

**Live demo:** https://waste-classifier-ui-943543256910.europe-central2.run.app
> ℹ️ The service uses cold-start Cloud Run instances. The first request may take ~30 seconds; subsequent requests are fast. On the mobile devices it is recommended to add an image from the gallery rather than making a photo online due to known Streamlit limitations.

**Project repository:** https://github.com/JerzyBatygolski/Waste_classifier

**Tech stack:** 
| Layer | Technologies |
|---|---|
| ML | Python, TensorFlow 2.x / Keras, MobileNetV2, scikit-learn |
| API | FastAPI, Uvicorn, Docker |
| Frontend | Streamlit |
| Cloud | Google Cloud Run, Artifact Registry |
| IaC | Terraform |

## Physics

2. Simulation of an ideal gas in a box. We can see how 10 000 of particles, starting from random initial positions and orientations, but having the same magnitudes of velocities, reaches the Maxwell-Boltzmann distribution of speeds. If we add gravity and temperature gradient (e.g. heating at the bottom and cooling at the top), the particles tend to self-organize and start to move in a convection roll.

**Tech stack:** C, Wolfram Mathematica, Matlab, kinetic theory, statistical physics

![hist1](https://user-images.githubusercontent.com/58355098/210148843-c3e74f54-6801-480a-a5f7-dcc5eac46050.png)

![hist2](https://user-images.githubusercontent.com/58355098/210149036-abc5c0e1-634b-453b-ad13-38fe8f17923e.png)

3. Simulation of an Ising-doped voter model on a square lattice. The simulation was a part of my scientific paper in Physical Review:
https://journals.aps.org/pre/abstract/10.1103/PhysRevE.105.064120

**Tech stack:** C, Wolfram Mathematica, Matlab, Linux

![ising1](https://user-images.githubusercontent.com/58355098/210149491-746348dd-37ef-43c5-bd37-b521cf5cc0ef.PNG)

![ising2](https://user-images.githubusercontent.com/58355098/210149492-89d5f808-0837-49f6-a120-aec681fef00b.PNG)

## Robotics

4. Two-wheeled mobile robot controlled from a smartphone app. Robot measures the distance to the nearest obstacle and shows it in app.

**Tech stack:** Arduino, Bluetooth, MIT App Inventor 2, electronic circuits

![1](https://user-images.githubusercontent.com/58355098/210149827-46e7e568-acd1-494a-8d66-33e246cff5c3.png)
![3](https://user-images.githubusercontent.com/58355098/210149715-88effbaa-9d87-4f0a-8542-269689ba47b0.png)
![5](https://user-images.githubusercontent.com/58355098/210149781-78cc743e-0d0c-4ad4-bfcc-421800192c89.PNG)
![6](https://user-images.githubusercontent.com/58355098/210149719-e6154aac-11a9-4fad-baf4-593295581e9f.PNG)

![7](https://user-images.githubusercontent.com/58355098/210149720-5b6fd69a-5215-47cb-b99b-da5ead88aa67.PNG)

![8](https://user-images.githubusercontent.com/58355098/210149722-eb5bc72e-e3db-44e9-8b9f-83f47018e7cc.PNG)

## Embedded systems

5. Cubic dice randomness tester - electronic circuit design with ATmega328P microprocessor. If you play boardgames with friends, you can check if you had luck or bad and saw statistics of your rolls.

**Tech stack:** Arduino, soldered electronic circuits

![cubic_dice1](https://user-images.githubusercontent.com/58355098/210137938-6819b901-d594-4b55-8fc3-05fa3c974b3f.png)

![cubic_dice2](https://user-images.githubusercontent.com/58355098/210137942-9cfeb8b8-0c82-4242-b386-8145a5080bb0.png)

## Complex simulations with industrial automation software

6. Simulation of an apple juice factory in a Codesys software. Code is written in ST language on Astraada PLC.  

**Tech stack:** Codesys, ST, PLC, thermodynamics

https://user-images.githubusercontent.com/58355098/210151134-c61ba448-6e9f-4cc5-8ace-4adb56bb6243.mp4

## Classical GUI applications

7. Traffic simulation with GUI, written in C++ in OOP paradigm. The main aim is to mimic real traffic with smoothness of car movements including collision avoidance.

**Tech stack:** Visual Studio C++, classical mechanics

![traffic_wideo](https://user-images.githubusercontent.com/58355098/211143696-071014e2-0670-47d1-be0c-018c83d86a3f.gif)
