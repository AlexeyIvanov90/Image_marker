﻿#include <iostream>
#include "data_checker.h"



int main()
{
	std::string data_set = "../data_set/data_set.csv";
	std::string new_data_set = "../data_set/new_data_set.csv";

	verification_single_data_set(data_set, new_data_set);
}


