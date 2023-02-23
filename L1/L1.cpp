
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int vertexDegree(int V, int matr[10][10], int N) {
    if (V < 10) {
        int stepen = 0;
        for (int i = 0; i < N; i++) {
            stepen += matr[V][i];
        }
        return stepen;
    }
    else {
        return 0;
    }
}


    

int edges(int matr[][10], int N) {
    int rebra = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            rebra += matr[i][j];
        }
    }
    return rebra/2;
}

int maxDegree(int matr[][10], int N) {
    int maxDegree = 0;
    for (int i = 0; i < N; i++) {
        int degree = vertexDegree(i, matr, N);
        if (maxDegree < degree) {
            maxDegree = degree;
        }
    }
    return maxDegree;
}

int** convertToVectorMatrix(int matr[][10], int N) {
    const int M = maxDegree(matr, N);
    int** vectorMatr = new int* [N];
    for (int i = 0; i < N; i++) {
        vectorMatr[i] = new int[M];//задание пустой матрицы смежности векторов
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            vectorMatr[i][j] = 0;//заполнение матрицы векторов нулями.
        }
    }

    for (int i = 0; i < N; i++) {
        int k = 0;
        for (int j = 0; j < N; j++) {
            if (matr[i][j] == 1) {
                vectorMatr[i][k] = j + 1;//заполнение матрицы векторов.
                k++;
            }
        }
    }
    return vectorMatr;
}

void findAdjacentEdges(int edge, int M, int** vectorMatr) {
    int firstVertex = (edge / 10) - 1;
    int secondVertex = (edge % 10) - 1;

    for (int i = 0; i < M; i++) {
        if (vectorMatr[firstVertex][i] > 0 and vectorMatr[firstVertex][i] != secondVertex + 1) {
            cout << firstVertex + 1 << vectorMatr[firstVertex][i] << " ";
        }
    }

    for (int i = 0; i < M; i++) {
        if (vectorMatr[secondVertex][i] > 0 and vectorMatr[secondVertex][i] != firstVertex + 1) {
            cout << secondVertex + 1 << vectorMatr[secondVertex][i] << " ";
        }
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    const int N = 10;//количество вершин
    int matr[N][N]{};//инициализация пустого двумерного массива

    int x = 0;//инициализация переменной для хранения элемента двуменого массива
    ifstream m1("matrix.txt");//откртие файлика с матрицей


    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            m1 >> x;//запись 1 значения из файлика в переменную x
            matr[i][j] = x; //запись переменной x в двумерный массив
        }
    }

    cout << "Матрица смежности" << endl;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << matr[i][j] << " ";//вывод двумерного массива
        }
        cout << endl;
    }

    int V = 0;
    cout << "Степень какой вершины вы хотите узнать? - ";
    cin >> V;

    const int M = maxDegree(matr, N);

    cout <<"Степень выбранной вершины "<<V <<" - " << vertexDegree(V - 1, matr, N) << endl;
    cout <<"Степень графа - " << M<<endl;
    cout<<"Количество ребер в графе - " << edges(matr, N)<<endl;
    cout << "Матрица вектров смежности : " << endl;

    int** vectorMatr = convertToVectorMatrix(matr, N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cout  << vectorMatr[i][j] << " ";//вывод матрицы векторов смежности
        }
        cout << endl;
    }



    int edge;
    cout << "Ребра смежные какому ребру желаете получить? - ";
    cin >> edge;

    cout << "Ребра смежные ребру - " << edge<< ": ";
    findAdjacentEdges(edge, M, vectorMatr);
    cout << endl;


}


