#pragma once

#include <string>
#include <memory>

class GameObject {
protected:
    int x_coord;
    int y_coord;
    char map_symbol;
public:
    GameObject(int start_x, int start_y, char symbol)
        : x_coord(start_x), y_coord(start_y), map_symbol(symbol) {
    }

    virtual ~GameObject() = default;

    virtual std::unique_ptr<GameObject> clone() const = 0;
    virtual std::string get_type() const = 0;

    int get_x() const { return x_coord; }
    int get_y() const { return y_coord; }
    char get_symbol() const { return map_symbol; }

    void set_coordinates(int new_x, int new_y) {
        x_coord = new_x;
        y_coord = new_y;
    }
};