#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void throwError(char *errorMessage)
{
    fprintf(stderr, "%s:%s\n", errorMessage, strerror(errno));
    // perror(errorMessage);
    exit(errno);
}

void *allocateMemory(size_t memory)
{
    void *p = malloc(memory);
    if (NULL == p)
    {
        throwError("Error at allocating memory");
    }
    return p;
}

void throwErrorFromFile(char *errorMessage, char *fileName)
{
    char tmp[1001];
    snprintf(tmp, 1000, "%s %s", errorMessage, fileName);
    throwError(tmp);
}

FILE *openFile(char *fileName, char *openType)
{
    FILE *file;
    file = fopen(fileName, openType);

    if (NULL == file)
    {
        throwErrorFromFile("Error at opening file: ", fileName);
    }

    return file;
}

void closeFile(FILE *file, char *fileName)
{
    if (fclose(file))
    {
        throwErrorFromFile("Error at closing file: ", fileName);
    }
}

void readFromFile(char *fileName)
{
    FILE *file = openFile(fileName, "r");

    static const int MAX_BUFFER_LENGTH = 1000;
    char buffer[MAX_BUFFER_LENGTH];

    int firstNumber;
    errno = 0;
    if (fscanf(file, "%d\n", &firstNumber) != 1)
    {
        throwErrorFromFile("Error at reading from file ", fileName);
    }

    printf("%d\n", firstNumber);

    while (fgets(buffer, MAX_BUFFER_LENGTH, file))
    {
        printf("%s", buffer);
    }

    if(!feof(file)){
        throwErrorFromFile("EOF not reachead: ", fileName);
    }

    if (errno)
    {
        throwErrorFromFile("Errror reading from file: ", fileName);
    }

    closeFile(file, fileName);
}

void writeToFile(char *fileName)
{
    FILE *file = openFile(fileName, "w");
    char *dummyText[] = {"This is a sentence", "This is the second one", "Third one"};

    errno = 0;
    for (int i = 0; i < 3; ++i)
    {
        if (fprintf(file, "%s\n", dummyText[i]) != strlen(dummyText[i]) + 1)
        {
            throwErrorFromFile("Error at writing to file: ", fileName);
        }
    }

    if (errno)
    {
        throwErrorFromFile("Error at writing to file: ", fileName);
    }

    closeFile(file, fileName);
}

void writeToBinaryFile(char *fileName, char *openType, void *elements, size_t elementSize, size_t numberOfElements)
{
    FILE *file = openFile(fileName, openType);

    errno = 0;
    if (fwrite(elements, elementSize, numberOfElements, file) != numberOfElements)
    {
        throwErrorFromFile("Error at writing to binary file: ", fileName);
    }

    if (errno)
    {
        throwErrorFromFile("Error at writing to binary file: ", fileName);
    }

    closeFile(file, fileName);
}

void copy(char *sourceFilePath, char *destinationFilePath, size_t elementSize)
{
    FILE *sourceFile = openFile(sourceFilePath, "rb");
    size_t numberOfElementsRead = 1;
    void *element = allocateMemory(elementSize * numberOfElementsRead);

    errno = 0;

    while (fread(element, elementSize, numberOfElementsRead, sourceFile) == numberOfElementsRead)
    {
        writeToBinaryFile(destinationFilePath, "ab", element, elementSize, numberOfElementsRead);
    }

    if (!feof(sourceFile))
    {
        throwErrorFromFile("EOF not reached ", sourceFilePath);
    }

    if (errno)
    {
        throwErrorFromFile("Error at writing to binary file: ", destinationFilePath);
    }

    free(element);

    closeFile(sourceFile, sourceFilePath);
}

void basicTesting()
{
    int n = 0x1177AAEE;
    writeToBinaryFile("1.dat", "wb", &n, sizeof(int), 1);
    writeToBinaryFile("1.dat", "a+", &n, sizeof(int), 1);
    copy("1.dat", "2.dat", sizeof(int));
}

int main()
{
    printf("Hello World!\n");
    readFromFile("input.txt");
    writeToFile("output.txt");
    basicTesting();

    return 0;
}
