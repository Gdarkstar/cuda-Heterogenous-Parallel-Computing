#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *base_dir;
const size_t NUM_BINS = 128;

static void compute(unsigned int *bins, const char *input, int num)
{
    for (int i = 0; i < num; ++i)
    {
        ++bins[(unsigned int)input[i]];
    }
}

static char *generate_data(size_t n)
{
    char *data = (char *)malloc(n + 1);
    for (unsigned int i = 0; i < n; i++)
    {
        data[i] = (rand() % (128 - 32)) + 32;
    }
    data[n] = 0; 
    return data;
}

static void write_data_str(const char *file_name, const char *data, int num)
{
    FILE *handle = fopen(file_name, "a");
    for (int ii = 0; ii < num; ii++)
    {
        fprintf(handle, "%c", *data++);
    }
    fprintf(handle, "\n");
    fflush(handle);
    fclose(handle);
}

static void write_data_int(const char *file_name, unsigned int *data, int num)
{
    FILE *handle = fopen(file_name, "a");
    fprintf(handle, "%d", num);
    for (int ii = 0; ii < num; ii++)
    {
        fprintf(handle, "\n%d", *data++);
    }
    fprintf(handle, "\n");
    fflush(handle);
    fclose(handle);
}

static void create_dataset_fixed(int datasetNum, const char *str)
{
    const char *input_file_name = "input.txt";
    const char *output_file_name = "expected.raw";

    unsigned int *output_data =
        (unsigned int *)calloc(NUM_BINS, sizeof(unsigned int));

    compute(output_data, str, strlen(str));

    write_data_str(input_file_name, str, strlen(str));
    write_data_int(output_file_name, output_data, NUM_BINS);

    free(output_data);
}

static void create_dataset_random(int datasetNum, size_t input_length)
{
    const char *input_file_name = "input.txt";
    const char *output_file_name = "expected.raw";

    char *str = generate_data(input_length);
    unsigned int *output_data =
        (unsigned int *)calloc(NUM_BINS, sizeof(unsigned int));

    compute(output_data, str, input_length);

    write_data_str(input_file_name, str, input_length);
    write_data_int(output_file_name, output_data, NUM_BINS);

    free(str);
    free(output_data);
}

int main()
{
    FILE *a=fopen("input.txt", "w");
    FILE *b=fopen("expected.raw", "w");
    fclose(a);
    fclose(b);

    create_dataset_fixed(0, "the quick brown fox jumps over the lazy dog");
    create_dataset_fixed(1, "gpu teaching kit - accelerated computing");
    create_dataset_random(2, 16);
    create_dataset_random(3, 513);
    create_dataset_random(4, 511);
    create_dataset_random(5, 1);
    return 0;
}
