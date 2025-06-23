#pragma once
#include "core.hpp"
#include <cstdlib>
#include <raylib.h>
#include <sstream>
#include <string>
#include <vector>
class EngineContext;

std::vector<std::string> splitByWhitespace(const std::string &input);
class DebugManager;
class DebugFeature {
public:
  DebugFeature() {}
  std::string command;
  std::string description;
  virtual int draw(EngineContext *context [[maybe_unused]]) { return 0; }
  virtual int call(std::vector<std::string> arguments [[maybe_unused]],
                   DebugManager *debugManager [[maybe_unused]]) {
    return 0;
  }
};
class DebugManager {
public:
  bool alwaysDraw;
  std::string inputText;
  std::string output;
  std::vector<DebugFeature *> debugFeatures;
  DebugManager() {}
  void finish_init() {
    print("zEngine debug console v." + (std::string)ZENGINE_VERSION +
          "\nType `help` for help\n");
    print(std::to_string(debugFeatures.size()) + " methods\n");
  }
  void print(std::string text) { output += text; }
  void update() {
    char pressed = GetCharPressed();
    if (pressed != 0) {
      inputText.push_back(pressed);
    }
    if (IsKeyPressed(KEY_ENTER) && inputText.length() > 0) {
      output.push_back('>');
      output += inputText;
      output.push_back('\n');
      parseCommand();
      inputText.clear();
    }
    if (IsKeyPressed(KEY_BACKSPACE) && inputText.length() > 0) {
      inputText.pop_back();
    }
  }
  void draw() {
    DrawRectangleV(Vector2{(float)GetScreenWidth() / 2.f + 10.f, 10.f},
                   Vector2{(float)GetScreenWidth() / 2.f - 20.f,
                           (float)GetScreenHeight() - 20.f},
                   GRAY);
    DrawRectangleLinesEx(Rectangle{(float)GetScreenWidth() / 2.f + 12.f, 12.f,
                                   (float)GetScreenWidth() / 2.f - 24.f,
                                   (float)GetScreenHeight() - 24.f},
                         5, BLACK);
    DrawRectangle(GetScreenWidth() / 2 + 20, GetScreenHeight() - 50,
                  GetScreenWidth() / 2 - 40, 30, WHITE);

    // draw console
    DrawText(output.c_str(), GetScreenWidth() / 2 + 21, 16, 20, BLACK);

    // draw input
    std::string drawnText = inputText;
    while (MeasureText(drawnText.c_str(), 28) > GetScreenWidth() / 2 - 50) {
      drawnText.erase(0, 1);
    }
    DrawText(drawnText.c_str(), GetScreenWidth() / 2 + 21,
             GetScreenHeight() - 51, 28, BLACK);
  }
  void parseCommand() {
    if (inputText == "help") {
      print(std::to_string(debugFeatures.size()) + " methods:\n");
      for (auto &feature : debugFeatures) {
        print(feature->command + ": " + feature->description + "\n");
      }
    } else {
      std::vector<std::string> input = splitByWhitespace(inputText);
      bool broken = false;
      for (auto &feature : debugFeatures) {
        if (splitByWhitespace(inputText).size() > 0) {
          if (feature->command == input[0]) {
            feature->call(input, this);
            broken = true;
            break;
          }
        }
      }
      if (!broken) {
        print("unknown command\n");
      }
    }
  }
  void addDebugFeature(DebugFeature *f) { this->debugFeatures.push_back(f); }
};
