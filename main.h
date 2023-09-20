#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdarg.h>

extern char **environ;

/*Prototypes*/
void _execute_command(char **args, size_t no_of_args, char **env);
int _handle_command(char *command, char **env);
char *_str_concat(int num_strings, ...);
void _handle_builtin_command(char *command);
bool _handle_file_status(struct stat *statbuffer, char *pathname);
int _strlen(const char *string);
char *_strncpy(const char *string, char *destination, int n);
int _count_words(char *string, char seperator);
void _panic(char *string);
void _free_vector(char **listOfStrings, size_t len);
char **_allocate_memory_for_matrix(size_t size);
char *_handle_file_in_path(char *executable, struct stat *statbuffer);
void _handle_execute(char **arguments, int no_of_args, char **envp);
int _strcmp(char *string1, char *string2);
/*char **_strsplit(char *str, char seperator, size_t *num_strings);*/
void _extract_substrings(char *str, char seperator, char **matrix);
char *_extract_substring(char *str, int start, int end);
void _copy_strings(char *fullstring, int num_strings, va_list args);
size_t _calculate_total_length(int num_strings, va_list args);
int _atoi(char *s);
char **strsplit(char *str, char separator, size_t *num_strings);
size_t count_words(char *str, char separator);
char **_allocate_memory_for_matrix(size_t size);
void _extract_substrings(char *str, char separator, char **matrix);
char *_extract_substring(char *str, int start, int end);
char *_extract_word(char *str, int start, int end);
void _cleanup_matrix(char **matrix, int num_words);
bool _add_word_to_matrix(char **matrix, char *word, int word_index);
void _handle_exit(char **exit_arguments, size_t no_of_args);
bool _handle_buitin(char **args, size_t no_of_args);
#endif
