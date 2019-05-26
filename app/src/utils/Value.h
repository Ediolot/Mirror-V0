//
// Created by jsier on 17/05/2019.
//

#ifndef MIRROR_APP_VALUE_H
#define MIRROR_APP_VALUE_H


class Value {
public:
    enum Type {
        NUMERIC, PERCENT
    };

private:
    double number;
    Type type;

public:
    explicit Value(double number, Type type = Type::NUMERIC);

    Type getType() const;
    double getDouble() const;

    double calculate(double original);
};


#endif //MIRROR_APP_VALUE_H
