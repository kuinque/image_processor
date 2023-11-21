#include "filter.h"

Filter::Filter() : pixel_array_(nullptr) {
}

Filter::Filter(Matrix* origin) : pixel_array_(origin) {
}

Filter::~Filter() {
}

void Filter::CheckParametrsValidity(int parametrs_size, char* parametrs[]) {
}

void Filter::ApplyFilter(int parametrs_size, char* parametrs[]) {
}
