#include "main.h"

/*Forward declarations of helper functions*/
size_t count_words(char *str, char separator);
char **allocate_memory_for_matrix(size_t size);
void extract_substrings(char *str, char separator, char **matrix);
char *extract_substring(char *str, int start, int end);

char **strsplit(char *str, char separator, size_t *num_strings)
{
    size_t num_words;
    char **matrix;

    if (str == NULL || separator == '\0')
    {
        if (num_strings != NULL)
            *num_strings = 0;
        return NULL;
    }

    num_words = count_words(str, separator);

    if (num_strings != NULL)
        *num_strings = num_words;

    if (num_words == 0)
        return NULL;

    matrix = allocate_memory_for_matrix(num_words);

    if (matrix == NULL)
        return NULL;

    extract_substrings(str, separator, matrix);

    return matrix;
}

size_t count_words(char *str, char separator)
{
    size_t num_words = 0;
    bool in_word = false;
    char *ptr;

    for (ptr = str; *ptr != '\0'; ptr++)
    {
        if (*ptr == separator)
        {
            if (in_word)
            {
                num_words++;
                in_word = false;
            }
        }
        else
        {
            if (!in_word)
                in_word = true;
        }
    }

    if (in_word)
        num_words++;

    return num_words;
}

char **allocate_memory_for_matrix(size_t size)
{
    return ((char **)malloc(sizeof(char *) * (size + 1)));
}

void extract_substrings(char *str, char separator, char **matrix)
{
    int word_index = 0;
    bool in_word = false;
    char *start = str;
    char *ptr;
    int i;

    for (ptr = str; *ptr != '\0'; ptr++)
    {
        if (*ptr == separator)
        {
            if (in_word)
            {
                int length = ptr - start;
                matrix[word_index] = extract_substring(str, start - str, (int)(start - str + length));
                if (matrix[word_index] == NULL)
                {
                    /*Handle memory allocation error*/
                    for (i = 0; i < word_index; i++)
                        free(matrix[i]);
                    free(matrix);
                    return;
                }
                word_index++;
                in_word = false;
            }
        }
        else
        {
            if (!in_word)
                start = ptr;
            in_word = true;
        }
    }

    /*Handle the last word (if any)*/
    if (in_word)
    {
        int length = ptr - start;
        matrix[word_index] = extract_substring(str, start - str, (int)(start - str + length));
        if (matrix[word_index] == NULL)
        {
            /*Handle memory allocation error*/
            for (i = 0; i <= word_index; i++)
                free(matrix[i]);
            free(matrix);
            return;
        }
    }
}

char *extract_substring(char *str, int start, int end)
{
    int i;

    int length = end - start;
    char *temp = (char *)malloc(sizeof(char) * (length + 1));

    if (temp == NULL)
        return NULL;

    for (i = 0; i < length; i++)
        temp[i] = str[start + i];

    temp[length] = '\0';
    
    return temp;
}
