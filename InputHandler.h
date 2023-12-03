#pragma once

class InputHandler {
public:
  static InputHandler* Instance();

  void HandleEvents();
protected:
  InputHandler() {};
private:
  inline static InputHandler* _instance = nullptr;
};

typedef InputHandler TheInputHandler;
