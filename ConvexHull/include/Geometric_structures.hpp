#ifndef Geometric_structures
#define Geometric_structures

#include "Stack.hpp"
#include "errors.hpp"


//Declara o TAD ponto
struct point {
    int x;
    int y;

};

//Declara o TAD reta
class line{
    public:

    string equation();

    void create(point a, point b);

    private:
        float alpha, beta;
};

//Declara o TAD fecho convexo 
class ConvexHull{
    public:

    Stack<point> Graham_merge(point points[], int size);
    Stack<point> Graham_inserction(point points[], int size);
    Stack<point> Graham_bucket(point points[], int size);
    Stack<point>Jarvis(point points[], int size);

};




#endif