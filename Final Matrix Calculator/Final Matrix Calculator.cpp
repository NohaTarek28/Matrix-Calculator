#include <stdio.h>
#include <cstring>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <vector>
#include<iomanip>
#include <sstream>

using namespace std;

int rows = 0;
int cols = 0;
vector <float> oneDimension;


void addm(float** matrix1, float** matrix2, float** matrix3, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            matrix3[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
}

void subm(float** matrix1, float** matrix2, float** matrix3, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            matrix3[i][j] = matrix1[i][j] - matrix2[i][j];

        }
    }
}

void multiplyByScalar(float** matrix, float scalar, float** resultMatrix, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            resultMatrix[i][j] = matrix[i][j] * scalar;
        }
    }
}

void multiply(float** matrix1, float** matrix2, float** matrix3, int rows1, int rows2, int cols1, int cols2)
{
    for (int i = 0; i < rows1; i++)
    {
        for (int j = 0; j < cols2; j++)
        {
            float sum = 0;
            for (int x = 0; x < cols1; x++)
            {
                sum += matrix1[i][x] * matrix2[x][j];
                matrix3[i][j] = sum;
            }
        }
    }
}

void transpose(float** matrix, float** resultMatrix, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            resultMatrix[j][i] = matrix[i][j];
        }
    }
}

float determinant(float** matrix, int rows)
{
    float result = 0;
    float** smallMatrix = new float* [rows];
    for (int i = 0; i < rows; i++)
    {
        smallMatrix[i] = new float[rows];
    }
    if (rows == 2)
    {
        result = (matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]);
        return result;
    }

    else
    {
        for (int x = 0; x < rows; x++)
        {
            int smallMatrixI = 0;
            for (int i = 1; i < rows; i++)
            {
                int smallMatrixJ = 0;
                for (int j = 0; j < rows; j++)
                {
                    if (j == x)
                        continue;
                    smallMatrix[smallMatrixI][smallMatrixJ] = matrix[i][j];
                    smallMatrixJ++;
                }
                smallMatrixI++;
            }
            result = result + (pow(-1, x) * matrix[0][x] * determinant(smallMatrix, rows - 1));
        }
    }
    return result;
}

bool inverse(float** matrix, float** resultMatrix, int rows)
{
    if (determinant(matrix, rows) == 0)
        return false;

    else
    {
        float det = determinant(matrix, rows);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < rows; j++)
            {
                resultMatrix[i][j] = ((matrix[(j + 1) % rows][(i + 1) % rows] * matrix[(j + 2) % rows][(i + 2) % rows]) -
                    (matrix[(j + 1) % rows][(i + 2) % rows] * matrix[(j + 2) % rows][(i + 1) % rows])) / det;
            }
        }

    }
    return true;
}

void printMatrix(int rows, int cols, float** matrix)
{
    cout << "[";
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if ((int)matrix[i][j] == matrix[i][j])
                cout << matrix[i][j];
            else
            {
                stringstream s;
                s << setprecision(2) << fixed << matrix[i][j];
                string number = s.str();
                number = number.substr(0, number.find_last_not_of('0') + 1);
                cout << number;
            }

            if (j != cols - 1)
                cout << " ";
        }
        if (i != rows - 1)
            cout << ", ";
    }
    cout << "]";
}

string removeLeadingTrailingSpaces(string s)
{
    int start = s.find_first_not_of(" \n\r\t\f\v");
    if (start != string::npos)
    {
        s = s.substr(start);
    }
    int end = s.find_last_not_of(" \n\r\t\f\v");
    if (end != string::npos)
    {
        s = s.substr(0, end + 1);
    }
    return s;
}

string removeMiddleSpaces(string s)
{
    string temp = "i";
    string cleanString;
    for (int i = 0; i < s.size(); i++)
    {
        if (temp.back() != ' ' && s[i] == ' ')
        {
            cleanString.push_back(' ');
        }
        temp.push_back(s[i]);
        if (s[i] != ' ')
        {
            cleanString.push_back(s[i]);
        }
    }
    return cleanString;
}

int getNumberOfElements(string s)
{
    int num = 0;
    string cleanString = removeMiddleSpaces(s);
    for (int i = 0; i < cleanString.size(); i++)
    {
        if (isspace(cleanString[i]))
            num++;
    }
    return num;
}
bool isNumber(string s)
{
    for (int i = 0; i < s.size(); i++)
    {
        if (isdigit(s[i]) || s[i] == '.' || s[i] == '-')
            continue;
        else
            return false;
    }
    return true;
}

bool cutString(string s)
{
    string noBrackets = s.substr(s.find("[") + 1, s.size() - 2);
    noBrackets = removeLeadingTrailingSpaces(noBrackets);

    int start1 = 0;
    int end1 = noBrackets.find(",");

    int start2 = 0;
    int end2 = noBrackets.find(" ");

    string fullRow = noBrackets.substr(start1, end1 - start1);
    fullRow = removeLeadingTrailingSpaces(fullRow);
    fullRow = removeMiddleSpaces(fullRow);
    string matrixElement = fullRow.substr(start2, end2 - start2);
    cols = getNumberOfElements(fullRow) + 1;

    while (end1 != -1)
    {
        fullRow = noBrackets.substr(start1, end1 - start1);
        fullRow = removeLeadingTrailingSpaces(fullRow);
        fullRow = removeMiddleSpaces(fullRow);

        start2 = 0;
        end2 = fullRow.find(" ");
        if (cols != getNumberOfElements(fullRow) + 1)
        {
            return false;
        }

        while (end2 != -1)
        {
            matrixElement = fullRow.substr(start2, end2 - start2);
            if (isNumber(matrixElement))
                oneDimension.push_back(stof(matrixElement));
            else
                return false;

            start2 = end2 + 1;
            end2 = fullRow.find(" ", start2);
        }

        //For the last matrixElement
        matrixElement = fullRow.substr(start2);
        if (isNumber(matrixElement))
            oneDimension.push_back(stof(matrixElement));
        else
            return false;

        start1 = end1 + 1;
        end1 = noBrackets.find(",", start1);
        rows = rows + 1;
    }

    //For the last row
    if (end1 == -1)
    {
        fullRow = noBrackets.substr(start1);
        fullRow = removeLeadingTrailingSpaces(fullRow);
        fullRow = removeMiddleSpaces(fullRow);

        start2 = 0;
        end2 = fullRow.find(" ");

        if (cols != getNumberOfElements(fullRow) + 1)
        {
            return false;
        }

        while (end2 != -1)
        {
            matrixElement = fullRow.substr(start2, end2 - start2);
            if (isNumber(matrixElement))
                oneDimension.push_back(stof(matrixElement));
            else
                return false;

            start2 = end2 + 1;
            end2 = fullRow.find(" ", start2);
        }

        //For the last matrix element in the last row
        matrixElement = fullRow.substr(start2);
        if (isNumber(matrixElement))
            oneDimension.push_back(stof(matrixElement));
        else
            return false;
        rows = rows + 1;
    }

    if (oneDimension.empty())
        return false;
    else
        return true;
}

int main()
{
    string m1;
    string op;
    string m2;
    int rows1 = 0;
    int cols1 = 0;
    int rows2 = 0;
    int cols2 = 0;
    int rows3 = 0;
    int cols3 = 0;
    float** matrix1;
    float** matrix2;
    float** matrix3;
    float scalar = 0;

    getline(cin, m1);
    if (m1[0] == '[')
    {

        //Converts m1 from string to matrix
        if (!cutString(m1) || m1[m1.size() - 1] != ']')
        {
            cout << "ERROR!" << endl;
            return 0;
        }
        rows1 = rows;
        cols1 = cols;
        matrix1 = new float* [rows1];
        for (int i = 0; i < rows1; i++)
        {
            matrix1[i] = new float[cols1];
        }

        int k = 0;
        for (int i = 0; i < rows1; i++)
        {
            for (int j = 0; j < cols1; j++)
            {
                matrix1[i][j] = oneDimension[k];
                k++;
            }
        }
    }
    else
    {
        scalar = stof(m1);
        rows1 = -1;
        cols1 = -1;
        matrix1 = new float* [1];
        matrix1[0] = new float[1];
    }

    //clear global variables
    rows = 0;
    cols = 0;
    oneDimension.clear();

    getline(cin, op);

    if (op == "+" || op == "-" || op == "*")
    {
        getline(cin, m2);
        if (m2[0] == '[')
        {
            //Converts m2 from string to matrix2
            if (!cutString(m2) || m2[m2.size() - 1] != ']')
            {
                cout << "ERROR!" << endl;
                return 0;
            }
            rows2 = rows;
            cols2 = cols;
            matrix2 = new float* [rows2];
            for (int i = 0; i < rows2; i++)
            {
                matrix2[i] = new float[cols2];
            }

            int k = 0;
            for (int i = 0; i < rows2; i++)
            {
                for (int j = 0; j < cols2; j++)
                {
                    matrix2[i][j] = oneDimension[k];
                    k++;
                }
            }
        }
        else
        {
            scalar = stof(m2);
            rows2 = -1;
            cols2 = -1;
            matrix2 = new float* [1];
            matrix2[0] = new float[1];
        }

        //Define the result matrix
        if (rows1 == -1 && cols1 == -1 && op == "*")
        {
            rows3 = rows2;
            cols3 = cols2;
            matrix3 = new float* [rows2];
            for (int i = 0; i < rows2; i++)
            {
                matrix3[i] = new float[cols2];
            }
        }
        else if (rows2 == -1 && cols2 == -1 && op == "*")
        {
            rows3 = rows1;
            cols3 = cols1;
            matrix3 = new float* [rows1];
            for (int i = 0; i < rows1; i++)
            {
                matrix3[i] = new float[cols1];
            }
        }
        else
        {
            rows3 = rows1;
            cols3 = cols2;
            matrix3 = new float* [rows1];
            for (int i = 0; i < rows1; i++)
            {
                matrix3[i] = new float[cols2];
            }
        }
    }
    else
    {
        rows3 = cols1;
        cols3 = rows1;
        matrix3 = new float* [rows3];
        for (int i = 0; i < rows3; i++)
        {
            matrix3[i] = new float[cols3];
        }
        rows2 = -1;
        cols2 = -1;
        matrix2 = new float* [1];
        matrix2[0] = new float[1];
    }

    //calculation process
    if (op == "*")
    {
        if (cols1 == rows2)
        {
            multiply(matrix1, matrix2, matrix3, rows1, rows2, cols1, cols2);
            printMatrix(rows3, cols3, matrix3);
        }

        else if (rows1 == -1 && cols1 == -1)
        {
            multiplyByScalar(matrix2, scalar, matrix3, rows2, cols2);
            printMatrix(rows3, cols3, matrix3);
        }

        else if (rows2 == -1 && cols2 == -1)
        {
            multiplyByScalar(matrix1, scalar, matrix3, rows1, cols1);
            printMatrix(rows3, cols3, matrix3);
        }

        //error checking process
        else
        {
            cout << "ERROR!" << endl;
            return 0;
        }
    }
    else if (op == "+")
    {
        //error checking process
        if (cols1 != cols2 || rows1 != rows2)
        {
            cout << "ERROR!" << endl;
            return 0;
        }

        addm(matrix1, matrix2, matrix3, rows2, cols2);
        printMatrix(rows3, cols3, matrix3);
    }
    else if (op == "-")
    {
        //error checking process
        if (cols1 != cols2 || rows1 != rows2)
        {
            cout << "ERROR!" << endl;
            return 0;
        }

        subm(matrix1, matrix2, matrix3, rows2, cols2);
        printMatrix(rows3, cols3, matrix3);
    }
    else if (op == "T")
    {
        transpose(matrix1, matrix3, rows1, cols1);
        printMatrix(rows3, cols3, matrix3);
    }
    else if (op == "D")
    {
        if (rows1 == cols1)
            cout << determinant(matrix1, rows1);
        else
            cout << "ERROR!" << endl;
    }

    else if (op == "I")
    {
        if (rows1 == cols1)
        {
            if (inverse(matrix1, matrix3, rows1))
            {
                printMatrix(rows3, cols3, matrix3);
            }
            else
            {
                cout << "ERROR!" << endl;
            }
        }
        else
            cout << "ERROR!" << endl;
    }
    else
    {
        cout << "ERROR!" << endl;
    }

    for (int i = 0; i < rows1; i++)
    {
        delete matrix1[i];
    }
    delete[] matrix1;
    for (int i = 0; i < rows2; i++)
    {
        delete matrix2[i];
    }
    delete[] matrix2;
    for (int i = 0; i < rows3; i++)
    {
        delete matrix3[i];
    }
    delete[] matrix3;

    return 0;
}