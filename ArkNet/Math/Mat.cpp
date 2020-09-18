#include "Core/core.h"
#include "Mat.h"

namespace AN {

	void Mat::mul(Mat& src1, Mat& src2, Mat& dst) {
		size_t dst_rows = src1.m_rows;
		size_t dst_cols = src2.m_cols;
		dst.realloc(dst_rows, dst_cols);

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
	}

	Mat::Mat(Mat& src) {
		realloc(src.rows(), src.cols());
		for (size_t i = 0; i < m_rows; i++) {
			for (size_t j = 0; j < m_cols; j++) {
				at(i, j) = src.at(i, j);
			}
		}
	}

	Mat::Mat(size_t rows, size_t cols) {
		m_rows = rows;
		m_cols = cols;
		m_data.reset(new double[m_rows * m_cols]());
	}

	void Mat::mul(Mat& src, Mat& dst) const
	{
		if (m_cols != src.m_rows) {
			ARKNET_ERROR("not compatible matrix shapes!");
			return;
		}

		size_t dst_rows = m_rows;
		size_t dst_cols = src.m_cols;
		dst.realloc(dst_rows, dst_cols);


		for (size_t i = 0; i < dst_rows; i++) {
			for (size_t j = 0; j < dst_cols; j++) {

				double value = 0;
				for (size_t k = 0; k < m_cols; k++) {
					value += at(i, k) * src.at(k, j);
				}
				dst.at(i, j) = value;
			}
		}
	}

	void Mat::add(Mat& src) {

		if (src.cols() != m_cols || src.rows() != m_rows) {
			ARKNET_ERROR("not compatible matrix shapes!");
			return;
		}

		for (size_t i = 0; i < m_rows; i++) {
			for (size_t j = 0; j < m_cols; j++) {
				at(i, j) = at(i, j) * src.at(i, j);
			}
		}
	}

	Mat Mat::operator*(Mat& src) const
	{
		Mat out;
		mul(src, out);
		return out;
	}

	Mat Mat::operator+(Mat& src) const
	{

		if (src.cols() != m_cols || src.rows() != m_rows) {
			ARKNET_ASSERT((src.cols() != m_cols || src.rows() != m_rows), "not compatible matrix shapes!");
			ARKNET_ERROR("not compatible matrix shapes!");
			return Mat();
		}

		Mat out;
		out.realloc(m_rows, m_cols);
		for (size_t i = 0; i < m_rows; i++) {
			for (size_t j = 0; j < m_cols; j++) {
				out.at(i,j) = at(i, j) * src.at(i, j);
			}
		}
		return out;
	}


	void Mat::realloc(size_t rows, size_t cols) {
		m_rows = rows;
		m_cols = cols;
		m_data.reset(new double[m_rows * m_cols]());
	}

	//ToDo: do not reallocate memory if resize to a smaller matrix
	//		resize cuts off all values from the original that are out of the new range or pads with zeros
	void Mat::resize(size_t rows, size_t cols) {
		double* oldBuffer = new double[m_rows * m_cols]();
		memcpy(oldBuffer, m_data.get(), m_rows * m_cols * sizeof(double));
		size_t oldRows = m_rows;
		size_t oldCols = m_cols;

		realloc(rows, cols);

		size_t oldIdx;
		size_t newIdx;

		for (size_t i = 0; i < fmin(m_rows, oldRows); i++) {
			for (size_t j = 0; j < fmin(m_cols, oldCols); j++) {
				oldIdx = i * oldCols + j;
				newIdx = i * m_cols + j;

				m_data[newIdx] = oldBuffer[oldIdx];
			}
		}
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

	void Mat::copyTo(Mat& dst) {
		dst.realloc(m_rows, m_cols);
		memcpy(dst.data_raw(), m_data.get(), sizeof(double) * m_rows * m_cols);
	}

}