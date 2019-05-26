//
// Created by jsier on 17/05/2019.
//

#include "Value.h"

Value::Value(double number, Value::Type type)
    : type(type)
    , number(number)
{}

Value::Type Value::getType() const {
    return type;
}

double Value::getDouble() const {
    return number;
}

double Value::calculate(double original) {
    if (type == Type::PERCENT) {
        return number * original;
    }
    return number;
}
