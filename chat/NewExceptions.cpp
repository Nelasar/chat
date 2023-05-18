#include "NewExceptions.h"

const char* bad_range::what() const noexcept {
	return "ERROR! Out of range!";
}
const char* bad_length::what() const noexcept {
	return "ERROR! Bad size format!";
}
const char* bad_index::what() const noexcept {
	return "ERROR! Wrong index format!";
}
const char* cant_open_file::what() const noexcept {
	return "ERROR! Can't open the file!";
}
