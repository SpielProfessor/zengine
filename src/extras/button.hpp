#include "../../include/zEngine.hpp"
#include <memory>
#include <vector>
#pragma once

class Button : public Actor {
public:
  std::string text = "";
  Color color = WHITE;
  int fontSize = 30;
  bool highlight = false;
  void (*callback)(Scene *sceneLink) = 0;
  std::string hlLeft = "> ";
  std::string hlRight = " <";
  Button(std::string text_, void (*callback_)(Scene *sceneLink), Vector2 pos_,
         int fontSize_)
      : text(text_), fontSize(fontSize_) {
    this->position = pos_;
    callback = callback_;
  }
  void draw() override {
    if (highlight) {
      DrawText(hlLeft.c_str(),
               getGlobalX() - MeasureText(hlLeft.c_str(), fontSize),
               getGlobalY(), fontSize, color);
      DrawText(hlRight.c_str(),
               getGlobalX() + MeasureText(text.c_str(), fontSize), getGlobalY(),
               fontSize, color);
    }
    DrawText(text.c_str(), getGlobalX(), getGlobalY(), fontSize, color);
  }
  void update(float delta [[maybe_unused]]) override {
    this->dimensions =
        Vector2{(float)MeasureText(text.c_str(), fontSize), (float)fontSize};
    Vector2 mouse = GetVirtualMousePosition(GetScreenWidth(), GetScreenHeight(),
                                            sceneLink->ctxLink->vWidth,
                                            sceneLink->ctxLink->vHeight);
    if (CheckCollisionPointRec((Vector2){mouse.x, mouse.y},
                               (Rectangle){getGlobalX(), getGlobalY(),
                                           dimensions.x, dimensions.y})) {
      highlight = true;
      if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        if (callback != 0 && sceneLink != 0) {

          callback(sceneLink);
        }
      }
    } else {
      highlight = false;
    }
  }
};

class ButtonMenu : public Actor {
public:
  std::vector<Button *> buttons;
  int fontSize = 30;
  int zindex = 30000000;
  ButtonMenu(float x, float y) { position = (Vector2){x, y}; }
  void addButton(std::string text_, void (*callback_)(Scene *sceneLink)) {
    position =
        (Vector2{position.x / 2.f,
                 (float)buttons.size() * (float)fontSize + (position.y / 2.f)});
    buttons.push_back((Button *)addChild(
        std::make_unique<Button>(text_, callback_, position, fontSize)));
    for (auto &button : buttons) {
      button->zindex = zindex;
    }
  }
};
