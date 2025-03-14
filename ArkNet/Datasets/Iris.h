#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include <random>
#include <algorithm>

#include "Math/Mat.h"

namespace AN {

	void get_iris_data_classification(std::vector<Mat>& rand_samples, std::vector<Mat>& rand_labels) {

		std::ifstream infile("Resources/iris.csv");
		std::string line;

		std::vector<Mat> samples, labels;

		while (std::getline(infile, line))
		{
			Mat sample(4, 1);
			Mat label(3, 1);

			size_t pos = 0;
			std::vector<double> numbers;
			while ((pos = line.find(",")) != std::string::npos) {
				std::string token = line.substr(0, pos);
				numbers.push_back(std::stod(token));
				line.erase(0, pos + 1);
			}
			numbers.push_back(std::stod(line));

			sample.at(0, 0) = numbers[0];
			sample.at(1, 0) = numbers[1];
			sample.at(2, 0) = numbers[2];
			sample.at(3, 0) = numbers[3];

			label.at(0, 0) = numbers[4];
			label.at(1, 0) = numbers[5];
			label.at(2, 0) = numbers[6];

			samples.push_back(sample);
			labels.push_back(label);
		}

		std::vector<int> indices;
		for (int i = 0; i < samples.size(); i++) {
			indices.push_back(i);
		}
		std::random_device rd;
		std::mt19937 g(rd());
		std::shuffle(indices.begin(), indices.end(), g);

		rand_samples.resize(samples.size());
		rand_labels.resize(samples.size());

		for (int i = 0; i < samples.size(); i++) {
			rand_samples[indices[i]] = samples[i];
			rand_labels[indices[i]] = labels[i];
		}

	}

	void get_iris_data_regression(std::vector<Mat>& rand_samples, std::vector<Mat>& rand_labels) {

		std::ifstream infile("Resources/iris.csv");
		std::string line;

		std::vector<Mat> samples, labels;

		while (std::getline(infile, line))
		{
			Mat sample(4, 1);
			Mat label(1, 1);

			size_t pos = 0;
			std::vector<double> numbers;
			while ((pos = line.find(",")) != std::string::npos) {
				std::string token = line.substr(0, pos);
				numbers.push_back(std::stod(token));
				line.erase(0, pos + 1);
			}
			numbers.push_back(std::stod(line));

			sample.at(0, 0) = numbers[0];
			sample.at(1, 0) = numbers[1];
			sample.at(2, 0) = numbers[2];
			sample.at(3, 0) = numbers[3];

			if (numbers[4] == 1.0) {
				label.at(0, 0) = 0;
			}
			if (numbers[5] == 1.0) {
				label.at(0, 0) = 1;
			}
			if (numbers[6] == 1.0) {
				label.at(0, 0) = 2;
			}

			samples.push_back(sample);
			labels.push_back(label);
		}

		std::vector<int> indices;
		for (int i = 0; i < samples.size(); i++) {
			indices.push_back(i);
		}
		std::random_device rd;
		std::mt19937 g(rd());
		std::shuffle(indices.begin(), indices.end(), g);

		rand_samples.resize(samples.size());
		rand_labels.resize(samples.size());

		for (int i = 0; i < samples.size(); i++) {
			rand_samples[indices[i]] = samples[i];
			rand_labels[indices[i]] = labels[i];
		}

	}
}