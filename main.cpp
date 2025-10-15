#include <iostream>
#include <thread>
#include <chrono>
#include "Spacecraft.hpp"
#include "Input.hpp"

void render(const Spacecraft& s) {
    std::cout << "\033[H\033[J"; // clear
    std::cout << "---------------- SPACECRAFT INSTRUMENT PANEL ----------------\n";
    std::cout << "POS:  X=" << s.pos.x << "  Y=" << s.pos.y << "  Z=" << s.pos.z << "\n";
    std::cout << "VEL:  VX=" << s.vel.x << "  VY=" << s.vel.y << "  VZ=" << s.vel.z << "\n";
    std::cout << "ATT:  Pitch=" << s.pitch << "°  Yaw=" << s.yaw << "°\n";
    std::cout << "THR:  " << s.thrust * 100 << "%   Engine: " << (s.engine_on ? "ON" : "OFF") << "\n";
    std::cout << "FUEL: " << s.fuel << "%\n";
    std::cout << "--------------------------------------------------------------\n";
    std::cout << "Controls: W/S=Pitch  A/D=Yaw  T/G=Thrust  SPACE=Engine  Q=Quit\n";
}

int main() {
    Spacecraft s;
    bool running = true;

    while (running) {
        char c = getch_noblock();
        switch (c) {
            case 'w': s.pitch += 1; break;
            case 's': s.pitch -= 1; break;
            case 'a': s.yaw -= 2; break;
            case 'd': s.yaw += 2; break;
            case 't': s.thrust = std::min(1.0, s.thrust + 0.05); break;
            case 'g': s.thrust = std::max(0.0, s.thrust - 0.05); break;
            case ' ': s.engine_on = !s.engine_on; break;
            case 'q': running = false; break;
            default: break;
        }

        s.update();
        render(s);
        std::this_thread::sleep_for(std::chrono::milliseconds(int(DT * 1000)));
    }

    std::cout << "Simulation ended.\n";
    return 0;
}
