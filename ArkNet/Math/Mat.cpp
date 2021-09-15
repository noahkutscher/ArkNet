#include "Core/core.h"
#include "Mat.h"

namespace AN {

	bool operator==(MatSize a, MatSize b) {
		return (a.batch == b.batch) && (a.channel == b.channel) && (a.rows == b.rows) && (a.cols == b.cols);
	}


	//STATIC

	void Mat::mul(Mat& src1, Mat& src2, Mat& dst) {
		ARKNET_ASSERT(src1.batch() == src2.batch(), "Number of batches dont match during dot product")
		ARKNET_ASSERT(src1.channel() == src2.channel(), "Number of channels dont match during dot product")
		ARKNET_ASSERT(src1.cols() == src2.rows(), "not compatible matrix shapes!");

		MatSize dstSize = {src1.batch(), src1.channel(), src1.rows(), src2.cols()};
		dst.realloc(dstSize);

		for(size_t b = 0; b < dstSize.batch; b++) {
			for(size_t c = 0; c < dstSize.channel; c++) {
				for (size_t i = 0; i < dstSize.rows; i++) {
					for (size_t j = 0; j < dstSize.cols; j++) {

						double value = 0;
						for (size_t k = 0; k < src1.cols(); k++) {
							value += src1.at(b, c, i, k) * src2.at(b, c, k, j);
						}
						dst.at(b, c, i, j) = value;
					}
				}
			}
		}
	}

	Mat Mat::abs(Mat& src)
	{
		Mat out;
		out.realloc(src.size());
		for (size_t i = 0; i < src.elems(); i++) {
			out.at(i) = src.at(i) < 0 ? src.at(i) * -1 : src.at(i);
		}
		return out;
	}

	double Mat::sum(Mat& src)
	{
		double out = 0.0;

		for (size_t i = 0; i < src.elems(); i++) {
			out += src.at(i);
		}

		return out;
	}

	// transpose over rows and cols (not affecting batch and channel axis)
	Mat Mat::transpose(Mat& src)
	{
		Mat out;
		out.realloc({src.batch(), src.channel(), src.cols(), src.rows()});
		for(size_t b = 0; b < src.batch(); b++) {
			for(size_t c = 0; c < src.channel(); c++) {
				for (size_t i = 0; i < src.rows(); i++) {
					for (size_t j = 0; j < src.cols(); j++) {
						out.at(b, c, j, i) = src.at(b, c, i, j);
					}
				}
			}
		}
		return out;
	}

	Mat Mat::log(Mat& src)
	{
		Mat out;
		out.realloc(src.size());
		for (size_t i = 0; i < src.elems(); i++) {
			out.at(i) = std::log(src.at(i));
		}
		return out;
	}

	// STATIC END

	Mat::Mat() {
		m_size = {1, 1, 1, 1};
		m_data.reset(new double[m_size.batch * m_size.channel * m_size.rows * m_size.cols]());
	}

	Mat::Mat(MatSize size) {
		m_size = size;
		m_data.reset(new double[m_size.batch * m_size.channel * m_size.rows * m_size.cols]());
	}

	Mat::Mat(size_t rows, size_t cols) {
		m_size = {1, 1, rows, cols};
		m_data.reset(new double[m_size.batch * m_size.channel * m_size.rows * m_size.cols]());
	}

	// dot product over rows and cols (not affecting batch and channel axis)
	void Mat::mul(Mat& src, Mat& dst) const
	{
		ARKNET_ASSERT(m_size.batch == src.batch(), "Number of batches dont match during dot product")
		ARKNET_ASSERT(m_size.channel == src.channel(), "Number of channels dont match during dot product")
		ARKNET_ASSERT(cols() == src.rows(), "not compatible matrix shapes!");

		MatSize dstSize = {src.batch(), src.channel(), rows(), src.cols()};
		dst.realloc(dstSize);

		for(size_t b = 0; b < dstSize.batch; b++) {
			for(size_t c = 0; c < dstSize.channel; c++) {
				for (size_t i = 0; i < dstSize.rows; i++) {
					for (size_t j = 0; j < dstSize.cols; j++) {

						double value = 0;
						for (size_t k = 0; k < cols(); k++) {
							value += at(b, c, i, k) * src.at(b, c, k, j);
						}
						dst.at(b, c, i, j) = value;
					}
				}
			}
		}
	}

	void Mat::mul(double scalar, Mat& dst) const
	{
		dst.realloc(m_size);
		for (size_t i = 0; i < elems(); i++) {
			dst.at(i) = at(i) * scalar;
		}
	}

	void Mat::mul_elem(Mat& src, Mat& dst) const
	{
		dst.realloc(m_size);
		for (size_t i = 0; i < elems(); i++) {
			dst.at(i) = at(i) * src.at(i);
		}
	}

	void Mat::add(Mat& src)
	{
		ARKNET_ASSERT(src.size() == m_size, "not compatible matrix shapes!");

		for (size_t i = 0; i < elems(); i++) {
			at(i) = at(i) + src.at(i);
		}
	}

	// * defaults to dot product not element wise multiplication
	Mat Mat::operator*(Mat& src) const
	{
		Mat out;
		mul(src, out);
		return out;
	}

	Mat Mat::operator*(double scalar) const
	{
		Mat out;
		mul(scalar, out);
		return out;
	}

	double Mat::max()
	{
		double max_out = 0;
		for(size_t i = 0; i < elems(); i++) {
			if(at(i) > max_out)
				max_out = at(i);
		}
		return max_out;
	}

	Mat Mat::operator+(Mat& src) const
	{
		ARKNET_ASSERT(src.size() == m_size, "not compatible matrix shapes!");
		Mat out;
		out.realloc(m_size);
		for (size_t i = 0; i < elems(); i++) {
			out.at(i) = at(i) + src.at(i);
		}
		return out;
	}

	Mat Mat::operator-(Mat& src) const
	{
		ARKNET_ASSERT(src.size() == m_size, "not compatible matrix shapes!");
		Mat out;
		out.realloc(m_size);
		for (size_t i = 0; i < elems(); i++) {
			out.at(i) = at(i) - src.at(i);
		}
		return out;
	}


	void Mat::realloc(MatSize size) {
		m_size = size;
		m_data.reset(new double[m_size.batch * m_size.channel * m_size.rows * m_size.cols]());
	}

	void Mat::reset(double* ptr)
	{
		m_data.reset(ptr);
	}

	//ToDo: do not reallocate memory if resize to a smaller matrix
	//		resize cuts off all values from the original that are out of the new range or pads with zeros
	void Mat::resize(MatSize size) {
		
		#ifdef ARKNET_DEBUG
			ARKNET_INFO("resize method called, if no data needs to be copied call the realloc method")
		#endif

		size_t buffer_size = m_size.batch * m_size.channel * m_size.rows * m_size.cols;
		std::shared_ptr<double[]> oldBuffer(new double[buffer_size]());
		memcpy(oldBuffer.get(), m_data.get(), buffer_size * sizeof(double));
		MatSize oldSize = m_size;

		realloc(size);

		size_t oldIdx;
		size_t newIdx;

		size_t old_batch_ptr;
		size_t batch_ptr;
		size_t old_channel_ptr;
		size_t channel_ptr;
		size_t old_row_ptr;
		size_t row_ptr;


		for (size_t b = 0; b < fmin(m_size.batch, oldSize.batch); b++) {

			batch_ptr = b * m_size.channel * m_size.rows * m_size.cols;
			old_batch_ptr = b * oldSize.channel * oldSize.rows * oldSize.cols;

			for (size_t c = 0; c < fmin(m_size.channel, oldSize.channel); c++) {

				channel_ptr = c * m_size.rows * m_size.cols;
				old_channel_ptr = c * oldSize.rows * oldSize.cols;

				for (size_t i = 0; i < fmin(m_size.rows, oldSize.rows); i++) {

					row_ptr = i * m_size.channel;
					old_row_ptr = i * oldSize.channel;

					for (size_t j = 0; j < fmin(m_size.cols, oldSize.cols); j++) {
						
						oldIdx = old_batch_ptr + old_channel_ptr + old_row_ptr + j;
						newIdx = batch_ptr + channel_ptr + row_ptr + j;

						m_data[newIdx] = oldBuffer[oldIdx];
					}
				}
			}
		}	
	}

	void Mat::print() {
		std::cout << "[ ";
		for (size_t b = 0; b < m_size.batch; b++) {
			std::cout << "[ ";
			for (size_t c = 0; c < m_size.channel; c++) {
				std::cout << "[ ";
				for (size_t i = 0; i < m_size.rows; i++) {
					std::cout << "[ ";
					for (size_t j = 0; j < m_size.cols; j++) {
						double value = at(b, c, i, j);
						std::cout << value << ", ";
					}
					std::cout << "], " << std::endl;
				}
				std::cout << "], " << std::endl;
			}
			std::cout << "], " << std::endl;
		}
		std::cout << "]" << std::endl;
	}

	void Mat::copyTo(Mat& dst) {
		dst.realloc(m_size);
		size_t buffer_size = m_size.batch * m_size.channel * m_size.rows * m_size.cols;
		memcpy(dst.data_raw(), m_data.get(), sizeof(double) * buffer_size);
	}

}