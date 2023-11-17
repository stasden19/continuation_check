#include <stdio.h>
#include <stdlib.h>

int main() {
    // Открываем файл
    FILE *file = fopen("your_file_path", "rb");

    if (file == NULL) {
        perror("Unable to open file");
        return 1;
    }

    // Определяем размер файла
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    // Читаем файл в байтовый буфер
    char *byteBuffer = (char *)malloc(fileSize);
    fread(byteBuffer, 1, fileSize, file);

    // Закрываем файл
    fclose(file);

    // Буфер для хранения кластеров по 1024 байта
    int clusterSize = 1024;
    int numClusters = fileSize / clusterSize + (fileSize % clusterSize != 0);
    char **clusters = (char **)malloc(numClusters * sizeof(char *));

    // Разбиваем байтовый буфер на кластеры
    for (int i = 0; i < numClusters; ++i) {
        int offset = i * clusterSize;
        int size = (i == numClusters - 1) ? (fileSize % clusterSize) : clusterSize;

        clusters[i] = (char *)malloc(size);
        memcpy(clusters[i], byteBuffer + offset, size);
    }

    // Теперь переменная clusters содержит кластеры по 1024 байта

    // Освобождаем выделенную память
    free(byteBuffer);
    for (int i = 0; i < numClusters; ++i) {
        free(clusters[i]);
    }
    free(clusters);

    return 0;
}
