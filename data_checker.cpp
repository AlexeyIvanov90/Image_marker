#include "data_checker.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include <opencv2/opencv.hpp>
#include <conio.h>
#include <vector>
#include <filesystem>


void verification_single_data_set(std::string file_csv) {
	std::filesystem::path path_csv(file_csv);

	std::string root_path =	path_csv.string().erase(path_csv.string().find(
		path_csv.filename().string()), path_csv.filename().string().length());

	std::string new_csv = root_path + "new_" + path_csv.filename().string();
	std::string delete_csv = root_path + "delete_" + path_csv.filename().string();

	std::fstream in_csv(file_csv, std::ios::in);
	std::fstream out_new_csv(new_csv, std::ios::in);
	std::fstream out_delete_csv(delete_csv, std::ios::in);

	std::string line;
	std::string last_line_new_csv;
	std::string last_line_delete_csv;

	std::vector<std::string> data;

	while (getline(out_new_csv, line))
		last_line_new_csv = line;
	out_new_csv.close();

	while (getline(out_delete_csv, line))
		last_line_delete_csv = line;
	out_new_csv.close();

	bool found_last_line_new = false;
	bool found_last_line_delete = false;

	if (last_line_new_csv.empty())
		found_last_line_new = true;

	if (last_line_delete_csv.empty())
		found_last_line_delete = true;

	while (getline(in_csv, line)) {
		if (found_last_line_new && found_last_line_delete)
			data.push_back(line);

		if (line == last_line_new_csv)
			found_last_line_new = true;

		if (line == last_line_delete_csv)
			found_last_line_delete = true;
	}

	in_csv.close();

	for each (auto path in data)
	{
		std::cout << path << std::endl;

		auto img = cv::imread(path);
		cv::resize(img, img, cv::Size({ img.cols * 3, img.rows * 3 }));
		cv::imshow("<-TRUE IMG FALSE->", img);
		cv::waitKey(1);

		int key;
		while (true) {
			key = _getch();
			if (key != 224)
				continue;
			key = _getch();
			if (key == 75 || key == 77)
				break;
		}

		if (key == 75) {
		std::ofstream out;
		out.open(new_csv, std::ios::app);
		if (out.is_open())
			out << path + "\n";
		out.close();
		}
		else {
			std::cout << "img delete from .csv" << std::endl;
			std::ofstream out;
			out.open(delete_csv, std::ios::app);
			if (out.is_open())
				out << path + "\n";
			out.close();
		}
	}
}
