#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <sys/time.h>
#include <sys/resource.h>
#include "Geometric_structures.hpp"



using namespace std;

int main(int argc, char** argv){
    ifstream file;
    //Variável que declara se o usuário quer as retas que passam nos pontos do fecho ou não
    bool extra = false;

    //Parse Args
    for(int i = 1; i < argc; i++){
        char c = argv[i][1];
        switch(c){
            case 'f':
                file.open(argv[i+1]);
                break;
            case 'r':
                extra = true;
                break;
            default:
                if(strstr(argv[i],".txt")!= NULL){
                    continue;
                }else{
                    cout << "Argumento inválido" << endl;
                    break;
                }
        }
    }
    //Tempo dos algoritmos
    struct timespec clock_GM_start, clock_GM_end, clock_GI_start, clock_GI_end, clock_GB_start, clock_GB_end;
    struct timespec clock_J_start, clock_J_end;
    struct rusage start_GM, end_GM,start_GI, end_GI, start_GB, end_GB;
    struct rusage start_J, end_J;
    double T_clock_GM, T_clock_GI, T_clock_GB, T_clock_J; 
    
    try{

        if(file.is_open())
        {
            //Pega o numero de pontos presentes no arquivo, dps recomeça sua leitura 
            string auxiliar_line;
            int size = 0, i = 0;
            while(getline(file, auxiliar_line, '\n')){
                size++;
            }
            file.clear();
            file.seekg(0, file.beg);
            point *points = new point[size];
            //Armazena os pontos contidos no arquivo em um vetor
            while(getline(file,auxiliar_line,'\n')){
                stringstream ss(auxiliar_line);
                string x, y;
                ss >> x >> y;
                points[i].x = stoi(x);
                points[i].y = stoi(y);
                i++;
            }
            //Cria o TAD fecho convexo para executar as operações
            ConvexHull s;
            point copy1[size], copy2[size], copy3[size],copy4[size],copy5[size];

            for(int i = 0; i < size; i++){
                copy1[i] = points[i];
                copy2[i] = points[i];
                copy3[i] = points[i];
                copy4[i] = points[i];
                copy5[i] = points[i];
            };
            
            //Coleta o tempo de cada algoritmo

            //Como decisão de projeto, a pilha a ser utilizada para plotar os pontos será pelo algoritmo de graham merge
            getrusage(RUSAGE_SELF, &start_GM);
            clock_gettime(CLOCK_MONOTONIC, &clock_GM_start);
            s.Graham_merge(copy1,size);
            getrusage(RUSAGE_SELF, &end_GM);
            clock_gettime(CLOCK_MONOTONIC, &clock_GM_end);
            
            getrusage(RUSAGE_SELF, &start_GI);
            clock_gettime(CLOCK_MONOTONIC, &clock_GI_start);
            s.Graham_inserction(copy2,size);
            getrusage(RUSAGE_SELF, &end_GI);
            clock_gettime(CLOCK_MONOTONIC, &clock_GI_end);

            getrusage(RUSAGE_SELF, &start_GB);
            clock_gettime(CLOCK_MONOTONIC, &clock_GB_start);
            s.Graham_bucket(copy3,size);
            getrusage(RUSAGE_SELF, &end_GB);
            clock_gettime(CLOCK_MONOTONIC, &clock_GB_end);

            getrusage(RUSAGE_SELF, &start_J);
            clock_gettime(CLOCK_MONOTONIC, &clock_J_start);
            Stack<point> S = s.Jarvis(copy4,size);
            getrusage(RUSAGE_SELF, &end_J);
            clock_gettime(CLOCK_MONOTONIC, &clock_J_end);

            //Executa a plotagem dos pontos
            cout << "FECHO CONVEXO:" << endl;
            while(!S.Vazia()){
                point p = S.Desempilha();
                cout << p.x << " " << p.y << endl;
            }



            //Calcula os tempos de cada algoritmo
            T_clock_GM = (clock_GM_end.tv_sec - clock_GM_start.tv_sec) + (clock_GM_end.tv_nsec - clock_GM_start.tv_nsec)/10e9;
            T_clock_GI = (clock_GI_end.tv_sec - clock_GI_start.tv_sec) + (clock_GI_end.tv_nsec - clock_GI_start.tv_nsec)/10e9;
            T_clock_GB = (clock_GB_end.tv_sec - clock_GB_start.tv_sec) + (clock_GB_end.tv_nsec - clock_GB_start.tv_nsec)/10e9;
            T_clock_J = (clock_J_end.tv_sec - clock_J_start.tv_sec) + (clock_J_end.tv_nsec - clock_J_start.tv_nsec)/10e9;

            //Colocar uma precisão de 7 casas
            cout << fixed << setprecision(7);
            //Retorna os tempos para analise de desempenho
            cout << endl << "GRAHAM+MERGE: " << T_clock_GM << endl;
            cout << "GRAHAM+INSERCTION: " << T_clock_GI << endl;
            cout << "GRAHAM+BUCKET: " << T_clock_GB << endl;
            cout << "JARVIS: " << T_clock_J << endl;
            
            //Caso escolha reproduzir as retas
            if(extra == true){
                //Construindo retas
                cout << endl << "RETAS:" << endl;
                Stack<string> lines;
                Stack<point> aux = s.Jarvis(copy5,size);
                point top = aux.get_top();
                point last = aux.get_top();
                aux.Desempilha();
                line r; 


                while(!aux.Vazia()){
                    point p = aux.get_top();
                    aux.Desempilha();

                    r.create(last,p);
                    lines.Empilha(r.equation());
                    last = p;
                }
                r.create(last,top);
                lines.Empilha(r.equation());

                while(!lines.Vazia()){
                    string line = lines.Desempilha();
                    cout << line << endl;
                }
            }

            delete[] points;
        }else{
            file_not_open error;
            throw error;
        }
    }catch(file_not_open error){
        cout << "File not found" << endl << "The program will end" << endl;
    }catch(not_enough_points error){
        cout << "Insuficient number of points" << endl << "The program will end" << endl;
    }catch(invalid_argument error){
        cout << "Invalid Argument" << endl << "The program will end" << endl;
    }
}