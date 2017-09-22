#include <iostream>
#include <math.h>
#include <iomanip>

#define MT 4

// Resolução de matriz 4x4 por método de Cramer
// Formula| Xi = det(Ai)/det(A)
// Formula Laplace| Sum (-1)^i+j*A(i*j)*det(A)i*j


using namespace std;

int eliminarColuna(int, int **matriz);
void imprimirMatrizCof(int **mtrz, int*, int*, int A);
int **_alocMtrz(int, int);
int calcCof(int **cof);
int **_initializerMtrz (int **mtrz, int *result, int);
int detFinal(int r[4], int **mtrz);

int main()
{
    cout << " ********** Resolução de matriz 4x4 pela regra de cramer ************" << endl;
    int ** _mtrz = _alocMtrz(MT,MT);
    int result[MT] = {0};
    int resultPpr[MT] = {0};
    int valueX[MT] = {0};


    // Inicializando matriz com seus devidos números.
    cout << "Insira a matriz 4x4 [Separados por espaço e ENTER]" << endl << "Exemplo:" << endl;
    cout << "X X X X" << endl << "X X X X" << endl << "X X X X" << endl << "X X X X" << endl;
    for(int i = 0; i < MT; i++){
        for(int j = 0; j < MT; j++){
            cin >> _mtrz[i][j];
        }
    }

    // Inicializando Resultados (b)
    cout << "Insira os resultados [Separados por espaço]" << endl;
    for(int i = 0; i < MT; i++)
        cin >> result[i];

    // Resultados DET(A)
    resultPpr[0] =  eliminarColuna(0, _mtrz);
    resultPpr[1] =  eliminarColuna(1, _mtrz);
    resultPpr[2] =  eliminarColuna(2, _mtrz);
    resultPpr[3] =  eliminarColuna(3, _mtrz);
    const int A = detFinal(resultPpr, _mtrz);

    // Eliminar coluna transforma matriz em 3x5 e retorna o resultado inteiro.
    int **_det;
    int leng = 0;
    while(leng < MT){
        int resultCof[MT] = {0};
        _det = _initializerMtrz(_mtrz, result, leng);

        for(int i = 0; i < MT; i++){
            resultCof[i] =  eliminarColuna(i, _det);
        }

        valueX[leng] = detFinal(resultCof,_det);
        leng++;
    }

    cout << "Determinante A = " << A << endl;
    cout << "X1 = " << (double)valueX[0]/A << endl;
    cout << "X2 = " << (double)valueX[1]/A << endl;
    cout << "X3 = " << (double)valueX[2]/A << endl;
    cout << "X4 = " << (double)valueX[3]/A << endl;

    imprimirMatrizCof(_mtrz, result, valueX, A);


    // Desalocar Det1
    for(int i = 0;i < MT; ++i){
            delete[] _mtrz[i];
            delete[] _det[i];
    }
    delete[] _mtrz;
    delete[] _det;

    return 0;
}

int eliminarColuna(int col, int **matriz){
    int **_cof = (int**)_alocMtrz(3,5);

    for(int i = 1, l = 0; i < MT; i++,l++){
        for(int j = 0, k = 0; j < MT; j++){
            if (j == col) continue;
            else{
                _cof[l][k] = matriz[i][j];
                k++;
            }
        }
    }

    //Duplicar coluna
    for(int i = 0; i < 3; i++){
        for(int j = 3; j < 5; j++){
            _cof[i][j] = _cof[i][j-3];
        }
    }

    // Calcula matriz[3][5] e retorna inteiro.
    int result = calcCof(_cof);

    // Liberando memória

    return result;
}


void imprimirMatrizCof(int **mtrz, int *result, int *valueX, int A){
    for(int i = 0; i < MT; i++){
        cout << endl;
        for(int j = 0; j < MT; j++){
            cout << setw(3);
            cout << "[" << mtrz[i][j] << "*" << (double)valueX[j]/A << "]";
        }
        cout << setw(2);
        cout << " = " << result[i];
    }

    cout << endl;
}

int **_alocMtrz(int rows, int colmns){
    int **_cof = new int*[rows];
    for(int i = 0; i < rows; i++)
        _cof[i] = new int[colmns];

    return _cof;
}

int calcCof(int **cof){
    int result = 0;
    result = (cof[0][0]*cof[1][1]*cof[2][2])+(cof[0][1]*cof[1][2]*cof[2][3])+(cof[0][2]*cof[1][3]*cof[2][4])-(cof[0][4]*cof[1][3]*cof[2][2])-(cof[0][3]*cof[1][2]*cof[2][1])-(cof[0][2]*cof[1][1]*cof[2][0]);
    return result;
}

int **_initializerMtrz (int **mtrz, int *result, int aColumn){
    int **det = _alocMtrz(MT,MT);
    for(int i = 0; i < MT; i++){
        for(int j = 0; j < MT; j++){
          (j == aColumn) ? det[i][j] = result[i] : det[i][j] = mtrz[i][j];
        }
    }

    return det;
}

int detFinal(int r[4], int **mtrz){
    int final = 0;
    for(int i = 1; i <= 4; i++){
        final += (pow(-1.0,(1.0+i)) * (mtrz[0][i-1]) * (r[i-1]));
    }

    return final;
}
