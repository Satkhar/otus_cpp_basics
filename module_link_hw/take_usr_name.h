
#ifndef TAKE_USER_NAME_H
#define TAKE_USER_NAME_H
#include <string>

int take_user_name(std::string* name, int* size, uint32_t* best_val);
int take_best_val(const std::string &high_scores_filename, const std::string &name, uint32_t* best_val);

#endif  //TAKE_USER_NAME_H