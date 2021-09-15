#pragma once

#include <cmath>
#include <memory>
#include <iostream>
#include <cstring>

#include "Core/core.h"

// TODO: Rewrite Matrix class to be 4 dimensional defaulting to lower dimensions

namespace AN {

	struct MatSize{
		size_t batch = 1;
		size_t channel = 1;
		size_t rows = 1;
		size_t cols = 1;
	};

	class Mat {

	public:
		ARKNET_EXPORT static void mul(Mat& src1, Mat& src2, Mat& dst);
		ARKNET_EXPORT static Mat abs(Mat& src1);
		ARKNET_EXPORT static double sum(Mat& src);
		ARKNET_EXPORT static Mat transpose(Mat& src);
		ARKNET_EXPORT static Mat log(Mat& src);
	
	private:
		MatSize m_size;
		std::shared_ptr<double[]> m_data;
	
	public:
		ARKNET_EXPORT Mat();
		ARKNET_EXPORT Mat(MatSize size);
		ARKNET_EXPORT Mat(size_t rows, size_t cols);
		ARKNET_EXPORT ~Mat() = default;

		ARKNET_EXPORT void copyTo(Mat& dst);
		ARKNET_EXPORT void print();
		ARKNET_EXPORT void realloc(MatSize size);
		ARKNET_EXPORT void resize(MatSize size);
		ARKNET_EXPORT void reset(double* ptr);
		ARKNET_EXPORT void add(Mat& src);

		ARKNET_EXPORT void mul(Mat& src, Mat& dst) const;
		ARKNET_EXPORT void mul(double scalar, Mat& dst) const;
		ARKNET_EXPORT void mul_elem(Mat& src, Mat& dst) const;

		ARKNET_EXPORT Mat operator+(Mat& src) const;
		ARKNET_EXPORT Mat operator-(Mat& src) const;
		ARKNET_EXPORT Mat operator*(Mat& src) const;
		ARKNET_EXPORT Mat operator*(double scalar) const;

		ARKNET_EXPORT inline double* data_raw() const { return m_data.get(); }
		ARKNET_EXPORT inline size_t batch() const { return m_size.batch; }
		ARKNET_EXPORT inline size_t channel() const { return m_size.channel; }
		ARKNET_EXPORT inline size_t rows() const { return m_size.rows; }
		ARKNET_EXPORT inline size_t cols() const { return m_size.cols; }
		ARKNET_EXPORT inline size_t elems() const { return (m_size.batch * m_size.channel * m_size.rows * m_size.cols); }
		ARKNET_EXPORT inline MatSize size() const { return m_size; }

		ARKNET_EXPORT inline double max();
		
		ARKNET_EXPORT inline double& at(size_t row, size_t col) const {
			ARKNET_ASSERT(row < m_size.rows && col < m_size.cols, "tried to get an item out of range!");
			return at(0, 0, row, col);
		}

		ARKNET_EXPORT inline double& at(size_t batch, size_t channel, size_t row, size_t col) const {
			ARKNET_ASSERT(batch < m_size.batch && channel < m_size.channel && row < m_size.rows && col < m_size.cols, "tried to get an item out of range!");
			size_t batch_ptr = batch * m_size.channel * m_size.rows * m_size.cols;
			size_t channel_ptr = channel * m_size.rows * m_size.cols;
			size_t row_ptr = row * m_size.channel;
			return m_data[batch_ptr + channel_ptr + row_ptr + col];
		}

		ARKNET_EXPORT inline double& at(size_t idx) const {
			ARKNET_ASSERT(idx < elems(), "tried to get an item out of range!");
			return m_data[idx];

		}

	};

}