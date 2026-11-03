#pragma once
#include <stdexcept>
#include <string>

class GameException : public std::runtime_error {
public:
    explicit GameException(const std::string& message) : std::runtime_error(message) {}
};

class FieldLimitException : public GameException {
public:
    explicit FieldLimitException()
        : GameException("[Исключение] Превышен лимит юнитов на поле!") {
    }
};

class OutOfBoundsException : public GameException {
public:
    OutOfBoundsException(int x, int y, int w, int h)
        : GameException("[Исключение] Координаты (" + std::to_string(x) + ", " + std::to_string(y) +
            ") выходят за границы поля " + std::to_string(w) + "x" + std::to_string(h) + "!") {
    }
};

class CellOccupiedException : public GameException {
public:
    CellOccupiedException(int x, int y)
        : GameException("[Исключение] Клетка (" + std::to_string(x) + ", " + std::to_string(y) + ") уже занята!") {
    }
};

class ObjectNotFoundException : public GameException {
public:
    ObjectNotFoundException(int x, int y)
        : GameException("[Исключение] В клетке (" + std::to_string(x) + ", " + std::to_string(y) + ") нет объектов для удаления!") {
    }
};
