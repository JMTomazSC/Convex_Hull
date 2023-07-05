#ifndef functions_HPP
#define functions_HPP

#include "Geometric_structures.hpp"
#include "Stack.hpp"
#include <iostream>
#include <math.h>

//Namespace auxiliar para as funções secundárias
namespace functions{
    //Efetuar a troca entre dois pontos
    void trade(point& r, point& s){
        point aux = r;
        r = s;
        s = aux;
    }
    //Calcula a posição relativa dos pontos de acordo com o produto cruzado
    int relative_position(point r, point s, point t){
        int value = (s.y - r.y) * (t.x - s.x) - (s.x - r.x) * (t.y - s.y);
        if(value == 0){
            //colineares
            return 0;
        }else if(value > 0){
            //sentido horário
            return 1;
        }else{
            //sentido anti-horário
            return 2;
        }
    }
    //Calcula a distancia entre os pontos
    double distance(point a, point b){
        return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    }
    // Merge Sort adaptado para pontos
    void merge(point p, point arr[], int left, int middle, int right) {
        int i, j, k;
        int n1 = middle - left + 1;
        int n2 = right - middle;
    
        point L[n1], R[n2];
    
        for (i = 0; i < n1; i++)
            L[i] = arr[left + i];
        for (j = 0; j < n2; j++)
            R[j] = arr[middle + 1 + j];
    
        i = 0;
        j = 0;
        k = left;
    
        //Checa Caso estiver no sentido anti-horário ou se é colinear para fazer a ordenação corretamente
        while (i < n1 && j < n2) {
            if (relative_position(p,L[i],R[j]) == 2 || (relative_position(p,L[i],R[j]) == 0 && distance(p, R[j]) > distance(p, L[i]))) {
                arr[k] = L[i];
                i++;
            } else {
                arr[k] = R[j];
                j++;
            }
            k++;
        }
    
        while (i < n1) {
            arr[k] = L[i];
            i++;
            k++;
        }
    
        while (j < n2) {
            arr[k] = R[j];
            j++;
            k++;
        }
    }
    //Merge sort
    void mergeSort(point p, point arr[], int left, int right) {
        if (left < right) {
            int middle = left + (right - left) / 2;
    
            mergeSort(p,arr, left, middle);
            mergeSort(p,arr, middle + 1, right);
    
            merge(p,arr, left, middle, right);
        }
    }
    //Insertion sort
    void Insercao_otimizado(point p,point *vetor, int tam){ 
    int i, j;
    point aux;
    for (i = 1; i < tam; i++){ 
        aux = vetor[i]; 
        j = i-1;
        //Checa posições relativas entres os pontos para fazer a ordenação corretamente
        while (j >= 0 && ((relative_position(p,aux,vetor[j]) == 2) || (relative_position(p,aux,vetor[j]) == 0 && distance(p, vetor[j]) >= distance(p, aux)))) {
        vetor[j+1] = vetor[j]; 
        j--;
        }
        vetor[j+1] = aux;
    }
    }
    //Retira o ângulo polar entre dois pontos
    double polar(point& a, point& b){
        int dx = b.x - a.x;
        int dy = b.y - a.y;
        return atan2(dy,dx);
    }

    void bucketSort(point points[], int size, point p) {
        //inicializa os baldes e seus tamanhos utilizando aritmética de matrizes
        //Método de otimizar o bucketSort
        const int numBuckets = size > 500 ? 500:size;
        point buckets[numBuckets][size];
        int bucketSizes[numBuckets];
        //Setar os tamanhos iguais a 0;
        for(int i = 0; i < numBuckets; i++){
        bucketSizes[i] = 0;
        }
        //Fazer com que o critério de ordenação seja o ângulo polar e que o loop vá de 0 a 2pi
        double maxVal = 2 * M_PI;
        double range = maxVal / (double)(numBuckets);

        //Coloca os pontos nos buckets 
        for (int i = 0; i < size; i++) {
            int bucketIndex = static_cast<int>(polar(p,points[i]) / range);
            buckets[bucketIndex][bucketSizes[bucketIndex]] = points[i];
            bucketSizes[bucketIndex]++;
        }
        
        //Ordena os buckets
        for (int i = 0; i < numBuckets; i++) {
            if (bucketSizes[i] > 0) {
                if(bucketSizes[i] > 1000){
                    //Caso o bucket seja muito grande, ordena usando o Merge Sort pois para grandes entradas ele é mais eficiente
                    mergeSort(p,buckets[i],0,bucketSizes[i]-1);
                }else{
                    // Ordena cada bucket usando o Insertion Sort
                    Insercao_otimizado(p, buckets[i],bucketSizes[i]);
                }
            }
        }
        

        // Concatena os buckets em um único array de pontos
        int index = 0;
        for (int i = 0; i < numBuckets; i++) {
            for (int j = 0; j < bucketSizes[i]; j++) {
                points[index++] = buckets[i][j];
            }
        }
        
    }

    
}



#endif