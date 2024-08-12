#include "other_lib.h"


double rescale(double var, double min, double max, double newmin, double newmax) {
    return ((((newmax) - (newmin)) / ((max) - (min))) * ((var) - (min)) + (newmin));
}