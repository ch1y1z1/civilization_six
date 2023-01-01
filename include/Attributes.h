#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H


struct Attributes
{
    float tech = 0.0;
    float cul = 0.0;
    float food = 0.0;
    float prod = 0.0;
    Attributes() {}
    Attributes(float t, float c = 0.0, float f = 0.0, float p = 0.0):tech(t), cul(c), food(f), prod(p) {}
    Attributes operator+(const Attributes& a) const {
        Attributes tmp(a);
        tmp.tech += this->tech;
        tmp.cul += this->cul;
        tmp.food += this->food;
        tmp.prod += this->prod;
        return tmp;
    }
    Attributes operator+=(const Attributes& a) {
        Attributes tmp(a);
        *this = *this + tmp;
        return *this;
    }
    Attributes operator*(const float n) const {
        Attributes tmp;
        tmp.tech = tech * n;
        tmp.cul = cul * n;
        tmp.food = food * n;
        tmp.prod = prod * n;
        return tmp;
    }
    Attributes operator-(const Attributes& a) const {
        Attributes tmp(a);
        tmp.tech -= this->tech;
        tmp.cul -= this->cul;
        tmp.food -= this->food;
        tmp.prod -= this->prod;
        return tmp;
    }
    Attributes operator-=(const Attributes& a) {
        Attributes tmp(a);
        *this = *this - tmp;
        return *this;
    }
};

#endif // ATTRIBUTES_H
