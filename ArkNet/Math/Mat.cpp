#include "Mat.h"

namespace AN {

	void Mat::mul(Mat& src1, Mat& src2, Mat& dst) {
		size_t dst_rows = src1.m_rows;
		size_t dst_cols = src2.m_cols;
		dst.resize(dst_rows, dst_cols);

		if (src1.m_cols != src2.m_rows) {
			printf("[ERROR] not compatible matrix shapes!\n");
			return;
		}

		for (size_t i = 0; i < dst_rows; i++) {
			for (size_t j = 0; j < dst_cols; j++) {

				double value = 0;
				for (size_t k = 0; k < src1.m_cols; k++) {
					value += src1.at(i, k) * src2.at(k, j);
				}
				dst.at(i, j) = value;
			}
		}
	}


	Mat::Mat() {
		m_rows = 0;
		m_cols = 0;
		m_data = nullptr;
	}

	Mat::Mat(size_t rows, size_t cols) {
		m_rows = rows;
		m_cols = cols;
		m_data.reset(new double[m_rows * m_cols]());
	}

	double& Mat::at(size_t row, size_t col) {
		size_t idx = row * m_cols + col;
		return m_data[idx];
	}

	void Mat::resize(size_t rows, size_t cols) {
		m_rows = rows;
		m_cols = cols;
		m_data.reset(new double[m_rows * m_cols]());
	}

	void Mat::log() {
		for (size_t i = 0; i < m_rows; i++) {
			for (size_t j = 0; j < m_cols; j++) {
				double value = at(i, j);
				std::cout << value << ", ";
			}
			std::cout << "" << std::endl;
		}
	}

	void Mat::copyTo(Mat & dst) {
		dst.resize(m_rows, m_cols);
		memcpy(dst.data_raw(), m_data.get(), sizeof(double) * m_rows * m_cols);
	}

}