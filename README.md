🚦 Four-Way Junction Traffic Management System
This project implements a queue-based traffic management simulation for a four-way junction, designed to simulate traffic flow with normal and priority lanes using a vector-based queue system. The simulation includes dynamic vehicle generation, traffic light control, and vehicle movement based on traffic conditions.

![image](https://github.com/user-attachments/assets/5c1019b1-c016-4085-8bb7-3b4b011b30f9)


📋 Project Overview
The traffic simulation system manages normal and high-priority vehicle dispatch using queue data structures. Traffic flow is controlled by dynamically adjusting traffic lights based on traffic conditions and vehicle locations. Vehicles are processed in a queue system, where priority lanes are handled differently from normal lanes to simulate emergency vehicles or other high-priority traffic.

Key Features
🚗 Queue-based Traffic Management: Vehicles are managed in queues for each lane and processed based on traffic light conditions and lane priority.

🚨 Priority Lane Handling: Vehicles in priority lanes move faster than those in normal lanes to simulate emergency vehicles.

🖥️ Real-time Visualization: The simulation uses Raylib for graphical representation.

⚙️ Dynamic Traffic Light Control: Traffic lights rotate every 100 frames, controlling vehicle flow.

🏗️ System Architecture

Traffic Management Rules
Normal Condition: Traffic lights switch based on a round-robin pattern every 100 frames, ensuring fair service to all lanes.

Priority Condition: Vehicles in priority lanes move faster than those in normal lanes to simulate urgent traffic (e.g., emergency vehicles).

Vehicle Stopping Condition: Vehicles stop when their respective light is red and they haven't passed the 40% threshold on their path.

Core Components
Vehicle Generator: Dynamically creates vehicle data and adds it to the vehicle queue.

Traffic Simulator: Manages vehicle movement, traffic light changes, and lane conditions based on vehicle positions.

Visualization: Real-time rendering of vehicles, traffic lights, and lanes on the screen.

📊 Data Structures
Structure	Implementation	Purpose
std::vector<Vehicle>	Vector-based (acting as a queue)	Storing vehicles in a queue-like manner for each lane
Vehicle	Struct	Contains vehicle information such as position, speed, and priority lane type
TrafficLight	Struct	Manages traffic light state (green/red) for each lane
Priority and Normal Lanes
Priority Lane: Vehicles in these lanes are assigned a higher speed to simulate emergency or high-priority traffic.
Normal Lane: Vehicles in these lanes move at a default speed.
⚙️ Algorithm Design
The algorithm follows these steps:

Vehicle Creation: New vehicles are generated based on traffic light status, and they are added to the corresponding lane's queue.
Traffic Light Update: Every 100 frames, the traffic light changes in a round-robin manner, controlling vehicle flow.
Vehicle Movement: Vehicles move based on their direction (left, right, top, or bottom). Priority vehicles move faster.
Vehicle Processing: Vehicles in the queue are processed in FIFO order. If a vehicle's corresponding light is red and it hasn't crossed the 40% threshold of its path, it stops.
Visualization: The screen is updated every frame to render the vehicles, traffic lights, and lanes.

📊 Time Complexity Analysis
Queue Operations (enqueue, dequeue): O(1)
Traffic Light Update: O(n), where n is the number of lanes
Vehicle Movement: O(n), where n is the number of vehicles
Overall Time Complexity: O(n), where n is the number of vehicles processed in the simulation.

💻 Implementation Details
Key Functions
Queue Operations:
void enqueue(std::vector<Vehicle>& vehicles, Vehicle v);
Vehicle dequeue(std::vector<Vehicle>& vehicles);
bool isEmpty(std::vector<Vehicle>& vehicles);
Traffic Management:
void updateTrafficLights(TrafficLight* lights);
void processVehicles(std::vector<Vehicle>& vehicles);
Visualization:
void drawTrafficLights(TrafficLight* lights);
void drawVehicles(std::vector<Vehicle>& vehicles);
void drawBackground();
Vehicle Generation:
void createVehicle();
void updateVehicles(std::vector<Vehicle>& vehicles);

🚀 Installation and Setup
Prerequisites
C++ compiler (GCC or MinGW)
Raylib graphics library
Git (optional, for cloning the repository)
Installation Steps
1. Install Raylib on Ubuntu/Debian
bash
Copy
Edit
sudo apt-get install libraylib-dev
2. Install Raylib on macOS using Homebrew
bash
Copy
Edit
brew install raylib
3. Install Raylib on Windows
Download Raylib from https://www.raylib.com
Building the Project
1. Clone the Repository
bash
Copy
Edit
git clone https://github.com/YOUR_USERNAME/four-way-junction-traffic-simulation.git
cd four-way-junction-traffic-simulation
2. Compile the Code
bash
Copy
Edit
g++ -o bin/main src/main.cpp src/traffic_simulation.cpp -lraylib -lm -lpthread -ldl -lrt -lX11
Running the Program
bash
Copy
Edit
./bin/main


📄 License
This project is licensed under the MIT License - see the LICENSE file for details.

# Raylib-CPP-Starter-Template-for-VSCODE-V2
Raylib C++ Starter Template for Visual Studio Code on Windows.
This demo project contains a bouncing ball raylib example program.
It works with raylib version 5.0. Tested on both Windows 10 and Windows 11.

# How to use this template
1. Double click on the main.code-workspace file. This will open the template in VS Code.
2. From the Explorer Window of VS Code navigate to the src folder and double click on the main.cpp file.
3. Press F5 on the keyboard to compile and run the program.

# What's changed
The template now uses folders for better organizion of the files. So, all the source code now lives in the src folder.

# Video Tutorial

<p align="center">
  <img src="preview.jpg" alt="" width="800">
</p>

<p align="center">
🎥 <a href="https://www.youtube.com/watch?v=PaAcVk5jUd8">Video Tutorial on YouTube</a>
</p>

<br>
<br>
<p align="center">
| 📺 <a href="https://www.youtube.com/channel/UC3ivOTE5EgpmF2DHLBmWIWg">My YouTube Channel</a>
| 🌍 <a href="http://www.programmingwithnick.com">My Website</a> | <br>
</p>
