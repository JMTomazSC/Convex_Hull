#include "../include/Geometric_structures.hpp"
#include "../include/functions.hpp"
#include "../include/Stack.hpp"
#include <iostream>



using namespace std;

//Gera a equação da errata baseado em seus parâmetros
string line::equation(){
    return to_string(this->alpha) + "x + " + to_string(this->beta) + " = y";
}

//Cria uma reta que passa entre os dois pontos de parâmetro
void line::create(point a, point b){
    if(b.x - a.x == 0){
        this->alpha = 1;
        this->beta = a.y;
        return;
    }
    float alpha = (b.y - a.y)/(b.x - a.x);
    float beta = a.y - alpha * a.x;

    this->alpha = alpha;
    this->beta = beta;
}

//Algoritmo de Graham utilizando o merge sort para ordenar os pontos
Stack<point> ConvexHull::Graham_merge(point points[], int size){
    Stack<point> S;

    int min = 0; 
    //Encontra o ponto inicial cujo critério é ter menor coordenada y e estar mais a esquerda 
    for(int i = 1; i < size; i++){
        if(points[i].y < points[min].y)min = i;
        else if(points[i].y == points[min].y && points[i].x < points[min].x)min = i;
    }

    //Troca os pontos no vetor e logo em seguida ordena
    functions::trade(points[0],points[min]);
    functions::mergeSort(points[0],points,1,size-1);
    point p0 = points[0];

    int m = 1;
    //Elimina possíveis pontos colineares que sobraram no vetor de pontos
    for(int i = 1; i < size; i++){
        while(i < size -1 && functions::relative_position(p0,points[i],points[i + 1])== 0)i++;

        points[m] = points[i];
        m++;
    }
    
    //Caso o numero de pontos seja insuficiente, retorna erro
    if(m < 3){
        not_enough_points error;
        error.size = m;
        throw error;
        return S;
    }

    //Empilha os 3 primeiros pontos 
    S.Empilha(points[0]);
    S.Empilha(points[1]);
    S.Empilha(points[2]);

    //Faz a varredura completa
    for(int i = 3; i < size; i++){
        while(S.size() > 1 && functions::relative_position(S.Next_to_top(), S.get_top(), points[i]) != 2)S.Desempilha();
        S.Empilha(points[i]);
    }

    return S;
}

//Algoritmo de Graham utilizando o insertion sort para ordenar os pontos
Stack<point> ConvexHull::Graham_inserction(point points[], int size){
    Stack<point> S;
    

    int min = 0; 
    //Encontra o ponto inicial cujo critério é ter menor coordenada y e estar mais a esquerda 
    for(int i = 0; i < size; i++){
        if(points[i].y < points[min].y)min = i;
        else if(points[i].y == points[min].y && points[i].x < points[min].x)min = i;
    }


    //Troca os pontos no vetor e logo em seguida ordena
    functions::trade(points[0],points[min]);
    functions::Insercao_otimizado(points[0],&points[1],size-1);
    point p0 = points[0];

    int m = 1;

    //Elimina possíveis pontos colineares que sobraram no vetor de pontos
    for(int i = 1; i < size; i++){
        while(i < size -1 && functions::relative_position(p0,points[i],points[i + 1])== 0)i++;

        points[m] = points[i];
        m++;
    }
    //Caso o numero de pontos seja insuficiente, retorna erro
    if(m < 3){
        not_enough_points error;
        error.size = m;
        throw error;
        return S;
    }
    //Empilha os 3 primeiros pontos
    S.Empilha(points[0]);
    S.Empilha(points[1]);
    S.Empilha(points[2]);

    //Faz a varredura completa
    for(int i = 3; i < size; i++){
        while(S.size() > 1 && functions::relative_position(S.Next_to_top(), S.get_top(), points[i]) != 2)S.Desempilha();
        S.Empilha(points[i]);
    }

    return S;
}

//Algoritmo de Graham utilizando o bucket sort para ordenar os pontos
Stack<point> ConvexHull::Graham_bucket(point points[], int size){
    Stack<point> S;

    int min = 0; 
    //Encontra o ponto inicial cujo critério é ter menor coordenada y e estar mais a esquerda 
    for(int i = 1; i < size; i++){
        if(points[i].y < points[min].y)min = i;
        else if(points[i].y == points[min].y && points[i].x < points[min].x)min = i;
    }

    //Troca os pontos no vetor e logo em seguida ordena
    functions::trade(points[0],points[min]);
    functions::bucketSort(&points[1],size-1,points[0]);
    point p0 = points[0];

    int m = 1;

    //Elimina possíveis pontos colineares que sobraram no vetor de pontos
    for(int i = 1; i < size; i++){
        while(i < size -1 && functions::relative_position(p0,points[i],points[i + 1])== 0)i++;

        points[m] = points[i];
        m++;
    }
    //Caso o numero de pontos seja insuficiente, retorna erro
    if(m < 3){
        not_enough_points error;
        error.size = m;
        throw error;
        return S;
    }
    //Empilha os 3 primeiros pontos
    S.Empilha(points[0]);
    S.Empilha(points[1]);
    S.Empilha(points[2]);

    //Faz a varredura completa
    for(int i = 3; i < size; i++){
        while(S.size() > 1 && functions::relative_position(S.Next_to_top(), S.get_top(), points[i]) != 2)S.Desempilha();
        S.Empilha(points[i]);
    }

    return S;
}

//Algoritmo Marcha de Jarvis
Stack<point>ConvexHull::Jarvis(point points[], int size){
    Stack<point> S;
    //Caso o numero de pontos seja insuficiente, retorna erro
    if(size < 3){
        not_enough_points error;
        error.size = size;
        throw error;
        return S;
    }


    int min = 0; 

    //Pega o ponto mais a esquerda 
    for(int i = 1; i < size; i++){
        if(points[i].x < points[min].x){
            min = i;
        }
    }
    int p =min,q;
    //Faz a varredura de jarvis
    do{
        S.Empilha(points[p]);
        q = (p+1) % size;
        //Observa a posição reminativa entre os pontos passados
        for(int i = 0; i < size; i++){
            if(functions::relative_position(points[p],points[i],points[q]) == 2){
                q = i;
            }
        }
        p = q;
    }while(p != min);
    return S;
}
