#include "data_checker.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include <opencv2/opencv.hpp>
#include <conio.h>
#include <vector>
#include <filesystem>


//left arrow - TRUE lable, right arrow - FALSE lable
void verification_error_CNN(std::string file_csv, std::string new_csv) {
	std::fstream in(file_csv, std::ios::in);
	std::string line;
	std::string path;
	std::string label;
	std::string result_nn;

	std::vector<std::string> data;

	while (getline(in, line))
		data.push_back(line);

	std::ofstream out;
	out.open(new_csv, std::ios::out);

	for each (auto str in data)
	{
		std::stringstream s(str);
		getline(s, path, ',');
		getline(s, label, ',');
		getline(s, result_nn, ',');

		std::cout << path << std::endl;
		std::cout << "label: " << label << std::endl;
		std::cout << "result_nn: " << result_nn << std::endl;

		auto img = cv::imread(path);

		cv::resize(img, img, cv::Size({ img.cols * 3, img.rows * 3}));

		cv::imshow("<-TRUE LABEL FALSE->", img);
		cv::waitKey(1);

		int key;

		while (true) {
			if (_getch() != 224)
				continue;
			key = _getch();
			if (key == 75 || key == 77)
				break;
		}

		if (key == 75)
			if (out.is_open())
				out << path + "\n";
		else
			std::cout << "img delete from .csv" << std::endl;		
	}

	out.close();
}


//verification data set (singl class, not lable)
void verification_single_data_set(std::string file_csv, std::string new_csv) {

	std::fstream in(file_csv, std::ios::in);
	std::fstream out(new_csv, std::ios::in);

	std::string line;
	std::string last_line;

	std::vector<std::string> data;

	while (getline(out, line))
		last_line = line;
	out.close();

	bool write_mode = false;

	if (last_line.empty())
		write_mode = true;

	while (getline(in, line)) {
		if (write_mode)
			data.push_back(line);

		if (!write_mode && line == last_line)
			write_mode = true;
	}

	in.close();

	for each (auto path in data)
	{
		std::cout << path << std::endl;

		auto img = cv::imread(path);
		cv::resize(img, img, cv::Size({ img.cols * 3, img.rows * 3 }));
		cv::imshow("<-TRUE IMG FALSE->", img);
		cv::waitKey(1);

		int key;
		while (true) {
			if (_getch() != 224)
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
		else 
			std::cout << "img delete from .csv" << std::endl;
	}

}


void verification_data_set(std::string file_csv, std::string new_csv){
	std::fstream in(file_csv, std::ios::in);
	std::string line;
	std::string path;
	std::string label;

	std::vector<std::string> data;

	while (getline(in, line))
		data.push_back(line);

	std::ofstream out;
	out.open(new_csv, std::ios::out);

	for each (auto str in data)
	{
		std::stringstream s(str);
		getline(s, path, ',');
		getline(s, label, ',');

		std::cout << path << std::endl;
		std::cout << "label: " << label << std::endl;

		auto img = cv::imread(path);

		cv::resize(img, img, cv::Size({ img.cols * 3, img.rows * 3 }));

		cv::imshow("<-TRUE LABEL FALSE->", img);
		cv::waitKey(1);

		int key;
		while (true) {
			if (_getch() != 224)
				continue;
			key = _getch();
			if (key == 75 || key == 77)
				break;
		}

		if (key == 75)
			if (out.is_open())
				out << path + "\n";
		else
			std::cout << "img delete from .csv" << std::endl;
	}

	out.close();
}