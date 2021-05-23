#include "errors.h"



int error_catcher(error_t err) {
    if (NoErrors == err) {
        return 0;
    }
    else {
        switch(err) {
            case MemoryError:
            fprintf(stderr, "Memory allocation error");
            break;
            case LoopError:
            fprintf(stderr, "Loop has been created");
            break;
            case WeightOutOfRangeError:
            fprintf(stderr, "Weight out range");
            break;
            case VertexNotExistsError:
            fprintf(stderr, "Vertex accessing to does not exists");
            break;
            case UnknownError:
            fprintf(stderr, "Unknown error");
            break;
            case InvalidArg:
            fprintf(stderr, "Invalid argument");
            break;
            default:
            ;
        }
        fprintf(stderr, "\n");
        return -1;
    }
}