#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include "utils.h"

int string_to_int(const char *string) {
    char *endptr;
    long value;
    
    // Check for null pointer
    if (string == NULL) {
        return 0;
    }
    
    // Skip leading whitespace
    while (*string == ' ' || *string == '\t') {
        string++;
    }
    
    // Check for empty string
    if (*string == '\0') {
        return 0;
    }
    
    // Convert string to long
    errno = 0;
    value = strtol(string, &endptr, 10);
    
    // Check for conversion errors
    if (errno != 0 || *endptr != '\0') {
        return 0;
    }
    
    // Check for overflow/underflow
    if (value > INT_MAX || value < INT_MIN) {
        return 0;
    }
    
    return (int)value;
}