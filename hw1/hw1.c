#include <stdio.h>

#define MAX_SIZE 100

// 定義矩陣結構體
typedef struct {
    int rows;
    int cols;
    double data[MAX_SIZE * MAX_SIZE]; // 使用一維指標存儲矩陣元素
} Matrix;

// 初始化矩陣
void init_matrix(Matrix *mat, int rows, int cols) {
    mat->rows = rows;
    mat->cols = cols;
    // 將所有元素初始化為0
    for (int i = 0; i < rows * cols; i++) {
        mat->data[i] = 0.0;
    }
}

// 設置矩陣元素的值
void set_element(Matrix *mat, int row, int col, double value) {
    if (row >= 0 && row < mat->rows && col >= 0 && col < mat->cols) {
        mat->data[row * mat->cols + col] = value;
    } else {
        printf("Error: Index out of range.\n");
    }
}

// 獲取矩陣元素的值
double get_element(Matrix *mat, int row, int col) {
    if (row >= 0 && row < mat->rows && col >= 0 && col < mat->cols) {
        return mat->data[row * mat->cols + col];
    } else {
        printf("Error: Index out of range.\n");
        return 0.0; // 錯誤時返回0
    }
}

// 打印矩陣
void print_matrix(Matrix *mat) {
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            printf("%f ", get_element(mat, i, j));
        }
        printf("\n");
    }
}

// 矩陣相加
Matrix add_matrix(Matrix *mat1, Matrix *mat2) {
    Matrix result;
    if (mat1->rows != mat2->rows || mat1->cols != mat2->cols) {
        printf("Error: Matrix dimensions do not match.\n");
        init_matrix(&result, 0, 0);
        return result;
    }
    result.rows = mat1->rows;
    result.cols = mat1->cols;
    for (int i = 0; i < mat1->rows; i++) {
        for (int j = 0; j < mat1->cols; j++) {
            double sum = get_element(mat1, i, j) + get_element(mat2, i, j);
            set_element(&result, i, j, sum);
        }
    }
    return result;
}

// 矩陣相乘
Matrix multiply_matrix(Matrix *mat1, Matrix *mat2) {
    Matrix result;
    if (mat1->cols != mat2->rows) {
        printf("Error: Matrix dimensions do not allow multiplication.\n");
        init_matrix(&result, 0, 0);
        return result;
    }
    result.rows = mat1->rows;
    result.cols = mat2->cols;
    for (int i = 0; i < mat1->rows; i++) {
        for (int j = 0; j < mat2->cols; j++) {
            double sum = 0.0;
            for (int k = 0; k < mat1->cols; k++) {
                sum += get_element(mat1, i, k) * get_element(mat2, k, j);
            }
            set_element(&result, i, j, sum);
        }
    }
    return result;
}

int main() {
    Matrix mat1, mat2, result;
    init_matrix(&mat1, 2, 2);
    init_matrix(&mat2, 2, 2);

    // 設置矩陣元素的值
    set_element(&mat1, 0, 0, 1);
    set_element(&mat1, 0, 1, 2);
    set_element(&mat1, 1, 0, 3);
    set_element(&mat1, 1, 1, 4);

    set_element(&mat2, 0, 0, 5);
    set_element(&mat2, 0, 1, 6);
    set_element(&mat2, 1, 0, 7);
    set_element(&mat2, 1, 1, 8);

    printf("Matrix 1:\n");
    print_matrix(&mat1);
    printf("\nMatrix 2:\n");
    print_matrix(&mat2);

    // 矩陣相加
    result = add_matrix(&mat1, &mat2);
    printf("\nMatrix Addition Result:\n");
    print_matrix(&result);

    // 矩陣相乘
    result = multiply_matrix(&mat1, &mat2);
    printf("\nMatrix Multiplication Result:\n");
    print_matrix(&result);

    return 0;
}
