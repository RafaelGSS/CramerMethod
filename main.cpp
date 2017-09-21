#include <iostream>

// Resolução de matriz 4x4 por método de Cramer

using namespace std;

//Se queremos alterar * devemos passar *+1
int** eliminarColuna(int, int **matriz);
void imprimirMatrizCof(int **mtrz, int, int);
int **_alocMtrz(int, int);


int main()
{
    int ** _mtrz = _alocMtrz(4,4);
    int result[4] = {0};

    // Inicializando matriz com seus devidos números.
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            cin >> _mtrz[i][j];
        }
    }

    // Inicializando Resultados (b)
    for(int i = 0; i < 4; i++)
        cin >> result[i];

    // Imprimindo matriz com arg2 = linhas arg3 = colunas.
    imprimirMatrizCof(_mtrz, 4, 4);

    // Alocação dos cofadores dinamicamente para liberar depois.
    // Retornando memoria alocada **
    int **_cof1 =  eliminarColuna(1, _mtrz);
    int **_cof2 =  eliminarColuna(2, _mtrz);
    int **_cof3 =  eliminarColuna(3, _mtrz);
    int **_cof4 =  eliminarColuna(4, _mtrz);



    imprimirMatrizCof(_cof1, 3,5);
    imprimirMatrizCof(_cof2, 3,5);
    imprimirMatrizCof(_cof3, 3,5);
    imprimirMatrizCof(_cof4, 3,5);



    return 0;
}

int** eliminarColuna(int col, int **matriz){
    int **_cof = (int**)_alocMtrz(3,5);

    int k = 0; // Percorrer
    for(int i = 1; i < 4; i++){
        for(int j = 0; j < 4; j++,k++){
            if (j == (col-1)) continue;
           _cof[i-1][k] = matriz[i][j];
        }
    }

    //Duplicar coluna
    for(int i = 0; i < 3; i++){
        for(int j = 3; j < 5; j++){
            _cof[i][j] = _cof[i][j-3];
        }
    }

    return _cof;
}


void imprimirMatrizCof(int **mtrz, int a, int b){
    if(a == 3){
        cout << "************* Imprimindo cofator ***************";
    } else {
        cout << "************* Imprimindo matriz ***************";
    }
    for(int i = 0; i < a; i++){
        cout << endl;
        for(int j = 0; j < b; j++){
            cout << "[" << mtrz[i][j] << "] ";
        }
    }

    cout << endl;
}

int **_alocMtrz(int rows, int colmns){
    int **_cof = new int*[rows];
    for(int i = 0; i < colmns; i++)
        _cof[i] = new int[colmns];

    return _cof;
}

// ESTÁ IMPRIMINDO APENAS A LINHA 0 NO COFATOR.
