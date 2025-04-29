#ifndef KITCHEN_H
#define KITCHEN_H

#include "Point.h"

class Kitchen{
public:
  Kitchen();
  void createElectronicsRoom(float height , float width , float depth);
  void createKitchenRoom(float height , float width , float depth, int kitchen_wall , int kitchen_floor , int fridge_side_texture , int fridge_front_textureint, int washing_machine_side_texture, int washing_machine_front_texture, int microwave_front_texture,int shelf_texture, int oven_front_texture, int title_texture );
  void creategamingsRoom(float height , float width , float depth);
  void createLibraryRoom(float height , float width , float depth);
  void drawFridge(Point start, float width, float height, float depth, int side_texture, int front_texture);
  void drawWashingMachine(Point start, float width, float height, float depth, int side_texture, int front_texture);
  void drawMicrowave(Point start, float width, float height, float depth, int side_texture, int front_texture);
  void drawShelf(Point start, float width, float height, float depth, int texture);
  void drawOven(Point start, float width, float height, float depth, int side_texture, int front_texture);
  void drawMallFloor(Point start, float width, float depth, int floor_texture);
  void createMallLand(float floor_width, float floor_depth, int floor_texture);
};

#endif
