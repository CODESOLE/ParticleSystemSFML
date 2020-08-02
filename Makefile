c:
	clear;g++ -O3 main.cpp imgui/imgui.cpp imgui/imgui_demo.cpp imgui/imgui_draw.cpp imgui/imgui_widgets.cpp imgui-sfml/imgui-SFML.cpp  Random.cpp Particle.cpp -o main -lGL -lsfml-graphics -lsfml-window -lsfml-system;./main;rm ./main
