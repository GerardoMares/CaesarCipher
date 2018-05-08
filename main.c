#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <ctype.h>


/*
 * In order to run:
 *
 * create a text file you want to encrypt
 *
 * compile the program using gcc
 *  -ex: gcc -o cipher cipher.c
 *
 *
 * run the encryption program:
 *
 *  -ex: ./cipher -E sample.txt -s 3
 *  -the above example will encrypt using a shift of 3
 *
 *
 * run the decryption program:
 *
 *  -ex: ./cipher -D encrypted.txt -s 3
 *  -this will decrypt the previous encrypted file with a shift of 3
 *
 */

void help(char **argv) {
    printf("--------------------------\n");
    printf("\"%s -E <input file> -s <shift key value>\" to encrypt your text\n", argv[0]);
    printf("\"%s -D <input file> -s <shift key value>\" to decrypt your text\n", argv[0]);
    printf("--------------------------\n");
    printf("Example:\n");
    printf("\"%s -E input.txt -s 3\" to encrypt your text\n", argv[0]);
    printf("\"%s -D encrypted.txt -s 3\" to decrypt your text\n", argv[0]);
}


void shiftE(char *initial, char charA, char charZ, int offset) {

    int shifted = *initial + offset;

    if (shifted > charZ) {
        int diff = shifted - charZ - 1;
        *initial = charA + diff;
    } else {
        *initial = *initial + offset;
    }
}

void shiftD(char *initial, char charA, char charZ, int offset) {

    int shifted = *initial + offset;

    if (shifted < charA) {
        int diff = charA - shifted - 1;
        *initial = charZ - diff;
    } else {
        *initial = *initial + offset;
    }
}

void readWriteFile(char c, FILE *input_file, FILE *output_file, int offset, int encrypt) {

    while ((c = fgetc(input_file)) != EOF) {
        if (isupper(c)) {

            if (encrypt) {
                shiftE(&c, 'A', 'Z', offset);
            } else {
                shiftD(&c, 'A', 'Z', offset);
            }

            fprintf(output_file, "%c", c);

        } else if (islower(c)) {

            if (encrypt) {
                shiftE(&c, 'a', 'z', offset);
            } else {
                shiftD(&c, 'a', 'z', offset);
            }

            fprintf(output_file, "%c", c);

        } else {
            fprintf(output_file, "%c", c);
        }
    }

    if (encrypt) {
        printf("Your file was encrypted and written to encrypted.txt\n");
    } else {
        printf("Your file was decrypted and written to decrypted.txt\n");
    }

    exit(0);
}

int main(int argc, char **argv) {
    char *input_file_name;
    char *output_file_name;
    char c;
    int offset = 1;
    int encrypt;

    if (argc != 5) {
        printf("Invalid argument count!\n");
        help(argv);
    } else {
        while ((c = getopt(argc, argv, "E:e:D:d:s:S")) != -1) {
            switch (c) {
                case 'D':
                case 'd':
                    input_file_name = optarg;
                    offset *= -1;
                    encrypt = 0;
                    output_file_name = "decrypted.txt";
                    break;
                case 'E':
                case 'e':
                    input_file_name = optarg;
                    encrypt = 1;
                    output_file_name = "encrypted.txt";
                    break;
                case 's':
                case 'S':
                    offset *= atoi(optarg);
                    break;
                default:
                    printf("Invalid Input\n");
                    help(argv);
                    exit(1);
            }
        }

        if (offset > 26) {
            printf("Choose a shift value between 0 and 26\n");
            exit(1);
        }

        FILE *input_file, *output_file;

        input_file = fopen(input_file_name, "r");
        if (input_file == NULL) {
            fprintf(stderr, "Can't open input file %s!\n", input_file_name);
            exit(1);
        }

        output_file = fopen(output_file_name, "w");
        if (output_file == NULL) {
            fprintf(stderr, "Can't open output file %s!\n", output_file_name);
            exit(1);
        }

        readWriteFile(c, input_file, output_file, offset, encrypt);
    }

    return 0;
}

//tar -zcvf gerardo_mares_assignment0.tar.gz gerardo_mares_assignment0
//tar xvzf gerardo_mares_assignment0.tar.gz


Desktop/CompSec/Proj0/gerardo_mares_assignment0.tar.gz